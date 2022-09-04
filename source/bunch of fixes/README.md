Open (ZOptionInterface.cpp)

Fix: Iterator crash fix, in case resolution isn't supported

Find

    map< int, D3DDISPLAYMODE>::iterator iter = find_if( gDisplayMode.begin(), gDisplayMode.end(), value_equals<int, D3DDISPLAYMODE>(ddm));
    
Place under

			if (iter != gDisplayMode.end())
				pWidget->SetSelIndex(iter->first);
			else
				pWidget->SetSelIndex(0);
    
Open (RVisualMesh.cpp)

Find

	DEL(m_pCloth);
    
Replace

	 SAFE_DELETE_ARRAY(m_pCloth);
    
    
Open (MCommandBuilder.h)

Changed buffer size to fix shop list issues.

Find

	#define COMMAND_BUFFER_LEN	16384
    
Replace

	#define COMMAND_BUFFER_LEN	65535 
