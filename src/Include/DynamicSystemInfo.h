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

#include <QString>
#include <QDataStream>
#include <QList>

#include "../sharedExport.h"

namespace PWTS {
    struct PWTSHARED_EXPORT [[nodiscard]] DynamicSystemInfo final {
        QString swapMemory;
        QList<QString> cpuMicrocode;
        int onlineCPUCount;

        friend QDataStream &operator<<(QDataStream &ds, const DynamicSystemInfo &data) {
            ds << data.swapMemory <<
                data.cpuMicrocode <<
                data.onlineCPUCount;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, DynamicSystemInfo &data) {
            ds >> data.swapMemory >>
                data.cpuMicrocode >>
                data.onlineCPUCount;

            return ds;
        }
    };
}
