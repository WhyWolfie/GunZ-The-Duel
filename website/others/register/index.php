<?
$filename = 'config.php';

if (file_exists($filename)) {
include ($filename);
?>
<head>
<title><? echo $Title; ?></title>
</head> <div align="center"> <?
echo $Title2; 
}
$conn = mssql_connect($DBHost, $DBUser, $DBPass) or die ("Cannot connect to the Database");

mssql_select_db($DB)or die ("Can connect to the mssql_server, but the Database doesn't exist");
$filename2 = 'register.php';
include ($filename2);
?> </div>

