const char INDEX_Page[] PROGMEM=R"=====(
<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>GPS Config Page</title>
<meta name="generator" content="">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>div#container { width:952px; position:relative; margin:0 auto 0 auto; text-align:left; }
body { background-color:#FFFFFF; color:#000000; font-family:Arial; font-weight:normal; font-size:13px; line-height:1.1875; margin:0; text-align:center; }
a { color:#FFFFFF; text-decoration:none; }
a:visited { color:#FFDEAD; }
a:active { color:#B0E0E6; }
a:hover { color:#AFEEEE; text-decoration:none; }
#wb_LayoutGrid1 { clear:both; position:relative; table-layout:fixed; display:table; text-align:center; width:100%; background-color:transparent; background-image:none; border:0px #CCCCCC solid; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; }
#LayoutGrid1 { -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:0px 15px 0px 15px; margin-right:auto; margin-left:auto; }
#LayoutGrid1 .row { margin-right:-15px; margin-left:-15px; }
#LayoutGrid1 .col-1,#LayoutGrid1 .col-2,#LayoutGrid1 .col-3 { -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; font-size:0px; min-height:1px; padding-right:15px; padding-left:15px; position:relative; }
#LayoutGrid1 .col-1,#LayoutGrid1 .col-2,#LayoutGrid1 .col-3 { float:left; }
#LayoutGrid1 .col-1 { background-color:transparent; background-image:none; width:33.33333333%; text-align:left; }
#LayoutGrid1 .col-2 { background-color:transparent; background-image:none; width:33.33333333%; text-align:left; }
#LayoutGrid1 .col-3 { background-color:transparent; background-image:none; width:33.33333333%; text-align:left; }
#LayoutGrid1:before,#LayoutGrid1:after,#LayoutGrid1 .row:before,#LayoutGrid1 .row:after { display:table; content:" "; }
#LayoutGrid1:after,#LayoutGrid1 .row:after { clear:both; }
@media (max-width: 1050px) {
#LayoutGrid1 .col-1,#LayoutGrid1 .col-2,#LayoutGrid1 .col-3 { float:none; width:100%; }
}
#Line1 { border-color:transparent; border-style:solid; border-width:33px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#wb_Text1 { background-color:transparent; background-image:none; border:0px #000000 solid; padding:0; margin:0; text-align:center; }
#wb_Text1 div { text-align:center; }
#Line2 { border-color:transparent; border-style:solid; border-width:12px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#wb_LayoutGrid2 { clear:both; position:relative; table-layout:fixed; display:table; text-align:center; width:100%; background-color:transparent; background-image:none; border:0px #CCCCCC solid; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; }
#LayoutGrid2 { -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:0px 15px 0px 15px; margin-right:auto; margin-left:auto; }
#LayoutGrid2 .row { margin-right:-15px; margin-left:-15px; }
#LayoutGrid2 .col-1,#LayoutGrid2 .col-2,#LayoutGrid2 .col-3 { -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; font-size:0px; min-height:1px; padding-right:15px; padding-left:15px; position:relative; }
#LayoutGrid2 .col-1,#LayoutGrid2 .col-2,#LayoutGrid2 .col-3 { float:left; }
#LayoutGrid2 .col-1 { background-color:transparent; background-image:none; width:33.33333333%; text-align:center; }
#LayoutGrid2 .col-2 { background-color:transparent; background-image:none; width:33.33333333%; text-align:center; }
#LayoutGrid2 .col-3 { background-color:transparent; background-image:none; width:33.33333333%; text-align:center; }
#LayoutGrid2:before,#LayoutGrid2:after,#LayoutGrid2 .row:before,#LayoutGrid2 .row:after { display:table; content:" "; }
#LayoutGrid2:after,#LayoutGrid2 .row:after { clear:both; }
@media (max-width: 1050px) {
#LayoutGrid2 .col-1,#LayoutGrid2 .col-2,#LayoutGrid2 .col-3 { float:none; width:100%; }
}
#Line3 { border-color:transparent; border-style:solid; border-width:12px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#APN { border:1px #343C49 solid; border-radius:4px; background-color:#FFFFFF; background-image:none; color:#000000; font-family:Arial; font-weight:normal; font-size:13px; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:4px 4px 4px 4px; text-align:center; vertical-align:middle; }
#APN:focus { border-color:#66AFE9; -webkit-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); -moz-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); outline:0; }
#Line4 { border-color:transparent; border-style:solid; border-width:24px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#USER { border:1px #343C49 solid; border-radius:4px; background-color:#FFFFFF; background-image:none; color:#000000; font-family:Arial; font-weight:normal; font-size:13px; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:4px 4px 4px 4px; text-align:center; vertical-align:middle; }
#USER:focus { border-color:#66AFE9; -webkit-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); -moz-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); outline:0; }
#Line5 { border-color:transparent; border-style:solid; border-width:24px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#PASSWORD { border:1px #343C49 solid; border-radius:4px; background-color:#FFFFFF; background-image:none; color:#000000; font-family:Arial; font-weight:normal; font-size:13px; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:4px 4px 4px 4px; text-align:center; vertical-align:middle; }
#PASSWORD:focus { border-color:#66AFE9; -webkit-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); -moz-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); outline:0; }
#Line7 { border-color:transparent; border-style:solid; border-width:44px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#TRACCAR { border:1px #343C49 solid; border-radius:4px; background-color:#FFFFFF; background-image:none; color:#000000; font-family:Arial; font-weight:normal; font-size:13px; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:4px 4px 4px 4px; text-align:center; vertical-align:middle; }
#TRACCAR:focus { border-color:#66AFE9; -webkit-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); -moz-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); outline:0; }
#Line8 { border-color:transparent; border-style:solid; border-width:24px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#PORT { border:1px #343C49 solid; border-radius:4px; background-color:#FFFFFF; background-image:none; color:#000000; font-family:Arial; font-weight:normal; font-size:13px; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:4px 4px 4px 4px; text-align:center; vertical-align:middle; }
#PORT:focus { border-color:#66AFE9; -webkit-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); -moz-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); outline:0; }
#Line9 { border-color:transparent; border-style:solid; border-width:24px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#ID { border:1px #343C49 solid; border-radius:4px; background-color:#FFFFFF; background-image:none; color:#000000; font-family:Arial; font-weight:normal; font-size:13px; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:4px 4px 4px 4px; text-align:center; vertical-align:middle; }
#ID:focus { border-color:#66AFE9; -webkit-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); -moz-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); outline:0; }
#Line10 { border-color:transparent; border-style:solid; border-width:19px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#Button1 { border:1px #2E6DA4 solid; border-radius:4px; background-color:#343C49; background-image:none; color:#FFFFFF; font-family:"Bookman Old Style"; font-weight:bold; font-size:13px; }
#Combobox1 { border:1px #343C49 solid; border-radius:4px; background-color:#FFFFFF; background-image:none; color:#1E90FF; font-family:Arial; font-weight:bold; font-size:13px; padding:4px 4px 4px 4px; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; }
#Combobox1:focus { border-color:#66AFE9; -webkit-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); -moz-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); outline:0; }
#Line6 { border-color:transparent; border-style:solid; border-width:21px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#Line11 { border-color:transparent; border-style:solid; border-width:24px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#NUMBER { border:1px #343C49 solid; border-radius:4px; background-color:#FFFFFF; background-image:none; color:#000000; font-family:Arial; font-weight:normal; font-size:13px; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:4px 4px 4px 4px; text-align:center; vertical-align:middle; }
#NUMBER:focus { border-color:#66AFE9; -webkit-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); -moz-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); outline:0; }
#Line12 { border-color:transparent; border-style:solid; border-width:24px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#wb_Text2 { background-color:transparent; background-image:none; border:0px #000000 solid; padding:0; margin:0; text-align:center; }
#wb_Text2 div { text-align:center; }
#Editbox1 { border:1px #343C49 solid; border-radius:4px; background-color:#FFFFFF; background-image:none; color:#343C49; font-family:Arial; font-weight:normal; font-size:13px; -webkit-box-sizing:border-box; -moz-box-sizing:border-box; box-sizing:border-box; padding:4px 4px 4px 4px; text-align:center; vertical-align:middle; }
#Editbox1:focus { border-color:#66AFE9; -webkit-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); -moz-box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); box-shadow:inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60); outline:0; }
#Line13 { border-color:transparent; border-style:solid; border-width:21px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#Line14 { border-color:transparent; border-style:solid; border-width:21px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#wb_Text3 { background-color:transparent; background-image:none; border:0px #000000 solid; padding:0; margin:0; text-align:center; }
#wb_Text3 div { text-align:center; }
#Line15 { border-color:transparent; border-style:solid; border-width:21px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#wb_Text4 { background-color:transparent; background-image:none; border:0px #000000 solid; padding:0; margin:0; text-align:center; }
#wb_Text4 div { text-align:center; }
#Line16 { border-color:transparent; border-style:solid; border-width:21px; border-top:0px; border-left:0px; border-right:0px; height:0; line-height:0px  !important; margin:0; padding:0; }
#wb_Text5 { background-color:transparent; background-image:none; border:0px #000000 solid; padding:0; margin:0; text-align:center; }
#wb_Text5 div { text-align:center; }
#wb_uid1 { color:#00BFFF; font-family:Bookman Old Style; font-size:13px; }
#Line6 { display:block; width:100%; z-index:19; }
#Editbox1 { display:block; width:100%; height:26px; line-height:26px; z-index:16; }
#wb_uid2 { background-color:#343C49; color:#000000; font-family:Arial; font-size:19px; }
#PORT { display:block; width:100%; height:26px; line-height:26px; z-index:12; }
#Line7 { display:block; width:100%; z-index:9; }
#wb_uid3 { background-color:#343C49; color:#000000; font-family:Arial; font-size:19px; }
#Line10 { display:block; width:100%; z-index:15; }
#Line8 { display:block; width:100%; z-index:11; }
#wb_uid4 { color:#00BFFF; font-family:Bookman Old Style; font-size:13px; }
#Line11 { display:block; width:100%; z-index:21; }
#Line9 { display:block; width:100%; z-index:13; }
#Line12 { display:block; width:100%; z-index:17; }
#Line13 { display:block; width:100%; z-index:23; }
#Line14 { display:block; width:100%; z-index:25; }
#Line15 { display:block; width:100%; z-index:27; }
#TRACCAR { display:block; width:100%; height:26px; line-height:26px; z-index:10; }
#Line16 { display:block; width:100%; z-index:29; }
#NUMBER { display:block; width:100%; height:26px; line-height:26px; z-index:20; }
#USER { display:block; width:100%; height:26px; line-height:26px; z-index:6; }
#ID { display:block; width:100%; height:26px; line-height:26px; z-index:14; }
#APN { display:block; width:100%; height:26px; line-height:26px; z-index:4; }
#Line1 { display:block; width:100%; z-index:0; }
#Button1 { display:inline-block; width:140px; height:31px; }
#Line2 { display:block; width:100%; z-index:2; }
#Line3 { display:block; width:100%; z-index:3; }
#Combobox1 { display:block; width:100%; height:28px; z-index:18; }
#Line4 { display:block; width:100%; z-index:5; }
#PASSWORD { display:block; width:100%; height:26px; line-height:26px; z-index:8; }
#Line5 { display:block; width:100%; z-index:7; }
#wb_uid0 { color:#00BFFF; font-family:Bookman Old Style; font-size:37px; }
</style>
</head>
<body>
<div id="container">
</div>
<div id="wb_LayoutGrid1">
<div id="LayoutGrid1">
<div class="row">
<div class="col-1">
</div>
<div class="col-2">
<hr id="Line1">
<div id="wb_Text1">
<span id="wb_uid0"><strong>Config Page</strong></span>
</div>
<hr id="Line2">
</div>
<div class="col-3">
</div>
</div>
</div>
</div>
<div id="wb_LayoutGrid2">
<form name="LayoutGrid2" method="get" action="/config" enctype="text/plain" id="LayoutGrid2" onsubmit="return ValidateLayoutGrid2(this)">
<div class="row">
<div class="col-1">
</div>
<div class="col-2">
<hr id="Line3">
<input type="text" id="APN" name="APN" value="" spellcheck="false" placeholder="APN Name of sim card provider *">
<hr id="Line4">
<input type="text" id="USER" name="USER" value="" spellcheck="false" placeholder="User Name of sim card provider">
<hr id="Line5">
<input type="text" id="PASSWORD" name="PASSWORD" value="" spellcheck="false" placeholder="Password of sim card provider">
<hr id="Line7">
<input type="text" id="TRACCAR" name="TRACCAR" value="" spellcheck="false" placeholder="Traccar Server URL or IP *">
<hr id="Line8">
<input type="text" id="PORT" name="PORT" value="" spellcheck="false" placeholder="Traccar Port default is 5055 *">
<hr id="Line9">
<input type="text" id="ID" name="ID" value="" spellcheck="false" placeholder="Device Unique ID  e.g. IMEI *">
<hr id="Line10">
<input type="text" id="Editbox1" name="interval" value="" spellcheck="false" placeholder="GPRS Position send interval in Second *">
<hr id="Line12">
<select name="MODE" size="1" id="Combobox1" title="GPS Type">
<option value="AGPS">Assisted GPS</option>
<option selected value="GPS">GPS</option>
</select>
<hr id="Line6">
<input type="text" id="NUMBER" name="NUMBER" value="" spellcheck="false" placeholder="Owner phone number e.g 989300001234  *">
<hr id="Line11">
<input type="submit" id="Button1" name="" value="SAVE and Reboot">
<hr id="Line13">
<div id="wb_Text2">
<span id="wb_uid1">By : Abbas Soltani&nbsp; Final Project</span>
</div>
<hr id="Line14">
<div id="wb_Text3">
<span id="wb_uid2"><a href="/reset">Exit without saving</a></span>
</div>
<hr id="Line15">
<div id="wb_Text4">
<span id="wb_uid3"><a href="/firmware">Firmware Update</a></span>
</div>
<hr id="Line16">
<div id="wb_Text5">
<span id="wb_uid4">Version 1.0.0</span>
</div>
</div>
<div class="col-3">
</div>
</div>
</form>
</div>
<script>
function ValidateLayoutGrid2(theForm)
{
   var regexp;
   if (theForm.APN.value == "")
   {
      alert("Please enter a value for the \"APN\" field.");
      theForm.APN.focus();
      return false;
   }
   if (theForm.TRACCAR.value == "")
   {
      alert("Please enter a value for the \"TRACCAR\" field.");
      theForm.TRACCAR.focus();
      return false;
   }
   if (theForm.PORT.value == "")
   {
      alert("Please enter a value for the \"PORT\" field.");
      theForm.PORT.focus();
      return false;
   }
   if (theForm.ID.value == "")
   {
      alert("Please enter a value for the \"ID\" field.");
      theForm.ID.focus();
      return false;
   }
   regexp = /^[-+]?\d*\.?\d*$/;
   if (!regexp.test(theForm.Editbox1.value))
   {
      alert("you have to type data in Number greater than or equal to 15");
      theForm.Editbox1.focus();
      return false;
   }
   if (theForm.Editbox1.value == "")
   {
      alert("you have to type data in Number greater than or equal to 15");
      theForm.Editbox1.focus();
      return false;
   }
   if (theForm.Editbox1.value != "" && !(theForm.Editbox1.value >= 15))
   {
      alert("you have to type data in Number greater than or equal to 15");
      theForm.Editbox1.focus();
      return false;
   }
   if (theForm.NUMBER.value == "")
   {
      alert("Please enter a value for the \"NUMBER\" field.");
      theForm.NUMBER.focus();
      return false;
   }
   return true;
}
</script>
</body>
</html>
)=====";
