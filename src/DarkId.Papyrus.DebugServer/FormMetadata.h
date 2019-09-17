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
			member("ID", &RE::TESForm::GetFormID)
		);
	}

	template <>
	inline auto registerMembers<RE::TESGlobal>()
	{
		return std::tuple_cat(
			meta::getMembers<RE::TESForm>(),
			members(member("Value", &RE::TESGlobal::value))
		);
	}
#endif
}

namespace DarkId::Papyrus::DebugServer
{
	#define FORM_TYPE_LIST(code) \
		code(RE::BGSKeyword) \
		code(RE::BGSLocationRefType) \
		code(RE::BGSLocationRefType) \
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
		
}