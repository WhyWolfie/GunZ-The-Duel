
<?php
$query = mssql_query("SELECT * FROM Account order by DonatorCoins DESC");

?>
<style type="text/css">

.style28 {font-size: 15px}
.style29 {color: #FFFFFF; font-weight: bold; font-size: 15px; }
.style30 {color: #0C0 font-weight: bold; font-size: 15px; }

</style>
<table width="646" border="1">
  <tr >
    <th colspan="10" scope="row"><span class="style28">Account List</span></th>
  </tr>
  <tr>
    <th width="18" scope="row"><span class="style28"><strong>Nº</strong></span></th>
     <th width="28" scope="row"><span class="style28"><strong>AID</strong></span></th>
    <td width="57"><span class="style28"><strong>UserID</strong></span></td>
    <td width="68"><span class="style28"><strong>UGradeID</strong></span></td>
    <td width="61"><span class="style28"><strong>Coins</strong></span></td>
    <td width="56"><span class="style28"><strong>ECoins</strong></span></td>
    <td width="64"><span class="style29"><strong>DCoins</strong></span></td>

</tr>
  <?
 for($i=0;$i < mssql_num_rows($query);)
{
$row = mssql_fetch_row($query);
$rank = $i+1;
  ?>
  <tr>
      <th scope="row"><span class="style28"><strong><?php echo "$rank";?></strong></span></th>
	<td><span class="style28"><?php echo "$row[0]";?></span></td>
    <td><span class="style28"><?php echo "$row[1]";?></span></td>
    <td><span class="style28"><?php echo "$row[2]";?></span></td>
    <td><span class="style28"><?php echo "$row[23]";?></span></td>
    <td><span class="style28"><?php echo "$row[24]";?></span></td>
    <td><span class="style29"><?php echo "$row[25]";?></span></td>


</tr>





















  <?
  $i++;
  }
   ?>
   


</table>
</div>
</body>

</html>