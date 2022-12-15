#include "Pex.h"

#include <sstream>
#include <regex>

#include "GameInterfaces.h"
#include "Utilities.h"
#if SKYRIM
#include <SKSE/Logger.h>
#elif FALLOUT
#include <F4SE/Logger.h>
#include <f4se/GameStreams.h>
#endif 

#include <Champollion/Pex/FileReader.hpp>

namespace DarkId::Papyrus::DebugServer
{
	bool ReadPexResource(const char* scriptName, std::ostream& stream)
	{
		const auto scriptPath = "Scripts/" + NormalizeScriptName(scriptName) + ".pex";
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

	bool LoadAndDumpPexData(const char* scriptName, std::string outputDir) {
		std::stringstream buffer;

		if (!ReadPexResource(scriptName, buffer))
		{
			logger::error("Failed to load pex resource for script {}"sv, scriptName);
			return false;
		}

		buffer.seekp(0);
		// DEBUG
		std::string scriptFile(scriptName);
		auto outputPath = std::filesystem::path(outputDir) / (std::string(scriptName) + ".pex");
		std::ofstream output(outputPath, std::ios::binary);
		if (output.bad()) {
			logger::error("Failed to open file for writing: {}"sv, outputPath.string());
			return false;

		}
		char byte;
		while (buffer.get(byte)) {
			output.put(byte);
		}
		output.close();
		return true;
	}

	bool LoadPexData(const char* scriptName, Pex::Binary& binary)
	{
		std::stringstream buffer;

		if (!ReadPexResource(scriptName, buffer))
		{
			logger::error("Failed to load pex resource for script {}"sv, scriptName);
			return false;
		}

		buffer.seekp(0);

		std::istream input(buffer.rdbuf());
		Pex::FileReader reader(&input);
		try {
			reader.read(binary);
		}
		catch (std::runtime_error e) {
			logger::error("Failed to parse PEX resource {}:"sv, scriptName);
			logger::error("\t{}"sv, e.what());
		}
		return true;
	}
}
