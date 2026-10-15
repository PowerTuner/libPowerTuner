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

#include "LinuxAMDThreadData.h"

namespace PWTS::LNX::AMD {
    struct PWTSHARED_EXPORT [[nodiscard]] LinuxAMDData final {
        // package level
        RWData<QString> pstateStatus;

        // thread level
        QList<LinuxAMDThreadData> threadData;

        friend QDataStream &operator<<(QDataStream &ds, const LinuxAMDData &data) {
            ds << data.pstateStatus <<
                data.threadData;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, LinuxAMDData &data) {
            ds >> data.pstateStatus >>
                data.threadData;

            return ds;
        }
    };
}
