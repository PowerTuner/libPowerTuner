/*
 * This file is part of PWTShared.
 * Copyright (C) 2025 kylon
 *
 * PWTShared is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PWTShared is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "../../../Types/ROData.h"
#include "../../../Types/RWData.h"
#include "../../../CPU/Intel/HWPCapabilities.h"
#include "../../../CPU/Intel/HWPRequest.h"

namespace PWTS::Intel {
    struct PWTSHARED_EXPORT [[nodiscard]] IntelThreadData final {
        ROData<HWPCapabilities> hwpCapapabilities;
        RWData<HWPRequest> hwpRequest;

        friend QDataStream &operator<<(QDataStream &ds, const IntelThreadData &data) {
            ds << data.hwpCapapabilities <<
                data.hwpRequest;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, IntelThreadData &data) {
            ds >> data.hwpCapapabilities >>
                data.hwpRequest;

            return ds;
        }
    };
}
