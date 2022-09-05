<?php
 if ($_SERVER['REQUEST_METHOD'] == 'GET' && realpath(__FILE__) == realpath($_SERVER['SCRIPT_FILENAME'])) {
	header("Location: index.php");
	exit();
 } else {
?>
<br>
<div class="etsov" align="center">
<center><a href="<?=$download?>"><img src="Images/download.png" width="260" height="100" alt="GunZ Client Download"></a></center>
<br><br>
 <?php
  $query = odbc_exec($connect, "SELECT CurrPlayer FROM ServerStatus");
  odbc_fetch_row($query);
  $players = odbc_result($query, 1);
  echo "<b><font color='#ffff00'>" . $players . "</font> <font color='#ffffff'>/ $max_players Online Players </font></b> <br />";

  $query = odbc_exec($connect, "SELECT * FROM ServerStatus(nolock) WHERE Opened != 0");
    while( $data = odbc_fetch_object($query) )
    {
        $ip = $data->IP;
        $port = $data->Port;
        $check = @fsockopen($ip, $port, $errno, $errstr, 1);

        if (!$check)
        {
            echo "<b><font color='#ffffff'>Server Status:</font></b> <font style='color: #FF3300'><B>Offline</B></font><br />";
        }
        else
        {
            echo "<b><font color='#ffffff'>Server Status:</font></b> <font style='color: #009933'><B>Online</B></font><br />";
            fclose($check);
        }
	}
 ?>
<br>
<!-- Please Keep Credits :) -->
<font size="1">Copyright <?=$year?> Tannous | <?=$servername?>, All Rights Reserved.</font>
</center>
</div>
</body>
</html>
<?php
 }
?>