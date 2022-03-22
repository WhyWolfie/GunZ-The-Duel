<?
if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }
if(isset($_POST['submit'])){
    $eliminar = clean_sql($_POST['eliminar']);
    mssql_query("DELETE FROM IndexContent WHERE ICID = '$eliminar'");
    msgbox("Noticia eliminada!  By Sacker.","index.php?do=enews");
}else{
?>
<style type="text/css">
<!--
.style1 {color: #FF0000}
.sacker {
	color: #F00;
	font-weight: bold;
}
.sacker {
	text-align: center;
}

-->
</style>
<body bgcolor="#323232">
<form method="POST" action="index.php?do=enews">
<table width="454" height="100%" border="1" align="center" style="border-collapse: collapse">
  <tr>
    <td width="432" colspan="3">ELIMINAR NOTICIAS  </td>
</tr>
<tr>
  <td width="432" colspan="3">    <table width="375" border="1" align="center">
        <tr>
          <td width="116">&nbsp;</td>
          <td width="243">&nbsp;</td>
        </tr>
        <tr>
          <td class="sacker">ICID:</td>
          <td><input type="text" name="eliminar" size="40"></td>
  </tr>
        <tr>
          <td>&nbsp;</td>
          <td><input type="submit" value="ELIMINAR" name="submit"></td>
        </tr></form>

  
  <?
$query = mssql_query("SELECT * FROM IndexContent order by ICID asc");
?>
<table width="442" border="1" align="center">
  <tr >
    <th colspan="10" scope="row"><span class="style28">Lista de Noticias</span></th>
  </tr>
  <tr>
    <th width="41" scope="row"><span class="style28"><strong>Nro</strong></span></th>
     <th width="57" bgcolor="#00FF00" scope="row"><span class="sacker"><strong>ICID</strong></span></th>
    <td width="52"><span class="style28"><strong>Tipo</strong></span></td>
    <td width="264"><span class="style28"><strong>Titulo</strong></span>
    </td>
    <td width="264"><span class="style28"><strong>Usuario</strong></span>
    </td>

  <?
 for($i=0;$i < mssql_num_rows($query);)
{
$row = mssql_fetch_row($query);
$rank = $i+1;
  ?>
  <tr>
      <th height="40" scope="row"><span class="style28"><strong><?php echo "$rank";?></strong></span></th>
	<td bgcolor="#00FF00" class="sacker"><?php echo "$row[1]";?></td>
    <td><span class="style28"><?php echo "$row[0]";?></span></td>
    <td><span class="style28"><?php echo "$row[2]";?></span></td>
     <td><span class="style28"><?php echo "$row[3]";?></span></td>
    

</tr>
  <?
  $i++;
  }
   ?>
</table>

<style type="text/css">

.style28 {font-size: 15px}
.style29 {color: #FFFFFF; font-weight: bold; font-size: 15px; }

</style>

</div>

</body>
</html>
</table>
</form>

<?
}
?>