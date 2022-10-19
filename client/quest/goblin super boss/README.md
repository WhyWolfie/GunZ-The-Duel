Ok here. Just follow these steps. <br>

NOTE: Make a backup copy of your files before modifying it <br>

npc.xml <br>
scenario.xml <br>
questmap.xml ((Don't worry about the key_sector = "102"))  <br>
shop.xml <br>
zquestitem.xml <br>


npc.xml <br>

    <NPC id="214"
         name="STR:NPC_NAME_13"
         desc="STR:NPC_DESC_13"
         meshname="goblinW"
         scale="2.8 2.8 2.8"
         grade="boss"
         max_hp="7000"
         max_ap="8000"
         int="4"
         agility="4"
         view_angle="25"
         dc="6"
         offensetype="1"
         dyingtime="5">
         <COLLISION radius="30" height="200" />
         <ATTACK type="melee" range="130" weaponitem_id="300013" />
         <SPEED default="400" />
         <SKILL id="131" />
         <SKILL id="132" />
         <SKILL id="341" />
         <DROP table="G13" />
    </NPC>  

scenario.xml <br>

    <SPECIAL_SCENARIO id="556"

        title="Goblin Super Boss"
        QL="1"
        DC="1"
        mapset="Mansion"
        XP="10000000"
        BP="500000">

          <SACRI_ITEM itemid="050592" />

        <MAP dice="1" key_sector="102" key_npc="214" boss="true" >
            <NPCSET_ARRAY>G61</NPCSET_ARRAY>
            <JACO count="2" tick="5" min_npc="0" max_npc="13">
                <NPC npcid="11" rate="0.2" />
                <NPC npcid="214" rate="0.3" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.1" />
            </JACO>
        </MAP>
        <MAP dice="2" key_sector="102" key_npc="214" boss="true">
            <NPCSET_ARRAY>G61</NPCSET_ARRAY>
            <JACO count="2" tick="5" min_npc="0" max_npc="13">
                <NPC npcid="11" rate="0.2" />
                <NPC npcid="214" rate="0.3" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.1" />
            </JACO>
        </MAP>
        <MAP dice="3" key_sector="102" key_npc="214" boss="true">
            <NPCSET_ARRAY>G61</NPCSET_ARRAY>
            <JACO count="2" tick="5" min_npc="0" max_npc="13">
                <NPC npcid="11" rate="0.2" />
                <NPC npcid="214" rate="0.3" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.1" />
            </JACO>
        </MAP>
        <MAP dice="4" key_sector="102" key_npc="214" boss="true">
            <NPCSET_ARRAY>G61</NPCSET_ARRAY>
            <JACO count="2" tick="5" min_npc="0" max_npc="13">
                <NPC npcid="11" rate="0.2" />
                <NPC npcid="214" rate="0.3" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.1" />
            </JACO>
        </MAP>
        <MAP dice="5" key_sector="102" key_npc="214" boss="true">
            <NPCSET_ARRAY>G61</NPCSET_ARRAY>
            <JACO count="2" tick="5" min_npc="0" max_npc="13">
                <NPC npcid="11" rate="0.2" />
                <NPC npcid="214" rate="0.3" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.1" />
            </JACO>
        </MAP>
        <MAP dice="6" key_sector="102" key_npc="214" boss="true">
            <NPCSET_ARRAY>G61</NPCSET_ARRAY>
            <JACO count="2" tick="5" min_npc="0" max_npc="13">
                <NPC npcid="11" rate="0.2" />
                <NPC npcid="214" rate="0.3" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.2" />
                <NPC npcid="214" rate="0.1" />
            </JACO>
        </MAP>
    </SPECIAL_SCENARIO>  

shop.xml <br>

    <SELL itemid="050592"/>  



zquestitem.xml 

    <ITEM id="050592" name="Goblin Super Boss" level="0" type="doll" desc="Endless Quest." unique="0" price="1" secrifice="1" param="0" />  


Results <br>

![img](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/client/quest/goblin%20super%20boss/1.jpg)

![img](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/client/quest/goblin%20super%20boss/2.jpg)

















