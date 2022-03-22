<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }

    showmessage();

    if( isset($_POST['fetchrank']) )
    {
        $query01 = odbc_exec($connection, "
                                SELECT CLID FROM {$_CONFIG[ClanTable]}(nolock) WHERE DeleteFlag=0 AND ((Wins != 0) OR (Losses != 0))
	                            ORDER BY Point Desc, Wins Desc, Losses Asc");
        $rank = 0;

        while( odbc_fetch_row($query01) )
        {
            $rank++;
            $clid = odbc_result($query01, 1);
            odbc_exec($connection, "UPDATE {$_CONFIG[ClanTable]} SET Ranking = $rank WHERE CLID = $clid");
        }

        writetolog( $_STR[Log18] );
        setmessage("Clan Ranking", $_STR[Clan18]);
        redirect("index.php?do=clans");
        die();
    }
    elseif( isset($_POST['createclan']) )
    {
        $clanname = clean_sql($_POST['clanname']);
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);

        if( $clanname == "" || $type == "" || $id == "" )
        {
            setmessage("Create Clan", $_STR[Msg1]);
            redirect("index.php?do=clans");
            die();
        }

        $query01 = odbc_exec($connection, "SELECT CLID FROM {$_CONFIG[ClanTable]}(nolock) WHERE Name = '$clanname'");
        if( num_rows($query01) != 0 )
        {
            setmessage("Create Clan", $_STR[Clan19]);
            redirect("index.php?do=clans");
            die();
        }

        if( $type == 0 )
        {
            $query02 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]}(nolock) WHERE Name = '$id'");
        }
        elseif( $type == 1 )
        {
            $query02 = odbc_exec($connection, "SELECT CID FROM {$_CONFIG[CharTable]}(nolock) WHERE CID = '$id'");
        }
        else
        {
            redirect("index.php?do=clans");
            die();
        }

        if( num_rows($query02) != 1 )
        {
            setmessage("Create Clan", $_STR[Clan20]);
            redirect("index.php?do=clans");
            die();
        }
        else
        {
            odbc_fetch_row($query02);
            $cid = odbc_result($query02, 1);

            $query03 = odbc_exec($connection, "SELECT CLID FROM {$_CONFIG[ClanMembTable]} WHERE CID = '$cid'");

            if( num_rows($query03) != 0 )
            {
                setmessage("Create Clan", $_STR[Clan21]);
                redirect("index.php?do=clans");
                die();
            }

            odbc_exec($connection, "
                            INSERT INTO {$_CONFIG[ClanTable]} (Name, MasterCID, RegDate)
                            VALUES ('$clanname', '$cid', GETDATE())");

            $query04 = odbc_exec($connection, "SELECT CLID FROM {$_CONFIG[ClanTable]}(nolock) WHERE Name = '$clanname' AND MasterCID = '$cid'");
            odbc_fetch_row($query04);
            $clid = odbc_result($query04, 1);

            odbc_exec($connection, "
                            INSERT INTO {$_CONFIG[ClanMembTable]} (CLID, CID, Grade, RegDate)
                            VALUES ('$clid', '$cid', 1, GETDATE())");

            writetolog( sprintf($_STR[Log19], $clanname, $cid) );
            setmessage("Create Clan", $_STR[Clan22]);
            redirect("index.php?do=clans");
            die();
        }

    }
    elseif( isset($_POST['deleteclan']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);

        if( $type == "" || $id == "" )
        {
            setmessage("Delete Clan", $_STR[Msg1]);
            redirect("index.php?do=clans");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CLID, Name FROM {$_CONFIG[ClanTable]}(nolock) WHERE Name = '$id'");
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CLID, Name FROM {$_CONFIG[ClanTable]}(nolock) WHERE CLID = '$id'");
        }
        else
        {
            redirect("index.php?do=clans");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Delete Clan", $_STR[Clan23]);
            redirect("index.php?do=clans");
            die();
        }
        else
        {
            odbc_fetch_row($query01);
            $clid = odbc_result($query01, 1);
            $name = odbc_result($query01, 2);
            odbc_exec($connection, "DELETE FROM {$_CONFIG[ClanMembTable]} WHERE CLID = '$clid'");
            odbc_exec($connection, "UPDATE {$_CONFIG[ClanTable]} SET Name = NULL, DeleteFlag = 1, DeleteName = '$name' WHERE CLID = '$clid'");

            writetolog( sprintf($_STR[Log20], $name) );
            setmessage("Delete Clan", $_STR[Clan24]);
            redirect("index.php?do=clans");
            die();
        }
    }
    elseif( isset($_POST['resetclan']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);

        if( $type == "" || $id == "" )
        {
            setmessage("Reset Clan", $_STR[Msg1]);
            redirect("index.php?do=clans");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CLID, Name FROM {$_CONFIG[ClanTable]}(nolock) WHERE Name = '$id'");
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CLID, Name FROM {$_CONFIG[ClanTable]}(nolock) WHERE CLID = '$id'");
        }
        else
        {
            redirect("index.php?do=clans");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Reset Clan", $_STR[Clan23]);
            redirect("index.php?do=clans");
            die();
        }
        else
        {
            odbc_fetch_row($query01);
            $clid = odbc_result($query01, 1);
            $name = odbc_result($query01, 2);

            odbc_exec($connection, "
                            UPDATE {$_CONFIG[ClanTable]} SET Ranking = 0, Wins=0, Losses=0, Point=1000,
                            RankIncrease=0, LastDayRanking=0 WHERE CLID = '$clid'");

            writetolog( sprintf($_STR[Log21], $name) );
            setmessage("Reset Clan", $_STR[Clan25]);
            redirect("index.php?do=clans");
            die();
        }
    }
    elseif( isset($_POST['resetallclans']) )
    {
        odbc_exec($connection, "
                        UPDATE {$_CONFIG[ClanTable]} SET Ranking = 0, Wins=0, Losses=0, Point=1000,
                        RankIncrease=0, LastDayRanking=0");

        writetolog($_STR[Log22]);
        setmessage("Reset all Clans", $_STR[Clan26]);
        redirect("index.php?do=clans");
        die();
    }
    elseif( isset($_POST['removeemblem']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);

        if( $type == "" || $id == "" )
        {
            setmessage("Remove Emblem", $_STR[Msg1]);
            redirect("index.php?do=clans");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CLID, Name FROM {$_CONFIG[ClanTable]}(nolock) WHERE Name = '$id'");
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CLID, Name FROM {$_CONFIG[ClanTable]}(nolock) WHERE CLID = '$id'");
        }
        else
        {
            redirect("index.php?do=clans");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Remove Emblem", $_STR[Clan23]);
            redirect("index.php?do=clans");
            die();
        }
        else
        {
            odbc_fetch_row($query01);
            $clid = odbc_result($query01, 1);
            $name = odbc_result($query01, 2);

            odbc_exec($connection, "
                            UPDATE {$_CONFIG[ClanTable]} SET EmblemURL = NULL, EmblemChecksum = EmblemChecksum + 2
                            WHERE CLID = '$clid'");

            writetolog( sprintf($_STR[Log23], $name) );
            setmessage("Remove Emblem", $_STR[Clan27]);
            redirect("index.php?do=clans");
            die();
        }
    }
    elseif( isset($_POST['changestats']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $wins = clean_sql($_POST['wins']);
        $losses = clean_sql($_POST['losses']);
        $points = clean_sql($_POST['points']);

        if( $type == "" || $id == "" || $wins == "" || $losses == "" || $points == "")
        {
            setmessage("Change Stats", $_STR[Msg1]);
            redirect("index.php?do=clans");
            die();
        }

        if( !is_numeric($wins) || !is_numeric($losses) || !is_numeric($points) )
        {
            setmessage("Change Stats", $_STR[Clan28]);
            redirect("index.php?do=clans");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CLID, Name FROM {$_CONFIG[ClanTable]}(nolock) WHERE Name = '$id'");
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CLID, Name FROM {$_CONFIG[ClanTable]}(nolock) WHERE CLID = '$id'");
        }
        else
        {
            redirect("index.php?do=clans");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Change Stats", $_STR[Clan23]);
            redirect("index.php?do=clans");
            die();
        }
        else
        {
            odbc_fetch_row($query01);
            $clid = odbc_result($query01, 1);
            $name = odbc_result($query01, 2);

            odbc_exec($connection, "
                            UPDATE {$_CONFIG[ClanTable]} SET Wins = '$wins', Losses = '$losses', Point = '$points'
                            WHERE CLID = '$clid'");

            writetolog( sprintf($_STR[Log24], $name) );
            setmessage("Change Stats", $_STR[Clan29]);
            redirect("index.php?do=clans");
            die();
        }
    }
    elseif( isset($_POST['changerank']) )
    {
        $type = clean_sql($_POST['type']);
        $id = clean_sql($_POST['id']);
        $rank = clean_sql($_POST['rank']);

        if( $type == "" || $id == "" )
        {
            setmessage("Change Rank", $_STR[Msg1]);
            redirect("index.php?do=clans");
            die();
        }

        if( $rank != 2 && $rank != 9 )
        {
            setmessage("Change Rank", $_STR[Clan31]);
            redirect("index.php?do=clans");
            die();
        }

        if( $type == 0 )
        {
            $query01 = odbc_exec($connection, "SELECT CID, Name FROM {$_CONFIG[CharTable]}(nolock) WHERE Name = '$id'");
        }
        elseif( $type == 1 )
        {
            $query01 = odbc_exec($connection, "SELECT CID, Name FROM {$_CONFIG[CharTable]}(nolock) WHERE CID = '$id'");
        }
        else
        {
            redirect("index.php?do=clans");
            die();
        }

        if( num_rows($query01) != 1 )
        {
            setmessage("Change Rank", $_STR[Clan30]);
            redirect("index.php?do=clans");
            die();
        }
        else
        {
            odbc_fetch_row($query01);
            $cid = odbc_result($query01, 1);
            $name = odbc_result($query01, 2);

            $query02 = odbc_exec($connection, "SELECT CLID, Grade FROM {$_CONFIG[ClanMembTable]}(nolock) WHERE CID = '$cid'");
            if( num_rows($query02) != 1 )
            {
                setmessage("Change Rank", $_STR[Clan32]);
                redirect("index.php?do=clans");
                die();
            }

            odbc_fetch_row($query02);
            if( odbc_result($query02, 2) == 1 )
            {
                setmessage("Change Rank", $_STR[Clan33]);
                redirect("index.php?do=clans");
                die();
            }

            odbc_exec($connection, "UPDATE {$_CONFIG[ClanMembTable]} SET Grade = '$rank' WHERE CID = '$cid'");
            writetolog( sprintf($_STR[Log25], $name, $rank) );
            setmessage("Change Rank", $_STR[Clan34]);
            redirect("index.php?do=clans");
            die();
        }


    }

?>

<table border="1" style="border-collapse: collapse" id="fetchrank">
<tr><td colspan="2"><b><?php echo $_STR[Clan0]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=clans">
<tr>
    <td width="450" align="center">
    <?php echo $_STR[Clan1]; ?><br />
    <input type="submit" name="fetchrank" value="<?php echo $_STR[Clan2]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="createclan">
<tr><td colspan="2"><b><?php echo $_STR[Clan3]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=clans">
<tr>
    <td width="450">
    <?php echo $_STR[Clan4]; ?>:&nbsp;&nbsp;<input type="text" name="clanname" /><br /><br />
    Master:&nbsp;&nbsp;
    <select name="type">
    <option value="0"><?php echo $_STR[Clan4]; ?></option>
    <option value="1">CID</option>
    </select>&nbsp;&nbsp;<input type="text" name="id" />
    <input type="submit" name="createclan" value="<?php echo $_STR[Clan5]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="deleteclan">
<tr><td colspan="2"><b><?php echo $_STR[Clan6]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=clans">
<tr>
    <td width="450">
    <select name="type">
    <option value="0"><?php echo $_STR[Clan4]; ?></option>
    <option value="1">CLID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />
    <input type="submit" name="deleteclan" value="<?php echo $_STR[Clan7]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="resetclan">
<tr><td colspan="2"><b><?php echo $_STR[Clan8]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=clans">
<tr>
    <td width="450">
    <select name="type">
    <option value="0"><?php echo $_STR[Clan4]; ?></option>
    <option value="1">CLID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />
    <input type="submit" name="resetclan" value="<?php echo $_STR[Clan10]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="resetallclans">
<tr><td colspan="2"><b><?php echo $_STR[Clan9]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form name="resetall" method="post" action="index.php?do=clans">
<tr>
    <td width="450" align="center">
    <?php echo $_STR[Clan17]; ?>
    <input type="submit" name="resetallclans" value="<?php echo $_STR[Clan10]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="removeemblem">
<tr><td colspan="2"><b><?php echo $_STR[Clan11]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=clans">
<tr>
    <td width="450">
    <select name="type">
    <option value="0"><?php echo $_STR[Clan4]; ?></option>
    <option value="1">CLID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />
    <input type="submit" name="removeemblem" value="<?php echo $_STR[Clan12]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changestats">
<tr><td colspan="2"><b><?php echo $_STR[Clan13]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=clans">
<tr>
    <td width="450">
    <select name="type">
    <option value="0"><?php echo $_STR[Clan4]; ?></option>
    <option value="1">CLID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" />
    Wins:&nbsp;&nbsp;<input type="text" name="wins" /><br /><br />
    Losses:&nbsp;&nbsp;<input type="text" name="losses" />&nbsp;&nbsp;Points:&nbsp;&nbsp;<input type="text" name="points" />
    <input type="submit" name="changestats" value="<?php echo $_STR[Clan14]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="changerank">
<tr><td colspan="2"><b><?php echo $_STR[Clan15]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=clans">
<tr>
    <td width="450">
    <select name="type">
    <option value="0"><?php echo $_STR[Clan4]; ?></option>
    <option value="1">CID</option>
    </select>:&nbsp;&nbsp;<input type="text" name="id" /><br /><br />
    <?php echo $_STR[Clan16]; ?>:&nbsp;&nbsp;
    <select name="rank">
    <option value="9">Normal</option>
    <option value="2">Admin</option>
    </select>
    <input type="submit" name="changerank" value="<?php echo $_STR[Clan14]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
