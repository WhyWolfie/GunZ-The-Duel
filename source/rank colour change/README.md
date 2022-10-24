Hex Colour: [Hex Colour](https://htmlcolorcodes.com/)

Open(ZColorTable.h)

    #define ZCOLOR_ADMIN_NAME			0xFF(add here your colour)

Example

    #define ZCOLOR_ADMIN_NAME			0xFFff8040


Open(ZGame.cpp - bool GetUserGradeIDColor(MMatchUserGradeID gid,MCOLOR& UserNameColor,char* sp_name))

	else if(gid == MMUG_ADMIN) {
		UserNameColor = MCOLOR(ur code, ur code, ur code); RGB
		return true; 
	}


Example

	else if(gid == MMUG_ADMIN) {
		UserNameColor = MCOLOR(255, 128, 64);
		return true; 
	}
  
  

![wolfie](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/rank%20colour%20change/wolfie.jpg)
![wolfie2](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/rank%20colour%20change/wolfie2.jpg)
