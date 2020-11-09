<?php

    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: index.php");
        die();
    }

// Messages System
$_STR[Msg0]     = "Message from:";
$_STR[Msg1]     = "You must fill all the fields";

// Login Frame
$_STR[Login0]   = "Staff Login";
$_STR[Login1]   = "Username";
$_STR[Login2]   = "Password";
$_STR[Login3]   = "Login";

// Login Module
$_STR[Login4]   = "You must fill all the fields at the login form";
$_STR[Login5]   = "Your account does not have permission to access at this admin panel";
$_STR[Login6]   = "Invalid UserID / Password";

// Menu
$_STR[Menu0]    = "Panel's Menu";
$_STR[Menu1]    = "Welcome %s!";
$_STR[Menu2]    = "Home";
$_STR[Menu3]    = "NotePad";
$_STR[Menu4]    = "ASCII Table";
$_STR[Menu5]    = "Search";
$_STR[Menu6]    = "Manage Accounts";
$_STR[Menu7]    = "Manage Characters";
$_STR[Menu8]    = "Logout";
$_STR[Menu9]    = "Manage Clans";
$_STR[Menu10]   = "Country Restriction";

// Home
$_STR[Home0]    = "Welcome to the Gunz Control Panel";
$_STR[Home1]    = "Panel created by Emisand for RageZone<br />Skin designed by Lambda<br />Support at:";
$_STR[Home2]    = "Server Information";
$_STR[Home3]    = "Accounts created: ";
$_STR[Home4]    = "- Characters created: ";
$_STR[Home5]    = "- Players online: ";
$_STR[Home6]    = "Status";
$_STR[Home7]    = "Name";

// NotePad
$_STR[Notepad0] = "Send a Note";
$_STR[Notepad1] = "Note:";
$_STR[Notepad2] = "Send Note";
$_STR[Notepad3] = "View Notes";

// Ascii
$_STR[Ascii1]   = "Ascii Character Table";
$_STR[Ascii2]   = "Symbol";

// Search
$_STR[Search0]  = "Search";
$_STR[Search1]  = "Search Characters";
$_STR[Search2]  = "Search Accounts";
$_STR[Search3]  = "Search Clans";
$_STR[Search4]  = "Search Clan Wins/Losses";
$_STR[Search5]  = "Name";
$_STR[Search6]  = "Clan Name";
$_STR[Search7]  = "Character Name";
$_STR[Search8]  = "Master Character Name";
$_STR[Search9]  = "This Clan";
$_STR[Search10] = "Wins";
$_STR[Search11] = "Losses";
$_STR[Search12] = "Max Rows";
$_STR[Search13] = "Invalid Search Type";
$_STR[Search14] = "No results found";
$_STR[Search15] = "Search Results";

// Logs

$_STR[Log0]     = "The UserID from the %s %s has been changed to %s";
$_STR[Log1]     = "The Password from the %s %s has been changed to %s";
$_STR[Log2]     = "The Rank from the %s %s has been changed to %s";
$_STR[Log3]     = "The Item %s has been sent to all accounts";
$_STR[Log4]     = "The Item %s has been sent to the AID %s";

$_STR[Log5]     = "The name of the character %s has been changed to %s";
$_STR[Log6]     = "The character %s has been deleted";
$_STR[Log7]     = "All the character items from %s have been deleted";
$_STR[Log8]     = "All the account items from the AID %s have been deleted";
$_STR[Log9]     = "The Item with ItemID %s has been sent to the CID %s";
$_STR[Log10]    = "The Item with ItemID %s has been deleted from the CID %s";
$_STR[Log11]    = "The character %s has been reset";
$_STR[Log12]    = "The EXP from the character %s has been changed to %s";
$_STR[Log13]    = "The Level from the character %s has been changed to %s";
$_STR[Log14]    = "The Bounty from the character %s has been changed to %s";
$_STR[Log15]    = "The Sex from the character %s has been changed";
$_STR[Log16]    = "The Hair from the character %s has been changed";
$_STR[Log17]    = "The Face from the character %s has been changed";

$_STR[Log18]    = "Clan Ranking Updated";
$_STR[Log19]    = "The clan %s has been created with MasterCID %s";
$_STR[Log20]    = "The clan %s has been deleted";
$_STR[Log21]    = "The clan %s has been resetted";
$_STR[Log22]    = "All clans have been resetted";
$_STR[Log23]    = "Emblem removed from the clan %s";
$_STR[Log24]    = "The stats of the clan %s have been changed";
$_STR[Log25]    = "The clanmember %s grade has been changed to %s";

$_STR[Log26]    = "All countries have been allowed";
$_STR[Log27]    = "All countries have been blocked";
$_STR[Log28]    = "The country with countrycode3 %s has been allowed";
$_STR[Log29]    = "The country with countrycode3 %s has been blocked";
$_STR[Log30]    = "A new block message has been set: %s";

// Accounts

$_STR[Acc0]     = "Change UserID";
$_STR[Acc1]     = "New UserID";
$_STR[Acc2]     = "Change";
$_STR[Acc3]     = "Change Password";
$_STR[Acc4]     = "New Password";
$_STR[Acc5]     = "Change Account Rank";
$_STR[Acc6]     = "Banned";
$_STR[Acc7]     = "Normal User";
$_STR[Acc8]     = "Invisible Mod";
$_STR[Acc9]     = "Mod";
$_STR[Acc10]    = "Administrator";
$_STR[Acc11]    = "Send Item to ALL accounts Storage";
$_STR[Acc12]    = "Rent Period(Days)";
$_STR[Acc13]    = "Send Item to Storage";
$_STR[Acc14]    = "Send";
$_STR[Acc15]    = "It alredy exists an account with the UserID %s";
$_STR[Acc16]    = "The selected account does not exist";
$_STR[Acc17]    = "UserID changed successfully";
$_STR[Acc18]    = "Password changed successfully";
$_STR[Acc19]    = "Rank changed successfully";
$_STR[Acc20]    = "Incorrect ItemID or RentPeriod";
$_STR[Acc21]    = "Item sent to all account's storage";
$_STR[Acc22]    = "Item sent to the selected account's storage";

// Characters

$_STR[Char0]    = "Change Character Name";
$_STR[Char1]    = "Name";
$_STR[Char2]    = "New Name";
$_STR[Char3]    = "Change";
$_STR[Char4]    = "Delete Character";
$_STR[Char5]    = "Delete";
$_STR[Char6]    = "Delete all items from Equipment";
$_STR[Char7]    = "Delete all items from Storage";
$_STR[Char8]    = "Send Item to Equipment";
$_STR[Char9]    = "Delete Item from Equipment";
$_STR[Char10]   = "Send";
$_STR[Char11]   = "Reset character (Lvl 1, XP: 0, BT: 1000)";
$_STR[Char12]   = "Reset";
$_STR[Char13]   = "Change EXP from character";
$_STR[Char14]   = "Change Level from character";
$_STR[Char15]   = "Change Bounty from character";
$_STR[Char16]   = "Change Sex from character";
$_STR[Char17]   = "Male";
$_STR[Char18]   = "Female";
$_STR[Char19]   = "Change Hair from character";
$_STR[Char20]   = "Hair";
$_STR[Char21]   = "Change Face from character";
$_STR[Char22]   = "Face";
$_STR[Char23]   = "It alredy exists a character with the Name %s";
$_STR[Char24]   = "The selected character does not exist";
$_STR[Char25]   = "Name changed successfully";
$_STR[Char26]   = "Character deleted successfully";
$_STR[Char27]   = "Items deleted successfully";
$_STR[Char28]   = "The selected character or account does not exist";
$_STR[Char29]   = "Item sent successfully";
$_STR[Char30]   = "Item deleted successfully";
$_STR[Char31]   = "Character reset successfully";
$_STR[Char32]   = "Incorrect numeric value";
$_STR[Char33]   = "EXP changed successfully";
$_STR[Char34]   = "LVL changed successfully";
$_STR[Char35]   = "Bounty changed successfully";
$_STR[Char36]   = "Invalid Sex";
$_STR[Char37]   = "Sex changed successfully";
$_STR[Char38]   = "Invalid Hair";
$_STR[Char39]   = "Hair changed successfully";
$_STR[Char40]   = "Invalid Face";
$_STR[Char41]   = "Face changed successfully";

// Clans

$_STR[Clan0]    = "Update Clan Ranking";
$_STR[Clan1]    = "This will update all clan's ranking<br />It may take long if you have many clans<br />";
$_STR[Clan2]    = "Update";
$_STR[Clan3]    = "Create Clan";
$_STR[Clan4]    = "Name";
$_STR[Clan5]    = "Create";
$_STR[Clan6]    = "Delete Clan";
$_STR[Clan7]    = "Delete";
$_STR[Clan8]    = "Reset Clan Score";
$_STR[Clan9]    = "Reset ALL Clans";
$_STR[Clan10]   = "Reset";
$_STR[Clan11]   = "Remove Clan Emblem";
$_STR[Clan12]   = "Remove";
$_STR[Clan13]   = "Change Clan Stats";
$_STR[Clan14]   = "Change";
$_STR[Clan15]   = "Change Member Grade";
$_STR[Clan16]   = "Rank";
$_STR[Clan17]   = "<b>Warning:</b> This cannot be reverted<br /><br />";
$_STR[Clan18]   = "Clan Ranking successfully updated";
$_STR[Clan19]   = "It already exists a clan with the selected name";
$_STR[Clan20]   = "The selected clan Master does not exist";
$_STR[Clan21]   = "The selected clan Master is member of another clan";
$_STR[Clan22]   = "Clan successfully created";
$_STR[Clan23]   = "The selected clan does not exist";
$_STR[Clan24]   = "Clan successfully deleted";
$_STR[Clan25]   = "Clan successfully resetted";
$_STR[Clan26]   = "All Clans successfully resetted";
$_STR[Clan27]   = "Emblem successfully removed";
$_STR[Clan28]   = "The Wins, Losses and Points must be numeric values";
$_STR[Clan29]   = "Stats successfully changed";
$_STR[Clan30]   = "The selected ClanMember does not exist";
$_STR[Clan31]   = "The selected ClanMember Rank is invalid";
$_STR[Clan32]   = "The selected Character is not member of any clan";
$_STR[Clan33]   = "The selected ClanMember is the owner of a clan, and you can't change his grade";
$_STR[Clan34]   = "The ClanMember Rank was successfully changed";

// Country Restriction plugin

$_STR[Country0] = "Allow all countries";
$_STR[Country1] = "Allow";
$_STR[Country2] = "Block all countries";
$_STR[Country3] = "Block";
$_STR[Country4] = "Allow a country";
$_STR[Country5] = "Block a country";

$_STR[Country6] = "All countries have been allowed";
$_STR[Country7] = "All countries have been blocked";
$_STR[Country8] = "Country allowed successfully";
$_STR[Country9] = "Country blocked successfully";
$_STR[Country10]= "Block message set successfully";
$_STR[Country11]= "Set a new blocked country message";
$_STR[Country12]= "Set";



?>