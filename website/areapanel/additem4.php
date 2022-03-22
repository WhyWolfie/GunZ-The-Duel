<!-- Coding By Sacker - GodOfWar -->
<?
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }
?>
<?
if(isset($_POST['submit'])){
    $nombre = clean_sql($_POST['nombre']);
	$level = clean_sql($_POST['level']);
	$price = clean_sql($_POST['price']);
	$sex = clean_sql($_POST['sex']);
	$img = clean_sql($_POST['img']);
	$cabeza = clean_sql($_POST['cabeza']);
	$pecho = clean_sql($_POST['pecho']);
	$mano = clean_sql($_POST['mano']);
	$pierna = clean_sql($_POST['pierna']);
	$pies = clean_sql($_POST['pies']);	
    mssql_query_logged("INSERT INTO ShopSets ([Name], [Level], [Price], [Sex], [ImageURL], [HeadItemID], [ChestItemID], [HandItemID], [LegItemID], [FeetItemID])VALUES('$nombre', '$level', '$price', '$sex', '$img', '$cabeza', '$pecho', '$mano', '$pierna', '$pies')");
    	
	msgbox("Su Set Fue agregado con exito.","index.php?do=additem4");
}else{
?>
<style type="text/css">
<!--
.style1 {color: #FF0000}
body p {
	text-align: center;
}
-->
</style>
<body bgcolor="#323232">
<form method="POST" action="index.php?do=additem4">
<table border="1" style="border-collapse: collapse" width="585" height="100%">
<!-- Coding By Sacker - GodOfWar -->
										<tr>
											<td colspan="3">Agrega item's Set By SackerZ</td>
										</tr>

										

										<tr>
											<td width="114" align="right" valign="top">Nombre</td>
											<td width="11">&nbsp;
											</td>
											<td width="363"><input type="text" name="nombre" value="NAME SET" size="20"></td>
										</tr>

										<tr>
											<td width="114" height="26" align="right">
											Image</td>
											<td width="11">&nbsp;
									    </td>
											<td width="363"><p>&quot; images/shop/
                                            <input type="text" name="img" size="34" value="imagen.png">
											  </p></td>
										</tr>

										<tr>
											<td width="114">
											  <p align="right"></td>
											<td width="11">&nbsp;
											</td>
											<td width="363">&nbsp;</td>
										</tr>

										
											
										

										<tr>
											<td width="114" align="right">
											Sex</td>
											<td width="11">&nbsp;
											</td>
											<td width="363">
											<select size="1" name="sex">
											<option selected value="0">Hombre</option>
											<option value="1">Mujer</option>
											</select></td>
										</tr>

										<tr>
											<td width="114" align="right">
											Lv. Min</td>
											<td width="11">&nbsp;
											</td>
											<td width="363">
											<input type="text" name="level" size="20" value="1"></td>
										</tr>

										

										<tr>
											<td width="114" align="right">
											Precio</td>
											<td width="11">&nbsp;
											</td>
											<td width="363">
											<input type="text" name="price" size="20" value="0"></td>
										</tr>

										<tr>
											<td width="114" align="right">Cabeza ItemID</td>
											<td width="11">&nbsp;
											</td>
											<td width="363">
											<input type="text" name="cabeza" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="114" align="right">Pecho ItemID</td>
											<td width="11">&nbsp;
											</td>
											<td width="363">
											<input type="text" name="pecho" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="114" align="right">
											Mano ItemID</td>
											<td width="11">&nbsp;
											</td>
											<td width="363">
											<input type="text" name="mano" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="114" align="right">Pierna ItemID</td>
											<td width="11">&nbsp;
											</td>
											<td width="363">
											<input type="text" name="pierna" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="114" align="right">Pies ItemID</td>
											<td width="11">&nbsp;
											</td>
											<td width="363">
											<input type="text" name="pies" size="11" value="0"></td>
										</tr>
                                        
                                        

										<tr>
											
										</tr>

										<tr>
											<td width="114" height="24">&nbsp;
											</td>
											<td width="11">&nbsp;
											</td>
											<td width="363">&nbsp;</td>
	</tr>

										<tr>
										  <td colspan="3">
                                          <span style="text-align: center">
                                          <input type="submit" value="Agregar Item's Set" name="submit">
                                          </span>
                                          <td width="69" colspan="3">
      <p align="center"></td>
  </tr>
  
</table>
</form>
<?
}
?>

<!-- Coding By Sacker - GodOfWar -->