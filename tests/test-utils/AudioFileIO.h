/*  SPDX-License-Identifier: GPL-2.0-or-later */
/*!********************************************************************

  Audacity: A Digital Audio Editor

  AudioFileIO.h

  Matthieu Hodgkinson

**********************************************************************/
/*

 This file was copied from Audacity 3.5.1,
 https://github.com/audacity/audacity/releases/tag/Audacity-3.5.1.

 Modifications might have been made to remove dependencies on Audacity code and
 when renaming files. The algorithm remains the same.

EDIT: Commit "Simplify and improve algorithm by considering only 4/4" improves
quality of classifier and possibly time performance, too.

 */
#pragma once

#include "AudioFileInfo.h"

#include <chrono>
#include <optional>
#include <string>
#include <vector>

struct AudioFileIO
{
   static bool Read(
      const std::string& path, std::vector<std::vector<float>>& audio,
      AudioFileInfo& info,
      const std::optional<std::chrono::seconds>& upTo = std::nullopt);
};
