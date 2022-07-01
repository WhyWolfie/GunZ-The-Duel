<b>Enabled Windowed Shop Equipment like UGG</b><br>

File: ZGameInterface.cpp
find: void ZGameInterface::ShowEquipmentDialog(bool bShow)
You can see below

    ShowWidget( "Lobby", false);
    ShowWidget( "Stage", false);
    ShowWidget( "Shop",  false); 
    
Just comment like this:

    //ShowWidget( "Lobby", false);
    //ShowWidget( "Stage", false);
    //ShowWidget( "Shop",  false); 


or delete that
next
find: void ZGameInterface::ShowShopDialog(bool bShow)
inside the function you can see:

    ShowWidget( "Lobby", false);
    ShowWidget( "Stage", false);
    ShowWidget( "Equipment", false); 

just comment or delete that:

    //ShowWidget( "Lobby", false);
    //ShowWidget( "Stage", false);
    //ShowWidget( "Equipment", false); 


Now XML
file: Interface/default/equipment.xml
find: <FRAME item="Equipment">
now overwrite all struct with this:

  
      <FRAME item="Equipment">
          <FRAMELOOK>DefaultFrameLook</FRAMELOOK>
          <BOUNDS>
                  <X>0</X>
                 <Y>0</Y>
                  <W>700</W>
                  <H>550</H>
          </BOUNDS>
          <ALIGN>
                  <HALIGN>center</HALIGN>
                  <VALIGN>center</VALIGN>
          </ALIGN>
          <VISIBLE>TRUE</VISIBLE>
          <RESIZABLE>false</RESIZABLE>
          <TEXT>Equip</TEXT>
      </FRAME> 

  

next file
file: Interface/default/shop.xml
find: <FRAME item="Shop">
now overwrite all struct with this:
  
  
        <FRAME item="Shop">
          <FRAMELOOK>DefaultFrameLook</FRAMELOOK>
          <BOUNDS>
                  <X>0</X>
              <Y>0</Y>
                  <W>700</W>
                  <H>550</H>
          </BOUNDS>
          <ALIGN>
                  <HALIGN>center</HALIGN>
                  <VALIGN>center</VALIGN>
           </ALIGN>
           <VISIBLE>TRUE</VISIBLE>
           <RESIZABLE>false</RESIZABLE>
           <TEXT>Shop</TEXT>
      </FRAME> 
  
You need fix the objects inside the shop/equipment in the files xml shop.xml and equipment.xml
