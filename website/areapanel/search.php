<?php
if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }

    function show_results()
    {
        global $_CONFIG, $_STR, $connection;

        if( isset($_POST['schar']) ) // Character Search
        {
            $type = clean_sql($_POST['type']);
            $reference = clean_sql($_POST['reference']);

            if($type == 1)
            {
                $query = odbc_exec($connection, "SELECT TOP 1000 CID, AID, Name, Level, XP, BP, KillCount, DeathCount FROM {$_CONFIG[CharTable]}(nolock) WHERE Name LIKE '%$reference%' AND DeleteFlag = 0");
            }
            elseif($type == 2)
            {
                $query = odbc_exec($connection, "SELECT TOP 1000 CID, AID, Name, Level, XP, BP, KillCount, DeathCount FROM {$_CONFIG[CharTable]}(nolock) WHERE AID = '$reference'");
            }
            elseif($type == 3)
            {
                $query = odbc_exec($connection, "
                            SELECT TOP 1000 ch.CID, ch.AID, ch.Name, ch.Level, ch.XP, ch.BP, ch.KillCount, ch.DeathCount FROM {$_CONFIG[CharTable]} ch INNER JOIN {$_CONFIG[ClanMembTable]} cm
                            ON ch.CID = cm.CID WHERE cm.CLID = '$reference'");
            }
            elseif($type == 4)
            {
                $query = odbc_exec($connection, "SELECT TOP 1000 CID, AID, Name, Level, XP, BP, KillCount, DeathCount FROM {$_CONFIG[CharTable]}(nolock) WHERE CID = '$reference'");
            }
            else
            {
                setmessage("Character Search", $_STR[Search13]);
                redirect("index.php?do=search");
                die();
            }

            if(num_rows($query) == 0)
            {
                setmessage("Character Search", $_STR[Search14]);
                redirect("index.php?do=search");
                die();
            }
            else
            {
            ?>
                <p><b><?php echo $_STR[Search15]; ?></b></p>
                <table width="90%" border="1" style="border-collapse: collapse" id="characters">
                <tr>
                    <td>CID</td>
                    <td>AID</td>
                    <td>Name</td>
                    <td>Level</td>
                    <td>XP</td>
                    <td>BP</td>
                    <td>KillCount</td>
                    <td>DeathCount</td>
                </tr>
                <?php

                while( odbc_fetch_row($query) )
                {
                    printf("<tr>
                    <td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td>
                    </tr>", odbc_result($query, 1), odbc_result($query, 2), odbc_result($query, 3), odbc_result($query, 4),
                    odbc_result($query, 5), odbc_result($query, 6), odbc_result($query, 7), odbc_result($query, 8));
                }
                echo "</table>";
            }

        }
        elseif( isset($_POST['sacc']) ) // Account Search
        {
            $type = clean_sql($_POST['type']);
            $reference = clean_sql($_POST['reference']);

            if($type == 1)
            {
                $query = odbc_exec($connection, "
                            SELECT TOP 1000 a.AID, a.UserID, a.UGradeID, a.Email, 1.DonatorCoins, l.LastIP, l.LastConnDate
                            FROM {$_CONFIG[AccountTable]} a INNER JOIN {$_CONFIG[LoginTable]} l ON a.AID = l.AID
                            WHERE a.UserID LIKE '%$reference%'");
            }
            elseif ($type == 2)
            {
                $query = odbc_exec($connection, "
                            SELECT a.AID, a.UserID, a.UGradeID, a.Email, 1.DonatorCoins, l.LastIP, l.LastConnDate
                            FROM {$_CONFIG[AccountTable]} a INNER JOIN {$_CONFIG[LoginTable]} l ON a.AID = l.AID
                            INNER JOIN {$_CONFIG[CharTable]} c ON a.AID = c.AID
                            WHERE c.Name = '$reference'");
            }
            else
            {
                setmessage("Account Search", $_STR[Search13]);
                redirect("index.php?do=search");
                die();
            }

            if(num_rows($query) == 0)
            {
                setmessage("Account Search", $_STR[Search14]);
                redirect("index.php?do=search");
                die();
            }
            else
            {
            ?>
                <p><b><?php echo $_STR[Search15]; ?></b></p>
                <table width="100%" border="1" style="border-collapse: collapse" id="accounts">
                <tr>
                    <td>AID</td>
                    <td>UserID</td>
                    <td>UGradeID</td>
                    <td>Email</td>
                    <td>LastIP</td>
                    <td>LastConnDate</td>
                    <td>DonatorCoins</td>
                </tr>
            <?php

                while( odbc_fetch_row($query) )
                {
                    printf("<tr>
                    <td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td>
                    </tr>", odbc_result($query, 1), odbc_result($query, 2), odbc_result($query, 3),
                    odbc_result($query, 4), odbc_result($query, 5), odbc_result($query, 6), odbc_result($query, 7));
                }
                echo "</table>";
            }
        }
        elseif( isset($_POST['sclan']) ) // Clan Search
        {
            $type = clean_sql($_POST['type']);
            $reference = clean_sql($_POST['reference']);

            if($type == 1)
            {
                $query = odbc_exec($connection, "SELECT CLID, Name, MasterCID, Point, Wins, Losses FROM {$_CONFIG[ClanTable]}(nolock) WHERE Name LIKE '%$reference%'");
            }
            elseif($type == 2)
            {
                $query = odbc_exec($connection, "SELECT CLID, Name, MasterCID, Point, Wins, Losses FROM {$_CONFIG[ClanTable]}(nolock) WHERE CLID = '$reference'");
            }
            elseif($type == 3)
            {
                $query = odbc_exec($connection, "
                                SELECT TOP 1000 cl.CLID, cl.Name, cl.MasterCID, cl.Point, cl.Wins, cl.Losses FROM {$_CONFIG[ClanTable]} cl INNER JOIN {$_CONFIG[CharTable]} ch
                                ON cl.MasterCID = ch.CID WHERE ch.Name = '$reference'");
            }
            else
            {
                setmessage("Clan Search", $_STR[Search13]);
                redirect("index.php?do=search");
                die();
            }

            if(num_rows($query) == 0)
            {
                setmessage("Clan Search", $_STR[Search14]);
                redirect("index.php?do=search");
                die();
            }
            else
            {
            ?>
                <p><b><?php echo $_STR[Search15]; ?></b></p>
                <table width="80%" border="1" style="border-collapse: collapse" id="clans">
                <tr>
                    <td>CLID</td>
                    <td>Name</td>
                    <td>MasterCID</td>
                    <td>Points</td>
                    <td>Wins</td>
                    <td>Losses</td>
                </tr>
            <?php

                while( odbc_fetch_row($query) )
                {
                    printf("<tr>
                    <td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td>
                    </tr>", odbc_result($query, 1), odbc_result($query, 2), odbc_result($query, 3),
                    odbc_result($query, 4), odbc_result($query, 5), odbc_result($query, 6));
                }
                echo "</table>";
            }
        }
        elseif( isset($_POST['spoints']) ) // Wins / Losses Search
        {
            $type = clean_sql($_POST['type']);
            $reference = clean_sql($_POST['reference']);
            $result = clean_sql($_POST['result']);
            $maxrows = clean_sql($_POST['maxrows']);

            if( $maxrows != 50 && $maxrows != 100 && $maxrows != 250 && $maxrows != 500 )
            {
                redirect("index.php?do=search");
                die();
            }

            if( $result == 1 )
            {
                $cond = "WinnerCLID";
            }
            elseif( $result == 2 )
            {
                $cond = "LoserCLID";
            }
            else
            {
                redirect("index.php?do=search");
                die();
            }

            if($type == 1)
            {
                $query = odbc_exec($connection, "
                            SELECT TOP $maxrows l.WinnerCLID, l.LoserCLID, l.WinnerClanName, l.LoserClanName, l.RoundWins, l.RoundLosses, l.RegDate
                            FROM {$_CONFIG[ClanLogTable]} l INNER JOIN {$_CONFIG[ClanTable]} c ON l.$cond = c.CLID WHERE c.Name = '$reference' ORDER BY RegDate DESC");
            }
            elseif($type == 2)
            {
                $query = odbc_exec($connection, "
                            SELECT TOP $maxrows WinnerCLID, LoserCLID, WinnerClanName, LoserClanName, RoundWins, RoundLosses, RegDate
                            FROM {$_CONFIG[ClanLogTable]} WHERE $cond = '$reference' ORDER BY RegDate DESC");
            }
            else
            {
                setmessage("Clan Games Search", $_STR[Search13]);
                redirect("index.php?do=search");
                die();
            }

            if(num_rows($query) == 0)
            {
                setmessage("Clan Games Search", $_STR[Search14]);
                redirect("index.php?do=search");
                die();
            }
            else
            {
            ?>
                <p><b><?php echo $_STR[Search15]; ?></b></p>
                <table width="90%" border="1" style="border-collapse: collapse" id="clans">
                <tr>
                    <td>WinnerCLID</td>
                    <td>LoserCLID</td>
                    <td>WinnerClanName</td>
                    <td>LoserClanName</td>
                    <td>RoundWins</td>
                    <td>RoundLosses</td>
                    <td>Date</td>
                </tr>
            <?php

                while( odbc_fetch_row($query) )
                {
                    printf("<tr>
                    <td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td>
                    </tr>", odbc_result($query, 1), odbc_result($query, 2), odbc_result($query, 3),
                    odbc_result($query, 4), odbc_result($query, 5), odbc_result($query, 6), odbc_result($query, 7));
                }
                echo "</table>";
            }
        }
    }

showmessage();
?>
<table border="1" style="border-collapse: collapse" id="search">
<tr><td colspan="2"><b><?php echo $_STR[Search1]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=search">
<tr>
    <td>
    <select name="type">
        <option value="1"><?php echo $_STR[Search5]; ?></option>
        <option value="2">AID</option>
        <option value="3">CLID</option>
        <option value="4">CID</option>
    </select>
    :&nbsp;&nbsp;<input type="text" name="reference" />&nbsp;&nbsp;&nbsp;<input type="submit" name="schar" value="<?php echo $_STR[Search0]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="search2">
<tr><td colspan="2"><b><?php echo $_STR[Search2]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=search">
<tr>
    <td>
    <select name="type">
        <option value="1">UserID</option>
        <option value="2"><?php echo $_STR[Search7]; ?></option>
    </select>
    :&nbsp;&nbsp;<input type="text" name="reference" />&nbsp;&nbsp;&nbsp;<input type="submit" name="sacc" value="<?php echo $_STR[Search0]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="search3">
<tr><td colspan="2"><b><?php echo $_STR[Search3]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=search">
<tr>
    <td>
    <select name="type">
        <option value="1"><?php echo $_STR[Search5]; ?></option>
        <option value="2">CLID</option>
        <option value="3"><?php echo $_STR[Search8]; ?></option>
    </select>
    :&nbsp;&nbsp;<input type="text" name="reference" />&nbsp;&nbsp;&nbsp;<input type="submit" name="sclan" value="<?php echo $_STR[Search0]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="search4">
<tr><td colspan="2"><b><?php echo $_STR[Search4]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=search">
<tr>
    <td>
    <select name="type">
        <option value="1"><?php echo $_STR[Search6]; ?></option>
        <option value="2">CLID</option>
    </select>
    :&nbsp;&nbsp;<input type="text" name="reference" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <input type="submit" name="spoints" value="<?php echo $_STR[Search0]; ?>" />
    </td>
</tr>
<tr>
<td><?php echo $_STR[Search9]; ?>:&nbsp;
<select name="result">
<option value="1"><?php echo $_STR[Search10]; ?></option>
<option value="2"><?php echo $_STR[Search11]; ?></option>
</select>&nbsp;&nbsp;<?php echo $_STR[Search12]; ?>:&nbsp;
<select name="maxrows">
<option value="50">50</option>
<option value="100" selected>100</option>
<option value="250">250</option>
<option value="500">500</option>
</select></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />

<?php
show_results();
?>