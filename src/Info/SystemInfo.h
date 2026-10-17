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
#include <string>
#include <vector>

#include "../lib_export.h"
#include "../enums/OSType.h"

namespace LIBPWT {
    struct LIBPWT_EXPORT SystemInfo final {
        OSType osType;
        std::string distribution;
        std::string kernel;
        std::string arch;
        std::string biosVersion;
        std::string biosVendor;
        std::string biosDate;
        std::string ecVersion;
        std::string product;
        std::string manufacturer;
        std::string availableRam;
        std::string swapMemory;
        std::vector<std::string> cpuMicrocode;
    };
}
