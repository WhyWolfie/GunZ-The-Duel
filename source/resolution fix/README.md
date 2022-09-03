Fix for jur13n source 1.5<br>
Sorry I had to release this since I've been asked about it on skype alot...<br>
ZOptionInterface.cpp<br>
anyways, it's easy tho, search for this (about the line 193)<br>

      map< int, D3DDISPLAYMODE>::iterator iter = find_if( gDisplayMode.begin(), gDisplayMode.end(), value_equals<int, D3DDISPLAYMODE>(ddm));

you'll see under it<br>

    pWidget->SetSelIndex( 1 );

so lemme explain alittle, 1 means the first resolution, 2 means the second... etc<br>
that's why it doesn't matter if you change it it'll stay on that resolution once you click on Option.<br>
so simply replace the 1 with<br>

    pWidget->SetSelIndex( iter->first );


Credits too Tannous.<br>
