<table width="100%" height="400">
<tr><td align="center"><div class="title">Login</div>
<div id="login_bg">
 <div id="login">
  <form action="index.php?do=login" method="post">
   <table>
    <tr><td>Login :</td><td><input type="text" name="username" class="user" /></td></tr>
    <tr><td>Senha :</td><td><input type="password" name="password" class="pass" /></td>
    <td><input type="submit" name="login" value="" class="button"></td></tr>
   </table>
  </form>
 </div>
</div>
</td></tr></table>

<?php
if (isset($_POST['login'])){
$username = sql($_POST['username']);
$password = sql($_POST['password']);

if($username&&$password){
$sql = mssql_query("SELECT * FROM Login WHERE UserID = '$username' AND Password = '$password'");
$data = mssql_fetch_assoc($sql);
if (mssql_num_rows($sql) == 1){

$_SESSION['AID'] =  $data['AID'];
$_SESSION['UserID'] = $username;
        
$query2 = mssql_query("SELECT * FROM Account WHERE AID = '".$data['AID']."'");
$get = mssql_fetch_assoc($query2);

$_SESSION['UGradeID'] = $get['UGradeID'];

redirect("index.php");
}else{
  echo '<div id="error">'."Username or password is incorrect!".'</div>';
}
}else{
echo '<div id="error">'."Please enter username and password!".'</div>';
}
}
?>