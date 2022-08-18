	<!-- GM Panel Start -->
	<?php
	 if($_SESSION['UGradeID'] == $gmugid){
	 $do = anti_injection($_GET['do']);
	?>
	<div id="tbl_head">
	 <div class="tbl_title_pos">
	  <?php
	  if($do == ""){
	   echo $title['16'];
	  }else{
	   echo $title['16'].' - '.$do;
	  }
	  ?>
	 </div>
	</div>
	<div id="tbl_body">
	 <div class="tbl_pos">
	 <?php if($do == ""){ ?>
	  <div id="admin">
	   <ul>
	    <li><a href="index.php?act=gm&amp;do=characters"><?php echo $admingmp['72']; ?></a></li>
	    <li><a href="index.php?act=gm&amp;do=accounts"><?php echo $admingmp['73']; ?></a></li>
	    <li><a href="index.php?act=gm&amp;do=clans"><?php echo $admingmp['74']; ?></a></li>
	   </ul>
	  </div>
	 <?php }elseif($do == "characters"){ ?>
	 <!-- Change Character Name Start -->
	 <div class="adm_tit"><?php echo $admingmp['1']; ?></div>
      <form action="index.php?act=gm&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['2'].' :'; ?></td><td ><input type="text" name="oldname" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['3'].' :'; ?></td><td><input type="text" name="newname" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="changechname" value="<?php echo $admingmp['4']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	   <?php
	    if(isset($_POST['changechname'])){
		 $oldname = anti_injection($_POST['oldname']);
		 $newname = anti_injection($_POST['newname']);
		 $charsql = mssql_query("SELECT * FROM Character WHERE Name='$oldname'");
		  if($oldname&&$newname){
		   if(mssql_num_rows($charsql)<>0){
		    $chcrnm = mssql_query("UPDATE Character SET Name='$newname' WHERE Name='$oldname'");
			echo $admingmp['7'];
		   }else{
		     echo $admingmp['6'];
		   }
		  }else{
		    echo $admingmp['5'];
		  }
		}
	   ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Character Name End -->
	 <!-- Send Item Start -->
	 <div class="adm_tit"><?php echo $admingmp['63']; ?></div>
      <form action="index.php?act=gm&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td ><input type="text" name="userid" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['64'].' :'; ?></td><td><input type="text" name="itemid" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="senditem" value="<?php echo $admingmp['65']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	   <?php
       if(isset($_POST['senditem'])){
       $userid = anti_injection($_POST['userid']);
       $itemid = anti_injection($_POST['itemid']);
        $sql = mssql_query("SELECT Name FROM Character WHERE Name = '$userid'");
       if(!$userid OR !$itemid){
        echo $admingmp['68'];
      }elseif(strlen($itemid)>9){
       echo $admingmp['67'];
      }elseif(mssql_num_rows($sql)<>0){
       $sql = "SELECT CID FROM Character WHERE Name = '$userid'";
       $num = mssql_query($sql);
       $ad = mssql_fetch_assoc($num);
       $sql2 = mssql_query_z("INSERT INTO CharacterItem (CID, ItemID, RegDate) VALUES('".$ad['CID']."','$itemid',GETDATE())");
        echo $admingmp['66'];
      }else{
       echo $admingmp['6'];
      }
      }
	   ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Send Item End -->
	 <!-- Delete Item Start -->
	 <div class="adm_tit"><?php echo $admingmp['70']; ?></div>
      <form action="index.php?act=gm&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td ><input type="text" name="cname" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['64'].' :'; ?></td><td><input type="text" name="itemid" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="deleteitem" value="<?php echo $admingmp['69']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	   <?php
       if(isset($_POST['deleteitem'])){
       $name = anti_injection($_POST['cname']);
       $itemid = anti_injection($_POST['itemid']);
        $sql = mssql_query("SELECT Name FROM Character WHERE Name = '$name'");
       if(!$name OR !$itemid){
        echo $admingmp['68'];
      }elseif(strlen($itemid)>9){
       echo $admingmp['67'];
      }elseif(mssql_num_rows($sql)<>0){
       $sql = "SELECT CID FROM Character WHERE Name = '$name'";
       $num = mssql_query($sql);
       $ad = mssql_fetch_assoc($num); 
       $sql2 = mssql_query("DELETE FROM CharacterItem WHERE CID = '".$ad['CID']."' AND ItemID='$itemid'");
        echo $admingmp['71'];
      }else{
        echo $admingmp['6'];
      }
      }
	   ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Delete Item End -->
	 <!-- Change Character Level Start -->
	 <div class="adm_tit"><?php echo $admingmp['9']; ?></div>
      <form action="index.php?act=gm&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td ><input type="text" name="name" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['11'].' :'; ?></td><td><input type="text" name="level" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="changelevel" value="<?php echo $admingmp['4']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	   <?php
	    if(isset($_POST['changelevel'])){
		 $name = anti_injection($_POST['name']);
		 $level = anti_injection($_POST['level']);
		 $charsql = mssql_query("SELECT * FROM Character WHERE Name='$name'");
		  if($name&&$level){
		   if(mssql_num_rows($charsql)<>0){
		    $chcrnm = mssql_query("UPDATE Character SET Level='$level' WHERE Name='$name'");
			echo $admingmp['14'];
		   }else{
		     echo $admingmp['6'];
		   }
		  }else{
		    echo $admingmp['13'];
		  }
		}
	   ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Character Level End -->
	 <!-- Change Character EXP Start -->
	 <div class="adm_tit"><?php echo $admingmp['18']; ?></div>
      <form action="index.php?act=gm&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td ><input type="text" name="name" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['17'].' :'; ?></td><td><input type="text" name="exp" class="tbl_colbor" maxlength="9" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="changeexp" value="<?php echo $admingmp['4']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	   <?php
	    if(isset($_POST['changeexp'])){
		 $name = anti_injection($_POST['name']);
		 $exp = anti_injection($_POST['exp']);
		 $charsql = mssql_query("SELECT * FROM Character WHERE Name='$name'");
		  if($name&&$exp){
		   if(mssql_num_rows($charsql)<>0){
		    $chcrnm = mssql_query("UPDATE Character SET XP='$exp' WHERE Name='$name'");
			echo $admingmp['16'];
		   }else{
		     echo $admingmp['6'];
		   }
		  }else{
		    echo $admingmp['15'];
		  }
		}
	   ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Character EXP End -->
	 <!-- Change Character Sex Start -->
	 <div class="adm_tit"><?php echo $admingmp['19']; ?></div>
      <form action="index.php?act=gm&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td ><input type="text" name="name" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['20'].' :'; ?></td><td><select name="sex" class="tbl_colbor">
	   <option value="1">Female</option><option value="0">Male</option></select></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="changesex" value="<?php echo $admingmp['4']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	   <?php
	    if(isset($_POST['changesex'])){
		 $name = anti_injection($_POST['name']);
		 $sex = anti_injection($_POST['sex']);
		 $charsql = mssql_query("SELECT * FROM Character WHERE Name='$name'");
		  if($name){
		   if(mssql_num_rows($charsql)<>0){
		    $chcrnm = mssql_query("UPDATE Character SET Sex='$sex' WHERE Name='$name'");
			echo $admingmp['21'];
		   }else{
		     echo $admingmp['6'];
		   }
		  }else{
		    echo $admingmp['22'];
		  }
		}
	   ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Character Sex End -->
	 <!-- Reset Character Start -->
	 <div class="adm_tit"><?php echo $admingmp['29']; ?></div>
      <form action="index.php?act=gm&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td ><input type="text" name="name" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="resetchar" value="<?php echo $admingmp['28']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	   <?php
	    if(isset($_POST['resetchar'])){
		 $name = anti_injection($_POST['name']);
		 $charsql = mssql_query("SELECT * FROM Character WHERE Name='$name'");
		  if($name){
		   if(mssql_num_rows($charsql)<>0){
		    $chcrnm = mssql_query("UPDATE Character SET Level='1', XP='0', PlayTime='0', KillCount='0', DeathCount='0' WHERE Name='$name'");
			echo $admingmp['27'];
		   }else{
		     echo $admingmp['6'];
		   }
		  }else{
		    echo $admingmp['22'];
		  }
		}
	   ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Reset Character End -->
	 <?php }elseif($do == "accounts"){ ?>
	 <!-- Change Password Start -->
	 	 <div class="adm_tit"><?php echo $admingmp['30']; ?></div>
      <form action="index.php?act=gm&amp;do=accounts" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['31'].' :'; ?></td><td ><input type="text" name="userid" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['32'].' :'; ?></td><td ><input type="text" name="password" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="changepass" value="<?php echo $admingmp['4']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
      <?php
      if(isset($_POST['changepass'])){
      $userid = anti_injection($_POST['userid']);
      $password = anti_injection($_POST['password']);
       if($userid&&$password){
	   $sql = mssql_query("SELECT * FROM Account WHERE UserID = '$userid'");
	    if(mssql_num_rows($sql)<>0){
	    $sql2 = mssql_query("UPDATE Login SET Password = '$password' WHERE UserID = '$userid'");
         echo $admingmp['35'];
	   }else{
         echo $admingmp['34'];
	   }
	   }else{
         echo $admingmp['33'];
	   }
     }
      ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Password End -->
	 <!-- Change Rank Start -->
	 	 <div class="adm_tit"><?php echo $admingmp['37']; ?></div>
      <form action="index.php?act=gm&amp;do=accounts" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['31'].' :'; ?></td><td ><input type="text" name="userid" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['36'].' :'; ?></td><td align="right"><select name="rank" class="tbl_colbor">
	   <option value="<?php echo $membugid; ?>"><?php echo $staff['6']; ?></option>
	   <option value="<?php echo $bannedugid; ?>"><?php echo $staff['7']; ?></option>
	   </select></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="changerank" value="<?php echo $admingmp['4']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
      <?php
      if(isset($_POST['changerank'])){
      $userid = anti_injection($_POST['userid']);
      $rank = anti_injection($_POST['rank']);
       if($userid){
	   $sql = mssql_query("SELECT * FROM Account WHERE UserID = '$userid'");
	    if(mssql_num_rows($sql)<>0){
	    $sql2 = mssql_query("UPDATE Account SET UGradeID = '$rank' WHERE UserID = '$userid'");
         echo $admingmp['38'];
	   }else{
         echo $admingmp['34'];
	   }
	   }else{
         echo $admingmp['39'];
	   }
     }
      ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Rank End -->
	 <?php }elseif($do == "clans"){ ?>
	 <!-- Create Clan Start -->
	 	 <div class="adm_tit"><?php echo $admingmp['40']; ?></div>
      <form action="index.php?act=gm&amp;do=clans" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['41'].' :'; ?></td><td ><input type="text" name="mname" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['42'].' :'; ?></td><td ><input type="text" name="clanname" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="createclan" value="<?php echo $admingmp['43']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
      <?php
     if(isset($_POST['createclan'])){
      $master = anti_injection($_POST['mname']);
      $clanname = anti_injection($_POST['clanname']);
       $mastsql = mssql_query("SELECT * FROM Character WHERE Name='$master'");
       $clanssql = mssql_query("SELECT * FROM Clan WHERE Name='$clanname'");
       if($clanname&&$master){
       if(mssql_num_rows($mastsql)<>0){
       if(mssql_num_rows($clanssql)!= 1){
        $selmastercid = mssql_query("SELECT CID FROM Character WHERE Name='$master'");
        $mcid = mssql_fetch_assoc($selmastercid);
         $date = date("m.d.Y H:i:s");
         $ccsql = mssql_query("INSERT INTO Clan (Name,Exp,Level,Point,MasterCID,Wins,RegDate,Losses,Draws)
	     VALUES('$clanname','0','1','1000','".$mcid['CID']."','0','$date','0','0')");
        $selclid = mssql_query("SELECT CLID FROM Clan WHERE Name='$clanname'");
	    $cclid = mssql_fetch_assoc($selclid);
	    $insertcm = mssql_query_z("INSERT INTO ClanMember (CLID,CID,Grade,RegDate) VALUES('".$cclid['CLID']."','".$mcid['CID']."','1','$date')");
	     echo $admingmp['47'];
      }else{
	    echo $admingmp['46'];
      }
      }else{
	    echo $admingmp['45'];
      }
      }else{
	    echo $admingmp['44'];
      }
     }
     ?>  
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Create Clan End -->
	 <!-- Delete Clan Start -->
	 	 <div class="adm_tit"><?php echo $admingmp['48']; ?></div>
      <form action="index.php?act=gm&amp;do=clans" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['42'].' :'; ?></td><td ><input type="text" name="clanname" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="deleteclan" value="<?php echo $admingmp['49']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
      <?php
      if(isset($_POST['deleteclan'])){
       $clanname = anti_injection($_POST['clanname']);
       $clansql = mssql_query("SELECT * FROM Clan WHERE Name='$clanname'");
      if($clanname){
      if(mssql_num_rows($clansql)<>0){
        $selclid = mssql_query("SELECT CLID FROM Clan WHERE Name='$clanname'");
        $clid = mssql_fetch_assoc($selclid);
         $delclanmembers = mssql_query("DELETE FROM ClanMember WHERE CLID='".$clid['CLID']."'");
         $delclan = mssql_query("UPDATE Clan SET Name = NULL, DeleteFlag = 1, DeleteName='$clanname' WHERE CLID='".$clid['CLID']."'");
	      echo $admingmp['52'];
     }else{
	   echo $admingmp['51'];
     }
     }else{
	   echo $admingmp['50'];
     }
     }
     ?>  
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Delete Clan End -->
	 <?php } ?>
	 </div>
	</div>
	<div id="tbl_footer"></div><br /><br />
	<?php
	}else{
	  redirect("index.php");
	}
	?>
	<!-- GM Panel End -->