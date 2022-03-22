<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: index.php");
        die();
    }
    
function display_notes()
{
    $file = fopen("logs/notes.txt", "r");
    $text = fread($file, 102400);
    echo $text;
    fclose($file);
}

if( isset($_POST['sendnote']) )
{
    $note = trim($_POST['note']);
    if( empty($note) )
    {
        setmessage("Notepad", "You can't send an empty note");
        redirect("index.php?do=notepad");
        die();
    }
    $file = fopen("logs/notes.txt", "r");
    $text = fread($file, 102400);
    fclose($file);
    $file = fopen("logs/notes.txt", "w");
    $note = sprintf("%s: %s\r\n%s", $_SESSION[UserID], $note, $text);
    fputs($file, $note);
    fclose($file);
}

showmessage();
?>

<table border="1" width="50%" style="border-collapse: collapse" id="table1">
<form method="post" action="index.php?do=notepad" name="note">
	<tr>
		<td colspan="2" align="center"><?php echo $_STR[Notepad0]; ?></td>
	</tr>
	<tr>
		<td align="center" width="15%"><?php echo $_STR[Notepad1]; ?></td>
		<td><input type="text" size="40" name="note" /></td>
	</tr>
	<tr>
		<td colspan="2">&nbsp;</td>
	</tr>
	<tr>
		<td colspan="2" align="center"><input type="submit" name="sendnote" value="<?php echo $_STR[Notepad2]; ?>" /></td>
	</tr>
	<tr>
		<td colspan="2">&nbsp;</td>
	</tr>
	<tr>
		<td colspan="2" align="center"><?php echo $_STR[Notepad3]; ?></td>
	</tr>
	<tr>
		<td colspan="2">&nbsp;</td>
	</tr>
	<tr>
		<td colspan="2" align="center">
		<textarea name="notes" cols="50" rows="20" readonly><?php display_notes(); ?></textarea></td>
	</tr>
</form>
</table>
