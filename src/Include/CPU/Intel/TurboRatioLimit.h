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

#include "../../../sharedExport.h"

namespace PWTS::Intel {
    struct PWTSHARED_EXPORT [[nodiscard]] TurboRatioLimit final {
        int maxRatioLimit1C;
        int maxRatioLimit2C;
        int maxRatioLimit3C;
        int maxRatioLimit4C;
        int maxRatioLimit5C;
        int maxRatioLimit6C;
        int maxRatioLimit7C;
        int maxRatioLimit8C;

        friend QDataStream &operator<<(QDataStream &ds, const TurboRatioLimit &data) {
            ds << data.maxRatioLimit1C <<
                data.maxRatioLimit2C <<
                data.maxRatioLimit3C <<
                data.maxRatioLimit4C <<
                data.maxRatioLimit5C <<
                data.maxRatioLimit6C <<
                data.maxRatioLimit7C <<
                data.maxRatioLimit8C;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, TurboRatioLimit &data) {
            ds >> data.maxRatioLimit1C >>
                data.maxRatioLimit2C >>
                data.maxRatioLimit3C >>
                data.maxRatioLimit4C >>
                data.maxRatioLimit5C >>
                data.maxRatioLimit6C >>
                data.maxRatioLimit7C >>
                data.maxRatioLimit8C;

            return ds;
        }
    };
}
