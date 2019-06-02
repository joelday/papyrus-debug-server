#pragma once

#include "f4se/PapyrusInterfaces.h"
#include "champollion/Pex/Binary.hpp"
#include "PexStreamReader.hpp"

#include <iostream>

namespace DarkId::Papyrus::DebugServer

{
    bool LoadPexData(const char* scriptName, Pex::Binary& binary);
}
