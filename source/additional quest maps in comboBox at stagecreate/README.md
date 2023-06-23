I searched for a while and couldn't find anything posted about this. So i figured i'd post it publicly to help someone in the future (or incase i forget myself) <br>
I noticed alot of sources don't do this and rely on Mansion as the target for their custom quests. (Probably because nobody likes quests but me) :p <br>

Example: <br>
MQuestScenario.cpp <br>

    else if (!stricmp(szAttrName, MTOK_SCENARIO_MAPSET))
            {
              if ( !stricmp(szAttrValue, "mansion"))
                  pScenarioInfo->nMapSet = 1;
              if ( !stricmp(szAttrValue, "prison"))
                  pScenarioInfo->nMapSet = 2;
              if ( !stricmp(szAttrValue, "dungeon"))
                  pScenarioInfo->nMapSet = 3;
              if (!stricmp(szAttrValue, "graveyard")) //added
                  pScenarioInfo->nMapSet = 4;
          }
          
Also: here

in void MMatchRuleQuest::MakeStageGameInfo() Also:

        m_StageGameInfo.nMapsetID = 1;
        if ( !stricmp( pStage->GetMapName(), "mansion"))
            m_StageGameInfo.nMapsetID = 1;
        else if ( !stricmp( pStage->GetMapName(), "prison"))
            m_StageGameInfo.nMapsetID = 2;
        else if ( !stricmp( pStage->GetMapName(), "dungeon"))
            m_StageGameInfo.nMapsetID = 3;
        else if (!stricmp(pStage->GetMapName(), "graveyard"))
            m_StageGameInfo.nMapsetID = 4;

In Scenario.xml The following needs to be added for the ParseSpecialScenario function to add an additional combobox. If you do not make a Standard_Scenario, it will never show up. This is the base requirement. You can add additional special scenarios (boss modes or questbooks) normally, but this enables the population of combobox. <br>
Note: The placement of this code in your scenario.xml determines where the combobox sits. <br>

      <STANDARD_SCENARIO
          QL="0"
          title="Quest Graveyard QL0"
          DC="1"
          mapset="Graveyard"
          XP="200"
          BP="25">
      
          <!-- nest1 맵 부터 시작 -->
          <MAP dice="1" key_sector="501">
              <NPCSET_ARRAY>S01/S02/S03</NPCSET_ARRAY>
          </MAP>
          <MAP dice="2" key_sector="502">
              <NPCSET_ARRAY>S01/S02/S03</NPCSET_ARRAY>
          </MAP>
          <MAP dice="3" key_sector="503">
              <NPCSET_ARRAY>S01/S02/S03</NPCSET_ARRAY>
          </MAP>
          <MAP dice="4" key_sector="504">
              <NPCSET_ARRAY>S01/S02/S03</NPCSET_ARRAY>
          </MAP>
          <MAP dice="5" key_sector="505">
              <NPCSET_ARRAY>S01/S02/S03</NPCSET_ARRAY>
          </MAP>
          <MAP dice="6" key_sector="505">
              <NPCSET_ARRAY>S01/S02/S03</NPCSET_ARRAY>
          </MAP>
      </STANDARD_SCENARIO>
  
  in questmap.xml We assign a mapset <br>
  
    <MAPSET id="4"  title="Graveyard">
        <SECTOR id="501"
                title="ruin1f"
                melee_spawn="10"
                range_spawn="15">
            <LINK>
                <TARGET sector="cemetary_grave"/>
            </LINK>
        </SECTOR>
        <SECTOR id="502"
                title="cemetary_grave"
                melee_spawn="10"
                range_spawn="15">
            <LINK>
                <TARGET sector="cemetary_altar" />
            </LINK>
        </SECTOR>
        <SECTOR id="503"
                title="cemetary_altar"
                melee_spawn="10"
                range_spawn="15">
            <LINK>
                <TARGET sector="cemetary_trench"    />
            </LINK>
        </SECTOR>
        <SECTOR id="504"
                title="cemetary_trench"
                melee_spawn="10"
                range_spawn="15">
            <LINK>
                <TARGET sector="cemetary_final"    />
            </LINK>
        </SECTOR>
        <SECTOR id="505"
                title="cemetary_final"
                melee_spawn="10"
                range_spawn="15">
            <LINK>
                <TARGET sector="ruin1f"    />
            </LINK>
        </SECTOR>
     
    </MAPSET>

![img](https://i.imgur.com/C9OyVrYl.png)

If you want to add to survival: Edit void MMatchRuleSurvival::MakeStageGameInfo() or just search for "dungeon" to find the 4 locations for the edits. But this is already enough spoon feeding. <br>

![img2](https://forum.ragezone.com/data/attachments/176/176780-10cf45d0d903a3e08ffaf853d7c3421e.jpg)

Credits to: xDividerx
