#pragma once

#include "Meta.h"
#include "FormTypeMacros.h"
#include "GameInterfaces.h"

#ifndef STRING
#define STRING(s) #s
#endif

/**
 *		Notes:
 * 1.	Using a library called MetaStuff in order to statically declare reflection
 *		metadata for form and form component types. This is tedious and has a
 *		decent maintenance burden, but there isn't really any way to infer it all.
 *		
 * 2.	Given that maintenance burden, it probably makes sense to do this incrementally,
 *		prioritizing useful types like GlobalVariable along with existing native
 *		getters.
 *		
 * 3.	Made changes to MetaStuff to allow for a lambda expression to return a value.
 * 
 * 4.	The way I managed that involved loss of const correctness.
 * 
 * 5.	Very little is being passed around by ref now, but most non-trivial values
 *		aren't copy constructable anyway and are being passed as pointers.
 *		
 * 6.	Didn't figure out how to get some template argument deduction to work,
 *		so a lot of the macros exist to reduce explicit argument verbosity.
 *		
 * 7.	I'm not too concerned with concurrency because this is all being executed
 *		while paused in the debugger.
 *		
 * 8.	I'm sure these macros are all using ##?## way more than is necessary.
 */

namespace meta
{
#define VIRT_FUNC_MEMBER_IMPL(type, returnType, funcName, name) \
	member<##type##, ##returnType##>(STRING(name), [](##type##* value) { return value->##funcName##(); }) \

#define VIRT_FUNC_MEMBER(type, returnType, name) \
	VIRT_FUNC_MEMBER_IMPL(type, returnType, name, name) \
	
#define VIRT_FUNC_GET_MEMBER(type, returnType, name) \
	VIRT_FUNC_MEMBER_IMPL(type, returnType, Get##name##, name) \
	
#define BASE_TYPE_MEMBER(type, baseType) \
	member<##type##, ##baseType##*>(typeid(##baseType##).name(), [](##type##* value) { return value; }) \

	template <typename Class>
	std::string toDisplayValue(Class value)
	{
		return std::string();
	}

	template <>
	inline std::string toDisplayValue<RE::TESForm*>(RE::TESForm* value)
	{
		char description[512];
#if SKYRIM
		value->GetFormDesc(description, sizeof(description));
#else
		value->GetFormDescription(description, sizeof(description));
#endif
		
		return std::string(description);
	}

	template <>
	inline auto registerMembers<RE::TESForm>()
	{
		return members(
#if SKYRIM
			member<RE::TESForm, RE::BSScript::Object*>("VM Object", [](RE::TESForm* form)
				{
					auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();

					RE::BSTSmartPointer<RE::BSScript::Class> classType;

					// TODO: This is blowing up in F4, I assume because the type id needs to be fixed up first.
					if (vm->GetScriptClassByTypeID(static_cast<RE::FormType32>(form->GetFormType()), classType))
					{
						const auto handle = vm->GetHandlePolicy()->GetHandle(static_cast<RE::FormType32>(form->GetFormType()), form);
						if (vm->GetHandlePolicy()->IsValidHandle(handle))
						{
							RE::BSTSmartPointer<RE::BSScript::Object> object;
							if (vm->ResolveScriptObject(handle, classType->GetName(), object))
							{
								return object.get();
							}
						}
					}

					return static_cast<RE::BSScript::Object*>(nullptr);
				}),
			VIRT_FUNC_MEMBER(RE::TESForm, bool, PlayerKnows),
			VIRT_FUNC_MEMBER(RE::TESForm, bool, IsPlayable),
			VIRT_FUNC_MEMBER(RE::TESForm, bool, NeverFades),
			VIRT_FUNC_MEMBER(RE::TESForm, bool, IgnoredBySandbox),
			VIRT_FUNC_MEMBER(RE::TESForm, bool, Has3D),
			VIRT_FUNC_MEMBER(RE::TESForm, bool, IsMagicItem)
#endif
		);
	}
	
#if SKYRIM
	template <>
	inline std::string toDisplayValue<RE::BGSKeyword*>(RE::BGSKeyword* value)
	{
		// TODO: Get rid of this manual quoting concatenation crap
		return "\"" + std::string(value->keyword.c_str()) + "\"";
	}
	
	template <>
	inline auto registerMembers<RE::BGSKeyword>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::BGSKeyword, RE::TESForm),
			member("Keyword", &RE::BGSKeyword::keyword)
		);
	}

	template <>
	inline auto registerMembers<RE::BGSLocationRefType>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::BGSLocationRefType, RE::BGSKeyword)
		);
	}

	template <>
	inline auto registerMembers<RE::BGSAction>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::BGSAction, RE::BGSKeyword),
			member("Index", &RE::BGSAction::index)
		);
	}
#endif
	
	template <>
	inline auto registerMembers<RE::TESObject>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::TESObject, RE::TESForm)
#if SKYRIM
			,
			VIRT_FUNC_MEMBER(RE::TESObject, bool, CanAnimate),
			VIRT_FUNC_GET_MEMBER(RE::TESObject, RE::TESWaterForm*, WaterActivator),
			VIRT_FUNC_MEMBER(RE::TESObject, bool, IsAutoCalc),
			VIRT_FUNC_MEMBER(RE::TESObject, bool, IsMarker),
			VIRT_FUNC_MEMBER(RE::TESObject, bool, IsCullingMarker)
#endif
		);
	}

	template <>
	inline auto registerMembers<RE::TESBoundObject::ObjectBounds>()
	{
		return members(
			member("x1", &RE::TESBoundObject::ObjectBounds::x1),
			member("y1", &RE::TESBoundObject::ObjectBounds::y1),
			member("z1", &RE::TESBoundObject::ObjectBounds::z1),
			member("x2", &RE::TESBoundObject::ObjectBounds::x2),
			member("y2", &RE::TESBoundObject::ObjectBounds::y2),
			member("z2", &RE::TESBoundObject::ObjectBounds::z2)
		);
	}
	
	template <>
	inline auto registerMembers<RE::TESBoundObject>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::TESBoundObject, RE::TESObject),
			member("ObjectBounds", &RE::TESBoundObject::objectBounds)
		);
	}

	//template <>
	//inline auto registerMembers<RE::NiRefObject>()
	//{
	//	return members();
	//}
	
	//template <>
	//inline auto registerMembers<RE::NiObject>()
	//{
	//	return members(
	//		BASE_TYPE_MEMBER(RE::NiObject, RE::NiRefObject)
	//	);
	//}
	//
	//template <>
	//inline auto registerMembers<RE::BSTextureSet>()
	//{
	//	return members(
	//		BASE_TYPE_MEMBER(RE::BSTextureSet, RE::NiObject)
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::TESTexture>()
	//{
	//	return members(
	//		VIRT_FUNC_GET_MEMBER(RE::TESTexture, UInt32, Size),
	//		VIRT_FUNC_GET_MEMBER(RE::TESTexture, std::string, SearchDir),
	//		member("Texture", &RE::TESTexture::texture)
	//	);
	//}
	//
	//template <>
	//inline auto registerMembers<RE::BGSTextureSet>()
	//{
	//	return members(
	//		BASE_TYPE_MEMBER(RE::BGSTextureSet, RE::TESBoundObject),
	//		BASE_TYPE_MEMBER(RE::BGSTextureSet, RE::BSTextureSet),
	//		
	//		// TODO: Simplified pattern/macro for this
	//		member<RE::BGSTextureSet, std::vector<RE::TESTexture*>>("Textures", [](RE::BGSTextureSet* form)
	//			{
	//				// TODO: Is this a correct way to do this?
	//				const UInt32 elementCount = sizeof(form->textures) / sizeof(RE::TESTexture);
	//			
	//				std::vector<RE::TESTexture*> elements;
	//				
	//				for (auto i = 0; i < elementCount; i++)
	//				{
	//					elements.push_back(&form->textures[i]);
	//				}
	//		
	//				return elements;

	//				// TODO: Tried this, but need each element to be a pointer.
	//				// return std::vector<RE::TESTexture*>(form->textures, std::end(form->textures));
	//			})
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::TESIcon>()
	//{
	//	return members(
	//		BASE_TYPE_MEMBER(RE::TESIcon, RE::TESTexture)
	//	);
	//}
	//
	//template <>
	//inline auto registerMembers<RE::BGSMenuIcon>()
	//{
	//	return members(
	//		BASE_TYPE_MEMBER(RE::BGSMenuIcon, RE::TESForm),
	//		BASE_TYPE_MEMBER(RE::BGSMenuIcon, RE::TESIcon)
	//	);
	//}
#if SKYRIM
	template <>
	inline std::string toDisplayValue<RE::TESGlobal*>(RE::TESGlobal* value)
	{
		return DarkId::Papyrus::DebugServer::StringFormat("%f", value->value);
	}
	
	template <>
	inline auto registerMembers<RE::TESGlobal>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::TESGlobal, RE::TESForm),
			member("Value", &RE::TESGlobal::value)
		);
	}
#endif
	
	template <>
	inline auto registerMembers<RE::TESFullName>()
	{
		return members(
			member("FullName", &RE::TESFullName::fullName)
		);
	}
	
#if SKYRIM
	template <>
	inline auto registerMembers<RE::TESDescription>()
	{
		return members(
			// TODO
		);
	}
#endif

	//// TODO: Skill enum
	//
	//template <>
	//inline auto registerMembers<RE::TESClass::Data::SkillWeights>()
	//{
	//	return members(
	//		// TODO
	//	);
	//}
	
	//template <>
	//inline auto registerMembers<RE::TESClass::Data::AttributeWeights>()
	//{
	//	return members(
	//		member("Health", &RE::TESClass::Data::AttributeWeights::health),
	//		member("Magicka", &RE::TESClass::Data::AttributeWeights::magicka),
	//		member("Stamina", &RE::TESClass::Data::AttributeWeights::stamina)
	//	);
	//}
	//
	//template <>
	//inline auto registerMembers<RE::TESClass::Data>()
	//{
	//	return members(
	//		member("Teaches", &RE::TESClass::Data::teaches),
	//		member("MaximumTrainingLevel", &RE::TESClass::Data::maximumTrainingLevel),
	//		member("SkillWeights", &RE::TESClass::Data::skillWeights),
	//		member("BleedoutDefault", &RE::TESClass::Data::bleedoutDefault),
	//		member("VoicePoints", &RE::TESClass::Data::voicePoints),
	//		member("AttributeWeights", &RE::TESClass::Data::attributeWeights)
	//	);
	//}
	//
	//template <>
	//inline auto registerMembers<RE::TESClass>()
	//{
	//	return members(
	//		BASE_TYPE_MEMBER(RE::TESClass, RE::TESForm),
	//		BASE_TYPE_MEMBER(RE::TESClass, RE::TESFullName),
	//		BASE_TYPE_MEMBER(RE::TESClass, RE::TESDescription),
	//		BASE_TYPE_MEMBER(RE::TESClass, RE::TESTexture),
	//		member("Data", &RE::TESClass::data)
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::TESReactionForm>()
	//{
	//	return members(
	//		// TODO
	//	);
	//}
	//
#if SKYRIM
	template <>
	inline auto registerMembers<RE::TESFaction>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::TESFaction, RE::TESForm),
			BASE_TYPE_MEMBER(RE::TESFaction, RE::TESFullName),
			BASE_TYPE_MEMBER(RE::TESFaction, RE::TESReactionForm)
		);
	}
#endif
}
