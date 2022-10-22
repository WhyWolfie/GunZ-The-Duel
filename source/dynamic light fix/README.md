Open(RBspObject.cpp) <br>

				for(int j=0;j<3;j++) {
					BSPVERTEX *pv = &m_pOcVertices[indices[j]] + pNode->m_nBaseVertexIndex;
					v[j].coord = *pv->Coord();
					v[j].tu2 = pv->tu1;
					v[j].tv2 = pv->tv1;
				}
        
Replace <br>

				for(int j=0;j<3;j++) {
					BSPVERTEX *pv = &m_pOcVertices[indices[j]] + pNode->m_nBaseVertexIndex;;
					v[j].coord = *pv->Coord();
					v[j].tu2 = pv->tu1;
					v[j].tv2 = pv->tv1;
				}
