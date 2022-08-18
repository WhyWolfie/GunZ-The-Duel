<!-- Login Start -->
<?php
 $userid = anti_injection($_POST['userid']);
 $password = anti_injection($_POST['password']);
 
 $sqllogin = mssql_query("SELECT * FROM Login WHERE UserID='$userid' AND Password='$password'");
 if($userid&&$userid){
  if(mssql_num_rows($sqllogin)<>0){
   $sql1 = mssql_query("SELECT * FROM Account WHERE UserID='$userid'");
    $_SESSION['user'] = $userid;
    $sql2 = "SELECT * FROM Account WHERE UserID='".$_SESSION['user']."'";
	$res = mssql_query($sql2);
	$ugid = mssql_fetch_assoc($res);
	$_SESSION['UGradeID'] = $ugid['UGradeID'];
  }else{
    $msg = $logerror['1']; alert($msg);
    redirect("index.php");
    die();
  }
 }else{
   $msg = $logerror['2']; alert($msg);
   redirect("index.php");
   die();
 }

header("Refresh: 3; url=\"index.php\"");
?>
<div style="text-align:center; padding-top:150px;">
<img align="absmiddle" src="images/progress.gif">&nbsp;<?php echo $login['1']; ?><br /><br />
<script language="javascript">
var time_left = 2;
var cinterval;

function time_dec(){
  time_left--;
  document.getElementById('countdown').innerHTML = time_left;
  if(time_left == 0){
    clearInterval(cinterval);
  }
}
cinterval = setInterval('time_dec()', 1000);
</script>
<?php echo $login['2']; ?> <span id="countdown">2</span>.
</div>
<!-- Login End -->