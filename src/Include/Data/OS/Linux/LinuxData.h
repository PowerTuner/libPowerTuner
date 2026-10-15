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

#include <QMap>

#include "LinuxThreadData.h"
#include "LinuxIntelGPUData.h"
#include "LinuxAMDGPUData.h"
#include "../../../OS/Linux/BlockDeviceQueSched.h"
#include "../../../OS/Linux/MiscPMDevice.h"

namespace PWTS::LNX {
    struct PWTSHARED_EXPORT [[nodiscard]] LinuxData final {
        RWData<QString> smtState;
        ROData<QList<QString>> cpuIdleAvailableGovernors;
        RWData<QString> cpuIdleGovernor;
        QMap<QString, BlockDeviceQueSched> blockDevicesQueSched;
        QList<MiscPMDevice> miscPMDevices;
        QMap<int, LinuxIntelGPUData> intelGpuData;
        QMap<int, LinuxAMDGPUData> amdGpuData;

        // thread level
        QList<LinuxThreadData> threadData;

        friend QDataStream &operator<<(QDataStream &ds, const LinuxData &data) {
            ds << data.smtState <<
                data.cpuIdleAvailableGovernors <<
                data.cpuIdleGovernor <<
                data.blockDevicesQueSched <<
                data.miscPMDevices <<
                data.intelGpuData <<
                data.amdGpuData <<
                data.threadData;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, LinuxData &data) {
            ds >> data.smtState >>
                data.cpuIdleAvailableGovernors >>
                data.cpuIdleGovernor >>
                data.blockDevicesQueSched >>
                data.miscPMDevices >>
                data.intelGpuData >>
                data.amdGpuData >>
                data.threadData;

            return ds;
        }
    };
}
