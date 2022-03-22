<?php
if( !session_start() )
{
    session_start();
}
require "config/config.php";
include "functions.php";
$langfile = "config/{$_CONFIG[Language]}.php";
include $langfile;

$connection = connect();
?>

<html>

<head>
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title>Panel SackerZ</title> 
<style type="text/css">
<!--
body,td,th {
	color:#0C6; font-family:Trebuchet MS
}
a {
	color: #00FF99; font-family:Trebuchet MS
}
body {
	background-color:#000;
}
input {
    border: 1px solid  #0C6;
    color: #000000;
    background: #0C6;
    font-family:Trebuchet MS;
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
        <table width="30%" border="1" align="center" id="login" style="border-collapse: collapse">
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
            $includefile = "sacker/notepad.php";
            $title = $_STR[SACKER3];
            break;
        case "ascii":
            $includefile = "sacker/ascii.php";
            $title = $_STR[SACKER4];
            break;
		case "topdcoins":
            $includefile = "sacker/topdcoins.php";
            $title = $_STR[SACKER30];
            break;
		case "topecoins":
            $includefile = "sacker/topecoins.php";
            $title = $_STR[SACKER31];
            break;
	case "account":
            $includefile = "sacker/account.php";
            $title = $_STR[SACKER11];
            break;
	case "topclan":
            $includefile = "sacker/topclan.php";
            $title = $_STR[SACKER32];
            break;	
	case "reg":
            $includefile = "sacker/register.php";
            $title = $_STR[SACKER35];
            break;		
			
	case "login":
            $includefile = "sacker/login.php";
            $title = $_STR[SACKER20];
            break;
	case "character":
            $includefile = "sacker/character.php";
            $title = $_STR[SACKER12];
            break;
        case "search":
            $includefile = "sacker/search.php";
            $title = $_STR[SACKER5];
            break;
		case "buscarid":
            $includefile = "sacker/buscarid.php";
            $title = $_STR[SACKER29];
            break;
        case "accounts":
            $includefile = "sacker/accounts.php";
            $title = $_STR[SACKER6];
            break;
        case "characters":
            $includefile = "sacker/characters.php";
            $title = $_STR[SACKER7];
            break;
        case "clans":
            $includefile = "sacker/clans.php";
            $title = $_STR[SACKER9];
            break;
        case "additem":
            $includefile = "sacker/additem.php";
            $title = $_STR[SACKER15];
            break;
        case "additem2":
            $includefile = "sacker/additem2.php";
            $title = $_STR[SACKER16];
            break;
		case "additem3":
            $includefile = "sacker/additem3.php";
            $title = $_STR[SACKER24];
            break;
		case "additem4":
            $includefile = "sacker/additem4.php";
            $title = $_STR[SACKER26];
            break;
		case "quitaritem":
            $includefile = "sacker/quitaritem.php";
            $title = $_STR[SACKER33];
            break;
		case "namecolor":
            $includefile = "sacker/namecolor.php";
            $title = $_STR[SACKER27];
            break;
        case "banuser":
            $includefile = "sacker/banormal.php";
            $title = $_STR[SACKER17];
            break;
        case "banip":
            $includefile = "sacker/banip.php";
            $title = $_STR[SACKER18];
            break;
        case "evcoins":
            $includefile = "sacker/darevcoins.php";
            $title = $_STR[SACKER19];
            break;
		case "dcoins":
            $includefile = "sacker/dcoins.php";
            $title = $_STR[SACKER25];
            break;
        case "char":
            $includefile = "sacker/character.php";
            $title = $_STR[SACKER20];
            break;
		case "topugrade";
			$includefile = "sacker/topugrades.php";
			$title = $_STR[SACKER34];
			break;
        case "scoins":
            $includefile = "sacker/scoins.php";
            $title = $_STR[SACKER22];
            break;
		case "news":
            $includefile = "sacker/news.php";
            $title = $_STR[SACKER23];
          	break;
		case "enews":
            $includefile = "sacker/enews.php";
            $title = $_STR[SACKER28];
            break;			
        case "logout":
            logout();
            break;
        default:
            $includefile = "sacker/panel.php";
            $title = $_STR[SACKER2];
            break;

    }
?>

<div align="center">
<table border="0" width="85%" style="border-collapse: collapse" id="main" cellspacing="0" cellpadding="0">
	<tr>
		<td height="67" width="220" background="img/header.png" STYLE="background-repeat:no-repeat"></td>
		<td width="6" align="left" background="images/header_r_1.jpg" STYLE="background-repeat:no-repeat"></td>
		<td background="images/header_r_2.jpg"><b><?php echo $title ?></b></td>
	</tr>
	<tr>
		<td valign="top" width="220" background="images/panel_l_d.jpg">
			<table border="0" width="220" cellspacing="0" cellpadding="0">
			<tr>
				<td valign="top" height="350" background="images/panel_l_t.jpg" STYLE="background-repeat:no-repeat">
					<table width="220">
					<tr>
						<td valign="top" height="7"></td>
					</tr>
					<tr>
						<td height="25" width="10"></td>
						<td valign="center"><font size="2"><?php printf($_STR[SACKER1], $_SESSION[UserID]); ?></font></td>
					  </tr>
					
					<tr>
					<td width="26"></td>
					<td width="189"><a href="index.php"><font size="2"><?php echo $_STR[SACKER2]; ?></font></a></td>
					</tr>
					<tr>
					  <td></td>
					  <td><a href="index.php?do=account"><font size="2"><?php echo $_STR[SACKER11]; ?></font></a></td>
					  </tr>
                      	<tr>
					  <td></td>
					  <td><a href="index.php?do=topclan"><font size="2"><?php echo $_STR[SACKER32]; ?></font></a></td>
					  </tr>
                    <tr>
					  <td></td>
					  <td><a href="index.php?do=topdcoins"><font size="2"><?php echo $_STR[SACKER30]; ?></font></a></td>
					  </tr>
                     <tr>
					  <td></td>
					  <td><a href="index.php?do=topecoins"><font size="2"><?php echo $_STR[SACKER31]; ?></font></a></td>
					  </tr>
                         <tr>
					  <td></td>
					  <td><a href="index.php?do=topugrade"><font size="2"><?php echo $_STR[SACKER34]; ?></font></a></td>
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
					<td width="26"></td>
					<td><a href="index.php?do=reg"><font size="2"><?php echo $_STR[SACKER35]; ?></font></a></td>
					</tr>
                      <tr>
					  <td></td>
					  <td>//Type Coins</td>
					  </tr>                      
					<tr>
					  <td>
                      </td>
					  <td><a href="index.php?do=scoins"><font size="2"><?php echo $_STR[SACKER22]; ?></font></a></td>					  </tr>
                      <tr>
					  <td></td>
					  <td><a href="index.php?do=evcoins"><font size="2"><?php echo $_STR[SACKER19]; ?></font></a></td>
					  </tr><!-- Panel By Sacker - s4cker@hotmail.com -->
                      <tr>
					  <td></td>
					  <td><a href="index.php?do=dcoins"><font size="2"><?php echo $_STR[SACKER25]; ?></font></a></td>
					  </tr>
                      <tr>
					  <td></td>
					  <td>//Add Items Shop</td>
					  </tr> 
                      <tr>
					<td width="26"></td>
					<td><a href="index.php?do=additem"><font size="2"><?php echo $_STR[SACKER15]; ?></font></a></td>
					</tr>                     
					<tr>
					  <td><!-- Panel By Sacker - s4cker@hotmail.com -->
                      </td>
					  <td><a href="index.php?do=additem2"><font size="2"><?php echo $_STR[SACKER16]; ?></font></a></td>
					  </tr>					
                    <tr>
					<td width="26"></td>
					<td><a href="index.php?do=additem3"><font size="2"><?php echo $_STR[SACKER24]; ?></font></a></td>
					</tr>
                    <tr>
					<td width="26"></td>
					<td><a href="index.php?do=additem4"><font size="2"><?php echo $_STR[SACKER26]; ?></font></a></td>
					</tr>
                     <tr>
					<td width="26"></td>
					<td><a href="index.php?do=quitaritem"><font size="2"><?php echo $_STR[SACKER33]; ?></font></a></td>
					</tr>
                    <tr>
					  <td></td>
					  <td>//Otros</td>
					  </tr> 
					<tr>
					  <td></td>
					  <td><a href="index.php?do=notepad"><font size="2"><?php echo $_STR[SACKER3]; ?></font></a></td>
					  </tr>
					
					<tr>
                    
					<td width="26"></td>
					<td><a href="index.php?do=ascii"><font size="2"><?php echo $_STR[SACKER4]; ?></font></a></td>
					</tr>
			
					<tr>
					<td width="26"></td>
					<td><a href="index.php?do=character"><font size="2"><?php echo $_STR[SACKER12]; ?></font></a></td>
					</tr>
					<tr>
					<td width="26"></td>
					<td><a href="index.php?do=search"><font size="2"><?php echo $_STR[SACKER5]; ?></font></a></td>
					</tr><!-- Panel By Sacker - s4cker@hotmail.com -->
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
					<tr>
					<td width="26"></td>
					<td><a href="index.php?do=clans"><font size="2"><?php echo $_STR[SACKER9]; ?></font></a></td>
					</tr>
                    <?php
                    if( $_CONFIG[CountryBlock] == 1 )
                    {
                    ?>
				
                    <!-- Panel By Sacker - s4cker@hotmail.com -->
					
                    <?php
                    }
                    ?>
					<tr>
					<td width="26"></td>
					<td><a href="index.php?do=logout"><font size="2"><?php echo $_STR[SACKER8]; ?></font></a></td>
					</tr>					
					</table>
				</td>
        	</tr>
			</table>		
		</td>
		<td width="6" background="images/panel_l_d.jpg"></td>
		<td valign="top" height="500" bgcolor="#000000"> 
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
<p class="cred"> <span class="cred"><? echo base64_decode(s());?></span></p>
</center>
<!-- Panel By Sacker - s4cker@hotmail.com -->

