<!-- Coding By Sacker - GodOfWar -->
<?
if(isset($_POST['submit'])){
    $nombre = clean_sql($_POST['nombre']);
	$iditem = clean_sql($_POST['zitemid']);
	$sex = clean_sql($_POST['sex']);
	$img = clean_sql($_POST['img']);
	$level = clean_sql($_POST['level']);
	$peso = clean_sql($_POST['peso']);
	$price = clean_sql($_POST['price']);
	$delay = clean_sql($_POST['delay']);
	$damage = clean_sql($_POST['damage']);
	$magazine = clean_sql($_POST['magazine']);
	$reloadtime = clean_sql($_POST['reloadtime']);
	$maxbalas = clean_sql($_POST['MaxBullet']);
	$hp = clean_sql($_POST['hp']);
	$ap = clean_sql($_POST['ap']);
	$maxpeso = clean_sql($_POST['maxpeso']);
	$control = clean_sql($_POST['control']);
	$dura = clean_sql($_POST['duration']);
	$FR = clean_sql($_POST['FR']);
	$PR = clean_sql($_POST['PR']);
	$CR = clean_sql($_POST['CR']);
	$LR = clean_sql($_POST['LR']);
    
	mssql_query("INSERT INTO ShopEvents ([Name], [zItemID], [Sex], [ImageURL], [Level], [Weight], [Price], [Delay], [Damage], [Magazine], [ReloadTime], [MaxBullet], [HP], [AP], [MaxWeight], [Control], [FR], [PR], [CR], [LR], [Duration])VALUES('$nombre', '$iditem', '$sex', '$img', '$level', '$peso', '$price', '$delay', '$damage', '$magazine', '$reloadtime', '$maxbalas', '$hp', '$ap', '$maxpeso', '$control', '$FR', '$PR', '$CR', '$LR', '$dura')");
    msgbox("Su Item Event fue agregado con exito!!!!^^ By Sacker","index.php?do=additem2");
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
<form method="POST" action="index.php?do=additem2">
<table border="1" style="border-collapse: collapse" width="585" height="100%">
<!-- Coding By Sacker - GodOfWar -->
										<tr>
											<td colspan="3">Agrega Items Event By SackerZ</td>
										</tr>

										<tr>
											<td width="84" align="right">
											ItemID (zitem.xml)</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="zitemid" size="20" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right" valign="top">Nombre</td>
											<td width="14">&nbsp;
											</td>
											<td width="330"><input type="text" name="nombre" size="20"></td>
										</tr>

										<tr>
											<td width="84" height="26" align="right">
											Image</td>
											<td width="14">&nbsp;
									    </td>
											<td width="330">
											  <p>
										    &quot; images/shop/
                                            <input type="text" name="img" size="34" value="imagen.png">
											  </p></td>
										</tr>

										<tr>
											<td width="84">
											  <p align="right"></td>
											<td width="14">&nbsp;
											</td>
											<td width="330">&nbsp;</td>
										</tr>

										
											
										

										<tr>
											<td width="84" align="right">
											Sex</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<select size="1" name="sex">
											<option selected value="2">Todos</option>
											<option value="0">Man</option>
											<option value="1">Mujer</option>
											</select></td>
										</tr>

										<tr>
											<td width="84" align="right">
											Lv. Min</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="level" size="20" value="1"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											Peso</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="peso" size="20" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											Precio</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="price" size="20" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											Da&ntilde;o</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="damage" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											Delay</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="delay" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											Magazine</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="magazine" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											Reload Time</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="reloadtime" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											Max Balas</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="maxbalas" size="11" value="0"></td>
										</tr>
                                        
                                        <tr>
											<td width="84" align="right">
											Duration</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="duration" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											HP</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="hp" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											AP</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="AP" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											 Max Peso</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="maxpeso" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											Control</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="control" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											FR</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="FR" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											PR</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="PR" size="11" value="0"></td>
										</tr>

<!-- Coding By Sacker - GodOfWar -->
										<tr>
											<td width="84" align="right">
											CR</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="CR" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" align="right">
											LR</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">
											<input type="text" name="LR" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="84" height="24">&nbsp;
											</td>
											<td width="14">&nbsp;
											</td>
											<td width="330">&nbsp;</td>
	</tr>

										<tr>
										  <td colspan="3">
                                          <span style="text-align: center">
                                          <input type="submit" value="Agregar Item Event" name="submit">
                                          </span>
                                          <td width="129" colspan="3">
      <p align="center"></td>
  </tr>
  
</table>
</form>
<?
}
?>

<!-- Coding By Sacker - GodOfWar -->