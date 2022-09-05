<?php
	require "Header.php";
	
	if (!isset($_SESSION['userUID'])) {
		header("Location: Login.php");
		exit();
	}
	
	if (isset($_SESSION['userGrade'])) {
		if ($_SESSION['userGrade'] !== "255" && $_SESSION['userGrade'] !== "254") {
			header("Location: Login.php");
			exit();
		}
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
	
	
	echo '<b><h1>' . $servername . ': The Duel</h1></b>';
	echo '<div style="float: left; padding-left: 20px;">Welcome, <u>' . $_SESSION['userUID'] . '</u></div>
	<div class="linkie" style="float: right; padding-right: 20px;"><a href="Logout.php">Logout</a></div>';
	
	echo '<div class="linkie" style="float: right; padding-right: 20px;"><a href="Chars.php">Character List</a></div>';
	echo '<div class="linkie" style="float: right; padding-right: 20px;"><a href="Panel.php">Panel</a></div><br><br>';

	$query = odbc_exec($connect, "SELECT * FROM $chartable WHERE Name !='' ORDER BY CID ASC");
		
?>
<hr />


<table width="90%" border="1">
 <tr>
  <th colspan="8" scope="row"><span class="style28">Character List</span></th>
 </tr>
 <tr>
	<th width="19" scope="row"><span class="style28"><strong>CID</strong></span></th>
    <th width="19" scope="row"><span class="style28"><strong>AID</strong></span></th>
    <td width="61"><span class="style28"><strong>Name</strong></span></td>
    <td width="54"><span class="style28"><strong>Level</strong></span></td>
    <td width="61"><span class="style28"><strong>XP</strong></span></td>
</tr>
<?php
	for($i = 0; $i < num_rows($query); ) {
		$row = odbc_fetch_array($query);
		$rank = $i+1;
?>
 <tr>
    <th scope="row"><span class="style28"><strong><?php echo $rank;?></strong></span></th>
    <td><span class="style28"><?php echo $row['AID'];?></span></td>
    <td><span class="style28"><?php echo $row['Name'];?></span></td>
    <td><span class="style28"><?php echo $row['Level'];?></span></td>
    <td><span class="style29"><?php echo $row['XP'];?></span></td>

 </tr>
<?php
	$i++;
  }
?>
</table>

</div>

<?php
	require "Footer.php";
?>