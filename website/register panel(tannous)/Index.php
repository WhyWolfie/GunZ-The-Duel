<?php
	require "Header.php";
	
	if (isset($_SESSION['userUID'])) {
		header("Location: Panel.php");
		exit();
	}
?>
<div class="etsov">
<center>
<?php
$ip = $_SERVER['REMOTE_ADDR'];
$query1 = odbc_exec($connect,"SELECT AID FROM $logintable WHERE LastIP = '$ip'");

$i=1;
while (odbc_fetch_row($query1, $i)){
	$aid = odbc_result($query1, 'AID');

	$query2 = odbc_exec($connect,"SELECT UGradeID FROM $accounttable WHERE AID = '$aid'");
	odbc_fetch_row($query2);
	$ugradeid = odbc_result($query2, 1);

	if ($ugradeid == "253")
	{
		Secures(" <br><br><br><br><br><br><br><br> You Are Banned...");
	}

	$i++;
}

if (isset($_GET['do']) AND $_GET['do'] == "register")
{

	if (!is_numeric($_POST['age']) OR !checkemail($_POST['email']) OR empty($_POST['username']) OR empty($_POST['password']) OR empty($_POST['email']) OR empty($_POST['name']) OR empty($_POST['age']))
	{
		Secures("<br><br><br><br><br><br><br><br> Please Fill In All The Blanks.");
	}

	$query1 = odbc_exec($connect, "SELECT AID FROM $accounttable WHERE UserID = '" . $_POST['username'] . "'");
	$count1 = num_rows($query1);

	if ($count1 >= 1)
	{
		Secures("<br><br><br><br><br><br><br><br> Username is Already Taken.");
	}

	$pw1 = $_POST['password'];
	$pw2 = $_POST['password1'];

	if($pw1 != $pw2)
	{
		Secures(" <br><br><br><br><br><br><br><br> Passwords Don't Match.");
	}

	$query2 = odbc_exec($connect, "SELECT AID FROM $accounttable WHERE Email = '" . $_POST['email'] . "'");
	$count2 = num_rows($query2);

	if ($count2 >= 1)
	{
		Secures(" <br><br><br><br><br><br><br><br> E-mail Address is Already In Use.");
	}

	$query3 = odbc_exec($connect, "INSERT INTO $accounttable (UserID, UGradeID, PGradeID, RegDate, Email, Age, Name) VALUES ('".$_POST['username']."', '0', '0', '6/9/2020 0:00:00', '".$_POST['email']."', '".$_POST['age']."', '".$_POST['name']."')");

	$query4 = odbc_exec($connect, "SELECT AID FROM $accounttable WHERE UserID = '" . $_POST['username'] . "'");
	odbc_fetch_row($query4);
	$aid = odbc_result($query4, 1);

	if (!$aid)
	{
		Secures("<br><br><br><br><br><br><br><br> Register Failed, Please Contact Us For More Info.");
	}

	odbc_exec($connect, "INSERT INTO $logintable (UserID, AID, Password) VALUES ('".$_POST['username']."', '$aid', '".$_POST['password']."')");

	Secures(" <br><br><br><br><br><br><br>You Are Registered Successfully.<br><br>
	<table width='350'>
	<tr>
	<td width='50%'><b>Username</b></td>
	<td width='50%'><b>$_POST[username]</b></td>
	</tr>
	<tr>
	<td width='50%'><b>Password</b></td>
	<td width='50%'><b>$_POST[password]</b></td>
	</tr>
	</table><br><br>
	Enjoy Your Time At $servername!");
}
?>
<table width="350">
<form action="<?=$_SERVER['PHP_SELF'] . '?do=register'?>" method="POST">
<b><h1><?=$servername?>: The Duel</h1></b>
<h3>.: Registration :.</h3>
<br>
<tr>
<td width="50%"><b>Username</b></td>
<td width="50%"><input type="text" class="txtbox" name="username" maxlength="30"></td>
</tr>
<tr>
<td width="50%"><b>Password</b></td>
<td width="50%"><input type="password" name="password" maxlength="30" class="txtbox"></td>
</tr>
<tr>
<td width="50%"><b>Confirm Password</b></td>
<td width="50%"><input type="password" name="password1" maxlength="30" class="txtbox"></td>
</tr>
<tr>
<td width="50%"><b>E-mail Address</b></td>
<td width="50%"><input type="text" name="email" maxlength="40" class="txtbox"></td>
</tr>
<tr>
<td width="50%"><b>Name</b></td>
<td width="50%"><input type="text" name="name" maxlength="30" class="txtbox"></td>
</tr>
<tr>
<td width="50%"><b>Age</b></td>
<td width="50%"><input type="text" name="age" maxlength="10" class="txtbox"></td>
</tr>
<tr>
<td colspan="2"><center><input type="submit" value="Register" class="btn"></center></td>
</tr>
<tr>
<td colspan="2" class="trlink"><center>Have an account? <a href="Login.php">Login here</a></center></td>
</tr>
</form>
</table>
</div>

<?php
	require "Footer.php";
?>