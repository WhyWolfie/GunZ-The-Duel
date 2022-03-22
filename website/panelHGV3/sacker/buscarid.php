<!-- Coding By Sacker - GodOfWar -->
<title>Buscaor de Cuenta con DCoins</title>
<style type="text/css">
.tabla {
	font-size: 14px;
	font-style: normal;
	color: #F93;
}
.x {
	text-align: center;
}
</style><center>
<!-- Creador Sacker  -  s4cker@hotmail.com -->
<form action="index.php?do=buscarid" method="post" name="form1" class="x">
   <p>Buscador de DCoins   </p>
 <table width="215" border="0" align="center">
  <tr>

    <td width="52">UserID:</td>
    <td width="153"><input name="busca" type="text" id="busca" /></td>
  </tr>

</table>
 <input type="submit" name="Submit" value="Buscar Coins" />
<p>&nbsp;</p>
</form>
<?php
// By Sacker
$busca="";
$busca=$_POST['busca'];
if($busca!== ""){
	$busqueda=mssql_query("SELECT * FROM Account WHERE UserID = '".$busca."'");{
		}
while($f = mssql_fetch_array($busqueda)){
	$user = $f['UserID'];
	$aid = $f['AID'];
	$dcoins = $f['DonatorCoins'];
	$ecoins = $f['EventCoins'];
	$coins = $f['Coins'];
	$name = $f['Name'];
	// By Sacker
	?>
	

<table width="551" border="1" align="center">
  <tr>
    <td width="46" class="tabla">AID</td>
    <td width="111" class="tabla">UserID</td>
    <td width="115" class="tabla">Nombre</td>
    <td width="91" class="tabla">DonatorCoins</td>
    <td width="79" class="tabla">EventCoins</td>
    <td width="69" class="tabla">Coins</td>
  </tr>
  <tr>
    <td><? echo $aid; ?></td>
    <td><? echo $user; ?></td>
    <td><? echo $name; ?></td>
    <td><? echo $dcoins; ?></td>
    <td><? echo $ecoins; ?></td>
    <td><? echo $coins; ?></td>
  </tr>
</table>
<?
}
}
?>
<!-- Creador Sacker  -  s4cker@hotmail.com -->
</center>
<!-- Creador Sacker  -  s4cker@hotmail.com -->