<?php


  ////////////////////
 // MAIN Functions //
////////////////////

function connect()
{
    global $_MSSQL;

    $resource = odbc_connect("Driver={SQL Server};Server={$_MSSQL[Host]}; Database={$_MSSQL[DBNa]}", $_MSSQL[User], $_MSSQL[Pass]) or die(odbc_errormsg());
    return $resource;

}

function num_rows($result)
{
    $count = 0;
    while( odbc_fetch_row($result) )
    {
        $count++;
    }
    odbc_fetch_row($result, 0);
    return $count;
}


function clean_sql($sql)
{
    $sql = str_replace("'","''",$sql);
    $sql = preg_replace(sql_regcase("/(from|xp_|execute|exec|sp_executesql|sp_|select|insert|delete|where|drop table|truncate|show tables|#|\*|--|\\\\)/"),"",$sql);
    $sql = strip_tags($sql);
    $sql = addslashes($sql);
    return $sql;
}

function redirect($url)
{
    printf("<meta http-equiv=\"Refresh\" content=\"0; url=%s\">", $url);
    die();
}

function writetolog($log)

{
    $date = date("d-m-y - H:i:s");
    $logfile = fopen("logs/log.txt","a+");
    $logtext = "$date - {$_SERVER['REMOTE_ADDR']} - StaffAID: {$_SESSION[AID]} : $log\r\n";
    fputs($logfile, $logtext);
	fclose($logfile);
}
function s() { return "PGEgc3R5bGU9ImNvbG9yOiMwOTY7IiBocmVmPSJodHRwOi8vc2Fja2Vyei5ibG9nc3BvdC5jb20v
Ij5QYW5lbCBjcmVhZG8gcG9yIFNhY2tlclo8L2E+"; }
function setmessage($title, $message)
{
    global $_STR;

    $_SESSION[Message] =
    "<br /><table border=\"1\" width=\"60%\" id=\"message\" style=\"border-collapse: collapse\">
	<tr>
		<td><b><i>{$_STR[Msg0]} $title</i></b></td>
	</tr>
	<tr>
		<td>$message</td>
	</tr>
</table><br />";

}

function showmessage()
{
    if( $_SESSION[Message] != "" )
    {
        printf("%s", $_SESSION[Message]);
        unset($_SESSION[Message]);
    }
}
function msgbox($text, $url){
echo "<body  bgcolor='#000000'><script>alert('$text');document.location = '$url'</script></body>"; 
}
function mssql_query_logged($query)
{

    //$f = fopen("logs/Querylogs.txt", "a+");
    //fprintf($f, "%s (mod_%s.php) - [AID=%s] %s [%s] - %s\r\n", $_SERVER[PHP_SELF],$_GET['do'], $_SESSION['AID'],  date("d-m-y - H:i:S"), $_SERVER['REMOTE_ADDR'], $query);
    //fclose($f);

    return mssql_query($query);
}

if(!function_exists("alertbox")){
function alertbox($text, $url)
{
    echo "<script>alert('$text');document.location = '$url'</script>";
    die("Javascript disabled");
} }
   ////////////////////
  // End OF         //
 // MAIN Functions //
////////////////////

  /////////////////////
 // LOGIN Functions //
/////////////////////

function login()
{
    global $_STR, $_CONFIG, $connection;
    $userid = clean_sql($_POST['userid']);
    $password = clean_sql($_POST['password']);

    if( $userid == "" || $password == "" )
    {
        setmessage("Login", $_STR[Login4]);
        redirect("index.php");
        die();
    }

    $loginquery = odbc_exec($connection, "
                    SELECT a.AID, a.UserID, a.UgradeID FROM {$_CONFIG[AccountTable]} a
                    INNER JOIN {$_CONFIG[LoginTable]} l ON a.AID = l.AID
                    WHERE l.UserID = '$userid' AND l.Password = '$password'
                    ");
		
    if( num_rows($loginquery) == 1 )
    {
        $logindata = odbc_fetch_row($loginquery);
        $ugradeid = odbc_result($loginquery, 3);
        if( $ugradeid != 255 )
        {
            setmessage("Login", $_STR[Login5]);
            redirect("index.php");
            die();
        }
        $_SESSION[AID] = odbc_result($loginquery, 1);
        $_SESSION[UserID] = odbc_result($loginquery, 2);
        $_SESSION[UGradeID] = $ugradeid;
        redirect("index.php");
    }
    else
    {
        setmessage("Login", $_STR[Login6]);
        redirect("index.php");
        die();
    }
}

function logout()
{
    unset($_SESSION[AID], $_SESSION[UserID], $_SESSION[UGradeID]);
	  redirect("http://sackerz.blogspot.com");
}

function check_ugradeid()
{
    global $_STR, $_CONFIG, $connection;

    $check = odbc_exec($connection, "SELECT UGradeID FROM {$_CONFIG[AccountTable]} WHERE AID = '{$_SESSION[AID]}'");
    odbc_fetch_row($check);
    $cugradeid = odbc_result($check, 1);
    if($cugradeid != 255)
    {
        printf( $_STR[Login5] );
        logout();
    }
    else
    {
        $_SESSION[UGradeID] = $check[0 && 2 && 3 && 4 && 5 && 6 && 7 && 8 && 253 && 254 && 255 && 100 && 101 && 102 && 103 && 104 && 105];
    }

}

   /////////////////////
  // End OF          //
 // LOGIN Functions //
/////////////////////

// 
$bienvenidos = "Bienvenidos al Panel HG V3 Creado por Sacker.";

?>