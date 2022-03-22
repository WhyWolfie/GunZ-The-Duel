<?
if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }
if (isset($_POST['submit'])){
	$user = clean_sql($_POST['user']);
	$ugrade = clean_sql($_POST['ugrade']);
	mssql_query("UPDATE Account SET UGradeID = '$ugrade' WHERE UserID = '$user'");
	msgbox("Usuario $user ahora tiene name color numero UGrade $ugrade ","index.php?do=namecolor");
}else{
	
}
?>
<form name="ban" method="POST" action="index.php?do=namecolor"><table border="1" style="border-collapse: collapse" width="454" height="100%">


										<tr>
										  <td colspan="3">Name Color al usuario. </td>
    </tr>

										<tr>
											<td width="135" height="44">
											<p align="right">
										UserID
										  </td>
											<td width="106"><input type="text" name="user" size="26" />
									      </td>
                                          <td width="106">
                                          <select size="1" name="ugrade">
                                          <option value="<? echo $_COLORUGRA_1 ?>"><? echo $_UGRADENAME_1 ?> </option>
                                          <option value="<? echo $_COLORUGRA_2 ?>"><? echo $_UGRADENAME_2 ?></option>
                                          <option value="<? echo $_COLORUGRA_3 ?>"><? echo $_UGRADENAME_3 ?></option>			                                          <option value="<? echo $_COLORUGRA_4 ?>"><? echo $_UGRADENAME_4 ?></option>
                                          <option value="<? echo $_COLORUGRA_5 ?>"><? echo $_UGRADENAME_5 ?></option>
                                          <option value="<? echo $_COLORUGRA_6 ?>"><? echo $_UGRADENAME_6 ?></option>
                                          </select>
									      </td>
											
										</tr>

									

										
										<tr>
											<td height="85" colspan="3">
											<p align="center">
											  <input type="submit" value="Dar Name Color" name="submit">
											</td>
										</tr>
										</table>
</form>