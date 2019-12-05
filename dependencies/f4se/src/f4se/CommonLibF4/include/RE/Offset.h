#pragma once


namespace RE
{
	namespace Offset
	{
		namespace BSFixedString
		{
			// 44 88 44 24 18 48 89 54 24 10 48 89 4C 24 08 53 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 58
			constexpr std::uintptr_t CtorU8 = 0x01B43DB0;	// 1_10_138
		}

		namespace CRC32Calculator
		{
			// TODO: IndirectSig:
			constexpr std::uintptr_t SizeOf32 = 0x01B107A0;		// 1_10_138
			// TODO: IndirectSig:
			constexpr std::uintptr_t SizeOf64 = 0x01B10830;		// 1_10_138
			// TODO: IndirectSig:
			constexpr std::uintptr_t SizeOfSize = 0x01B106B0;	// 1_10_138
		}

		namespace BSScript
		{
			namespace Struct
			{
				constexpr std::uintptr_t Dtor = 0x0271B7E0;		// 1_10_138
			}
		}
	}
}
