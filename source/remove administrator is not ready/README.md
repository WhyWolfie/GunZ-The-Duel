
Administrator: ¿î¿µÀÚ <br>
Developer: °³¹ßÀÚ <br>

![1](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/remove%20administrator%20is%20not%20ready/1.jpg)


Open up CSCommon\Source\MMatchStage.cpp <br>


Go to line 609 and find: <br>

    bool _GetUserGradeIDName(MMatchUserGradeID gid,char* sp_name)
    {
        if(gid == MMUG_DEVELOPER) 
        { 
            if(sp_name) {
                strcpy(sp_name,"°³¹ßÀÚ");
            }
            return true; 
        }
        else if(gid == MMUG_ADMIN) {

            if(sp_name) { 
                strcpy(sp_name,"¿î¿µÀÚ");
            }
            return true; 
        }


        return false;
    }




You have 2 options now. Show their original names or show their rank names (Administrator/Developer). <br>
The first option is useful when you have unmasked ranks. <br>
The second option is useful when you have masked ranks. <br>


-------------------------------------------------- <br>


1. If you want to show them their original names, replace the code with this: <br>


        bool _GetUserGradeIDName(MMatchUserGradeID gid,char* sp_name)
        {
            /*if(gid == MMUG_DEVELOPER) 
            { 
                if(sp_name) {
                    strcpy(sp_name,"°³¹ßÀÚ");
                }
                return true; 
            }
            else if(gid == MMUG_ADMIN) {

                if(sp_name) { 
                    strcpy(sp_name,"¿î¿µÀÚ");
                }
                return true; 
            }*/


            return false;
        }




![2](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/remove%20administrator%20is%20not%20ready/2.png)


2. If you want to show their rankname, replace the code with this:


        bool _GetUserGradeIDName(MMatchUserGradeID gid,char* sp_name)
        {
            if(gid == MMUG_DEVELOPER) 
            { 
                if(sp_name) {
                    strcpy(sp_name,"Developer");
                }
                return true; 
            }
            else if(gid == MMUG_ADMIN) {

                if(sp_name) { 
                    strcpy(sp_name,"Administrator");
                }
                return true; 
            }


            return false;
        }



![replace](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/remove%20administrator%20is%20not%20ready/replace.jpg)






Now save MMatchStage.cpp and rebuild your Runnable AND MatchServer. <br>


Enjoy. <br>



Credits to Patrick2607 <br>
