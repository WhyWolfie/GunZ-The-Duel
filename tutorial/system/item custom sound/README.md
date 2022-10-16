Follow this step first: https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/source/custom%20shotgun%20sounds

decompile 'Effect.mrs' <br>
convert your file to '.wav' <br>
copy paste to Effect folder 'fx_dash.wav' your '.wav' file <br>

open 'effect.xml'

"your .wav name"

find: 

    <EFFECT NAME="we_rifle_fire" MINDISTANCE="320"/>

place

    <EFFECT NAME="fx_dash" MINDISTANCE="320"/>

system->zitem.xml <br>
matchserver->zitem.xml <br>

change: snd_fire="your sound name" -> snd_fire="we_shotgunev_fire" <br>

example: snd_reload="we_shotgunpa_reload" snd_fire="we_shotgunev_fire" snd_dryfire="762arifle_dryfire" <br>

    <ITEM id="94556" name="Pikachu Shotgun" mesh_name="PikachuShotty" totalpoint="0" type="range" res_sex="a" res_level="0" slot="range" weapon="shotgun" weight="10" bt_price="0" delay="915" damage="9" ctrl_ability="0" magazine="5" reloadtime="5" slug_output="true" gadget_id="0" hp="0" ap="0" maxwt="0" sf="0" fr="0" cr="0" pr="0" lr="0" color="#FFFFFFFF" image_id="2" bullet_image_id="0" magazine_image_id="0" desc="Gratz you won a event." snd_reload="we_shotgunpa_reload" snd_fire="we_shotgunev_fire" snd_dryfire="762arifle_dryfire" maxbullet="40" effect_id="7" iscashitem="false" />


compile <br>
system.mrs <br>
effect.mrs <br>
