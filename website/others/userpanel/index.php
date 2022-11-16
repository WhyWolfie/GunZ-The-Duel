<?php
session_start();
include("secure/config.php");
include("secure/functions.php");
include("secure/anti_sql.php");

if($_SESSION['UGradeID'] == 253){
  echo "Your Account is Banned";
  die();
}
$page = sql($_GET['page']);
?>
<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>//Title</title>
<?php
Title("KnightGunZ - UserPainel");
?>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
<link href="style.css" rel="stylesheet" type="text/css">
<script language="JavaScript">
var message="";
///////////////////////////////////
function clickIE() {if (document.all) {(message);return false;}}
function clickNS(e) {if
(document.layers||(document.getElementById&&!document.all)) {
if (e.which==2||e.which==3) {(message);return false;}}}
if (document.layers)
{document.captureEvents(Event.MOUSEDOWN);document.onmousedown=clickNS;}
else{document.onmouseup=clickNS;document.oncontextmenu=clickIE;}
document.oncontextmenu=new Function("return false")
</script>
</head>
<body>
<?php if ($_SESSION['UserID']){ ?>
<br /><br /><br /><br />
<div id="table_header">
 <div class="table_h">
<?php
  echo 'Bem Vindo, <b><a>'.$_SESSION['UserID'].'</a></b>';
?>
<div id="link_home"><a href="index.php"><b>Inicio</b></a></div>
 </div>
</div>

<div id="table_body">
 <div class="table_b">
<?php
if($page == ""){
echo "
<div class='ap'>
<table>
<tr>
<td>
   <a href='/index.php'>Voltar</a>
   </td><td>
   <div class='line'></div>
   <td>
   <a href='index.php?page=editinfo'>Editar Perfil</a>
   </td><td>
   <div class='line'></div>
   </td><td>
   <a href='index.php?page=changepassword'>Editar senha</a>
   </td><td>
   <div class='line'></div>
   </td><td>
   <a href='index.php?page=stats'>Status do Jogador</a>
   </td><td>
   <div class='line'></div>
   </td>
   </td><td> 
   <a href='index.php?page=logout'>Logout</a>
   </td>   
</tr> 
</table>
</div>

";
}elseif($page == "changepassword"){
  include("inc/changepassword.php");
  Title("UserPanel &bull; Change Password");
}elseif($page == "stats"){
  include("inc/stats.php");
  Title("UserPanel &bull; User Stats");
}elseif($page == "changesex"){
  include("inc/changesex.php");
  Title("UserPanel &bull; Change Sex");
}elseif($page == "clan"){
  include("inc/clan.php");
  include("inc/logout.php");
  Title("UserPanel &bull; Logout");
}elseif($page == "editinfo"){
  include("inc/editinfo.php");
  Title("UserPanel &bull; Edit Info");
}
?> 
 </div>
</div>

<div id="table_footer"></div>
<div id="footer">
  <!-- Please to not remove credits -->
  Copyright &copy; 2012 AulaGunZ UserPanel &bull; Created By <a>Emisand</a>
</div>
<?php
}else{
  include("inc/login.php");
}
?>
</body>
</html>