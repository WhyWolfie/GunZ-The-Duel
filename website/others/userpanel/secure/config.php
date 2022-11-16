<?php
//Créditos à Aula GunZ
$gunzname = 'Aula GunZ';
$link = mssql_connect("FILGUEIR-E7C4C0\SQLEXPRESS","sa","123456");
mssql_select_db("GunzDB");
$opened = 1;
if($opened == 0){
   header("Location: Maintenance.php");
   }
?>