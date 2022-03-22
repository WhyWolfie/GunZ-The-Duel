<?
if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }
include '../secure/config.php';
$query = mssql_query("SELECT * FROM Login order by AID asc");

?>
<style type="text/css">

.style28 {font-size: 15px}
.style29 {color: #FFFFFF; font-weight: bold; font-size: 15px; }

</style>
<table width="708" border="1">
  <tr >
    <th colspan="8" scope="row"><span class="style28">Account Login List </span></th>
  </tr>
  <tr>
    <th width="51" scope="row"><span class="style28"><strong>Nº</strong></span></th>
     <th width="52" scope="row"><span class="style28"><strong>AID</strong></span></th>
    <td width="154"><span class="style28"><strong>UserID</strong></span></td>
    <td width="219"><span class="style28"><strong>Last Conection</strong></span></td>
    <td width="198"><span class="style28"><strong>Last IP </strong></span></td>
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
    <td><span class="style28"><?php echo "$row[0]";?></span></td>
    <td><span class="style28"><?php echo "$row[3]";?></span></td>
    <td><span class="style28"><?php echo "$row[4]";?></span></td>
  </tr>
  <?
  $i++;
  }
   ?>
</table>
</div>
</body>

</html>