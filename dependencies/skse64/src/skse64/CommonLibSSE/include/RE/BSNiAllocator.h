#pragma once

#include "skse64/GameRTTI.h"  // RTTI_BSNiAllocator

#include "RE/NiAllocator.h"  // NiAllocator


namespace RE
{
	class BSNiAllocator : public NiAllocator
	{
	public:
		inline static const void* RTTI = RTTI_BSNiAllocator;


		virtual ~BSNiAllocator();																																																										// 00

		// override (
		virtual void*	Allocate(std::size_t& a_sizeInBytes, std::size_t& a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate, const char* a_file, SInt32 a_line, const char* a_function) override;											// 01
		virtual void	Deallocate(void* a_memory, NiMemEventType a_eventType, std::size_t a_sizeInBytes) override;																																						// 02
		virtual void*	Reallocate(void* a_memory, size_t& a_sizeInBytes, std::size_t& a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate, std::size_t a_sizeCurrent, const char* a_file, SInt32 a_line, const char* a_function) override;	// 03
		virtual bool	TrackAllocate(const void* const a_memory, std::size_t a_sizeInBytes, NiMemEventType a_eventType, const char* a_file, SInt32 a_line, const char* a_function) override;																			// 04
		virtual bool	TrackDeallocate(const void* const a_memory, NiMemEventType a_eventType) override;																																								// 05
		virtual void	Unk_06(void) override;																																																							// 06 - implements a realloc
		virtual void	Initialize() override;																																																							// 07 - { return; }
		virtual void	Shutdown() override;																																																							// 08 - { return; }
		virtual bool	VerifyAddress(const void* a_memory) override;																																																	// 09 - { return true; }
	};
	STATIC_ASSERT(sizeof(BSNiAllocator) == 0x8);
}
