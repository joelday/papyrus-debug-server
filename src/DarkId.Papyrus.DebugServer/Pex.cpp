#include "Pex.h"

#include "f4se\PapyrusVM.h"
#include "GameInterfaces.h"

#include <sstream>

namespace DarkId::Papyrus::DebugServer
{
	RelocPtr <Game::BSScript::CompiledScriptLoader> g_compiledScriptLoader(0x5ABD9B8);

	bool ReadPexResource(const char* scriptName, std::ostream* stream)
	{
		GameVM* game = *g_gameVM;
		VirtualMachine* vm = game->m_virtualMachine;

		// TODO: No idea if this is the correct lock:
		BSReadLocker scriptLocker(&vm->scriptsLock);

        Game::GameScript::Store* store = g_compiledScriptLoader->m_store;

		if (store->Open(scriptName) && store->m_hasOpenFile)
		{
			UInt32 length = store->m_readerStream->m_streamLength;
			char* data = new char[length];

			store->Read(length, data);
			store->Close();

			stream->write(data, length);

			delete data;

			return true;
		}

		return false;
	}

	bool LoadPexData(const char* scriptName, Pex::Binary& binary)
	{
		std::stringstream buffer;

		if (!ReadPexResource(scriptName, &buffer))
		{
			_ERROR("Failed to load pex resource.");
			return false;
		}

		buffer.seekp(0);

		std::istream input(buffer.rdbuf());

		Pex::PexStreamReader* reader = new Pex::PexStreamReader(&input);

		bool success = false;

		try
		{
			reader->read(binary);
			success = true;
		}
		catch (void*)
		{
			_ERROR("Failed to parse pex data.");
		}

		if (reader)
		{
			delete reader;
		}

		return success;
	}
}
