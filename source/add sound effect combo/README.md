You've seen this combo? on your enemy. <b>

You can make it sound(COOL,NICE,GREAT,WONDERFUL) better by modifying the source on project Gunz.sln .<b>
======================================

1. Open ZScreenRffectManager.cpp<b>

2. Find word "ZGetGameInterface()->PlayVoiceSound( VOICE_NICE, 1000);"<b>

3. Remove the // leading<b>

Save and Build it work!! sure!<b>

======================================<b>
Comment : At the same light. To a new sound. Or adjust the volume up.<b>

Old Code<b>

    void ZScreenEffectManager::AddNice()
    {	
      AddScreenEffect(m_pNiceEffect); 
      //	ZGetGameInterface()->PlayVoiceSound( VOICE_NICE, 1000);

    }
    void ZScreenEffectManager::AddGreat()
    {	
      AddScreenEffect(m_pGreatEffect); 
      //	ZGetGameInterface()->PlayVoiceSound( VOICE_GREAT, 800);
    }

    void ZScreenEffectManager::AddWonderful()
    {	
      AddScreenEffect(m_pWonderfullEffect); 
      //	ZGetGameInterface()->PlayVoiceSound( VOICE_WONDERFUL, 1200);
    }

    void ZScreenEffectManager::AddCool()
    {	
      AddScreenEffect(m_pCoolEffect); 
      //	ZGetGameInterface()->PlayVoiceSound( VOICE_COOL, 700);
    }
  
  Fix Code Remove the // leading ZGetGameInterface
  
      void ZScreenEffectManager::AddNice()
    {	
      AddScreenEffect(m_pNiceEffect); 
        ZGetGameInterface()->PlayVoiceSound( VOICE_NICE, 1000);

    }
    void ZScreenEffectManager::AddGreat()
    {	
      AddScreenEffect(m_pGreatEffect); 
        ZGetGameInterface()->PlayVoiceSound( VOICE_GREAT, 800);
    }

    void ZScreenEffectManager::AddWonderful()
    {	
      AddScreenEffect(m_pWonderfullEffect); 
        ZGetGameInterface()->PlayVoiceSound( VOICE_WONDERFUL, 1200);
    }

    void ZScreenEffectManager::AddCool()
    {	
      AddScreenEffect(m_pCoolEffect); 
        ZGetGameInterface()->PlayVoiceSound( VOICE_COOL, 700);
    }
