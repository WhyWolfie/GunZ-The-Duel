<?php
function alert($msg){
  echo "<script langauge=\"javascript\">alert(\"".$msg."\");</script>";
}
function Sex($xx){
switch($xx){
case 0:
return "Man";
break;
case 1:
return "Female";
break;
}
}
function redirect($url){
echo "<body  bgcolor='#000000'><script>document.location = '$url'</script></body>";
}
function Char($cid){
$ncid = sql($cid);
$query = mssql_fetch_row(mssql_query("SELECT ac.UGradeID, ch.Name From Character ch INNER JOIN Account ac ON ac.AID = ch.AID WHERE ch.CID = '$ncid'"));
$name = $query[1];
switch($query[0]){
case 255:
return "<font color='#FF0000'>$name</font>";
break;
case 254:
return "<font color='#FF8040'>$name</font>";
break;
case 252:
return "<font color='#0033FF'>$name</font>";
break;
default:
return $name;
break;
}
}
function sql($sql){
$sql = preg_replace(sql_regcase("/(from|select|insert|delete|where|'|\"|drop table|show tables|#|\*|--|\\\\)/"),"",$sql);
$sql = trim($sql);
$sql = strip_tags($sql);
$sql = addslashes($sql);
return $sql;
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