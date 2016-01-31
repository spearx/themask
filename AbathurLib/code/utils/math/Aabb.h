#pragma once

#include "Vector3.h"

namespace MathUtils
{
  struct AABB {
    Vector3f mCenter;
    Vector3f mHalfSize;

    void Enlarge(const Vector3f &p) 
    {
      Vector3f pmin, pmax;
      GetMinMax(pmin, pmax);
      pmax.MaxBound(p);
      pmin.MinBound(p);
      SetMinMax(pmin, pmax);
    }

    void GetMinMax(Vector3f &pvmin, Vector3f &pvmax) const
    {
      pvmin = mCenter - mHalfSize;
      pvmax = mCenter + mHalfSize;
    }

    void SetMinMax(const Vector3f &vmin, const Vector3f &vmax)
    {
      mHalfSize = (vmax - vmin)*0.5f;
      mCenter = vmin + mHalfSize;
    }
  };

}

