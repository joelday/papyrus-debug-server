#include "PexCache.h"

#include <functional>
#include <algorithm>
#include <string>

namespace DarkId::Papyrus::DebugServer

{
    PexCache::PexCache()
    {
    }

    int PexCache::GetScriptReference(const char* scriptName)
    {
        std::hash<std::string> hasher;

        std::string name = scriptName;
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        // TODO: This might be a little excessive...
        return (int)(((UInt32)hasher(name)) / 2) - 1;
    }

    Pex::Binary* PexCache::GetScript(const char* scriptName)
    {
        UInt32 reference = GetScriptReference(scriptName);

        auto entry = m_scripts.find(reference);
        if (entry == m_scripts.end())
        {
            Pex::Binary* binary = new Pex::Binary();

            if (LoadPexData(scriptName, *binary))
            {
                m_scripts.emplace(reference, binary);
                return binary;
            }
            else
            {
                delete binary;
            }
        }

        return entry != m_scripts.end() ? entry->second : NULL;
    }

    PexCache::~PexCache()
    {
        for (auto pair : m_scripts)
        {
            delete pair.second;
        }
    }
}
