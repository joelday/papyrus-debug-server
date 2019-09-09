#pragma once

#include "f4se/GameThreads.h"  // TaskDelegate
// #include "f4se/Hooks_UI.h"  // UIDelegate_v1
#include "f4se/PapyrusDelayFunctors.h"  // F4SEDelayFunctorManager
#include "f4se/PapyrusObjects.h"  // F4SEObjectRegistry, F4SEPersistentObjectStorage
#include "f4se/PluginAPI.h"  // PluginHandle, F4SEInterface, F4SEScaleformInterface, F4SESerializationInterface, F4SETaskInterface, F4SEPapyrusInterface, F4SEMessagingInterface, F4SEObjectInterface

#include <functional>  // function

#include "RE/BSScript/Internal/VirtualMachine.h"  // BSScript::Internal::VirtualMachine
//#include "RE/GFxMovieView.h"  // GFxMovieView
//#include "RE/GFxValue.h"  // GFxValue
//#include "RE/InventoryEntryData.h"  // InventoryEntryData


namespace F4SE
{
	enum class InterfaceID : UInt32
	{
		kInvalid = 0,
		kMessaging,
		kScaleform,
		kPapyrus,
		kSerialization,
		kTask,
		
		kObject,

		kTotal
	};


	class QueryInterface
	{
	public:
		UInt32 F4SEVersion() const;
		UInt32 RuntimeVersion() const;
		UInt32 EditorVersion() const;
		bool IsEditor() const;

	protected:
		const F4SEInterface* GetProxy() const;
	};


	class LoadInterface : public QueryInterface
	{
	public:
		void* QueryInterface(InterfaceID a_id) const;
		PluginHandle GetPluginHandle() const;
		UInt32 GetReleaseIndex() const;
	};


	//class ScaleformInterface
	//{
	//public:
	//	using RegCallback = bool(RE::GFxMovieView* a_view, RE::GFxValue* a_root);
	//	using RegInvCallback = void(RE::GFxMovieView* a_view, RE::GFxValue* a_object, RE::InventoryEntryData* a_item);

	//	enum { kVersion = 2 };

	//	UInt32 Version() const;

	//	bool Register(RegCallback* a_callback, const char* a_name) const;
	//	void Register(RegInvCallback* a_callback) const;

	//protected:
	//	const F4SEScaleformInterface* GetProxy() const;
	//};
	//STATIC_ASSERT(ScaleformInterface::kVersion == F4SEScaleformInterface::kInterfaceVersion);


	//class SerializationInterface
	//{
	//public:
	//	using EventCallback = void(SerializationInterface* a_intfc);
	//	using FormDeleteCallback = void(RE::VMHandle a_handle);

	//	enum { kVersion = 4 };

	//	UInt32 Version() const;

	//	void SetUniqueID(UInt32 a_uid) const;

	//	void SetRevertCallback(EventCallback* a_callback) const;
	//	void SetSaveCallback(EventCallback* a_callback) const;
	//	void SetLoadCallback(EventCallback* a_callback) const;
	//	void SetFormDeleteCallback(FormDeleteCallback* a_callback) const;

	//	bool WriteRecord(UInt32 a_type, UInt32 a_version, const void* a_buf, UInt32 a_length) const;
	//	bool OpenRecord(UInt32 a_type, UInt32 a_version) const;
	//	bool WriteRecordData(const void* a_buf, UInt32 a_length) const;

	//	bool GetNextRecordInfo(UInt32& a_type, UInt32& a_version, UInt32& a_length) const;
	//	UInt32 ReadRecordData(void* a_buf, UInt32 a_length) const;
	//	bool ResolveHandle(RE::VMHandle a_oldHandle, RE::VMHandle& a_newHandle) const;
	//	bool ResolveFormID(RE::FormID a_oldFormID, RE::FormID& a_newFormID) const;

	//protected:
	//	const F4SESerializationInterface* GetProxy() const;
	//};
	//STATIC_ASSERT(SerializationInterface::kVersion == F4SESerializationInterface::kVersion);


	class TaskInterface
	{
	public:
		using TaskFn = std::function<void()>;

		enum { kVersion = 2 };

		UInt32 Version() const;

		void AddTask(TaskFn a_task) const;
		void AddTask(ITaskDelegate* a_task) const;
		void AddUITask(TaskFn a_task) const;
		void AddUITask(ITaskDelegate* a_task) const;

	protected:
		class Task : public ITaskDelegate
		{
		public:
			Task(TaskFn&& a_fn);

			virtual void Run() override;

		private:
			TaskFn _fn;
		};

		const F4SETaskInterface* GetProxy() const;
	};
	STATIC_ASSERT(TaskInterface::kVersion == F4SETaskInterface::kInterfaceVersion);


	//class PapyrusInterface
	//{
	//public:
	//	using RegFunction = bool(RE::BSScript::Internal::VirtualMachine* a_vm);

	//	enum { kVersion = 1 };

	//	UInt32 Version() const;

	//	template <class Last>
	//	bool Register(Last a_last) const
	//	{
	//		return Register_Impl(a_last);
	//	}

	//	template <class First, class... Rest>
	//	bool Register(First a_first, Rest... a_rest) const
	//	{
	//		return Register_Impl(a_first) && Register(a_rest...);
	//	}

	//protected:
	//	const F4SEPapyrusInterface* GetProxy() const;

	//private:
	//	bool Register_Impl(RegFunction* a_fn) const;
	//};
	//STATIC_ASSERT(PapyrusInterface::kVersion == F4SEPapyrusInterface::kInterfaceVersion);


	class MessagingInterface
	{
	public:
		struct Message
		{
			const char*	sender;
			UInt32		type;
			UInt32		dataLen;
			void*		data;
		};

		using EventCallback = void(Message* a_msg);

		enum { kVersion = 1 };

		enum : UInt32
		{
			kPostLoad,		// sent to registered plugins once all plugins have been loaded (no data)
			kPostPostLoad,	// sent right after kPostLoad to facilitate the correct dispatching/registering of messages/listeners
			kPreLoadGame,	// dispatched immediately before savegame is read by Fallout
									// dataLen: length of file path, data: char* file path of .ess savegame file
			kPostLoadGame,	//dispatched after an attempt to load a saved game has finished (the game's LoadGame() routine
									//has returned). You will probably want to handle this event if your plugin uses a Preload callback
									//as there is a chance that after that callback is invoked the game will encounter an error
									//while loading the saved game (eg. corrupted save) which may require you to reset some of your
									//plugin state.
									//data: bool, true if game successfully loaded, false otherwise
									// plugins may register as listeners during the first callback while deferring dispatches until the next
			kPreSaveGame,	// right before the game is saved
			kPostSaveGame,	// right after the game is saved
			kDeleteGame,	// sent right before deleting the .f4se cosave and the .ess save.
									// dataLen: length of file path, data: char* file path of .ess savegame file
			kInputLoaded,	// sent right after game input is loaded, right before the main menu initializes
			kNewGame,		// sent after a new game is created, before the game has loaded (Sends CharGen TESQuest pointer)
			kGameLoaded,	// sent after the game has finished loading (only sent once)
			kGameDataReady,	// sent when the data handler is ready (data is false before loading, true when finished loading)

			kTotal
		};

		enum class Dispatcher : UInt32
		{
			//kModEvent = 0,
			//kCameraEvent,
			//kCrosshairEvent,
			//kActionEvent,
			//kNiNodeUpdateEvent,

			kTotal
		};

		UInt32 Version() const;

		bool RegisterListener(const char* a_sender, EventCallback* a_callback) const;
		bool Dispatch(UInt32 a_messageType, void* a_data, UInt32 a_dataLen, const char* a_receiver) const;
		void* GetEventDispatcher(Dispatcher a_dispatcherID) const;

	protected:
		const F4SEMessagingInterface* GetProxy() const;
	};
	STATIC_ASSERT(MessagingInterface::kVersion == F4SEMessagingInterface::kInterfaceVersion);


	class ObjectInterface
	{
	public:
		enum { kVersion = 1 };

		UInt32 Version() const;

		F4SEDelayFunctorManager& GetDelayFunctorManager() const;
		F4SEObjectRegistry& GetObjectRegistry() const;
		F4SEPersistentObjectStorage& GetPersistentObjectStorage() const;

	private:
		const F4SEObjectInterface* GetProxy() const;
	};
	STATIC_ASSERT(ObjectInterface::kVersion == F4SEObjectInterface::kInterfaceVersion);


	struct PluginInfo
	{
		enum { kVersion = 1 };

		UInt32		infoVersion;
		const char*	name;
		UInt32		version;
	};
	STATIC_ASSERT(PluginInfo::kVersion == ::PluginInfo::kInfoVersion);
	STATIC_ASSERT(offsetof(PluginInfo, infoVersion) == offsetof(::PluginInfo, infoVersion));
	STATIC_ASSERT(offsetof(PluginInfo, name) == offsetof(::PluginInfo, name));
	STATIC_ASSERT(offsetof(PluginInfo, version) == offsetof(::PluginInfo, version));
	STATIC_ASSERT(sizeof(PluginInfo) == sizeof(::PluginInfo));
}
