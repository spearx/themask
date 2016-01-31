#pragma once

#include "utils/math/Math.h"
#include "utils/Callbacks.h"
#include "abathur_entity.h"

namespace Abathur
{
  enum class ETriggerEvent
  {
    ON_ENTER_EVENT,
    ON_EXIT_EVENT,
    UNKNOWN_EVENT
  };

  typedef CFunctionCaller2<TEntityId, ETriggerEvent> TPhysXTriggerCallback;

  bool InitPhysX(const Vector3 &gravity);
  void DestroyPhysX();
  void SetRenderDebugPhysX(bool enabled);
  void AddPhysXPlane(const Vector3 &normal, float distance);
  void RegisterPhysXTrigger(TPhysXTriggerCallback callback);
}

