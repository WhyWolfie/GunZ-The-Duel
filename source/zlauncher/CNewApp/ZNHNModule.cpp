#include "stdafx.h"
#include "ZNHNModule.h"


ZNHNModule::ZNHNModule()
{
}


ZNHNModule::~ZNHNModule()
{
}


ZNHNModule& GetNHNModule()
{
	return ZNHNModule::GetInstance();
}