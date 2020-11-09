<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: index.php");
        die();
    }
?>

<p align="left"><b><font face="Arial" size="4"><?php echo $_STR[Home0]; ?></font></b></p>
<p align="left"><font face="Arial"><?php echo $_STR[Home1]; ?> <a href="http://forum.ragezone.com/f245/emisands-gunz-admin-panel-v3-481443/">http://forum.ragezone.com/f245/emisands-gunz-admin-panel-v3-481443/</a></font></p>
<table border="0" width="80%" id="table1" cellspacing="1" style="border-collapse: collapse">
	<tr>
		<td style="border-style: solid; border-width: 2px; padding-left: 4px; padding-right: 4px" bordercolor="#FF9933">
		<p align="left"><font face="Arial"><em><strong><?php echo $_STR[Home2]; ?></strong></em></font></td>
	</tr>
	<tr>
		<td style="border-style: solid; border-width: 2px; padding-left: 4px; padding-right: 4px" bordercolor="#FF9933">
		<p align="left"><font face="Arial" style="font-size: 11pt"><?php echo $_STR[Home3]; ?><strong>
    <?php
	$query = odbc_exec($connection, "SELECT COUNT(*) FROM {$_CONFIG[AccountTable]}(nolock)");
    odbc_fetch_row($query);
    echo odbc_result($query, 1);
    ?>
    </strong><?php echo $_STR[Home4]; ?><strong>
    <?php
    $query = odbc_exec($connection, "SELECT COUNT(*) FROM {$_CONFIG[CharTable]}(nolock)");
    odbc_fetch_row($query);
    echo odbc_result($query, 1);
    ?>
    </strong><?php echo $_STR[Home5]; ?><strong>
    <?php
    $query = odbc_exec($connection, "SELECT CurrPlayer FROM ServerStatus(nolock) WHERE Opened != 0");
    $count = 0;
    while( odbc_fetch_row($query) )
    {
        $count = $count + odbc_result($query, 1);
    }
    echo $count;
    ?>
    </strong></font></font></p>
    <p align="left"><font face="Arial" style="font-size: 11pt"><strong><?php echo $_STR[Home6]; ?><br />
    <?php
    $query = odbc_exec($connection, "SELECT * FROM ServerStatus(nolock) WHERE Opened != 0");
    while( $data = odbc_fetch_object($query) )
    {
        $ip = $data->IP;
        $port = $data->Port;
        $name = $data->ServerName;
        $fp = @fsockopen($ip, $port, $errno, $errstr, 1);

        if (!$fp)
        {
            echo "{$_STR[Home7]}: $name - <font style='color: #FF3300'><B>Offline</B></font><br />";
        }
        else
        {
            echo "{$_STR[Home7]}: $name - <font style='color: #009933'><B>Online</B></font><br />";
            fclose($fp);
        }
    }
    ?>
    </strong></font></font></p></td>

    </tr>
</table>