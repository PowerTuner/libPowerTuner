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
#include <QSharedPointer>
#include <QSet>

#include "../PacketError.h"
#include "../OSType.h"
#include "../CPU/CPUVendor.h"
#include "../DaemonError.h"
#include "../DynamicSystemInfo.h"
#include "../Data/OS/Linux/LinuxData.h"
#include "../Data/OS/Linux/LinuxAMDData.h"
#include "../Data/OS/Windows/WindowsData.h"
#include "../Data/Vendor/Intel/IntelData.h"
#include "../Data/Vendor/AMD/AMDData.h"
#include "../Data/FAN/FanData.h"

namespace PWTS {
    struct PWTSHARED_EXPORT [[nodiscard]] DaemonPacket final {
        static constexpr int version = 2;
        PacketError error = PacketError::NoError;
        bool hasProfileData = false;
        OSType os;
        CPUVendor vendor;
        QSet<DError> errors;
        DynamicSystemInfo dynSysInfo;
        QList<QString> profilesList;
        QString activeProfile;
        QSharedPointer<LNX::LinuxData> linuxData;
        QSharedPointer<LNX::AMD::LinuxAMDData> linuxAmdData;
        QSharedPointer<WIN::WindowsData> windowsData;
        QSharedPointer<AMD::AMDData> amdData;
        QSharedPointer<Intel::IntelData> intelData;
        QMap<QString, FanData> fanData;

        friend QDataStream &operator<<(QDataStream &ds, const DaemonPacket &data) {
            ds << version <<
                data.hasProfileData <<
                data.os <<
                data.vendor <<
                data.errors <<
                data.dynSysInfo <<
                data.profilesList <<
                data.activeProfile <<
                data.fanData;

            switch (data.os) {
                case OSType::Linux:
                    ds << *data.linuxData;
                    break;
                case OSType::Windows:
                    ds << *data.windowsData;
                    break;
                default:
                    break;
            }

            switch (data.vendor) {
                case CPUVendor::Intel:
                    ds << *data.intelData;
                    break;
                case CPUVendor::AMD: {
                    ds << *data.amdData;

                    switch (data.os) {
                        case OSType::Linux:
                            ds << *data.linuxAmdData;
                            break;
                        default:
                            break;
                    }
                }
                    break;
                default:
                    break;
            }

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, DaemonPacket &data) {
            int dataVersion;

            ds >> dataVersion;
            if (dataVersion != version) {
                data.error = PacketError::VersionMismatch;
                return ds;
            }

            ds >> data.hasProfileData >>
                data.os >>
                data.vendor >>
                data.errors >>
                data.dynSysInfo >>
                data.profilesList >>
                data.activeProfile >>
                data.fanData;

            switch (data.os) {
                case OSType::Linux: {
                    if (data.linuxData.isNull())
                        data.linuxData = QSharedPointer<LNX::LinuxData>::create();

                    ds >> *data.linuxData;
                }
                    break;
                case OSType::Windows: {
                    if (data.windowsData.isNull())
                        data.windowsData = QSharedPointer<WIN::WindowsData>::create();

                    ds >> *data.windowsData;
                }
                    break;
                default:
                    break;
            }

            switch (data.vendor) {
                case CPUVendor::Intel: {
                    if (data.intelData.isNull())
                        data.intelData = QSharedPointer<Intel::IntelData>::create();

                    ds >> *data.intelData;
                }
                    break;
                case CPUVendor::AMD: {
                    if (data.amdData.isNull())
                        data.amdData = QSharedPointer<AMD::AMDData>::create();

                    ds >> *data.amdData;

                    switch (data.os) {
                        case OSType::Linux: {
                            if (data.linuxAmdData.isNull())
                                data.linuxAmdData = QSharedPointer<LNX::AMD::LinuxAMDData>::create();

                            ds >> *data.linuxAmdData;
                        }
                            break;
                        default:
                            break;
                    }
                }
                    break;
                default:
                    break;
            }

            return ds;
        }
    };
}
Q_DECLARE_METATYPE(PWTS::DaemonPacket)
