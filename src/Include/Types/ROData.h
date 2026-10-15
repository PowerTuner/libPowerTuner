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

#include "../../sharedExport.h"

namespace PWTS {
    template<class T>
    class PWTSHARED_EXPORT [[nodiscard]] ROData final {
    private:
        bool valid = false;
        T value;

    public:
        ROData() = default;

        explicit ROData(const T &val, const bool isValid = false): value(val) {
            valid = isValid;
        }

        [[nodiscard]] bool isValid() const { return valid; }
        [[nodiscard]] T getValue() const { return value; }

        friend QDataStream &operator<<(QDataStream &ds, const ROData &data) {
            ds << data.valid << data.value;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, ROData &data) {
            ds >> data.valid >> data.value;

            return ds;
        }
    };
}
