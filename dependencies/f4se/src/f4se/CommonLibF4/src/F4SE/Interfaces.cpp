#include "F4SE/Interfaces.h"

#include "f4se/PluginAPI.h"  // F4SEInterface, F4SEScaleformInterface, F4SESerializationInterface, F4SETaskInterface, F4SEPapyrusInterface, F4SEMessagingInterface, F4SEObjectInterface

#include "RE/BSScript/Internal/VirtualMachine.h"  // BSScript::Internal::VirtualMachine
#include "F4SE/API.h"  // GetPluginHandle


namespace F4SE
{
	UInt32 QueryInterface::F4SEVersion() const
	{
		return GetProxy()->f4seVersion;
	}


	UInt32 QueryInterface::RuntimeVersion() const
	{
		return GetProxy()->runtimeVersion;
	}


	UInt32 QueryInterface::EditorVersion() const
	{
		return GetProxy()->editorVersion;
	}


	bool QueryInterface::IsEditor() const
	{
		return GetProxy()->isEditor;
	}


	const F4SEInterface* QueryInterface::GetProxy() const
	{
		return reinterpret_cast<const F4SEInterface*>(this);
	}


	void* LoadInterface::QueryInterface(InterfaceID a_id) const
	{
		return GetProxy()->QueryInterface(static_cast<UInt32>(a_id));
	}


	PluginHandle LoadInterface::GetPluginHandle() const
	{
		return GetProxy()->GetPluginHandle();
	}


	UInt32 LoadInterface::GetReleaseIndex() const
	{
		return GetProxy()->GetReleaseIndex();
	}


	//UInt32 ScaleformInterface::Version() const
	//{
	//	return GetProxy()->interfaceVersion;
	//}


	//bool ScaleformInterface::Register(RegCallback* a_callback, const char* a_name) const
	//{
	//	return GetProxy()->Register(a_name, reinterpret_cast<F4SEScaleformInterface::RegisterCallback>(a_callback));
	//}


	//void ScaleformInterface::Register(RegInvCallback* a_callback) const
	//{
	//	GetProxy()->RegisterForInventory(reinterpret_cast<F4SEScaleformInterface::RegisterInventoryCallback>(a_callback));
	//}


	//const F4SEScaleformInterface* ScaleformInterface::GetProxy() const
	//{
	//	return reinterpret_cast<const F4SEScaleformInterface*>(this);
	//}


	//UInt32 SerializationInterface::Version() const
	//{
	//	return GetProxy()->version;
	//}


	//void SerializationInterface::SetUniqueID(UInt32 a_uid) const
	//{
	//	GetProxy()->SetUniqueID(GetPluginHandle(), a_uid);
	//}


	//void SerializationInterface::SetRevertCallback(EventCallback* a_callback) const
	//{
	//	GetProxy()->SetRevertCallback(GetPluginHandle(), reinterpret_cast<F4SESerializationInterface::EventCallback>(a_callback));
	//}


	//void SerializationInterface::SetSaveCallback(EventCallback* a_callback) const
	//{
	//	GetProxy()->SetSaveCallback(GetPluginHandle(), reinterpret_cast<F4SESerializationInterface::EventCallback>(a_callback));
	//}


	//void SerializationInterface::SetLoadCallback(EventCallback* a_callback) const
	//{
	//	GetProxy()->SetLoadCallback(GetPluginHandle(), reinterpret_cast<F4SESerializationInterface::EventCallback>(a_callback));
	//}


	//void SerializationInterface::SetFormDeleteCallback(FormDeleteCallback* a_callback) const
	//{
	//	GetProxy()->SetFormDeleteCallback(GetPluginHandle(), reinterpret_cast<F4SESerializationInterface::FormDeleteCallback>(a_callback));
	//}


	//bool SerializationInterface::WriteRecord(UInt32 a_type, UInt32 a_version, const void* a_buf, UInt32 a_length) const
	//{
	//	return GetProxy()->WriteRecord(a_type, a_version, a_buf, a_length);
	//}


	//bool SerializationInterface::OpenRecord(UInt32 a_type, UInt32 a_version) const
	//{
	//	return GetProxy()->OpenRecord(a_type, a_version);
	//}


	//bool SerializationInterface::WriteRecordData(const void* a_buf, UInt32 a_length) const
	//{
	//	return GetProxy()->WriteRecordData(a_buf, a_length);
	//}


	//bool SerializationInterface::GetNextRecordInfo(UInt32& a_type, UInt32& a_version, UInt32& a_length) const
	//{
	//	return GetProxy()->GetNextRecordInfo(&a_type, &a_version, &a_length);
	//}


	//UInt32 SerializationInterface::ReadRecordData(void* a_buf, UInt32 a_length) const
	//{
	//	return GetProxy()->ReadRecordData(a_buf, a_length);
	//}


	//bool SerializationInterface::ResolveHandle(RE::VMHandle a_oldHandle, RE::VMHandle& a_newHandle) const
	//{
	//	return GetProxy()->ResolveHandle(a_oldHandle, &a_newHandle);
	//}


	//bool SerializationInterface::ResolveFormID(RE::FormID a_oldFormID, RE::FormID& a_newFormID) const
	//{
	//	return GetProxy()->ResolveFormId(a_oldFormID, &a_newFormID);
	//}


	//const F4SESerializationInterface* SerializationInterface::GetProxy() const
	//{
	//	return reinterpret_cast<const F4SESerializationInterface*>(this);
	//}


	UInt32 TaskInterface::Version() const
	{
		return GetProxy()->interfaceVersion;
	}


	void TaskInterface::AddTask(TaskFn a_task) const
	{
		GetProxy()->AddTask(new Task(std::move(a_task)));
	}


	void TaskInterface::AddTask(ITaskDelegate* a_task) const
	{
		GetProxy()->AddTask(a_task);
	}


	void TaskInterface::AddUITask(TaskFn a_task) const
	{
		GetProxy()->AddUITask(new Task(std::move(a_task)));
	}


	void TaskInterface::AddUITask(ITaskDelegate* a_task) const
	{
		GetProxy()->AddUITask(a_task);
	}


	TaskInterface::Task::Task(TaskFn&& a_fn) :
		_fn(std::move(a_fn))
	{}


	void TaskInterface::Task::Run()
	{
		_fn();
	}

	const F4SETaskInterface* TaskInterface::GetProxy() const
	{
		return reinterpret_cast<const F4SETaskInterface*>(this);
	}


	//UInt32 PapyrusInterface::Version() const
	//{
	//	return GetProxy()->interfaceVersion;
	//}


	//bool PapyrusInterface::Register_Impl(RegFunction* a_fn) const
	//{
	//	auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
	//	if (vm) {
	//		a_fn(vm);
	//		return true;
	//	} else {
	//		return GetProxy()->Register(reinterpret_cast<F4SEPapyrusInterface::RegisterFunctions>(a_fn));
	//	}
	//}


	//const F4SEPapyrusInterface* PapyrusInterface::GetProxy() const
	//{
	//	return reinterpret_cast<const F4SEPapyrusInterface*>(this);
	//}


	UInt32 MessagingInterface::Version() const
	{
		return GetProxy()->interfaceVersion;
	}


	bool MessagingInterface::RegisterListener(const char* a_sender, EventCallback* a_callback) const
	{
		return GetProxy()->RegisterListener(GetPluginHandle(), a_sender, reinterpret_cast<F4SEMessagingInterface::EventCallback>(a_callback));
	}


	bool MessagingInterface::Dispatch(UInt32 a_messageType, void* a_data, UInt32 a_dataLen, const char* a_receiver) const
	{
		return GetProxy()->Dispatch(GetPluginHandle(), a_messageType, a_data, a_dataLen, a_receiver);
	}


	void* MessagingInterface::GetEventDispatcher(Dispatcher a_dispatcherID) const
	{
		return GetProxy()->GetEventDispatcher(static_cast<UInt32>(a_dispatcherID));
	}


	const F4SEMessagingInterface* MessagingInterface::GetProxy() const
	{
		return reinterpret_cast<const F4SEMessagingInterface*>(this);
	}


	UInt32 ObjectInterface::Version() const
	{
		return GetProxy()->interfaceVersion;
	}


	F4SEDelayFunctorManager& ObjectInterface::GetDelayFunctorManager() const
	{
		return GetProxy()->GetDelayFunctorManager();
	}


	F4SEObjectRegistry& ObjectInterface::GetObjectRegistry() const
	{
		return GetProxy()->GetObjectRegistry();
	}


	F4SEPersistentObjectStorage& ObjectInterface::GetPersistentObjectStorage() const
	{
		return GetProxy()->GetPersistentObjectStorage();
	}


	const F4SEObjectInterface* ObjectInterface::GetProxy() const
	{
		return reinterpret_cast<const F4SEObjectInterface*>(this);
	}
}
