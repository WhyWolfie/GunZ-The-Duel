Fix for jur13n source 1.5
Sorry I had to release this since I've been asked about it on skype alot...
ZOptionInterface.cpp
anyways, it's easy tho, search for this (about the line 193)

      map< int, D3DDISPLAYMODE>::iterator iter = find_if( gDisplayMode.begin(), gDisplayMode.end(), value_equals<int, D3DDISPLAYMODE>(ddm));

you'll see under it

    pWidget->SetSelIndex( 1 );

so lemme explain alittle, 1 means the first resolution, 2 means the second... etc
that's why it doesn't matter if you change it it'll stay on that resolution once you click on Option.
so simply replace the 1 with

    pWidget->SetSelIndex( iter->first );


Credits too Tannous.
