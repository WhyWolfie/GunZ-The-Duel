<?
    if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }
?>
<?
include_once '.../config/config.php';
if(!isset($_POST['submit'])){
}else
?>
<style type="text/css">
.xd {
	color: #F00;
}
.xd {
	color: #066;
}
</style>

<form method="post" name="from">
<table width="259" border="1">
  <tr>
    <th width="54" scope="col">Buscar</th>
    <th width="156" scope="col">
    <select onchange="this.form.submit()" name="type" >
    <option value="255">Administradores</option>
    <option value="254">Desarrollador</option>
    <option value="253">Usuarios con Banned</option>
    <option value="252">Moderador</option>
    <option value="2">User Con jjang</option>
    </select></th>
    <th width="27" scope="col">
    <input type="submit" name="submit" value="Buscar">
    
    </th>
  </tr>
</table><br>
</form>
<table width="739" border="1">
  <tr>
    <th width="45" scope="col">AID</th>
    <th width="134" scope="col">UserID</th>
    <th width="71" scope="col">UGradeID</th>
    <th width="95" scope="col">Nombre</th>
    <th width="161" scope="col">Pregunta </th>
    <th width="193" scope="col">Respuesta</th>
  </tr>
<tr>

<?
{
	
$q = $_POST['type'];
if($q <= 0){
	die();
	}else{
$tp = mssql_query("SELECT * From Account WHERE UGradeID = '".$q."'");
while($acc = mssql_fetch_object($tp)){
	
	
?>
  
    <th class="xd" scope="col"><?=$acc->AID;?></th>
    <th class="xd" scope="col"><?=$acc->UserID?></th>
    <th class="xd" scope="col"><?=$acc->UGradeID?></th>
    <th class="xd" scope="col"><?=$acc->Name?></th>
    <th class="xd" scope="col"><?=$acc->sa?></th>
    <th class="xd" scope="col"><?=$acc->sq?></th>
 

 </tr>
 <? }}}?>
</table>
