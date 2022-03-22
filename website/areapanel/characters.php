<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: index.php");
        die();
    }

    showmessage();

    if( isset($_POST['changename']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $nname = clean_sql($_POST['nname']);

        if( $type == "" || $id == "" || $nname == "" )
        {
            setmessage("Name Change", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$nname'");
        if( num_rows($query01) != 0 )
        {
            setmessage("Name Change", sprintf($_STR[Char23], $nname));
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query02 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query02 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query02) != 1 )
        {
            setmessage("Name Change", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[CharTable]} SET Name = '$nname' WHERE $part = '$id'");
            writetolog( sprintf($_STR[Log5], $id, $nname) );
            setmessage("Name Change", $_STR[Char25]);
            redirect("index.php?do=characters");
            die();
        }

    }
    elseif( isset($_POST['deletechar']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);

        if( $type == "" || $id == "" )
        {
            setmessage("Delete Characters", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Name Change", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[CharTable]} SET CharNum = -1, DeleteFlag = 1, Name='', DeleteName='$id' WHERE $part = '$id'");
            writetolog( sprintf($_STR[Log6], $id) );
            setmessage("Name Change", $_STR[Char26]);
            redirect("index.php?do=characters");
            die();
        }


    }
    elseif( isset($_POST['deletecitems']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);

        if( $type == "" || $id == "" )
        {
            setmessage("Delete C Items", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Delete C Items", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "DELETE FROM {$_CONFIG[CItemTable]} WHERE $part = '$id'");
            writetolog( sprintf($_STR[Log7], $id) );
            setmessage("Delete C Items", $_STR[Char27]);
            redirect("index.php?do=characters");
            die();
        }
    }
    elseif( isset($_POST['deleteaitems']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);

        if( $type == "" || $id == "" )
        {
            setmessage("Delete A Items", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT ac.AID FROM {$_CONFIG[AccountTable]} ac INNER JOIN {$_CONFIG[CharTable]} ch ON ac.AID = ch.AID WHERE ch.Name = '$id'");
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT ac.AID FROM {$_CONFIG[AccountTable]} ac INNER JOIN {$_CONFIG[CharTable]} ch ON ac.AID = ch.AID WHERE ch.CID = '$id'");
        }
        elseif( $type == 2 )
        {
            $query01 = odbc_exec($connection, "SELECT AID FROM {$_CONFIG[AccountTable]} WHERE AID = '$id'");
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Delete A Items", $_STR[Char28]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_fetch_row($query01);
            $aid = odbc_result($query01, 1);

            odbc_exec($connection, "DELETE FROM {$_CONFIG[AItemTable]} WHERE AID = '$aid'");
            writetolog( sprintf($_STR[Log8], $aid) );
            setmessage("Delete A Items", $_STR[Char27]);
            redirect("index.php?do=characters");
            die();
        }
    }
    elseif( isset($_POST['senditem']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $itemid = clean_sql($_POST['itemid']);

        if( $type == "" || $id == "" || $itemid == "" )
        {
            setmessage("Send Item", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( !is_numeric($itemid) )
        {
            setmessage("Send Item", $_STR[Char32]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Send Item", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_fetch_row($query01);
            $cid = odbc_result($query01, 1);

            odbc_exec($connection, "INSERT INTO {$_CONFIG[CItemTable]} (CID, ItemID, RegDate) VALUES ('$cid', '$itemid', GETDATE())");
            writetolog( sprintf($_STR[Log9], $itemid, $cid) );
            setmessage("Send Item", $_STR[Char29]);
            redirect("index.php?do=characters");
            die();

        }

    }
    elseif( isset($_POST['deleteitem']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $itemid = clean_sql($_POST['itemid']);

        if( $type == "" || $id == "" || $itemid == "" )
        {
            setmessage("Delete Item", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( !is_numeric($itemid) )
        {
            setmessage("Delete Item", $_STR[Char32]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Delete Item", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_fetch_row($query01);
            $cid = odbc_result($query01, 1);

            odbc_exec($connection, "DELETE FROM {$_CONFIG[CItemTable]} WHERE CID = '$cid' AND ItemID = '$itemid'");
            writetolog( sprintf($_STR[Log10], $itemid, $cid) );
            setmessage("Delete Item", $_STR[Char30]);
            redirect("index.php?do=characters");
            die();
        }
    }
    elseif( isset($_POST['resetchar']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);

        if( $type == "" || $id == "" )
        {
            setmessage("Reset Character", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Reset Character", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[CharTable]} SET Level = 1, XP = 0, BP = 1000 WHERE $part = '$id'");
            writetolog( sprintf($_STR[Log11], $id) );
            setmessage("Reset Character", $_STR[Char31]);
            redirect("index.php?do=characters");
            die();
        }
    }
    elseif( isset($_POST['changexp']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $exp = clean_sql($_POST['exp']);

        if( $type == "" || $id == "" || $exp == "" )
        {
            setmessage("Change EXP", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( !is_numeric($exp) )
        {
            setmessage("Change EXP", $_STR[Char32]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Change EXP", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[CharTable]} SET XP = '$exp' WHERE $part = '$id'");
            writetolog( sprintf($_STR[Log12], $id, $exp) );
            setmessage("Change EXP", $_STR[Char33]);
            redirect("index.php?do=characters");
            die();
        }
    }
    elseif( isset($_POST['changelvl']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $lvl = clean_sql($_POST['lvl']);

        if( $type == "" || $id == "" || $lvl == "" )
        {
            setmessage("Change LVL", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( !is_numeric($lvl) )
        {
            setmessage("Change LVL", $_STR[Char32]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Change LVL", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[CharTable]} SET Level = '$lvl' WHERE $part = '$id'");
            writetolog( sprintf( $_STR[Log13], $id, $lvl ) );
            setmessage("Change LVL", $_STR[Char34]);
            redirect("index.php?do=characters");
            die();
        }
    }
    elseif( isset($_POST['changebounty']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $bounty = clean_sql($_POST['bounty']);

        if( $type == "" || $id == "" || $bounty == "" )
        {
            setmessage("Change Bounty", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( !is_numeric($bounty) )
        {
            setmessage("Change Bounty", $_STR[Char32]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Change Bounty", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[CharTable]} SET BP = '$bounty' WHERE $part = '$id'");
            writetolog( sprintf( $_STR[Log14], $id, $bounty ) );
            setmessage("Change Bounty", $_STR[Char35]);
            redirect("index.php?do=characters");
            die();
        }
    }
    elseif( isset($_POST['changesex'] ) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $sex = clean_sql($_POST['sex']);

        if( $type == "" || $id == "" || $sex == "" )
        {
            setmessage("Change Sex", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( $sex != 0 && $sex != 1 )
        {
            setmessage("Change Sex", $_STR[Char36]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Change Sex", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[CharTable]} SET Sex = '$sex' WHERE $part = '$id'");
            writetolog( sprintf( $_STR[Log15], $id ) );
            setmessage("Change Sex", $_STR[Char37]);
            redirect("index.php?do=characters");
            die();
        }
    }
    elseif( isset($_POST['changehair']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $hair = clean_sql($_POST['hair']);

        if( $type == "" || $id == "" || $hair == "" )
        {
            setmessage("Change Face", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( $hair != 0 && $hair != 1 && $hair != 2 && $hair != 3 )
        {
            setmessage("Change Hair", $_STR[Char38]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Change Hair", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[CharTable]} SET Hair = '$hair' WHERE $part = '$id'");
            writetolog( sprintf( $_STR[Log16], $id ) );
            setmessage("Change Hair", $_STR[Char39]);
            redirect("index.php?do=characters");
            die();
        }
    }
    elseif( isset($_POST['changeface']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $face = clean_sql($_POST['face']);

        if( $type == "" || $id == "" || $face == "" )
        {
            setmessage("Change Face", $_STR[Msg1]);
            redirect("index.php?do=characters");
            die();
        }

        if( $face != 0 && $face != 1 && $face != 2 && $face != 3 )
        {
            setmessage("Change Face", $_STR[Char40]);
            redirect("index.php?do=characters");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE Name = '$id'");
            $part = "Name";
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]} WHERE CID = '$id'");
            $part = "CID";
        }
        else
        {
            redirect("index.php?do=characters");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Change Face", $_STR[Char24]);
            redirect("index.php?do=characters");
            die();
        }
        else
        {
            odbc_exec($connection, "UPDATE {$_CONFIG[CharTable]} SET Face = '$face' WHERE $part = '$id'");
            writetolog( sprintf( $_STR[Log17], $id ) );
            setmessage("Change Face", $_STR[Char41]);
            redirect("index.php?do=characters");
            die();
        }
    }

?>

<table border="1" style="border-collapse: collapse" id="changename">
<tr><td colspan="2"><b><?php echo $_STR[Char0]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;<?php echo $_STR[Char2]; ?>:&nbsp;&nbsp;<input type="text" name="nname" />
    &nbsp;&nbsp;<input type="submit" name="changename" value="<?php echo $_STR[Char3]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="deletechar">
<tr><td colspan="2"><b><?php echo $_STR[Char4]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />
    &nbsp;&nbsp;<input type="submit" name="deletechar" value="<?php echo $_STR[Char5]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="deletecitems">
<tr><td colspan="2"><b><?php echo $_STR[Char6]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />
    &nbsp;&nbsp;<input type="submit" name="deletecitems" value="<?php echo $_STR[Char5]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="deleteaitems">
<tr><td colspan="2"><b><?php echo $_STR[Char7]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
        <option value="2">AID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />
    &nbsp;&nbsp;<input type="submit" name="deleteaitems" value="<?php echo $_STR[Char5]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="senditem">
<tr><td colspan="2"><b><?php echo $_STR[Char8]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;ItemID:&nbsp;&nbsp;<input type="text" name="itemid" />
    &nbsp;&nbsp;<input type="submit" name="senditem" value="<?php echo $_STR[Char10]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="deleteitem">
<tr><td colspan="2"><b><?php echo $_STR[Char9]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;ItemID:&nbsp;&nbsp;<input type="text" name="itemid" />
    &nbsp;&nbsp;<input type="submit" name="deleteitem" value="<?php echo $_STR[Char5]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="resetchar">
<tr><td colspan="2"><b><?php echo $_STR[Char11]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />
    &nbsp;&nbsp;<input type="submit" name="resetchar" value="<?php echo $_STR[Char12]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changexp">
<tr><td colspan="2"><b><?php echo $_STR[Char13]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;EXP:&nbsp;&nbsp;<input type="text" name="exp" />
    &nbsp;&nbsp;<input type="submit" name="changexp" value="<?php echo $_STR[Char3]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changelvl">
<tr><td colspan="2"><b><?php echo $_STR[Char14]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;LvL:&nbsp;&nbsp;<input type="text" name="lvl" />
    &nbsp;&nbsp;<input type="submit" name="changelvl" value="<?php echo $_STR[Char3]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changebounty">
<tr><td colspan="2"><b><?php echo $_STR[Char15]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;Bounty:&nbsp;&nbsp;<input type="text" name="bounty" />
    &nbsp;&nbsp;<input type="submit" name="changebounty" value="<?php echo $_STR[Char3]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changesex">
<tr><td colspan="2"><b><?php echo $_STR[Char16]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;
    <select name="sex">
        <option value="0"><?php echo $_STR[Char17]; ?></option>
        <option value="1"><?php echo $_STR[Char18]; ?></option>
    </select>
    &nbsp;&nbsp;<input type="submit" name="changesex" value="<?php echo $_STR[Char3]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changehair">
<tr><td colspan="2"><b><?php echo $_STR[Char19]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;<?php echo $_STR[Char20]; ?>
    <select name="hair">
        <option value="0">0</option>
        <option value="1">1</option>
        <option value="2">2</option>
        <option value="3">3</option>
    </select>
    &nbsp;&nbsp;<input type="submit" name="changehair" value="<?php echo $_STR[Char3]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changeface">
<tr><td colspan="2"><b><?php echo $_STR[Char21]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=characters">
<tr>
    <td>
    <select name="type">
        <option value="0"><?php echo $_STR[Char1]; ?></option>
        <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />&nbsp;&nbsp;<?php echo $_STR[Char22]; ?>
    <select name="face">
        <option value="0">0</option>
        <option value="1">1</option>
        <option value="2">2</option>
        <option value="3">3</option>
    </select>
    &nbsp;&nbsp;<input type="submit" name="changeface" value="<?php echo $_STR[Char3]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br /><br />