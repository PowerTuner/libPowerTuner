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

#include <QDataStream>

#include "../../../sharedExport.h"

namespace PWTS::Intel {
    struct PWTSHARED_EXPORT [[nodiscard]] MCHBARPkgRaplLimit final {
        int pl1;
        int pl2;
        int pl1Time;
        bool pl1Clamp;
        bool pl1Enable;
        bool pl2Enable;
        bool lock;

        friend QDataStream &operator<<(QDataStream &ds, const MCHBARPkgRaplLimit &data) {
            ds << data.pl1 <<
                data.pl2 <<
                data.pl1Time <<
                data.pl1Clamp <<
                data.pl1Enable <<
                data.pl2Enable <<
                data.lock;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, MCHBARPkgRaplLimit &data) {
            ds >> data.pl1 >>
                data.pl2 >>
                data.pl1Time >>
                data.pl1Clamp >>
                data.pl1Enable >>
                data.pl2Enable >>
                data.lock;

            return ds;
        }
    };
}
