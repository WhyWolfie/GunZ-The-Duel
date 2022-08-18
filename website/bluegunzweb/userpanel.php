	<!-- UserPanel Start -->
    <script type="text/javascript">
    function confirmDelete(){
      var agree = confirm("<?php echo $userpanel['23']; ?>");
       if(agree){
       return true ;
     }else {
      return false ;
     }
    }
     </script>
	<?php
	 if($_SESSION['user']){
	?>
	<div id="tbl_head">
	 <div class="tbl_title_pos">
	  <?php echo $title['14']; ?>
	 </div>
	</div>
	<div id="tbl_body">
	 <div class="tbl_pos">
	 <!-- Change Name Start -->
      <form action="index.php?act=userpanel&amp;do=changename" method="post">
	  <table width="430" height="40" border="0" style="font-weight:bold; color:#FF3300;">
	  <?php
	   $getnmsql = mssql_query("SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'");
	   $getnmres = mssql_fetch_assoc($getnmsql);
	  ?>
	   <tr><td align="left"><?php echo $userpanel['1'].' :'; ?></td><td align="right"><input type="text" name="rname" value="<?php echo $getnmres['Name']; ?>" class="tbl_colbor" /></td>
	   <td align="right" width="130"><input type="submit" name="changename" value="<?php echo $userpanel['2']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	  <?php
	  if(isset($_POST['changename'])){
	  $rname = anti_injection($_POST['rname']);
	   if($rname){
	     $chnmsql = mssql_query("UPDATE Account SET Name='$rname' WHERE UserID='".$_SESSION['user']."'");
		 echo $userpanel['19'];
	   }else{
	     echo $userpanel['3'];
	   }
	  }
	  ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Name End -->
	 <!-- Change Age Start -->
      <form action="index.php?act=userpanel&amp;do=changeage" method="post">
	  <table width="430" height="40" border="0" style="font-weight:bold; color:#FF3300;">
	  <?php
	   $getagesql = mssql_query("SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'");
	   $getageres = mssql_fetch_assoc($getagesql);
	  ?>
	   <tr><td align="left"><?php echo $userpanel['4'].' :'; ?></td><td align="right"><input type="text" name="age" value="<?php echo $getageres['Age']; ?>" class="tbl_colbor" /></td>
	   <td align="right" width="130"><input type="submit" name="changeage" value="<?php echo $userpanel['5']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	  <?php
	  if(isset($_POST['changeage'])){
	  $age = anti_injection($_POST['age']);
	   if($age){
	     $chnmsql = mssql_query("UPDATE Account SET Age='$age' WHERE UserID='".$_SESSION['user']."'");
		 echo $userpanel['20'];
	   }else{
	     echo $userpanel['6'];
	   }
	  }
	  ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Age End -->
	 <!-- Change Password Start -->
      <form action="index.php?act=userpanel&amp;do=changepassword" method="post">
	  <table width="430" height="40" border="0" style="font-weight:bold; color:#FF3300;">
	  <?php
	   $getpasssql = mssql_query("SELECT * FROM Login WHERE UserID='".$_SESSION['user']."'");
	   $getpassres = mssql_fetch_assoc($getpasssql);
	  ?>
	   <tr><td align="left"><?php echo $userpanel['16'].' :'; ?></td><td align="right"><input type="text" name="password" value="<?php echo $getpassres['Password']; ?>" class="tbl_colbor" /></td>
	   <td align="right" width="130"><input type="submit" name="changepassword" value="<?php echo $userpanel['18']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	  <?php
	  if(isset($_POST['changepassword'])){
	  $password = anti_injection($_POST['password']);
	   if($password){
	     $chnmsql = mssql_query("UPDATE Login SET Password='$password' WHERE UserID='".$_SESSION['user']."'");
		 echo $userpanel['21'];
	   }else{
	     echo $userpanel['17'];
	   }
	  }
	  ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Password End -->
	 <!-- Change Country Start -->
      <form action="index.php?act=userpanel&amp;do=changecountry" method="post">
	  <table width="430" height="40" border="0" style="font-weight:bold; color:#FF3300;">
	  <?php
	   $getcountrysql = mssql_query("SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'");
	   $getcountryres = mssql_fetch_assoc($getcountrysql);
	  ?>
	   <tr><td align="left"><?php echo $userpanel['7'].' :'; ?></td><td align="right"><input type="text" name="country" value="<?php echo $getcountryres['Country']; ?>" class="tbl_colbor" /></td>
	   <td align="right" width="130"><input type="submit" name="changecountry" value="<?php echo $userpanel['8']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	  <?php
	  if(isset($_POST['changecountry'])){
	  $country = anti_injection($_POST['country']);
	   if($country){
	     $chnmsql = mssql_query("UPDATE Account SET Country='$country' WHERE UserID='".$_SESSION['user']."'");
		 echo $userpanel['22'];
	   }else{
	     echo $userpanel['9'];
	   }
	  }
	  ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Country End -->
	 <!-- Change Email Start -->
      <form action="index.php?act=userpanel&amp;do=changeemail" method="post">
	  <table width="430" height="40" border="0" style="font-weight:bold; color:#FF3300;">
	  <?php
	   $getcountrysql = mssql_query("SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'");
	   $getcountryres = mssql_fetch_assoc($getcountrysql);
	  ?>
	   <tr><td align="left"><?php echo $userpanel['24'].' :'; ?></td><td align="right"><input type="text" name="email" value="<?php echo $getcountryres['Email']; ?>" class="tbl_colbor" /></td>
	   <td align="right" width="130"><input type="submit" name="changeemail" value="<?php echo $userpanel['25']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	  <?php
	  if(isset($_POST['changeemail'])){
	  $email = anti_injection($_POST['email']);
	   if($email){
	     $chnmsql = mssql_query("UPDATE Account SET Email='$email' WHERE UserID='".$_SESSION['user']."'");
		 echo $userpanel['27'];
	   }else{
	     echo $userpanel['26'];
	   }
	  }
	  ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Email End -->
	 <!-- Delete Clan Start -->
      <form action="index.php?act=userpanel&amp;do=deleteclan" method="post">
	  <table width="430" height="40" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td align="left"><?php echo $userpanel['11'].' :'; ?></td><td align="right">
	   <select name="clanname" class="tbl_colbor">
	  <?php
       $acsql1 = mssql_query("SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'");
	   $acres = mssql_fetch_assoc($acsql1);
	   
       $chsql1 = mssql_query("SELECT * FROM Character WHERE AID='".$acres['AID']."'");
	   while($chres = mssql_fetch_assoc($chsql1)){
        
		$clsgql1 = mssql_query("SELECT * FROM Clan WHERE MasterCID='".$chres['CID']."' AND DeleteFlag='0'");
		while($clres = mssql_fetch_assoc($clsgql1)){
	  ?>
	   <option value="<?php echo $clres['Name']; ?>"><?php echo $clres['Name']; ?></option>
	   <?php }} ?>
	   </select></td>
	   <td align="right" width="130"><input type="submit" name="deleteclan" value="<?php echo $userpanel['11']; ?>" onclick="return confirmDelete()" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	  <?php
	  if(isset($_POST['deleteclan'])){
	  $clanname = anti_injection($_POST['clanname']);
	   if($clanname){
         $selfrclan = mssql_query("SELECT * FROM Clan WHERE Name='$clanname'");
		 $clidclan = mssql_fetch_assoc($selfrclan);
         $delclanmembs = mssql_query("DELETE FROM ClanMember WHERE CLID='".$clidclan['CLID']."'");
		 $delclan = mssql_query("UPDATE Clan SET Name = NULL, DeleteFlag = 1, DeleteName='$clanname' WHERE CLID='".$clidclan['CLID']."'");
		 echo $userpanel['12'];
	   }else{
	     echo $userpanel['10'];
	   }
	  }
	  ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Delete Clan End -->
	 <?php if("yes" == $allow_sex_change){ ?>
	 <!-- Change Sex Start -->
      <form action="index.php?act=userpanel&amp;do=changesex" method="post">
	  <table width="430" height="40" border="0" style="font-weight:bold; color:#FF3300;">
	   <tr><td align="left"><?php echo $userpanel['15'].' :'; ?></td>
	   <td align="right"><select name="chname" class="tbl_colbor">
	   <?php
	    $sqlacc = mssql_query("SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'");
	    $sqlaccres = mssql_fetch_assoc($sqlacc);
		echo $sqlaccres['AID'];
		$sqlchar = mssql_query("SELECT * FROM Character WHERE AID='".$sqlaccres['AID']."' ORDER BY CID DESC");
		 while($sqlchr = mssql_fetch_assoc($sqlchar)){
	   ?>
	   <option value="<?php echo $sqlchr['Name']; ?>"><?php echo $sqlchr['Name']; ?></option>
	   <?php } ?>
	   </select></td>
	   <td align="right"><select name="sex" class="tbl_colbor"><option value="1">Female</option><option value="0">Male</option></select></td>
	   <td align="right" width="130"><input type="submit" name="changesex" value="<?php echo $userpanel['15']; ?>" /></td></tr>
	  </table>
	  </form>
	  <div class="tbl_errmes">
	  <?php
	  if(isset($_POST['changesex'])){
	  $sex = anti_injection($_POST['sex']);
	  $chname = anti_injection($_POST['chname']);
       $upsexsql = mssql_query("UPDATE Character SET Sex='$sex' WHERE Name='$chname'");
		 echo $userpanel['14'];
	  }
	  ?>
	  </div>
	  <div class="dotted_line"></div>
	 <!-- Change Sex End -->
	 <?php } ?>
	 </div>
	</div>
	<div id="tbl_footer"></div><br /><br />
	<?php
	}else{
	  redirect("index.php");
	}
	?>
	<!-- UserPanel End -->