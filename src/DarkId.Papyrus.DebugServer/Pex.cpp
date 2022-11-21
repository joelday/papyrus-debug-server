#include "Pex.h"

#include <sstream>
#include <regex>

#include "GameInterfaces.h"

#if SKYRIM
#include <SKSE/Impl/PCH.h>
#include <SKSE/Logger.h>
#elif FALLOUT
#include <F4SE/Logger.h>
#include <f4se/GameStreams.h>
#endif 

#include "PexStreamReader.hpp"

namespace DarkId::Papyrus::DebugServer
{
	bool ReadPexResource(const char* scriptName, std::ostream& stream)
	{
		const auto scriptPath = "Scripts/" + std::regex_replace(scriptName, std::regex(":"), "/") + ".pex";
#if SKYRIM
		RE::BSResourceNiBinaryStream scriptStream(scriptPath);

		if (scriptStream.good())
		{
			char byte;
			while (scriptStream.get(byte))
			{
				stream.put(byte);
			}

			return true;
		}
#elif FALLOUT
		BSResourceNiBinaryStream scriptStream(scriptPath.c_str());

		if (scriptStream.IsValid())
		{
			char byte;
			while (scriptStream.Read(&byte, 1))
			{
				stream.put(byte);
			}

			return true;
		}
#endif 

		return false;
	}

	bool LoadPexData(const char* scriptName, Pex::Binary& binary)
	{
		std::stringstream buffer;

		if (!ReadPexResource(scriptName, buffer))
		{
			SKSE::log::error("Failed to load pex resource.");
			return false;
		}

		buffer.seekp(0);

		std::istream input(buffer.rdbuf());
		Pex::PexStreamReader reader(&input);

		reader.read(binary);
		return true;
	}
}
