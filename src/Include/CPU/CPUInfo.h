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

#include "../../lib_export.h"
#include "../../enums/CPUVendor.h"

namespace LIBPWT {
    struct LIBPWT_EXPORT CPUInfo final {
        CPUVendor vendor;
        std::string brand;
        std::string codename;
        std::string techNode;
        std::string CPUString;
        int model;
        int extModel;
        int family;
        int extFamily;
        int cores;
        int threads;
        int stepping;
        std::string l1DCache;
        std::string l1ICache;
        std::string l2Cache;
        std::string l3Cache;
        std::string l4Cache;
    };
}
