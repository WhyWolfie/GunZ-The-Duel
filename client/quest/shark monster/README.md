instructions: <br>
1.decompile palmpoa.mrs and Put Sk.elu and shark.xml into it.. <br>

2.decompile model.mrs and add this script in NPC.xml: <br>

<AddXml name="Shark" 	filename="model/npc/palmpoa/shark.xml" autoload = "false">  </AddXml> <br>

3.now here is my suggested npc profile for server and system.mrs npc.xml: <br>

its only for boss monster here so you better DIY own risk if you want to have regular shark monster <br>

    <!-- Shark king -->
    <NPC id="57"
       name="Shark Boss"
       desc="Sea Monster"
       meshname="Shark"
       scale="6.0 6.0 6.0"
       grade="boss"
       max_hp="8000"
       max_ap="8000"
       int="1"
       agility="4"
       view_angle="60"
       dc="50"
       offensetype="1"
       dyingtime="5">
       <COLLISION radius="60" height="20" />
       <ATTACK type="melee" range="80"  />
       <FLAG never_blasted="true" never_pushed="true" never_attack_cancel="true" />
       <SPEED default="190" rotate="2.356" />
       <SKILL id="451" />
       <SKILL id="392" />
       <DROP table="P45" />
    </NPC>


![img](http://i864.photobucket.com/albums/ab201/evilcorpse5/Gunz005-1.jpg)
![img](http://i864.photobucket.com/albums/ab201/evilcorpse5/Gunz004-1.jpg)
![img](http://i864.photobucket.com/albums/ab201/evilcorpse5/Gunz003.jpg)
![img](http://i864.photobucket.com/albums/ab201/evilcorpse5/Gunz002.jpg)
![img](http://i864.photobucket.com/albums/ab201/evilcorpse5/Gunz001.jpg)
![img](http://i864.photobucket.com/albums/ab201/evilcorpse5/Gunz000.jpg)
