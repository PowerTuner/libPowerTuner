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
#include <unordered_map>

#include "CPUSysFs.h"
#include "Includes/BlockDeviceQueueScheduler.h"
#include "Includes/MiscPMDevice.h"
#include "Includes/IntelGPU.h"
#include "Includes/AMDGPU.h"

namespace LIBPWT::LNX {
    struct LIBPWT_EXPORT SysFs final {
        std::vector<CPUSysFs> cpus;
        std::unordered_map<int, Intel::LNX::IntelGPU> intelGPUs;
        std::unordered_map<int, AMD::LNX::AMDGPU> amdGPUs;
        std::optional<std::string> smtControl;
        std::vector<std::string> cpuIdleAvailableGovernors;
        std::optional<std::string> cpuIdleCurrentGovernor;
        std::vector<BlockDeviceQueueScheduler> blockDevicesQueScheduler;
        std::vector<MiscPMDevice> miscPMDevices;

        // amd cpu
        std::optional<std::string> amdPStateStatus;

        // intel cpu
        std::optional<int> intelPStateMaxPerfPct;
        std::optional<int> intelPStateMinPerfPct;
    };
}
