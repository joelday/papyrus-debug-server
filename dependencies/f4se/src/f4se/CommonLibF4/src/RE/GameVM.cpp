#include "RE/GameVM.h"  // SkyrimVM

#include "f4se/PapyrusVM.h"  // g_skyrimVM


namespace RE
{
	GameVM* GameVM::GetSingleton()
	{
		return *reinterpret_cast<GameVM**>(g_gameVM.GetUIntPtr());
	}
}
