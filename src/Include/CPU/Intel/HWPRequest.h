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

#include "HWPRequestPkg.h"

namespace PWTS::Intel {
    struct PWTSHARED_EXPORT [[nodiscard]] HWPRequest final {
        HWPRequestPkg requestPkg;
        bool packageControl;
        bool acwValid;
        bool eppValid;
        bool desiredValid;
        bool maxValid;
        bool minValid;

        friend QDataStream &operator<<(QDataStream &ds, const HWPRequest &data) {
            ds << data.requestPkg <<
                data.packageControl <<
                data.acwValid <<
                data.eppValid <<
                data.desiredValid <<
                data.maxValid <<
                data.minValid;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, HWPRequest &data) {
            ds >> data.requestPkg >>
                data.packageControl >>
                data.acwValid >>
                data.eppValid >>
                data.desiredValid >>
                data.maxValid >>
                data.minValid;

            return ds;
        }
    };
}
