#pragma once

#include "abathur.h"
#include "utils/compileTime/compile_time_utils.h"

namespace World
{
	class CLasers
	{
  public:
    enum class ELaserType {
      RED_LASER,
      BLUE_LASER,
      GREEN_LASER
    };

    struct TLaserRay {
      Abathur::TEntityId mSource;
      Abathur::TEntityId mTarget;
    };
    typedef std::vector<TLaserRay> VLaserRays;

    struct TLaserData
    {
      ELaserType mType;
      Abathur::TEntityId mCollisionMesh;
      VLaserRays mRays;
      void AddRayLaser(Abathur::TEntityId src, Abathur::TEntityId tgt);
    };

  private:   
    typedef std::vector<TLaserData> VLaserData;
    VLaserData lasers;

	public:

    CLasers();
    TLaserData *RegistreTypeLaser(ELaserType laser_type, Abathur::TEntityId collision_mesh );
    void EnableTypeLaser(ELaserType laser_type);
    void DisableTypeLaser(ELaserType laser_type, bool exclusive);
    void Render();

  };
}