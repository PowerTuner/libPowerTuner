/*
 * This file is part of libPowerTuner.
 * Copyright (C) 2026 kylon
 *
 * libPowerTuner is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libPowerTuner is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <QIODevice>
#include <QHostAddress>
#include <QJsonObject>

#include "Include/DaemonError.h"
#include "Include/Packets/DeviceInfoPacket.h"

namespace PWTS {
    [[nodiscard]] LIBPWT_EXPORT bool isValidPort(quint16 port);
    [[nodiscard]] LIBPWT_EXPORT QByteArray loadFile(const QString &path);
    [[nodiscard]] LIBPWT_EXPORT bool writeFile(const QString &path, const QByteArray &data);
    [[nodiscard]] LIBPWT_EXPORT bool isValidProfileForImport(const QString &profile);
    [[nodiscard]] LIBPWT_EXPORT QString getErrorStr(DError e);
    [[nodiscard]] LIBPWT_EXPORT QString getPacketErrorStr(PacketError e);
    [[nodiscard]] LIBPWT_EXPORT QHostAddress getHostAddress(const QString &adr);
    [[nodiscard]] LIBPWT_EXPORT QString featureToString(Feature feat);
    [[nodiscard]] LIBPWT_EXPORT QString GPUVendorToString(GPUVendor vnd);
    [[nodiscard]] LIBPWT_EXPORT QJsonObject getDeviceInfoJson(const DeviceInfoPacket &packet);

    template<class T>
    [[nodiscard]]
    bool unpackData(const QByteArray &data, T &out) {
        if (data.isEmpty())
            return false;

        QByteArray ba = data;
        QDataStream ds(&ba, QIODevice::ReadOnly);

        ds.startTransaction();
        ds >> out;

        return ds.commitTransaction() && ds.status() == QDataStream::Ok;
    }

    template<class T>
    [[nodiscard]]
    bool packData(const T &data, QByteArray &out) {
        QDataStream ds(&out, QIODevice::WriteOnly);

        ds.startTransaction();
        ds << data;

        return ds.commitTransaction() && ds.status() == QDataStream::Ok;
    }
}
