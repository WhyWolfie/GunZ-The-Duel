<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: index.php");
        die();
    }

    showmessage();

    if( isset($_POST['changeuserid']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $nuserid = clean_sql($_POST['nuserid']);

        if( $type == "" || $id == "" || $nuserid == "" )
        {
            setmessage("UserID Change", $_STR[Msg1]);
            redirect("index.php?do=accounts");
            die();
        }

        $query01 = odbc_exec($connection, "SELECT AID FROM {$_CONFIG[AccountTable]}(nolock) WHERE UserID = '$nuserid'");
        if( num_rows($query01) != 0 )
        {
            setmessage("UserID Change", sprintf($_STR[Acc15], $nuserid));
            redirect("index.php?do=accounts");
            die();
        }

        if( $type == 0 )
        {
            $query02 = odbc_exec($connection, "SELECT AID FROM {$_CONFIG[AccountTable]}(nolock) WHERE UserID = '$id'");
            $part = "UserID";
        }
        elseif( $type == 1 )
        {
            $query02 = odbc_exec($connection, "SELECT UserID FROM {$_CONFIG[AccountTable]}(nolock) WHERE AID = '$id'");
            $part = "AID";
        }
        else
        {
            redirect("index.php?do=accounts");
            die();
        }

        if( num_rows($query02) != 1 )
        {
            setmessage("UserID Change", $_STR[Acc16]);
            redirect("index.php?do=accounts");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[AccountTable]} SET UserID = '$nuserid' WHERE $part = '$id'");
			odbc_exec($connection, "UPDATE {$_CONFIG[LoginTable]} SET UserID = '$nuserid' WHERE $part = '$id'");
            writetolog( sprintf($_STR[Log0], $part, $id, $nuserid) );
            setmessage("UserID Change", $_STR[Acc17]);
            redirect("index.php?do=accounts");
            die();
        }
    }
    elseif( isset($_POST['changepassword']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $passw = clean_sql($_POST['npassw']);

        if( $type == "" || $id == "" || $passw == "" )
        {
            setmessage("Password Change", $_STR[Msg1]);
            redirect("index.php?do=accounts");
            die();
        }

        if( $type == 0 )
        {
            $query02 = odbc_exec($connection, "SELECT AID FROM {$_CONFIG[AccountTable]}(nolock) WHERE UserID = '$id'");
            $part = "UserID";
        }
        elseif( $type == 1 )
        {
            $query02 = odbc_exec($connection, "SELECT UserID FROM {$_CONFIG[AccountTable]}(nolock) WHERE AID = '$id'");
            $part = "AID";
        }
        else
        {
            redirect("index.php?do=accounts");
            die();
        }

        if( num_rows($query02) != 1 )
        {
            setmessage("Password Change", $_STR[Acc16]);
            redirect("index.php?do=accounts");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[LoginTable]} SET Password = '$passw' WHERE $part = '$id'");
            writetolog( sprintf($_STR[Log1], $part, $id, $passw) );
            setmessage("Password Change", $_STR[Acc18]);
            redirect("index.php?do=accounts");
            die();
        }
    }
    elseif( isset($_POST['changeugradeid']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $rank = clean_sql($_POST['rank']);

        if($rank != 253 && $rank != 0 && $rank != 252 && $rank != 254 && $rank != 255 && $rank != 3 && $rank != 4 && $rank != 5 && $rank != 6 && $rank != 7 && $rank != 8 && $rank != 100 && $rank != 101 && $rank != 102 && $rank != 103 && $rank != 104  && $rank != 105  && $rank != 2)
        {
            setmessage("Rank Change", "Invalid Rank");
            redirect("index.php?do=accounts");
            die();
        }

        if( $type == "" || $id == "" || $rank == "" )
        {
            setmessage("Rank Change", $_STR[Msg1]);
            redirect("index.php?do=accounts");
            die();
        }

        if( $type == 0 )
        {
            $query02 = odbc_exec($connection, "SELECT AID FROM {$_CONFIG[AccountTable]}(nolock) WHERE UserID = '$id'");
            $part = "UserID";
        }
        elseif( $type == 1 )
        {
            $query02 = odbc_exec($connection, "SELECT UserID FROM {$_CONFIG[AccountTable]}(nolock) WHERE AID = '$id'");
            $part = "AID";
        }
        elseif( $type == 2 )
        {
            $query02 = odbc_exec($connection, "SELECT AID FROM {$_CONFIG[CharTable]}(nolock) WHERE Name = '$id'");
            if( num_rows($query02) != 1 )
            {
                setmessage("Rank Change", $_STR[Acc16]);
                redirect("index.php?do=accounts");
                die();
            }
            else
            {
                odbc_fetch_row($query02);
                $id = odbc_result($query02, 1);
                $part = "AID";
            }
        }
        else
        {
            redirect("index.php?do=accounts");
            die();
        }

        if( $type != 2 && num_rows($query02) != 1 )
        {
            setmessage("Rank Change", $_STR[Acc16]);
            redirect("index.php?do=accounts");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[AccountTable]} SET UgradeID = '$rank' WHERE $part = '$id'");
            writetolog( sprintf($_STR[Log2], $part, $id, $rank) );
            setmessage("Rank Change", $_STR[Acc19]);
            redirect("index.php?do=accounts");
            die();
        }
    }
    elseif( isset($_POST['sendallstorage']) )
    {
        $itemid = clean_sql($_POST['itemid']);
        $rentperiod = clean_sql($_POST['rentperiod']);

        if($rentperiod == "")
            $rentperiod = 0;

        if( !is_numeric($itemid) || !is_numeric($rentperiod) )
        {
            setmessage("Send Item", $_STR[Acc20]);
            redirect("index.php?do=accounts");
            die();
        }

        if($rentperiod == 0)
        {
            odbc_exec($connection, "
                        INSERT INTO {$_CONFIG[AItemTable]} (AID, ItemID, RentDate, cnt)
                        (SELECT ac.AID, '$itemid', GETDATE(), 1 FROM {$_CONFIG[AccountTable]}(nolock) ac)");
        }
        else
        {
            $rentperiod = $rentperiod*24;
            odbc_exec($connection, "
                        INSERT INTO {$_CONFIG[AItemTable]} (AID, ItemID, RentDate, RentHourPeriod, cnt)
                        (SELECT ac.AID, '$itemid', GETDATE(), '$rentperiod', 1 FROM {$_CONFIG[AccountTable]}(nolock) ac)");
        }
            writetolog( sprintf($_STR[Log3], $itemid) );
            setmessage("Send Item", $_STR[Acc21]);
            redirect("index.php?do=accounts");
            die();

    }
    elseif( isset($_POST['sendstorage']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $itemid = clean_sql($_POST['itemid']);
        $rentperiod = clean_sql($_POST['rentperiod']);

        if($rentperiod == "")
            $rentperiod = 0;

        if( !is_numeric($itemid) || !is_numeric($rentperiod) )
        {
            setmessage("Send Item", $_STR[Acc20]);
            redirect("index.php?do=accounts");
            die();
        }

        if( $type == 0 )
        {
            $query02 = odbc_exec($connection, "SELECT AID FROM {$_CONFIG[AccountTable]}(nolock) WHERE UserID = '$id'");
        }
        elseif( $type == 1 )
        {
            $query02 = odbc_exec($connection, "SELECT UserID FROM {$_CONFIG[AccountTable]}(nolock) WHERE AID = '$id'");
        }
        else
        {
            redirect("index.php?do=accounts");
            die();
        }

        if( num_rows($query02) != 1 )
        {
            setmessage("Send Item", $_STR[Acc16]);
            redirect("index.php?do=accounts");
            die();
        }
        else
        {
            if( $type == 0 )
            {
                odbc_fetch_row($query02);
                $id = odbc_result($query02, 1);
            }

            if($rentperiod == 0)
            {
                odbc_exec($connection, "
                            INSERT INTO {$_CONFIG[AItemTable]} (AID, ItemID, RentDate, cnt)
                            VALUES('$id', '$itemid', GETDATE(), 1)");
            }
            else
            {
                $rentperiod = $rentperiod*24;
                odbc_exec($connection, "
                            INSERT INTO {$_CONFIG[AItemTable]} (AID, ItemID, RentDate, RentHourPeriod, cnt)
                            VALUES('$id', '$itemid', GETDATE(), '$rentperiod', 1)");
            }

            writetolog( sprintf($_STR[Log4], $itemid, $id) );
            setmessage("Send Item", $_STR[Acc22]);
            redirect("index.php?do=accounts");
            die();
        }



    }
?>

<table border="1" style="border-collapse: collapse" id="changeuserid">
<tr><td colspan="2"><b><?php echo $_STR[Acc0]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=accounts">
<tr>
    <td>
    <select name="type">
        <option value="0">UserID</option>
        <option value="1">AID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;<?php echo $_STR[Acc1]; ?>:&nbsp;&nbsp;<input type="text" name="nuserid" />
    &nbsp;&nbsp;<input type="submit" name="changeuserid" value="<?php echo $_STR[Acc2]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changepassword">
<tr><td colspan="2"><b><?php echo $_STR[Acc3]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=accounts">
<tr>
    <td>
    <select name="type">
        <option value="0">UserID</option>
        <option value="1">AID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;<?php echo $_STR[Acc4]; ?>:&nbsp;&nbsp;<input type="text" name="npassw" />
    &nbsp;&nbsp;<input type="submit" name="changepassword" value="<?php echo $_STR[Acc2]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changeugradeid">
<tr><td colspan="2"><b><?php echo $_STR[Acc5]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=accounts">
<tr>
    <td>
    <select name="type">
        <option value="0">UserID</option>
        <option value="1">AID</option>
        <option value="2"><?php echo $_STR[Search7];?></option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;
    <select name="rank">
        <option value="253"><?php echo $_STR[Acc6];?></option>
        <option value="0"><?php echo $_STR[Acc7];?></option>
        <option value="252"><?php echo $_STR[Acc8];?></option>
        <option value="254"><?php echo $_STR[Acc9];?></option>
        <option value="255"><?php echo $_STR[Acc10];?></option>
        <option value="2">JJang de Cuenta</option>
        <option value="3">Donador Amarillo</option>
        <option value="4">Donador Naranja</option>
        <option value="5">Donador Celeste</option>
        <option value="6">Donador Rosado</option>
        <option value="7">Donador Azul</option>
        <option value="8">Donador Blanco</option>
        <option value="100">Criminal</option>
        <option value="101">Advertido 1º</option>
        <option value="102">Advertido 2º</option>
        <option value="103">Advertido 3º</option>
        <option value="104">Baneado en Chat</option>
        <option value="105">Penalty</option>
    </select>
    &nbsp;&nbsp;<input type="submit" name="changeugradeid" value="<?php echo $_STR[Acc2]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="sendallstorage">
<tr><td colspan="2"><b><?php echo $_STR[Acc11]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=accounts">
<tr>
    <td>
    ItemID:&nbsp;&nbsp;<input type="text" name="itemid" />&nbsp;&nbsp;<?php echo $_STR[Acc12]; ?>:&nbsp;&nbsp;<input type="text" name="rentperiod" />
    &nbsp;&nbsp;<input type="submit" name="sendallstorage" value="<?php echo $_STR[Acc14]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="sendstorage">
<tr><td colspan="2"><b><?php echo $_STR[Acc13]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=accounts">
<tr>
    <td>
    <select name="type">
        <option value="0">UserID</option>
        <option value="1">AID</option>
    </select>
    :&nbsp;&nbsp;<input type="text" name="id" />
    ItemID:&nbsp;&nbsp;<input type="text" name="itemid" /><br /><br /><?php echo $_STR[Acc12]; ?>:&nbsp;&nbsp;<input type="text" name="rentperiod" />
    &nbsp;&nbsp;<input type="submit" name="sendstorage" value="<?php echo $_STR[Acc14]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br /><br />