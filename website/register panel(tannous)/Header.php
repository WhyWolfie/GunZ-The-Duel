<?PHP
session_start();

 if ($_SERVER['REQUEST_METHOD'] == 'GET' && realpath(__FILE__) == realpath($_SERVER['SCRIPT_FILENAME'])) {
	header("Location: index.php");
	exit();
 } else {
	include "Config.php";
 
?>
<html>
<head>
<title>.: <?=$servername?> :.</title> 
<link rel="icon" href="Images/favicon.ico" />
<link rel="stylesheet" type="text/css" href="style.css" />
<body bgcolor="#B1C6BD" text="white" />
<div align="center">
    <?php
          
	include "Secure/SQLCheck.php";
	include "Secure/AntiSQLi.php";

function Secures($chck) {
	echo "<br><br><table width='500' cellpadding='5' cellspacing='0' border='0' style='border: 1px ;'>
	<tr>
	<td align=center width='100%' style='border-bottom: 1px solid white; padding-bottom: 10px;'><b><img src='Images/msg.png' width='206' height='79' border='0' alt='Info Message'></b></td>
	</tr>
	<tr>
	<td width='100%'><center>$chck</center></td>
	</tr>
	<tr>
	<td width='100%'><center><input type='button' class='btn' value='Go Back' onclick='history.back()'></center></td>
	</tr>
	</table>";
	die();
}

function checkemail($address) {
	list($local, $host) = explode("@", $address);
	$pattern_local = "/^([0-9a-z]*([-|_]?[0-9a-z]+)*)(([-|_]?)\.([-|_]?)[0-9a-z]*([-|_]?[0-9a-z]+)+)*([-|_]?)$/";
	$pattern_host  = "/^([0-9a-z]+([-]?[0-9a-z]+)*)(([-]?)\.([-]?)[0-9a-z]*([-]?[0-9a-z]+)+)*\.[a-z]{2,4}$/";
	$match_local = preg_match ($pattern_local, $local);
	$match_host = preg_match ($pattern_host, $host);
	if($match_local && $match_host) {
	return 1;
	}
	else {
	return 0;
	}
}

function num_rows(&$rid) {
	$num= odbc_num_rows($rid);
	if ($num >= 0) {
	return $num;
	}
	if (!odbc_fetch_row($rid, 1)) {
	odbc_fetch_row($rid, 0);
	return 0;
	}
	if (!odbc_fetch_row($rid, 2)) {
	odbc_fetch_row($rid, 0);
	return 1;
	}
	$min= 2;
	$max= 8192000;
	while ($min < ($max - 1)) {
	$mid= (int)(($max + $min) / 2);
	if (odbc_fetch_row($rid, $mid)) {
	$min= $mid;
	} else {
	$max= $mid;
	}
	}
	$num= $min;
	odbc_fetch_row($rid, 0);
	return $num;
}
?>
</div>
</head>
<body bgcolor="#B1C6BD" text="white">
<?php
}
?>