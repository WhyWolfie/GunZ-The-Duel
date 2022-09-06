After doing some thinking I have decided to post this. <br>

Ever since I was introduced to the concept of underclocking in gunz(well its not really underclocking but time functions manipulation), it was strange to me that by manipulating time on my client, I could affect damage calculations on other clients.
After reading this, you will too, understand why this happens. <br>

Many gunz players think that gunz was build with a "LEAD" system, that is not true. "LEAD" is the result of maiet bad system. <br>
In theory maiet "NO-LEAD" system works like this: <br>
* each client store the last 200 positions of all the players in the room (10 positions per 1 sec = 20 seconds worth of positions) <br>
* when a client recieve a shot packet, calculate the approximative shot time <br>
* based on the calculated time, get from the positions list 2 positions + directions, use these 2 positions + directions to predict a third position (to cover player movement), use this third position and the info from the shot packet (position + direction + spread) to determine if a player was hit or not.

On paper: this system is fairly good, you would have high accuracy of damage. <br>
In practice: doesn't work, relays on very stable connection between clients, very exploitable, maiet fucked up. <br>
 <br>


Why it doesn't work, and instead we have this "LEAD" system? <br>
the main error is here: <br>

in ZGame::OnPeerShot: <br>

    fShotTime-=pOwnerCharacter->m_fTimeOffset;
    
m_fTimeOffset is being calculated as the difference between the game time of our client and the sender client, (it doesn't compensate distance between computers) <br>
so 99.9% of the time, fShotTime - pOwnerCharacter->m_fTimeOffset == ZGame::GetTime() or in words, our current client game time. <br>
This means that, that our newest (== current position) will be used to determine if we were hit or not, hence why we are getting a "LEAD" system. <br>
Now, when someone is "ucing" (it also needs to be the right amount relative to the distance to the opponent), the fShotTime he sends is lower, so an older position of ours will be used in the damage calculation, hence we are getting damaged, or in other words maiet "NO-LEAD" working as intended. <br>
 <br>
one way to fix maiet "NO-LEAD" would be to subtract from fShotTime also (Sender_Ping / 1000.0f) or something like that, but it will still be a horrible system. <br>


Now for the patch: <br>

in ZActor::HitTest: <br>
change <br>

    if(!GetHistory(&footpos,&actor_dir,fTime)) return ZOH_NONE;
to

    if(!ZObject::GetHistory(&footpos,&actor_dir,fTime)) return ZOH_NONE;
    
in ZCharacter::HitTest:
change

    if(GetHistory(&footpos,&characterdir,fTime))
to 

    if(ZObject::GetHistory(&footpos,&characterdir,fTime))
    

ZObject::GetHistory will return the current position and direction of the object, if you modified this method, take this in consideration. <br>

I hope this will inspire other coders, to try and fix things themselves, or to try and actually research and understand better the code they are using. <br>

- Updated <br>

btw this does not fix slow player movement, it should not matter, as they will be only hurting themselves this way without benefits.  <br>
    
    
    
