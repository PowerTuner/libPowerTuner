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

#include <QDataStream>
#include <QString>

#include "../../../sharedExport.h"

namespace PWTS::LNX {
    struct PWTSHARED_EXPORT [[nodiscard]] MiscPMDevice final {
        QString name;
        QString control;
        QString controlValue;

        friend QDataStream &operator<<(QDataStream &ds, const MiscPMDevice &data) {
            ds << data.name <<
                data.control <<
                data.controlValue;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, MiscPMDevice &data) {
            ds >> data.name >>
                data.control >>
                data.controlValue;

            return ds;
        }
    };
}
