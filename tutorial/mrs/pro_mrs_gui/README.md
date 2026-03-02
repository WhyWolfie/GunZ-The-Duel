# Pro MRS GUI - Custom Encryption Tutorial

Simple guide to create a custom-encrypted `MRS.EXE` and repack `system.mrs` with your own key using **Pro MRS GUI**.

**Files needed**
- [MRS_GUI.zip](https://github.com/WhyWolfie/GunZ-The-Duel/blob/master/Tools/MRS/MRS_GUI.zip) (contains Pro MRS GUI.exe)
- Original `system.mrs` from GunZ client 1.5

**Credits**  
Tool created by **Yuri Lopes (Ryokusei)**

## Step-by-Step Guide

1. Extract and open **MRS_GUI.exe** (run as administrator if needed).  
   ![Main GUI](https://i.imgur.com/spTW4ME.png)

2. Go to **File → MRS Custom Encrypter**.  
   ![Custom Encrypter Menu](https://i.imgur.com/A9TDcCm.png)

3. Enter your desired encryption key (e.g. `69`) and click **Create**.  
   ![Enter Key](https://i.imgur.com/WhBXvYC.png)

4. Choose a folder and save the file as `mrs_custom.exe` (or any name you prefer).  
   ![Save Location](https://i.imgur.com/HESgjNu.png)

5. Confirm: "File 'mrs_custom.exe' was successfully created". Click **OK**.

6. Back in the main window, **Decompile** your original `system.mrs`.  
   ![Decompile Original](https://i.imgur.com/1BjeArJ.png)

7. Wait until decompilation finishes — you'll see the extracted files in a new folder.  
   ![Decompiled Files](https://i.imgur.com/Vv7dMKT.png)

8. Go to **System → Compile (Encrypted MRS)**.  
   Use your custom key from step 3 if prompted (or it may auto-detect if using the new exe).  
   ![Compile Encrypted](https://i.imgur.com/pzrUqwh.png)

9. A new encrypted `system.mrs` is generated. Delete the temporary extracted folder (e.g. `system`).

10. Test: Try to **Decompile** the new `system.mrs` → it should fail (because it's now encrypted with your custom key).  
    ![Decompile Fails](https://i.imgur.com/G4D2kad.png)

11. To open it again → use **Decompile (Encrypted MRS)** and provide your custom key (or use your new `mrs_custom.exe` as the loader).  
    ![Decompile Encrypted Option](https://i.imgur.com/iisd4uv.png)

**Done!**  
You've successfully created and applied a custom encryption key to your MRS files.
