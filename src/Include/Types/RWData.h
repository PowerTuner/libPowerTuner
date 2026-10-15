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
    class PWTSHARED_EXPORT [[nodiscard]] RWData final {
    private:
        bool valid = false;
        bool ignored = false;
        T value;

    public:
        RWData() = default;

        explicit RWData(const T &val, const bool isValid = false, const bool isIgnored = false): value(val) {
            valid = isValid;
            ignored = isIgnored;
        }

        [[nodiscard]] bool isValid() const { return valid; }
        [[nodiscard]] bool isIgnored() const { return ignored; }
        [[nodiscard]] T getValue() const { return value; }
        void setIgnored(const bool isIgnored) { ignored = isIgnored; }

        void setValue(const T &val, const bool isValid, const bool isIgnored = false) {
            value = val;
            valid = isValid;
            ignored = isIgnored;
        }

        friend QDataStream &operator<<(QDataStream &ds, const RWData &data) {
            ds << data.valid << data.ignored << data.value;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, RWData &data) {
            ds >> data.valid >> data.ignored >> data.value;

            return ds;
        }
    };
}
