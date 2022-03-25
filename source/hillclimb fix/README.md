<b> hillclimb fix</b>
[find code]

      if ( zStatus.m_bRButtonPressed == true ) return; //  if (MEvent::GetRButtonState()) return;

[replace code]

      if(MEvent::GetRButtonState()) return;

[video] <br>

https://www.youtube.com/watch?v=TRWjoJX5A3A
