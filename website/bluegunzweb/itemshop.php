	<!-- Item Shop Start -->
    <script type="text/javascript">
    function confirmBuy(){
      var agree = confirm("<?php echo $itmshop['23']; ?>");
       if(agree){
       return true ;
     }else {
      return false ;
     }
    }
    function confirmGift(){
      var agree = confirm("<?php echo $itmshop['24']; ?>");
       if(agree){
       return true ;
     }else {
      return false ;
     }
    }
     </script>
	<?php
	 $do = anti_injection($_GET['do']);
	?>
	<div id="tbl_head">
	 <div class="tbl_title_pos">
	  <?php
	  if($do == ""){
       echo $title['20'];
	  }else{
	   echo $title['20'].' - '.$do;
	  }
	  ?>
	 </div>
	</div>
	<div id="tbl_body">
	 <div class="tbl_pos">
	<div id="items_nav">
	 <ul>
      <li><a href="index.php?act=itemshop&amp;do=ranged"><?php echo $itmshop['1']; ?></a></li>
      <li><a href="index.php?act=itemshop&amp;do=malee"><?php echo $itmshop['2']; ?></a></li>
      <li><a href="index.php?act=itemshop&amp;do=armor"><?php echo $itmshop['3']; ?></a></li>
      <li><a href="index.php?act=itemshop&amp;do=sets"><?php echo $itmshop['4']; ?></a></li>
	 </ul>
	</div><br /><br /><br />
    <?php
     if($do == "ranged"){
	  Title("$gunz_name &bull; ".$title['20'].' - '.$itmshop['1']."");
      include("itemshop/ranged.php");  
     }elseif($do == "malee"){
	  Title("$gunz_name &bull; ".$title['20'].' - '.$itmshop['2']."");
      include("itemshop/malee.php"); 
	 }elseif($do == "armor"){
	  Title("$gunz_name &bull; ".$title['20'].' - '.$itmshop['3']."");
      include("itemshop/armor.php"); 
	 }elseif($do == "sets"){
	  Title("$gunz_name &bull; ".$title['20'].' - '.$itmshop['4']."");
      include("itemshop/sets.php"); 
	 }
    ?>
	 </div>
	</div>
	<div id="tbl_footer"></div><br /><br />
	<!-- Item Shop End -->