#pragma once

#include "utils/compileTime/compile_time_utils.h"

namespace Abathur
{
  WRAP_TYPE(uint32, TAudioId, 0u);
  
  TAudioId playAudio(const char *filename, bool loop);
  void stopAudio(TAudioId audioID);
  void pauseAudio(TAudioId audioID, bool pause);
  void setVolumeAudio(TAudioId audioID, float vol);
  bool isPlaying(TAudioId audioID);

};

