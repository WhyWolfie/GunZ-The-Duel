 <?php if($act == "rankings"){ ?>
    <!-- Player Rankings Start -->
	<div id="tbl_head">
	 <div class="tbl_title_pos">
	  <?php echo $title['12']; ?>
	  <div class="ranks_link"><a href="index.php?act=clanrankings"><?php echo $clranks['5']; ?></a></div>
	 </div>
	</div>
	<div id="tbl_body">
	 <div class="tbl_pos">
	    <table width="100%" style="text-align:center; position:relative; bottom:5px;" class="rkslink">
		 <tr style="background-color:#101010;">
		  <td style="color:#993333;"><?php echo $prankings['1']; ?></td><td style="color:#993333;"><?php echo $prankings['2']; ?></td>
		  <td style="color:#993333;"><?php echo $prankings['3']; ?></td><td style="color:#993333;"><?php echo $prankings['4']; ?></td>
		  <td style="color:#993333;"><?php echo $prankings['5']; ?></td><td style="color:#993333;"><?php echo $prankings['6']; ?></td>
		 </tr>
		 <?php
         $limit = 25;

         $queryq = "SELECT COUNT(*) as num FROM Character";
         $total_pages = mssql_fetch_assoc(mssql_query($queryq));
         $total_pages = $total_pages['num'];
	
         $stages = 3;
         $page = anti_injection($_GET['page']);
         if($page){
          $start = ($page - 1) * $limit; 
         }else{
	      $start = 0;	
         }	 
		 
		  $sqlplayer = mssql_query("SELECT TOP $limit * FROM Character WHERE CID not in (SELECT TOP $start CID FROM Character ORDER BY XP DESC) AND DeleteFlag='0' ORDER BY Level DESC,XP DESC,KillCount DESC,DeathCount DESC");
		  if(mssql_num_rows($sqlplayer)<>0){
		  $count=1+$start;
		   while($char = mssql_fetch_assoc($sqlplayer)){
		    echo '<tr style="height:18px;"><td>'.$count.'.</td>';
		    echo '<td><a href="index.php?act=profile&amp;aid='.$char['AID'].'">'.Char($char['CID']).'</a></td>';
		    echo '<td>'.$char['Level'].'</td>';
		    echo '<td>'.$char['XP'].'</td>';
		    echo '<td>'.$char['KillCount'].'</td>';
		    echo '<td>'.$char['DeathCount'].'</td></tr>';
			$count++;
		   }
		  }else{
		   echo "<tr><td></td></tr>";
		  }
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
			$paginate.= "<a href='index.php?act=rankings&amp;page=$prev'>Prev</a>";
		}else{
			$paginate.= "<span class='disabled'>Prev</span>";	}
			
		// Pages	
        if ($lastpage < 7 + ($stages * 2)){	
	    for ($counter = 1; $counter <= $lastpage; $counter++){
	     if ($counter == $page){
	      $paginate.= "<span class='current'>$counter</span>";
	     }else{
	      $paginate.= "<a href='index.php?act=rankings&amp;page=$counter'>$counter</a>";}					
	     }
         }elseif($lastpage > 5 + ($stages * 2)){
        // Beginning only hide later pages
	    if($page < 1 + ($stages * 2)){
	    for ($counter = 1; $counter < 4 + ($stages * 2); $counter++){
	    if ($counter == $page){
		 $paginate.= "<span class='current'>$counter</span>";
	    }else{
		 $paginate.= "<a href='index.php?act=rankings&amp;page=$counter'>$counter</a>";}					
	    }
		$paginate.= "...";
		$paginate.= "<a href='index.php?act=rankings&amp;page=$LastPagem1'>$LastPagem1</a>";
		$paginate.= "<a href='index.php?act=rankings&amp;page=$lastpage'>$lastpage</a>";	
        // Middle hide some front and some back		
	    }elseif($lastpage - ($stages * 2) > $page && $page > ($stages * 2)){
	  	  $paginate.= "<a href='index.php?act=rankings&amp;page=1'>1</a>";
		  $paginate.= "<a href='index.php?act=rankings&amp;page=2'>2</a>";
		  $paginate.= "...";
        for ($counter = $page - $stages; $counter <= $page + $stages; $counter++){
	  	if ($counter == $page){
			$paginate.= "<span class='current'>$counter</span>";
		}else{
			$paginate.= "<a href='index.php?act=rankings&amp;page=$counter'>$counter</a>";}					
        }
			$paginate.= "...";
			$paginate.= "<a href='index.php?act=rankings&amp;page=$LastPagem1'>$LastPagem1</a>";
			$paginate.= "<a href='index.php?act=rankings&amp;page=$lastpage'>$lastpage</a>";		
	}else{
		$paginate.= "<a href='index.php?act=rankings&amp;page=1'>1</a>";
		$paginate.= "<a href='index.php?act=rankings&amp;page=2'>2</a>";
		$paginate.= "...";
    for ($counter = $lastpage - (2 + ($stages * 2)); $counter <= $lastpage; $counter++){
	if ($counter == $page){
		$paginate.= "<span class='current'>$counter</span>";
	}else{
		$paginate.= "<a href='index.php?act=rankings&amp;page=$counter'>$counter</a>";}					
	}
	}
    }			
	// Next
	if ($page < $counter - 1){ 
		$paginate.= "<a href='index.php?act=rankings&amp;page=$next'>next</a>";
	}else{
		$paginate.= "<span class='disabled'>next</span>";
	}	
	$paginate.= "</div>";
    }
    //Paginate End
    echo "<tr><td align='center' colspan='6' style='padding-top:10px;'>";
	?>
	<div class="legends">
	  <font color="<?php echo $admincol; ?>"><?php echo $staff['1']; ?></font> &bull;
	  <font color="<?php echo $fmodcol; ?>"><?php echo $staff['3']; ?></font> &bull;
	  <font color="<?php echo $gmcol; ?>"><?php echo $staff['4']; ?></font> &bull;
	  <font color="<?php echo $devcol; ?>"><?php echo $staff['5']; ?></font>
	</div>
	<?php
	echo "</td></tr><tr><td align='center' colspan='6' style='padding-top:10px;'>";
	  echo $paginate;
	echo "</td></tr>";
	?>
	</table>
	</div>
	</div>
	<div id="tbl_footer"></div>
    <!-- Player Rankings End -->
   <?php }else{ ?>
   <!-- Clan Rankings End -->
	<div id="tbl_head">
	 <div class="tbl_title_pos">
	  <?php echo $title['13']; ?>
	  <div class="ranks_link"><a href="index.php?act=rankings"><?php echo $plranks['5']; ?></a></div>
	 </div>
	</div>
	<div id="tbl_body">
	 <div class="tbl_pos">
	    <table width="100%" style="text-align:center; position:relative; bottom:5px;">
		 <tr style="background-color:#101010;">
		  <td style="color:#993333;"><?php echo $crankings['1']; ?></td><td style="color:#993333;"><?php echo $crankings['2']; ?></td>
		  <td style="color:#993333;"><?php echo $crankings['3']; ?></td><td style="color:#993333;"><?php echo $crankings['4']; ?></td>
		  <td style="color:#993333;"><?php echo $crankings['5']; ?></td><td style="color:#993333;"><?php echo $crankings['6']; ?></td>
		 </tr>
		 <?php
		  $sqlplayer = mssql_query("SELECT TOP 100* FROM Clan WHERE DeleteFlag='0' ORDER BY Point DESC,Wins DESC,Losses DESC,Draws DESC");
		  if(mssql_num_rows($sqlplayer)<>0){
		  $count=1;
		   while($char = mssql_fetch_assoc($sqlplayer)){
		    echo '<tr style="height:18px;"><td>'.$count.'.</td>';
		    echo '<td>'.$char['Name'].'</td>';
		    echo '<td>'.$char['Point'].'</td>';
		    echo '<td>'.$char['Wins'].'</td>';
		    echo '<td>'.$char['Losses'].'</td>';
		    echo '<td>'.$char['Draws'].'</td></tr>';
			$count++;
		   }
		  }else{
		   echo "<tr><td></td></tr>";
		  }
		 ?>
		</table>
	 </div>
	</div>
	<div id="tbl_footer"></div><br /><br />
   
   <!-- Clan Rankings End -->
   <?php } ?>