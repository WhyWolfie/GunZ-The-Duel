I apologize if this seems trivial, but I get ALOT of requests for assistance debugging code. This is code will allow the visual studio debugger to natively launch at runtime. (No more mlog BS);

It should work out of the box, some tweaks might be required. I had to edit out lots of what I had inside of my source to slim it down to just 3 files xD.

Open (ZgameInterface.cpp)


    bool ZGameInterface::OnCreate(ZLoadingProgress *pLoadingProgress)
    {
      mlog( "game interface create success.\n" );
      InitGunZConsole(); // ADD HERE at the very bottom!
      return true;
    }

also add <br>

    void InitGunZConsole();

to GunZConsole.h line #14







Thanks too xDividerx
