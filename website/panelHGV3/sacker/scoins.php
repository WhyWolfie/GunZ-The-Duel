<?php
if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }
if (isset($_POST['submit']))
{
    if ($_POST['UserID'] == "")
    {
        msgbox ("Please enter a UserID.","index.php?do=scoins");
    }
    
    if ($_POST['Coins'] == "")
    {
        msgbox ("Please enter a Coins Number.","index.php?do=scoins");
    }
    
    $ip = ''.($_SERVER['REMOTE_ADDR']);
    $userid = ($_POST['UserID']);
    $dgcoins = ($_POST['Coins']);

/////////////////////////////////////////////////////
// Insuficent Coins.
$res2 = mssql_query("SELECT Coins FROM Account WHERE AID = '".$_SESSION['AID']."'");
$acc = mssql_fetch_assoc($res2);
$result = $acc['Coins']-$item['CashPrice'];
// Insuficent Coins END.
////////////////////////////////////////////////////

    $result1 = mssql_query("SELECT Coins FROM Account WHERE UserID = '$useridby'");
    $result2 = mssql_query("SELECT Coins FROM Account WHERE UserID = '$userid'");

if (mssql_num_rows($result2) == 0)
{
msgbox ("Error, UserID not found.","index.php?do=scoins");
return;
}
    
    $row1 = mssql_fetch_assoc($result1);
    $row2 = mssql_fetch_assoc($result2);
    
    $coins1 = $row1['Coins'];
    $coins2 = $row2['Coins'];
    
    //if ($coins1 < $dgcoins)
    //{
    //    return;
    //}

    $coins1 -= $dgcoins;
    $coins2 += $dgcoins;
    
    mssql_query("UPDATE [Account] SET [Coins] = $coins1 WHERE UserID = '$useridby'");
    mssql_query("UPDATE [Account] SET [Coins] = $coins2 WHERE UserID = '$userid'");
    done();
}
else gift();

?>
<?php
function gift()
{
?>
<form name="reg" method="POST" action="index.php?do=scoins">
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
<body bgcolor="#323232">

                    <div align="center">
                        <table border="1" style="border-collapse: collapse" width="461" height="100%">
                                        <tr>
                                          <td colspan="2">Enviar Coins</td>
                                      </tr>
                                        <tr>
                                          <td width="162">&middot;<span lang="es"> User ID<font color="#FF9933">*</font></span></td>
                                          <td width="254"><input type="text" name="UserID" id="UserID"></td>
                                      </tr>
                                        <tr>
                                          <td>&middot;<span lang="es"> Coins <font color="#FF9933">*</font></span></td>
                                          <td><select size="1" name="Coins" id="Coins">
						                              <option value="10">10 Coins</option>
                                                      <option value="50" selected>50 Coins</option>
                                                      <option value="100">100 Coins</option>
                                                      <option value="150">150 Coins</option>
                                                      <option value="200">200 Coins</option>
                                                      <option value="250">250 Coins</option>
                                                      <option value="300">300 Coins</option>
                                                      <option value="350">350 Coins</option>
                                                      <option value="400">400 Coins</option>
                                                      <option value="450">450 Coins</option>
                                                      <option value="500">500 Coins</option>
											</select></td>
                                      </tr>
                                        <tr>
                                          <td colspan="2"><div align="center">
                                            <form name="form1" method="post" action="">
                                              <label>
                                              <input type="submit" name="submit" id="submit" value="Enviar">
                                              </label>
                                            </form>
                                            </div></td>
                                      </tr>
                                    </table>
                    </div>
                    </form>
<?php
}
?>
<?php
function done()
{
msgbox ("Coins enviados correctamente.","index.php?do=scoins");
?>

<?php
}
?> 
<br />
<br />