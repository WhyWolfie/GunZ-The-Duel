<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: index.php");
        die();
    }

   ///////////////////////////////////
  // Emisand's Gunz Admin Panel /////
 /// -- Configuration File  -- /////
///////////////////////////////////

//MSSQL Server configuration

$_MSSQL[Host]   = "COMPUTER\SQLEXPRESS";    // MSSQL Server HOST, it can be an IP Address or a computer name
$_MSSQL[User]   = "sa";                     // MSSQL User
$_MSSQL[Pass]   = "";                       // MSSQL Password
$_MSSQL[DBNa]   = "GunzDB";                 // Gunz Database Name

// Here you set the language for the panel
// If you set this to english, the panel will try to load lang/english.php
$_CONFIG[Language]  = "english";

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
                                    // to selected countries

?>
