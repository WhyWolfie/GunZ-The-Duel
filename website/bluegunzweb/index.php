<?php
session_start();
include("secure/config.php");
include("secure/functions.php");
include("secure/anti_sql.php");
include("language/$language.php");

//Ban
$sql = "SELECT UGradeID FROM Account WHERE UserID = '".$_SESSION['user']."'";
$query = mssql_query($sql);
$xx = mssql_fetch_assoc($query);
$ugid = $xx['UGradeID'];
$ban = $bannedugid;
if($ugid == $ban){
 die($banned['1']);
}
//IP Ban
$gip = $_SERVER['REMOTE_ADDR'];
$select_ip = "SELECT IP FROM ipbans";
$ipquery = mssql_query($select_ip);
 while($ipbanned = mssql_fetch_assoc($ipquery)){
  if($gip==$ipbanned['IP']){
    die("<h3 align='center'>".$banned['2']." $gunz_name.</h3>");
  }
 }
$act = anti_injection($_GET['act']);
$aid = anti_injection($_GET['aid']);
?>
<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><?php echo "//Title"; ?></title>
<?php
 Title("$gunz_name");
?>
 <meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
 <link href="style.css" rel="stylesheet" type="text/css" />
<style type="text/css">
<!--
body {
   background-color: #1b1b1b;
   background-image: url(images/bg.png);
   font-family: verdana;
   font-size: 12px;
   color: #FFF;
   margin: 0;
}
-->
</style>
</head>
<body>
<?php
if($act == "login"){
  Title("$gunz_name &bull; ".$title['18']."");
  include("includes/login.php");
}elseif($act == "logout"){
  Title("$gunz_name &bull; ".$title['19']."");
  include("includes/logout.php");
}else{
?>
 <div id="head_bg">
 <!-- Header Start -->
  <div id="header">
   <!-- Logo -->
   <div id="logo"></div>
  </div>
  <!-- Header End -->
  <!-- Navigation Start -->
  <div id="nav">
   <ul>
     <li><a href="index.php"><?php echo $nav['1']; ?></a></li>
     <li><a href="index.php?act=download"><?php echo $nav['2']; ?></a></li>
	 <?php if($_SESSION['user']){ ?>
     <li><a href="index.php?act=register" onclick="alert('<?php echo $regerror['8']; ?>');return false"><?php echo $nav['3']; ?></a></li>
	 <?php }else{ ?>
     <li><a href="index.php?act=register"><?php echo $nav['3']; ?></a></li>
	 <?php } ?>
     <li><a href="<?php echo $forum; ?>"><?php echo $nav['4']; ?></a></li>
     <li><a href="index.php?act=rankings"><?php echo $nav['5']; ?></a></li>
     <li><a href="index.php?act=stafflist"><?php echo $nav['6']; ?></a></li>
     <li><a href="<?php echo $vote; ?>"><?php echo $nav['7']; ?></a></li>
     <li><a href="index.php?act=itemshop"><?php echo $nav['8']; ?></a></li>
   </ul>
  </div>
  <!-- Navigation End -->
 </div>
<div id="body">
 <table border="0" width="100%">
  <tr>
   <td valign="top">
   <!-- Login Start -->
    <div id="login">
	 <table style="position:relative; left:12px; top:11px; width:90%;">
	  <tr><td width="220" height="15" class="tbl_title"><?php echo $title['1']; ?></td></tr>
	  <?php if($_SESSION['user'] == ""){ ?>
	  <tr><td height="140px" valign="top" style="font-size:11px; padding-top:5px;">
       <form action="index.php?act=login" method="post">
	    <?php echo $logpanel['1']; ?> <input type="text" name="userid" maxlength="15" class="logbbg" />
		<input type="submit" name="login" value="" class="login_button" />
	    <?php echo $logpanel['2']; ?> <input type="password" name="password" maxlength="20" class="logbbg" /> <br />
	   </form>
	    <div id="loginf">
	     <div style="padding-top:7px; font-size:10px;"><?php echo $logpanel['3']; ?> <a href="index.php?act=register"><?php echo $logpanel['5']; ?></a></div>
	     <div style="padding-top:5px; font-size:10px;"><?php echo $logpanel['4']; ?> <a href="index.php?act=forgottenpassword"><?php echo $logpanel['6']; ?></a></div>
	    </div>
	  </td></tr>
	  <?php }else{ ?>
	  <!-- Logged in Start -->
	   <tr><td class="loggeduser"><?php echo $logpanel['7'].' '.$_SESSION['user']; ?> <a href="index.php?act=logout"><?php echo $logpanel['8']; ?></a></td></tr>
	   <tr><td></td></tr><tr><td></td></tr>
	   <?php
	    $sqlloged = "SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'";
		$logquer = mssql_query($sqlloged);
		$logaid = mssql_fetch_assoc($logquer);
        echo '<tr><td class="logged_dline"><span class="logdu">'.$loinup['1'].' :</span> '.$logaid['Name'].'</td></tr>';
        echo '<tr><td class="logged_dline"><span class="logdu">'.$loinup['2'].' :</span> '.$logaid['Age'].'</td></tr>';
        echo '<tr><td class="logged_dline"><span class="logdu">-</td></tr>';
        echo '<tr><td class="logged_dline"><span class="logdu">'.$loinup['3'].' :</span> ';
		 if($logaid['Coins'] == ""){
		  echo "0";
		 }else{
		  echo $logaid['Coins'];
		 }
		echo '</td></tr>';
	   ?>
	   <tr><td></td></tr><tr><td></td></tr>
	   <tr><td class="logged_links">
	    <ul>
		<?php if($_SESSION['UGradeID'] == 255){ ?>
		 <li><a href="index.php?act=admin" class="admin_button"></a></li>
		<?php } ?>
		<?php if($_SESSION['UGradeID'] == 254){ ?>
		 <li><a href="index.php?act=gm" class="gm_button"></a></li>
		<?php } ?>
		 <li><a href="index.php?act=userpanel" class="user_button"></a></li>
		</ul>
	   </td></tr>
	  <!-- Logged in End -->
	  <?php } ?>
	 </table>
	</div><br />
	<!-- Login End -->
	<!-- Server Info -->
	<div id="server_info">
	 <table style="position:relative; left:12px; top:11px; width:90%;font-size:11px;">
	  <tr><td width="220" height="5px" class="tbl_title"><?php echo $title['2']; ?></td></tr>
	  <tr><td valign="top" style="padding-top:5px; padding-left:10px;">
      <?php
	  //Server Status
      $sql = "SELECT * FROM ServerStatus WHERE Opened != 0";
      $num = mssql_query($sql);
      while ($get = mssql_fetch_assoc($num)){
       $_host_name = $get['IP']; $_servers = Array(
        "<font color='#FF9900'><b>".$servinfo['1']." </b></font> "=> 6000,
       );
       foreach($_servers as $_servername => $_port){
        $_connection = @fsockopen($_host_name, $_port, $errno, $errstr, 0.003);
        if(!$_connection){
         $_status = "<font style='color:#c80026'><b>".$servinfo['8']."</b></font>";
        }else{
         $_status = "<font style='color:#159725'><b>".$servinfo['7']."</b></font>";
        }
        print $_servername . '' . $_status . '<br />';
      }
     }
     ?>
	 </td></tr><tr><td style="padding-left:10px;">
	  <?php
	  //Players Online
       $query = mssql_query("SELECT * FROM ServerStatus");
       if(mssql_num_rows($query)<>0){
	    while($status = mssql_fetch_assoc($query)){
         echo "<font color='#FF9900'><b>".$servinfo['2']." </b></font> ".$status['CurrPlayer'];
        }
       }
	  ?>
	  </td></tr>
	  <tr><td style="padding-left:10px;">
	   <font color="Darkorange"><b><?php echo $servinfo['3'].' '; ?></b></font> <?php echo $exprate; ?>
	  </td></tr>
	  <tr><td style="padding-left:10px;">
	  <?php
	   //Newest Player
	   $sqlnp = "SELECT TOP 1* FROM Account ORDER BY AID DESC";
	   $npquery = mssql_query($sqlnp);
	   $newestplayer = mssql_fetch_assoc($npquery);
	   echo "<font color='#FF9900'><b>".$servinfo['4']." </b></font>".$newestplayer['Name'];
	  ?>
	  </td></tr>
	  <tr><td style="padding-left:10px;">
	  <?php
	   //Total Accounts
       $query = "SELECT COUNT(*) FROM Account";
       $result = mssql_query($query);
       $row = mssql_fetch_row($result);
       echo '<font color="#FF9900"><b>'.$servinfo['5'].' </b></font>'.$row[0];
	  ?>
	  </td></tr>
	  <tr><td style="padding-left:10px;">
	  <?php
	   //Total Characters
       $query3 = "SELECT COUNT(*) FROM Character WHERE DeleteFlag='0'";
       $result3 = mssql_query($query3);
       $row3 = mssql_fetch_row($result3);
       echo '<font color="#FF9900"><b>'.$servinfo['9'].' </b></font>'.$row3[0];
	  ?>
	  </td></tr>
	  <tr><td style="padding-left:10px;">
	  <?php
	   //Total Clans
       $query2 = "SELECT COUNT(*) FROM Clan WHERE DeleteFlag='0'";
       $result2 = mssql_query($query2);
       $row2 = mssql_fetch_row($result2);
       echo '<font color="#FF9900"><b>'.$servinfo['6'].' </b></font>'.$row2[0];
	  ?>
	  </td></tr>
	 </table>
	</div>
	<!-- Server Info -->
	<br />
	<!-- Link To ItemShop Start -->
	<div align="center">
	 <a href="index.php?act=itemshop"><img src="images/itemshop.png" width="198" height="73" border="0" title="ItemShop" alt="" /></a>
	</div>
	<!-- Link To ItemShop End -->
   </td>
   <td valign="top" width="440">
    <!-- Server Status & Players Online -->
    <div id="server_player_status">
	 <table align="center" width="370" border="0" style="height:35px; position:relative; top:9px; text-align:center; color:#ff7200;">
	  <tr><td width="170">
      <?php
	  //Server Status
      $sql = "SELECT * FROM ServerStatus WHERE Opened != 0";
      $num = mssql_query($sql);
      while ($get = mssql_fetch_assoc($num)){
       $_host_name = $get['IP']; $_servers = Array(
        "<font color='#FF9900'><b>".$servinfo['1']." :</b></font> "=> 6000,
       );
       foreach($_servers as $_servername => $_port){
        $_connection = @fsockopen($_host_name, $_port, $errno, $errstr, 0.003);
        if(!$_connection){
         $_status = "<font style='color:#c80026'><b>Offline</b></font>";
        }else{
         $_status = "<font style='color:#159725'><b>Online</b></font>";
        }
        print $_servername . '' . $_status . '<br />';
      }
     }
     ?></td>
	  <td width="2"><div class="spsline"></div></td>
	  <td>
	  <?php
	  //Players Online
       $query = mssql_query("SELECT * FROM ServerStatus");
       if(mssql_num_rows($query)<>0){
	    while($status = mssql_fetch_assoc($query)){
         echo "<font color='#FF9900'><b>".$servinfo['2']." :</b></font> <font style='color:#c80026'><b>".$status['CurrPlayer'].'</b></font>';
        }
       }
	  ?>
	  </td></tr>
	 </table>
	</div><br /><br />
	<?php if($act == ""){ ?>
	<!-- News & Updates -->
	<div id="news_updates_head">
	 <div class="tbl_title_pos">
	  <?php echo $title['7']; ?>
	 </div>
	</div>
	<div id="news_updates_body">
	 <div class="tbl_pos">
     <?php include("includes/news_updates.html"); ?>
	 </div>
	</div>
	<div id="news_updates_footer"></div><br /><br />
	<!-- News & Updates End -->
	<!-- Top 5 Player & Clan Rankings -->
	<div id="top5ranks">
	 <table border="0" width="430" style="margin:0 auto; position:relative; top:10px;">
	   <tr><td class="tbl_title"><?php echo $title['5']; ?></td>
	   <td class="tbl_title"><?php echo $title['6']; ?></td></tr>
	 </table>
	 <table border="0" width="430" style="margin:0 auto; position:relative; top:11px; font-size:11px; text-align: center;">
	   <!-- Player & Clan Titles -->	   
	   <tr style="color:#07b803; text-shadow: 3px 2px 3px #000;">
	    <!-- Player -->
	    <td width="10"><?php echo $plranks['1']; ?></td><td width="70"><?php echo $plranks['2']; ?></td><td width="35"><?php echo $plranks['3']; ?></td>
	    <td width="63"><?php echo $plranks['4']; ?></td>
	    <!-- Clan -->
	    <td width="10"><?php echo $clranks['1']; ?></td><td width="70"><?php echo $clranks['2']; ?></td><td width="45"><?php echo $clranks['3']; ?></td>
	    <td width="40"><?php echo $clranks['4']; ?></td>
	   </tr>
	  </table>
	  <!-- Player Results -->
	  <table border="0" width="220" style="float:left; position:relative; top:12px; left:8px; font-size:10px; text-align:center; color:#c8c5c5;" class="rkslink">
	  <?php
	   $sqlt5pr = mssql_query("SELECT TOP 5* FROM Character WHERE DeleteFlag='0' ORDER BY Level DESC, XP DESC");
	   if(mssql_num_rows($sqlt5pr)<>0){
	   $count=1;
	    while($char = mssql_fetch_assoc($sqlt5pr)){
		 echo '<tr><td width="5">'.$count.'.</td>';
		 echo '<td width="65"><a href="index.php?act=profile&amp;aid='.$char['AID'].'">'.Char($char['CID']).'</a></td>';
		 echo '<td width="35">'.$char['Level'].'</td>';
		 echo '<td width="63">'.$char['XP'].'</td></tr>';
		 $count++;
		}
	   }else{
	    echo '<tr><td></td></tr>';
	   }
	  ?>
	 </table>
	  <!-- Clan Results -->
	  <table border="0" width="220" style="float:right;position:relative; top:12px; font-size:10px; text-align:center; color:#c8c5c5;">
	  <?php
	   $sqlt5cr = mssql_query("SELECT TOP 5* FROM Clan WHERE DeleteFlag='0' ORDER BY Point DESC,Wins DESC,Losses DESC");
	   if(mssql_num_rows($sqlt5cr)<>0){
	   $count=1;
	    while($clan = mssql_fetch_assoc($sqlt5cr)){
		 echo '<tr><td width="5">'.$count.'.</td>';
		 echo '<td width="60">'.$clan['Name'].'</td>';
		 echo '<td width="25">'.$clan['Point'].'</td>';
		 $clmemb = "SELECT COUNT(*) FROM ClanMember WHERE CLID='".$clan['CLID']."'";
         $memb_res = mssql_query($clmemb);
         $memb_row = mssql_fetch_row($memb_res);
		  echo '<td width="40">'.$memb_row[0].'</td></tr>';
		 $count++;
		}
	   }else{
	    echo '<tr><td></td></tr>';
	   }
	  ?>
	 </table>
	</div>
	<!-- Top 5 Player & Clan Rankings End -->
    <?php
    }elseif($act == "download"){
	 Title("$gunz_name &bull; ".$title['8']."");
	 include("includes/download.php");
	}elseif($act == "register"){
	 Title("$gunz_name &bull; ".$title['9']."");
	 include("includes/register.php");
	}elseif($act == "rankings"){
	 Title("$gunz_name &bull; ".$title['12']."");
	 include("includes/rankings.php");
	}elseif($act == "clanrankings"){
	 Title("$gunz_name &bull; ".$title['13']."");
	 include("includes/rankings.php");
	}elseif($act == "stafflist"){
	 Title("$gunz_name &bull; ".$title['11']."");
	 include("includes/stafflist.php");
	}elseif($act == "forgottenpassword"){
	 Title("$gunz_name &bull; ".$title['14']."");
	 include("includes/forgottenpassword.php");
	}elseif($act == "userpanel"){
	 Title("$gunz_name &bull; ".$title['14']."");
	 include("userpanel.php");
	}elseif($act == "admin"){
	 Title("$gunz_name &bull; ".$title['15']."");
	 include("admin.php");
	}elseif($act == "gm"){
	 Title("$gunz_name &bull; ".$title['16']."");
	 include("gm.php");
	}elseif($act == "profile"){
	 Title("$gunz_name &bull; ".$title['17']."");
	 include("profile.php");
	}elseif($act == "itemshop"){
	 Title("$gunz_name &bull; ".$title['20']."");
	 include("itemshop.php");
	}
    ?>
   </td>
   <td valign="top" width="220">
   <!-- Trailer Start -->
    <div id="trailer">
	 <table border="0" style="position:relative; left:12px; top: 11px; width:95%;">
	   <tr><td height="10" class="tbl_title"><?php echo $title['3']; ?></td></tr>
	   <tr><td height="110" valign="top">
	    <?php include("includes/trailer.html"); ?>
	   </td></tr>
	 </table>
	</div><br />
	<!-- Trailer End -->
	<!-- Links Start -->
	 <div id="links">
	 <table border="0" style="position:relative; left:12px; top: 11px; width:90%;">
	   <tr><td height="10px" class="tbl_title"><?php echo $title['4']; ?></td></tr>
	   <tr><td height="110px" valign="top" align="center" style="font-size:11px; padding-top:5px;">
	    <a href="<?php echo $forum; ?>"><img src="images/forum.png" width="178" height="40" border="0" alt="" title="<?php echo $linkimg['1']; ?>" style="padding-top:2px;" /></a>
	    <a href="<?php echo $vote; ?>"><img src="images/vote.png" width="178" height="40" border="0" alt="" title="<?php echo $linkimg['2']; ?>" style="padding-top:3px;" /></a>
	    <a href="<?php echo $donate; ?>"><img src="images/donate.png" width="178" height="40" border="0" alt="" title="<?php echo $linkimg['3']; ?>" style="padding-top:3px;" /></a>
	   </td></tr>
	 </table>
	 </div><br />
	<!-- Links End -->
	<!-- Newest Item Start -->
    <div id="newestitem">
	 <table border="0" style="position:relative; left:12px; top:8px; width:95%;">
	   <tr><td height="10" class="tbl_title"><?php echo $title['21']; ?></td></tr>
	   <tr><td height="110" valign="top">
	    <div class="nwstitm">
         <div class="itemshp_pos">
		 <?php
		  $sqlnwst = mssql_query("SELECT TOP 1* FROM ItemShop ORDER BY ID DESC");
		  $newstitm = mssql_fetch_assoc($sqlnwst);
		  if($_SESSION['user'] == ""){
		   echo '<img src="'.$newstitm['Image'].'" title="'.$newstitm['Name'].'" alt="" />';
		  }else{
		   echo '<a href="index.php?act=itemshop&do='.$newstitm['Category'].'&buy='.$newstitm['ItemID'].'">
		   <img src="'.$newstitm['Image'].'" title="'.$newstitm['Name'].'" alt="" />
		   </a>';
		  }
		 ?>
		 </div>
		</div>
	   </td></tr>
	 </table>
	</div>
	<!-- Newest Item End -->
   </td>
  </tr>
 </table>
</div>
<!-- Footer Start -->
<div id="footer_line"></div>
<div id="footer">
 <!-- Copyright -->
 <?php echo $copyright['1']; ?> <u><?php echo $gunz_name; ?></u>. <?php echo $copyright['2']; ?> <br /> <div style="padding-top:3px;"><?php echo $copyright['3']; ?> <a href="mailto:Z-e-w-a@hotmail.com"><?php echo $copyright['4']; ?></a></div>
</div><br />
<!-- Footer End -->
<?php } ?>
</body>
</html>