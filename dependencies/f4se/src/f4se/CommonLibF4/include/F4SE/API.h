#pragma once

#include "f4se/PapyrusDelayFunctors.h"  // F4SEDelayFunctorManager
#include "f4se/PapyrusObjects.h"  // F4SEObjectRegistry, F4SEPersistentObjectStorage
#include "f4se/PluginAPI.h"  // PluginHandle

#include <functional>  // function

// #include "RE/BSTEvent.h"  // BSTEventSource
// #include "F4SE/Events.h"  // ModCallbackEvent, CameraEvent, CrosshairRefEvent, ActionEvent, NiNodeUpdateEvent
#include "F4SE/Interfaces.h"  // LoadInterface, ScaleformInterface, PapyrusInterface, SerializationInterface, TaskInterface, MessagingInterface, ObjectInterface


namespace F4SE
{
	bool	Init(const LoadInterface* a_f4se);
	void	RegisterForAPIInitEvent(std::function<void()> a_fn);

	const PluginHandle	GetPluginHandle();
	const UInt32		GetReleaseIndex();

	//const ScaleformInterface*		GetScaleformInterface();
	//const PapyrusInterface*			GetPapyrusInterface();
	//const SerializationInterface*	GetSerializationInterface();
	const TaskInterface*			GetTaskInterface();

	const MessagingInterface*				GetMessagingInterface();
	//RE::BSTEventSource<ModCallbackEvent>*	GetModCallbackEventSource();
	//RE::BSTEventSource<CameraEvent>*		GetCameraEventSource();
	//RE::BSTEventSource<CrosshairRefEvent>*	GetCrosshairRefEventSource();
	//RE::BSTEventSource<ActionEvent>*		GetActionEventSource();
	//RE::BSTEventSource<NiNodeUpdateEvent>*	GetNiNodeUpdateEventSource();

	const ObjectInterface*				GetObjectInterface();
	//const F4SEDelayFunctorManager*		GetDelayFunctorManager();
	//const F4SEObjectRegistry*			GetObjectRegistry();
	//const F4SEPersistentObjectStorage*	GetPersistentObjectStorage();

	bool	AllocLocalTrampoline(std::size_t a_size);
	bool	AllocBranchTrampoline(std::size_t a_size);
}
