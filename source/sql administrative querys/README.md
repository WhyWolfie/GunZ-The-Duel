<b>SQL Administrative Querys</b><br>

Query to find how many STAFFs are in the database!:

    SELECT UgradeID FROM Account WHERE UGRADEID ='255'SELECT UgradeID FROM Account WHERE UGRADEID = '254'SELECT UgradeID FROM Account WHERE UGRADEID ='252'

Query to Send Coins and Evcoins!

    UPDATE Account SET Coins ='9999999' WHERE UserID ='Vamp'UPDATE Account SET EvCoins ='9999999' WHERE UserID ='Vamp'

Query to change the User password!

    UPDATE Login SET password ='123456' WHERE UserID ='Vamp'

Color Name Query Query!

    UPDATE ACCOUNT SET UGradeID='10' WHERE USERID='Vamp'

Query to ban!

    UPDATE ACCOUNT SET UGradeID='253' WHERE USERID='Vamp'

Quezy Remove Player Item:

    DELETE FROM CharacterItem WHERE CID ='CID Do Cara' AND ItemID ='ID Do Item'DELETE FROM AccountItem WHERE AID ='AID Do Cara' AND ItemID ='ID Do Item'

Query Remove item from all players:

    DELETE FROM CharacterItem WHERE ItemID ='ID Do Item'DELETE FROM AccountItem WHERE ItemID ='ID Do Item'

Query Submit Item "One" for Inventory:

    INSERT INTO CharacterItem(CID, ItemID, RegDate)VALUES('Cid do Player','Id do Item',GETDATE()

Query Sending Item to Everyone Bank:

    INSERT INTO AccountItem(AID, ItemID, RentDate, cnt)(SELECT ac.AID,'Id do Item',GETDATE(),1 FROM AccountItem(nolock) ac)

Query Zeroing all level of all characters:

    UPDATE Character SET Level =1, XP =0, BP =1000

Query Zeroing Coins all Accounts:

    UPDATE Login SET RZCoins='0'UPDATE Login SET EVCoins='0'

Query Send Coins To All Accounts:

    UPDATE Login SET RZCoins='0'+ CoinsUPDATE Login SET EVCoins='0'+ Coins










