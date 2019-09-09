#pragma once

#include "Pex/Binary.hpp"

namespace DarkId::Papyrus::DebugServer
{
	bool LoadPexData(const char* scriptName, Pex::Binary& binary);
}
