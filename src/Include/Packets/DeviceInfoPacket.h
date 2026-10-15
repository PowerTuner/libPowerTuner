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

#include <QMetaType>

#include "../PacketError.h"
#include "../SystemInfo.h"
#include "../DynamicSystemInfo.h"
#include "../CPU/CpuInfo.h"
#include "../GPU/GpuInfo.h"
#include "../Features.h"

namespace PWTS {
    struct PWTSHARED_EXPORT [[nodiscard]] DeviceInfoPacket final {
        static constexpr int version = 1;
        PacketError error = PacketError::NoError;
        int daemonMajorVersion = 0;
        int daemonMinorVersion = 0;
        int daemonPwtsMajorVersion = 0;
        int daemonPwtsMinorVersion = 0;
        QString daemonDataPath;
        QByteArray daemonSettings;
        SystemInfo sysInfo;
        DynamicSystemInfo dynSysInfo;
        CpuInfo cpuInfo;
        QMap<int, GpuInfo> gpusInfo;
        QMap<QString, QString> fanLabels;
        Features features;

        friend QDataStream &operator<<(QDataStream &ds, const DeviceInfoPacket &data) {
            ds << version <<
                data.daemonMajorVersion <<
                data.daemonMinorVersion <<
                data.daemonPwtsMajorVersion <<
                data.daemonPwtsMinorVersion <<
                data.daemonDataPath <<
                data.daemonSettings <<
                data.sysInfo <<
                data.dynSysInfo <<
                data.cpuInfo <<
                data.gpusInfo <<
                data.fanLabels <<
                data.features;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, DeviceInfoPacket &data) {
            int dataVersion;

            ds >> dataVersion;
            if (dataVersion != version) {
                data.error = PacketError::VersionMismatch;
                return ds;
            }

            ds >> data.daemonMajorVersion >>
                data.daemonMinorVersion >>
                data.daemonPwtsMajorVersion >>
                data.daemonPwtsMinorVersion >>
                data.daemonDataPath >>
                data.daemonSettings >>
                data.sysInfo >>
                data.dynSysInfo >>
                data.cpuInfo >>
                data.gpusInfo >>
                data.fanLabels >>
                data.features;

            return ds;
        }
    };
}
Q_DECLARE_METATYPE(PWTS::DeviceInfoPacket)
