/*
 * This file is part of libPowerTuner.
 * Copyright (C) 2026 kylon
 *
 * libPowerTuner is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libPowerTuner is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "CoreData.h"
#include "ThreadData.h"
#include "../../../CPU/AMD/PStateCurrentLimit.h"

namespace LIBPWT::AMD {
    struct LIBPWT_EXPORT AMDData final {
        // package level
        std::optional<PStateCurrentLimit> pstateCurrentLimit;
        std::optional<int> stapmLimit;
        std::optional<int> fastLimit;
        std::optional<int> slowLimit;
        std::optional<int> tctlTemp;
        std::optional<int> apuSlow;
        std::optional<int> apuSkinTemp;
        std::optional<int> dgpuSkinTemp;
        std::optional<int> curveOptimizer;
        std::optional<int> vrmCurrent;
        std::optional<int> vrmSocCurrent;
        std::optional<int> vrmMaxCurrent;
        std::optional<int> vrmSocMaxCurrent;
        std::optional<int> staticGfxClock;
        std::optional<int> minGfxClock;
        std::optional<int> maxGfxClock;
        std::optional<int> powerProfile;
        std::optional<int> cppcEnableBit;

        // core level
        std::vector<CoreData> coreData;

        // thread level
        std::vector<ThreadData> threadData;
    };
}
