<? 
$Title = 'GunZ'; // Website title page !
$Title2 = 'GunZ REGISTRATION PAGE'; // Your GunZ Name - Registration Page !
$DBHost = '\SQLEXPRESS'; // MSSQL Host : ....\SQLEXPRESS
$DBUser = ''; // MSSQL User
$DBPass = ''; // MSSQL Password
$DB = 'GunzDB'; // Gunz Database Name

$conn = mssql_connect($DBHost, $DBUser, $DBPass); // DONT CHANGE THIS //
mssql_select_db($DB); // DONT CHANGE THIS //
?>