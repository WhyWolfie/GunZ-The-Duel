	<!-- Reset Password Start -->
	<div id="tbl_head">
	 <div class="tbl_title_pos">
	  <?php echo $title['22']; ?>
	 </div>
	</div>
	<div id="tbl_body">
	 <div class="tbl_pos">
	  <form action="index.php?act=forgottenpassword" method="post">
	  <table width="70%" align="center" style="font-weight:bold;">
	   <tr><td><?php echo $fopass['2'].' : ';?></td> <td><input type="text" name="fuserid" class="tbl_colbor" /></td></tr>
	   <tr><td><?php echo $fopass['3'].' : ';?></td> <td><input type="text" name="femail" class="tbl_colbor" /></td></tr>
	   <tr><td></td><td><input type="submit" name="sendpassword" value="<?php echo $fopass['1']; ?>" />
	  </table>
	  </form>
	  <div class="forgpaser">
	 <?php
	  if(isset($_POST['sendpassword'])){
	   $userid = anti_injection($_POST['fuserid']);
	   $email = anti_injection($_POST['femail']);
	    if(!$fuserid&&!$fuserid){
		  echo $fopass['4'];
		}else{
		  $fsql = mssql_query("SELECT UserID FROM Account WHERE UserID='$userid'");
		  if(mssql_num_rows($fsql)<>0){
		  $fcusid = mssql_fetch_assoc($fsql);
		   $fsql2 = mssql_query("SELECT Email FROM Account WHERE UserID='".$fcusid['UserID']."'");
		   if(mssql_num_rows($fsql2)<>0){
           $fcemail = mssql_fetch_assoc($fsql2);
		    $fsql3 = mssql_query("SELECT Email FROM Account WHERE Email='".$fcemail['Email']."'");
			if(mssql_num_rows($fsql3)<>0){
			$coremail = mssql_fetch_assoc($fsql3);
			  if($email == $coremail['Email']){
			   $fsql4 = "SELECT * FROM Login WHERE UserID='".$fcusid['UserID']."'";
			   $fcnquery = mssql_query($fsql4);
			   $password = mssql_fetch_assoc($fcnquery);
               $pass = $password['Password'];
			   
			   $text = 'Your '.$gunz_name.' Password : '.$pass;
                mail($coremail['Email'],'Your '.$gunz_name.' Password',$text,'From: '.$gunz_name.' <'.$gunz_name.'@hotmail.com>');
                echo $fopass['7'];
				
			  }else{
			    echo $fopass['6'];
			  }
			}
		   }
		  }else{
		    echo $fopass['5'];
		  }
		}
	  }
	 ?>
	 </div>
	 </div>
	</div>
	<div id="tbl_footer"></div><br /><br />
	<!-- Reset Password End -->