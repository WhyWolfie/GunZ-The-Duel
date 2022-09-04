Open (ZOptionInterface.cpp)

Fix: Iterator crash fix, in case resolution isn't supported

Find

    map< int, D3DDISPLAYMODE>::iterator iter = find_if( gDisplayMode.begin(), gDisplayMode.end(), value_equals<int, D3DDISPLAYMODE>(ddm));
    
Place under

			if (iter != gDisplayMode.end())
				pWidget->SetSelIndex(iter->first);
			else
				pWidget->SetSelIndex(0);
    

    
    
    
    
    
    
    
