<?php
$ip = $_SERVER['REMOTE_ADDR'];
$time = date("l dS of F Y h:i:s A");
$script = $_SERVER[PATH_TRANSLATED];
$fp = fopen ("secure/sql_Injections.txt", "a+");
$sql_inject_1 = array(";","'","%",'"'); #Whoth need replace
$sql_inject_2 = array("", "","","&quot;"); #To wont replace
$GET_KEY = array_keys($_GET); #array keys from $_GET
/*begin clear $_GET */
for($i=0;$i<count($GET_KEY);$i++){
  $real_get[$i] = $_GET[$GET_KEY[$i]];
  $_GET[$GET_KEY[$i]] = str_replace($sql_inject_1, $sql_inject_2, HtmlSpecialChars($_GET[$GET_KEY[$i]]));
   if($real_get[$i] != $_GET[$GET_KEY[$i]]){
	if($_SESSION['user']){
     fwrite ($fp, "Username: ".$_SESSION['user']."\r\n");
	}
	$msg = "SQL Injection detected. Your IP has been saved!"; alert($msg);
     fwrite ($fp, "IP: $ip\r\n");
     fwrite ($fp, "Method: GET\r\n");
     fwrite ($fp, "Value: $real_get[$i]\r\n");
     fwrite ($fp, "Script: $script\r\n");
     fwrite ($fp, "Time: $time\r\n");
     fwrite ($fp, "==================================\r\n");
	redirect("index.php");
   }
}
fclose ($fp);
/*end clear $_GET */
?>