Open(ZGameInterface.cpp) <br>
Find <br>

    char* pszAgentIP =
    
Replace <br>

    char* pszAgentIP = _AGENT_IP;

Open(MMatchConfig.h) <br>
Find <br>

    #define SERVER_CONFIG_DEFAULT_NJ_DBAGENT_IP	

Replace <br>

    #define SERVER_CONFIG_DEFAULT_NJ_DBAGENT_IP			_AGENT_IP


Open(MFeatureDefine.h) <br>
Add <br>

    #define _AGENT_IP "127.0.0.1"
    
Replace <br>

    #define _AGENT_IP "YOUR IP ADDRESS"
