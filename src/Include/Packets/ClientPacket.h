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

#include "../PacketError.h"
#include "../Data/OS/Linux/LinuxData.h"
#include "../Data/OS/Linux/LinuxAMDData.h"
#include "../Data/OS/Windows/WindowsData.h"
#include "../Data/Vendor/Intel/IntelData.h"
#include "../Data/Vendor/AMD/AMDData.h"
#include "../Data/FAN/FanData.h"
#include "../OSType.h"
#include "../CPU/CPUVendor.h"

namespace PWTS {
    struct PWTSHARED_EXPORT [[nodiscard]] ClientPacket final {
        static constexpr int version = 1;
        PacketError error = PacketError::NoError;
        OSType os;
        CPUVendor vendor;
        QSharedPointer<LNX::LinuxData> linuxData;
        QSharedPointer<LNX::AMD::LinuxAMDData> linuxAmdData;
        QSharedPointer<WIN::WindowsData> windowsData;
        QSharedPointer<Intel::IntelData> intelData;
        QSharedPointer<AMD::AMDData> amdData;
        QMap<QString, FanData> fanData;

        friend QDataStream &operator<<(QDataStream &ds, const ClientPacket &data) {
            ds << version <<
                data.os <<
                data.vendor <<
                data.fanData;

            switch (data.os) {
                case OSType::Linux: {
                    const bool empty = data.linuxData.isNull();

                    ds << empty;
                    if (!empty)
                        ds << *data.linuxData;
                }
                    break;
                case OSType::Windows: {
                    const bool empty = data.windowsData.isNull();

                    ds << empty;
                    if (!empty)
                        ds << *data.windowsData;
                }
                    break;
                default:
                    break;
            }

            switch (data.vendor) {
                case CPUVendor::Intel: {
                    const bool empty = data.intelData.isNull();

                    ds << empty;
                    if (!empty)
                        ds << *data.intelData;
                }
                    break;
                case CPUVendor::AMD: {
                    const bool empty = data.amdData.isNull();

                    ds << empty;
                    if (!empty)
                        ds << *data.amdData;

                    switch (data.os) {
                        case OSType::Linux: {
                            const bool laEmpty = data.linuxAmdData.isNull();

                            ds << laEmpty;
                            if (!laEmpty)
                                ds << *data.linuxAmdData;
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

        friend QDataStream &operator>>(QDataStream &ds, ClientPacket &data) {
            int dataVersion;

            ds >> dataVersion;
            if (dataVersion != version) {
                data.error = PacketError::VersionMismatch;
                return ds;
            }

            ds >> data.os >>
                data.vendor >>
                data.fanData;

            switch (data.os) {
                case OSType::Linux: {
                    bool empty;

                    ds >> empty;
                    if (empty)
                        break;

                    if (data.linuxData.isNull())
                        data.linuxData = QSharedPointer<LNX::LinuxData>::create();

                    ds >> *data.linuxData;
                }
                    break;
                case OSType::Windows: {
                    bool empty;

                    ds >> empty;
                    if (empty)
                        break;

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
                    bool empty;

                    ds >> empty;
                    if (empty)
                        break;

                    if (data.intelData.isNull())
                        data.intelData = QSharedPointer<Intel::IntelData>::create();

                    ds >> *data.intelData;
                }
                    break;
                case CPUVendor::AMD: {
                    bool empty;

                    ds >> empty;
                    if (empty)
                        break;

                    if (data.amdData.isNull())
                        data.amdData = QSharedPointer<AMD::AMDData>::create();

                    ds >> *data.amdData;

                    switch (data.os) {
                        case OSType::Linux: {
                            bool laEmpty;

                            ds >> laEmpty;
                            if (laEmpty)
                                break;

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
Q_DECLARE_METATYPE(PWTS::ClientPacket)
