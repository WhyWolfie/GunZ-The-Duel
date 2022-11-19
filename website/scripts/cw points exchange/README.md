    <?//Script By: Gaspar

    // Funcao para filtrar (Anti-SQL-Injection)Function Filtrrar($str){
        $caracters = array("'", "!", "from", "select", "insert", "delete", "where", "drop table", "show tables");
        $blank = "";
    return str_replace($caracters, $blank, $str);
    }$login22 = Filtrrar($_SESSION["login"]);$etapa22 = Filtrrar($_GET["etapa"]);

    if (!(isset($_SESSION["login"])))
    {
    die ("Desculpe, Para acessar esta pagina voce prescisa estar logado!");
    }else{

    if($etapa22 == 0){?><form id="ev_coins" name="ev_coins" method="post" action="?gz=ev_coins&etapa=1">
    Personagem:
    <select name="cid" class="text">
    <?
    $pegaLogin = mssql_fetch_row(mssql_query("SELECT AID FROM LOGIN WHERE UserID = '$login22'"));$c = mssql_query("SELECT CID,NAME FROM CHARACTER WHERE AID = '$pegaLogin[0]' AND DeleteFlag = 0");

    while($array = mssql_fetch_row($c))
    {
        echo '<option value="'.$array[0].'">'.$array[1].'</option>';
    }?></select><br><br>
    <input type="submit" name="ev_coins" value="Proximo ->" />
    </form>
    <?}

    if($etapa22 == 1){$cid22 = Filtrrar($_POST["cid"]);$busca1 = mssql_query("SELECT ContPoint FROM ClanMember WHERE CID = '$cid22'");$busca2 = mssql_fetch_row($busca1);

    if (!(isset($busca2[0])))
    {
    die ("Este Personagem Não Pertence a Nenhum Clan");
    }else{$_SESSION["CID"] = $cid22;
    echo '
    <form id="ev_coins" name="ev_coins" method="post" action="?gz=ev_coins&etapa=2">';
    echo "Olá $login22 você tem $busca2[0] Pontos com o personagem selecionado para trocar em EvCoins.<br><br>";
    echo "Quantos pontos deseja trocar?<br>";
    echo '
    <input type="text" id="pontos" value="'.$busca2[0].'" class="log_field" size="3" name="pontos" value="" maxlength="3"><br><br>';
    echo '
    <input type="submit" name="ev_coins" value="Trocar" />';
    echo '</form>';
    }
    }

    if($etapa22 == 2){$pontos = Filtrrar($_POST["pontos"]);$cid23 = Filtrrar($_SESSION["CID"]);$busca3 = mssql_query("SELECT ContPoint FROM ClanMember WHERE CID = '$cid23'");$busca4 = mssql_fetch_row($busca3);

    if($busca4[0] < $pontos){
    echo "Você não possui essa quantia de coins. Espertinho =P";
    }else{mssql_query("update Account set EvCoins=EvCoins +$pontos where UserID='$login22'");mssql_query("update ClanMember set ContPoint=ContPoint -$pontos where CID='$cid23'");
    echo "Troca realizada com sucesso!";


    }

    }

    }?>
    
• To remove the function to check if you are logged in • <br>

    if (!(isset($_SESSION["login"])))
    {
    die ("Desculpe, Para acessar esta pagina voce prescisa estar logado!");
    }else{  

And there, on the penultimate line, remove: <br>

    }

• Changing the Coins column • <br>
If your column is not "EvCoins" and is not in the "Account" table, just change this: <br>

    mssql_query("update Account set EvCoins=EvCoins +$pontos where UserID='$login22'");  

• If your site does not have the Config • <br>
If your site does not have the config included in index.php, the script will give an error. <br>
Then just add the following code: <br>

    include "pasta da sua config/config.php";  

Under:

    <?//Script By: Gaspar

• Changing the variable ?gz= • <br>

If your site is not ?gz= or another such as ?go= just change this: <br>

    <form id="ev_coins" name="ev_coins" method="post" action="?gz=ev_coins&etapa=1">  

and <br>
PHP code: <br>

    <form id="ev_coins" name="ev_coins" method="post" action="?gz=ev_coins&etapa=2">  








