#include "triggers.h"

namespace World
{
  CTriggers* CTriggers::m_pInstance = nullptr;

  CTriggers::CTriggers() {


  }

  void CTriggers::RegisterTriggerSphere(Abathur::TEntityId entityId, float radius, const std::string &event_name)
  {
    TTrigger t;
    t.type = ETriggerType::TRIGGER_SPHERE;
    t.sphere.center = Vector3(0.0f);
    t.sphere.radius = radius;
    t.event_name = event_name;
    Abathur::TAbathurEntity *entity = Abathur::GetEntity(entityId);
    ASSERT(entity);
    if (Abathur::TLocationComponent* pLocComponent = entity->QueryComponent<Abathur::TLocationComponent>())
    {
      Vector3 pos = pLocComponent->mtx.GetTranslation();
      t.sphere.center = pos;
    }
    vtriggers.push_back(t);
  }

  void CTriggers::RegisterTriggerBox(Vector3 &min, Vector3 &max, const std::string &event_name) 
  {
    TTrigger t;
    t.type = ETriggerType::TRIGGER_BOX;
    t.box.min = min;
    t.box.min.MinBound(max);
    t.box.max = min;
    t.box.max.MaxBound(max);
    t.event_name = event_name;
    vtriggers.push_back(t);
  }

  void CTriggers::RegisterListenner(TTriggerEventCallback listener)
  {
    mListenner = listener;
  }

  void CTriggers::SetPlayerPosition(const Vector3 &pos)
  {
    if (!mListenner.IsFunctionValid())
      return;

    for (auto &t : vtriggers) 
    {
      bool is_inside = false;
      if (t.type == ETriggerType::TRIGGER_BOX)
      {
        is_inside = t.box.isInside(pos);
      }
      else if (t.type == ETriggerType::TRIGGER_SPHERE)
      {
        is_inside = t.sphere.isInside(pos);
      }
      if (is_inside)
      {
        mListenner(t.event_name);
      }
    }
  }

  bool CTriggers::TTriggerBox::isInside(const Vector3 pos) const {
    if (min.x < pos.x && max.x > pos.x && min.z < pos.z && max.z > pos.z) {
      return true;
    }
    return false;
  }

  bool CTriggers::TTriggerSphere::isInside(const Vector3 pos) const {
    float distance = pos.GetDistance(center);
    if (distance <= radius) {
      return true;
    }
    return false;
  }


}

