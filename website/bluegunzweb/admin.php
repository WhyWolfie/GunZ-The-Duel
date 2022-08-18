	<!-- AdminPanel Start -->
	<?php
	 if($_SESSION['UGradeID'] == $adminugid){
	 $do = anti_injection($_GET['do']);
	?>
	<div id="tbl_head">
	 <div class="tbl_title_pos">
	  <?php
	  if($do == ""){
	   echo $title['15'];
	  }else{
	   echo $title['15'].' - '.$do;
	  }
	  ?>
	 </div>
	</div>
	<div id="tbl_body">
	 <div class="tbl_pos">
	 <?php if($do == ""){ ?>
	  <div id="admin">
	   <ul>
	    <li><a href="index.php?act=admin&amp;do=characters"><?php echo $admingmp['72']; ?></a></li>
	    <li><a href="index.php?act=admin&amp;do=accounts"><?php echo $admingmp['73']; ?></a></li>
	    <li><a href="index.php?act=admin&amp;do=clans"><?php echo $admingmp['74']; ?></a></li>
	    <li><a href="index.php?act=admin&amp;do=givecoins"><?php echo $admingmp['75']; ?></a></li>
	    <li><a href="index.php?act=admin&amp;do=additem"><?php echo $admingmp['76']; ?></a></li>
	   </ul>
	  </div>
	 <?php }elseif($do == "characters"){ ?>
	 <!-- Change Character Name Start -->
	 <div class="adm_tit"><?php echo $admingmp['1']; ?></div>
      <form action="index.php?act=admin&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['2'].' :'; ?></td><td><input type="text" name="oldname" class="tbl_colbor" /></td></tr>
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
      <form action="index.php?act=admin&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td><input type="text" name="userid" class="tbl_colbor" /></td></tr>
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
      <form action="index.php?act=admin&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td><input type="text" name="cname" class="tbl_colbor" /></td></tr>
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
      <form action="index.php?act=admin&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td><input type="text" name="name" class="tbl_colbor" /></td></tr>
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
      <form action="index.php?act=admin&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td><input type="text" name="name" class="tbl_colbor" /></td></tr>
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
      <form action="index.php?act=admin&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td><input type="text" name="name" class="tbl_colbor" /></td></tr>
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
	 <!-- Change Character Kill/DeathCount Start -->
	 <div class="adm_tit"><?php echo $admingmp['24']; ?></div>
      <form action="index.php?act=admin&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td><input type="text" name="name" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['25'].' :'; ?></td><td><input type="text" name="kills" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['26'].' :'; ?></td><td><input type="text" name="deaths" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="changecharkd" value="<?php echo $admingmp['4']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	   <?php
	    if(isset($_POST['changecharkd'])){
		 $name = anti_injection($_POST['name']);
		 $kills = anti_injection($_POST['kills']);
		 $deaths = anti_injection($_POST['deaths']);
		 $charsql = mssql_query("SELECT * FROM Character WHERE Name='$name'");
		  if($name){
		   if(mssql_num_rows($charsql)<>0){
		    $chcrnm = mssql_query("UPDATE Character SET KillCount='$kills', DeathCount='$deaths' WHERE Name='$name'");
			echo $admingmp['23'];
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
	 <!-- Change Character Kill/DeathCount End -->
	 <!-- Reset Character Start -->
	 <div class="adm_tit"><?php echo $admingmp['29']; ?></div>
      <form action="index.php?act=admin&amp;do=characters" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['10'].' :'; ?></td><td><input type="text" name="name" class="tbl_colbor" /></td></tr>
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
      <form action="index.php?act=admin&amp;do=accounts" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['31'].' :'; ?></td><td><input type="text" name="userid" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['32'].' :'; ?></td><td><input type="text" name="password" class="tbl_colbor" /></td></tr>
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
      <form action="index.php?act=admin&amp;do=accounts" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['31'].' :'; ?></td><td><input type="text" name="userid" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['36'].' :'; ?></td><td align="right"><select name="rank" class="tbl_colbor">
	   <option value="<?php echo $adminugid; ?>"><?php echo $staff['1']; ?></option>
	   <option value="<?php echo $fmodugid; ?>"><?php echo $staff['3']; ?></option>
	   <option value="<?php echo $gmugid; ?>"><?php echo $staff['4']; ?></option>
	   <option value="<?php echo $devugid; ?>"><?php echo $staff['5']; ?></option>
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
	 <!-- Ban IP Start -->
	 	 <div class="adm_tit"><?php echo $admingmp['107']; ?></div>
      <form action="index.php?act=admin&do=accounts" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['31'].' :'; ?></td><td><input type="text" name="userid" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['108'].' :'; ?></td><td><input type="text" name="userip" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="banip" value="<?php echo $admingmp['109']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
      <?php
      if(isset($_POST['banip'])){
      $userid = anti_injection($_POST['userid']);
      $userip = anti_injection($_POST['userip']);
       if($userip){
	    $sql2 = mssql_query("INSERT INTO ipbans (UserID,IP) VALUES('$userid','$userip')");
         echo $admingmp['111'];
	   }else{
         echo $admingmp['110'];
	   }
     }
      ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Ban IP End -->
	 <?php }elseif($do == "clans"){ ?>
	 <!-- Create Clan Start -->
	 	 <div class="adm_tit"><?php echo $admingmp['40']; ?></div>
      <form action="index.php?act=admin&amp;do=clans" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['41'].' :'; ?></td><td><input type="text" name="mname" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['42'].' :'; ?></td><td><input type="text" name="clanname" class="tbl_colbor" /></td></tr>
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
      <form action="index.php?act=admin&amp;do=clans" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['42'].' :'; ?></td><td><input type="text" name="clanname" class="tbl_colbor" /></td></tr>
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
	 <!-- Change Clan Stats Start -->
	 	 <div class="adm_tit"><?php echo $admingmp['53']; ?></div>
      <form action="index.php?act=admin&amp;do=clans" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['42'].' :'; ?></td><td><input type="text" name="clanname" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['54'].' :'; ?></td><td><input type="text" name="wins" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['55'].' :'; ?></td><td><input type="text" name="losses" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['56'].' :'; ?></td><td><input type="text" name="draws" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['57'].' :'; ?></td><td><input type="text" name="points" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="changestats" value="<?php echo $admingmp['4']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
      <?php
      if(isset($_POST['changestats'])){
       $clanname = anti_injection($_POST['clanname']);
       $wins = anti_injection($_POST['wins']);
       $losses = anti_injection($_POST['losses']);
       $draws = anti_injection($_POST['draws']);
       $points = anti_injection($_POST['points']);
        $sql = mssql_query("SELECT * FROM Clan WHERE Name = '$clanname'");
        if(!$clanname&&!$points){
         echo $admingmp['60'];
        }elseif(mssql_num_rows($sql)<>0){
        $sql2 = mssql_query("UPDATE Clan SET Point='$points', Wins='$wins', Losses='$losses', Draws='$draws' WHERE Name='$clanname'");
         echo $admingmp['59'];
        }else{
          echo $admingmp['58'];
        }
      }
      ?>  
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Clan Stats End -->
	 <!-- Reset Clan Start -->
	 	 <div class="adm_tit"><?php echo $admingmp['62']; ?></div>
      <form action="index.php?act=admin&amp;do=clans" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['42'].' :'; ?></td><td><input type="text" name="clanname" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="resetclan" value="<?php echo $admingmp['28']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
      <?php
      if(isset($_POST['resetclan'])){
       $clanname = anti_injection($_POST['clanname']);
       $sql = mssql_query("SELECT * FROM Clan WHERE Name = '$clanname'");
        if(!$clanname){
         echo $admingmp['50'];
       }elseif(mssql_num_rows($sql)<>0){
       $sql2 = mssql_query("UPDATE Clan SET Point='1000', Wins='0', Losses='0', Draws='0', Ranking='0', TotalPoint='0' WHERE Name='$clanname'");
        echo $admingmp['61'];
      }else{
       echo $admingmp['58'];
      }
     }
  ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Reset Clan End -->
	 <?php }elseif($do == "givecoins"){ ?>
	 <!-- Give Coins Start -->
	 	 <div class="adm_tit"><?php echo $admingmp['75']; ?></div>
      <form action="index.php?act=admin&do=givecoins" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['31'].' :'; ?></td><td><input type="text" name="userid" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['78'].' :'; ?></td><td><input type="text" name="coins" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="givecoins" value="<?php echo $admingmp['77']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
      <?php
      if(isset($_POST['givecoins'])){
       $userid = anti_injection($_POST['userid']);
       $coins = anti_injection($_POST['coins']);
       $sql = mssql_query("SELECT * FROM Account WHERE UserID = '$userid'");
       if($userid&&$coins){
	    if(mssql_num_rows($sql)<>0){
		 $res = mssql_query("SELECT Coins FROM Account WHERE UserID = '$userid'");
		 $ucoins = mssql_fetch_assoc($res);
		  $usercoins = $ucoins['Coins'];
		 $updatecoins = $usercoins + $coins;
		 $resupd = mssql_query("UPDATE Account SET Coins='$updatecoins' WHERE UserID='$userid'");
		 echo $admingmp['80'];
		}else{
		 echo $admingmp['34'];
		}
	   }else{
	    echo $admingmp['79'];
	   }
     }
     ?>
	 </div>
	 <!-- Give Coins End -->
	 <?php }elseif($do == "additem"){ ?>
	 <!-- Add Item Start -->
	  <div class="adm_tit"><?php echo $admingmp['76']; ?></div>
      <form action="index.php?act=admin&do=additem" method="post">
	  <table width="350" align="center" height="60" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td><?php echo $admingmp['81'].' :'; ?></td><td><input type="text" name="itemname" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['82'].' :'; ?></td><td><input type="text" name="itemid" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['83'].' :'; ?></td><td><select name="sex" class="tbl_colbor">
	   <option value="1"><?php echo $admingmp['96']; ?></option><option value="0"><?php echo $admingmp['95']; ?></option><option value="2"><?php echo $admingmp['97']; ?></option></select></td></tr>
	   <tr><td><?php echo $admingmp['84'].' :'; ?></td><td><input type="text" name="level" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['85'].' :'; ?></td><td><input type="text" name="price" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['86'].' :'; ?></td><td><select name="category" class="tbl_colbor">
	   <option value="<?php echo $admingmp['98']; ?>"><?php echo $admingmp['98']; ?></option>
	   <option value="<?php echo $admingmp['99']; ?>"><?php echo $admingmp['99']; ?></option>
	   <option value="<?php echo $admingmp['100']; ?>"><?php echo $admingmp['100']; ?></option>
	   <option value="<?php echo $admingmp['101']; ?>"><?php echo $admingmp['101']; ?></option></select></td></tr>
	   <tr><td><?php echo $admingmp['87'].' :'; ?></td><td><select name="type" class="tbl_colbor">
	   <option value="<?php echo $admingmp['103']; ?>"><?php echo $admingmp['103']; ?></option>
	   <option value="<?php echo $admingmp['104']; ?>"><?php echo $admingmp['104']; ?></option>
	   <option value="<?php echo $admingmp['105']; ?>"><?php echo $admingmp['105']; ?></option>
	   <option value="<?php echo $admingmp['106']; ?>"><?php echo $admingmp['106']; ?></option></select></td></tr>
	   <tr><td><?php echo $admingmp['88'].' :'; ?></td><td><input type="text" name="image" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['89'].' :'; ?></td><td><input type="text" name="damage" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['90'].' :'; ?></td><td><input type="text" name="delay" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['91'].' :'; ?></td><td><input type="text" name="magazine" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['92'].' :'; ?></td><td><input type="text" name="hp" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['93'].' :'; ?></td><td><input type="text" name="ap" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $admingmp['94'].' :'; ?></td><td><input type="text" name="weight" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td width="130" align="right"><input type="submit" name="addnewitem" value="<?php echo $admingmp['76']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
      <?php	  
      if(isset($_POST['addnewitem'])){
       $itemname = anti_injection($_POST['itemname']);
       $itemid = anti_injection($_POST['itemid']);
       $sex = anti_injection($_POST['sex']);
       $level = anti_injection($_POST['level']);
       $price = anti_injection($_POST['price']);
       $category = anti_injection($_POST['category']);
       $type = anti_injection($_POST['type']);
       $image = anti_injection($_POST['image']);
       $damage = anti_injection($_POST['damage']);
       $delay = anti_injection($_POST['delay']);
       $magazine = anti_injection($_POST['magazine']);
       $hp = anti_injection($_POST['hp']);
       $ap = anti_injection($_POST['ap']);
       $weight = anti_injection($_POST['weight']);
       if($itemname&&$itemid&&$category&&$type&&$image){
	    $ins = mssql_query("INSERT INTO Item (ItemID,Name) VALUES('$itemid','$itemname')");
         $resquer = mssql_query("INSERT INTO ItemShop (Name,ItemID,Sex,Level,Price,Category,Type,Image,Damage,Delay,Magazine,HP,AP,Weight)
		  VALUES('$itemname','$itemid','$sex','$level','$price','$category','$type','$image','$damage','$delay','$magazine','$hp','$ap','$weight')");
		 echo $admingmp['102'];
	   }else{
	    echo $admingmp['60'];
	   }
     }
     ?>
	 </div>
	 <!-- Add Item End -->
	 <?php } ?>
	 </div>
	</div>
	<div id="tbl_footer"></div><br /><br />
	<?php
	}else{
	  redirect("index.php");
	}
	?>
	<!-- AdminPanel End -->