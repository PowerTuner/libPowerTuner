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
#include "Utils.h"

namespace LIBPWT {
    using namespace std::string_view_literals;

    std::string_view errorToString(const Error e) {
        switch (e) {
            case Error::CORE_DATA_MISMATCH:
                return "Core data size mismatch"sv;
            case Error::THREAD_DATA_MISMATCH:
                return "Thread data size mismatch"sv;
            case Error::CORE_IDX_MISMATCH:
                return "Core count and core index count mismatch"sv;
            case Error::CORRUPTED_DATA:
                return "Corrupted object"sv;
            case Error::INVALID_ARGS:
                return "Invalid message args"sv;
            case Error::PROFILE_LOAD_FAIL:
                return "Unable to load profile"sv;
            case Error::OS_ACCESS_FAIL:
                return "Failed to setup OS access"sv;

            // linux
            case Error::NO_MSR_FD:
                return "Unable to open MSR descriptor"sv;
            case Error::W_CPUS_ONLINE:
                return "Unable to write online status for some CPUs"sv;
            case Error::W_CPU_SMT:
                return "Unable to write SMT state"sv;
            case Error::W_CPU_SCALING_GOV:
                return "Unable to write scaling governor for some CPUs"sv;
            case Error::W_CPU_FREQ_MIN_MAX:
                return "Unable to write min/max CPU frequency for some CPUs"sv;
            case Error::W_CPU_IDLE_GOV:
                return "Unable to write CPU idle governor"sv;
            case Error::W_BLOCK_DEVICES:
                return "Unable to write some block device queue scheduler"sv;
            case Error::W_MISC_PM_DEVICES:
                return "Unable to write some misc. power management devices settings"sv;

            // windows
            case Error::W_PWR_SCHEME:
                return "Unable to write some power scheme settings"sv;
            case Error::W_PWR_ACTIVE_SCHEME:
                return "Unable to set active power scheme"sv;
            case Error::W_PWR_DELETE_SCHEMES:
                return "Unable to delete some power schemes"sv;
            case Error::W_PWR_RESET_INDIVIDUAL_DEFAULT:
                return "Unable to reset some power schemes to their default values"sv;
            case Error::W_PWR_CREATE_SCHEMES:
                return "Unable to create some power schemes"sv;
            case Error::W_PWR_RESET_SCHEMES_DEFAULT:
                return "Unable to reset power schemes to Windows defaults"sv;
            case Error::W_PWR_REPLACE_WIN_DEFAULT_SCHEMES:
                return "Unable to replace Windows default power schemes"sv;
            case Error::W_PWR_NO_SCHEME_ACCESS:
                return "User has no permission to edit some power schemes"sv;

            // intel
            case Error::W_PKG_POWER_LIMIT:
                return "Unable to write power limit register"sv;
            case Error::R_POWER_LIMIT_MCHBAR:
                return "Unable to read MCHBAR register"sv;
            case Error::W_POWER_LIMIT_MCHBAR:
                return "Unable to write MCHBAR register"sv;
            case Error::W_VR_CURRENT_CFG:
                return "Unable to write VR current config register"sv;
            case Error::W_PP1_CURRENT_CFG:
                return "Unable to write PP1 current config register"sv;
            case Error::W_TURBO_POWER_CURRENT_LIMIT:
                return "Unable to write turbo current power limit register"sv;
            case Error::W_CPU_BLNC:
                return "Unable to write CPU power balance register"sv;
            case Error::W_GPU_BLNC:
                return "Unable to write GPU power balance register"sv;
            case Error::W_ENERGY_PERF_BIAS:
                return "Unable to write power policy preference register"sv;
            case Error::W_TURBO_RATIO_LIMIT:
                return "Unable to write turbo ratio limit register"sv;
            case Error::W_MISC_PROC_FEATURES:
                return "Unable to write misc processor features register"sv;
            case Error::W_POWER_CTL:
                return "Unable to write power ctl register"sv;
            case Error::W_MISC_PWR_MGMT:
                return "Unable to write misc power management register"sv;
            case Error::W_HWP_ENABLE:
                return "Unable to write HWP enable register"sv;
            case Error::W_HWP_REQ_PKG:
                return "Unable to write HWP request pkg register"sv;
            case Error::W_HWP_REQ:
                return "Unable to write HWP request register"sv;
            case Error::W_HWP_CTL:
                return "Unabel to write HWP CTL register"sv;
            case Error::W_CPU_UV:
                return "Unable to write CPU voltage register"sv;
            case Error::W_GPU_UV:
                return "Unable to write GPU voltage register"sv;
            case Error::W_CACHE_UV:
                return "Unable to write cache voltage register"sv;
            case Error::W_UNSLICE_UV:
                return "Unable to write unslice voltage register"sv;
            case Error::W_SA_UV:
                return "Unable to write sys-agent voltage register"sv;
            case Error::W_PKG_CST_CONFIG_CONTROL:
                return "Unable to write C-State configuration control register"sv;

            // amd linux
            case Error::W_AMDPSTATE_SYSFS:
                return "Unable to write AMD PState data"sv;
            case Error::W_AMDPSTATE_EPP_SYSFS:
                return "Unable to write AMD EPP data"sv;

            // ryzenadj
            case Error::RY_REFRESH_TABLE:
                return "Failed to refresh RyzenAdj table, values may be old"sv;
            case Error::W_RY_STAPM_LIMIT:
                return "RyzenAdj: unable to write stapm limit"sv;
            case Error::W_RY_FAST_LIMIT:
                return "RyzenAdj: unable to write fast limit"sv;
            case Error::W_RY_SLOW_LIMIT:
                return "RyzenAdj: unable to write slow limit"sv;
            case Error::W_RY_TCTL_TEMP:
                return "RyzenAdj: unable to write tctl temp"sv;
            case Error::W_RY_APU_SLOW:
                return "RyzenAdj: unable to write apu slow limit"sv;
            case Error::W_RY_APU_SKIN_TEMP:
                return "RyzenAdj: unable to write apu skin temperature limit"sv;
            case Error::W_RY_DGPU_SKIN_TEMP:
                return "RyzenAdj: unable to write dgpu skin temperature limit"sv;
            case Error::W_RY_VRM_CURRENT:
                return "RyzenAdj: unable to write vrm current"sv;
            case Error::W_RY_VRM_SOC_CURRENT:
                return "RyzenAdj: unable to write vrm soc current"sv;
            case Error::W_RY_VRM_MAX_CURRENT:
                return "RyzenAdj: unable to write vrm max current"sv;
            case Error::W_RY_VRM_SOC_MAX_CURRENT:
                return "RyzenAdj: unable to write vrm soc max current"sv;
            case Error::W_RY_STATIC_GFX_CLOCK:
                return "RyzenAdj: unable to write static gpu clock"sv;
            case Error::W_RY_MIN_GFX_CLOCK:
                return "RyzenAdj: unable to set minimum gpu clock"sv;
            case Error::W_RY_MAX_GFX_CLOCK:
                return "RyzenAdj: unable to set maximum gpu clock"sv;
            case Error::W_RY_POWER_PROFILE:
                return "RyzenAdj: unable to set power profile"sv;
            case Error::W_RY_CO_ALL:
                return "RyzenAdj: unable to set curve optimizer"sv;
            case Error::W_RY_CO_PER:
                return "RyzenAdj: unable to set core curve optimizer"sv;

            // amd
            case Error::W_AMD_HWPSTATE_CMD:
                return "Unable to write P-State control register"sv;
            case Error::W_AMD_CORE_PERFORMANCE_BOOST:
                return "Unable to write core performance boost register"sv;
            case Error::W_AMD_CPPC_ENBL_BIT:
                return "Unable to write CPPC enable register"sv;
            case Error::W_AMD_CPPC_REQ:
                return "Unable to write CPPC request register"sv;

            // intel gpu
            case Error::W_INTEL_GPU_FREQ:
                return "Unable to write Intel GPU frequency"sv;
            case Error::W_INTEL_GPU_BOOST:
                return "Unable to write Intel GPU boost frequency"sv;

            // amd gpu
            case Error::W_AMD_GPU_DPM_FORCE_PERF_LEVEL:
                return "Unable to write AMD GPU power dpm force performance level"sv;
            case Error::W_AMD_GPU_POWER_DPM_STATE:
                return "Unable to write AMD GPU power dpm state"sv;

            // fan control
            case Error::W_FAN_MODE:
                return "Unable to write fan mode"sv;
            case Error::W_FAN_SPEED:
                return "Unable to write fan speed"sv;
            default:
                break;
        }

        return ""sv;
    }

    std::string_view GPUVendorToString(const GPUVendor vnd) {
        switch (vnd) {
            case GPUVendor::Intel:
                return "Intel"sv;
            case GPUVendor::AMD:
                return "AMD";
            case GPUVendor::NVIDIA:
                return "NVIDIA"sv;
            default:
                break;
        }

        return "Unknown"sv;
    }
}
