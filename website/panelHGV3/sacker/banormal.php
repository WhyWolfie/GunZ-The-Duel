<?php
//Coding By Sacker - GodOfWar

    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }

if (isset($_POST['submit'])){
	$user = clean_sql($_POST['user']);
	mssql_query("UPDATE Account SET UGradeID = '253' WHERE UserID = '$user'");
	msgbox("Usuario $user ha sido banneado. para SIEMPRE (;","index.php?do=banuser");
}else{
	
}
?>
<form name="ban" method="POST" action="index.php?do=banuser"><table border="1" style="border-collapse: collapse" width="454" height="100%">


										<tr>
										  <td colspan="3">Ban User </td>
    </tr>

										<tr>
											<td width="135" height="44">
											<p align="right">
										UserID
										  </td>
											<td width="106"><input type="text" name="user" size="26" />
									      </td>
											
										</tr>

									

										
										<tr>
											<td height="85" colspan="3">
											<p align="center">
											  <input type="submit" value="Ban User" name="submit">
											</td>
										</tr>
										</table>
</form>