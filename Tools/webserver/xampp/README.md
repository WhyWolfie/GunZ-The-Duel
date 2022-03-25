<b>[xampp installation tutorial]</b><br>
[files]<br>
  - https://sourceforge.net/projects/xampp/files/XAMPP%20Windows/1.7.3/xampp-win32-1.7.3.exe/download (xampp-win32-1.7.3.exe)
  - alternative: https://archive.org/details/xampp-win32-1.7.3
 
 
1. Download -> xampp-win32-1.7.3.exe
2. Install -> xampp-win32-1.7.3.exe
3. Start -> XAMPP Control Panel
4. Install the apache, do not start the apache yet!
5. Go to your php.ini location at: C:\xampp\php\php.ini
6. Find short_open_tag till you see this: Short_open_tag = Off -> On
7. Find php_mssql.dll till you see this, remove ';' (;extension=php_mssql.dll -> extension=php_mssql.dll)
8. If you are using PDO MSSQL find this, remove ';' (;extension=php_pdo_mssql.dll -> extension=php_pdo_mssql.dll)
9. Start the apache!
10. Go to your htdocs located at : C:\xampp\htdocs
11. Make a file called 'index.php' (without the '')
12. place this script below
  
            <?php

            if (function_exists('mssql_fetch_row')) {
            echo "I guess it worked hum?.<br />\n";
            } else {
            echo "Nah, you need to uninstall the version of xampp you were using.\n";
            }

            ?>
