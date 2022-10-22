#include "stdafx.h"
#include "ZPlayerWarsRankingListBox.h"

ZPlayerWarsRankingListBox::ZPlayerWarsRankingListBox(const char* szName, MWidget* pParent, MListener* pListener) 
: MWidget(szName, pParent, pListener)
{
	m_pBmpRankingItemBg = NULL;

	m_nMyRankIndex = -1;
}

ZPlayerWarsRankingListBox::~ZPlayerWarsRankingListBox()
{

}

void ZPlayerWarsRankingListBox::ClearAll()
{
}

void ZPlayerWarsRankingListBox::LoadInterfaceImgs()
{
	if (m_pBmpRankingItemBg == NULL) {
		m_pBmpRankingItemBg = new MBitmapR2;
		((MBitmapR2*)m_pBmpRankingItemBg)->Create( "DuelTournamentRankingItemBg.png", RGetDevice(), "interface/loadable/DuelTournamentRankingItemBg.png");
	}
}

void ZPlayerWarsRankingListBox::UnloadInterfaceImgs()
{
	SAFE_DELETE(m_pBmpRankingItemBg);
}

void ZPlayerWarsRankingListBox::SetRankInfo( unsigned int nIndex, const ZPLAYERRANKINGITEM& rankingItem )
{
	if (nIndex >= NUM_DISPLAY_DUELTOURNAMENT_RANKING) { _ASSERT(0); return; }
	
	m_rankingList[nIndex] = rankingItem;
}

void ZPlayerWarsRankingListBox::OnDraw( MDrawContext* pDC )
{

	const int nWidth = this->GetRect().w;
	const int nHeight = this->GetRect().h;
	const int nY_firstItem = nHeight * 0.17f;	// 리스트 첫째 항목의 y위치
	const int nItemHeight = (int)(nHeight / 7.f);

	char szTemp[128];
	MRECT rc;

	for (int i=0; i<NUM_DISPLAY_DUELTOURNAMENT_RANKING; ++i)
	{
		int y = (nY_firstItem + nItemHeight * i) - (nItemHeight * 0.04f);

		// 리스트아이템 배경이미지
		pDC->SetBitmap(m_pBmpRankingItemBg);
		pDC->Draw(0, y, nWidth, nItemHeight);

		// 항목 내용 그리기
		ZPLAYERRANKINGITEM* pRankItem = &m_rankingList[i];

		y = nY_firstItem + nItemHeight * i;

		pDC->SetColor(MCOLOR(0xFFFFFFFF));

		// 순위
		if (pRankItem->nRank == -1)	// 초기화 직후 순위정렬되지 않았을때 -1로 되어 있음
			strcpy(szTemp, "--");
		else
			sprintf(szTemp, "%d", pRankItem->nRank);
		rc.Set((int)(0.01f*nWidth), y, (int)(fabs(0.01f - 0.11f)*nWidth), nItemHeight);
		pDC->Text(rc, szTemp, MAM_RIGHT|MAM_VCENTER);

		rc.Set((int)(0.30f*nWidth), y, (int)(fabs(0.30f - 0.52f)*nWidth), nItemHeight);
		pDC->Text(rc, pRankItem->szCharName, MAM_HCENTER|MAM_VCENTER);

		sprintf(szTemp, "%d", pRankItem->nWins);
		rc.Set((int)(0.60f*nWidth), y, (int)(fabs(0.60f - 0.70f)*nWidth), nItemHeight);
		pDC->Text(rc, szTemp, MAM_RIGHT|MAM_VCENTER);
		rc.Set((int)(0.70f*nWidth), y, (int)(fabs(0.70f - 0.81f)*nWidth), nItemHeight);
		pDC->Text(rc, "/", MAM_HCENTER|MAM_VCENTER);
		sprintf(szTemp, "%d", pRankItem->nLosses);
		rc.Set((int)(0.81f*nWidth), y, (int)(fabs(0.81f - 0.91f)*nWidth), nItemHeight);
		pDC->Text(rc, szTemp, MAM_LEFT|MAM_VCENTER);

		if (i == m_nMyRankIndex)
		{
			MBitmapR2 *pBitmap=(MBitmapR2*)MBitmapManager::Get("button_glow.png");
			if(pBitmap) {
				DWORD defaultcolor = 0x333333;
				DWORD opacity=(DWORD)pDC->GetOpacity();
				MRECT rt(0, y, nWidth, nItemHeight);
				MDrawEffect prevEffect = pDC->GetEffect();
				pDC->SetEffect(MDE_ADD);
				MCOLOR prevColor = pDC->GetBitmapColor();
				pDC->SetBitmapColor(MCOLOR(defaultcolor));
				unsigned char prevOpacity = pDC->GetOpacity();
				pDC->SetOpacity(opacity);
				pDC->SetBitmap(pBitmap);
				pDC->Draw(rt.x,rt.y,rt.w,rt.h,0,0,64,32);
				pDC->SetBitmapColor(prevColor);
				pDC->SetEffect(prevEffect);
				pDC->SetOpacity(prevOpacity);
			}
		}
	}
}