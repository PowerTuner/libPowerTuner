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
#include <optional>

#include "../../../OS/Linux/CPUScalingAvailableGovernors.h"
#include "../../../OS/Linux/CPUFrequencyLimits.h"

namespace LIBPWT::LNX {
    struct LIBPWT_EXPORT LinuxThreadData final {
        std::optional<CPUScalingAvailableGovernors> scalingAvailableGovernors;
        std::optional<CPUFrequencyLimits> cpuFrequencyLimits;
        std::optional<bool> cpuLogicalOffAvailable;
        std::optional<int> coreID; // the core this thread belongs to
        std::optional<std::ranges::min_max_result<int>> cpuFrequency;
        std::optional<std::string> scalingGovernor;
        std::optional<int> cpuOnlineStatus;
    };
}
