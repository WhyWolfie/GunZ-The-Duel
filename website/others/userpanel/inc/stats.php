<div id="ststitle">My Characters :</div><p>
<div id="us">
<?php
$query = mssql_query("SELECT TOP 4* FROM Character WHERE AID = '".$_SESSION['AID']."' AND DeleteFlag = 0 ORDER BY Level DESC");
if ( mssql_num_rows($query) < 1 ){
echo '<font color="#ff0000">You dont have Characters yet.';
}else{

echo "<table border='0' style='border-collapse:collapse' width='700'><tr height='23' style='font-weight:bold;color:#00FF00;'>";
echo "<td>Name</td>";
echo "<td>Lvl</td>";
echo "<td>Experience</td>";
echo "<td>Sex</td>";
echo "<td>Kills</td>";
echo "<td>Deaths</td>";
echo "<td>Reg Date</td></tr>";
$i = 1;
while ( $i <= mssql_num_rows($query) ){
$chars = mssql_fetch_assoc($query);

echo '<tr style="font-size:11px;"><td width="70">'.Char($chars['CID']).'</td>';
echo '<td width="30">'.$chars['Level'].'</td>';
echo '<td width="80">'.$chars['XP'].'</td>';
echo '<td width="60">'.Sex($chars['Sex']).'</td>';
echo '<td width="40">'.$chars['KillCount'].'</td>';
echo '<td width="60">'.$chars['DeathCount'].'</td>';
echo '<td>'.$chars['RegDate'].'</td></tr>';

$i++;
}
echo '</table>';
}
?>
		
<div class="logged_dline"></div>

<font color="#00FF00"><b>My Clans :</b></font><p>
<?		
$query2 = mssql_query("SELECT * FROM Character WHERE AID = '".$_SESSION['AID']."' ORDER BY CharNum ASC");
if (mssql_num_rows($query2) >1){

echo "<table border='0' style='border-collapse: collapse' width='610'><tr height='23' style='font-weight:bold;color:#00FF00;'>";
echo "<td>Clan Name</td>";
echo "<td>Clan Leader</td>";
echo "<td>Wins</td>";
echo "<td>Losses</td>";
echo "<td>Draws</td></tr>";

while ($cha = mssql_fetch_assoc($query2)){

$clanq = mssql_query("SELECT * FROM ClanMember WHERE CID = '".$cha['CID']."'");
if (mssql_num_rows($clanq) != 0){
$clanq2 = mssql_fetch_assoc($clanq);
if($clanq2['Grade'] == 9){
{
$claninfoq = mssql_query("SELECT * FROM Clan WHERE CLID = '".$clanq2['CLID']."'");
$claninfo = mssql_fetch_assoc($claninfoq);

echo "<tr style='font-size:11px;'><td>".$claninfo['Name']."</td>";
echo "<td>".Char($cha['CID'])."</td>";
echo "<td>".$claninfo['Wins']."</td>";
echo "<td>".$claninfo['Losses']."</td>";
echo "<td>".$claninfo['Draws']."</td></tr>";
}
}else
if($clanq2['Grade'] == 1){
{
$claninfoq = mssql_query("SELECT * FROM Clan WHERE CLID = '".$clanq2['CLID']."'");
$claninfo = mssql_fetch_assoc($claninfoq);

echo "<tr style='font-size:11px;'><td>".$claninfo['Name']."</td>";
echo "<td>".Char($cha['CID'])."</td>";
echo "<td>".$claninfo['Wins']."</td>";
echo "<td>".$claninfo['Losses']."</td>";
echo "<td>".$claninfo['Draws']."</td></tr>";
}
}else
if($clanq2['Grade'] == 2){
{
$claninfoq = mssql_query("SELECT * FROM Clan WHERE CLID = '".$clanq2['CLID']."'");
$claninfo = mssql_fetch_assoc($claninfoq);

echo "<tr style='font-size:11px;'><td>".$claninfo['Name']."</td>";
echo "<td>".Char($cha['CID'])."</td>";
echo "<td>".$claninfo['Wins']."</td>";
echo "<td>".$claninfo['Losses']."</td>";
echo "<td>".$claninfo['Draws']."</td></tr>";
}
}
}
}
}
echo "</table>";
?>
</div>