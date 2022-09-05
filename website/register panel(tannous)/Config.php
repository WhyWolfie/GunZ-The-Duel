<?PHP
////////////////////////////////////
///////    Configuration 	////////
////////////////////////////////////
/////// Edit This File Only ////////
////////////////////////////////////

$servername = "GunZ"; 					// Here put the Server Name as you put it in dbo.ServerStatus
$accounttable = "Account"; 
$logintable = "Login"; 
$chartable = "Character";
$citemtable = "CharacterItem";
$max_players = "500"; 					// Change this to the maximum number of players in your server
$download = "#"; 						// Here you put your Gunz Client download link
$year = "2020"; 						// which year are we now 

$host = "COMPUTER\SQLEXPRESS"; 	// Host Name (Example: BlaBla\SQLEXPRESS)
$user = "sa"; 							// SQL User (Default: sa)
$pass = ""; 					// SQL Pass (As you put it when you installed the program)
$dbname = "GunzDB"; 					// DataBase Name

$connect = odbc_connect("Driver={SQL Server};Server={$host}; Database={$dbname}", $user, $pass) or die("Can't connect the MSSQL server.");

?>