#pragma once
#include "Meta.h"
#include "GameInterfaces.h"

namespace meta
{
#if SKYRIM
	template <>
	inline auto registerMembers<RE::TESForm>()
	{
		return members(
			member<RE::TESForm, bool>("Has3D", [](RE::TESForm* form) { return form->Has3D(); }),
			member("HasWorldModel", &RE::TESForm::HasWorldModel)
		);
	}

	template <>
	inline auto registerMembers<RE::BGSKeyword>()
	{
		return members(
			member<RE::BGSKeyword, RE::TESForm*>("TESForm", [](RE::BGSKeyword* form) { return form; }),
			member("Keyword", &RE::BGSKeyword::keyword)
		);
	}

	template <>
	inline auto registerMembers<RE::BGSLocationRefType>()
	{
		return members(
			member<RE::BGSLocationRefType, RE::BGSKeyword*>("BGSKeyword", [](RE::BGSLocationRefType* form) { return form; })
		);
	}

	//template <>
	//inline auto registerMembers<RE::BGSAction>()
	//{
	//	return std::tuple_cat(
	//		meta::getMembers<RE::BGSKeyword>(),
	//		members(
	//			member("Index", &RE::BGSAction::index)
	//		)
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::TESObject>()
	//{
	//	return std::tuple_cat(
	//		meta::getMembers<RE::TESForm>(),
	//		members(
	//			member("CanAnimate", &RE::TESObject::CanAnimate),
	//			// member("GetWaterActivator", &RE::TESObject::GetWaterActivator),
	//			member("IsAutoCalc", &RE::TESObject::IsAutoCalc),
	//			member("IsMarker", &RE::TESObject::IsMarker),
	//			member("IsCullingMarker", &RE::TESObject::IsCullingMarker)
	//		)
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::TESBoundObject>()
	//{
	//	return std::tuple_cat(
	//		meta::getMembers<RE::TESObject>(),
	//		members(
	//			member("Index", &RE::BGSAction::index)
	//		)
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::BGSTextureSet>()
	//{
	//	return std::tuple_cat(
	//		meta::getMembers<RE::TESBoundObject>(),
	//		members(
	//			// TODO: Array issues
	//			// member("Textures", &RE::BGSTextureSet::textures)
	//		)
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::TESTexture>()
	//{
	//	return members(
	//		// member("Size", &RE::TESTexture::GetSize),
	//		// member("SearchDir", &RE::TESTexture::GetSearchDir),
	//		// member("Texture", &RE::TESTexture::texture)
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::TESIcon>()
	//{
	//	return std::tuple_cat(
	//		meta::getMembers<RE::TESTexture>()
	//	);
	//}
	//
	//template <>
	//inline auto registerMembers<RE::BGSMenuIcon>()
	//{
	//	return std::tuple_cat(
	//		meta::getMembers<RE::TESForm>(),
	//		meta::getMembers<RE::TESIcon>()
	//	);
	//}
	//
	//template <>
	//inline auto registerMembers<RE::TESGlobal>()
	//{
	//	return std::tuple_cat(
	//		meta::getMembers<RE::TESForm>(),
	//		members(
	//			member("Value", &RE::TESGlobal::value)
	//		)
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::TESFullName>()
	//{
	//	return members(
	//		member("Name", &RE::TESFullName::name)
	//	);
	//}

	//template <>
	//inline auto registerMembers<RE::TESDescription>()
	//{
	//	return members(
	//		// TODO
	//	);
	//}

	//// TODO: Skill enum
	//
	//template <>
	//inline auto registerMembers<RE::TESClass::Data::SkillWeights>()
	//{
	//	return members(
	//		// TODO
	//	);
	//}
	//
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
	//	return std::tuple_cat(
	//		meta::getMembers<RE::TESForm>(),
	//		meta::getMembers<RE::TESFullName>(),
	//		meta::getMembers<RE::TESDescription>(),
	//		meta::getMembers<RE::TESTexture>(),
	//		members(
	//			member("Data", &RE::TESClass::data)
	//		)
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
	//template <>
	//inline auto registerMembers<RE::TESFaction>()
	//{
	//	return std::tuple_cat(
	//		meta::getMembers<RE::TESForm>(),
	//		meta::getMembers<RE::TESFullName>(),
	//		meta::getMembers<RE::TESReactionForm>(),
	//		members(
	//			// TODO
	//		)
	//	);
	//}
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