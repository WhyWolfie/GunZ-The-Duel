# GunZ: The Duel – .MRS Files Tutorial  
**Unpack (Decompile) / Pack (Compile) using MRSDecompiler Ultimate**

**MRSDecompiler Ultimate** is a classic tool (originally by XZeenon ~2010) for extracting and repacking `.mrs` archives in GunZ: The Duel clients — most commonly used for editing `system.mrs` (XML configs like zitem.xml, interface, quests, etc.).

## Download
Download MRSDecompiler Ultimate here:  
[https://github.com/WhyWolfie/GunZ-The-Duel/blob/master/Tools/MRS/MRSDecompiler%20Ultimate.zip](https://github.com/WhyWolfie/GunZ-The-Duel/blob/master/Tools/MRS/MRSDecompiler%20Ultimate.zip)

## Preparation
1. Download and extract the ZIP to any folder (recommended: `C:\GunZ Tools\MRSDecompiler Ultimate\`).
2. Copy the `.mrs` file you want to edit (usually `system.mrs`) into the same folder as `MRSDecompiler Ultimate.exe`.

## Decompile (Unpack / Extract) .MRS Files

Goal: Extract contents (XMLs, DDS textures, sounds, etc.) into a folder.

1. Double-click **MRSDecompiler Ultimate.exe** to launch.
2. In the left panel ("Decompile"), find and select your `.mrs` file (e.g. `system.mrs`).
3. Click **Decompile Selected Item(s)**.

   ![Decompile interface example](https://i.imgur.com/kBwC0ut.png)

4. Wait for the success popup → click **OK**.

   ![Success notification](https://i.imgur.com/h1iuTOP.png)

5. A new folder appears (e.g. `system/`) containing all extracted files.  
   → Done! Edit files with Notepad++, GIMP/Photoshop, etc.

## Compile (Pack / Repack) .MRS Files

Goal: Rebuild the edited folder back into a valid `.mrs` file.

1. Ensure the folder name matches the original `.mrs` name **without** the extension  
   (Example: folder `system/` → becomes `system.mrs`).

2. Launch **MRSDecompiler Ultimate.exe** again.
3. In the right panel ("Compile"), select the **folder** (e.g. `system/` — it appears as a directory).
4. Click **Compile Selected Item(s)**.

   ![Compile interface example](https://i.imgur.com/dxGFrbI.png)

5. Wait for the success popup → click **OK**.

   ![Success notification](https://i.imgur.com/ziIUDBm.png)

6. A new/updated `.mrs` file is created in the same directory.  
   → Done! Replace it in your GunZ client folder.

   ![Compiled result](https://i.imgur.com/ziIUDBm.png)
