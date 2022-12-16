#pragma once

struct GGSet
{
	UINT  WeaponSet[3];
};

class GunGame
{
private:
	bool ParseXML_ItemSet(MXmlElement& elem, GGSet& Node);
	std::vector<std::vector<GGSet>> m_Set;
public:
	GunGame();
	~GunGame();
	void			OnDestroy();
	bool			ReadXML(const char* szFileName, MZFileSystem* pFileSystem = nullptr);
	static GunGame* GetInstance();	

	std::vector<GGSet> GetGGSet(int set);
	int const GetSetCount();

}; inline GunGame* MGetGunGame() { return GunGame::GetInstance(); }