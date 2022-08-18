<?php
//Anti Injection
function anti_injection($sql) {
$sql = preg_replace(sql_regcase("/(from|select|insert|delete|where|'|\"|drop table|show tables|#|\*|--|\\\\)/"),"",$sql);
$sql = trim($sql);
$sql = strip_tags($sql);
$sql = addslashes($sql);
return $sql;
}
//Alert
function alert($msg){
echo '<script language="javascript">alert("'.$msg.'");</script>';
}
//Redirect
function redirect($url){
echo "<body><script>document.location = '$url'</script></body>";
}
function mssql_query_z($query){
return mssql_query($query);
}
//Sex
function Sex($xx){
switch($xx){
case 0:
return "Man";
break;
case 1:
return "Female";
break;
case 2:
return "All";
break;
}
}
//Check Session
function CheckSession(){
 if($_SESSION['user'] == ""){
   redirect("index.php");
   die();
 }
}
//UGradeID Color Name
function Char($cid){
$ncid = c($cid);
$res = mssql_fetch_row(mssql_query("SELECT ac.UGradeID, ch.Name From Character ch INNER JOIN Account ac ON ac.AID = ch.AID WHERE ch.CID = '$ncid'"));
$name = $res[1];

include("secure/config.php");

switch($res[0]){
case $adminugid:  //Administrator
return "<font color='".$admincol."'>$name</font>";
break;
case $gmugid:  //GameMaster
return "<font color='".$gmcol."'>$name</font>";
break;
case $fmodugid:  //Forum Moderator
return "<font color='".$fmodcol."'>$name</font>";
break;
case $devugid:  //Developer
return "<font color='".$devcol."'>$name</font>";
break;
case $bannedugid: //Banned
return "<font color='".$bannedcol."'><strike>$name</strike></font>";
break;
default:  //Member
return "<font color='".$membcol."'>$name</font>";
break;
}
}
function c($value){
return($value);
}
//Page Title
ob_start("ParseTitle");
function ParseTitle($content){
if($_SESSION[PageTitle] <> ""){
 $r = str_replace("//Title", $_SESSION[PageTitle], $content);
 $_SESSION[PageTitle] = "";
 return $r;
 }else{
  $r = str_replace("//Title", "", $content);
  return $r;
 }
}
function Title($title){
 $_SESSION[PageTitle] = $title;
}
?>