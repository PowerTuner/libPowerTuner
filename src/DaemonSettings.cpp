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
#include "DaemonSettings.h"
#include "Utils.h"

namespace PWTS {
    QByteArray DaemonSettings::getData() const {
        QByteArray data;

        if (!packData<DData>(_data, data))
            return {};

        return data;
    }

    bool DaemonSettings::load(const QByteArray &data) {
        DData ddata;

        if (!unpackData<DData>(data, ddata))
            return false;

        _data = ddata;

        validate();
        return true;
    }

    void DaemonSettings::validate() {
        if (!isValidInterval(_data.applyInterval))
            _data.applyInterval = 0;

        if (QHostAddress(_data.address).isNull())
            _data.address = QHostAddress(QHostAddress::Any).toString();

        if (!isValidPort(_data.tcpPort))
            _data.tcpPort = DefaultTCPPort;

        if (!isValidPort(_data.udpPort))
            _data.udpPort = DefaultUDPPort;
    }

    void DaemonSettings::setApplyInterval(const int interval) {
        if (isValidInterval(interval))
            _data.applyInterval = interval;
    }

    void DaemonSettings::setAddress(const QString &adr) {
        const QHostAddress _adr = getHostAddress(adr);

        if (!_adr.isNull())
            _data.address = _adr.toString();
    }

    void DaemonSettings::setSocketTcpPort(const quint16 port) {
        if (isValidPort(port))
            _data.tcpPort = port;
    }

    void DaemonSettings::setSocketUdpPort(const quint16 port) {
        if (isValidPort(port))
            _data.udpPort = port;
    }

    QDataStream &operator<<(QDataStream &ds, const DaemonSettings::DData &ddata) {
        ds << DaemonSettings::version <<
            ddata.startProfile <<
            ddata.batteryProfile <<
            ddata.powerSupplyProfile <<
            ddata.applyInterval <<
            ddata.applyOnWakeFromSleep <<
            ddata.ignoreBatteryEvent <<
            ddata.logLvl <<
            ddata.address <<
            ddata.tcpPort <<
            ddata.udpPort;

        return ds;
    }

    QDataStream &operator>>(QDataStream &ds, DaemonSettings::DData &ddata) {
        int version;

        ds >> version;

        ds >> ddata.startProfile >>
            ddata.batteryProfile >>
            ddata.powerSupplyProfile >>
            ddata.applyInterval >>
            ddata.applyOnWakeFromSleep >>
            ddata.ignoreBatteryEvent >>
            ddata.logLvl >>
            ddata.address >>
            ddata.tcpPort >>
            ddata.udpPort;

        return ds;
    }
}
