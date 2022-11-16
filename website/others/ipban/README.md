///// Modulo Creado Por Zalish 

Instrucciones: -> Leer Con Atencion.

1.- Descomprime la carpeta -> IpBan <- en donde tengas la carpeta WWW de tu
AppServ. Ej: C:\Appserv\WWW -> Quedarioa C:\Appserv\www\IpBan

2.- Ejecuta el archivo WebIpBan.sql, selecciona la ejecucion a GunzDB o el nombre de tu base
de datos.

3.- Modifica tu Index.php de la web de tu gunz,colocale include "IpBan/ipban.php";
checar_baneo_ip($_SERVER['REMOTE_ADDR']);  Por ejemplo el mio quedo asi:

//////////

<?
include "secure/config.php";
include "secure/functions.php";
include "secure/anti_inject.php";
include "secure/sql_check.php";
include "secure/ipban.php";
include "secure/ban.php";
include "secure/shield.php";
include "IpBan/ipban.php";
checar_baneo_ip($_SERVER['REMOTE_ADDR']);

//////////


4.- Modifica el archivo dentro de la caropeta IpBan llamado: managerip.php
colocandole los datos que quieras para poder acceder al modulo de banear // desbanear
ips, las variables son: $usuario_para_acceder , y $clave_para_acceder.

el link para banear o desbanear ip, si hiciste los pasos anteriores seria ->
http://localhost/ipban/managerip.php

introduces los datos que configuraste, y listo tu modulo de IpBan estaria listo!
