<?
if( !ereg("index.php", $_SERVER['PHP_SELF']) )
    {
        header("Location: http://sackerz.blogspot.com/");
        die();
    }
if(isset($_POST['submit'])){
    $title = clean_sql($_POST['title']);
    $type = clean_sql($_POST['type']);
    $text = clean_sql($_POST['text']);
    $user = $_SESSION['UserID'];
    mssql_query_logged("INSERT INTO IndexContent ([Type], [User], [Date], [Text], [Title])VALUES($type, '$user', GETDATE(), '$text', '$title')");
    msgbox("La Noticia Fue Agregada","index.php?do=news");
}else{
?>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
<body bgcolor="#323232">
<form method="POST" action="index.php?do=news">
<table width="454" height="100%" border="1" align="center" style="border-collapse: collapse">
  <tr>
    <td width="432" colspan="3">Agregar Noticia,En Esta Seccion Se podra poner Noticia Via Foro, con tan solo poniendo la URL del Sitio.</td>
  </tr>
  <tr>
    <td width="432" align="right"> Titulo</td>
    <td width="432"></td>
    <td width="432">
      <input type="text" name="title" size="40"></td>
  </tr>
  <tr>
    <td width="432" align="right"> Tipo</td>
    <td width="432">&nbsp; </td>
    <td width="432">
      <select size="1" name="type">
        <option selected value="1">NEWS & UPDATES</option>
        <option value="2">LATESTS FORUM POST</option>
    </select></td>
  </tr>
  <tr>
    <td width="432" align="right" valign="top">URL De la Noticia</td>
    <td width="432">&nbsp; </td>
    <td width="432">
      <textarea rows="8" name="text" cols="35"></textarea></td>
  </tr>
  <tr>

  </tr>
  <tr>
    <td width="432" colspan="3">
      <p align="center">
        <input type="submit" value="Aceptar" name="submit">
    </td>
  </tr>
</table>
</form>
<?
}
?>