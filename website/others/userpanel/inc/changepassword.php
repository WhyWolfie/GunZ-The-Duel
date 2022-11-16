<div id="title">Mudar senha :</div><p />
<form action="index.php?page=changepassword" method='post'>
<table align="center">
 <tr><td><b>Senha atual :</b></td><td><input type="password" name="oldpassword" /></td></tr>
 <tr><td><b>Nova senha :</b></td><td><input type="password" name="newpassword" /></td></tr>
 <tr><td><b>Repetir nova senha :</b></td><td><input type="password" name="repeatnewpassword" /></td></tr>
 <tr><td></td><td><input type="submit" name="changepassword" value="Concluir" /></td></tr>
</table>
</form>
<?php
if ($_POST['changepassword']){
echo '<div class="errmessage">';
$oldpassword = sql($_POST['oldpassword']);
$newpassword = sql($_POST['newpassword']);
$repeatnewpassword = sql($_POST['repeatnewpassword']);

$select_pass = mssql_query("SELECT Password FROM Login WHERE UserID='".$_SESSION['UserID']."'");
$row_pass = mssql_fetch_assoc($select_pass);
$old_pass = $row_pass['Password'];

if($oldpassword&&$newpassword&&$repeatnewpassword){
  if($oldpassword==$old_pass){
    if($newpassword==$repeatnewpassword){
	
	  $change_pass = mssql_query("UPDATE Login SET Password='$newpassword' WHERE UserID='".$_SESSION['UserID']."'");
      $msg = "Password changed!"; alert($msg);
	  session_destroy();
      redirect("index.php");
	  
	}else{
     echo "New passwords doesnt match!";
	}
  }else{
    echo "Old password isnt correct!";
  }
}else{
   echo "Please fill all fields!";
}

}
echo '</div>';
?>