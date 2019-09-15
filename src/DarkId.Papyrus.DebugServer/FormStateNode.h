#pragma once

#include "StateNodeBase.h"
#include "RE/FormTypes.h"
#include <map>
#include <functional>
#include <variant>

namespace DarkId::Papyrus::DebugServer
{
	//using Structured = std::variant<>;
	//using Value = std::variant<UInt32, SInt32, float, bool, std::string, Structured, void>;

	//
	
	// template <class T >
	
	//template <class T>
	//using MemberAccessor
	
	//template <class T>
	//using MemberInfo = std::function<void(std::string, std::function<void(T*, std::string&)>)>;
	
	/**
	 * 1. Need types and their members
	 * 2. Some types are primitives or not RTTI
	 * 3. Others are RTTI
	 * 4. 
	 * 
	 */
	
//#define VALUE_TYPE_LIST(code) \
//        code(Identifier, id, VMIdentifier*) \
//        code(String, GetStr(), BSFixedString*) \
//        code(Int, i, SInt32) \
//        code(Float, f, float) \
//        code(Bool, b, bool) \
//        code(Variable, var, VMValue*) \
//
//	template<typename... T>
//	class ValueVisitorBase
//	{
//	public:
//		void Visit(VMValue* value, T... out)
//		{
//			if (!value)
//			{
//				return;
//			}
//
//			if (value->IsComplexArrayType() && value->GetComplexType()->GetType() == VMValue::kType_Struct)
//			{
//				std::vector<VMValue::StructData*> elements;
//
//				if (value->data.arr)
//				{
//					for (auto i = 0; i < value->data.arr->arr.count; i++)
//					{
//						VMValue elementValue;
//						value->data.arr->arr.GetNthItem(i, elementValue);
//						elements.push_back(elementValue.data.strct);
//					}
//				}
//
//				VisitStructArray(value, elements, out...);
//
//				return;
//			}
//
//			if (value->IsArrayType() && (!value->IsComplexArrayType() || value->GetComplexType()->GetType() != VMValue::kType_Struct))
//			{
//				const auto typeId = value->GetTypeEnum();
//				switch (typeId)
//				{
//#define DEFINE_SWITCH_CASE(name, accessor, type)  \
//            case VMValue::kType_##name##Array: \
//                std::vector<VMValue*> ##name##ValueElements; \
//                std::vector<##type> ##name##Elements; \
//                \
//                if (value->data.arr) \
//                { \
//                    for (auto i = 0; i < value->data.arr->arr.count; i++) \
//                    { \
//                        VMValue elementValue; \
//                        value->data.arr->arr.GetNthItem(i, elementValue); \
//                        ##name##ValueElements.push_back(&elementValue); \
//                        ##name##Elements.push_back(elementValue.data.##accessor); \
//                    } \
//                } \
//                \
//                Visit##Array(value, ##name##ValueElements, out...); \
//                Visit##name##Array(value, ##name##Elements, out...); \
//                \
//                break; \
//
//					VALUE_TYPE_LIST(DEFINE_SWITCH_CASE)
//
//#undef DEFINE_SWITCH_CASE
//				}
//
//				return;
//			}
//
//			if (value->IsComplexType() && value->GetComplexType()->GetType() == VMValue::kType_Struct)
//			{
//				VisitStruct(value, value->data.strct, out...);
//				return;
//			}
//
//			const auto typeId = value->GetTypeEnum();
//
//			switch (typeId)
//			{
//#define DEFINE_SWITCH_CASE(name, accessor, type)  \
//            case VMValue::kType_##name: Visit##name(value, value->data.##accessor, out...); break; \
//
//				VALUE_TYPE_LIST(DEFINE_SWITCH_CASE)
//
//#undef DEFINE_SWITCH_CASE
//			}
//		}
//
//		virtual void DefaultVisit(VMValue* vmValue, T... out)
//		{
//		}
//
//#define DEFINE_VISIT(name, _, type)  \
//        virtual bool Visit##name(VMValue* vmValue, ##type value, T... out) { DefaultVisit(value, out...); } \
//        virtual bool Visit##name##Array(VMValue* vmValue, const std::vector<##type>& values, T... out) { DefaultVisit(value, out...); } \
//
//		VALUE_TYPE_LIST(DEFINE_VISIT)
//
//#undef DEFINE_VISIT
//
//			virtual void VisitStruct(VMValue* vmValue, VMValue::StructData* value, T... out)
//		{
//			DefaultVisit(vmValue, out...);
//		}
//
//		virtual void VisitStructArray(VMValue* vmValue, const std::vector<VMValue::StructData*>& values, T... out)
//		{
//			DefaultVisit(vmValue, out...);
//		}
//
//		virtual void VisitArray(VMValue* vmValue, const std::vector<VMValue*>& values, T... out)
//		{
//		}
//	};
	
	class FormStateNode :
		public StateNodeBase,
		public IProtocolVariableSerializable,
		public IStructuredState
	{

		
		
	private:
		inline static std::map<RE::FormType, std::string> _formDisplayNames =
		{
			{ RE::FormType::PluginInfo, "Plugin Info (TES4)" },
			{ RE::FormType::FormGroup, "Form Group (GRUP)" },
			{ RE::FormType::GameSetting, "Game Setting (GMST)" },
			{ RE::FormType::Keyword, "Keyword (KYWD)" },
			{ RE::FormType::LocationRefType, "Location Ref Type (LCRT)" },
			{ RE::FormType::Action, "Action (AACT)" },
			{ RE::FormType::TextureSet, "Texture Set (TXST)" },
			{ RE::FormType::MenuIcon, "Menu Icon (MICN)" },
			{ RE::FormType::Global, "Global (GLOB)" },
			{ RE::FormType::Class, "Class (CLAS)" },
			{ RE::FormType::Faction, "Faction (FACT)" },
			{ RE::FormType::HeadPart, "Head Part (HDPT)" },
			{ RE::FormType::Eyes, "Eyes (EYES)" },
			{ RE::FormType::Race, "Race (RACE)" },
			{ RE::FormType::Sound, "Sound (SOUN)" },
			{ RE::FormType::AcousticSpace, "Acoustic Space (ASPC)" },
			{ RE::FormType::Skill, "Skill (SKIL)" },
			{ RE::FormType::MagicEffect, "Magic Effect (MGEF)" },
			{ RE::FormType::Script, "Script (SCPT)" },
			{ RE::FormType::LandTexture, "Land Texture (LTEX)" },
			{ RE::FormType::Enchantment, "Enchantment (ENCH)" },
			{ RE::FormType::Spell, "Spell (SPEL)" },
			{ RE::FormType::Scroll, "Scroll (SCRL)" },
			{ RE::FormType::Activator, "Activator (ACTI)" },
			{ RE::FormType::TalkingActivator, "Talking Activator (TACT)" },
			{ RE::FormType::Armor, "Armor (ARMO)" },
			{ RE::FormType::Book, "Book (BOOK)" },
			{ RE::FormType::Container, "Container (CONT)" },
			{ RE::FormType::Door, "Door (DOOR)" },
			{ RE::FormType::Ingredient, "Ingredient (INGR)" },
			{ RE::FormType::Light, "Light (LIGH)" },
			{ RE::FormType::Misc, "Misc (MISC)" },
			{ RE::FormType::Apparatus, "Apparatus (APPA)" },
			{ RE::FormType::Static, "Static (STAT)" },
			{ RE::FormType::StaticCollection, "Static Collection (SCOL)" },
			{ RE::FormType::MovableStatic, "Movable Static (MSTT)" },
			{ RE::FormType::Grass, "Grass (GRAS)" },
			{ RE::FormType::Tree, "Tree (TREE)" },
			{ RE::FormType::Flora, "Flora (FLOR)" },
			{ RE::FormType::Furniture, "Furniture (FURN)" },
			{ RE::FormType::Weapon, "Weapon (WEAP)" },
			{ RE::FormType::Ammo, "Ammo (AMMO)" },
			{ RE::FormType::NPC, "NPC (NPC_)" },
			{ RE::FormType::LeveledNPC, "Leveled NPC (LVLN)" },
			{ RE::FormType::KeyMaster, "Key Master (KEYM)" },
			{ RE::FormType::AlchemyItem, "Alchemy Item (ALCH)" },
			{ RE::FormType::IdleMarker, "Idle Marker (IDLM)" },
			{ RE::FormType::Note, "Note (NOTE)" },
			{ RE::FormType::ConstructibleObject, "Constructible Object (COBJ)" },
			{ RE::FormType::Projectile, "Projectile (PROJ)" },
			{ RE::FormType::Hazard, "Hazard (HAZD)" },
			{ RE::FormType::SoulGem, "Soul Gem (SLGM)" },
			{ RE::FormType::LeveledItem, "Leveled Item (LVLI)" },
			{ RE::FormType::Weather, "Weather (WTHR)" },
			{ RE::FormType::Climate, "Climate (CLMT)" },
			{ RE::FormType::ShaderParticleGeometryData, "Shader Particle Geometry Data (SPGD)" },
			{ RE::FormType::ReferenceEffect, "Reference Effect (RFCT)" },
			{ RE::FormType::Region, "Region (REGN)" },
			{ RE::FormType::Navigation, "Navigation (NAVI)" },
			{ RE::FormType::Cell, "Cell (CELL)" },
			{ RE::FormType::Reference, "Reference (REFR)" },
			{ RE::FormType::ActorCharacter, "Actor Character (ACHR)" },
			{ RE::FormType::ProjectileMissile, "Projectile Missile (PMIS)" },
			{ RE::FormType::ProjectileArrow, "Projectile Arrow (PARW)" },
			{ RE::FormType::ProjectileGrenade, "Projectile Grenade (PGRE)" },
			{ RE::FormType::ProjectileBeam, "Projectile Beam (PBEA)" },
			{ RE::FormType::ProjectileFlame, "Projectile Flame (PFLA)" },
			{ RE::FormType::ProjectileCone, "Projectile Cone (PCON)" },
			{ RE::FormType::ProjectileBarrier, "Projectile Barrier (PBAR)" },
			{ RE::FormType::PlacedHazard, "Placed Hazard (PHZD)" },
			{ RE::FormType::WorldSpace, "World Space (WRLD)" },
			{ RE::FormType::Land, "Land (LAND)" },
			{ RE::FormType::NavMesh, "Nav Mesh (NAVM)" },
			{ RE::FormType::TLOD, "TLOD" },
			{ RE::FormType::Dialogue, "Dialogue (DIAL)" },
			{ RE::FormType::Info, "Info (INFO)" },
			{ RE::FormType::Quest, "Quest (QUST)" },
			{ RE::FormType::Idle, "Idle (IDLE)" },
			{ RE::FormType::Package, "Package (PACK)" },
			{ RE::FormType::CombatStyle, "Combat Style (CSTY)" },
			{ RE::FormType::LoadScreen, "Load Screen (LSCR)" },
			{ RE::FormType::LeveledSpell, "Leveled Spell (LVSP)" },
			{ RE::FormType::AnimatedObject, "Animated Object (ANIO)" },
			{ RE::FormType::Water, "Water (WATR)" },
			{ RE::FormType::EffectShader, "Effect Shader (EFSH)" },
			{ RE::FormType::TOFT, "TOFT" },
			{ RE::FormType::Explosion, "Explosion (EXPL)" },
			{ RE::FormType::Debris, "Debris (DEBR)" },
			{ RE::FormType::ImageSpace, "Image Space (IMGS)" },
			{ RE::FormType::ImageAdapter, "Image Adapter (IMAD)" },
			{ RE::FormType::FormList, "Form List (FLST)" },
			{ RE::FormType::Perk, "Perk (PERK)" },
			{ RE::FormType::BodyPartData, "Body Part Data (BPTD)" },
			{ RE::FormType::AddonNode, "Addon Node (ADDN)" },
			{ RE::FormType::ActorValueInfo, "Actor Value Info (AVIF)" },
			{ RE::FormType::CameraShot, "Camera Shot (CAMS)" },
			{ RE::FormType::CameraPath, "Camera Path (CPTH)" },
			{ RE::FormType::VoiceType, "Voice Type (VTYP)" },
			{ RE::FormType::MaterialType, "Material Type (MATT)" },
			{ RE::FormType::Impact, "Impact (IPCT)" },
			{ RE::FormType::ImpactDataSet, "Impact Data Set (IPDS)" },
			{ RE::FormType::Armature, "Armature (ARMA)" },
			{ RE::FormType::EncounterZone, "Encounter Zone (ECZN)" },
			{ RE::FormType::Location, "Location (LCTN)" },
			{ RE::FormType::Message, "Message (MESG)" },
			{ RE::FormType::Ragdoll, "Ragdoll (RGDL)" },
			{ RE::FormType::DefaultObject, "Default Object (DOBJ)" },
			{ RE::FormType::LightingMaster, "Lighting Master (LGTM)" },
			{ RE::FormType::MusicType, "Music Type (MUSC)" },
			{ RE::FormType::Footstep, "Footstep (FSTP)" },
			{ RE::FormType::FootstepSet, "Footstep Set (FSTS)" },
			{ RE::FormType::StoryManagerBranchNode,"Story Manager Branch Node (SMBN)" },
			{ RE::FormType::StoryManagerQuestNode," Story Manager Quest Node (SMQN)" },
			{ RE::FormType::StoryManagerEventNode,"Story Manager Event Node (SMEN)" },
			{ RE::FormType::DialogueBranch, "Dialogue Branch (DLBR)" },
			{ RE::FormType::MusicTrack, "Music Track (MUST)" },
			{ RE::FormType::DialogueView, "Dialogue View (DLVW)" },
			{ RE::FormType::WordOfPower, "Word Of Power (WOOP)" },
			{ RE::FormType::Shout, "Shout (SHOU)" },
			{ RE::FormType::EquipSlot, "Equip Slot (EQUP)" },
			{ RE::FormType::Relationship, "Relationship (RELA)" },
			{ RE::FormType::Scene, "Scene (SCEN)" },
			{ RE::FormType::AssociationType, "Association Type (ASTP)" },
			{ RE::FormType::Outfit, "Outfit (OTFT)" },
			{ RE::FormType::ArtObject, "Art Object (ARTO)" },
			{ RE::FormType::MaterialObject, "Material Object (MATO)" },
			{ RE::FormType::MovementType, "Movement Type (MOVT)" },
			{ RE::FormType::SoundRecord, "Sound Record (SNDR)" },
			{ RE::FormType::DualCastData, "Dual Cast Data (DUAL)" },
			{ RE::FormType::SoundCategory, "Sound Category (SNCT)" },
			{ RE::FormType::SoundOutputModel, "Sound Output Model (SOPM)" },
			{ RE::FormType::CollisionLayer, "Collision Layer (COLL)" },
			{ RE::FormType::ColorForm, "Color Form (CLFM)" },
			{ RE::FormType::ReverbParam, "Reverb Param (REVB)" },
			{ RE::FormType::LensFlare, "Lens Flare (LENS)" },
			{ RE::FormType::LensSprite, "Lens Sprite (LSPR)" },
			{ RE::FormType::VolumetricLighting, "Volumetric Lighting (VOLI)" }
		};
	};
}
