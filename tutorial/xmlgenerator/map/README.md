# Map XML Generator  
Quick tool for generating/updating GunZ: The Duel map entries in `System/Map.xml` and `ChannelRule.xml`

## Download  
🔗 [Map Xml Generator.zip](https://github.com/WhyWolfie/GunZ-The-Duel/blob/master/Tools/xmlgenerator/Map%20Xml%20Generator.zip)

## Usage (4 simple steps)

1. **Extract** the archive  
   Unzip `Map Xml Generator.zip` into your `Gunz/Maps`

   <img src="https://i.imgur.com/ryoQHHa.png" width="520" alt="Tool interface screenshot">

2. **Move** the executable  
   Copy `Map Xml Generator.exe` into your server's `System/Map.xml` and `System/ChannelRule.xml` & `MatchServer` folder

   <img src="https://i.imgur.com/ro0FqNE.png" width="520" alt="Maps folder with exe">

3. **Generate & Replace** XML content  
   - Run `Map Xml Generator.exe`  
   - Press **Ctrl+A** → **Ctrl+C** (copy all generated text)  
   - Open `System/Map.xml` and `System/ChannelRule.xml` (usually in MatchServer folder)  
   - Replace the old map/channel entries with the copied content (**Ctrl+V**)

4. **Update ChannelRule.xml**  
   Make sure the channel name matches your setup (e.g. `novice`, `train`, `newbie`, etc.)

   ```xml
   <!-- Example snippet in ChannelRule.xml -->
   <CHANNEL NAME="novice" ...>
       <!-- your new map entries appear here -->
   </CHANNEL>
