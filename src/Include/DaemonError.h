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
    enum struct DError: int {
    	CORE_DATA_MISMATCH,
    	THREAD_DATA_MISMATCH,
    	CORE_IDX_MISMATCH,
        CORRUPTED_DATA,
    	INVALID_PACKET,
    	INVALID_DCMD,
    	INVALID_ARGS,
    	PROFILE_LOAD_FAILED,
    	OS_ACCESS_FAIL,

		// linux
        NO_MSR_FD,
        W_CPUS_ONLINE,
    	W_CPU_SMT,
        W_CPU_SCALING_GOV,
        W_CPU_FREQ_MIN_MAX,
    	W_CPU_IDLE_GOV,
    	W_BLOCK_DEVICES,
        W_MISC_PM_DEVICES,

		// windows
		W_PWR_SCHEME,
        W_PWR_ACTIVE_SCHEME,
        W_PWR_DELETE_SCHEMES,
    	W_PWR_RESET_INDIVIDUAL_DEFAULT,
        W_PWR_CREATE_SCHEMES,
        W_PWR_RESET_SCHEMES_DEFAULT,
        W_PWR_REPLACE_WIN_DEFAULT_SCHEMES,
        W_PWR_NO_SCHEME_ACCESS,

    	// intel
        W_PKG_POWER_LIMIT,
        R_POWER_LIMIT_MCHBAR,
        W_POWER_LIMIT_MCHBAR,
        W_VR_CURRENT_CFG,
        W_PP1_CURRENT_CFG,
        W_TURBO_POWER_CURRENT_LIMIT,
        W_CPU_BLNC,
        W_GPU_BLNC,
        W_ENERGY_PERF_BIAS,
        W_TURBO_RATIO_LIMIT,
        W_MISC_PROC_FEATURES,
        W_POWER_CTL,
        W_MISC_PWR_MGMT,
        W_HWP_ENABLE,
        W_HWP_REQ_PKG,
        W_HWP_REQ,
        W_HWP_CTL,
        W_CPU_UV,
        W_GPU_UV,
        W_CACHE_UV,
        W_UNSLICE_UV,
        W_SA_UV,
    	W_PKG_CST_CONFIG_CONTROL,

    	// linux amd
        W_AMDPSTATE_SYSFS,
    	W_AMDPSTATE_EPP_SYSFS,

    	// amd
        RY_REFRESH_TABLE,
        W_RY_STAPM_LIMIT,
        W_RY_FAST_LIMIT,
        W_RY_SLOW_LIMIT,
        W_RY_TCTL_TEMP,
        W_RY_APU_SLOW,
        W_RY_APU_SKIN_TEMP,
        W_RY_DGPU_SKIN_TEMP,
        W_RY_VRM_CURRENT,
        W_RY_VRM_SOC_CURRENT,
        W_RY_VRM_MAX_CURRENT,
        W_RY_VRM_SOC_MAX_CURRENT,
        W_RY_STATIC_GFX_CLOCK,
        W_RY_MIN_GFX_CLOCK,
        W_RY_MAX_GFX_CLOCK,
        W_RY_POWER_PROFILE,
    	W_RY_CO_ALL,
    	W_RY_CO_PER,
        W_AMD_CORE_PERFORMANCE_BOOST,
        W_AMD_CPPC_ENBL_BIT,
        W_AMD_CPPC_REQ,
        W_AMD_HWPSTATE_CMD,

        W_INTEL_GPU_FREQ,
        W_INTEL_GPU_BOOST,
        W_AMD_GPU_DPM_FORCE_PERF_LEVEL,
        W_AMD_GPU_POWER_DPM_STATE,

    	// fan control
    	W_FAN_MODE,
    	W_FAN_SPEED,
    };
}
