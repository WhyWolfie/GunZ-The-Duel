1. ZConfiguration.cpp
Below:

        childElement.GetChildContents(&m_Mouse.bInvert, ZTOK_MOUSE_INVERT);

Add:

      childElement.GetChildContents(&m_Mouse.fSensiSni, ZTOK_MOUSE_SENSISNI);

Search for:

    m_Mouse.fSensitivity = ValidateMouseSensitivityInFloat(m_Mouse.fSensitivity);
    *Code
    *to
    aElement.SetContents(temp);

Add below:

    parentElement.AppendText("\n\t\t");
    aElement = parentElement.CreateChildElement(ZTOK_MOUSE_SENSISNI);
    m_Mouse.fSensiSni = ValidateSensiSniInFloat(m_Mouse.fSensiSni);
    sprintf(temp, "%f", m_Mouse.fSensiSni);
    aElement.SetContents(temp);

Search for:

    m_Mouse.bInvert = false;

Add below:

    m_Mouse.fSensiSni = 1.f;

Search for:

    int ZConfiguration::SetMouseSensitivityInInt(int i)

below of this code block, add:

    int ZConfiguration::ValidateSensiSniInInt(int i)
    {
        if (i < MOUSE_SENSISNI_MIN)
            i = MOUSE_SENSISNI_MIN;
    
        else if (i > MOUSE_SENSISNI_MAX)
            i = MOUSE_SENSISNI_MAX;
    
        return i;
    }
    
    float ZConfiguration::ValidateSensiSniInFloat(float f)
    {
        return ValidateSensiSniInInt(f * MOUSE_SENSISNI_MAX) / float(MOUSE_SENSISNI_MAX);
    }
    
    float ZConfiguration::GetSensiSniInFloat()
    {
        return Z_MOUSE_SENSISNI;
    }
    
    int ZConfiguration::GetSensiSniInInt()
    {
        return (int(ZGetConfiguration()->GetMouse()->fSensiSni * MOUSE_SENSISNI_MAX));
    }
    
    float ZConfiguration::SetSensiSniInFloat(float f)
    {
        float validated = ValidateSensiSniInFloat(f);
    
        Z_MOUSE_SENSISNI = validated;
        return validated;
    }
    
    int ZConfiguration::SetSensiSniInInt(int i)
    {
        int validated = ValidateSensiSniInInt(i);
    
        Z_MOUSE_SENSISNI = validated / (float)MOUSE_SENSISNI_MAX;
        return validated;
    }

2. ZConfiguration.h
Search for:

        struct ZCONFIG_MOUSE {

Inside it, add the code:

    float fSensiSni;

Next, search:

    #define MOUSE_SENSITIVITY_MAX 10000

and below:

    #define MOUSE_SENSISNI_MIN 1
    #define MOUSE_SENSISNI_MAX 30

Search for:

    int SetMouseSensitivityInInt(int i);

add below:

    int ValidateSensiSniInInt(int i);
    float ValidateSensiSniInFloat(float f);
    float GetSensiSniInFloat();
    int GetSensiSniInInt();
    float SetSensiSniInFloat(float f);
    int SetSensiSniInInt(int i);

Search:

    #define ZTOK_MOUSE_SENSITIVITY "SENSITIVITY"

Below:

    #define ZTOK_MOUSE_SENSISNI "SENSISNI"

Search:

    #define Z_MOUSE_SENSITIVITY (ZGetConfiguration()->GetMouse()->fSensitivity)

Below:

    #define Z_MOUSE_SENSISNI (ZGetConfiguration()->GetMouse()->fSensiSni)

3. ZGameInterface.cpp
Search:

        SetListenerWidget("MouseSensitivityEdit", ZGetMouseSensitivityEditListener());

Add below it:

    SetListenerWidget("SensiSniSlider", ZGetSensiSniSliderListener());
    SetListenerWidget("SensiSniEdit", ZGetSensiSniEditListener());

4. ZOptionInterface.cpp
Search

        MSlider* pWidget = (MSlider*)pResource->FindWidget("MouseSensitivitySlider");

Add below the entire block of code for the first time :

    pWidget = (MSlider*)pResource->FindWidget("SensiSniSlider");
    if(pWidget)
    {
        pWidget->SetMinMax(MOUSE_SENSISNI_MIN, MOUSE_SENSISNI_MAX);
        pWidget->SetValue(ZGetConfiguration()->GetSensiSniInInt());
    }

add below for the second time:

    pWidget = (MSlider*)pResource->FindWidget("SensiSniSlider");
    Z_MOUSE_SENSISNI = (float)((MSlider*)pWidget)->GetValue() / (float)MOUSE_SENSISNI_MAX;

Search:

    MListener* ZGetMouseSensitivityEditListener(void){

Add below the entire block of code:

    static void SetSensiSniSlider(int i)
    {
        ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
        MSlider* pSlider = (MSlider*)pResource->FindWidget("SensiSniSlider");
        if (pSlider)
        {
            pSlider->SetValue(i);
        }
    }
    static void SetSensiSniEdit(int i)
    {
        ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
        MEdit* pEdit = (MEdit*)pResource->FindWidget("SensiSniEdit");
        if (pEdit)
        {
            char sz[1024] = "";
            sprintf(sz, "%d", i);
            pEdit->SetText(sz);
        }
    }
    
    BEGIN_IMPLEMENT_LISTENER(ZGetSensiSniSliderListener, MLIST_VALUE_CHANGED)
        ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
        MSlider* pSlider = (MSlider*)pResource->FindWidget("SensiSniSlider");
        if (pSlider != NULL)
        {
            int i = ZGetConfiguration()->ValidateSensiSniInInt(pSlider->GetValue());
            SetSensiSniEdit(i);
        }
    END_IMPLEMENT_LISTENER()
    
    MListener* ZGetSensiSniEditListener(void){
        class ListenerClass : public MListener
        {
        public:
            virtual bool OnCommand(MWidget* pWidget, const char* szMessage){
                ZIDLResource* pResource = ZApplication::GetGameInterface()->GetIDLResource();
                MEdit* pEdit = (MEdit*)pResource->FindWidget("SensiSniEdit");
                {
                    int i = atoi(pEdit->GetText());
                    int v = ZGetConfiguration()->ValidateSensiSniInInt(i);
    
                    if (MWidget::IsMsg(szMessage, MEDIT_CHAR_MSG) == true)
                    {
                        SetSensiSniSlider(v);
                        return true;
                    }
                    else if (MWidget::IsMsg(szMessage, MEDIT_KILL_FOCUS) == true)
                    {
                        SetSensiSniSlider(v);
                        SetSensiSniEdit(v);
                        return true;
                    }
                }
                return false;
            }
        };
        static ListenerClass Listener;
        return &Listener;
    }


5. ZOptionInterface.h
Below:

        DECLARE_LISTENER(ZGetMouseSensitivityEditListener)

Add:

    DECLARE_LISTENER(ZGetSensiSniSliderListener)
    DECLARE_LISTENER(ZGetSensiSniEditListener)

6. ZWeaponScreenEffect.cpp
At the top of the file, add:


       #include "ZConfiguration.h"

Search for:

    void ZWeaponScreenEffect::InitWeapon(MMatchWeaponType nWeaponType)


Replace all with:

    void ZWeaponScreenEffect::InitWeapon(MMatchWeaponType nWeaponType)
    {
        switch (nWeaponType)
        {
        case MWT_SNIFER:
            {
                // sniper mode save the current FOV and set the new one
                // g_fFOV = D3DXToRadian(currentFOV / 2.0f); // Half the FOV for sniper mode
                g_fFOV = (40.0f / 180.0f * pi); // Set the FOV to 40 degrees when opening the scope
                // Save the current mouse sensitivity
                originalSensitivity = ZGetConfiguration()->GetMouseSensitivityInFloat();
                // Change the mouse sensitivity
                ZGetConfiguration()->SetMouseSensitivityInFloat(originalSensitivity * ZGetConfiguration()->GetSensiSniInFloat());
            }
            break;
        }
    }


Next, you'll see:

    void ZWeaponScreenEffect::FinalWeapon(MMatchWeaponType nWeaponType)

Replace all with:

    void ZWeaponScreenEffect::FinalWeapon(MMatchWeaponType nWeaponType)
    {
        switch (nWeaponType)
        {
        case MWT_SNIFER:
            {
                // sniper mode restore the FOV and set the new one
                float currentFOV = ZGetConfiguration()->GetEtc()->fFOV;
                g_fFOV = D3DXToRadian(currentFOV); // Restore the FOV to its original value when closing the scope
                // Restore the mouse sensitivity
                ZGetConfiguration()->SetMouseSensitivityInFloat(originalSensitivity);
            }
            break;
        }
    }

7. ZWeaponScreenEffect.h
Below:

        virtual ~ZWeaponScreenEffect();

Add:

    float originalSensitivity;

8. Decompile your default.mrs and open option.xml
Search:

        <EDIT item="MouseSensitivityEdit" parent="KeyboardOptionGroup5">

At the end of this block of code, add:

    <LABEL item="Label" parent="KeyboardOptionGroup5">
        <FONT>FONTa9</FONT>
        <TEXTCOLOR>
            <R>205</R>
            <G>205</G>
            <B>205</B>
        </TEXTCOLOR>
        <BOUNDS>
            <X>0</X>
            <Y>90</Y>
            <W>300</W>
            <H>24</H>
        </BOUNDS>
        <TEXT>Sniper Sensitivity</TEXT>
    </LABEL>
    <SLIDER item="SensiSniSlider" parent="KeyboardOptionGroup5">
        <BOUNDS>
            <X>160</X>
            <Y>90</Y>
            <W>160</W>
            <H>24</H>
        </BOUNDS>
        <ALIGN>
            <HALIGN>right</HALIGN>
        </ALIGN>
    </SLIDER>
    <EDIT item="SensiSniEdit" parent="KeyboardOptionGroup5">
        <BOUNDS>
            <X>100</X>
            <Y>90</Y>
            <W>60</W>
            <H>24</H>
        </BOUNDS>
    </EDIT>



Credits To Diguhey

