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

namespace PWTS {
    enum struct DCMD: int {
        PRINT_ERROR = 0,
        DAEMON_CMD_FAIL,
        GET_DEVICE_INFO_PACKET,
        GET_DAEMON_PACKET,
        APPLY_CLIENT_SETTINGS,
        GET_DAEMON_SETTS,
        APPLY_DAEMON_SETT,
        GET_PROFILE_LIST,
        DELETE_PROFILE,
        WRITE_PROFILE,
        LOAD_PROFILE,
        APPLY_PROFILE,
        EXPORT_PROFILES,
        IMPORT_PROFILES,
        BATTERY_STATUS_CHANGED,
        SYS_WAKE_FROM_SLEEP,
        APPLY_TIMER
    };
}
