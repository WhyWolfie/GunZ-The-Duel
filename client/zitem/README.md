WorldItem Information <br>

      <WORLDITEM id="260" <<< The Item Number, set a high number.
      name="Damagekit"> <<< Item name, Medikit, Repairkit or Damagekit.
      <TYPE>hpap</TYPE> <<< Enter HP if you want your item to be HP, AP if you want it to be AP or HPAP if you want it to be both HP and AP.
      <AMOUNT>-20</AMOUNT> <<< Set the amount or remove the item : Example : 20 will give 20 HP or AP, -20 will REMOVE HP or AP.
      <MODELNAME>Damagekit</MODELNAME> <<<< The name of the model of the item without the .ELU
      </WORLDITEM>


Staff Meds <br>
System->WorldItem.xml <br>
MatchServer->WorldItem.xml <br>

    <WORLDITEM id="260" name="Damagekit">
    <TYPE>hpap</TYPE>
    <AMOUNT>-20</AMOUNT>
    <MODELNAME>Damagekit</MODELNAME>
    </WORLDITEM>

Open(System->Zitem.xml) <br>

    <ITEM id="28282" name="Staff Damage Kit" mesh_name="Damagekit" totalpoint="0" type="custom" res_sex="a" res_level="0" slot="custom" weapon="medkit" weight="1" bt_price="0" delay="50" damage="0" ctrl_ability="0" magazine="999999" reloadtime="10" slug_output="false" gadget_id="0" hp="0" ap="0" maxwt="0" sf="0" fr="0" cr="0" pr="0" lr="0" color="#FFFFFFFF" image_id="3" bullet_image_id="0" magazine_image_id="0" desc="Damage Kit" snd_fire="we_grenade_fire" maxbullet="10" />

Open(MatchServer->Shop.xml) <br>

    <!-- Damage Kit -->
    <SELL itemid="28282"/>
