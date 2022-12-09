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



























