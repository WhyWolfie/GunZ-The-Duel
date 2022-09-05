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

if (isset($_GET['do']) AND $_GET['do'] == "login")
{

	if (empty($_POST['log-username']) OR empty($_POST['log-password']))
	{
		Secures("<br><br><br><br><br><br><br><br> Please Fill In All The Blanks.");
	}

	$query1 = odbc_exec($connect, "SELECT * FROM $accounttable WHERE UserID = '" . $_POST['log-username'] . "'");
	$count1 = num_rows($query1);

	if (!$count1 >= 1)
	{
		Secures("<br><br><br><br><br><br><br><br> Username does NOT exist.");
	}
	
	if (!$acc_row = odbc_fetch_array($query1)) {
		Secures("<br><br><br><br><br><br><br><br>Database error!");
	}
	
	$pw1 = $_POST['log-password'];

	$query2 = odbc_exec($connect, "SELECT * FROM $logintable WHERE UserID = '" . $_POST['log-username'] . "'");
	$count2 = num_rows($query2);

	if (!$count2 >= 1)
	{
		Secures(" <br><br><br><br><br><br><br><br>Username does NOT exist.");
	}
	
	if (!$row = odbc_fetch_array($query2)) {
		Secures("<br><br><br><br><br><br><br><br>Database error!");
	} else {
		if ($pw1 !== $row['Password']) {
			Secures("<br><br><br><br><br><br><br><br>Incorrect password.");
		} else {
			session_start();
			$_SESSION['userUID'] = $row['UserID'];
			$_SESSION['userGrade'] = $acc_row['UGradeID'];
			header("Location: Panel.php");
			exit();
		}
	}
}
?>
<table width="350">
<form action="<?=$_SERVER['PHP_SELF'] . '?do=login'?>" method="POST">
<b><h1><?=$servername?>: The Duel</h1></b>
<h3>.: Login :.</h3>
<br>
<tr>
<td width="50%"><b>Username</b></td>
<td width="50%"><input type="text" class="txtbox" name="log-username" maxlength="30"></td>
</tr>
<tr>
<td width="50%"><b>Password</b></td>
<td width="50%"><input type="password" name="log-password" maxlength="30" class="txtbox"></td>
</tr>
<tr>
<td colspan="2"><center><input type="submit" value="Login" class="btn"></center></td>
</tr>
<tr>
<td colspan="2" class="trlink"><center>New member? <a href="Index.php">Register here</a></center></td>
</tr>
</form>
</table>
</div>

<?php
	require "Footer.php";
?>