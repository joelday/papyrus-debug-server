#pragma once


namespace RE
{
	using FormID = UInt32;
	using RefHandle = UInt32;
	using VMHandle = UInt64;
	using FormType32 = UInt32;


	enum class VMTypeID : std::size_t
	{
		kNone			= 0,
		kObject	= 1,	// Number not actually used by VMValue
		kString		= 2,
		kInt			= 3,
		kFloat			= 4,
		kBool			= 5,
		kVariable		= 6,	// Points to a VMValue
		kStruct		= 7,	// Number not actually used by VMValue

		kArrayOffset		= 10,

		kObjectArray	= 11,
		kStringArray		= 12,
		kIntArray			= 13,
		kFloatArray		= 14,
		kBoolArray			= 15,
		kVariableArray		= 16,
		kStructArray		= 17,	// Number not actually used by VMValue
		kArrayEnd			= 18,

		kIntegralStart		= kStringArray,
		kIntegralEnd		= kVariableArray,
	};

	constexpr float FNAN = 0xFF7FFFFF;
}
