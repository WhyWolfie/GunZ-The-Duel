<b>Room with empty name</b><br>
Today I was poking around in my source I found a way for people not to create a room with an empty name.
And code is free for anyone who wants to update it.

ZInterfaceListener.cpp
Search: BEGIN_IMPLEMENT_LISTENER(ZGetStageCreateBtnListener, MBTN_CLK_MSG)

    if (strlen(szStageName) == NULL)
    {
        ZGetGameInterface()->ShowMessage("Enter a name to create your room.");
    }
