<?php
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        die();
    }
if (isset($_POST['submit']))
{
    if ($_POST['UserID'] == "")
    {
        msgbox ("Porfavor Inserte un UserID","index.php?do=evcoins");
    }
    
    if ($_POST['EventCoins'] == "")
    {
        msgbox ("Porfavor Inserte una cantidad de ECoins","index.php?do=evcoins");
    }
    
    $ip = ''.($_SERVER['REMOTE_ADDR']);
    $userid = ($_POST['UserID']);
    $dgcoins = ($_POST['EventCoins']);

/////////////////////////////////////////////////////
// Insuficent Coins.
$res2 = mssql_query("SELECT EventCoins FROM Account WHERE UserID = '".$_SESSION['AID']."'");
$acc = mssql_fetch_assoc($res2);
$result = $acc['EventCoins']-$item['CashPrice'];
// Insuficent Coins END.
////////////////////////////////////////////////////

    $result1 = mssql_query("SELECT EventCoins FROM Account WHERE UserID = '$useridby'");
    $result2 = mssql_query("SELECT EventCoins FROM Account WHERE UserID = '$userid'");

if (mssql_num_rows($result2) == 0)
{
msgbox ("Error, AID not found.","index.php?do=evcoins");
return;
}
    
    $row1 = mssql_fetch_assoc($result1);
    $row2 = mssql_fetch_assoc($result2);
    
    $coins1 = $row1['EventCoins'];
    $coins2 = $row2['EventCoins'];
    
    //if ($coins1 < $dgcoins)
    //{
    //    return;
    //}

    $coins1 -= $dgcoins;
    $coins2 += $dgcoins;
    
    mssql_query("UPDATE [Account] SET [EventCoins] = $coins1 WHERE UserID = '$useridby'");
    mssql_query("UPDATE [Account] SET [EventCoins] = $coins2 WHERE UserID = '$userid'");
    done();
}
else gift();

?>
<?php
function gift()
{
?>
<form name="reg" method="POST" action="index.php?do=evcoins">
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
<body bgcolor="#323232">

                    <div align="center">
                        <table border="1" style="border-collapse: collapse" width="461" height="100%">
                                        <tr>
                                          <td colspan="2">Enviar Event Coins</td>
                                      </tr>
                                        <tr>
                                          <td width="162">&middot;<span lang="es"> UserID <font color="#FF9933">*</font></span></td>
                                          <td width="254"><input type="text" name="UserID" id="UserID"></td>
                                      </tr>
                                        <tr>
                                          <td>&middot;<span lang="es"> CANTIDAD <font color="#FF9933">*</font></span></td>
                                          <td><select size="1" name="EventCoins" id="EventCoins">
						                              <option value="10" selected>10 ECoins</option>
                                                      <option value="50">50 ECoins</option>
                                                      <option value="75">75 ECoins</option>
                                                      <option value="100">100 ECoins</option>
                                                      <option value="150">150 ECoins</option>
                                                      <option value="200">200 ECoins</option>
                                                      <option value="250">250 ECoins</option>
                                                      <option value="300">300 ECoins</option>
                                                      <option value="350">350 ECoins</option>
                                                      <option value="400">400 ECoins</option>
                                                      <option value="450">450 ECoins</option>
                                                      <option value="500">500 ECoins</option>
                                                      <option value="1000">1000 ECoins</option>
											</select></td>
                                      </tr>
                                        <tr>
                                          <td colspan="2"><div align="center">
                                            <form name="form1" method="post" action="">
                                              <label>
                                              <input type="submit" name="submit" id="submit" value="Aceptar">
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
msgbox ("Event Coins enviados correctamente.","index.php?do=evcoins");
?>

<?php
}
?> 
<br />
<br />