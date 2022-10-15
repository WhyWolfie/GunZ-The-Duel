Contents: <br>
Step1: Where to place the Quest Maps and NPC. <br>
Step2: model.mrs (NPC.xml) <br>
Step3: system.mrs (npc.xml, questmap.xml, scenario.xml, zquestitem.xml) <br>
Step4: matchserver (npcset.xml, shop.xml) <br>

Step2 model.mrs (NPC.xml) <br>
Now go to your clients root folder and unpack 'model.mrs'. <br>
Right click on 'NPC.xml' and choose the option edit. <br>
Notepad will open, add this line and save it: <br>

    <AddXml name="boo" filename="model/npc/boo/boo.xml" autoload = "false">  </AddXml>
    

After that you pack your model.mrs. <br>

Step3 system.mrs (npc.xml, questmap.xml, scenario.xml, zquestitem.xml) <br>
Go to your clients root folder and unpack 'system.mrs'. <br>
Right click on 'npc.xml' and choose the option edit. <br>
Notepad will open, add these lines and save it. <br>

    <NPC id="98"
       name="Boo"
       desc="By Duster and XML by Lloyd Keijzer"
       meshname="boo"
       scale="1.0 1.0 1.0"
       grade="veteran"
       max_hp="50"
       max_ap="100"
       int="4"
       agility="2"
       view_angle="40"
       dc="7"
       offensetype="1"
       dyingtime="5">
       <COLLISION radius="35" height="140" />
       <FLAG never_pushed="true" />
       <ATTACK type="melee" range="170" weaponitem_id="300014" />
       <SPEED default="360" />
       <DROP table="G16" />
    </NPC>

    <NPC id="99"
       name="KingBoo"
       desc="By Duster and XML by Lloyd Keijzer"
       meshname="boo"
       scale="2.5 2.5 2.5"
       grade="boss"
       max_hp="8000"
       max_ap="8000"
       int="1"
       agility="4"
       view_angle="60"
       dc="50"
       offensetype="1"
       dyingtime="5">
       <COLLISION radius="25" height="120" />
       <ATTACK type="melee" range="80"  />
       <FLAG never_blasted="true" never_pushed="true" never_attack_cancel="true" />
       <SPEED default="150" rotate="2.356" />
       <SKILL id="162" /> <!-- Goblin Kings: Fire missle -->
       <DROP table="G16" />
    </NPC>

Warning: NPC id's may not be the same as the ones you already have! <br>
The droptable is optional to edit(now it drops the same as the goblin king). <br>
Right click on 'questmap.xml' and choose the option edit. <br>
Notepad will open, add these lines under the last sector of dungeon and save it. <br>


    <SECTOR id="310"
      title="BooS1"
      melee_spawn="15"
      range_spawn="15">
      <LINK>
        <TARGET sector="BooS2" />
      </LINK>
    </SECTOR>
    <SECTOR id="311"
      title="BooS2"
      melee_spawn="15"
      range_spawn="15">
      <LINK>
        <TARGET sector="BooBS" />
      </LINK>
    </SECTOR>
    <SECTOR id="312"
      title="BooBS"
      melee_spawn="15"
      range_spawn="15">
      <LINK>
        <TARGET sector="BooS1" />
      </LINK>
    </SECTOR>

Right click on 'scenario.xml' and choose the option edit. <br>
Notepad will open, add these lines and save it. <br>

    <SPECIAL_SCENARIO id="99"
      title="KingBoo"
      QL="1"
      DC="1"
      mapset="Dungeon"
      XP="120000"
      BP="10000">
      <SACRI_ITEM itemid="200099" />	<!-- Custom Item: Summon KingBoo -->

      <MAP dice="1" key_sector="312" key_npc="99" boss="true" >
        <NPCSET_ARRAY>B01/B02/B03</NPCSET_ARRAY>
      </MAP>
      <MAP dice="2" key_sector="312" key_npc="99" boss="true">
        <NPCSET_ARRAY>B01/B02/B03</NPCSET_ARRAY>
      </MAP>
      <MAP dice="3" key_sector="312" key_npc="99" boss="true">
        <NPCSET_ARRAY>B01/B02/B03</NPCSET_ARRAY>
      </MAP>
      <MAP dice="4" key_sector="312" key_npc="99" boss="true">
        <NPCSET_ARRAY>B01/B02/B03</NPCSET_ARRAY>
      </MAP>
      <MAP dice="5" key_sector="312" key_npc="99" boss="true">
        <NPCSET_ARRAY>B01/B02/B03</NPCSET_ARRAY>
      </MAP>
      <MAP dice="6" key_sector="312" key_npc="99" boss="true">
        <NPCSET_ARRAY>B01/B02/B03</NPCSET_ARRAY>
      </MAP>
    </SPECIAL_SCENARIO>

Right click on 'zquestitem.xml' and choose the option edit. <br>
Notepad will open, add this line and save it. <br>

    <!-- Boo Quest Item -->
    <ITEM id="200099" name="Summon KingBoo" level="0" type="skull" desc="Created by Duster and XML work by Lloyd Keijzer" unique="0" price="0" secrifice="1" param="0" />

Now pack your system.mrs and your done editing that. <br>

Step4 matchserver (npcset.xml, shop.xml) <br>
Go to your Server Files and open the folder 'MatchServer'. <br>
Copy paste all the files you modified in system.mrs to your MatchServer folder. <br>
After that right click on 'npcset.xml' and choose the option edit. <br>
Notepad will open, add these lines and save it. <br>

    <NPCSET id="10997" name="B01" basenpc="98">
      <ADDNPC npc_id="98" min_rate="100" max_rate="100" />
    </NPCSET>
    <NPCSET id="10998" name="B02" basenpc="98">
      <ADDNPC npc_id="98" min_rate="100" max_rate="100" />
    </NPCSET>
    <NPCSET id="10999" name="B03" basenpc="98">
      <ADDNPC npc_id="98" min_rate="100" max_rate="100" />
    </NPCSET>

Right click on 'shop.xml' and choose the option edit. <br>
Notepad will open, add this line and save it. <br>

    <SELL itemid="200099" /> <!-- Boo Quest -->

After you done that you need to unpack your model.mrs. <br>
Open NPC.xml and add this line: <br>

    <AddXml name="kingboo" 	filename="model/npc/boo/kingboo.xml" autoload = "false">  </AddXml>

save it and pack your model.mrs <br>

Now you need to unpack your system.mrs <br>
Open npc.xml and change this: <br>

    <NPC id="99"
       name="KingBoo"
       desc="By Duster and XML by Lloyd Keijzer"
       meshname="boo"
       scale="2.0 2.0 2.0"
       grade="boss"
       max_hp="8000"
       max_ap="8000"
       int="1"
       agility="4"
       view_angle="60"
       dc="50"
       offensetype="1"
       dyingtime="5">
       <COLLISION radius="25" height="120" />
       <ATTACK type="melee" range="80"  />
       <FLAG never_blasted="true" never_pushed="true" never_attack_cancel="true" />
       <SPEED default="150" rotate="2.356" />
       <SKILL id="162" /> <!-- Goblin Kings: Fire missle -->
       <DROP table="G16" />
    </NPC>

into this.

    <NPC id="99"
       name="KingBoo"
       desc="By [+]Python and XML by Lloyd Keijzer"
       meshname="kingboo"
       scale="2.0 2.0 2.0"
       grade="boss"
       max_hp="8000"
       max_ap="8000"
       int="1"
       agility="4"
       view_angle="60"
       dc="50"
       offensetype="1"
       dyingtime="5">
       <COLLISION radius="25" height="120" />
       <ATTACK type="melee" range="80"  />
       <FLAG never_blasted="true" never_pushed="true" never_attack_cancel="true" />
       <SPEED default="150" rotate="2.356" />
       <SKILL id="162" /> <!-- Goblin Kings: Fire missle -->
       <DROP table="G16" />
    </NPC>



save it and copy your npc.xml to your matchserver and pack your system.mrs. <br>

If you done all that you can restart your server and enjoy the new KingBoo Model <br>

Many thanks to [+]Python for making this model!!! <br>






















