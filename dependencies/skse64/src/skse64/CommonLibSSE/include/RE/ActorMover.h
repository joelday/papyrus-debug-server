#pragma once

#include "skse64/GameRTTI.h"  // RTTI_ActorMover


namespace RE
{
	class Actor;


	class ActorMover
	{
	public:
		inline static const void* RTTI = RTTI_ActorMover;


		virtual ~ActorMover();			// 00

		// add
		virtual void	Unk_01(void);	// 01 - { return; }
		virtual void	Unk_02(void);	// 02 - { return 0; }
		virtual void	Unk_03(void);	// 03 - { return 0; }


		// members
		Actor* actor;	// 08
	};
	STATIC_ASSERT(sizeof(ActorMover) == 0x10);
}
