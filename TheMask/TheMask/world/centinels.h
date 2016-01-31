#pragma once

#include "abathur.h"
#include "utils/compileTime/compile_time_utils.h"

namespace World
{
	class CCentinels
	{
  public:
    enum class EState
    {
      SLEEPING,
      AWAKE
    };

  private:    

    struct TCentinel
    {
      Abathur::TEntityId m_entity;
      std::string m_roomName;
      Matrix44 m_matrixOriginal;
      float m_yaw;
      float m_speed;
      float m_timeToTurn;
      float m_timeFactorPlayer;
      EState m_state;
    };

    typedef std::vector<TCentinel> VCentinels;
    VCentinels m_centinels;
    float m_speedFactor;
    float m_timeInIdle;
    Abathur::CScopedUpdate m_updateCallback;
    Abathur::TAudioId      m_tottemAudio;

    void Update(const Abathur::SUpdateContext& context);

	public:
    CCentinels();
    void RegisterCentinel(Abathur::TEntityId entity, std::string room_name, float time_factor_player);
    void SetSpeedSpeed(float delta);
    void SetCentinelsStateInRoom(const std::string &name, CCentinels::EState state);
  };
}