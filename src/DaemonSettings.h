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

#include <QHostAddress>

#include "lib_export.h"
#include "Include/LogLevel.h"

namespace PWTS {
    class LIBPWT_EXPORT DaemonSettings final {
    public:
        static constexpr quint16 DefaultTCPPort = 56000;
        static constexpr quint16 DefaultUDPPort = 56001;
        static constexpr int MinApplyInterval = 0;
        static constexpr int MaxApplyInterval = 1800;

    private:
        struct DData final {
            QString startProfile;
            QString batteryProfile;
            QString powerSupplyProfile;
            QString address = QHostAddress(QHostAddress::Any).toString();
            int applyInterval = 0;
            bool applyOnWakeFromSleep = false;
            bool ignoreBatteryEvent = false;
            LogLevel logLvl = LogLevel::Info;
            quint16 tcpPort = DefaultTCPPort;
            quint16 udpPort = DefaultUDPPort;
        };

        static constexpr int version = 1;
        DData _data;

        friend QDataStream &operator<<(QDataStream &ds, const DData &ddata);
        friend QDataStream &operator>>(QDataStream &ds, DData &ddata);

        [[nodiscard]] bool isValidInterval(const int interval) const { return interval >= MinApplyInterval && interval < MaxApplyInterval; }

        void validate();

    public:
        [[nodiscard]] QString getOnStartProfile() const { return _data.startProfile; }
        [[nodiscard]] QString getOnBatteryProfile() const { return _data.batteryProfile; }
        [[nodiscard]] QString getOnPowerSupplyProfile() const { return _data.powerSupplyProfile; }
        [[nodiscard]] QString getAddress() const { return _data.address; }
        [[nodiscard]] int getApplyInterval() const { return _data.applyInterval; }
        [[nodiscard]] quint16 getSocketTcpPort() const { return _data.tcpPort; }
        [[nodiscard]] quint16 getSocketUdpPort() const { return _data.udpPort; }
        [[nodiscard]] bool getApplyOnWakeFromSleep() const { return _data.applyOnWakeFromSleep; }
        [[nodiscard]] bool getIgnoreBatteryEvent() const { return _data.ignoreBatteryEvent; }
        [[nodiscard]] LogLevel getLogLevel() const { return _data.logLvl; }
        void setOnStartProfile(const QString &profile) { _data.startProfile = profile; }
        void setOnBatteryProfile(const QString &profile) { _data.batteryProfile = profile; }
        void setOnPowerSupplyProfile(const QString &profile) { _data.powerSupplyProfile = profile; }
        void setApplyOnWakeFromSleep(const bool enable) { _data.applyOnWakeFromSleep = enable; }
        void setIgnoreBatteryEvent(const bool enable) { _data.ignoreBatteryEvent = enable; }
        void setLogLevel(const LogLevel lvl) { _data.logLvl = lvl; }

        void setApplyInterval(int interval);
        void setAddress(const QString &adr);
        void setSocketTcpPort(quint16 port);
        void setSocketUdpPort(quint16 port);
        [[nodiscard]] QByteArray getData() const;
        [[nodiscard]] bool load(const QByteArray &data);
    };
}
