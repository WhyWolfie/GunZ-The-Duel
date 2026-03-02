# GunZ Map Debugger (GMD)

Simple tool that helps you quickly load and debug custom maps in **GunZ: The Duel**.

## How to Use

1. **Download & Extract**  
   Extract `GMD.exe` from the release / zip file

2. **Place the executable**  
   Copy `GMD.exe` into your **GunZ Client folder**  
   (the same folder where `Gunz.exe` is located)

3. **Fill in the fields**
   - **Gunz Exe**: usually just `Gunz.exe`  
     (or type the exact name if you renamed your client executable)
   - **Map Name**: enter the map file name **without** the `.rs` / `.xml` extension  
     Examples:
     - `mansion`
     - `town`
     - `battlearena`
     - `workshop_test`

4. **Press Run** 🚀

![GunZ Map Debugger Interface](https://i.imgur.com/6JrMHBr.png)

<br>

## Quick Tips

- Make sure your map files (`.rs`, `.xml`, `.col`, textures etc.) are already placed in the correct locations (`Maps/`, `Model/`, `Maps/<mapname>/` etc.)
- The tool launches GunZ with map loading parameters automatically
- Useful for fast testing of lighting, collision, spawn points, etc.
