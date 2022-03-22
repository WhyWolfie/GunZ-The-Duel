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
                                          <td>&middot;<span lang="es"> Coins <font color="#FF9933">*</font></span></td>
                                          <td><select size="1" name="DonatorCoins" id="DonatorCoins">
						                              <option value="10">10 DCoins</option>
                                                      <option value="50" selected>50 DCoins</option>
                                                      <option value="75">75 DCoins</option>
                                                      <option value="100">100 DCoins</option>
                                                      <option value="150">150 DCoins</option>
                                                      <option value="200">200 DCoins</option>
                                                      <option value="250">250 DCoins</option>
                                                      <option value="300">300 DCoins</option>
                                                      <option value="350">350 DCoins</option>
                                                      <option value="400">400 DCoins</option>
                                                      <option value="450">450 DCoins</option>
                                                      <option value="500">500 DCoins</option>
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
msgbox ("Coins enviados correctamente.","index.php?do=dcoins");
?>

<?php
}
?> 
<br />
<br />