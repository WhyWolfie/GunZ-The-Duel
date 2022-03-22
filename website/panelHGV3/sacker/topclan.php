<?php
$query = mssql_query("SELECT * FROM Clan  WHERE (DeleteFlag != 1) Order by CLID Desc");
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
     <th width="28" scope="row"><span class="style28"><strong>CLID</strong></span></th>
    <td width="57"><span class="style28"><strong>Name</strong></span></td>
    <td width="68"><span class="style28"><strong>Points</strong></span></td>
    <td width="61"><span class="style28"><strong>MasterCID</strong></span></td>
    <td width="56"><span class="style28"><strong>Wins</strong></span></td>
    <td width="64"><span class="style28"><strong>Losser</strong></span></td>

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
    <td><span class="style28"><?php echo "$row[4]";?></span></td>
    <td><span class="style28"><?php echo "$row[5]";?></span></td>
    <td><span class="style28"><?php echo "$row[6]";?></span></td>
    <td><span class="style28"><?php echo "$row[13]";?></span></td>


</tr>
  <?
  $i++;
  }   ?>
   
</table>
</div>
</body>
