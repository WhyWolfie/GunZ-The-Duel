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
        msgbox ("Please enter a UserID.","index.php?do=dcoins");
    }
    
    if ($_POST['DonatorCoins'] == "")
    {
        msgbox ("Please enter a DCoins Number.","index.php?do=dcoins");
    }
    
    $ip = ''.($_SERVER['REMOTE_ADDR']);
    $userid = ($_POST['UserID']);
    $dgcoins = ($_POST['DonatorCoins']);

/////////////////////////////////////////////////////
// Insuficent Coins.
$res2 = mssql_query("SELECT DonatorCoins FROM Account WHERE AID = '".$_SESSION['AID']."'");
$acc = mssql_fetch_assoc($res2);
$result = $acc['DonatorCoins']-$item['CashPrice'];
// Insuficent Coins END.
////////////////////////////////////////////////////

    $result1 = mssql_query("SELECT DonatorCoins FROM Account WHERE UserID = '$useridby'");
    $result2 = mssql_query("SELECT DonatorCoins FROM Account WHERE UserID = '$userid'");

if (mssql_num_rows($result2) == 0)
{
msgbox ("Error, UserID No existe.","index.php?do=dcoins");
return;
}
    
    $row1 = mssql_fetch_assoc($result1);
    $row2 = mssql_fetch_assoc($result2);
    
    $coins1 = $row1['DonatorCoins'];
    $coins2 = $row2['DonatorCoins'];
    
    //if ($coins1 < $dgcoins)
    //{
    //    return;
    //}

    $coins1 -= $dgcoins;
    $coins2 += $dgcoins;
    
    mssql_query("UPDATE [Account] SET [DonatorCoins] = $coins1 WHERE UserID = '$useridby'");
    mssql_query("UPDATE [Account] SET [DonatorCoins] = $coins2 WHERE UserID = '$userid'");
	writetolog( sprintf($_STR[Log31], $userid, $dgcoins));
    done();
}
else gift();

?>
<?php
function gift()
{
?>
<form name="reg" method="POST" action="index.php?do=dcoins">
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
<body bgcolor="#323232">

                    <div align="center">
                        <table border="1" style="border-collapse: collapse" width="461" height="100%">
                                        <tr>
                                          <td colspan="2">Enviar Donator Coins</td>
                                      </tr>
                                        <tr>
                                          <td width="162">&middot;<span lang="es"> UserID<font color="#FF9933">*</font></span></td>
                                          <td width="254"><input type="text" name="UserID" id="UserID"></td>
                                      </tr>
                                        <tr>
                                          <td>&middot;<span lang="es"> CANTIDAD <font color="#FF9933">*</font></span></td>
                                          <td><select size="1" name="DonatorCoins" id="DonatorCoins">
						                              <option value="10" selected>10 Donator C.</option>
                                                      <option value="30">30 Donator C.</option>
                                                      <option value="55">55 Donator C.</option>
                                                      <option value="105">105 Donator C.</option>
                                                      <option value="210">210 Donator C.</option>
                                                      <option value="315">315 Donator C.</option>
                                                      <option value="400">400 Donator C.</option>
                                                      <option value="420">420 Donator C.</option>
                                                      <option value="455">455 Donator C.</option>
                                                      <option value="500">500 Donator C.</option>
                                                      <option value="550">550 Donator C.</option>
                                                      <option value="600">600 Donator C.</option>
                                                      <option value="1000">1000 Donator C.</option>
                                                      <option value="2000">2000 Donator C.</option>
                                                      <option value="1000000">100000 Donator C.</option>
                                                      <option value="200000">200000 Donator C.</option>
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
msgbox ("Donator C. Enviado Correctamente","index.php?do=dcoins");
?>

<?php
}
?> 
<br />
<br />