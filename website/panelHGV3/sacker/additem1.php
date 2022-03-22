<!-- Coding By Sacker - GodOfWar -->
<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }
if ($_SESSION['UGradeID'] == "254"){
    msgbox("Only Admin can enter here.","index.php");
    die();
}
if(isset($_POST['submit'])){
    $name = clean_sql($_POST['name']);
    $zitemid = clean_sql($_POST['zItemID']);
    $desc = clean_sql($_POST['desc']);
    $price = clean_sql($_POST['price']);
    $img = clean_sql($_POST['img']);
    $sex = clean_sql($_POST['sex']);
    $minlvl = clean_sql($_POST['minlvl']);
    $peso = clean_sql($_POST['peso']);
    $slot = clean_sql($_POST['slot']);
    $damage = clean_sql($_POST['damage']);
    $AP = clean_sql($_POST['AP']);
    $FR = clean_sql($_POST['FR']);
    $delay = clean_sql($_POST['delay']);
    $HP = clean_sql($_POST['HP']);
    $PR = clean_sql($_POST['PR']);
    $magazine = clean_sql($_POST['magazine']);
    $maxpeso = clean_sql($_POST['maxpeso']);
    $CR = clean_sql($_POST['CR']);
    $balasmax = clean_sql($_POST['balasmax']);
    $reloadtime = clean_sql($_POST['reloadtime']);
    $LR = clean_sql($_POST['LR']);
    $control = clean_sql($_POST['control']);
    $csid = clean_sql($_POST['zItemID']);
    mssql_query_logged("INSERT INTO [Item] ([ItemID], [Name], [Description], [ResSex], [ResLevel], [Weight], [Slot], [Damage], [AP], [FR], [Delay], [HP], [PR], [Magazine], [CR], [MaxBullet], [ReloadTime], [LR])VALUES('$zitemid', '$name', '$desc', NULL, $minlvl, 1, '$slot', $damage, $AP, $FR, $delay, $HP, $PR, $magazine, $CR, $balasmax, $reloadtime, $LR)");
    mssql_query_logged("INSERT INTO [CashShop] ([ItemID], [Name], [CSID], [Description], [CashPrice], [WebImgName], [NewItemOrder], [ResSex], [ResLevel], [Weight], [Opened], [RegDate], [RentType], [Slot], [Damage], [AP], [FR], [Delay], [HP], [PR], [Magazine], [MaxWeight], [CR], [MaxBullet], [ReloadTime], [LR], [Control])VALUES('$zitemid', '$name', '$csid', '$desc', $price, '$img', NULL, $sex, $minlvl, $peso, 1, GETDATE(), NULL, '$slot', $damage, $AP, $FR, $delay, $HP, $PR, $magazine, $maxpeso, $CR, $balasmax, $reloadtime, $LR, $control)");

    msgbox("Item added correctly","index.php?do=additem");
}else{

?>
<form method="POST" action="index.php?do=additem">
  <table border="1" style="border-collapse: collapse" width="454" height="100%">

										<tr>
											<td width="438" colspan="3">ADD ITEM TO ITEM SHOP
											  </td>
										</tr>

										<tr>
											<td width="438" align="right">
											ItemID (zitem.xml)</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="zItemID" size="20" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right" valign="top">
											Description</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<textarea rows="4" name="desc" cols="26"></textarea></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Image</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="img" size="34"></td>
										</tr>

										<tr>
											<td width="438">
											<p align="right">Name</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="name" size="20"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Slot</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<select size="1" name="slot">
											<option selected value="1">Melee Weapons</option>
											<option value="2">Ranged Weapons</option>
											<option value="3">Armor</option>
											<option value="4">Full Set</option>
											<option value="5">Special Item</option>
											</select></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Sex</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<select size="1" name="sex">
											<option selected value="2">Everyone</option>
											<option value="0">Man</option>
											<option value="1">Woman</option>
											</select></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Lv. Min</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="minlvl" size="20" value="1"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Weight</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="peso" size="20" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Price</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="price" size="20" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Damage</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="damage" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Delay</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="delay" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Magazine</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="magazine" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Reload Time</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="reloadtime" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Max Bullet</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="balasmax" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											HP</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="HP" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											AP</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="AP" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											 Max Weight</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="maxpeso" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											Control</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="control" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											FR</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="FR" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											PR</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="PR" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											CR</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="CR" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438" align="right">
											LR</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">
											<input type="text" name="LR" size="11" value="0"></td>
										</tr>

										<tr>
											<td width="438">&nbsp;
											</td>
											<td width="438">&nbsp;
											</td>
											<td width="438">&nbsp;
											</td>
										</tr>

										<tr>
											<td width="438" colspan="3">
											<input type="submit" value="Add Item" name="submit"></td>
										</tr>
										</table>
</form>
<?
}
?>
