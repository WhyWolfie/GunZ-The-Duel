<?php
$aid = anti_injection($_GET['aid']);
$useraid = mssql_query("SELECT * FROM Account WHERE AID='$aid'");
$userquer = mssql_fetch_assoc($useraid);
?>
	<!-- User Profile Start -->
	<div id="tbl_head">
	 <div class="tbl_title_pos">
	  <?php echo $userquer['UserID'].' '.$title['17']; ?>
	 </div>
	</div>
	<div id="tbl_body">
	 <div class="tbl_pos">
	    <!-- User Info Start -->
	    <table width="100%" style="text-align:center; position:relative; bottom:5px;">
		 <tr style="background-color:#101010;">
		  <td style="color:#993333;"><?php echo $profile['1']; ?></td><td style="color:#993333;"><?php echo $profile['2']; ?></td>
		  <td style="color:#993333;"><?php echo $profile['3']; ?></td><td style="color:#993333;"><?php echo $profile['4']; ?></td>
		 </tr>
		 <?php
		  $userprof = mssql_query("SELECT * FROM Account WHERE AID='$aid'");
		  if(mssql_num_rows($userprof)<>0){
		   while($profinf = mssql_fetch_assoc($userprof)){
		    echo '<tr style="height:18px;"><td>'.$profinf['Name'].'</td>';
		    echo '<td>'.$profinf['Age'].'</td>';
		    echo '<td>'.$profinf['Country'].'</td>';
		    echo '<td>'.$profinf['RegDate'].'</td></tr>';
		   }
		  }
		 ?>
		</table>
	    <!-- User Info End -->
	    <br /><br />
	    <!-- User Characters Start -->
		<div style="color:#00CC00;"><b><?php echo $profile['9']; ?></b></div><br />
	    <table width="100%" style="text-align:center; position:relative; bottom:5px;">
		 <tr style="background-color:#101010;">
		  <td style="color:#993333;"><?php echo $profile['8']; ?></td><td style="color:#993333;"><?php echo $profile['1']; ?></td>
		  <td style="color:#993333;"><?php echo $profile['5']; ?></td><td style="color:#993333;"><?php echo $profile['11']; ?></td>
		  <td style="color:#993333;"><?php echo $profile['6']; ?></td><td style="color:#993333;"><?php echo $profile['7']; ?></td>
		 </tr>
		 <?php
		  $sqlplayer = mssql_query("SELECT TOP 4* FROM Character WHERE AID='$aid' AND DeleteFlag='0' ORDER BY Level DESC");
		  if(mssql_num_rows($sqlplayer)<>0){
		  $count=1;
		   while($profchar = mssql_fetch_assoc($sqlplayer)){
		    echo '<tr style="height:18px;"><td>'.$count.'.</td>';
		    echo '<td>'.$profchar['Name'].'</td>';
		    echo '<td>'.$profchar['Level'].'</td>';
		    echo '<td>'.Sex($profchar['Sex']).'</td>';
		    echo '<td>'.$profchar['KillCount'].'</td>';
		    echo '<td>'.$profchar['DeathCount'].'</td></tr>';
			$count++;
		   }
		  }else{
		   echo '<td colspan="5"><p align="center">'.$profile['10'].'</td>';
		  }
		 ?>
		</table>
	    <!-- User Characters End -->
	 </div>
	</div>
	<div id="tbl_footer"></div><br /><br />
	<!-- User Profile End -->