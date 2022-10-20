Hi again, Today i am going tutorial how to protect your client files so please follow cautiously! <br>

1)First of all please download this program and install: [hashcalc](https://github.com/WhyWolfie/GunZ-The-Duel/raw/master/Tools/hashcalc/hashcalc.zip) <br>
*This program uses for calculate our files SHA1 with HMAC key. <br>
2)After you install HashCalc open it and enable the check box of SHA1 and also of HMAC if disabled. <br>
3)The HMAC key that MAIET set on Gunz source is "gunzkingJJang": <br>


    (HMAC_SHA1.h)

    #define GUNZ_HMAC_KEY "gunzkingJJang"
    
*If you want you can change this string to anything you want. <br>

4)Now, load any file you want to "protect" on HashCalc example fmod.dll and then add on the HMAC <br>
this key: gunzkingJJang <br>

Picture: Soon<br>

This is my fmod.dll sha1: 888f1f7b7e3c43384f4b80b577fe091ac045383c <br>
So we should change sha1 to: <br>
0x88,0x8f,0x1f,0x7b,0x7e,0x3c,0x43,0x38,0x4f,0x4b,0x80,0xb5,0x77,0xfe,0x09,0x1a,0xc0,0x45,0x38,0x3c <br>

Open Main.cpp and search for: <br>

BYTE SHA_fmod[20] = <br>

and here you can add more files to check, Example: <br>

    //Check for system.mrs
    BYTE SHA_system[20] = {here your sha1};

    !CheckDll("system.mrs", SHA_system) ||




Credits: MAIET and Sahar042 for this tutorial.
