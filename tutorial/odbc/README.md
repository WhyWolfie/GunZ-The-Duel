# GunZ ODBC Data Source Setup (GunzDB)

Quick tutorial to configure the **ODBC connection** for GunZ private servers.  
This connects your MatchServer / server executables to the **GunzDB** database.

**Time required:** Less than 1 minute  
**Requirements:**  
- Microsoft SQL Server installed and running (with GunzDB database restored)  
- Windows (uses built-in ODBC Data Source Administrator 32-bit)

## Step-by-step Guide

1. **Open ODBC Data Source Administrator (32-bit)**  
   Press `Win + R` → type `odbcad32.exe` → press Enter  
   *(Important: Use the **32-bit** version even on 64-bit Windows, as most GunZ servers are 32-bit.)*

   <img src="https://i.imgur.com/1kC9nLT.png" alt="ODBC Administrator window" width="600">

2. **Click Add**  
   Go to the **System DSN** tab (recommended for servers) → click **Add**.

   <img src="https://i.imgur.com/b7GePDM.png" alt="Add new data source" width="600">

3. **Select SQL Server driver**  
   Choose **SQL Server** → click **Finish**.

   <img src="https://i.imgur.com/sBkzB7v.png" alt="Select SQL Server" width="600">

4. **Configure basic settings**  
   - **Name:** `GunzDB` (must be exactly this for most GunZ servers)  
   - **Description:** (optional) GunZ Database Connection  
   - **Server:** Enter your SQL Server name/instance  
     (e.g. `localhost\SQLEXPRESS`, `YOURPCNAME\SQLEXPRESS`, or `.` for local default instance)

   <img src="https://i.imgur.com/zo27nKD.png" alt="Name and server" width="600">

5. **Choose authentication method**  
   Select **SQL Server authentication** (recommended)  
   Check **Connect to SQL Server to obtain default settings...**  
   Enter your SQL login (usually **sa**) and password.

   <img src="https://i.imgur.com/zo27nKD.png" alt="Authentication" width="600">

6. **Set default database**  
   Check **Change the default database to:**  
   Select **GunzDB** from the dropdown.

   <img src="https://i.imgur.com/k3JEHVB.png" alt="Default database" width="600">

7. **Set language (optional but recommended)**  
   Change the language of SQL Server system messages to: **English**  
   *(Helps avoid encoding/collation issues in logs)*

8. **Finish configuration**  
   Click **Next** → **Finish**.

   <img src="https://i.imgur.com/Dljb2sd.png" alt="Summary screen" width="600">

9. **Test the connection**  
   Click **Test Data Source**.  
   You should see:  
   **TESTS COMPLETED SUCCESSFULLY!**

   <img src="https://i.imgur.com/HnInX8H.png" alt="Test successful" width="600">

10. **Save**  
    Click **OK** to close all windows.

    <img src="https://i.imgur.com/mflR8KF.png" alt="Final OK" width="600">

Done! Your GunZ server should now be able to connect to the database using DSN = `GunzDB`.

## Troubleshooting Tips
- Connection failed? → Double-check server name, sa password, and that SQL Server allows SQL authentication (Mixed Mode).
- "Data source name not found" → Make sure you created it in **System DSN** (not User DSN).
- 64-bit machine issues → Always use `odbcad32.exe` (32-bit), not the 64-bit version.
- Still stuck? Check your server's `server.ini` / config file — it should reference `DSN=GunzDB`.
