#pragma once

#include "abathur.h"
#include "utils/compileTime/compile_time_utils.h"

namespace World
{
	class CTriggers
	{
  public:
    
    enum class ETriggerEvent {
      ON_ENTER,
      ON_EXIT,
      NOT_EVENT
    };

    typedef CFunctionCaller2<const std::string &, ETriggerEvent> TTriggerEventCallback;

 private:   

   enum class ETriggerType {
     TRIGGER_BOX,
     TRIGGER_SPHERE
   };

   struct TTriggerBox {
      Vector3 min;
      Vector3 max;
      bool isInside(const Vector3 &pos) const;
    };
    struct TTriggerSphere {
      Vector3 center;
      float radius;
      bool isInside(const Vector3 &pos) const;
    };

    struct TTrigger
    {
      ETriggerType type;
      TTriggerBox box;
      TTriggerSphere sphere;
      bool is_inside;
      std::string event_name;
    };

    typedef std::vector<TTrigger> VTriggers;
    VTriggers vtriggers;

    TTriggerEventCallback mListenner;
    static CTriggers*     m_pInstance;

    static CTriggers& CreateInstance() { m_pInstance = new CTriggers(); return *m_pInstance; }

	public:

    CTriggers();
    void RegisterTriggerSphere(Abathur::TEntityId entity, float radius, const std::string &event_name);
    void RegisterTriggerBox(Vector3 min, Vector3 max, const std::string &event_name);
    void RegisterListenner(TTriggerEventCallback listener);

    void SetPlayerPosition(Vector3 pos);

    static CTriggers& Get() { return m_pInstance ? *m_pInstance : CreateInstance(); }
  };
}