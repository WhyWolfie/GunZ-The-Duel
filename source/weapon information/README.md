<b>Weapon Information</b>
<br>
<b>[ZCombatInterface.cpp]</b> <br>


        char szWeaponInfo[70];
        MMatchCharItemParts nParts = pCharacter->GetItems()->GetSelectedWeaponParts();
        if (nParts < MMCIP_END) {
        MMatchItemDesc* pItemDesc = MGetMatchItemDescMgr()->GetItemDesc(pCharacter->GetItems()->GetSelectedWeapon()->GetDescID());
        sprintf(szWeaponInfo, "(Damage %d / Delay %d)", pItemDesc->m_nDamage.Ref(), pItemDesc->m_nDelay.Ref());
        TextRelative(pDC, 00.f / 800.f, 00.f / 600.f, szWeaponInfo);
        }



<br>

![gunz logo](https://i.imgur.com/7XOHNz5.png)

<b> Credits too GunzFactor </b>
