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

#include "../../../CPU/AMD/CPPCCapability1.h"
#include "../../../CPU/AMD/CPPCRequest.h"

namespace LIBPWT::AMD {
    struct LIBPWT_EXPORT ThreadData final {
        std::optional<CPPCCapability1> cppcCapability1;
        std::optional<CPPCRequest> cppcRequest;
        std::optional<int> corePerfBoost;
        std::optional<int> pstateCmd;
    };
}
