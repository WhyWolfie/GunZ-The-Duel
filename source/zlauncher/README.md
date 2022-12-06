Set your Project Build on: Release_USA <br>
Only port 80 works <br>
Open(NewAppDlg.cpp) <br>
Change STR_ADDRESS_REAL = "your ip-address" <br>
Change STR_ADDRESS_ALPHA = "your ip-address" <br>
Change STR_WEBPAGE_URL = "too your website" <br> 
Create a folder in your appserv/xampp folder, "GunZUpdate" Use ZPatchBuilder to build your patches there. <br>


    // Settings of USA
    #ifdef LOCALE_NHNUSA
    #include "ZNHNModule.h"
    #define STR_GUNZ_PROCESS_NAME				"TheDuel"
    #define STR_GUNZ_EXCUTE_FILENAME			"TheDuel.exe"
    #define STR_LAUNCHER_EXCUTE_FILENAME		"GunzLauncher.exe"
    #define STR_PATCHINFO_FILENAME				"patch.xml"
    #define STR_WEBPAGE_URL						"http://jurienhamaker.net" //Your launcher start page url.
    #define STR_ADDRESS_REAL					"127.0.0.1" //Your ip address here
    #define STR_ADDRESS_ALPHA					"127.0.0.1" //Your ip address here
    #define STR_GUNZ_PROCESS_NAME				"Gunz"
    #define STR_GUNZ_EXCUTE_FILENAME			"Gunz.exe"
    #define STR_LAUNCHER_EXCUTE_FILENAME		"GunzLauncher.exe"
    #define STR_PATCHINFO_FILENAME				"patch.xml"
    #define STR_WEBPAGE_URL						"http://127.0.0.1" //Your launcher start page url.
    #define STR_ADDRESS_REAL					"127.0.0.1" //Your ip address here
    #define STR_ADDRESS_ALPHA					"127.0.0.1" //Your ip address here
    #define STR_DIRECTORY_REAL					"GunZUpdate" //Your path for yout patch
    #define STR_DIRECTORY_ALPHA					"GunZUpdate" //Your path for yout patch test
    #endif LOCALE_NHNUSA





![launcher](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/zlauncher/launcher.png)
