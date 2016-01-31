#include "centinels.h"
#include "world.h"
#include "player_component.h"
#include "menu/menu.h"

namespace World
{

  CCentinels::CCentinels()
    : m_speedFactor(1.0f)
    , m_timeInIdle(4.0f)
  {

  }

  void CCentinels::Update(const Abathur::SUpdateContext& context) 
  {
    Menu::CMenu::Get().SetTimeFactor(1.0f);
    Menu::CMenu::Get().SetTotemIconState(false);
    bool oneTotemAwake = false;

    float speed_elapsed = context.frameTime * m_speedFactor;
    for (auto &c : m_centinels) 
    {
      if (c.m_state == EState::SLEEPING) continue;

      if (c.m_timeToTurn > 0.0f)
      {
        oneTotemAwake = true;
        c.m_timeToTurn -= context.frameTime;
        Menu::CMenu::Get().SetTotemIconState(true);

        Abathur::TEntityId eID = CWorld::Get().GetPlayerEntityId();
        Abathur::TAbathurEntity *pPlayerEntity = Abathur::GetEntity(eID);
        CPlayerComponent *comp = pPlayerEntity->QueryComponent<CPlayerComponent>();
        bool is_moving = comp->IsMoving();
        if (is_moving) {
          Menu::CMenu::Get().SetTimeFactor(c.m_timeFactorPlayer);
          break;
        }
        continue;
      }

      Matrix33 mtx;
      mtx.SetIdentity();
      Abathur::TAbathurEntity *pTotemEntity = Abathur::GetEntity(c.m_entity);
      ASSERT(pTotemEntity);      
      c.m_yaw += c.m_turnSpeed * speed_elapsed;
      if( c.m_yaw >= gfPI2 )
      {
        //
        c.m_yaw = 0.0f;
        c.m_timeToTurn = m_timeInIdle;
        printf("Centinel is Awake Warning!!!\n");
        //Abathur::setVolumeAudio(m_tottemAudio, 0.0f);
      }
      Abathur::TLocationComponent* pLocComponent = pTotemEntity->QueryComponent<Abathur::TLocationComponent>();
      mtx.SetRotationY(c.m_yaw);
      Vector3 loc = pLocComponent->mtx.GetTranslation();
      pLocComponent->mtx = mtx * c.m_matrixOriginal;
      pLocComponent->mtx.SetTranslation(loc);
    }
    if(oneTotemAwake)
      Abathur::setVolumeAudio(m_tottemAudio, 1.0f);
    else
      Abathur::setVolumeAudio(m_tottemAudio, 0.0f);
  }

  void CCentinels::SetSpeedSpeed(float delta)
  {
    m_speedFactor = delta;
  }

  void CCentinels::SetCentinelsStateInRoom(const std::string &name, CCentinels::EState state) {
    for (auto &c : m_centinels)
    {
      if (c.m_roomName == name) {
        c.m_state = state;
      }
    }
  }

  void CCentinels::RegisterCentinel(Abathur::TEntityId entity, const TCentinelsParams &params)
  {
    ASSERT(entity.IsValid());
    Abathur::TAbathurEntity *pTotemEntity = Abathur::GetEntity(entity);
    ASSERT(pTotemEntity);
    Abathur::TLocationComponent* pLocComponent = pTotemEntity->QueryComponent<Abathur::TLocationComponent>();

    TCentinel centinel;
    centinel.m_entity = entity;
    centinel.m_yaw = 0.0f;
    centinel.m_timeToTurn = 0.0f;
    centinel.m_matrixOriginal = pLocComponent->mtx;
    centinel.m_matrixOriginal.SetTranslation(Vector3(0.0f));
    centinel.m_state = EState::SLEEPING;
    centinel.m_roomName = params.m_roomName;
    centinel.m_turnSpeed = params.m_turnSpeed;
    centinel.m_timeFactorPlayer = params.m_timeFactorPlayer;
    m_centinels.push_back(centinel);

    if (m_centinels.size() == 1) { //hack, when register first centinel, we register update callback
      m_updateCallback.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PreRender, Abathur::EUpdateStage::Default));
      m_updateCallback.SetCallback(Abathur::TUpdateCallback::SetMethod<CCentinels, &CCentinels::Update>(this));
      m_updateCallback.Register();
      m_tottemAudio = Abathur::playAudio("data/audio/tottem_turn.wav", true);
      Abathur::setVolumeAudio(m_tottemAudio, 0.0f);
    }

  }


}

