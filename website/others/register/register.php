<div align="center">
<?PHP 
mssql_select_db($DB);?>
<FORM METHOD=POST ACTION="<?php echo $_SERVER['PHP_SELF']; ?>?op=register&act=register">
<table cellspacing=0 border=0>
<tr>

</CENTER></td>
<td style="border-left: #FFFFFF">&nbsp;User ID : </td>
<td style="border-right: #FFFFFF"><INPUT TYPE="text" NAME="login"&nbsp;></td>
</tr>
<tr>
<td style="border-left: #FFFFFF">&nbsp;Password : </td>
<td style="border-right: #FFFFFF"><INPUT TYPE="password" NAME="senha1">&nbsp;</td>
</tr>
<tr>
<td style="border-left: #FFFFFF">&nbsp;Repeat Password : &nbsp;</td>
<td style="border-right: #FFFFFF"><INPUT TYPE="password" NAME="senha2">&nbsp;</td>
</tr>
<tr>
<td style="border-left: #FFFFFF">&nbsp;E-Mail : </td>
<td style="border-right: #FFFFCC"><INPUT TYPE="text" NAME="email">&nbsp;</td>
</tr>
<tr>
  <td style="border-left: #FFFFFF">&nbsp;Name : </td>
  <td style="border-right: #FFFFFF"><input name="name" type="text" id="name"></td>
</tr>
<tr>
  <td style="border-left: #FFFFFF">&nbsp;Age : </td>
  <td style="border-right: #FFFFFF"><input name="age" type="text" id="age"></td>
</tr>
<tr>
  <td style="border-left: #FFFFFF">&nbsp;Country : </td>
  <td style="border-right: #FFFFFF"><select name="country">
<option value=""></option>
<option value="AF">Afghanistan</option>
<option value="AL">Albania</option>
<option value="DZ">Algeria</option>
<option value="AS">American Samoa</option>
<option value="AD">Andorra</option>
<option value="AG">Angola</option>
<option value="AI">Anguilla</option>
<option value="AG">Antigua & Barbuda</option>
<option value="AR">Argentina</option>
<option value="AA">Armenia</option>
<option value="AW">Aruba</option>
<option value="AU">Australia</option>
<option value="AT">Austria</option>
<option value="AZ">Azerbaijan</option>
<option value="BS">Bahamas</option>
<option value="BH">Bahrain</option>
<option value="BD">Bangladesh</option>
<option value="BB">Barbados</option>
<option value="BY">Belarus</option>
<option value="BE">Belgium</option>
<option value="BZ">Belize</option>
<option value="BJ">Benin</option>
<option value="BM">Bermuda</option>
<option value="BT">Bhutan</option>
<option value="BO">Bolivia</option>
<option value="BL">Bonaire</option>
<option value="BA">Bosnia & Herzegovina</option>
<option value="BW">Botswana</option>
<option value="BR">Brazil</option>
<option value="BC">British Indian Ocean Ter</option>
<option value="BN">Brunei</option>
<option value="BG">Bulgaria</option>
<option value="BF">Burkina Faso</option>
<option value="BI">Burundi</option>
<option value="KH">Cambodia</option>
<option value="CM">Cameroon</option>
<option value="CA">Canada</option>
<option value="IC">Canary Islands</option>
<option value="CV">Cape Verde</option>
<option value="KY">Cayman Islands</option>
<option value="CF">Central African Republic</option>
<option value="TD">Chad</option>
<option value="CD">Channel Islands</option>
<option value="CL">Chile</option>
<option value="CN">China</option>
<option value="CI">Christmas Island</option>
<option value="CS">Cocos Island</option>
<option value="CO">Columbia</option>
<option value="CC">Comoros</option>
<option value="CG">Congo</option>
<option value="CK">Cook Islands</option>
<option value="CR">Costa Rica</option>
<option value="CT">Cote D'Ivoire</option>
<option value="HR">Croatia</option>
<option value="CU">Cuba</option>
<option value="CB">Curacao</option>
<option value="CY">Cyprus</option>
<option value="CZ">Czech Republic</option>
<option value="DK">Denmark</option>
<option value="DJ">Djibouti</option>
<option value="DM">Dominica</option>
<option value="DO">Dominican Republic</option>
<option value="TM">East Timor</option>
<option value="EC">Ecuador</option>
<option value="EG">Egypt</option>
<option value="SV">El Salvador</option>
<option value="GQ">Equatorial Guinea</option>
<option value="ER">Eritrea</option>
<option value="EE">Estonia</option>
<option value="ET">Ethiopia</option>
<option value="FA">Falkland Islands</option>
<option value="FO">Faroe Islands</option>
<option value="FJ">Fiji</option>
<option value="FI">Finland</option>
<option value="FR">France</option>
<option value="GF">French Guiana</option>
<option value="PF">French Polynesia</option>
<option value="FS">French Southern Ter</option>
<option value="GA">Gabon</option>
<option value="GM">Gambia</option>
<option value="GE">Georgia</option>
<option value="DE">Germany</option>
<option value="GH">Ghana</option>
<option value="GI">Gibraltar</option>
<option value="GB">Great Britain</option>
<option value="GR">Greece</option>
<option value="GL">Greenland</option>
<option value="GD">Grenada</option>
<option value="GP">Guadeloupe</option>
<option value="GU">Guam</option>
<option value="GT">Guatemala</option>
<option value="GN">Guinea</option>
<option value="GY">Guyana</option>
<option value="HT">Haiti</option>
<option value="HW">Hawaii</option>
<option value="HN">Honduras</option>
<option value="HK">Hong Kong</option>
<option value="HU">Hungary</option>
<option value="IS">Iceland</option>
<option value="IN">India</option>
<option value="ID">Indonesia</option>
<option value="IA">Iran</option>
<option value="IQ">Iraq</option>
<option value="IR">Ireland</option>
<option value="IM">Isle of Man</option>
<option value="IL">Israel</option>
<option value="IT">Italy</option>
<option value="JM">Jamaica</option>
<option value="JP">Japan</option>
<option value="JO">Jordan</option>
<option value="KZ">Kazakhstan</option>
<option value="KE">Kenya</option>
<option value="KI">Kiribati</option>
<option value="NK">Korea North</option>
<option value="KS">Korea South</option>
<option value="KW">Kuwait</option>
<option value="KG">Kyrgyzstan</option>
<option value="LA">Laos</option>
<option value="LV">Latvia</option>
<option value="LB">Lebanon</option>
<option value="LS">Lesotho</option>
<option value="LR">Liberia</option>
<option value="LY">Libya</option>
<option value="LI">Liechtenstein</option>
<option value="LT">Lithuania</option>
<option value="LU">Luxembourg</option>
<option value="MO">Macau</option>
<option value="MK">Macedonia</option>
<option value="MG">Madagascar</option>
<option value="MY">Malaysia</option>
<option value="MW">Malawi</option>
<option value="MV">Maldives</option>
<option value="ML">Mali</option>
<option value="MT">Malta</option>
<option value="MH">Marshall Islands</option>
<option value="MQ">Martinique</option>
<option value="MR">Mauritania</option>
<option value="MU">Mauritius</option>
<option value="ME">Mayotte</option>
<option value="MX">Mexico</option>
<option value="MI">Midway Islands</option>
<option value="MD">Moldova</option>
<option value="MC">Monaco</option>
<option value="MN">Mongolia</option>
<option value="MS">Montserrat</option>
<option value="MA">Morocco</option>
<option value="MZ">Mozambique</option>
<option value="MM">Myanmar</option>
<option value="NA">Nambia</option>
<option value="NU">Nauru</option>
<option value="NP">Nepal</option>
<option value="AN">Netherland Antilles</option>
<option value="NL">Netherlands</option>
<option value="NV">Nevis</option>
<option value="NC">New Caledonia</option>
<option value="NZ">New Zealand</option>
<option value="NI">Nicaragua</option>
<option value="NE">Niger</option>
<option value="NG">Nigeria</option>
<option value="NW">Niue</option>
<option value="NF">Norfolk Island</option>
<option value="NO">Norway</option>
<option value="OM">Oman</option>
<option value="PK">Pakistan</option>
<option value="PW">Palau Island</option>
<option value="PS">Palestine</option>
<option value="PA">Panama</option>
<option value="PG">Papua New Guinea</option>
<option value="PY">Paraguay</option>
<option value="PE">Peru</option>
<option value="PH">Philippines</option>
<option value="PO">Pitcairn Island</option>
<option value="PL">Poland</option>
<option value="PT">Portugal</option>
<option value="PR">Puerto Rico</option>
<option value="QA">Qatar</option>
<option value="RE">Reunion</option>
<option value="RO">Romania</option>
<option value="RU">Russia</option>
<option value="RW">Rwanda</option>
<option value="NT">St Barthelemy</option>
<option value="EU">St Eustatius</option>
<option value="HE">St Helena</option>
<option value="KN">St Kitts-Nevis</option>
<option value="LC">St Lucia</option>
<option value="MB">St Maarten</option>
<option value="PM">St Pierre & Miquelon</option>
<option value="VC">St Vincent & Grenadines</option>
<option value="SP">Saipan</option>
<option value="SO">Samoa</option>
<option value="AS">Samoa American</option>
<option value="SM">San Marino</option>
<option value="ST">Sao Tome & Principe</option>
<option value="SA">Saudi Arabia</option>
<option value="SN">Senegal</option>
<option value="SC">Seychelles</option>
<option value="SS">Serbia & Montenegro</option>
<option value="SL">Sierra Leone</option>
<option value="SG">Singapore</option>
<option value="SK">Slovakia</option>
<option value="SI">Slovenia</option>
<option value="SB">Solomon Islands</option>
<option value="OI">Somalia</option>
<option value="ZA">South Africa</option>
<option value="ES">Spain</option>
<option value="LK">Sri Lanka</option>
<option value="SD">Sudan</option>
<option value="SR">Suriname</option>
<option value="SZ">Swaziland</option>
<option value="SE">Sweden</option>
<option value="CH">Switzerland</option>
<option value="SY">Syria</option>
<option value="TA">Tahiti</option>
<option value="TW">Taiwan</option>
<option value="TJ">Tajikistan</option>
<option value="TZ">Tanzania</option>
<option value="TH">Thailand</option>
<option value="TG">Togo</option>
<option value="TK">Tokelau</option>
<option value="TO">Tonga</option>
<option value="TT">Trinidad & Tobago</option>
<option value="TN">Tunisia</option>
<option value="TR">Turkey</option>
<option value="TU">Turkmenistan</option>
<option value="TC">Turks & Caicos Is</option>
<option value="TV">Tuvalu</option>
<option value="UG">Uganda</option>
<option value="UA">Ukraine</option>
<option value="AE">United Arab Emirates</option>
<option value="GB">United Kingdom</option>
<option value="US">United States of America</option>
<option value="UY">Uruguay</option>
<option value="UZ">Uzbekistan</option>
<option value="VU">Vanuatu</option>
<option value="VS">Vatican City State</option>
<option value="VE">Venezuela</option>
<option value="VN">Vietnam</option>
<option value="VB">Virgin Islands (Brit)</option>
<option value="VA">Virgin Islands (USA)</option>
<option value="WK">Wake Island</option>
<option value="WF">Wallis & Futana Is</option>
<option value="YE">Yemen</option>
<option value="ZR">Zaire</option>
<option value="ZM">Zambia</option>
<option value="ZW">Zimbabwe</option>
</select></td>
</tr>
<tr>
  <td style="border-left: #FFFFCC">&nbsp;Sex : </td>
  <td style="border-right: #FFFFCC"><select name="sex" id="sex">
    <option value="0">Male</option>
    <option value="1">Female</option>
  </select>  </td>
</tr>
<tr>
<td style="border: #FFFFFF; border-top: 0px;" colspan=2><CENTER><INPUT NAME="Cadastrar" VALUE="Register" TYPE="submit">
    <input type="reset" name="Reset" value="Reset">
</CENTER></td>
</tr>
</table>
</FORM>
<?php
if ($_GET['act'] == 'register')
{
	$user = anti_injection($_POST['login']);
    $pass1 = anti_injection($_POST['senha1']);
    $pass2 = anti_injection($_POST['senha2']);
    $email = anti_injection($_POST['email']);
	$age = anti_injection($_POST['age']);
	$country = anti_injection($_POST['country']);
	$name = anti_injection($_POST['name']);
	$sex = anti_injection($_POST['sex']);
    if (valida(Array($user,$pass1,$pass2,$email,$name,$age)) == true)
    {
        if ($pass1 == $pass2)
        {
            if (ereg("([0-9,a-z,A-Z])", $user))
            {
                if (ereg("^([0-9,a-z,A-Z]+)([.,_]([0-9,a-z,A-Z]+))*[@]([0-9,a-z,A-Z]+)([.,_,-]([0-9,a-z,A-Z]+))*[.]([0-9,a-z,A-Z]){2}([0-9,a-z,A-Z])?$", $email))
                {
                    $query = mssql_query("SELECT UserID FROM Account WHERE UserID='$user'");
                    $num_rows = mssql_num_rows($query);
                    if ($num_rows == 0)
                    {
                        $query = mssql_query("SELECT * FROM Account WHERE EMail='$email'");
                        $num_rows = mssql_num_rows($query);
                        if ($num_rows == 0)
                        {
                            $query = mssql_query("DECLARE @RC int DECLARE @UserID varchar(20) DECLARE @Password varchar(20) DECLARE @Cert tinyint DECLARE @Name varchar(30) DECLARE @Age smallint DECLARE @Country char(3) DECLARE @Sex tinyint DECLARE @Email varchar(50) DECLARE @Ret int EXECUTE @RC = spWebInsertAccount @UserID = '$user' ,@Password = '$pass1' ,@Cert = '1' ,@Name = '$name' ,@Age = '$age' ,@Country = '$country' ,@Sex = '$sex' ,@Email = '$email' ,@Ret = '1'");
                            if (!$query)
                            {
                                echo ":: Error on account register try later ::<br>";
                            }
                            else
                            {
                                echo ":: Your Account is made succesfully. ::<br>";
																}
								
                            }
                        }
                        else
                        {
                            echo ":: Email already in use ::<br>";
                        }
                    }
                    else
                    {
                        echo ":: User already in use ::<br>";
                    }
                }
                else
                {
                    echo ":: Invalid Email ::<br>";
                }
            }
            else
            {
                echo ":: Only use Numbers and Letters in User ID ::<br>";
            }
        }
        else
        {
            echo ":: Password not equal with other ::<br>";
        }
    }

// Funo Anti Injection

function anti_injection($sql)
{
$sql = preg_replace(sql_regcase("/(from|select|insert|delete|where|drop table|show tables|#|\*|--|\\\\)/"),"",$sql);
$sql = trim($sql);
$sql = strip_tags($sql);
$sql = addslashes($sql);
return $sql;
}

"<br><B>Gunz Server Status : </B> ";
?>
<br>


<style type="text/css">
<!--
body
{
  


}
.style1 {
    color: #FF000;
    font-weight: bold;
}

.OFFLINE
{    color: #FF0000;}
.ONLINE
{    color: #009933;}
-->
</style>

</head>

<body onselectstart="return false;" oncontextmenu="return false;">

<?PHP

$_host_name = '127.0.0.1'; $_servers = Array(

"Quest Server"=> 6000,
"Clan Server"=> 6010,
"Match Server"=> 6025,
);


foreach($_servers as $_servername => $_port)
{    $_connection = @fsockopen($_host_name, $_port, $errno, $errstr, 0.003);

    if(!$_connection)
    {        $_status = '<span class="OFFLINE">offline</span>';    }
    else
    {
        $_status = '<span class="ONLINE">online</span>';
    }

    print '<span class="style1">';

    print $_servername . ' - ' . $_status . '<br />';

    print '</style>';}



// Verificar Campos Vazios

function valida($campos){
  foreach($campos as $c){
      if(empty($c)){
        echo ":: All fields needed ::<br>";
        return false;
      }else{
        return true;
      }
  }
}
?>
</div>
