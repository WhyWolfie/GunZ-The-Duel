<b> Icon Death Scoreboard </b><br>
![icon](https://i.imgur.com/jevO6PB.png) <br>
![example](https://i.imgur.com/KVwpEOb.jpg) <br>

[script]

    ZCharacter* pCharacter = (*itor).second;
    if (pCharacter->IsAdminName() || pCharacter->GetUserGrade() == MMUG_FREE) {
     if (pItem->bDeath) {
      BitmapRelative(pDC, 0.f, texty + 0.f, nIconSize, nIconSize, MBitmapManager::Get("icon_death.png"));
     }
    }
