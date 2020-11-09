<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: index.php");
        die();
    }

    showmessage();

    if( isset($_POST['allowall']) )
    {
        odbc_exec($connection, "UPDATE CustomIP SET IsBlock = 0");
        odbc_exec($connection, "UPDATE BlockCountryCode SET IsBlock = 0");

        writetolog( $_STR[Log26] );
        setmessage("Allow countries", $_STR[Country6]);
        redirect("index.php?do=country");
        die();
    }
    elseif( isset($_POST['blockall']) )
    {
        odbc_exec($connection, "UPDATE CustomIP SET IsBlock = 1");
        odbc_exec($connection, "UPDATE BlockCountryCode SET IsBlock = 1");

        writetolog( $_STR[Log27] );
        setmessage("Block countries", $_STR[Country7]);
        redirect("index.php?do=country");
        die();
    }
    elseif( isset($_POST['allow']) )
    {
        $cc3 = clean_sql($_POST['cc3']);

        odbc_exec($connection, "UPDATE CustomIP SET IsBlock = 0 WHERE CountryCode3 = '$cc3'");
        odbc_exec($connection, "UPDATE BlockCountryCode SET IsBlock = 0 WHERE CountryCode3 = '$cc3'");

        writetolog( sprintf($_STR[Log28], $cc3) );
        setmessage("Allow country", $_STR[Country8]);
        redirect("index.php?do=country");
        die();
    }
    elseif( isset($_POST['block']) )
    {
        $cc3 = clean_sql($_POST['cc3']);

        odbc_exec($connection, "UPDATE CustomIP SET IsBlock = 1 WHERE CountryCode3 = '$cc3'");
        odbc_exec($connection, "UPDATE BlockCountryCode SET IsBlock = 1 WHERE CountryCode3 = '$cc3'");

        writetolog( sprintf($_STR[Log29], $cc3) );
        setmessage("Block country", $_STR[Country9]);
        redirect("index.php?do=country");
        die();
    }
    elseif( isset($_POST['newmessage']) )
    {
        $message = clean_sql($_POST['message']);
        if( strlen($message) > 128 )
        {
            setmessage("New Message", "Message too long");
            redirect("index.php?do=country");
            die();
        }

        odbc_exec($connection, "UPDATE CustomIP SET Comment = '$message'");
        writetolog( sprintf($_STR[Log30], $message) );
        setmessage("New Message", $_STR[Country10]);
        redirect("index.php?do=country");
        die();

    }
    else
    {
        $countryq = odbc_exec($connection, "SELECT * FROM CountryCode(nolock)");
        $countrylist = "";
        while( $data = odbc_fetch_object($countryq) )
        {
            $countrylist .= "<option value=\"{$data->CountryCode3}\">".ucfirst(strtolower($data->CountryName))."</option>";
        }
    }

?>


<table border="1" style="border-collapse: collapse" id="allowall">
<tr><td colspan="2"><b><?php echo $_STR[Country0]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=country">
<tr>
    <td width="450" align="center">
    <input type="submit" name="allowall" value="<?php echo $_STR[Country1]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="blockall">
<tr><td colspan="2"><b><?php echo $_STR[Country2]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=country">
<tr>
    <td width="450" align="center">
    <input type="submit" name="blockall" value="<?php echo $_STR[Country3]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="allow">
<tr><td colspan="2"><b><?php echo $_STR[Country4]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=country">
<tr>
    <td width="450" align="center">
    <select name="cc3">
    <?php
    echo $countrylist;
    ?>
    </select>
    <input type="submit" name="allow" value="<?php echo $_STR[Country1]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="block">
<tr><td colspan="2"><b><?php echo $_STR[Country5]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=country">
<tr>
    <td width="450" align="center">
    <select name="cc3">
    <?php
    echo $countrylist;
    ?>
    </select>
    <input type="submit" name="block" value="<?php echo $_STR[Country3]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table>
<br />
<table border="1" style="border-collapse: collapse" id="newmessage">
<tr><td colspan="2"><b><?php echo $_STR[Country11]; ?></b></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<form method="post" action="index.php?do=country">
<tr>
    <td width="450" align="center">
    <input type="text" name="message" size="50" /><br /><br />
    <input type="submit" name="newmessage" value="<?php echo $_STR[Country12]; ?>" />
    </td>
</tr>
<tr><td colspan="2">&nbsp;</td></tr>
</form>
</table