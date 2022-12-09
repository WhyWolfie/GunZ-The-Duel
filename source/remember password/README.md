Open(Login.xml) <br>
Find <br>

	<!-- Edit : 비밀번호 입력창 -->
	<EDIT item="LoginPassword" parent="LoginFrame">
		<EDITLOOK>NullEditLook</EDITLOOK>
		<PASSWORD>true</PASSWORD>
		<BOUNDS>
			<X>283</X>
			<Y>105</Y>
			<W>105</W>
			<H>22</H>
		</BOUNDS>
		<TEXT></TEXT>
		<VISIBLE>true</VISIBLE>
	</EDIT>

Add under <br>


	<!-- REMEMBER PASSWORD -->
	<LABEL item="Label_Password_Remember" parent="LoginFrame">
		<FONT>FONTa10_O2Wht</FONT>
		<TEXTCOLOR>
			<R>200</R>
			<G>200</G>
			<B>200</B>
		</TEXTCOLOR>
		<BOUNDS>
			<X>300</X>
			<Y>130</Y>
			<W>150</W>
			<H>22</H>
		</BOUNDS>
		<TEXT>Remember Password</TEXT> <!-- TEMP -->
		<VISIBLE>true</VISIBLE>
	</LABEL>

	<BUTTON item="LoginRememberPass" parent="LoginFrame">
		<BUTTONLOOK>Custom1ButtonLook</BUTTONLOOK>
		<PUSHBUTTON/>
		<BOUNDS>
			<X>275</X>
			<Y>130</Y>
			<W>130</W>
			<H>24</H>
		</BOUNDS>
	</BUTTON>

Open(ZGameInterface.cpp) <br>
Find <br>

	void ZGameInterface::OnLoginDestroy(void)

Replace <br>

	void ZGameInterface::OnLoginDestroy(void)
	{
		ShowWidget("Login", false);

		MWidget* pWidget = m_IDLResource.FindWidget("LoginID");
		if (pWidget)
		{
			// �α��� �����ϸ� write �ؾ� �ϳ�.. ���� check out ����� ����� -_-;
			ZGetApplication()->SetSystemValue("LoginID", pWidget->GetText());

			if (m_pBackground)
				m_pBackground->SetScene(LOGIN_SCENE_FALLDOWN);
		}

		pWidget = m_IDLResource.FindWidget("LoginPassword");
		if (pWidget)
		{
			MButton* pw = (MButton*)m_IDLResource.FindWidget("LoginRememberPass");

			if (pw && pWidget)
			{
				if (pw->GetCheck())
				{

					ZGetApplication()->SetSystemValue("LoginPassword", pWidget->GetText());
				}
				else
				{
					ZGetApplication()->SetSystemValue("LoginPassword", "");
				}
			}

			if (m_pBackground)
				m_pBackground->SetScene(LOGIN_SCENE_FALLDOWN);
		}

		// ��� �̹����� �޸𸮷κ��� �����Ѵ�
		if (m_pLoginBG != NULL)
		{
			// ��� �̹����� �����ִ� ������ ��Ʈ�� �̹��� �����͸� �����Ѵ�
			MPicture* pPicture = (MPicture*)m_IDLResource.FindWidget("Login_BackgrdImg");
			if (pPicture)
				pPicture->SetBitmap(NULL);

			delete m_pLoginBG;
			m_pLoginBG = NULL;
		}

		// �г� �̹����� �޸𸮷κ��� �����Ѵ�
		if (m_pLoginPanel != NULL)
		{
			// �г� �̹����� �����ִ� ������ ��Ʈ�� �̹��� �����͸� �����Ѵ�
			MPicture* pPicture = (MPicture*)m_IDLResource.FindWidget("Login_Panel");
			if (pPicture)
				pPicture->SetBitmap(NULL);

			delete m_pLoginPanel;
			m_pLoginPanel = NULL;
		}

		ZGetShop()->Destroy();
	}

Find <br>

	MWidget* pWidget = m_IDLResource.FindWidget("LoginID");
	if (pWidget)
	{
		char buffer[256];
		if (ZGetApplication()->GetSystemValue("LoginID", buffer))
			pWidget->SetText(buffer);
	}

Add under <br>

	pWidget = m_IDLResource.FindWidget("LoginPassword");
	if (pWidget)
	{
		char buffer[256];
		MButton* pw = (MButton*)m_IDLResource.FindWidget("LoginRememberPass");

		if (ZGetApplication()->GetSystemValue("LoginPassword", buffer))
		{
			pWidget->SetText(buffer);
			if (pw)
			{
				if (strcmp(buffer, "") == 0)
					pw->SetCheck(false);
				else
					pw->SetCheck(true);
			}
		}
	}



















