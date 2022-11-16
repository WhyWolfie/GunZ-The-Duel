<?
function checar_baneo_ip($ip){
	$ipusuario = $ip;
	$select = "SELECT * FROM WebIpBan WHERE ip = '".$ipusuario."'";
	$query = mssql_query($select);
	$rows = mssql_num_rows($query);
	if($rows<1)
	{
		
	}else{
		$row = mssql_fetch_array($query);
		?>
		<center>
			<h1>
		Tu IP: <b><?=$_SERVER['REMOTE_ADDR']?></b> Ha Sido Baneada<br><br>
		Causa: <b><?=$row['razon']?></b><br><br>
		Fue Baneada La Fecha: <b><?=$row['fecha']?></b><br><br>
		Porfavor Contacte Con un Administrador!
		<?
		die();
	}
}
?>