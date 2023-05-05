This is a method so that I shoot them when they touch a wall, they will release sparks as they usually happen in real life when taking a weapon and seeing how these sparks are caused, in short, let's get to the point.

First of all we will do it in the switch method, follow me...

Open "stdafx.h" folder Gunz in your source y paste these

    #define _SPARKBULLET 1

add a // to disable, example //#define _YOURCODE

Open "ZEffectManager.cpp" and search "void ZEffectManager::AddBulletMark" and remplace all these line...

    #ifdef _SPARKBULLET
    void ZEffectManager::AddBulletMark(rvector& Target, rvector& TargetNormal)
    {
      if(g_nEffectLevel > Z_VIDEO_EFFECT_NORMAL) return;
      if (Z_VIDEO_BULLET_MARKS) return;

      m_BulletMarkList.Add(Target+TargetNormal,TargetNormal);
      AddLightFragment(Target + TargetNormal, TargetNormal);

      ZEffect* pNew = NULL;
      pNew = new ZEffectSlash(m_pBulletOnWallEffect[rand()%BULLETONWALL_COUNT],Target,TargetNormal);
      ((ZEffectSlash*)pNew)->SetAlignType(1);
      Add(pNew);
    }
    #else
    void ZEffectManager::AddBulletMark(rvector& Target, rvector& TargetNormal)
    {
      if (g_nEffectLevel > Z_VIDEO_EFFECT_NORMAL) return;
      if (Z_VIDEO_BULLET_MARKS) return;

      m_BulletMarkList.Add(Target + TargetNormal, TargetNormal);

      ZEffect* pNew = NULL;
      pNew = new ZEffectSlash(m_pBulletOnWallEffect[rand() % BULLETONWALL_COUNT], Target, TargetNormal);
      ((ZEffectSlash*)pNew)->SetAlignType(1);
      Add(pNew);
    }
    #endif
    
    
change these if (Z_VIDEO_BULLET_MARKS) return; to //if (Z_VIDEO_BULLET_MARKS) return;
compile and then test what those sparks look like, remember that there you have the option to activate or deactivate it in case you don't like it or some of its users, enjoy it.
