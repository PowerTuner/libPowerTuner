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
    struct PWTSHARED_EXPORT [[nodiscard]] PkgCstConfigControl final {
        short packageCStateLimit;
        short maxCoreCState;
        bool ioMwaitRedirectionEnable;
        bool cfgLock;
        bool c3StateAutodemotionEnable;
        bool c1StateAutodemotionEnable;
        bool c3UndemotionEnable;
        bool c1UndemotionEnable;
        bool pkgcAutodemotionEnable;
        bool pkgcUndemotionEnable;
        bool timedMwaitEnable;

        friend QDataStream &operator<<(QDataStream &ds, const PkgCstConfigControl &data) {
            ds << data.packageCStateLimit <<
                data.maxCoreCState <<
                data.ioMwaitRedirectionEnable <<
                data.cfgLock <<
                data.c3StateAutodemotionEnable <<
                data.c1StateAutodemotionEnable <<
                data.c3UndemotionEnable <<
                data.c1UndemotionEnable <<
                data.pkgcAutodemotionEnable <<
                data.pkgcUndemotionEnable <<
                data.timedMwaitEnable;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, PkgCstConfigControl &data) {
            ds >> data.packageCStateLimit >>
                data.maxCoreCState >>
                data.ioMwaitRedirectionEnable >>
                data.cfgLock >>
                data.c3StateAutodemotionEnable >>
                data.c1StateAutodemotionEnable >>
                data.c3UndemotionEnable >>
                data.c1UndemotionEnable >>
                data.pkgcAutodemotionEnable >>
                data.pkgcUndemotionEnable >>
                data.timedMwaitEnable;

            return ds;
        }
    };
}
