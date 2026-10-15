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

#include "../../../OS/Windows/PowerSchemeSettingData.h"
#include "../../../OS/Windows/PowerScheme.h"

namespace PWTS::WIN {
    struct PWTSHARED_EXPORT [[nodiscard]] WindowsData final {
        QMap<QString, PowerSchemeSettingData> schemeOptionsData;
        QMap<QString, PowerScheme> schemes;
        bool resetSchemesDefault = false;
        bool replaceDefaultSchemes = false;
        QString activeScheme;

        friend QDataStream &operator<<(QDataStream &ds, const WindowsData &data) {
            ds << data.schemeOptionsData <<
                data.schemes <<
                data.resetSchemesDefault <<
                data.replaceDefaultSchemes <<
                data.activeScheme;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, WindowsData &data) {
            ds >> data.schemeOptionsData >>
                data.schemes >>
                data.resetSchemesDefault >>
                data.replaceDefaultSchemes >>
                data.activeScheme;

            return ds;
        }
    };
}
