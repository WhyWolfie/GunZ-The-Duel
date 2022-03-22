
<html>
<head>
</head>

<body>
<form name="from1" method="post">
<table width="692" height="34" border="1">
  <tr>
    <th width="131" height="28" scope="col">Tipo de Shop:</th>
    <th width="235" scope="col"><select name="type"><option value="ShopDonator">ShopDonator</option><option value="ShopEvents">ShopEvents</option><option value="ShopItems">ShopItems</option></select></th>
    <th width="304" scope="col"><input type="submit" value="Ver Items" name="buscar"></th>
  </tr>
</table>
<table width="727" height="29" border="1">
<?php
		
if(isset($_POST['buscar'])){
	$type	 = $_POST['type'];

	
			$q = mssql_query("SELECT * From $type");
			
	if(mssql_num_rows($q) == 0){
		echo "No se encontro Items";
		}
	while($item = mssql_fetch_object($q)){
		$name=  $item->Name;
?>
  <tr>
    <th width="59" height="23" scope="col">Nombre:</th>
    <th width="287" scope="col"><?=$name?></th>
    <th width="43" scope="col">Level:</th>
    <th width="36" scope="col"><?=$item->Level?></th>
    <th width="47" scope="col">Precio:</th>
    <th width="71" scope="col"><?=$item->Price?></th>
    <th width="35" scope="col"><input type="hidden" value="<?=$item->zItemID?>" name="id"><input type="hidden" value="<?=$type?>" name="shop">-&gt;</th>
    <th width="97" scope="col"><input type="submit" name="delet" value="Eliminar Item"></th>
  </tr>
 <? 		} }
 
	 if(isset($_POST['delet'])){
	 $id = $_POST['id'];
	 $shop = $_POST['shop'];
	 mssql_query("DELETE From $shop WHERE zItemID='$id'");
	
	 mssql_query("DELETE From Item WHERE ItemID='$id'");
	msgbox("Item Eliminado  By Sacker.","index.php?do=quitaritem");
	}
?>
</table>
</form>
<p>&nbsp;</p>
</body>
</html>