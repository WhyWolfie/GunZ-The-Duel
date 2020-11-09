<?php
if( !session_start() )
{
    session_start();
}
require "config.php";
include "functions.php";
$langfile = "lang/{$_CONFIG[Language]}.php";
include $langfile;

$connection = connect();
?>

<html>

<head>
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title>GunZ Admin Panel v3 - By Emisand</title> 

<style type="text/css">
<!--
body,td,th {
	color: #FFFFFF; font-family:Trebuchet MS
}
a {
	color: #FFFFFF; font-family:Trebuchet MS
}
body {
	background-color: #171717;
}
input {
    border: 1px solid #A0A0A4;
    color: #000000;
    background: #CCCCCC;
    font-family:Trebuchet MS;
    font-size: 10pt
}
-->
</style>
</head>

<body topmargin="0">
<?php

if( $_SESSION['AID'] == "" )
{
    if( isset($_POST['login']) )
    {
        login();
    }
    else
    {

?>
    <center>
    <p><b>Gunz Admin Panel</b></p>
    <form name="login" method="POST" action="index.php">
    <?php showmessage(); ?>
        <table width="30%" border="1" style="border-collapse: collapse" id="login">
            <tr>
                <td colspan="2" align="center"><b><?php printf( $_STR[Login0] ); ?></b></td>
            </tr>
            <tr>
                <td colspan="2">&nbsp;</td>
            </tr>
            <tr>
                <td width="40%" align="center"><?php printf( $_STR[Login1] ); ?>:</td>
                <td align="center"><input type="text" name="userid" /></td>
            </tr>
            <tr>
                <td align="center"><?php printf( $_STR[Login2] ); ?>:</td>
                <td align="center"><input type="password" name="password" /></td>
            </tr>
            <tr>
                <td colspan="2"></td>
            </tr>
            <tr>
                <td colspan="2" align="center">
                <input type="submit" name="login" value="<?php printf( $_STR[Login3] ); ?>" />
                </td>
            </tr>
        </table>
    </form>
    </center>
<?php
    }
}

if( $_SESSION['AID'] != "" )
{
    check_ugradeid();

    switch($_GET['do'])
    {
        case "notepad":
            $includefile = "notepad.php";
            $title = $_STR[Menu3];
            break;
        case "ascii":
            $includefile = "ascii.php";
            $title = $_STR[Menu4];
            break;
        case "search":
            $includefile = "search.php";
            $title = $_STR[Menu5];
            break;
        case "accounts":
            $includefile = "accounts.php";
            $title = $_STR[Menu6];
            break;
        case "characters":
            $includefile = "characters.php";
            $title = $_STR[Menu7];
            break;
        case "clans":
            $includefile = "clans.php";
            $title = $_STR[Menu9];
            break;
        case "country":
            $includefile = "plugin_country.php";
            $title = $_STR[Menu10];
            break;
        case "logout":
            logout();
            break;
        default:
            $includefile = "panel.php";
            $title = $_STR[Menu2];
            break;
    }
?>

<div align="center">
<table border="0" width="85%" style="border-collapse: collapse" id="main" cellspacing="0" cellpadding="0">
	<tr>
		<td height="67" width="220" background="images/header_l.jpg" STYLE="background-repeat:no-repeat"></td>
		<td width="6" align="left" background="images/header_r_1.jpg" STYLE="background-repeat:no-repeat"></td>
		<td background="images/header_r_2.jpg"><b><?php echo $title ?></b></td>
	</tr>
	<tr>
		<td valign="top" width="220" background="images/panel_l_d.jpg">
			<table border="0" width="220" cellspacing="0" cellpadding="0">
			<tr>
				<td valign="top" height="319" background="images/panel_l_t.jpg" STYLE="background-repeat:no-repeat">
					<table width="220">
					<tr>
						<td valign="top" height="7"></td>
					</tr>
					<tr>
						<td height="25" width="10"></td>
						<td valign="center"><font size="2"><?php printf($_STR[Menu1], $_SESSION[UserID]); ?></font></td>
					</tr>
					<tr>
					<td colspan="2" height="50"></td>
					</tr>
					<tr>
					<td width="8"></td>
					<td><a href="index.php"><font size="2"><?php echo $_STR[Menu2]; ?></font></a></td>
					</tr>
					<tr>
					<td width="8"></td>
					<td><a href="index.php?do=notepad"><font size="2"><?php echo $_STR[Menu3]; ?></font></a></td>
					</tr>
					<tr>
					<td width="8"></td>
					<td><a href="index.php?do=ascii"><font size="2"><?php echo $_STR[Menu4]; ?></font></a></td>
					</tr>
					<tr>
					<td width="8"></td>
					<td><a href="index.php?do=search"><font size="2"><?php echo $_STR[Menu5]; ?></font></a></td>
					</tr>
					<tr>
					<td width="8"></td>
					<td><a href="index.php?do=accounts"><font size="2"><?php echo $_STR[Menu6]; ?></font></a></td>
					</tr>
					<tr>
					<td width="8"></td>
					<td><a href="index.php?do=characters"><font size="2"><?php echo $_STR[Menu7]; ?></font></a></td>
					</tr>
					<tr>
					<td width="8"></td>
					<td><a href="index.php?do=clans"><font size="2"><?php echo $_STR[Menu9]; ?></font></a></td>
					</tr>
                    <?php
                    if( $_CONFIG[CountryBlock] == 1 )
                    {
                    ?>
					<tr>
					<td width="8"></td>
					<td><a href="index.php?do=country"><font size="2"><?php echo $_STR[Menu10]; ?></font></a></td>
					</tr>
                    <?php
                    }
                    ?>
					<tr>
					<td width="8"></td>
					<td><a href="index.php?do=logout"><font size="2"><?php echo $_STR[Menu8]; ?></font></a></td>
					</tr>
					</table>
				</td>
        	</tr>
			</table>		
		</td>
		<td width="6" background="images/panel_l_d.jpg"></td>
		<td valign="top" height="500" bgcolor="#2A2C2B"> 
			<table width="100%">
			<tr>
				<td width="10"></td>
				<td><?php include $includefile; ?></td>
			</tr>
			</table>
		 
		</td>
	</tr>
</table>
</div>
<?php
}
?>

</body>

</html>