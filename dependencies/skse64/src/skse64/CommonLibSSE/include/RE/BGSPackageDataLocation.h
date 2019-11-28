#pragma once

#include "skse64/GameRTTI.h"  // RTTI_BGSPackageDataLocation

#include "RE/BGSPackageDataPointerTemplate.h"  // BGSPackageDataPointerTemplate
#include "RE/IPackageDataAIWorldLocationHandle.h"  // IPackageDataAIWorldLocationHandle


namespace RE
{
	class PackageLocation;

	//const BSFixedString kPackageDataLocationTypeName("Location");


	class BGSPackageDataLocation : public BGSPackageDataPointerTemplate<IPackageDataAIWorldLocationHandle, PackageLocation /*, kPackageDataLocationTypeName*/>
	{
	public:
		inline static const void* RTTI = RTTI_BGSPackageDataLocation;


		virtual ~BGSPackageDataLocation();									// 00

		// override (BGSPackageDataPointerTemplate<IPackageDataAIWorldLocationHandle, PackageLocation, kPackageDataLocationTypeName>)
		virtual void	Unk_06(void) override;								// 06
		virtual void	Unk_07(void) override;								// 07
		virtual void	LoadBuffer(BGSLoadFormBuffer* a_buf) override;		// 08
		virtual void	Unk_09(void) override;								// 09 - { return; }
		virtual bool	GetDataAsString(BSString* a_dst) const override;	// 0A
		virtual void	Unk_0C(void) override;								// 0C - { return pointer->type == PackageLocation::Type::kNearPackageStartLocation; }
	};
	STATIC_ASSERT(sizeof(BGSPackageDataLocation) == 0x20);
}
