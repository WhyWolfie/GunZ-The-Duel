<?
session_start();
$host = "USUARIO-PC\SQLEXPRESS";
$user = "sa";
$pass = "26885650";
$ndb = "GunzDB";
$conex = mssql_connect($host,$user,$pass);
$db = mssql_select_db($ndb,$conex);
$_SESSION['mensaje_login'] = "";
if(isset($_POST['logear']))
{
	$user = $_POST['user'];
	$pass = $_POST['pass'];




/////////////////////Modificar Esta Parte/////////////////
	$user_para_conectar = "Zalish";
	$clave_para_conectar = "202020";
//////////////////////////////////////////////////////////



if($user==$user_para_conectar && $pass==$clave_para_conectar){

$_SESSION['paneladmin'] = "mad9hgadjasdmbua98b3589qa7b5aosd7ab78rao8we7r";
?>
	<meta http-equiv="refresh" content="0;url=managerip.php"/>
<?

}else{
	$_SESSION['mensaje_login'] = "Usuario o Contrase&ntilde;a Incorrectos";
}

}
if(isset($_SESSION['paneladmin']) && $_SESSION['paneladmin'] == "mad9hgadjasdmbua98b3589qa7b5aosd7ab78rao8we7r")
{
?>
<center>
	<form method="post" action="">
<table style="display:inline-block;" border="1">
	<tr>
		<th colspan="2">Banear IP</th>
	</tr>
	<tr>
		<td>IP: <input type="text" name="ip1"/></td>
		<td rowspan="2"><input type="submit" name="enviar1" value="Banear IP" style="height:50px;"/></td>
		</tr>
		<tr>
			<td>Razon:<br><textarea name="razon"></textarea></td>
		</tr>
	</table>
	<br><br><br>
	<table style="display:inline-block;" border="1"/>
	<tr>
		<th colspan="2">Desbanear IP</th>
	</tr>
	<tr>
		<td><select name="ip2">
			<?
			$select = "SELECT * FROM WebIpBan ORDER BY id DESC";
			$query = mssql_query($select);
			$rows = mssql_num_rows($query);
			if($rows>0)
			{
				while($row = mssql_fetch_array($query))
				{
					?>
					<option value="<?=$row['ip']?>"><?=$row['ip']?></option>
					<?
				}
			}else{
				?>
				<option value="">No Hay Ip Baneadas</option>
				<?
			}
			?>
			</select>
			</td>
			<td><input type="submit" name="enviar2" value="Desbanear IP"/></td>

		</tr>
	</table>
</form>


<?
if(isset($_POST['enviar1']))
{
	$ip = $_POST['ip1'];
	$razon = $_POST['razon'];
	
	$insert = "INSERT INTO WebIpBan(ip,fecha,razon)";
	$insert.= "VALUES('".$ip."',GETDATE(),'".$razon."')";
	mssql_query($insert);
	?>
	<br><br>
	<h1>Ip <font color="darkgreen"><?=$ip?></font> Baneada Satisfactoreamente.
		<meta http-equiv="refresh" content="2;url=managerip.php"/>
	<?

}
if(isset($_POST['enviar2']))
{
	$ip = $_POST['ip2'];
	if(empty($ip) || $ip == "")
	{
		?>
		<br><br><h1>No Hay Ip Baneadas <font color="darkred">Error.</font>
		<?
	}else{
	$delete = "DELETE FROM WebIpBan WHERE ip = '".$ip."'";
	mssql_query($delete);
	?>
	<br><br>
	<h1>IP <font color="darkgreen"><?=$ip?></font> Desbaneada Satisfactoriamente.
		<meta http-equiv="refresh" content="2;url=managerip.php"/>
	<?
}
}
if(isset($_POST['logout']))
{
	session_destroy();
	?>
	<meta http-equiv="refresh" content="0;url=managerip.php"/>
	<?
}
?>
<br><br><br><center><form method="post" action=""><input type="submit" name="logout" value="Deslogearse"/></form></center>
<?
}else{
	?>
	<form method="post" action="">
	<center>
		<h1>No Tienes Permiso - By Zalish</h1>
		<br><br><br><br>
		<table>
			<tr>
				<th colspan="2">Iniciar Sesi&oacute;n</th>
			</tr>
			<tr>
				<td>Usuario</td>
				<td><input type="text" name="user" /></td>
			</tr>
			<tr>
				<td>Contrase&ntilde;a</td>
				<td><input type="password" name="pass"/></td>
			</tr>
			<tr>
				<td colspan="2" align="center"><input type="submit" name="logear" value="Acceder"/></td>
			</tr>
		</table>
		<br><br><h1><?=$_SESSION['mensaje_login']?>
		<?
		$_SESSION['mensaje_login'] ="";
		?>
	</form>
	<?
}
?>