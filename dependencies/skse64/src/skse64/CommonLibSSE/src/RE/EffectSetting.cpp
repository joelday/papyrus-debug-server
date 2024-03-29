#include "RE/EffectSetting.h"

#include "RE/ActorValues.h"  // ActorValue


namespace RE
{
	ActorValue EffectSetting::GetMagickSkill()
	{
		return data.magicSkill;
	}


	UInt32 EffectSetting::GetMinimumSkillLevel()
	{
		return data.minimumSkillLevel;
	}


	bool EffectSetting::HasArchetype(Data::Archetype a_type)
	{
		return data.archetype == a_type;
	}
}
