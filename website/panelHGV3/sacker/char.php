<!-- Coding By Sacker - GodOfWar -->
<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }

include '../secure/config.php';
$query = mssql_query("SELECT * FROM Character order by AID asc");

?>
<style type="text/css">

.style28 {font-size: 15px}
.style29 {color: #FFFFFF; font-weight: bold; font-size: 15px; }

</style>
<table width="442" border="1">
  <tr >
    <th colspan="7" scope="row"><span class="style28">Players Characters </span></th>
  </tr>
  <tr>
    <th width="19" scope="row"><span class="style28"><strong>Nº</strong></span></th>
     <th width="19" scope="row"><span class="style28"><strong>AID</strong></span></th>
    <td width="61"><span class="style28"><strong>Name</strong></span></td>
    <td width="54"><span class="style28"><strong>Level</strong></span></td>
  </tr>
  <?
 for($i=0;$i < mssql_num_rows($query);)
{
$row = mssql_fetch_row($query);
$rank = $i+1;
  ?>
  <tr>
      <th scope="row"><span class="style28"><strong><?php echo "$rank";?></strong></span></th>
	<td><span class="style28"><?php echo "$row[1]";?></span></td>
    <td><span class="style28"><?php echo "$row[2]";?></span></td>
    <td><span class="style28"><?php echo "$row[3]";?></span></td>
  </tr>
  <?
  $i++;
  }
   ?>
</table>
</div>
</body>

</html>