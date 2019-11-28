#pragma once

#include "RE/BGSNamedPackageData.h"  // BGSNamedPackageData
#include "RE/BSFixedString.h"  // BSFixedString


namespace RE
{
	class TESFile;


	template <class Parent, class Pointer /*, const BSFixedString& TYPE_NAME*/>
	class BGSPackageDataPointerTemplate : public BGSNamedPackageData<Parent>
	{
	public:
		virtual ~BGSPackageDataPointerTemplate();							// 00

		// override (BGSNamedPackageData<Parent>)
		virtual void					Unk_05(void) override;				// 05 - { return 1; }
		virtual const BSFixedString&	GetTypeName() const override;		// 0B - { return TYPE_NAME; }

		// add
		virtual void					LoadPointer(TESFile* a_mod) = 0;	// ??


		// members
		Pointer* pointer;	// ??
	};
}
