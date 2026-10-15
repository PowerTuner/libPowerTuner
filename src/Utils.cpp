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
#include <QFile>
#include <QDir>
#include <QJsonArray>

#include "Utils.h"

namespace PWTS {
    bool isValidPort(const quint16 port) {
        return (port > 1000 && port < UINT16_MAX);
    }

    QByteArray loadFile(const QString &path) {
        if (path.isEmpty())
            return {};

        QFile fd {path};
        QByteArray ba;

        if (!fd.open(QFile::ReadOnly))
            return ba;

        ba = fd.readAll();

        fd.close();
        return ba;
    }

    bool writeFile(const QString &path, const QByteArray &data) {
        QFile fd {path};
        qint64 written;

        if ((!fd.exists() && !QDir().mkpath(QFileInfo(fd).path())) || !fd.open(QFile::WriteOnly | QFile::Truncate))
            return false;

        written = fd.write(data);

        fd.close();
        return written == data.size();
    }

    bool isValidProfileForImport(const QString &profile) {
        const QFileInfo finfo {profile};

        return finfo.isFile() && finfo.isReadable() && finfo.suffix() == "pwt" && finfo.size() < (2 * 1024 * 1024);
    }

    QHostAddress getHostAddress(const QString &adr) {
        if (adr == "any")
            return QHostAddress::Any;
        else if (adr == "localhost")
            return QHostAddress::LocalHost;

        return QHostAddress(adr);
    }

    QString getErrorStr(const DError e) {
        switch (e) {
            case DError::CORE_DATA_MISMATCH:
                return "Core data size mismatch";
            case DError::THREAD_DATA_MISMATCH:
                return "Thread data size mismatch";
            case DError::CORE_IDX_MISMATCH:
                return "Core count and core index count mismatch";
            case DError::CORRUPTED_DATA:
                return "Corrupted object";
            case DError::INVALID_PACKET:
                return "Invalid packet";
            case DError::INVALID_DCMD:
                return "Invalid daemon cmd";
            case DError::INVALID_ARGS:
                return "Invalid message args";
            case DError::PROFILE_LOAD_FAILED:
                return "Unable to load profile";
            case DError::OS_ACCESS_FAIL:
                return "Failed to setup OS access";

            // linux
            case DError::NO_MSR_FD:
                return "Unable to open MSR descriptor";
            case DError::W_CPUS_ONLINE:
                return "Unable to write online status for some CPUs";
            case DError::W_CPU_SMT:
                return "Unable to write SMT state";
            case DError::W_CPU_SCALING_GOV:
                return "Unable to write scaling governor for some CPUs";
            case DError::W_CPU_FREQ_MIN_MAX:
                return "Unable to write min/max CPU frequency for some CPUs";
            case DError::W_CPU_IDLE_GOV:
                return "Unable to write CPU idle governor";
            case DError::W_BLOCK_DEVICES:
                return "Unable to write some block device queue scheduler";
            case DError::W_MISC_PM_DEVICES:
                return "Unable to write some misc. power management devices settings";

            // windows
            case DError::W_PWR_SCHEME:
                return "Unable to write some power scheme settings";
            case DError::W_PWR_ACTIVE_SCHEME:
                return "Unable to set active power scheme";
            case DError::W_PWR_DELETE_SCHEMES:
                return "Unable to delete some power schemes";
            case DError::W_PWR_RESET_INDIVIDUAL_DEFAULT:
                return "Unable to reset some power schemes to their default values";
            case DError::W_PWR_CREATE_SCHEMES:
                return "Unable to create some power schemes";
            case DError::W_PWR_RESET_SCHEMES_DEFAULT:
                return "Unable to reset power schemes to Windows defaults";
            case DError::W_PWR_REPLACE_WIN_DEFAULT_SCHEMES:
                return "Unable to replace Windows default power schemes";
            case DError::W_PWR_NO_SCHEME_ACCESS:
                return "User has no permission to edit some power schemes";

            // intel
            case DError::W_PKG_POWER_LIMIT:
                return "Unable to write power limit register";
            case DError::R_POWER_LIMIT_MCHBAR:
                return "Unable to read MCHBAR register";
            case DError::W_POWER_LIMIT_MCHBAR:
                return "Unable to write MCHBAR register";
            case DError::W_VR_CURRENT_CFG:
                return "Unable to write VR current config register";
            case DError::W_PP1_CURRENT_CFG:
                return "Unable to write PP1 current config register";
            case DError::W_TURBO_POWER_CURRENT_LIMIT:
                return "Unable to write turbo current power limit register";
            case DError::W_CPU_BLNC:
                return "Unable to write CPU power balance register";
            case DError::W_GPU_BLNC:
                return "Unable to write GPU power balance register";
            case DError::W_ENERGY_PERF_BIAS:
                return "Unable to write power policy preference register";
            case DError::W_TURBO_RATIO_LIMIT:
                return "Unable to write turbo ratio limit register";
            case DError::W_MISC_PROC_FEATURES:
                return "Unable to write misc processor features register";
            case DError::W_POWER_CTL:
                return "Unable to write power ctl register";
            case DError::W_MISC_PWR_MGMT:
                return "Unable to write misc power management register";
            case DError::W_HWP_ENABLE:
                return "Unable to write HWP enable register";
            case DError::W_HWP_REQ_PKG:
                return "Unable to write HWP request pkg register";
            case DError::W_HWP_REQ:
                return "Unable to write HWP request register";
            case DError::W_HWP_CTL:
                return "Unabel to write HWP CTL register";
            case DError::W_CPU_UV:
                return "Unable to write CPU voltage register";
            case DError::W_GPU_UV:
                return "Unable to write GPU voltage register";
            case DError::W_CACHE_UV:
                return "Unable to write cache voltage register";
            case DError::W_UNSLICE_UV:
                return "Unable to write unslice voltage register";
            case DError::W_SA_UV:
                return "Unable to write sys-agent voltage register";
            case DError::W_PKG_CST_CONFIG_CONTROL:
                return "Unable to write C-State configuration control register";

            // amd linux
            case DError::W_AMDPSTATE_SYSFS:
                return "Unable to write AMD PState data";
            case DError::W_AMDPSTATE_EPP_SYSFS:
                return "Unable to write AMD EPP data";

            // ryzenadj
            case DError::RY_REFRESH_TABLE:
                return "Failed to refresh RyzenAdj table, values may be old";
            case DError::W_RY_STAPM_LIMIT:
                return "RyzenAdj: unable to write stapm limit";
            case DError::W_RY_FAST_LIMIT:
                return "RyzenAdj: unable to write fast limit";
            case DError::W_RY_SLOW_LIMIT:
                return "RyzenAdj: unable to write slow limit";
            case DError::W_RY_TCTL_TEMP:
                return "RyzenAdj: unable to write tctl temp";
            case DError::W_RY_APU_SLOW:
                return "RyzenAdj: unable to write apu slow limit";
            case DError::W_RY_APU_SKIN_TEMP:
                return "RyzenAdj: unable to write apu skin temperature limit";
            case DError::W_RY_DGPU_SKIN_TEMP:
                return "RyzenAdj: unable to write dgpu skin temperature limit";
            case DError::W_RY_VRM_CURRENT:
                return "RyzenAdj: unable to write vrm current";
            case DError::W_RY_VRM_SOC_CURRENT:
                return "RyzenAdj: unable to write vrm soc current";
            case DError::W_RY_VRM_MAX_CURRENT:
                return "RyzenAdj: unable to write vrm max current";
            case DError::W_RY_VRM_SOC_MAX_CURRENT:
                return "RyzenAdj: unable to write vrm soc max current";
            case DError::W_RY_STATIC_GFX_CLOCK:
                return "RyzenAdj: unable to write static gpu clock";
            case DError::W_RY_MIN_GFX_CLOCK:
                return "RyzenAdj: unable to set minimum gpu clock";
            case DError::W_RY_MAX_GFX_CLOCK:
                return "RyzenAdj: unable to set maximum gpu clock";
            case DError::W_RY_POWER_PROFILE:
                return "RyzenAdj: unable to set power profile";
            case DError::W_RY_CO_ALL:
                return "RyzenAdj: unable to set curve optimizer";
            case DError::W_RY_CO_PER:
                return "RyzenAdj: unable to set core curve optimizer";

            // amd
            case DError::W_AMD_HWPSTATE_CMD:
                return "Unable to write P-State control register";
            case DError::W_AMD_CORE_PERFORMANCE_BOOST:
                return "Unable to write core performance boost register";
            case DError::W_AMD_CPPC_ENBL_BIT:
                return "Unable to write CPPC enable register";
            case DError::W_AMD_CPPC_REQ:
                return "Unable to write CPPC request register";

            // intel gpus
            case DError::W_INTEL_GPU_FREQ:
                return "Unable to write Intel GPU frequency";
            case DError::W_INTEL_GPU_BOOST:
                return "Unable to write Intel GPU boost frequency";

            // amd gpus
            case DError::W_AMD_GPU_DPM_FORCE_PERF_LEVEL:
                return "Unable to write AMD GPU power dpm force performance level";
            case DError::W_AMD_GPU_POWER_DPM_STATE:
                return "Unable to write AMD GPU power dpm state";

            // fan control
            case DError::W_FAN_MODE:
                return "Unable to write fan mode";
            case DError::W_FAN_SPEED:
                return "Unable to write fan speed";
            default:
                break;
        }

        return QString("Unknown error code: %1").arg(static_cast<int>(e));
    }

    QString getPacketErrorStr(const PacketError e) {
        switch (e) {
            case PacketError::NoError:
                return "No packet error";
            case PacketError::VersionMismatch:
                return "Client and daemon version mismatch, please update";
            default:
                break;
        }

        return QString("Unknown error code %1").arg(static_cast<int>(e));
    }

    QString featureToString(const Feature feat) {
        switch (feat) {
            // linux
            case Feature::CPU_PARK_SYSFS:
                return "Sysfs: CPU hotplug";
    	    case Feature::CPU_SMT_SYSFS:
                return "Sysfs: SMT/HT";
            case Feature::CPUFREQ_SYSFS:
                return "Sysfs: cpufreq";
    	    case Feature::CPUIDLE_GOV_SYSFS:
                return "Sysfs: cpuidle governor";

            // amd linux
            case Feature::AMD_PSTATE_SYSFS:
                return "Sysfs: AMD PState";

            // intel gpus
		    case Feature::INTEL_GPU_RPS_FREQ_SYSFS:
                return "Sysfs: Intel GPU frequency";
		    case Feature::INTEL_GPU_BOOST_SYSFS:
                return "Sysfs: Intel GPU boost";

            // amd gpus
		    case Feature::AMD_GPU_DPM_FORCE_PERF_LEVEL_SYSFS:
                return "Sysfs: AMD GPU DPM force perf level";
		    case Feature::AMD_GPU_POWER_DPM_STATE_SYSFS:
                return "Sysfs: AMD GPU power DPM state";

            // intel
            case Feature::INTEL_PKG_THERM_STATUS:
                return "MSR: Intel package thermal status information";
            case Feature::INTEL_PLATFORM_INFO:
                return "MSR: Intel platform info";
            case Feature::INTEL_PKG_POWER_LIMIT:
                return "MSR: Intel pkg power limit";
            case Feature::INTEL_MCHBAR_PKG_RAPL_LIMIT:
                return "MCHBAR: Intel pkg rapl limit";
            case Feature::INTEL_VR_CURRENT_CFG:
                return "MSR: Intel vr current config";
            case Feature::INTEL_PP1_CURRENT_CFG:
                return "MSR: Intel pp1 current config";
            case Feature::INTEL_TURBO_POWER_CURRENT_LIMIT:
                return "MSR: Intel turbo power current limit";
            case Feature::INTEL_TURBO_POWER_CURRENT_LIMIT_RW:
                return "MSR: Intel turbo power current limit writable";
            case Feature::INTEL_CPU_POWER_BALANCE:
                return "MSR: Intel CPU power balance";
            case Feature::INTEL_GPU_POWER_BALANCE:
                return "MSR: Intel GPU power balance";
            case Feature::INTEL_ENERGY_PERF_BIAS:
                return "MSR: Intel energy perf bias";
            case Feature::INTEL_TURBO_RATIO_LIMIT:
                return "MSR: Intel turbo ratio limit";
            case Feature::INTEL_TURBO_RATIO_LIMIT_RW:
                return "MSR: Intel turbo ratio limit writable";
            case Feature::INTEL_ENHANCED_SPEEDSTEP:
                return "MSR: Intel enhanced speedstep";
            case Feature::INTEL_TURBO_BOOST:
                return "MSR: Intel turbo boost";
            case Feature::INTEL_POWER_CTL:
                return "MSR: Intel power ctl";
            case Feature::INTEL_MISC_PWR_MGMT:
                return "MSR: Intel power mgmt";
            case Feature::INTEL_HWP_REQ_PKG:
                return "MSR: Intel HWP request pkg";
            case Feature::INTEL_HWP_EPP:
                return "MSR: Intel HWP EPP";
            case Feature::INTEL_HWP_ACT_WIND:
                return "MSR: Intel HWP activity window";
            case Feature::INTEL_HWP_VALID_BITS:
                return "MSR: Intel HWP valid bits";
            case Feature::INTEL_HWP_CTL:
                return "MSR: Intel HWP ctl";
            case Feature::INTEL_UNDERVOLT_CPU:
                return "MSR: Intel CPU undervolt";
            case Feature::INTEL_UNDERVOLT_GPU:
                return "MSR: Intel GPU undervolt";
            case Feature::INTEL_UNDERVOLT_CACHE:
                return "MSR: Intel Cache undervolt";
            case Feature::INTEL_UNDERVOLT_UNSLICE:
                return "MSR: Intel unslice undervolt";
            case Feature::INTEL_UNDERVOLT_SYSAGENT:
                return "MSR: Intel sysagent undervolt";
            case Feature::INTEL_PKG_CST_CONFIG_CONTROL:
                return "MSR: Intel package C-State configuration control";
            case Feature::INTEL_TEMPERATURE_TARGET:
                return "MSR: Intel temperature target";

            // ryzenadj
            case Feature::AMD_RY_STAPM_LIMIT_W:
                return "RADJ: stapm limit [write]";
            case Feature::AMD_RY_STAPM_LIMIT_R:
                return "RADJ: stapm limit [read]";
            case Feature::AMD_RY_FAST_LIMIT_W:
                return "RADJ: fast limit [write]";
            case Feature::AMD_RY_FAST_LIMIT_R:
                return "RADJ: fast limit [read]";
            case Feature::AMD_RY_SLOW_LIMIT_W:
                return "RADJ: slow limit [write]";
            case Feature::AMD_RY_SLOW_LIMIT_R:
                return "RADJ: slow limit [read]";
            case Feature::AMD_RY_TCTL_TEMP_W:
                return "RADJ: tctl temperature [write]";
            case Feature::AMD_RY_TCTL_TEMP_R:
                return "RADJ: tctl temperature [read]";
            case Feature::AMD_RY_TCTL_TEMP_VAL:
                return "RADJ: tctl temperature [stat]";
            case Feature::AMD_RY_APU_SLOW_W:
                return "RADJ: APU slow limit [write]";
            case Feature::AMD_RY_APU_SLOW_R:
                return "RADJ: APU slow limit [read]";
            case Feature::AMD_RY_APU_SKIN_TEMP_W:
                return "RADJ: APU skin temperature [write]";
            case Feature::AMD_RY_APU_SKIN_TEMP_R:
                return "RADJ: APU skin temperature [read]";
            case Feature::AMD_RY_DGPU_SKIN_TEMP_W:
                return "RADJ: DGPU skin temperature [write]";
            case Feature::AMD_RY_DGPU_SKIN_TEMP_R:
                return "RADJ: DGPU skin temperature [read]";
            case Feature::AMD_RY_VRM_CURRENT_W:
                return "RADJ: vrm current [write]";
            case Feature::AMD_RY_VRM_CURRENT_R:
                return "RADJ: vrm current [read]";
            case Feature::AMD_RY_VRM_SOC_CURRENT_W:
                return "RADJ: vrm soc current [write]";
            case Feature::AMD_RY_VRM_SOC_CURRENT_R:
                return "RADJ: vrm soc current [read]";
            case Feature::AMD_RY_VRM_MAX_CURRENT_W:
                return "RADJ: vrm max current [write]";
            case Feature::AMD_RY_VRM_MAX_CURRENT_R:
                return "RADJ: vrm max current [read]";
            case Feature::AMD_RY_VRM_SOC_MAX_CURRENT_W:
                return "RADJ: vrm soc max current [write]";
            case Feature::AMD_RY_VRM_SOC_MAX_CURRENT_R:
                return "RADJ: vrm soc max current [read]";
            case Feature::AMD_RY_STATIC_GFX_CLK_W:
                return "RADJ: static GPU clock [write]";
    	    case Feature::AMD_RY_MIN_GFX_CLOCK_W:
                return "RADJ: min GPU clock [write]";
            case Feature::AMD_RY_MIN_GFX_CLOCK_R:
                return "RADJ: min GPU clock [read]";
    	    case Feature::AMD_RY_MAX_GFX_CLOCK_W:
                return "RADJ: max GPU clock [write]";
            case Feature::AMD_RY_MAX_GFX_CLOCK_R:
                return "RADJ: max GPU clock [read]";
            case Feature::AMD_RY_POWER_PROFILE_W:
                return "RADJ: power profile [write]";
    	    case Feature::AMD_RY_CO_ALL_W:
                return "RADJ: curve optimizer all [write]";
    	    case Feature::AMD_RY_CO_PER_W:
                return "RADJ: per core curve optimizer [write]";

            // amd
            case Feature::AMD_HWPSTATE:
                return "MSR: AMD PState";
            case Feature::AMD_CORE_PERFORMANCE_BOOST:
                return "MSR: AMD CPU boost";
            case Feature::AMD_CPPC:
                return "MSR: AMD CPPC";

            // fan control
            case Feature::FAN_CURVE:
                return "Fan curve";
            default:
                break;
        }

        return "";
    }

    QString GPUVendorToString(const GPUVendor vnd) {
        switch (vnd) {
            case GPUVendor::Intel:
                return "Intel";
            case GPUVendor::AMD:
                return "AMD";
            case GPUVendor::NVIDIA:
                return "NVIDIA";
            default:
                break;
        }

        return "Unknown";
    }

    QJsonObject getDeviceInfoJson(const DeviceInfoPacket &packet) {
        const bool isLinux = packet.sysInfo.osType == OSType::Linux;
        QJsonObject powertunerInfo;
        QJsonObject jInfo;
        QJsonObject jSysInfo;
        QJsonObject jCpuInfo;
        QJsonArray jGpusInfo;
        QJsonArray jFansInfo;
        QJsonObject jFeatures;
        QJsonArray jCpuFeatures;
        QJsonObject jGpusFeatures;
        QJsonObject jFansFeatures;
        QJsonObject jDaemon;
        QJsonObject jobj;

        powertunerInfo.insert("daemon_major_ver", packet.daemonMajorVersion);
        powertunerInfo.insert("daemon_minor_ver", packet.daemonMinorVersion);
        powertunerInfo.insert("daemon_libshared_major_ver", packet.daemonPwtsMajorVersion);
        powertunerInfo.insert("daemon_libshared_minor_ver", packet.daemonPwtsMinorVersion);

        jSysInfo.insert("distribution", packet.sysInfo.distribution);
        jSysInfo.insert("product", packet.sysInfo.product);
        jSysInfo.insert("manufacturer", packet.sysInfo.manufacturer);
        jSysInfo.insert("kernel", packet.sysInfo.kernel);
        jSysInfo.insert("arch", packet.sysInfo.arch);
        jSysInfo.insert("bios_version", packet.sysInfo.biosVersion);
        jSysInfo.insert("bios_vendor", packet.sysInfo.biosVendor);
        jSysInfo.insert("bios_date", packet.sysInfo.biosDate);
        jSysInfo.insert("available_ram", packet.sysInfo.availableRam);

        if (!packet.sysInfo.ecVersion.isEmpty())
            jSysInfo.insert("ec_version", packet.sysInfo.ecVersion);

        if (packet.dynSysInfo.onlineCPUCount > 0) {
            const int logicalCPUCount = packet.cpuInfo.numLogicalCpus;
            const int onlineCpus = packet.dynSysInfo.onlineCPUCount;

            jSysInfo.insert("online_cpus", onlineCpus);
            jSysInfo.insert("offline_cpus", onlineCpus > 0 && onlineCpus <= logicalCPUCount ? (logicalCPUCount - onlineCpus) : 0);
        }

        if (isLinux)
            jSysInfo.insert("swap", packet.dynSysInfo.swapMemory);

        jCpuInfo.insert("brand", packet.cpuInfo.brand);
        jCpuInfo.insert("codename", packet.cpuInfo.codename);
        jCpuInfo.insert("technology_node", packet.cpuInfo.techNode);
        jCpuInfo.insert("vendor", packet.cpuInfo.vendorString);
        jCpuInfo.insert("model", QString("0x%1").arg(QString::number(packet.cpuInfo.model, 16)));
        jCpuInfo.insert("ext_model", QString("0x%1").arg(QString::number(packet.cpuInfo.extModel, 16)));
        jCpuInfo.insert("family", QString("0x%1").arg(QString::number(packet.cpuInfo.family, 16)));
        jCpuInfo.insert("ext_family", QString("0x%1").arg(QString::number(packet.cpuInfo.extFamily, 16)));
        jCpuInfo.insert("core_count", packet.cpuInfo.numCores);
        jCpuInfo.insert("thread_count", packet.cpuInfo.numLogicalCpus);
        jCpuInfo.insert("stepping", packet.cpuInfo.stepping);
        jCpuInfo.insert("l1_dcache", packet.cpuInfo.l1DCache);
        jCpuInfo.insert("l1_icache", packet.cpuInfo.l1ICache);
        jCpuInfo.insert("l2_cache", packet.cpuInfo.l2Cache);
        jCpuInfo.insert("l3_cache", packet.cpuInfo.l3Cache);

        if (!packet.cpuInfo.l4Cache.isEmpty())
            jCpuInfo.insert("l4_cache", packet.cpuInfo.l4Cache);

        for (int i=0,l=packet.dynSysInfo.cpuMicrocode.size(); i<l; ++i)
            jCpuInfo.insert(QString("cpu%1_microcode").arg(i), packet.dynSysInfo.cpuMicrocode[i]);

        for (const GpuInfo &info: packet.gpusInfo) {
            QJsonObject jgpu;

            jgpu.insert("index", info.index);
            jgpu.insert("device_id", info.deviceID);
            jgpu.insert("revision_id", info.revisionID);
            jgpu.insert("vendor", GPUVendorToString(info.vendor));

            if (!info.vbiosVersion.isEmpty())
                jgpu.insert("vbios_version", info.vbiosVersion);

            jGpusInfo.append(jgpu);
        }

        for (const auto &[fanID, label]: packet.fanLabels.asKeyValueRange()) {
            QJsonObject jfan;

            jfan.insert("id", fanID);
            jfan.insert("label", label);
            jFansInfo.append(jfan);
        }

        for (const Feature &feat: packet.features.cpu) {
            const QString str = featureToString(feat);

            if (!str.isEmpty())
                jCpuFeatures.append(str);
        }

        for (const auto &[gpuIdx, features]: packet.features.gpus.asKeyValueRange()) {
            QJsonArray jGpuFeats;

            for (const Feature &feat: features.second) {
                const QString str = featureToString(feat);

                if (!str.isEmpty())
                    jGpuFeats.append(str);
            }

            jGpusFeatures.insert(QString("gpu_%1").arg(gpuIdx), jGpuFeats);
        }

        for (const auto &[fanID, features]: packet.features.fans.asKeyValueRange()) {
            QJsonArray jFanFeatures;

            for (const Feature &feat: features) {
                const QString str = featureToString(feat);

                if (!str.isEmpty())
                    jFanFeatures.append(str);
            }

            jFansFeatures.insert(fanID, jFanFeatures);
        }

        jDaemon.insert("data_path", packet.daemonDataPath);
        jInfo.insert("system", jSysInfo);
        jInfo.insert("cpu", jCpuInfo);
        jInfo.insert("gpus", jGpusInfo);
        jInfo.insert("fans", jFansInfo);
        jFeatures.insert("cpu", jCpuFeatures);
        jFeatures.insert("gpus", jGpusFeatures);
        jFeatures.insert("fans", jFansFeatures);

        jobj.insert("powertuner", powertunerInfo);
        jobj.insert("device_info", jInfo);
        jobj.insert("features", jFeatures);
        jobj.insert("daemon", jDaemon);

        return jobj;
    }
}
