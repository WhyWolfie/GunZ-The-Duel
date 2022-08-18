<!-- Register Start -->
	<div id="tbl_head">
	 <div class="tbl_title_pos">
	  <?php echo $title['9']; ?>
	 </div>
	</div>
	<div id="tbl_body">
	 <div class="tbl_pos">
	 <?php
	  echo '<div style="color:#CC0000;font-size:11px;font-weight:;">'.$reg['8'].'</div>';
	 ?><br />
	 <div class="dotted_line"></div><br />
     <form action="index.php?act=register&amp;do=register" method="post">	
      <table border="0" align="center">
          <tr><td><b><?php echo $reg['1']." :"; ?></b> </td><td><input type="text" name="userid" maxlength="15" class="tbl_colbor" /></td></tr>
          <tr><td><b><?php echo $reg['2']." :"; ?></b> </td><td><input type="password" name="pw" maxlength="25" class="tbl_colbor" /></td></tr>
          <tr><td><b><?php echo $reg['3']." :"; ?></b> </td><td><input type="password" name="repeatpw" maxlength="25" class="tbl_colbor" /></td></tr>
          <tr><td><b><?php echo $reg['4']." :"; ?></b> </td><td><input type="text" name="email" maxlength="35" class="tbl_colbor" /></td></tr>
          <tr><td><b><?php echo $reg['5']." :"; ?></b> </td><td><input type="text" name="name" maxlength="20" class="tbl_colbor" /></td></tr>
          <tr><td><b><?php echo $reg['6']." :"; ?></b> </td><td><input type="text" name="age" maxlength="3" size="1" class="tbl_colbor" /></td></tr>
          <tr><td><b><img src="includes/CaptchaSecurityImages.php?width=100&height=40&characters=5" /></b></td>
		  <td><input type="text" id="security_code" name="security_code" maxlength="5" size="3" class="tbl_colbor" /></td></tr>
          <tr><td></td></tr>
          <tr><td><input type="submit" name="register" value="<?php echo $reg['7']; ?>" /></td></tr>
      </table>
     </form>
	 <div id="regs">
<?php
if(isset($_POST['register'])){
 $userid = anti_injection($_POST['userid']);
 $pw = anti_injection($_POST['pw']);
 $repeatpw = anti_injection($_POST['repeatpw']);
 $email = anti_injection($_POST['email']);
 $age = anti_injection($_POST['age']);
 $rname = anti_injection($_POST['name']);
 $captcha = anti_injection($_POST['security_code']);
	 
 if($userid&&$pw&&$repeatpw&&$email&&$age&&$rname&&$captcha){
  $query = mssql_query("SELECT UserID FROM Login WHERE UserID='$userid'");
  $num_rows = mssql_num_rows($query);
  if ($num_rows == 0)
  {
  $selectemail = mssql_query_z("SELECT Email FROM Account WHERE Email='$email'");
  $numrows = mssql_num_rows($selectemail);
  if ($numrows == 0){
   if($pw==$repeatpw){
   if(strlen($userid)>25){
    echo $regerror['1'];
   }  
   else{
  if($_SESSION['security_code'] == $_POST['security_code'] && !empty($_SESSION['security_code'] ) ) {
	unset($_SESSION['security_code']);
   $date = date("Y-m-d H:i:s");
   $IP = $_SERVER['REMOTE_ADDR'];
   $insert2 = mssql_query_z("INSERT INTO Account (UserID, UGradeID, PGradeID, RegDate, Email, Name, Age) VALUES('$userid', '0', '0', '$date', '$email', '$rname', '$age')");
   $query2 = mssql_query("SELECT AID FROM Account WHERE UserID='$userid'");
   if ($query2 <> 0){
   $i=1;
   while ($ad = mssql_fetch_assoc($query2)){
   $aid = $ad['AID'];
   $i++;
   $insert = mssql_query("INSERT INTO Login (UserID, AID, Password) VALUES('$userid', '$aid', '$pw')");
     echo $regerror['2'];
   }
   }
   }else{
    echo $regerror['3'];
   }}
   }else
     echo $regerror['4'];
   }else{
     echo $regerror['5'];
   }
   }else{
     echo $regerror['6'];
   }
  }else{
    echo $regerror['7'];
 }
}
?>
    </div>
	 </div>
	</div>
	<div id="tbl_footer"></div><br /><br />
<!-- Register End -->