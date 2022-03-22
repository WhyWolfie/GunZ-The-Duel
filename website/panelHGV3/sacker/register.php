<?
if(isset($_POST[reg])){
	$user = clean($_POST['userid']);
	$pw	  =  clean($_POST['pass']);
	$email =  clean($_POST['email']);
	$name =  clean($_POST['name']);
	$type =  clean($_POST['type']);
	if(empty($user) || empty($pw) || empty($email) || empty($name)){
		msgbox("Porfavor rellna los campos.","index.php?do=reg");
		die();
		}
	$reg  = "SELECT * From Account WHERE UserID ='$user'";
	$reg2 = "SELECT * From Account WHERE Email='$email'";
	$us = mssql_query($reg);
	$es = mssql_query($reg2);
	if(mssql_num_rows($us) == 1){
		msgbox("El usuario $user, Ya existe"."index.php?do=reg");
		die();
		}
	if(mssql_num_rows($es) == 1){
		msgbox("El Email $email, Ya existe"."index.php?do=reg");
		die();
		}

mssql_query("INSERT INTO Account (UserID, Email, Name, RegDate, UGradeID, PGradeID) VALUES ('$user', '$email', '$name', GETDATE(), '$type', 0)");
		$userid = mssql_query("SELECT * From Account WHERE AID='$aid'");	
		$acc = mssql_fetch_object($userid);
		$aid = $acc->AID;
	
		mssql_query("INSERT INTO Login (UserID, AID, Password) VALUES ('$user', '$aid', '$pw')");
		msgbox("Usuario $user, Registrador con Exito.","index.php?do=reg");
		die();
	}
?>
<style type="text/css">
<!--
.style1 {color: #FF0000}
.sacker {
	color: #F00;
	font-weight: bold;
}
.sacker {
	text-align: center;
}

-->
</style>
<body bgcolor="#323232">

                 
<form method="POST" action="index.php?do=reg">
<table width="454" height="100%" border="1" align="center" style="border-collapse: collapse">
  <tr>
    <td width="432" colspan="3"><table width="444" height="154" border="0">
     <tr>
        <td height="23">&nbsp;</td>
        <td colspan="3">Registro Rapido panel SackerZ </td>
        </tr>
      <tr>
        <th width="32" height="23" scope="col">&nbsp;</th>
        <td width="102" scope="col">UserID:</td>
        <td width="178" scope="col"><input type="text" name="userid" ></td>
        <td width="104" scope="col">&nbsp;</td>
      </tr>
      <tr>
        <td height="23">&nbsp;</td>
        <td>Password:</td>
        <td><input type="password" name="pass" id="pss" ></td>
        <td>&nbsp;</td>
      </tr>
      
      <tr>
        <td height="23">&nbsp;</td>
        <td>Email:</td>
        <td><input type="text" name="email" id="email" ></td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td height="23">&nbsp;</td>
        <td>Nombre:</td>
        <td><input type="text" name="name" id="name" ></td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td height="23">&nbsp;</td>
        <td>Tipo de User</td>
        <td><select name="type"><option value="0" selected>Normal</option><option value="255">Administrador</option>   <option value="254">Desarrollador</option>    <option value="252">Moderador</option>
    <option value="2">User Con jjang</option></select></td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td height="23">&nbsp;</td>
        <td>&nbsp;</td>
        <td><input type="submit" name="reg" value="Registrar User"></td>
        <td>&nbsp;</td>
      </tr>
     
    </table>
</form>




</div>

</body>
</html>

