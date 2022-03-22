<?
@session_start();
//MSSQL Server configuration
$_MSSQL[Host]               = "TU HOST SQL";
$_MSSQL[User]               = "sa";
$_MSSQL[Pass]               = "PASSWORD";
$_MSSQL[DBNa]               = "BASEDEDATOS";




$r = mssql_connect($_MSSQL[Host], $_MSSQL[User], $_MSSQL[Pass]) or die("No se pudo conectar al SQL");
mssql_select_db($_MSSQL[DBNa], $r) or die("La Base de datos no se encuentra.");
/*_________________________________________________
 |	Config del name Color.. 						\					\
 |	donde estan los numeros 10,20,30,40 Los cambias	|
 |	por tus UGrade TUYOS. 							|
 |	y abajo el Nombre de Cada Ugrade son 6 Ugrades	|	
 \_________________________________________________/__*/
//Config Numero UGrade Color. 1,2,3,4,5,6
$_COLORUGRA_1 			= "10"; 
$_COLORUGRA_2 			= "20";
$_COLORUGRA_3		    = "30";
$_COLORUGRA_4 			= "40";
$_COLORUGRA_5 			= "50";
$_COLORUGRA_6			= "60";
//Nombre de los Ugrade Color. ,1,2,3,4,5,6
$_UGRADENAME_1 			= "Verde";
$_UGRADENAME_2 			= "Azul";
$_UGRADENAME_3 			= "Celeste";
$_UGRADENAME_4 			= "Morado";
$_UGRADENAME_5 			= "Amarillo";
$_UGRADENAME_6 			= "Fucsia";
// Panel en español
$_CONFIG[Language]  = "espanol";
// Gunz Database Configuration
$_CONFIG[AccountTable]  = "Account";
$_CONFIG[LoginTable]    = "Login";
$_CONFIG[CharTable]     = "Character";
$_CONFIG[CItemTable]    = "CharacterItem";
$_CONFIG[AItemTable]    = "AccountItem";
$_CONFIG[ClanTable]     = "Clan";
$_CONFIG[ClanMembTable] = "ClanMember";
$_CONFIG[ClanLogTable]  = "ClanGameLog";
// Plugins Configuration
// To Disable, set the variable to 0
// To Enable, set the variable to 1
$_CONFIG[CountryBlock]  = 0;        // Add functions to Block / Unblock access to your GunZ Server
//Offline page
$_CONFIG[OfflinePage]       = "";
// Gunz Database Configuration
$_CONFIG[LoginTable]    = "Login";
$_CONFIG[CharTable]     = "Character";
$_CONFIG[ClanTable]    = "Clan";
$_CONFIG[ClanmemberTable]    = "ClanMember";
$color[255] = array(255,153,51); // Administrator
$color[254] = array(255,153,51); // Developer/Gamemaster
$color[253] = array(255,255,255); // Banned
$color[252] = array(255,153,51); // Hidden GM
$color[2]   = array(0,68,255); // User With Jjang
$color[0]   = array(255,255,255); // Normal User
// Panel en español
$_CONFIG[Language]  = "espanol";
// Gunz Database Configuration
$_CONFIG[LoginTable]    = "Login";
$_CONFIG[CharTable]     = "Character";
$_CONFIG[ClanTable]    = "Clan";
$_CONFIG[ClanmemberTable]    = "ClanMember";

// Creditos Sacker.
?>