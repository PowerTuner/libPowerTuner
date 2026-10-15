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

#include "../../../Types/ROData.h"
#include "../../../Types/RWData.h"
#include "../../../OS/Linux/CPUScalingAvailableGovernors.h"
#include "../../../OS/Linux/CPUFrequencyLimits.h"

namespace PWTS::LNX {
    struct PWTSHARED_EXPORT [[nodiscard]] LinuxThreadData final {
        ROData<CPUScalingAvailableGovernors> scalingAvailableGovernors;
        ROData<CPUFrequencyLimits> cpuFrequencyLimits;
        ROData<bool> cpuLogicalOffAvailable;
        ROData<int> coreID; // the core this thread belongs to
        RWData<MinMax> cpuFrequency;
        RWData<QString> scalingGovernor;
        RWData<int> cpuOnlineStatus;

        friend QDataStream &operator<<(QDataStream &ds, const LinuxThreadData &data) {
            ds << data.scalingAvailableGovernors <<
                data.cpuFrequencyLimits <<
                data.cpuLogicalOffAvailable <<
                data.coreID <<
                data.cpuFrequency <<
                data.scalingGovernor <<
                data.cpuOnlineStatus;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, LinuxThreadData &data) {
            ds >> data.scalingAvailableGovernors >>
                data.cpuFrequencyLimits >>
                data.cpuLogicalOffAvailable >>
                data.coreID >>
                data.cpuFrequency >>
                data.scalingGovernor >>
                data.cpuOnlineStatus;

            return ds;
        }
    };
}
