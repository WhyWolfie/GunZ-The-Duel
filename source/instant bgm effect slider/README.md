Open(ZGameInterface.cpp) <br>
Find <br>

	SetListenerWidget("ReplayClose",				ZGetReplayExitButtonListener());
	SetListenerWidget("Replay_FileList",			ZGetReplayFileListBoxListener());

Add <br>

	SetListenerWidget("BGMVolumeSlider", ZGetBGMVolumeSizeSliderListener());
	SetListenerWidget("EffectVolumeSlider", ZGetEffectVolumeSizeSliderListener());

Open(ZOptionInterface.cpp) <br>
Find <br>

    /////////////////////////////////////////////////
    //// mouse
    static void SetMouseSensitivitySlider(int i)
    {
      ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
      MSlider* pSlider = (MSlider*)pResource->FindWidget("MouseSensitivitySlider");
      if (pSlider) 
      {
        pSlider->SetValue(i);
      }
    }

Add <br>

    BEGIN_IMPLEMENT_LISTENER(ZGetBGMVolumeSizeSliderListener, MLIST_VALUE_CHANGED)
    MSlider* pWidget = (MSlider*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("BGMVolumeSlider");
    if (pWidget)
    {
      Z_AUDIO_BGM_VOLUME = (float)((MSlider*)pWidget)->GetValue() / (float)10000;
      ZGetSoundEngine()->SetMusicVolume(Z_AUDIO_BGM_VOLUME);
    }
    END_IMPLEMENT_LISTENER()

    BEGIN_IMPLEMENT_LISTENER(ZGetEffectVolumeSizeSliderListener, MLIST_VALUE_CHANGED)
    MSlider* pWidget = (MSlider*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("EffectVolumeSlider");
    if (pWidget)
    {
      Z_AUDIO_EFFECT_VOLUME = (float)((MSlider*)pWidget)->GetValue() / (float)10000;
      ZGetSoundEngine()->SetEffectVolume(Z_AUDIO_EFFECT_VOLUME);
    }
    END_IMPLEMENT_LISTENER()

Open(ZOptionInterface.h) <br>
Find <br>

    DECLARE_LISTENER(ZGetMouseSensitivitySliderListener)
    DECLARE_LISTENER(ZGetMouseSensitivityEditListener)

Add <br>

    DECLARE_LISTENER(ZGetBGMVolumeSizeSliderListener)
    DECLARE_LISTENER(ZGetEffectVolumeSizeSliderListener)







