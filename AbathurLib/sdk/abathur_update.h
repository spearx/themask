#pragma once

#include "utils/Callbacks.h"
#include "utils/compileTime/compile_time_utils.h"

namespace Abathur
{
	enum class EUpdateStage
	{
		Earliest = 1,
		Early,
		Default,
		Late,
		Latest,
	};

	enum class EUpdateTier
	{
		PrePhysics = 1,
		PostPhysics,
		PreRender,
		PostRender,
	};

	typedef uint32 TUpdatePriority;
	enum { InvalidUpdatePriority = 0u };

	constexpr inline TUpdatePriority GetUpdatePriority(const EUpdateTier tier, const EUpdateStage stage) { return ((ToUnderlyingType(tier)) << 8 | ToUnderlyingType(stage)); }
	constexpr inline EUpdateTier     GetUpdateTier(const TUpdatePriority priority) { return EUpdateTier(priority >> 8); }
	constexpr inline EUpdateStage    GetUpdateStage(const TUpdatePriority priority) { return EUpdateStage(priority & 0xffff); }

	struct SUpdateContext
	{
		SUpdateContext();
		explicit SUpdateContext(const float _frameTime);

		float frameTime;
	};

	WRAP_TYPE(uint32, TCallbackId, 0u);
	typedef CFunctionCaller1<const SUpdateContext&> TUpdateCallback;

	class CScopedUpdate
	{
	public:
		CScopedUpdate();
		~CScopedUpdate();

		void SetCallback(TUpdateCallback callback);
		void SetPriority(const TUpdatePriority priority);

		void Register();
		void Register(const TUpdatePriority priority);
		void Register(const TUpdatePriority priority, TUpdateCallback callback);
		void Unregister();

	private:
		TCallbackId       m_id;
		TUpdatePriority   m_priority;
		TUpdateCallback   m_callback;
	};

}