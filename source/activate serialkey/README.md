Open(ZApplication.cpp - line 218) <br>
Find <br>

    switch(ZGetLocale()->GetCountry()) {
    case MC_JAPAN:
    case MC_KOREA: 
    
Replace <br>

    switch(ZGetLocale()->GetCountry()) {
    case MC_JAPAN:
    //case MC_KOREA: 

Find <br>

    case MC_US:
    case MC_BRAZIL:
    case MC_INDIA: 
    
Replace <br>

    case MC_US:
    case MC_BRAZIL:
    case MC_INDIA:
    case MC_KOREA: 
    
Open (CGLEncription.h) <br>
Find <br>

    class CGLEncription
    {
    public:
    //    bool CreateSerialKey();

        int Decription( void);
    };
    #endif 
    
Replace <br>

    class CGLEncription
    {
    public:
        bool CreateSerialKey();

        int Decription( void);
    };
    #endif 
