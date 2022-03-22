<!-- Coding By Sacker - GodOfWar -->
<?
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }

if (isset($_POST['submit'])){
    $type = clean_sql($_POST['type']);
    $id = clean_sql($_POST['id']);
    $gmid = clean_sql($_POST['gmid']);
    $ip = clean_sql($_POST['ip']);
    $reason = clean_sql($_POST['reason']);
    $custom = clean_sql($_POST['cstom']);
    //--
    if($reason == 1){
        $reason = $custom;
        $custom = str_replace("
        ","</br>",$custom);
    }
    //--
    if ($type == 1){
        $res = mssql_query_logged("SELECT * FROM Account WHERE UserID = '$id'");
        if(mssql_num_rows($res) == 0){
            msgbox("UserID $id doesnt exist","index.php?do=banip");
}else{
            $data = mssql_fetch_assoc($res);
            $userID = $data['UserID'];
            $UserAID = $data['AID'];
            if($_POST['C1'] == "ON"){
            }
            mssql_query_logged("UPDATE Account SET UGradeID = '253' WHERE UserID = '$userID'");
            mssql_query_logged("INSERT INTO Banneduser (GMUserID, UserID, IP, BanReason, BanDate, IPBANMUTE)VALUES('$gmid', '$id', '$ip', '$reason', GETDATE(), 'Ban')");
            msgbox("The user with the ID $id has been IP banned","index.php?do=banip");
        }
    }else{
        $res = mssql_query_logged("SELECT * FROM Character WHERE Name = '$id'");
        if(mssql_num_rows($res) == 0){
            msgbox("The character $id doesnt exist","index.php?do=banip");
        }else{
            $res = mssql_query_logged("SELECT * FROM Character WHERE Name = '$id'");
            $data = mssql_fetch_assoc($res);
            $UserAID = $data['AID'];
            mssql_query_logged("UPDATE Account SET UGradeID = '253' WHERE AID = '$UserAID'");
            mssql_query_logged("INSERT INTO Banneduser (GMUserID, UserID, IP, BanReason, BanDate, IPBANMUTE)VALUES('$gmid', '$id', '$ip', '$reason', GETDATE(), 'Ban')");
            msgbox("The user with the character $id has been IP banned","index.php?do=banip");
        }
    }

}

?>
									<form name="ipban" method="POST" action="index.php?do=banip">
<table border="1" style="border-collapse: collapse" width="454" height="100%">
  <tr>
    <td width="432" colspan="3">Banear IP a un Usuario</td>
  </tr>
  <tr>
    <td width="432">&nbsp; </td>
    <td width="432">&nbsp; </td>
    <td width="432">&nbsp; </td>
  </tr>
  <tr>
    <td width="432">
      <p align="right">GM User ID</td>
    <td width="432">&nbsp; </td>
    <td width="432">
      <input type="text" name="gmid" size="26">
&nbsp; </td>
  </tr>
  <tr>
    <td width="432">
      <p align="right">
        <select size="1" name="type">
          <option selected value="1">User ID </option>
          <option value="2">Character Name </option>
        </select>
    </td>
    <td width="432">&nbsp; </td>
    <td width="432">
      <input type="text" name="id" size="26">
&nbsp; </td>
  </tr>
  <tr>
    <td width="432">
      <p align="right">User IP</td>
    <td width="432">&nbsp; </td>
    <td width="432">
      <input type="text" name="ip" size="26">
&nbsp; </td>
  </tr>
  <tr>
    <td width="432">
      <p align="right">Razon de Ban </td>
    <td width="432">&nbsp; </td>
    <td width="432">
      <select size="1" name="reason" onchange="UpdateCustom()">
        <option selected value="Modificando Cliente">Modificando Cliente</option>
        <option value="Trampas o hacker">Hack o Trampas</option>
        <option value="Insulto a Staff">Insulto a Staff</option>
        <option value="Insulto a Player">Insulto a Player</option>
        <option value="Swap / etc">Swap / etc. </option>
        <option value="Sin razon especifico">Sin razon especifico</option>
        <option value="1">Otros, especifica abajo</option>
    </select></td>
  </tr>
  <tr>
    <td width="432">&nbsp;</td>
    <td width="432">&nbsp;</td>
    <td width="432">
      <textarea disabled rows="9" name="cstom" cols="30"></textarea></td>
  </tr>
  <tr>
    <td width="432">&nbsp;</td>
    <td width="432">&nbsp;</td>
    <td width="432">&nbsp;</td>
  </tr>
  <tr>
    <td width="432" colspan="3">
      <p align="center">
        <input type="submit" value="IP Ban User" name="submit">
    </td>
  </tr>
</table></form>
<br /><br />