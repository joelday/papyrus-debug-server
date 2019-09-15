#pragma once
#include "Meta.h"
#include "GameInterfaces.h"

namespace meta
{
	template <>
	inline auto registerMembers<RE::TESForm>()
	{
		return members(
			member("FormID", &RE::TESForm::GetFormID),
			member("FormType", &RE::TESForm::GetFormType)
		);
	}
}