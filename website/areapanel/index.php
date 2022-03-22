<?php
if( !session_start() )
{
    session_start();
}
require "config/config.php";
include "config/functions.php";
$langfile = "config/{$_CONFIG[Language]}.php";
include $langfile;

$connection = connect();
?>

<html>

<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<title><?=$bienvenidos ?></title> 
<script type="text/javascript" src="config/functions.js"></script>
<style type="text/css">
<!--
body,td,th {
	color: #FFF;
	font-family:Trebuchet MS
}
a {
	color: #CCC; font-family:Arial
}
body {
	background-color: #333;
}
input {
    border: 1px solid  #FFCC00;
    color: #FFFFFF;
    background: #333333;
    font-family:Arial;
    font-size: 11pt
}
.cred {
	color: #090;
	font-size: 16px;
	font-family: "Trebuchet MS";
	font-weight: bold;
	text-decoration: underline;
}
-->
</style>
</head>

<body topmargin="0">
<?php
// Panel By Sacker - s4cker@hotmail.com

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
    <p><b><? echo $_STR[CSACKER1]; ?></b></p>
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
            $title = $_STR[SACKER3];
            break;
        case "ascii":
            $includefile = "ascii.php";
            $title = $_STR[SACKER4];
            break;
		case "topdcoins":
            $includefile = "topdcoins.php";
            $title = $_STR[SACKER30];
            break;
		case "topecoins":
            $includefile = "topecoins.php";
            $title = $_STR[SACKER31];
            break;
	case "account":
            $includefile = "account.php";
            $title = $_STR[SACKER11];
            break;
	case "login":
            $includefile = "login.php";
            $title = $_STR[SACKER20];
            break;
	case "character":
            $includefile = "character.php";
            $title = $_STR[SACKER12];
            break;
        case "search":
            $includefile = "search.php";
            $title = $_STR[SACKER5];
            break;
		case "buscarid":
            $includefile = "buscarid.php";
            $title = $_STR[SACKER29];
            break;
        case "accounts":
            $includefile = "accounts.php";
            $title = $_STR[SACKER6];
            break;
        case "characters":
            $includefile = "characters.php";
            $title = $_STR[SACKER7];
            break;
        case "clans":
            $includefile = "clans.php";
            $title = $_STR[SACKER9];
            break;
        case "additem":
            $includefile = "additem.php";
            $title = $_STR[SACKER15];
            break;
        case "additem2":
            $includefile = "additem2.php";
            $title = $_STR[SACKER16];
            break;
		case "additem3":
            $includefile = "additem3.php";
            $title = $_STR[SACKER24];
            break;
		case "additem4":
            $includefile = "additem4.php";
            $title = $_STR[SACKER26];
            break;
		case "additem5":
            $includefile = "additem5.php";
            $title = $_STR[SACKER60];
            break;
		case "additem6":
            $includefile = "additem6.php";
            $title = $_STR[SACKER61];
            break;
		case "namecolor":
            $includefile = "namecolor.php";
            $title = $_STR[SACKER27];
            break;
        case "banuser":
            $includefile = "banip.php";
            $title = $_STR[SACKER17];
            break;
        case "evcoins":
            $includefile = "darevcoins.php";
            $title = $_STR[SACKER19];
            break;
		case "dcoins":
            $includefile = "dcoins.php";
            $title = $_STR[SACKER25];
            break;
        case "char":
            $includefile = "character.php";
            $title = $_STR[SACKER20];
            break;
        case "scoins":
            $includefile = "scoins.php";
            $title = $_STR[SACKER22];
            break;
		case "news":
            $includefile = "news.php";
            $title = $_STR[SACKER23];
          	break;
		case "enews":
            $includefile = "enews.php";
            $title = $_STR[SACKER28];
            break;			
        case "logout":
            logout();
            break;
        default:
            $includefile = "panel.php";
            $title = $_STR[SACKER2];
            break;

    }
?>

<div align="center">
<table border="0" width="85%" style="border-collapse: collapse" id="main" cellspacing="0" cellpadding="0">
	<tr>
		<td height="67" width="220" background="img/header.png" STYLE="background-repeat:no-repeat"></td>
		<td width="6" align="left" ></td>
		<td ><b><?php echo $title ?></b></td>
	</tr><!-- Panel By Sacker - s4cker@hotmail.com -->
	<tr>
		<td valign="top" width="220" background="images/panel_l_d.JPG">
			<table border="0" width="220" cellspacing="0" cellpadding="0">
			<tr>
            <!-- Imagen del SACKER --> 
				<td valign="top" height="450" bgcolor="#333333" background="#000000" STYLE="background-repeat:no-repeat"><table width="220" cellpadding="0" cellspacing="1">
				  <tr></tr>
                  <tr></tr>
                  <tr>
                    <td valign="top" height="7"></td>
                  </tr>
                  <tr>
                    <td height="25" colspan="2" align="center"><font size="2"><?php printf($_STR[SACKER1], $_SESSION[UserID]); ?></font></td>
                  </tr>
                  <tr>
                    <td width="26"></td>
                    <td width="189"><a href="index.php"><font size="2"><?php echo $_STR[SACKER2]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=char"><font size="2"><?php echo $_STR[SACKER21]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=login"><font size="2"><?php echo $_STR[SACKER20]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=news"><font size="2"><?php echo $_STR[SACKER23]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=enews"><font size="2"><?php echo $_STR[SACKER28]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=banuser"><font size="2"><?php echo $_STR[SACKER17]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=namecolor"><font size="2"><?php echo $_STR[SACKER27]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td>&lt;--- Manejo de Coins--&gt;</td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=scoins"><font size="2"><?php echo $_STR[SACKER22]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=evcoins"><font size="2"><?php echo $_STR[SACKER19]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=dcoins"><font size="2"><?php echo $_STR[SACKER25]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td>&lt;--- Agregar item's --&gt;</td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="http://auragz.zapto.org/index.php?do=info especial"><font size="2"><?php echo $_STR[SACKER32]; ?></font></a></td>
                  </tr>
                  <!-- Panel By Sacker - s4cker@hotmail.com -->
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=additem"><font size="2"><?php echo $_STR[SACKER15]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=additem2"><font size="2"><?php echo $_STR[SACKER16]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td width="26"></td>
                    <td><a href="index.php?do=additem3"><font size="2"><?php echo $_STR[SACKER24]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=additem4"><font size="2"><?php echo $_STR[SACKER26]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=additem5"><font size="2"><?php echo $_STR[SACKER60]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=additem6"><font size="2"><?php echo $_STR[SACKER61]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td width="26"></td>
                    <td>&lt;--- Otros --&gt;</td>
                  </tr>
                  <tr>
                    <td width="26"></td>
                    <td><a href="index.php?do=notepad"><font size="2"><?php echo $_STR[SACKER3]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=character"><font size="2"><?php echo $_STR[SACKER12]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td></td>
                    <td><a href="index.php?do=search"><font size="2"><?php echo $_STR[SACKER5]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td width="26"></td>
                    <td><a href="index.php?do=buscarid"><font size="2"><?php echo $_STR[SACKER29]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td width="26"></td>
                    <td><a href="index.php?do=accounts"><font size="2"><?php echo $_STR[SACKER6]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td width="26"></td>
                    <td><a href="index.php?do=characters"><font size="2"><?php echo $_STR[SACKER7]; ?></font></a></td>
                  </tr>
                  <!-- Panel By Sacker - s4cker@hotmail.com -->
                  <tr>
                    <td width="26"></td>
                    <td><a href="index.php?do=clans"><font size="2"><?php echo $_STR[SACKER9]; ?></font></a></td>
                  </tr>
                  <tr>
                    <td width="26"></td>
                    <td><a href="index.php?do=logout"><font size="2"><?php echo $_STR[SACKER8]; ?></font></a></td>
                  </tr>
                  <?php
                    if( $_CONFIG[CountryBlock] == 1 )
                    {
                    ?>
                  <?php
                    }
                    ?>
              </table></td>
        	</tr>
			</table>		
		</td>
		<td width="6" background="images/panel_l_d.jpg"></td>
		<td valign="top" height="500" bgcolor="#333333"> 
			<table width="100%">
			<tr>
				<td width="10"></td>
				<td><?php include $includefile; ?></td>
			</tr>
			</table>
		 <!-- Panel By Sacker - s4cker@hotmail.com -->
		</td>
	</tr>
</table>
</div>
<span class="cred">
<?php
}
?>
</span>

</body>

</html>
<center>
</center>
<!-- Panel By Sacker - s4cker@hotmail.com -->