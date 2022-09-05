<?php
	require "Header.php";
	
	if (!isset($_SESSION['userUID'])) {
		header("Location: Login.php");
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
	
	$ugid = $_SESSION['userGrade'];
	
	if (isset($_POST['pwdreset']))
	{
		if (empty($_POST['cp-password']) OR empty($_POST['cp-password1']))
		{
			Secures("<br><br><br><br><br><br><br><br> Please Fill In All The Blanks.");
		}
		
		$pw1 = $_POST['cp-password'];
		$pw2 = $_POST['cp-password1'];

		if($pw1 != $pw2)
		{
			Secures(" <br><br><br><br><br><br><br><br> Passwords Don't Match.");
		}
		
		$query3 = odbc_exec($connect, "UPDATE $logintable SET Password='" . $pw1 . "' WHERE UserID='" . $_SESSION['userUID'] . "'");
		Secures(" <br><br><br><br><br><br><br>Your password was changed successfully.<br><br>");
	}
	
	if ($ugid == "255" || $ugid == "254") {
		if (isset($_POST['cpbtn1'])) {
			$user1 = $_POST['user1'];
			$rank = $_POST['rank'];
			
			if (empty($user1)) {
				Secures("<br><br><br><br><br><br><br><br> Fill in UserID");
			}
			if ($rank == "") {
				Secures("<br><br><br><br><br><br><br><br> Choose rank to update");
			}
			
			$query1 = odbc_exec($connect, "SELECT AID FROM $accounttable WHERE UserID = '" . $user1 . "'");
			$count1 = num_rows($query1);

			if (!$count1 >= 1)
			{
				Secures("<br><br><br><br><br><br><br><br> UserID does NOT exist.");
			}
			
			odbc_exec($connect, "UPDATE $accounttable SET UGradeID='" . $rank . "' WHERE UserID='" . $user1 . "'");
			Secures(" <br><br><br><br><br><br><br>Rank was upgraded successfully<br><br>");
		}
		
		if (isset($_POST['cpbtn2'])) {
			$user2 = $_POST['user2'];
			$userpwd = $_POST['userpwd'];
			
			if (empty($user2) || empty($userpwd)) {
				Secures("<br><br><br><br><br><br><br><br> Fill in all the fields");
			}
			
			$query1 = odbc_exec($connect, "SELECT AID FROM $accounttable WHERE UserID = '" . $user2 . "'");
			$count1 = num_rows($query1);

			if (!$count1 >= 1)
			{
				Secures("<br><br><br><br><br><br><br><br> UserID does NOT exist.");
			}
			
			odbc_exec($connect, "UPDATE $logintable SET Password='" . $userpwd . "' WHERE UserID='" . $user2 . "'");
			Secures(" <br><br><br><br><br><br><br>Password was upgraded successfully<br><br>");
		}
		
		if (isset($_POST['cpbtn3'])) {
			$char1 = $_POST['char1'];
			$newchar1 = $_POST['newchar1'];
			
			if (empty($char1) || empty($newchar1)) {
				Secures("<br><br><br><br><br><br><br><br> Fill in all the fields");
			}
			
			$query1 = odbc_exec($connect, "SELECT * FROM $chartable WHERE Name = '" . $char1 . "'");
			$count1 = num_rows($query1);

			if (!$count1 >= 1)
			{
				Secures("<br><br><br><br><br><br><br><br> Character name does NOT exist.");
			}
			
			odbc_exec($connect, "UPDATE $chartable SET Name='" . $newchar1 . "' WHERE Name='" . $char1 . "'");
			Secures(" <br><br><br><br><br><br><br>Character name was updated successfully<br><br>");
		}
		
		if (isset($_POST['cpbtn4'])) {
			$char2 = $_POST['char2'];
			$charlvl = $_POST['charlvl'];
			
			if (empty($char2) || empty($charlvl)) {
				Secures("<br><br><br><br><br><br><br><br> Fill in all the fields");
			}
			if(!is_numeric($charlvl) || $charlvl < 0) {
				Secures("<br><br><br><br><br><br><br><br> Level must be a number (greater than 0)");
			}
			
			$query1 = odbc_exec($connect, "SELECT * FROM $chartable WHERE Name = '" . $char2 . "'");
			$count1 = num_rows($query1);

			if (!$count1 >= 1)
			{
				Secures("<br><br><br><br><br><br><br><br> Character name does NOT exist.");
			}
			
			odbc_exec($connect, "UPDATE $chartable SET Level=" . $charlvl . " WHERE Name='" . $char2 . "'");
			Secures(" <br><br><br><br><br><br><br>Character level was updated successfully<br><br>");
		}
		
		if (isset($_POST['cpbtn5'])) {
			$char3 = $_POST['char3'];
			$charexp = $_POST['charexp'];
			
			if (empty($char3) || empty($charexp)) {
				Secures("<br><br><br><br><br><br><br><br> Fill in all the fields");
			}
			if(!is_numeric($charexp) || $charexp < 0) {
				Secures("<br><br><br><br><br><br><br><br> Exp must be a number (greater than 0)");
			}
			
			$query1 = odbc_exec($connect, "SELECT * FROM $chartable WHERE Name = '" . $char3 . "'");
			$count1 = num_rows($query1);

			if (!$count1 >= 1)
			{
				Secures("<br><br><br><br><br><br><br><br> Character name does NOT exist.");
			}
			
			odbc_exec($connect, "UPDATE $chartable SET XP=" . $charexp . " WHERE Name='" . $char3 . "'");
			Secures(" <br><br><br><br><br><br><br>Character EXP was updated successfully<br><br>");
		}
		
		if (isset($_POST['cpbtn6'])) {
			$char4 = $_POST['char4'];
			$charbp = $_POST['charbp'];
			
			if (empty($char4) || empty($charbp)) {
				Secures("<br><br><br><br><br><br><br><br> Fill in all the fields");
			}
			if(!is_numeric($charbp) || $charbp < 0) {
				Secures("<br><br><br><br><br><br><br><br> Bounty must be a number (greater than 0)");
			}
			
			$query1 = odbc_exec($connect, "SELECT * FROM $chartable WHERE Name = '" . $char4 . "'");
			$count1 = num_rows($query1);

			if (!$count1 >= 1)
			{
				Secures("<br><br><br><br><br><br><br><br> Character name does NOT exist.");
			}
			
			odbc_exec($connect, "UPDATE $chartable SET BP=" . $charbp . " WHERE Name='" . $char4 . "'");
			Secures(" <br><br><br><br><br><br><br>Character bounty was updated successfully<br><br>");
		}
		
		if (isset($_POST['cpbtn7'])) {
			$char5 = $_POST['char5'];
			$itemid1 = $_POST['itemid1'];
			
			if (empty($char5) || empty($itemid1)) {
				Secures("<br><br><br><br><br><br><br><br> Fill in all the fields");
			}
			if(!is_numeric($itemid1) || $itemid1 < 0) {
				Secures("<br><br><br><br><br><br><br><br> ItemID must be a number (greater than 0)");
			}
			
			$query1 = odbc_exec($connect, "SELECT * FROM $chartable WHERE Name = '" . $char5 . "'");
			$count1 = num_rows($query1);

			if (!$count1 >= 1)
			{
				Secures("<br><br><br><br><br><br><br><br> Character name does NOT exist.");
			}
			
			if (!$row = odbc_fetch_array($query1)) {
				Secures("<br><br><br><br><br><br><br><br>Database error!");
			} else {
				$cid = $row['CID'];
				
				odbc_exec($connect, "INSERT INTO $citemtable (CID, ItemID, RegDate) VALUES ('" . $cid . "', '" . $itemid1 . "', GETDATE())");
				Secures(" <br><br><br><br><br><br><br>Item was sent successfully<br><br>");
			}
		}
		
		if (isset($_POST['cpbtn8'])) {
			$char6 = $_POST['char6'];
			$itemid2 = $_POST['itemid2'];
			
			if (empty($char6) || empty($itemid2)) {
				Secures("<br><br><br><br><br><br><br><br> Fill in all the fields");
			}
			if(!is_numeric($itemid2) || $itemid2 < 0) {
				Secures("<br><br><br><br><br><br><br><br> ItemID must be a number (greater than 0)");
			}
			
			$query1 = odbc_exec($connect, "SELECT * FROM $chartable WHERE Name = '" . $char6 . "'");
			$count1 = num_rows($query1);

			if (!$count1 >= 1)
			{
				Secures("<br><br><br><br><br><br><br><br> Character name does NOT exist.");
			}
			
			if (!$row = odbc_fetch_array($query1)) {
				Secures("<br><br><br><br><br><br><br><br>Database error!");
			} else {
				$cid = $row['CID'];
				
				$query2 = odbc_exec($connect, "SELECT * FROM $citemtable WHERE CID='" . $cid . "' AND ItemID = '" . $itemid2 . "'");
				$count2 = num_rows($query2);

				if (!$count2 >= 1)
				{
					Secures("<br><br><br><br><br><br><br><br> Item does not exist for this Character");
				}
				
				odbc_exec($connect, "DELETE FROM $citemtable WHERE CID = '" . $cid . "' AND ItemID = '" . $itemid2 . "'");
				Secures(" <br><br><br><br><br><br><br>Item was deleted successfully<br><br>");
			}
			
		}
		
		
	}
	
	echo '<b><h1>' . $servername . ': The Duel</h1></b>';
	echo '<div style="float: left; padding-left: 20px;">Welcome, <u>' . $_SESSION['userUID'] . '</u></div>
	<div class="linkie" style="float: right; padding-right: 20px;"><a href="Logout.php">Logout</a></div>';
	if ($ugid == "255" || $ugid == "254") {
		echo '<div class="linkie" style="float: right; padding-right: 20px;"><a href="Chars.php">Character List</a></div>';
		echo '<div class="linkie" style="float: right; padding-right: 20px;"><a href="Panel.php">Panel</a></div><br><br>';
	} else {
		echo '<br><br>';
	}

	if ($ugid == "255" || $ugid == "254") {
		
?>
<hr />
<table width="90%" class="intable">
<form action="<?=$_SERVER['PHP_SELF']?>" method="POST">
<h3>.: Admin CP :.</h3>
<br>
<tr>
<td><b>UserID</b></td>
<td><input type="text" name="user1" maxlength="30" class="txtbox"></td>
<td><b>Set Rank to</b></td>
<td>
<select name="rank" class="cpdroplist">
  <option value="">Select...</option>
  <option value="0">Normal</option>
  <option value="2">Jjang</option>
  <option value="253">Banned</option>
</select>
</td>
<td>
<center><input type="submit" value="Update" name="cpbtn1" class="cpbtn"></center>
</td>
</tr>
<tr>
<td><b>UserID</b></td>
<td><input type="text" name="user2" maxlength="30" class="txtbox">
</td>
<td><b>Set Password to</b></td>
<td>
<input type="text" name="userpwd" maxlength="30" class="txtbox">
</td>
<td>
<center><input type="submit" value="Update" name="cpbtn2" class="cpbtn"></center>
</td>
</tr>
<tr>
<td colspan="5"><center><hr /></center></td>
</tr>
<tr>
<td><b>Char Name</b></td>
<td><input type="text" name="char1" maxlength="30" class="txtbox"></td>
<td><b>Set New Name to</b></td>
<td>
<input type="text" name="newchar1" maxlength="30" class="txtbox"></td>
<td>
<center><input type="submit" value="Update" name="cpbtn3" class="cpbtn"></center>
</td>
</tr>
<tr>
<td><b>Char Name</b></td>
<td><input type="text" name="char2" maxlength="30" class="txtbox"></td>
<td><b>Set Level to</b></td>
<td>
<input type="text" name="charlvl" maxlength="30" class="txtbox"></td>
<td>
<center><input type="submit" value="Update" name="cpbtn4" class="cpbtn"></center>
</td>
</tr>
<tr>
<td><b>Char Name</b></td>
<td><input type="text" name="char3" maxlength="30" class="txtbox"></td>
<td><b>Set EXP to</b></td>
<td>
<input type="text" name="charexp" maxlength="30" class="txtbox"></td>
<td>
<center><input type="submit" value="Update" name="cpbtn5" class="cpbtn"></center>
</td>
</tr>
<tr>
<td><b>Char Name</b></td>
<td><input type="text" name="char4" maxlength="30" class="txtbox"></td>
<td><b>Set Bounty to</b></td>
<td>
<input type="text" name="charbp" maxlength="30" class="txtbox"></td>
<td>
<center><input type="submit" value="Update" name="cpbtn6" class="cpbtn"></center>
</td>
</tr>
<tr>
<td><b>Char Name</b></td>
<td><input type="text" name="char5" maxlength="30" class="txtbox"></td>
<td><b>Send this ItemID</b></td>
<td>
<input type="text" name="itemid1" maxlength="30" class="txtbox"></td>
<td>
<center><input type="submit" value="Send" name="cpbtn7" class="cpbtn"></center>
</td>
</tr>
<tr>
<td><b>Char Name</b></td>
<td width="25%"><input type="text" name="char6" maxlength="30" class="txtbox"></td>
<td><b>Delete this ItemID</b></td>
<td width="25%">
<input type="text" name="itemid2" maxlength="30" class="txtbox"></td>
<td>
<center><input type="submit" value="Delete" name="cpbtn8" class="cpbtn"></center>
</td>
</tr>
</form>
</table>
<?php
	}
?>
<hr />
<table width="350">
<form action="<?=$_SERVER['PHP_SELF']?>" method="POST">
<h3>.: User CP :.</h3>
<br>
<tr>
<td width="50%"><b>Password</b></td>
<td width="50%"><input type="password" name="cp-password" maxlength="30" class="txtbox"></td>
</tr>
<tr>
<td width="50%"><b>Confirm Password</b></td>
<td width="50%"><input type="password" name="cp-password1" maxlength="30" class="txtbox"></td>
</tr>
<tr>
<td colspan="2"><center><input type="submit" name="pwdreset" value="Change password" class="btn"></center></td>
</tr>
</form>
</table>
</div>

<?php
	require "Footer.php";
?>