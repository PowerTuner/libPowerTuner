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
#include "enums/CPUVendor.h"
#include "enums/Error.h"
#include "enums/OSType.h"
#include "Info/DaemonInfo.h"
#include "Info/CPUInfo.h"
#include "Info/GPUInfo.h"
#include "Info/SystemInfo.h"
#include "FAN/Fan.h"
#include "OS/Linux/SysFs.h"
#include "Vendor/AMD/MSR.h"
#include "Vendor/Intel/MSR.h"

namespace LIBPWT {
    struct LIBPWT_EXPORT DeviceData final {
        OSType os;
        CPUVendor cpu;
        std::optional<DaemonInfo> daemonInfo;
        std::optional<SystemInfo> systemInfo;
        std::optional<CPUInfo> cpuInfo;
        std::vector<GPUInfo> gpusInfo;
        std::optional<LNX::SysFs> linuxSysFs;
        std::optional<AMD::MSR> amdMsr;
        std::optional<Intel::MSR> intelMsr;
        std::vector<FAN::Fan> fans;
        std::vector<std::string> profiles;
        std::vector<Error> errors;
    };
}