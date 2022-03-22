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
    msgbox("Su Noticia fue agregado con exito!^^ By Sacker","index.php?do=news");
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
    <td width="432" colspan="3">Agregar nueva noticia ^^</td>
  </tr>
  <tr>
    <td width="432" align="right"> Title</td>
    <td width="432">&nbsp; </td>
    <td width="432">
      <input type="text" name="title" size="40"></td>
  </tr>
  <tr>
    <td width="432" align="right"> Tipo</td>
    <td width="432">&nbsp; </td>
    <td width="432">
      <select size="1" name="type">
        <option selected value="1">News and updates xD </option>
        <option value="2">Forun derecho  </option>
    </select></td>
  </tr>
  <tr>
    <td width="432" align="right" valign="top"> Text</td>
    <td width="432">&nbsp; </td>
    <td width="432">
      <textarea rows="8" name="text" cols="35"></textarea></td>
  </tr>
  <tr>
    <td width="432">&nbsp; </td>
    <td width="432">&nbsp; </td>
    <td width="432">Panel By SackerZ </td>
  </tr>
  <tr>
    <td width="432" colspan="3">
      <p align="center">
        <input type="submit" value="Enviar Noticia" name="submit">
    </td>
  </tr>
</table>
</form>
<?
}
?>