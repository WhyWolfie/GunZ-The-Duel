<?php
$gunz_name = "GeneticGunz";  //Server Name
$exprate   = "50x";  //Server EXP Rate

$forum   = "";  //Forum Link
$vote    = "";  //Vote Page Link
$donate  = "";  //Donation Page Link

//Connect
$_MSSQL['Host'] = "\SQLEXPRESS"; //Host
$_MSSQL['User'] = "sa"; //Username
$_MSSQL['Pass'] = ""; //Password
$_MSSQL['DB']   = "GunzDB"; //Database

//Download Mirrors
$mirror1 = ""; //Download Link 1
$mirror2 = ""; //Download Link 2
$mirror3 = ""; //Download Link 3

//Language
$language = "english";

//Grade Colors
$admincol   = "#CC0000";  //Administrator
$fmodcol    = "#33CC00";  //Forum Moderator
$gmcol      = "#FF6600";  //GameMaster
$devcol     = "#33FFFF";  //Developer
$membcol    = "#c8c5c5";  //Member
$bannedcol  = "#000000";  //Banned

//UGradeID's
$adminugid   = 255;  //Administrator
$fmodugid    = 11;   //Forum Moderator
$gmugid      = 254;  //GameMaster
$devugid     = 10;   //Developer
$membugid    = 0;    //Member
$bannedugid  = 253;  //Banned

//Allow Character Sex Change (userpanel)
$allow_sex_change = "yes";  //Yes or No

$con = mssql_connect($_MSSQL['Host'],$_MSSQL['User'],$_MSSQL['Pass']) or die("Cant Connect!");
mssql_select_db($_MSSQL['DB']) or die("Cant Find Database!");
?>