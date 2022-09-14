Open(MMultiColListBox.cpp) <br>
Find <br>

    void MMultiColListBox::RemoveAll()
    {
        for (ItorMultiColListItem it=m_items.begin(); it!=m_items.end(); ++it)
            delete *it;
        m_items.clear();

        m_pScrollBar->SetValue(0);
        UpdateScrollBar();

        m_nSelItem = -1;
        m_nOverItem = -1;
    }
    
Change <br>

    void MMultiColListBox::RemoveAll()
    {
      for (ItorMultiColListItem it=m_items.begin(); it!=m_items.end(); ++it)
        delete *it;
      m_items.clear();

      //shop jump fix
      //m_pScrollBar->SetValue(0);
      UpdateScrollBar();

      m_nSelItem = -1;
      m_nOverItem = -1;
    }
