I see that in most gunz nowadays the problem of crashing in duel mode while you are in observer mode still continues to occur, I found a way that this can be fixed.
It's something simple and easy to add. 

Open: ZGame.cpp
Line: 6509
Old Code:

    if (pObserver && pObserver->IsVisible())
    uidTarget = pObserver->GetTargetCharacter()->GetUID();
    
    
    
New Code:

     if (pObserver && pObserver->IsVisible() && pObserver->GetTargetCharacter()->GetUID() != MUID(0, 0))
        uidTarget = pObserver->GetTargetCharacter()->GetUID();


Credits to: Orby
