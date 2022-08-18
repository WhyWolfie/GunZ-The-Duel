<!-- Malee Weapons Start -->
<?php
 $buy = anti_injection($_GET['buy']);
 $gift = anti_injection($_GET['gift']);
 if($gift == ""){
 if($buy == ""){
?>
<table><tr><td>
<?php
$limit = 10;

$queryq = "SELECT COUNT(*) as num FROM ItemShop WHERE Category='malee'";
$total_pages = mssql_fetch_assoc(mssql_query($queryq));
$total_pages = $total_pages['num'];
	
$stages = 3;
$page = anti_injection($_GET['page']);
if($page){
  $start = ($page - 1) * $limit; 
}else{
 $start = 0;	
}	 

$res = mssql_query("SELECT TOP $limit * FROM ItemShop WHERE ID not in (SELECT TOP
                    $start ID FROM ItemShop ORDER BY ID DESC) AND Category='malee' ORDER BY ID DESC");
 while($item = mssql_fetch_assoc($res)){
  ?>
  <table border="0" style="float:left;"><tr><td height="100" valign="top">
<div class="itemshp">
 <div class="itemshp_pos">
  <?php if($item['Image'] == ""){ ?>
   <img src="images/noimage.png" title="<?php echo $item['Name']; ?>" border="0" width="86" height="68" alt="" />
   <?php }else{ ?>
   <img src="<?php echo $item['Image']; ?>" title="<?php echo $item['Name']; ?>" border="0" width="86" height="68" alt="" />
   <?php } ?>
 </div>
</div></td><td valign="top">
 <div class="item_info">
 <?php
  echo '<font color="#006699">'.$item['Name'].'</font><br />'.$itmshop['5'].': '.$item['Type'].'<br />';
  echo $itmshop['6'].': '.Sex($item['Sex']).'<br />'.$itmshop['7'].': '.$item['Price'].' '.$itmshop['8'].' <br />';
 
 if($_SESSION['user'] == ""){
 ?>
 <a href="" onclick="alert('<?php echo $itmshop['11']; ?>!');return false"><button class="itmshp_button"><?php echo $itmshop['9']; ?></button></a>
 <a href="" onclick="alert('<?php echo $itmshop['11']; ?>!');return false"><button class="itmshp_button"><?php echo $itmshop['10']; ?></button></a>
 <?php }else{ ?>
 <a href="index.php?act=itemshop&amp;do=malee&amp;buy=<?php echo $item['ItemID']; ?>"><button class="itmshp_button"><?php echo $itmshop['9']; ?></button></a>
 <a href="index.php?act=itemshop&amp;do=malee&amp;gift=<?php echo $item['ItemID']; ?>"><button class="itmshp_button"><?php echo $itmshop['10']; ?></button></a>
 <?php } ?>
 </div>
 </td></tr></table>
 <?php } ?>
</td></tr></table>

<?php

        //Paginate Start
        if ($page == 0){$page = 1;}
        $prev = $page - 1;	
        $next = $page + 1;							
        $lastpage = ceil($total_pages/$limit);		
        $LastPagem1 = $lastpage - 1;					
	
	    $paginate = '';
	    if($lastpage > 1){	
	     $paginate .= "<div class='paginate'>";
		// Previous
		if ($page > 1){
			$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$prev'>Prev</a>";
		}else{
			$paginate.= "<span class='disabled'>Prev</span>";	}
			
		// Pages	
        if ($lastpage < 7 + ($stages * 2)){	
	    for ($counter = 1; $counter <= $lastpage; $counter++){
	     if ($counter == $page){
	      $paginate.= "<span class='current'>$counter</span>";
	     }else{
	      $paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$counter'>$counter</a>";}					
	     }
         }elseif($lastpage > 5 + ($stages * 2)){
        // Beginning only hide later pages
	    if($page < 1 + ($stages * 2)){
	    for ($counter = 1; $counter < 4 + ($stages * 2); $counter++){
	    if ($counter == $page){
		 $paginate.= "<span class='current'>$counter</span>";
	    }else{
		 $paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$counter'>$counter</a>";}					
	    }
		$paginate.= "...";
		$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$LastPagem1'>$LastPagem1</a>";
		$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$lastpage'>$lastpage</a>";	
        // Middle hide some front and some back		
	    }elseif($lastpage - ($stages * 2) > $page && $page > ($stages * 2)){
	  	  $paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=1'>1</a>";
		  $paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=2'>2</a>";
		  $paginate.= "...";
        for ($counter = $page - $stages; $counter <= $page + $stages; $counter++){
	  	if ($counter == $page){
			$paginate.= "<span class='current'>$counter</span>";
		}else{
			$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$counter'>$counter</a>";}					
        }
			$paginate.= "...";
			$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$LastPagem1'>$LastPagem1</a>";
			$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$lastpage'>$lastpage</a>";		
	}else{
		$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=1'>1</a>";
		$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=2'>2</a>";
		$paginate.= "...";
    for ($counter = $lastpage - (2 + ($stages * 2)); $counter <= $lastpage; $counter++){
	if ($counter == $page){
		$paginate.= "<span class='current'>$counter</span>";
	}else{
		$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$counter'>$counter</a>";}					
	}
	}
    }			
	// Next
	if ($page < $counter - 1){ 
		$paginate.= "<a href='index.php?act=itemshop&do=malee&amp;page=$next'>next</a>";
	}else{
		$paginate.= "<span class='disabled'>next</span>";
	}
	$paginate.= "</div>";
	    echo $paginate;
    }
    //Paginate End


}else{
  $itemsql = mssql_query("SELECT * FROM ItemShop WHERE ItemID='$buy'");
  $itemres = mssql_fetch_assoc($itemsql);
?>
<table align="center">
<tr><td style="float:left;position:relative;left:105px;">
 <div class="itemshp">
  <div class="itemshp_pos">
  <?php if($itemres['Image'] == ""){ ?>
    <img src="images/noimage.png" title="<?php echo $itemres['Name']; ?>" border="0" width="86" height="68" alt="" />
    <?php }else{ ?>
    <img src="<?php echo $itemres['Image']; ?>" title="<?php echo $itemres['Name']; ?>" border="0" width="86" height="68" alt="" />
    <?php } ?>
  </div>
 </div>
</td></tr>
<tr>
 <td style="text-align:center; line-height:15px;">
  <?php
   echo '<font color="#006699"><b>'.$itemres['Name'].'</b></font><br />';
   echo '<font color="#00CC33">'.$itmshop['5'].' :</font> '.$itemres['Type'].'<br />';
   echo '<font color="#00CC33">'.$itmshop['12'].' :</font> '.$itemres['Level'].'<br />';
   echo '<font color="#00CC33">'.$itmshop['6'].' :</font> '.Sex($itemres['Sex']).'<br />';
   echo '<font color="#00CC33">'.$itmshop['7'].' :</font> '.$itemres['Price'].' '.$itmshop['8'];
  ?>
  
 </td></tr><tr><td>
  
 <table><tr>
   <td>
    <table width="150">
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['15']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['Damage']; ?></td></tr>
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['16']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['Delay']; ?></td></tr>
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['17']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['Magazine']; ?></td></tr>
	</table>
   </td>
   <td>
    <table width="150">
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['18']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['HP']; ?></td></tr>
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['19']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['AP']; ?></td></tr>
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['20']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['Weight']; ?></td></tr>
	</table>
   </td>
  </tr></table>

</td></tr><tr><td></td></tr><tr><td align="center">
  
  <form action="" method="post">
   <input type="submit" name="buy" value="<?php echo $itmshop['9']; ?>" onclick="return confirmBuy()" />
  </form>
 </td>
</tr>
</table>
<div class="tbl_errmes">
<?php
  if(isset($_POST['buy'])){
  CheckSession();
  $itemid = anti_injection($buy);
  $name = anti_injection($itemres['Name']);
  $item_price = anti_injection($itemres['Price']);
   $slchar = mssql_query("SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'");
   $slacc = mssql_fetch_assoc($slchar);
  if($itemid){
    $chcoins = $slacc['Coins'] - $item_price;
   if($chcoins < 0){
    echo '<br />'.$itmshop['13']."!";
   }else{
    $date = date("Y-m-d H:i:s");
    //$ins = mssql_query("INSERT INTO Item (ItemID,Name) VALUES('$itemid','$name')");
    $itemsres = mssql_query("INSERT INTO AccountItem (AID, ItemID, RentDate, cnt) VALUES('".$slacc['AID']."','$itemid','$date','1')");
    $updatecoins = mssql_query("UPDATE Account SET Coins='$chcoins' WHERE UserID='".$_SESSION['user']."'");
	
	echo $itmshop['14']."!";
   }
  }else{
   redirect("index.php?act=itemshop");
  }
 }
?>
</div>
<?php }
  }else{
  //Gift
  $itemsql = mssql_query("SELECT * FROM ItemShop WHERE ItemID='$gift'");
  $itemres = mssql_fetch_assoc($itemsql);
?>
<table align="center">
<tr><td style="float:left;position:relative;left:105px;">
 <div class="itemshp">
  <div class="itemshp_pos">
  <?php if($itemres['Image'] == ""){ ?>
    <img src="images/noimage.png" title="<?php echo $itemres['Name']; ?>" border="0" width="86" height="68" alt="" />
    <?php }else{ ?>
    <img src="<?php echo $itemres['Image']; ?>" title="<?php echo $itemres['Name']; ?>" border="0" width="86" height="68" alt="" />
    <?php } ?>
  </div>
 </div>
</td></tr>
<tr>
 <td style="text-align:center; line-height:15px;">
  <?php
   echo '<font color="#006699"><b>'.$itemres['Name'].'</b></font><br />';
   echo '<font color="#00CC33">'.$itmshop['5'].' :</font> '.$itemres['Type'].'<br />';
   echo '<font color="#00CC33">'.$itmshop['12'].' :</font> '.$itemres['Level'].'<br />';
   echo '<font color="#00CC33">'.$itmshop['6'].' :</font> '.Sex($itemres['Sex']).'<br />';
   echo '<font color="#00CC33">'.$itmshop['7'].' :</font> '.$itemres['Price'].' '.$itmshop['8'];
  ?>
  
 </td></tr><tr><td style="text-align:center; line-height:15px;">

 </td></tr><tr><td>
 <table><tr>
   <td>
    <table width="150">
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['15']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['Damage']; ?></td></tr>
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['16']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['Delay']; ?></td></tr>
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['17']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['Magazine']; ?></td></tr>
	</table>
   </td>
   <td>
    <table width="150">
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['18']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['HP']; ?></td></tr>
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['19']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['AP']; ?></td></tr>
	 <tr><td style="border: 1px dotted #707070;"><?php echo $itmshop['20']; ?></td><td align="center" style="border: 1px dotted #707070;"><?php echo $itemres['Weight']; ?></td></tr>
	</table>
   </td>
  </tr></table>

</td></tr><tr><td></td></tr><tr><td align="center">
  
  <form action="" method="post">
   <input type="text" name="charname" class="tbl_colbor" value="Character Name" onfocus="if(this.value=='Character Name')this.value='';" onblur="if(this.value=='')this.value='Character Name';" /><br />
   <input type="submit" name="gift" value="<?php echo $itmshop['10']; ?>" onclick="return confirmGift()" />
  </form>
 </td>
</tr>
</table>
<div class="tbl_errmes">
<?php
  if(isset($_POST['gift'])){
  CheckSession();
  $to = anti_injection($_POST['charname']);
  $itemid = anti_injection($gift);
  $name = anti_injection($itemres['Name']);
  $item_price = anti_injection($itemres['Price']);
  $sqlgetaid = mssql_query("SELECT * FROM Character WHERE Name='$to'");
   if(mssql_num_rows($sqlgetaid)<>0){
  $chraid = mssql_fetch_assoc($sqlgetaid);
   $slchar = mssql_query("SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'");
   $slacc = mssql_fetch_assoc($slchar);
  if($itemid&&$name){
    $chcoins = $slacc['Coins'] - $item_price;
   if($chcoins < 0){
    echo '<br />'.$itmshop['13']."!";
   }else{
    $date = date("Y-m-d H:i:s");
    //$ins = mssql_query("INSERT INTO Item (ItemID,Name) VALUES('$itemid','$name')");
    $itemsres = mssql_query("INSERT INTO AccountItem (AID, ItemID, RentDate, cnt) VALUES('".$chraid['AID']."','$itemid','$date','1')");
    $updatecoins = mssql_query("UPDATE Account SET Coins='$chcoins' WHERE UserID='".$_SESSION['user']."'");
	
	echo $itmshop['21']."!";
   }
  }else{
   redirect("index.php?act=itemshop");
  }
 }else{
   echo $itmshop['22'].'!';
  }
 }
?>
</div>
<?php } ?>
<!-- Malee Weapons End -->