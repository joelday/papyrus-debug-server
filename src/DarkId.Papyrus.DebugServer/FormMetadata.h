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