Open(ZScreenEffectManager.cpp) <br>

Find: void ZScreenEffectManager::DrawCombo() - Replace all<br>

    void ZScreenEffectManager::DrawCombo()
    {
      int nFrame,nLastDigit=0;
      for(int i=0;i<COMBOEFFECTS_COUNT;i++)
      {
        if(m_pComboEffects[i] && m_pComboEffects[i]->GetVMesh()) {

          nLastDigit=i;

          //nFrame = m_pComboEffects[i]->GetVMesh()->m_nFrame[0];
          //VMesh NULL and GetFrameInfo fix
          if (m_pComboEffects[i]->GetVMesh() == NULL) continue;
          if (m_pComboEffects[i]->GetVMesh()->GetFrameInfo(ani_mode_lower) == NULL) continue;

          nFrame = m_pComboEffects[i]->GetVMesh()->GetFrameInfo(ani_mode_lower)->m_nFrame;

          if(m_pComboEffects[i]->GetVMesh()->isOncePlayDone()) {

            m_pComboEffects[i]->DeleteAfter();
            m_pComboEffects[i]=NULL;
            if(i==0)
            {
              if(m_pComboEffects[1])
                m_pComboEffects[1]->DeleteAfter();
              m_pComboEffects[1]=new ZComboEffect(m_pComboEndEffect);
              Add(m_pComboEffects[1]);
            }
          }
        }
      }

      for(int i=2;i<nLastDigit;i++) {
        if(m_pComboEffects[i]) {
          m_pComboEffects[i]->SetFrame(nFrame);
        }
      }
    }


Find: sprintf(buffer,"%d",nCombo); <br>
Replace <br>

	//sprintf_s prevent buffer overrun
	sprintf_s(buffer, "%d", nCombo);


Find: void ZScreenEffectManager::DrawArrow <br>
Replace <br>

    void ZScreenEffectManager::DrawArrow(rvector& vTargetPos, float fOffsetY, float OffsetX, int Type)
    {
      ZCharacter* pTargetCharacter = ZGetGameInterface()->GetCombatInterface()->GetTargetCharacter();
      if (!pTargetCharacter || !pTargetCharacter->GetInitialized()) return;
      rvector at = pTargetCharacter->GetPosition();
      rvector to = vTargetPos;
      rvector dir1, dir2;
      dir1 = pTargetCharacter->GetDirection();
      dir2 = to - at;
      float fAng = GetAngleOfVectors(dir2, dir1);

      if (m_pArrow)
      {
        m_pArrow->DrawCustom(0, rvector(0.0f, fOffsetY, 0.0f), fAng);
      }
    }

Open(ZScreenEffectManager.h) <br>
Find void DrawArrow - Add under to public:<br>

    public:
      void DrawArrow(rvector& vTargetPos, float post = 285.0f, float OffsetX = 0.0f, int Type = 0);
      void DrawEffects();




