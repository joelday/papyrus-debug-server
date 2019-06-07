#pragma once

#include "Pex.h"

namespace DarkId::Papyrus::DebugServer

{
    class PexCache
    {
    public:
        PexCache();
        ~PexCache();

        bool HasScript(int scriptReference);
        int GetScriptReference(const char* scriptName);

        Pex::Binary* GetScript(const char* scriptName);
    private:
        std::map<int, Pex::Binary*> m_scripts;
    };
}
