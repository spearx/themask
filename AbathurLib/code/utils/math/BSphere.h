#pragma once

#include "Vector3.h"

namespace MathUtils
{
  struct BoundingSphere {

    Vector3f mCenter;
    float    mRadius;

    void Enlarge(const Vector3f &p) 
    {    
      Vector3f dir = p - mCenter;
      dir.Normalize();
      Vector3f FarPoint;
      FarPoint = mCenter + (-dir * mRadius); 
      dir = p - FarPoint;
      mRadius = dir.GetLength() / 2.0f;
      dir.Normalize();
      mCenter = FarPoint + dir * mRadius;
    }

    void Enlarge(const BoundingSphere &bs)
    {
      Vector3f dir = bs.mCenter - mCenter;
      float l = dir.GetLength() / 2.0f;
      dir.Normalize();
      mCenter = mCenter + dir * l;
      float r = bs.mRadius > mRadius ? bs.mRadius : mRadius;
      mRadius = r + l;
    }

    void Reset(const Vector3f &p)
    {
      mCenter = p;
      mRadius = 0.0f;
    }

  };

}

