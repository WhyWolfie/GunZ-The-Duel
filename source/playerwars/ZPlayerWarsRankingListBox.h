#ifndef _ZPlayerWarsRankingListBox_H
#define _ZPlayerWarsRankingListBox_H

#define NUM_DISPLAY_DUELTOURNAMENT_RANKING 5
#define INDEX_DUELTOURNAMENT_MY_RANKING 2			// ∑©≈∑ ∏Ò∑œø°º≠ ≥ª ∑©≈∑ æ∆¿Ã≈€¿« ¿Œµ¶Ω∫

struct ZPLAYERRANKINGITEM {
	char szCharName[MAX_CHARNAME+1];
	int nWins;
	int nLosses;
	int nDraws;
    int nRank;

	ZPLAYERRANKINGITEM() : nWins(0), nLosses(0), nRank(0) {
		szCharName[0] = 0;
	}
};

class ZPlayerWarsRankingListBox : public MWidget {

	ZPLAYERRANKINGITEM m_rankingList[NUM_DISPLAY_DUELTOURNAMENT_RANKING];

	MBitmapR2* m_pBmpRankingItemBg;

	int m_nMyRankIndex;			// ≥ª ∑©≈∑ «•Ω√ ¿Œµ¶Ω∫

protected:
	virtual void	OnDraw( MDrawContext* pDC );

public:
	ZPlayerWarsRankingListBox(const char* szName=NULL, MWidget* pParent=NULL, MListener* pListener=NULL);
	~ZPlayerWarsRankingListBox();

	void ClearAll();
	void SetRankInfo(unsigned int nIndex, const ZPLAYERRANKINGITEM& rankingItem);

	void LoadInterfaceImgs();
	void UnloadInterfaceImgs();

	void SetMyRankIndex(int myRankIndex) { m_nMyRankIndex = myRankIndex; }

};



#endif