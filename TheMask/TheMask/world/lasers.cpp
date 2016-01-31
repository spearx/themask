#include "lasers.h"

namespace World
{

  CLasers::CLasers()
  {

  }
  
  CLasers::TLaserData *CLasers::RegistreTypeLaser(ELaserType laser_type, Abathur::TEntityId collision_mesh)
  {
    ASSERT(collision_mesh.IsValid());
    TLaserData data;
    data.mType = laser_type;
    data.mCollisionMesh = collision_mesh;
    lasers.push_back(data);
    return &lasers.back();
  }

  void CLasers::EnableTypeLaser(ELaserType laser_type)
  {
    for (auto &l : lasers)
    {
      if (laser_type == l.mType) {
        Abathur::TAbathurEntity *e = Abathur::GetEntity(l.mCollisionMesh);
        Abathur::TPhysXComponent *phyx_comp = e->QueryComponent<Abathur::TPhysXComponent>();
        phyx_comp->SetEnabled(true);
      }
    }
  }

  void CLasers::DisableTypeLaser(ELaserType laser_type, bool exclusive)
  {
    for (auto &l : lasers) 
    {
      if (laser_type == l.mType) {
        Abathur::TAbathurEntity *e = Abathur::GetEntity(l.mCollisionMesh);
        Abathur::TPhysXComponent *phyx_comp = e->QueryComponent<Abathur::TPhysXComponent>();
        phyx_comp->SetEnabled(false);
      }
      else if (exclusive) {
        Abathur::TAbathurEntity *e = Abathur::GetEntity(l.mCollisionMesh);
        Abathur::TPhysXComponent *phyx_comp = e->QueryComponent<Abathur::TPhysXComponent>();
        phyx_comp->SetEnabled(true);
      }
    }
  }

  void CLasers::Render()
  {
    for (auto &l : lasers)
    {
      Abathur::TAbathurEntity *e = Abathur::GetEntity(l.mCollisionMesh);
      Abathur::TPhysXComponent *phyx_comp = e->QueryComponent<Abathur::TPhysXComponent>();
      if (phyx_comp->mEnabled) {
        unsigned color = 0xffffffff;
        if (l.mType == ELaserType::RED_LASER)
          color = COLOR_ARGB(0xff, 0xff, 0x0, 0x0);
        else if (l.mType == ELaserType::GREEN_LASER)
          color = COLOR_ARGB(0xff, 0x0, 0xff, 0x0);
        else if (l.mType == ELaserType::BLUE_LASER)
          color = COLOR_ARGB(0xff, 0x0, 0x0, 0xff);

        for (auto &r : l.mRays)
        {
          Abathur::TAbathurEntity *src = Abathur::GetEntity(r.mSource);
          Abathur::TLocationComponent *src_loc = src->QueryComponent<Abathur::TLocationComponent>();
          Abathur::TAbathurEntity *tgt = Abathur::GetEntity(r.mTarget);
          Abathur::TLocationComponent *tgt_loc = tgt->QueryComponent<Abathur::TLocationComponent>();
          Vector3 src_pos = src_loc->mtx.GetTranslation();
          Vector3 tgt_pos = tgt_loc->mtx.GetTranslation();
          Abathur::drawLine(src_pos, tgt_pos, color);
        }
      }
    }
  }

  void CLasers::TLaserData::AddRayLaser(Abathur::TEntityId src, Abathur::TEntityId tgt)
  {
    TLaserRay ray;
    ray.mSource = src;
    ray.mTarget = tgt;
    mRays.push_back(ray);
  }


}

