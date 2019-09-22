#pragma once
#include "Meta.h"
#include "GameInterfaces.h"

#ifndef STRING
#define STRING(s) #s
#endif

namespace meta
{
#if SKYRIM
	
#define VIRT_FUNC_MEMBER_IMPL(type, returnType, funcName, name) \
	member<##type##, ##returnType##>(STRING(name), [](##type##* value) { return value->##funcName##(); }) \

#define VIRT_FUNC_MEMBER(type, returnType, name) \
	VIRT_FUNC_MEMBER_IMPL(type, returnType, name, name) \
	
#define VIRT_FUNC_GET_MEMBER(type, returnType, name) \
	VIRT_FUNC_MEMBER_IMPL(type, returnType, Get##name##, name) \
	
#define BASE_TYPE_MEMBER(type, baseType) \
	member<##type##, ##baseType##*>(typeid(##baseType##).name(), [](##type##* value) { return value; }) \
	
	template <>
	inline auto registerMembers<RE::TESForm>()
	{
		return members(
			VIRT_FUNC_MEMBER(RE::TESForm, bool, Has3D),
			member("HasWorldModel", &RE::TESForm::HasWorldModel)
		);
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

	template <>
	inline auto registerMembers<RE::TESObject>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::TESObject, RE::TESForm),
			VIRT_FUNC_MEMBER(RE::TESObject, bool, CanAnimate),
			VIRT_FUNC_GET_MEMBER(RE::TESObject, RE::TESWaterForm*, WaterActivator),
			VIRT_FUNC_MEMBER(RE::TESObject, bool, IsAutoCalc),
			VIRT_FUNC_MEMBER(RE::TESObject, bool, IsMarker),
			VIRT_FUNC_MEMBER(RE::TESObject, bool, IsCullingMarker)
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

	template <>
	inline auto registerMembers<RE::NiRefObject>()
	{
		return members();
	}
	
	template <>
	inline auto registerMembers<RE::NiObject>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::NiObject, RE::NiRefObject)
		);
	}
	
	template <>
	inline auto registerMembers<RE::BSTextureSet>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::BSTextureSet, RE::NiObject)
		);
	}

	template <>
	inline auto registerMembers<RE::TESTexture>()
	{
		return members(
			VIRT_FUNC_GET_MEMBER(RE::TESTexture, UInt32, Size),
			VIRT_FUNC_GET_MEMBER(RE::TESTexture, std::string, SearchDir),
			member("Texture", &RE::TESTexture::texture)
		);
	}
	
	template <>
	inline auto registerMembers<RE::BGSTextureSet>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::BGSTextureSet, RE::TESBoundObject),
			BASE_TYPE_MEMBER(RE::BGSTextureSet, RE::BSTextureSet),
			member<RE::BGSTextureSet, std::vector<RE::TESTexture*>>("Textures", [](RE::BGSTextureSet* form)
			{
				std::vector<RE::TESTexture*> elements;
				for (auto i = 0; i < sizeof(form->textures) / sizeof(RE::TESTexture); i++)
				{
					elements.push_back(&form->textures[i]);
				}
		
				return elements;
				// return std::vector<RE::TESTexture*>(form->textures, std::end(form->textures));
			})
		);
	}

	template <>
	inline auto registerMembers<RE::TESIcon>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::TESIcon, RE::TESTexture)
		);
	}
	
	template <>
	inline auto registerMembers<RE::BGSMenuIcon>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::BGSMenuIcon, RE::TESForm),
			BASE_TYPE_MEMBER(RE::BGSMenuIcon, RE::TESIcon)
		);
	}
	
	template <>
	inline auto registerMembers<RE::TESGlobal>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::TESGlobal, RE::TESForm),
			member("Value", &RE::TESGlobal::value)
		);
	}

	template <>
	inline auto registerMembers<RE::TESFullName>()
	{
		return members(
			member("Name", &RE::TESFullName::name)
		);
	}

	template <>
	inline auto registerMembers<RE::TESDescription>()
	{
		return members(
			// TODO
		);
	}

	// TODO: Skill enum
	
	template <>
	inline auto registerMembers<RE::TESClass::Data::SkillWeights>()
	{
		return members(
			// TODO
		);
	}
	
	template <>
	inline auto registerMembers<RE::TESClass::Data::AttributeWeights>()
	{
		return members(
			member("Health", &RE::TESClass::Data::AttributeWeights::health),
			member("Magicka", &RE::TESClass::Data::AttributeWeights::magicka),
			member("Stamina", &RE::TESClass::Data::AttributeWeights::stamina)
		);
	}
	
	template <>
	inline auto registerMembers<RE::TESClass::Data>()
	{
		return members(
			member("Teaches", &RE::TESClass::Data::teaches),
			member("MaximumTrainingLevel", &RE::TESClass::Data::maximumTrainingLevel),
			member("SkillWeights", &RE::TESClass::Data::skillWeights),
			member("BleedoutDefault", &RE::TESClass::Data::bleedoutDefault),
			member("VoicePoints", &RE::TESClass::Data::voicePoints),
			member("AttributeWeights", &RE::TESClass::Data::attributeWeights)
		);
	}
	
	template <>
	inline auto registerMembers<RE::TESClass>()
	{
		return members(
			BASE_TYPE_MEMBER(RE::TESClass, RE::TESForm),
			BASE_TYPE_MEMBER(RE::TESClass, RE::TESFullName),
			BASE_TYPE_MEMBER(RE::TESClass, RE::TESDescription),
			BASE_TYPE_MEMBER(RE::TESClass, RE::TESTexture),
			member("Data", &RE::TESClass::data)
		);
	}

	template <>
	inline auto registerMembers<RE::TESReactionForm>()
	{
		return members(
			// TODO
		);
	}
	
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

namespace DarkId::Papyrus::DebugServer
{
#if SKYRIM
	#define FORM_TYPE_LIST(code) \
		code(RE::BGSKeyword) \
		code(RE::BGSLocationRefType) \
		code(RE::BGSAction) \
		code(RE::BGSTextureSet) \
		code(RE::BGSMenuIcon) \
		code(RE::TESGlobal) \
		code(RE::TESClass) \
		code(RE::TESFaction) \
		code(RE::BGSHeadPart) \
		code(RE::TESEyes) \
		code(RE::TESRace) \
		code(RE::TESSound) \
		code(RE::BGSAcousticSpace) \
		code(RE::EffectSetting) \
		code(RE::Script) \
		code(RE::TESLandTexture) \
		code(RE::EnchantmentItem) \
		code(RE::SpellItem) \
		code(RE::ScrollItem) \
		code(RE::TESObjectACTI) \
		code(RE::BGSTalkingActivator) \
		code(RE::TESObjectARMO) \
		code(RE::TESObjectBOOK) \
		code(RE::TESObjectCONT) \
		code(RE::TESObjectDOOR) \
		code(RE::IngredientItem) \
		code(RE::TESObjectLIGH) \
		code(RE::TESObjectMISC) \
		code(RE::BGSApparatus) \
		code(RE::TESObjectSTAT) \
		code(RE::BGSStaticCollection) \
		code(RE::BGSMovableStatic) \
		code(RE::TESGrass) \
		code(RE::TESObjectTREE) \
		code(RE::TESFlora) \
		code(RE::TESFurniture) \
		code(RE::TESObjectWEAP) \
		code(RE::TESAmmo) \
		code(RE::TESNPC) \
		code(RE::TESLevCharacter) \
		code(RE::TESKey) \
		code(RE::AlchemyItem) \
		code(RE::BGSIdleMarker) \
		code(RE::BGSNote) \
		code(RE::BGSConstructibleObject) \
		code(RE::BGSProjectile) \
		code(RE::BGSHazard) \
		code(RE::TESSoulGem) \
		code(RE::TESLevItem) \
		code(RE::TESWeather) \
		code(RE::TESClimate) \
		code(RE::BGSShaderParticleGeometryData) \
		code(RE::BGSReferenceEffect) \
		code(RE::TESRegion) \
		code(RE::NavMeshInfoMap) \
		code(RE::TESObjectCELL) \
		code(RE::TESObjectREFR) \
		code(RE::Actor) \
		code(RE::Character) \
		code(RE::PlayerCharacter) \
		code(RE::MissileProjectile) \
		code(RE::ArrowProjectile) \
		code(RE::GrenadeProjectile) \
		code(RE::BeamProjectile) \
		code(RE::FlameProjectile) \
		code(RE::ConeProjectile) \
		code(RE::BarrierProjectile) \
		code(RE::Hazard) \
		code(RE::TESWorldSpace) \
		code(RE::TESObjectLAND) \
		code(RE::NavMesh) \
		code(RE::TESTopic) \
		code(RE::TESTopicInfo) \
		code(RE::TESQuest) \
		code(RE::TESIdleForm) \
		code(RE::TESPackage) \
		code(RE::TESCombatStyle) \
		code(RE::TESLoadScreen) \
		code(RE::TESLevSpell) \
		code(RE::TESObjectANIO) \
		code(RE::TESWaterForm) \
		code(RE::TESEffectShader) \
		code(RE::BGSExplosion) \
		code(RE::BGSDebris) \
		code(RE::TESImageSpace) \
		code(RE::TESImageSpaceModifier) \
		code(RE::BGSListForm) \
		code(RE::BGSPerk) \
		code(RE::BGSBodyPartData) \
		code(RE::BGSAddonNode) \
		code(RE::ActorValueInfo) \
		code(RE::BGSCameraShot) \
		code(RE::BGSCameraPath) \
		code(RE::BGSVoiceType) \
		code(RE::BGSMaterialType) \
		code(RE::BGSImpactData) \
		code(RE::BGSImpactDataSet) \
		code(RE::TESObjectARMA) \
		code(RE::BGSEncounterZone) \
		code(RE::BGSLocation) \
		code(RE::BGSMessage) \
		code(RE::BGSRagdoll) \
		code(RE::BGSDefaultObjectManager) \
		code(RE::BGSLightingTemplate) \
		code(RE::BGSMusicType) \
		code(RE::BGSFootstep) \
		code(RE::BGSFootstepSet) \
		code(RE::BGSStoryManagerBranchNode) \
		code(RE::BGSStoryManagerQuestNode) \
		code(RE::BGSStoryManagerEventNode) \
		code(RE::BGSDialogueBranch) \
		code(RE::BGSMusicTrackFormWrapper) \
		code(RE::TESWordOfPower) \
		code(RE::TESShout) \
		code(RE::BGSEquipSlot) \
		code(RE::BGSRelationship) \
		code(RE::BGSScene) \
		code(RE::BGSAssociationType) \
		code(RE::BGSOutfit) \
		code(RE::BGSArtObject) \
		code(RE::BGSMaterialObject) \
		code(RE::BGSMovementType) \
		code(RE::BGSSoundDescriptorForm) \
		code(RE::BGSDualCastData) \
		code(RE::BGSSoundCategory) \
		code(RE::BGSSoundOutput) \
		code(RE::BGSCollisionLayer) \
		code(RE::BGSColorForm) \
		code(RE::BGSReverbParameters) \
		code(RE::BGSLensFlare) \
		code(RE::BGSVolumetricLighting) \

#endif
}