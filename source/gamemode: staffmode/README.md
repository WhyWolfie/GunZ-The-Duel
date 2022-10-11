<b>Staff Mode (Newbies)</b><br>
1. CSCommon/Include/MBaseGameType.h

        MMATCH_GAMETYPE_STAFF_MODE            =12, // define the number that follows the previous one

2. CSCommon/Include/MMatchRule.h

        (nGameType == MMATCH_GAMETYPE_STAFF_MODE) ||

3. CSCommon/Include/MMatchRuleDeathMatch.h

        class MMatchRuleStaffMode : public MMatchRule {protected:
        bool CheckKillCount(MMatchObject* pOutObject);
        virtual void OnBegin();
        virtual void OnEnd();
        virtual void OnRoundTimeOut();
        virtual bool OnCheckRoundFinish();
        virtual bool RoundCount();
        public:
        MMatchRuleStaffMode(MMatchStage* pStage);
        virtual ~MMatchRuleStaffMode() { }
        virtual MMATCH_GAMETYPE GetGameType() { return MMATCH_GAMETYPE_STAFF_MODE; }
        };

4. CSCommon/Source/MBaseGametype.cpp

        #define MMATCH_GAMETYPE_STAFF_MODE_STR             "Staff Mode"
        "ST",        // Staff Mode (Newbies)
        _InitGameType(MMATCH_GAMETYPE_STAFF_MODE,        MMATCH_GAMETYPE_STAFF_MODE,            MMATCH_GAMETYPE_STAFF_MODE_STR,       1.0f,           1.0f,                     0.0f);

5. CSCommon/Source/MMatchRuleDeathMath.cpp

        //////////////////////////////////////////////////////////////////////////////////// MMatchRuleStaffMode ///////////////////////////////////////////////////////////
        MMatchRuleStaffMode::MMatchRuleStaffMode(MMatchStage* pStage) : MMatchRule(pStage)
        {


        }


        void MMatchRuleStaffMode::OnBegin()
        {


        }
        void MMatchRuleStaffMode::OnEnd()
        {
        }


        bool MMatchRuleStaffMode::RoundCount()
        {
        if (++m_nRoundCount < 1) return true;
        return false;
        }


        bool MMatchRuleStaffMode::CheckKillCount(MMatchObject* pOutObject)
        {
        MMatchStage* pStage = GetStage();
        for (MUIDRefCache::iterator i=pStage->GetObjBegin(); i!=pStage->GetObjEnd(); i++) 
        {
          MMatchObject* pObj = (MMatchObject*)(*i).second;
          if (pObj->GetEnterBattle() == false) continue;


          if (pObj->GetKillCount() >= (unsigned int)pStage->GetStageSetting()->GetRoundMax())
          {
           pOutObject = pObj;
           return true;
          }
        }
        return false;
        }


        bool MMatchRuleStaffMode::OnCheckRoundFinish()
        {
        MMatchObject* pObject = NULL;


        if (CheckKillCount(pObject))
        {
          return true;
        }
        return false;
        }


        void MMatchRuleStaffMode::OnRoundTimeOut()
        {
        SetRoundArg(MMATCH_ROUNDRESULT_DRAW);
        }

6. CSCommon/Source/MMatchStage.cpp

        case MMATCH_GAMETYPE_STAFF_MODE:        
              {
                  return (new MMatchRuleStaffMode(this));
              }
              break;
              
7. Gunz/ZGameInterface.cpp

        ZGetGameTypeManager()->SetGameTypeStr( MMATCH_GAMETYPE_STAFF_MODE, ZMsg( MSG_MT_STAFF_MODE));

8. Gunz/ZRule.cpp

          case MMATCH_GAMETYPE_STAFF_MODE:        
                {
                    return (new ZRuleStaffMode(pMatch));
                }
                break;

9. Gunz/ZRuleDeathMatch.cpp

        ZRuleStaffMode::ZRuleStaffMode(ZMatch* pMatch) : ZRule(pMatch)
        {


        }

        ZRuleStaffMode::~ZRuleStaffMode()
        {


        }

10. Gunz/ZRuleDeathMatch.h

        class ZRuleStaffMode : public ZRule{
        public:
            ZRuleStaffMode(ZMatch* pMatch);
            virtual ~ZRuleStaffMode();
        };

11. Gunz/ZStageInterface.cpp

        case MMATCH_GAMETYPE_STAFF_MODE:
        (pSetting->nGameType == MMATCH_GAMETYPE_STAFF_MODE) ||

12. Gunz/ZCharacter.cpp


         if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_STAFF_MODE)    
            {
                m_Items.EquipItem(MMCIP_PRIMARY, 400531); // first weapon
                m_Items.EquipItem(MMCIP_SECONDARY, 504504); // second weapon
                m_Items.EquipItem(MMCIP_MELEE, 6010); // melee
            }

        if( ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_STAFF_MODE)    
            {
                m_Property.fMaxHP.Set_CheckCrc(1000);
                    m_fPreMaxHP = 1000;
                m_Property.fMaxAP.Set_CheckCrc(1000);
                    m_fPreMaxAP = 1000;
            }

13. Gunz/ZMessage.h

        #define MSG_MT_STAFF_MODE                        9919        ///< Staff Mode, define the number that follows the previous one, although it doesn't matter much here

build matchserver and gunz...
Part 2 : Matchserver / system.mrs
1. Matchserver/Message.xml
      
        <MSG id="9916">Staff Mode</MSG>

2. Matchserver/gametypecfg.xml

        <GAMETYPE id="13">    <!-- GAMETYPE_STAFF_MODE -->        
                <ROUNDS    round="10"    str="10" />
                <ROUNDS    round="20"    str="20" />
                <ROUNDS    round="30"    str="30" />
                <ROUNDS    round="50"    str="50" default="true" />
                <ROUNDS    round="70"    str="70" />
                <ROUNDS    round="100"    str="100" />
                <LIMITTIME sec="99999"    str="STR:GAMETYPECFG_LIMITTIME_INFINITE" />
                <LIMITTIME sec="10"    str="STR:GAMETYPECFG_LIMITTIME_10MIN" />
                <LIMITTIME sec="20"    str="STR:GAMETYPECFG_LIMITTIME_20MIN" />
                <LIMITTIME sec="30"    str="STR:GAMETYPECFG_LIMITTIME_30MIN" default="true" />
                <LIMITTIME sec="40"    str="STR:GAMETYPECFG_LIMITTIME_40MIN" />
                <LIMITTIME sec="50"    str="STR:GAMETYPECFG_LIMITTIME_50MIN" />
                <LIMITTIME sec="60"    str="STR:GAMETYPECFG_LIMITTIME_60MIN" />
                <MAXPLAYERS player="4"  str="4" />
                <MAXPLAYERS player="8"  str="8" default="true" />
                <MAXPLAYERS player="12" str="12" />
                <MAXPLAYERS player="16" str="16" />
            </GAMETYPE>

3. Matchserver/ChannelRule.xml

        <GAMETYPE id="13" />         <!-- GAMETYPE_STAFF_MODE -->

Note : remember to place those files in your system.mrs

This has already been released years ago, It can even be customized with a staff clothing.
in ZCharacter.cpp for bool ZCharacter::Create(MTD_CharInfo... add these line.

    if (ZGetGame()->GetMatch()->GetMatchType() == MMATCH_GAMETYPE_MODE_STAFF)
            {

            if (GetProperty()->nSex == MMS_MALE)
            {
                m_Items.EquipItem(MMCIP_HEAD, 5060204);
                m_Items.EquipItem(MMCIP_CHEST, 399998);
                m_Items.EquipItem(MMCIP_HANDS, 5060206);
                m_Items.EquipItem(MMCIP_LEGS, 5060207);
                m_Items.EquipItem(MMCIP_FEET, 5060208);
            }
            else
            {
                m_Items.EquipItem(MMCIP_HEAD, 5060209);
                m_Items.EquipItem(MMCIP_CHEST, 399999);
                m_Items.EquipItem(MMCIP_HANDS, 5060211);
                m_Items.EquipItem(MMCIP_LEGS, 5060212);
                m_Items.EquipItem(MMCIP_FEET, 5060213);
            }
            m_Items.EquipItem(MMCIP_PRIMARY, 990004);
            m_Items.EquipItem(MMCIP_SECONDARY, 990002);
            m_Items.EquipItem(MMCIP_MELEE, 990001);
            m_Items.EquipItem(MMCIP_CUSTOM1, 990003);
        }
        m_Items.EquipItem(MMatchCharItemParts(i), pCharInfo->nEquipedItemDesc[i], pCharInfo->nEquipedItemCount[i]);
    } 




Credits to: Pablo 536
