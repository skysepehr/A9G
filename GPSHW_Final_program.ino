#include <FS.h>
#define TINY_GSM_MODEM_A7  //Defining model of modem
//#define TINY_GSM_DEBUG Serial

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <TinyGsmClient.h>
#include <TinyGPS++.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h> 
#include <DNSServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include "SSD1306.h"
#include "index.h"
#define Modem_PWR_Pin 16  ///////Define esp8266pin to Active_HIGH Power UP through PNP 2N3906 Transistor Connected to power Pin on A7 PWR
#define BUZZER_Pin 2 //Buzzer pin 
#define switch_Pin 0 //switch pin 
#define PUSH_button 10 //Push Button manual position send


////////////////////////////////////////////////////////////////////// Your GPRS credentials
//////////////////////////////////////////////////////////////////// Leave empty, if missing user or pass
String apn  = "";// (mcinet) for Hamrah Aval (mtnirancell) for irancell
String user = "";
String pass = "";

const char* update_path = "/firmware"; //internal server update path
 
String owner_number="";   //authorized owner phone number to accept calls
String HOST = "";  ///////Traccar server address
String port =""; ///////Traccar server port
String ID="";  ///////Traccar Device ID
String gps_mode="";///////GPS or AGPS mode
uint16_t port_int; ///////Traccar server port
const char *apname="GPS A9G" ;
int config_pointer = 0; ///////flag to allow or not allow send gps info by gprs

unsigned long startgprs;     ///variable that Holds Last GPRS Send Time
String response;  //recived response by Host 

String Switch_State= "0" ;//last state of relay

String Send_interval_str;
uint32_t Send_interval;

////////GPS Variables/////////
String latitude;    
String Longitude;
String HOUR;
String MINUTE;
String SECOND;
String YEAR;
String MONTH;
String DAY;
String SATELITES;
String COURSE;
String HDOP;
String ALTITUDE="0.00";
String SPEED="0";

ESP8266HTTPUpdateServer httpUpdater; //internal update server instance

// DNS server
const byte DNS_PORT = 53;
DNSServer dnsServer;

/* Soft AP network parameters */
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

SSD1306  display(0x3c, 4, 5); //define Instance for  OLED1306 Library
ESP8266WebServer server(80);  ////server instance
TinyGPSPlus gps;  // The TinyGPS++ object


SoftwareSerial GPS_Serial(13,15);   //D7,D8 The serial connection to the GPS device nodeMCU(RX,TX)

SoftwareSerial GSM_Serial(14,12);   //D5,D6 The serial connection to the GSM device nodeMCU(RX,TX)

TinyGsm modem(GSM_Serial);  // Define Tiny GSM Modem instance

TinyGsmClient GSM_client(modem);  //Define GPRS client with GSM Modem Instance

//////file instance///
File myFile ;
///////////////////////////////////////////////////////////////////////////////////////////////////Begin Of SetUP
void setup() {
  ESP.wdtDisable(); //disable software wdt to prevent resets
  ESP.wdtEnable(8000); //enable software wdt and set time to 8 second to prevent resets
  WiFi.mode(WIFI_OFF);
 SPIFFS.begin();
 
   display.init();
   display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    
     pinMode(Modem_PWR_Pin ,OUTPUT);
     pinMode(BUZZER_Pin,OUTPUT);
     pinMode(switch_Pin,OUTPUT);
     pinMode(PUSH_button,INPUT);
     
      digitalWrite(Modem_PWR_Pin ,HIGH);
      digitalWrite(BUZZER_Pin,HIGH);
       
     Serial.begin(115200);
     GSM_Serial.begin(115200);
     GPS_Serial.begin(9600);
     delay(1000);
     server.on("/",[](){server.send(200,"text/html",INDEX_Page);});
     server.on("/reset",[](){server.send(200,"text/plain","Reseting  Device in 3 Second");delay(3000);ESP.reset();});
   server.on("/config",save_config);
  server.onNotFound([](){server.send(302,"text/html",INDEX_Page);});
  httpUpdater.setup(&server, update_path);//run internal update server
    server.begin();
    
             /* Setup the DNS server redirecting all the domains to the apIP */
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);
  
  if (digitalRead(PUSH_button)==LOW){SET_Default();}
  read_SW_state();
  read_config();
     if(config_pointer==0){ RUN_GPSHW();}
}
//////////////////////////////////////////////////////////////////////////////////////////////////End Of Setup


///////////////////////////////////////////////////////////////////////////////////////////////Begin of Loop
void loop() {
  ESP.wdtFeed(); ///feed hardware watchdog
      //DNS
  dnsServer.processNextRequest();
  server.handleClient();
 if(config_pointer==0){
   if(millis()/1000 > 300 && YEAR == "2000" ){ESP.reset();}  // check if GPS is started or not to reset again
   
  checkcall();
   check_GPS(1000); //check and encode NMEA GPS responses
 

  if (millis() > 5000 && gps.charsProcessed() < 10){     ///check if GPS Sent Charachters or not
    
  display.clear();
  display.drawString(0, 33, "Nochars received");
    Serial.println(F("No GPS data received: check wiring"));
    display.display();
    
  }else{
    
display.clear();
                                          // PUT Encoded GPS to Variables
 latitude =String (gps.location.lat(),6); 
 Longitude=String (gps.location.lng(),6);
 HOUR=String(gps.time.hour());
 MINUTE=String(gps.time.minute());
 SECOND=String(gps.time.second());
 YEAR=String(gps.date.year());
 MONTH=String(gps.date.month());
 DAY=String(gps.date.day());
 SATELITES =String(gps.satellites.value());
 ALTITUDE =String(gps.altitude.meters());
 SPEED=String(gps.speed.knots());
 COURSE=String(gps.course.deg());
 HDOP=String(gps.hdop.value());
 ///////////////////////////////////////show GPS Variables on OLED
display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Latitude: "+latitude);
  display.drawString(0, 10, "Longitude: "+Longitude);
  display.drawString(0, 21, "Date : "+MONTH+"/"+DAY+"/"+YEAR);
  display.drawString(0, 32, "Time UTC : "+HOUR+":"+MINUTE+":"+SECOND);
  display.drawString(0, 43, "NO. of Satelites : "+SATELITES);
  display.drawString(0, 54, "Altitude Meters : "+ALTITUDE);
  display.display();
  }
  
  ///check if GPS Fixed or Not to send position to Server
  if(ALTITUDE!="0.00"){
    Send_position(Send_interval_str); //check for interval if reached then send position
    } 
    
  ///Manual send Position to Server with Push Button
if(digitalRead(PUSH_button)==LOW){
   BUZZER(100,30,5);      //BUZZ  Delay BUZZ lenght100 ms  and silence length 30 ms ,2 time
  Turn_AP_ON(); //Turn ON AP Mode
  //send_GPRS();
  }
 }
}
   
/////////////////////////////////////////////////////////////////////////end of Looop

////////////////////////////////////////////////////////////Function to Startup GSM modem A7 
void RUN_GPSHW(){
  GSM_Serial.flush();
  delay(30);
   POWER_UP_A7();
   
 
///////////////////////initialize setup for GSM Modem
    if(modem.begin()=="true"){  
      Serial.println("Modem is initialized");
       display.drawString(0, 10, "Modem is Initialized");
       display.display();
       BUZZER(100,30,2);      //BUZZ  Delay BUZZ lenght100 ms  and silence length 30 ms ,2 time
    }else{
    Serial.println(modem.begin());
         display.drawString(0, 10, modem.begin());
       display.display();
       BUZZER(300,500,3);      //BUZZ  Delay BUZZ lenght 300 ms  and silence length 500 ms ,3 time
       delay(5000);
       ESP.reset();
    }

//////////////////////////////////////////Check if SIM CARD exists
    
    if(modem.getSimStatus()==SIM_READY){
      Serial.println("SIM Card is Ready");
      display.drawString(0, 21, "SIM Card is Ready");
       display.display();
        BUZZER(100,30,2);      //BUZZ  Delay BUZZ lenght100 ms  and silence length 30 ms ,2 time
    }else{
      Serial.println(F("SIM Card is NOT Ready"));
       display.drawString(0, 21, (F("SIM Card is noT Ready")));
       display.display();
          BUZZER(300,500,3);      //BUZZ  Delay BUZZ lenght 300 ms  and silence length 500 ms ,3 time
       delay(5000);
       ESP.reset();
      return;
      }
      ///////////////////////////////////////Check mobile Network Status
   Serial.print("Waiting for network...");
  if (!modem.waitForNetwork()) {             
    Serial.println(" Failed");
     display.drawString(0, 32, "Failed Newtwork ");
       display.display();
       BUZZER(300,500,3);      //BUZZ  Delay BUZZ lenght 300 ms  and silence length 500 ms ,3 time
       delay(5000);
       ESP.reset();
    return;
  }
   BUZZER(100,30,2);      //BUZZ  Delay BUZZ lenght100 ms  and silence length 30 ms ,2 time
   display.drawString(0, 32, "Network OK");
       display.display();
  Serial.println(" OK");

  
   Serial.print("Connecting to ");
  Serial.print(apn);
  GSM_Serial.flush();
  delay(1000);
   ////////////////////////////////////////////////Connecting to GPRS DATA Service

  if (!modem.gprsConnect(apn.c_str(),user.c_str(),pass.c_str())) {
    Serial.println(" Failed");
     display.drawString(0, 43, "Failed APN Connect ");
       display.display();
       BUZZER(300,500,3);      //BUZZ  Delay BUZZ lenght 300 ms  and silence length 500 ms ,3 time
       delay(5000);
       ESP.reset();
    return;
  }
  
  BUZZER(100,30,2);      //BUZZ  Delay BUZZ lenght100 ms  and silence length 30 ms ,2 time
 Serial.println(" OK");
  
  
  if(gps_mode=="AGPS"){Serial.print("Start AGPS"); modem.agps_start();}else{Serial.print("Start GPS");modem.gps_start();} //switch between AGPS Or GPS 
  
Serial.println(" OK");
  display.drawString(0, 43, "GPRS-GPS OK ");
       display.display();
        BUZZER(100,30,4);      //BUZZ  Delay BUZZ lenght100 ms  and silence length 30 ms ,2 time
       delay(2000);
}

////////////////////////////////////////////////////////////////////smart Function to Read all NMEA Responses and Encode them...
static void check_GPS(unsigned long ms)
{
  unsigned long startgps = millis();
  do 
  {
    while (GPS_Serial.available())
      gps.encode(GPS_Serial.read());
  } while (millis() - startgps < ms);
}


///////////////////////////////////////////////////////////function to check last Time sent GPS position to server
static void Send_position(String s)
{
  Send_interval=s.toInt();
if (millis() - startgprs >= Send_interval*1000){
  send_GPRS();
  startgprs = millis();
}
}

//////////////////////////////////////////////////////////////Function to Send Positions to Server
   void send_GPRS(){ 
   gprs: 
    BUZZER(75,30,3);      //BUZZ  Delay BUZZ lenght 150 ms  and silence length 30 ms ,3 time
 Serial.print("Connecting to "); //Command debug
        display.clear();
        display.drawString(0, 0, "Connecting to");
         display.drawString(0, 11,HOST);
         display.display();
        GSM_Serial.flush(); 
        delay(30);
  Serial.println(HOST);  //debug terminal
 port_int=port.toInt();

  GSM_Serial.println("AT+CIPSTART=\"TCP\",\""+HOST+"\","+port_int); //Direct Send Data for GSM to connect Server
  Serial.println("AT+CIPSTART=\"TCP\",\""+HOST+"\","+port_int); //Command debug
  Wait_Response(76000,response);
  Serial.print("Response:"+response);
  if (response.startsWith("ERROR")||response.startsWith("COMMAND NO RESPONSE!") ){ //check to see if server is online or not
    BUZZER(300,200,4);
    GSM_Serial.println("AT+CIPCLOSE");
    GSM_Serial.println("AT+CIPSHUT");
    GSM_Serial.flush();
    delay(5000);
    goto gprs;
  }
 
    GSM_Serial.flush();
    delay(30);
GSM_Serial.println("AT+CIPSEND"); // Direct Send Data Through TCP or UDP conncetion 
 Serial.println("AT+CIPSEND");    //Command debug
Wait_Response(2000,response);
GSM_Serial.println("GET /?id="+ID+"&lat="+latitude+"&lon="+Longitude+"&altitude="+ALTITUDE+"&speed="+SPEED+"&bearing="+COURSE+"&hdop="+HDOP+" HTTP/1.1");     //Sending Resource Header
 Serial.println("GET /?id="+ID+"&lat="+latitude+"&lon="+Longitude+"&altitude="+ALTITUDE+"&speed="+SPEED+"&bearing="+COURSE+"&hdop="+HDOP+" HTTP/1.1");     //Command debug
 
   display.drawString(0, 21,"latitude:"+latitude );
   display.drawString(0, 32,"Longitude:"+Longitude );
   display.drawString(0, 43,"SPD."+SPEED+" ALT."+ALTITUDE);
       display.display();
       
GSM_Serial.println("HOST: "+HOST); //Sendig HOST Header
Serial.println("HOST: "+HOST);         //Command debug
GSM_Serial.println("Connection: close");       //Sending End Header
Serial.println("Connection: close");         //Command debug
GSM_Serial.println("");  //end of Header
Serial.println("");      //Command debug
GSM_Serial.println((char)26);      //Send Data to GPRS modem equels to CTRL+Z or 1A HEX((char)0X1A)
Serial.println((char)26);        //Command debug
  Serial.println(" OK");     //Command debug
 Wait_Response(20000,response);
Serial.print("Response:"+response);
   GSM_Serial.println("AT+CIPCLOSE");   ////Closing TCP Connection
   GSM_Serial.flush();
   delay(500);
 display.drawString(0, 54, "Server Disconnected");
       display.display();
       BUZZER(200,100,1);      //BUZZ  Delay BUZZ lenght 200 ms  and silence length 100 ms ,1 time
       Serial.println();
       
 Serial.println("Server disconnected");  //Command debug


} 
///////////////////////////////////////////////////////Function to Powerup A7 module
void POWER_UP_A7(){
   display.clear();
  display.drawString(0, 0, "Reseting Modem");
  Serial.println("");
    Serial.println(F("Reseting Modem"));
    display.display();
    delay(1000);
  modem.restart(); ////////Reboot Modem if  it's ON
  delay(3000);
   GSM_Serial.flush();
   delay(1000);
  digitalWrite(Modem_PWR_Pin ,0);
  delay(3000);
  digitalWrite(Modem_PWR_Pin ,1);
   Serial.println("");
    display.clear();
  display.drawString(0, 0, "Waiting for A9G Module..");
    Serial.println(F("Waiting for A9G Module to Start.."));
    display.display();
   delay(20000);            ///Wait for Modem  to compeletly  Boot
   GSM_Serial.flush();      //so important to flush Junk Data
    delay(1000);
}
/////////////////////////////////////////////////////////////////////////Buzzer Function 
void BUZZER(uint16_t timout1,uint16_t timout2,uint16_t count){
  for (int i=0;i<count;i++){
  digitalWrite(BUZZER_Pin,LOW);
       delay(timout1);
       digitalWrite(BUZZER_Pin,HIGH); 
       delay(timout2);
  }
}
                     ///////////////////////////////////////////////////////Check incomig Call 
void checkcall(){
  
 
  while(GSM_Serial.available()){
    String number=modem.Check_call();
    
    if(number == "no_call"){
         
   
    return;
    }
    if(number == owner_number){  // this can check whether its owner or some body else
    Serial.println("Called Number accepted");
    delay(1000);
     modem.enableSpeaker(1); /// enable OUTPUT Speaker 
      delay(1000);
      modem.callAnswer(); // answer the CALL 
      delay(1);
      if (digitalRead(switch_Pin)==LOW){
        Switch_State="1";
        save_SW_state(); // save state of Switch_pin to SPIFFS
        digitalWrite(switch_Pin,HIGH); /////////this will turn on a relay then you can connect Between NC and Common pins of relay with NPN Transistor to switch off CAR 
        //BUZZER(150,100,5);/////////////////////////////to Sniffing silently inside the car you can omit this line
     display.clear();
    display.setFont(ArialMT_Plain_16);
  display.drawString(29, 10, "Relay ON");
  display.drawString(20, 26, "Call Answerd");
       display.display();  
       modem.sendSMS(number,"your Device Location is :\n Latitude: "+latitude+"\n Longitude: "+Longitude); // send device location by SMS
       Wait_Response(3600000,response);
       GSM_Serial.println("ATH"+number);// to hang up phone
      }else{
         Switch_State="0";
        save_SW_state(); // save state of Switch_pin to SPIFFS
        digitalWrite(switch_Pin,LOW); ///this will reverse relay
        BUZZER(75,30,10);
             display.clear();
    display.setFont(ArialMT_Plain_16);
  display.drawString(29, 10, "Relay OFF");
  display.drawString(20, 26, "Call Answerd");
       display.display(); 
        modem.sendSMS(number,"your Device Location is :\n Latitude: "+latitude+"\n Longitude: "+Longitude); // send device location by SMS
        Wait_Response(3600000,response);
         GSM_Serial.println("ATH"+number);// to hang up phone
        }
   
     GSM_Serial.flush();
 delay(30);
   }else{
      display.clear();
      display.setFont(ArialMT_Plain_16);
      display.drawString(0,0,"Incoming CALL..");
      display.drawString(0,20,number);
       display.display();
       Serial.println("unauthorized number"+number);
       BUZZER(75,30,15);
    delay(1000);
    
 GSM_Serial.flush();
    }

}
}
//////////////////////////////////////TURN ON AP MODE//////////////////
void Turn_AP_ON(){
  config_pointer=1;
  WiFi.mode(WIFI_AP);
    WiFi.softAP(apname);
    delay(500);
     display.clear();
    display.setFont(ArialMT_Plain_16);
  display.drawString(30, 10, apname);
  display.drawString(20, 26, "Config Mode");
  display.drawString(20, 48, "192.168.4.1");
  Serial.println("");
    Serial.println(F("Config Mode"));
    display.display();
}
///////////////////////////////////////////////////////////saving configurations
void save_config(){
  apn=server.arg("APN");
  user=server.arg("USER");
  pass=server.arg("PASSWORD");
  HOST=server.arg("TRACCAR");
  port=server.arg("PORT");
  ID=server.arg("ID");
  gps_mode=server.arg("MODE");
  owner_number=server.arg("NUMBER");
  Send_interval_str=server.arg("interval");
  
   DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["APN"]=apn;
    json["USER"]=user;
    json["PASSWORD"]=pass;
    json["TRACCAR"]=HOST;
    json["PORT"]=port;
    json["ID"]=ID;
    json["MODE"]=gps_mode;
    json["NUMBER"]=owner_number;
    json["interval"]=Send_interval_str;
    
     myFile = SPIFFS.open("/CONFIG.TXT","w");
  if (!myFile) {
    Serial.println("Failed to open config file ");
   return;
  }
json.printTo(myFile);
 
  myFile.close();
   server.send(200,"text/plain","Config settings Saved and Device Rebooted");
        display.clear();
    display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "Device Config");
  display.drawString(33, 26, "Saved!!");
  display.drawString(0, 48, "Reseting...");
  Serial.println("");
    Serial.println(F("Config Mode"));
    display.display();
    delay(3000);
    ESP.restart();
}
 ////////////////////////////////////////////////////////Save Switch pin Status
void save_SW_state(){
  DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["SW"]=Switch_State;
       myFile = SPIFFS.open("/SW.TXT","w");
  if (!myFile) {
    Serial.println("Failed to open SW file ");
   return;
  }
json.printTo(myFile);
  myFile.close();
}
//////////////////////////////////////read Switch pin Status
void read_SW_state(){
  myFile = SPIFFS.open("/SW.TXT","r");///open config.txt file
        String config_str = myFile.readString();
 DynamicJsonBuffer jsonBuffer1;
  JsonObject& json1 = jsonBuffer1.parseObject(config_str); //parse json format from string_str
  if (!json1.success()) {
   display.clear();
     display.setFont(ArialMT_Plain_10);
     display.drawString(0, 33, "Failed to parse SW file.\n Relay OFF");
    display.display();
Switch_State="0";
digitalWrite(switch_Pin,0);
    return;
  }
  Switch_State=json1["SW"].as<String>();
  myFile.close();
  if (Switch_State=="0"){
    digitalWrite(switch_Pin,0);
  }else{
    digitalWrite(switch_Pin,1);
  }
}
/////////////////////////////////Read main config Files
void read_config(){
 myFile = SPIFFS.open("/CONFIG.TXT","r");///open config.txt file
        String config_str = myFile.readString();
 DynamicJsonBuffer jsonBuffer1;
  JsonObject& json1 = jsonBuffer1.parseObject(config_str); //parse json format from string_str
  if (!json1.success()) {
   display.clear();
     display.setFont(ArialMT_Plain_10);
     display.drawString(0, 33, "Failed to parse CONFIG file.\n Start ESP in AP Mode");
    display.display();
   delay(1000);
  Turn_AP_ON();
    return;
  }
  apn=json1["APN"].as<String>();
  user=json1["USER"].as<String>();
  pass=json1["PASSWORD"].as<String>();
  HOST=json1["TRACCAR"].as<String>();
  port=json1["PORT"].as<String>();
  ID=json1["ID"].as<String>();
  gps_mode=json1["MODE"].as<String>();
  owner_number=json1["NUMBER"].as<String>();
  Send_interval_str=json1["interval"].as<String>();
  myFile.close();
}

void SET_Default(){
 SPIFFS.remove("/CONFIG.TXT");
       display.clear();
    display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "Default Config");
  display.drawString(30, 26, "SAVED!!");
 
  Serial.println("");
    Serial.println(F("Default Saved!!"));
    display.display();
     BUZZER(100,30,10);      //BUZZ  Delay BUZZ lenght100 ms  and silence length 30 ms ,2 time
  ESP.restart();

}
////////////////////////////////////////////////////////////void to wait for Serial response  with TIMEOUT
void Wait_Response(uint32_t timeout,String& data){
 GSM_Serial.flush();
  String c;
    unsigned long starttimeout = millis();
  while(GSM_Serial.available()<=0 ){
    if( millis() - starttimeout < timeout){
    yield();               ///////////////////////////////////this function prevent ESP8266 from reset
    }else{
    return;
    }
    }
    // Print available data
    while (GSM_Serial.available()>0) {
       data = GSM_Serial.readStringUntil('\n');
    }
   GSM_Serial.flush();
   delay(30);
}
