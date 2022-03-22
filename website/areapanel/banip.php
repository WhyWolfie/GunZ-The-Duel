<!-- Coding By Sacker - GodOfWar -->
<?
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://auragz.zapto.org/");
        die();
    }

if (isset($_POST['submit'])){
    $type = clean_sql($_POST['type']);
    $id = clean_sql($_POST['id']);
    $UserAID = clean_sql($_POST['AID']);
    $ip = clean_sql($_POST['ip']);
    $reason = clean_sql($_POST['reason']);
    $custom = clean_sql($_POST['1']);
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
            msgbox("El Nombre De Usuario $id No Existe","index.php?do=banuser");
}else{
            $data = mssql_fetch_assoc($res);
            $userID = $data['UserID'];
            $UserAID = $data['AID'];
            if($_POST['C1'] == "ON"){
            }
            mssql_query_logged("UPDATE Account SET UGradeID = '253' WHERE UserID = '$userID'");
            mssql_query_logged("INSERT INTO AccountBan (AID, UserID, IP, BanReason, BanDate, Opened)VALUES('$UserAID', '$id', '$ip', '$reason', GETDATE(), '1')");
            msgbox("El Usuario $id ha sido Baneado de ip","index.php?do=banuser");
        }
    }else{
        $res = mssql_query_logged("SELECT * FROM Character WHERE Name = '$id'");
        if(mssql_num_rows($res) == 0){
            msgbox("El Nombre Del Personaje $id No Existe","index.php?do=banuser");
        }else{
            $res = mssql_query_logged("SELECT * FROM Character WHERE Name = '$id'");
            $data = mssql_fetch_assoc($res);
            $UserAID = $data['AID'];
            mssql_query_logged("UPDATE Account SET UGradeID = '253' WHERE AID = '$UserAID'");
            mssql_query_logged("INSERT INTO AccountBan (AID, UserID, IP, BanReason, BanDate, Opened)VALUES('$UserAID', '$id', '$ip', '$reason', GETDATE(), '1')");
            msgbox("The user with the character $id has been IP banned","index.php?do=banuser");
        }
    }

}

?>
									<form name="ipban" method="POST" action="index.php?do=banuser">
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
          <option selected value="1">Nombre de Usuario a Banear </option>
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
        <option selected value="Shotbot">Shotbot</option>
        <option value="Hacker">Hacker</option>
        <option value="NinjaStep(NS)">NinjaStep(NS)</option>
        <option value="Ofender al Staff">Ofender al Staff</option>
        <option value="Mamuteo">Mamuteo</option>
        <option value="UnderClock">Under Clock</option>
        <option value="Spam">Spam</option>
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