<?php


$ip = getenv('REMOTE_ADDR');
$requested = stripslashes($_SERVER['REQUEST_URI']);

foreach($_POST as $post)
if(preg_match ("[^0-9a-zA-Z_@.?<>]", $post)){
$posted = stripslashes($post);
$qIps = odbc_exec($connect, "Select memb___id From MEMB_STAT Where ip='".$ip."'");
if(odbc_num_rows ($qIps) <= 0){
}else{
	for($a=0;$a<odbc_num_rows ($qIps);$a++){
		$name = odbc_fetch_row ($qIps);
}
die("<script>alert('Error ! Please go back and try again!'); location='javascript:history.back()'</script>");
}
foreach($_GET as $get)
if(preg_match ("[^0-9a-zA-Z_@$]", $get)){
$qIps = odbc_exec($connect, "Select memb___id From MEMB_STAT Where ip='".$ip."'");
if(odbc_num_rows ($qIps) <= 0){
	fwrite($fp, "  None \n ============== \n");
}else{
	for($a=0;$a<odbc_num_rows ($qIps);$a++){
		$name = odbc_fetch_row ($qIps);
}
die("<script>alert('Error ! Please go back and try again!'); location='javascript:history.back()'</script>");
} 
foreach($_COOKIE as $cookie)
if(preg_match ("[^0-9a-zA-Z_@_$]", $cookie)){
$qIps = odbc_exec($connect, "Select memb___id From MEMB_STAT Where ip='".$ip."'");
if(odbc_num_rows ($qIps) <= 0){
	fwrite($fp, "  None \n ============== \n");
}else{
	for($a=0;$a<odbc_num_rows ($qIps);$a++){
		$name = odbc_fetch_row ($qIps);
}

} 
}
}


}
?>