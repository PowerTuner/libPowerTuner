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
#include "LinuxThreadData.h"
#include "IntelGPUData.h"
#include "AMDGPUData.h"
#include "../../../OS/Linux/BlockDeviceQueueScheduler.h"
#include "../../../OS/Linux/MiscPMDevice.h"

namespace LIBPWT::LNX {
    struct LIBPWT_EXPORT LinuxData final {
        std::optional<std::string> smtState;
        std::optional<std::vector<std::string>> cpuIdleAvailableGovernors;
        std::optional<std::string> cpuIdleGovernor;
        std::unordered_map<std::string, BlockDeviceQueueScheduler> blockDevicesQueSched;
        std::vector<MiscPMDevice> miscPMDevices;
        std::unordered_map<int, Intel::LNX::IntelGPUData> intelGpuData;
        std::unordered_map<int, AMD::LNX::AMDGPUData> amdGpuData;

        // thread level
        std::vector<LinuxThreadData> threadData;
    };
}
