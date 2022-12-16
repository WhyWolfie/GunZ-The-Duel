#include "stdafx.h"
#include "GunGame.h"

GunGame::GunGame()
{
}

GunGame::~GunGame()
{

}

void GunGame::OnDestroy()
{
}

GunGame* GunGame::GetInstance()
{
	static GunGame Instance;

	return &Instance;
}

bool GunGame::ReadXML(const char* szFileName, MZFileSystem* pFileSystem)
{
	m_Set.clear();
	MXmlDocument	xmlDocument;

	xmlDocument.Create();

	if (!xmlDocument.LoadFromFile(szFileName))
	{
		xmlDocument.Destroy();
		return false;
	}

	MXmlElement rootElement, chrElement, attrElement;
	char szTagName[256];

	rootElement = xmlDocument.GetDocumentElement();

	int iCount = rootElement.GetChildNodeCount();

	for (int i = 0; i < iCount; i++)
	{
		chrElement = rootElement.GetChildNode(i);
		chrElement.GetTagName(szTagName);
		if (szTagName[0] == '#') continue;

		if (_stricmp(szTagName, "SET") == 0)
		{
			vector<GGSet> ItemSets;
			ItemSets.clear();

			int count = chrElement.GetChildNodeCount();
			for (int j = 0; j < count; ++j)
			{
				attrElement = chrElement.GetChildNode(j);

				attrElement.GetTagName(szTagName);
				if (_stricmp(szTagName, "ITEMSET") == 0)
				{
					GGSet Node = { 0 };

					if (!ParseXML_ItemSet(attrElement, Node)) {
						mlog("Error parsing itemset");
						return false;
					}
					ItemSets.push_back(Node);
				}
			}
			m_Set.push_back(ItemSets);
		}
	}

	xmlDocument.Destroy();

	return true;
}

bool GunGame::ParseXML_ItemSet(MXmlElement& elem, GGSet& Node)
{
	int melee, primary, secondary;

	if (!elem.GetAttribute(&melee, "melee", 0))
		return false;
	if (!elem.GetAttribute(&primary, "primary", 0))
		return false;
	if (!elem.GetAttribute(&secondary, "secondary", 0))
		return false;

	Node.WeaponSet[0] = melee;
	Node.WeaponSet[1] = primary;
	Node.WeaponSet[2] = secondary;
	
	return true;
}

std::vector<GGSet> GunGame::GetGGSet(int set)
{
	auto itor = m_Set.at(set);
	if (itor.size() > 0) {
		return itor;
	}
	return {};
}

int const GunGame::GetSetCount()
{
	return (int)m_Set.size();
}