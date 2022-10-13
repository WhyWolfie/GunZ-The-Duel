Open(MMatchServer_Channel.cpp)

Search(MMatchServer::ChannelChat) <br>
and you will see inside that bool this:

    if( 0 == strlen(pszChat) ) return false;
    
They are going to select from that condition to

    int nGrade = (int) pObj->GetAccountInfo()->m_nUGrade;
    
and replace that selection with this:

    MMatchChannel* pChannel = FindChannel(uidChannel);
      MMatchObject* pObj = (MMatchObject*)GetObject(uidPlayer);

      if ((!IsAdminGrade(pObj)) && (strstr(pChannel->GetName(), "Event"))) return false;
      if( 0 == strlen(pszChat) ) return false;
      if (pChannel == NULL) return false;
      if ((pObj == NULL) || (pObj->GetCharInfo() == NULL)) return false;
      if (pObj->GetAccountInfo()->m_nUGrade == MMUG_CHAT_LIMITED) return false;

      int nGrade = (int) pObj->GetAccountInfo()->m_nUGrade;
      

Open(MMatchServer_Stage.cpp) <br>
Find(MMatchServer::StageChat) <br>
and you will see inside that bool this: <br>

    MMatchStage* pStage = FindStage(uidStage);

Select from that to

    if (pObj->GetAccountInfo()->m_nUGrade == MMUG_CHAT_LIMITED) return false;

and replace with

    MMatchStage* pStage = FindStage(uidStage);
      MMatchObject* pObj = (MMatchObject*)GetObject(uidPlayer);
      MMatchChannel* pChannel = FindChannel(pObj->GetChannelUID());

      if ((!IsAdminGrade(pObj)) && (strstr(pChannel->GetName(), "Event"))) return false;
      if (pStage == NULL)	return false;
      if ((pObj == NULL) || (pObj->GetCharInfo() == NULL)) return false;

      if (pObj->GetAccountInfo()->m_nUGrade == MMUG_CHAT_LIMITED) return false;


Prohibit room creation in the channel <br>
Find: <br>

    MMatchServer::OnStageCreate
    
and you will see below

    MUID uidStage;

Add below that:

    if ((!IsAdminGrade(pObj)) && (strstr(pChannel->GetName(), "Event")))
      {
        RouteResponseToListener(pObj, MC_MATCH_RESPONSE_STAGE_CREATE, MERR_CANNOT_CREATE_STAGE);
        return;
      }

