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
#include "Serialize.h"
#include "extern/yaml-cpp/include/yaml-cpp/yaml.h"
#include "YamlKeys.h"

namespace LIBPWT {
    static YAML::Emitter &operator<<(YAML::Emitter &out, const DaemonSettings &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::startProfile << YAML::Value << v.startProfile
            << YAML::Key << YKeys::batteryProfile << YAML::Value << v.batteryProfile
            << YAML::Key << YKeys::psupplyProfile << YAML::Value << v.powerSupplyProfile
            << YAML::Key << YKeys::address << YAML::Value << v.address
            << YAML::Key << YKeys::applyInterval << YAML::Value << v.applyInterval
            << YAML::Key << YKeys::applyOnWake << YAML::Value << v.applyOnWakeFromSleep
            << YAML::Key << YKeys::ignoreBatteryEvt << YAML::Value << v.ignoreBatteryEvent
            << YAML::Key << YKeys::logLevel << YAML::Value << static_cast<int>(v.logLvl)
            << YAML::Key << YKeys::port << YAML::Value << v.port
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Features &v) {
        out << YAML::BeginMap;

        if (!v.cpu.empty()) {
            out << YAML::Key << YKeys::cpu << YAML::Value << YAML::BeginSeq;

            for (const Feature &feature: v.cpu)
                out << static_cast<int>(feature);

            out << YAML::EndSeq;
        }

        if (!v.gpu.empty()) {
            out << YAML::Key << YKeys::gpu << YAML::Value << YAML::BeginMap;

            for (const auto &[index, features]: v.gpu) {
                out << YAML::Key << index << YAML::Value << YAML::BeginSeq;

                for (const Feature &f: features)
                    out << static_cast<int>(f);

                out << YAML::EndSeq;
            }

            out << YAML::EndMap;
        }

        if (!v.fan.empty()) {
            out << YAML::Key << YKeys::fan << YAML::Value << YAML::BeginMap;

            for (const auto &[index, features]: v.fan) {
                out << YAML::Key << index << YAML::Value << YAML::BeginSeq;

                for (const Feature &f: features)
                    out << static_cast<int>(f);

                out << YAML::EndSeq;
            }

            out << YAML::EndMap;
        }

        out << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::optional<DaemonInfo> &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::versionMajor << YAML::Value << v->versionMajor
            << YAML::Key << YKeys::versionMinor << YAML::Value << v->versionMinor
            << YAML::Key << YKeys::dataPath << YAML::Value << v->dataPath
            << YAML::Key << YKeys::settings << YAML::Value << v->settings
            << YAML::Key << YKeys::features << YAML::Value << v->features
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::optional<SystemInfo> &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::distribution << YAML::Value << v->distribution
            << YAML::Key << YKeys::kernel << YAML::Value << v->kernel
            << YAML::Key << YKeys::arch << YAML::Value << v->arch
            << YAML::Key << YKeys::biosVersion << YAML::Value << v->biosVersion
            << YAML::Key << YKeys::biosVendor << YAML::Value << v->biosVendor
            << YAML::Key << YKeys::biosDate << YAML::Value << v->biosDate
            << YAML::Key << YKeys::ecVersion << YAML::Value << v->ecVersion
            << YAML::Key << YKeys::product << YAML::Value << v->product
            << YAML::Key << YKeys::manufacturer << YAML::Value << v->manufacturer
            << YAML::Key << YKeys::availableRam << YAML::Value << v->availableRam
            << YAML::Key << YKeys::swapMemory << YAML::Value << v->swapMemory
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::optional<CPUInfo> &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::brand << YAML::Value << v->brand
            << YAML::Key << YKeys::codename << YAML::Value << v->codename
            << YAML::Key << YKeys::techNode << YAML::Value << v->techNode
            << YAML::Key << YKeys::CPUString << YAML::Value << v->CPUString
            << YAML::Key << YKeys::model << YAML::Value << v->model
            << YAML::Key << YKeys::extModel << YAML::Value << v->extModel
            << YAML::Key << YKeys::family << YAML::Value << v->family
            << YAML::Key << YKeys::extFamily << YAML::Value << v->extFamily
            << YAML::Key << YKeys::cores << YAML::Value << v->cores
            << YAML::Key << YKeys::threads << YAML::Value << v->threads
            << YAML::Key << YKeys::stepping << YAML::Value << v->stepping
            << YAML::Key << YKeys::l1DCache << YAML::Value << v->l1DCache
            << YAML::Key << YKeys::l1ICache << YAML::Value << v->l1ICache
            << YAML::Key << YKeys::l2Cache << YAML::Value << v->l2Cache
            << YAML::Key << YKeys::l3Cache << YAML::Value << v->l3Cache
            << YAML::Key << YKeys::l4Cache << YAML::Value << v->l4Cache
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const GPUInfo &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::vendor << YAML::Value << static_cast<int>(v.vendor)
            << YAML::Key << YKeys::deviceID << YAML::Value << v.deviceID
            << YAML::Key << YKeys::revisionID << YAML::Value << v.revisionID
            << YAML::Key << YKeys::biosVersion << YAML::Value << v.biosVersion
            << YAML::Key << YKeys::index << YAML::Value << v.index
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::vector<LNX::CPUSysFs> &v) {
        out << YAML::BeginSeq;

        for (const LNX::CPUSysFs &cpu: v) {
            out << YAML::BeginMap;

            if (cpu.microcode)
                out << YAML::Key << YKeys::microcode << YAML::Value << *cpu.microcode;

            if (cpu.online)
                out << YAML::Key << YKeys::online << YAML::Value << *cpu.online;

            if (!cpu.affectedCPUs.empty())
                out << YAML::Key << YKeys::affectedCPUs << YAML::Value << cpu.affectedCPUs;

            if (cpu.cpuinfoMaxFreq)
                out << YAML::Key << YKeys::cpuinfoMaxFreq << YAML::Value << *cpu.cpuinfoMaxFreq;

            if (cpu.cpuinfoMinFreq)
                out << YAML::Key << YKeys::cpuinfoMinFreq << YAML::Value << *cpu.cpuinfoMinFreq;

            if (!cpu.scalingAvailableGovernors.empty())
                out << YAML::Key << YKeys::scalingAvailableGovernors << YAML::Value << cpu.scalingAvailableGovernors;

            if (cpu.scalingGovernor)
                out << YAML::Key << YKeys::scalingGovernor << YAML::Value << *cpu.scalingGovernor;

            if (cpu.scalingMaxFreq)
                out << YAML::Key << YKeys::scalingMaxFreq << YAML::Value << *cpu.scalingMaxFreq;

            if (cpu.scalingMinFreq)
                out << YAML::Key << YKeys::scalingMinFreq << YAML::Value << *cpu.scalingMinFreq;

            if (!cpu.energyPerformanceAvailablePreferences.empty())
                out << YAML::Key << YKeys::energyPerformanceAvailablePreferences << YAML::Value << cpu.energyPerformanceAvailablePreferences;

            if (cpu.energyPerformancePreference)
                out << YAML::Key << YKeys::energyPerformancePreference << YAML::Value << *cpu.energyPerformancePreference;

            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::unordered_map<int, Intel::LNX::IntelGPU> &v) {
        out << YAML::BeginMap;

        for (const auto &[index, gpu]: v) {
            out << YAML::Key << index << YAML::Value << YAML::BeginMap;

            if (gpu.gtMaxFreqMHz)
                out << YAML::Key << YKeys::gtMaxFreqMHz << YAML::Value << *gpu.gtMaxFreqMHz;

            if (gpu.gtMinFreqMHz)
                out << YAML::Key << YKeys::gtMinFreqMHz << YAML::Value << *gpu.gtMinFreqMHz;

            if (gpu.gtRP0FreqMHz)
                out << YAML::Key << YKeys::gtRP0FreqMHz << YAML::Value << *gpu.gtRP0FreqMHz;

            if (gpu.gtRPnFreqMHz)
                out << YAML::Key << YKeys::gtRPnFreqMHz << YAML::Value << *gpu.gtRPnFreqMHz;

            if (gpu.gtBoostFreqMHz)
                out << YAML::Key << YKeys::gtBoostFreqMHz << YAML::Value << *gpu.gtBoostFreqMHz;

            out << YAML::EndMap;
        }

        out << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::unordered_map<int, AMD::LNX::AMDGPU> &v) {
        out << YAML::BeginMap;

        for (const auto &[index, gpu]: v) {
            out << YAML::Key << index << YAML::Value << YAML::BeginMap;

            if (gpu.sclkMaxFreq)
                out << YAML::Key << YKeys::sclkMaxFreq << YAML::Value << *gpu.sclkMaxFreq;

            if (gpu.sclkMinFreq)
                out << YAML::Key << YKeys::sclkMinFreq << YAML::Value << *gpu.sclkMinFreq;

            if (gpu.powerDpmForcePerfLevel)
                out << YAML::Key << YKeys::powerDpmForcePerfLevel << YAML::Value << *gpu.powerDpmForcePerfLevel;

            if (gpu.powerDpmState)
                out << YAML::Key << YKeys::powerDpmState << YAML::Value << *gpu.powerDpmState;

            out << YAML::EndMap;
        }

        out << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::vector<LNX::BlockDeviceQueueScheduler> &v) {
        out << YAML::BeginSeq;

        for (const LNX::BlockDeviceQueueScheduler &device: v) {
            out << YAML::BeginMap
                << YAML::Key << YKeys::device << YAML::Value << device.device
                << YAML::Key << YKeys::prettyName << YAML::Value << device.prettyName
                << YAML::Key << YKeys::availableSchedulers << YAML::Value << device.availableSchedulers
                << YAML::Key << YKeys::scheduler << YAML::Value << device.scheduler
                << YAML::EndMap;
        }

        out << YAML::EndSeq;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::vector<LNX::MiscPMDevice> &v) {
        out << YAML::BeginSeq;

        for (const LNX::MiscPMDevice &device: v) {
            out << YAML::BeginMap
                << YAML::Key << YKeys::name << YAML::Value << device.name
                << YAML::Key << YKeys::control << YAML::Value << device.control
                << YAML::Key << YKeys::controlValue << YAML::Value << device.controlValue
                << YAML::EndMap;
        }

        out << YAML::EndSeq;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::optional<LNX::SysFs> &v) {
        out << YAML::BeginMap;

        if (!v->cpus.empty())
            out << YAML::Key << YKeys::cpus << YAML::Value << v->cpus;

        if (!v->intelGPUs.empty())
            out << YAML::Key << YKeys::intelGPUs << YAML::Value << v->intelGPUs;

        if (!v->amdGPUs.empty())
            out << YAML::Key << YKeys::amdGPUs << YAML::Value << v->amdGPUs;

        if (v->smtControl)
            out << YAML::Key << YKeys::smtControl << YAML::Value << *v->smtControl;

        if (!v->cpuIdleAvailableGovernors.empty())
            out << YAML::Key << YKeys::cpuIdleAvailableGovernors << YAML::Value << v->cpuIdleAvailableGovernors;

        if (v->cpuIdleCurrentGovernor)
            out << YAML::Key << YKeys::cpuIdleCurrentGovernor << YAML::Value << *v->cpuIdleCurrentGovernor;

        if (!v->blockDevicesQueScheduler.empty())
            out << YAML::Key << YKeys::blockDevicesQueScheduler << YAML::Value << v->blockDevicesQueScheduler;

        if (!v->miscPMDevices.empty())
            out << YAML::Key << YKeys::miscPMDevices << YAML::Value << v->miscPMDevices;

        if (v->amdPStateStatus)
            out << YAML::Key << YKeys::amdPStateStatus << YAML::Value << *v->amdPStateStatus;

        if (v->intelPStateMaxPerfPct)
            out << YAML::Key << YKeys::intelPStateMaxPerfPct << YAML::Value << *v->intelPStateMaxPerfPct;

        if (v->intelPStateMinPerfPct)
            out << YAML::Key << YKeys::intelPStateMinPerfPct << YAML::Value << *v->intelPStateMinPerfPct;

        out << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::vector<AMD::MSRCore> &v) {
        out << YAML::BeginSeq;

        for (const AMD::MSRCore &core: v) {
            out << YAML::BeginMap;

            if (core.curveOptimizer)
                out << YAML::Key << YKeys::curveOptimizer << YAML::Value << *core.curveOptimizer;

            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const AMD::CPPCCapability1 &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::lowestPerf << YAML::Value << v.lowestPerf
            << YAML::Key << YKeys::lowNonLinearPerf << YAML::Value << v.lowNonLinearPerf
            << YAML::Key << YKeys::nominalPerf << YAML::Value << v.nominalPerf
            << YAML::Key << YKeys::highestPerf << YAML::Value << v.highestPerf
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const AMD::CPPCRequest &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::maxPerf << YAML::Value << v.maxPerf
            << YAML::Key << YKeys::minPerf << YAML::Value << v.minPerf
            << YAML::Key << YKeys::desiredPerf << YAML::Value << v.desiredPerf
            << YAML::Key << YKeys::epp << YAML::Value << v.epp
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::vector<AMD::MSRThread> &v) {
        out << YAML::BeginSeq;

        for (const AMD::MSRThread &thread: v) {
            out << YAML::BeginMap;

            if (thread.cppcCapability1)
                out << YAML::Key << YKeys::cppcCapability1 << YAML::Value << *thread.cppcCapability1;

            if (thread.cppcRequest)
                out << YAML::Key << YKeys::cppcRequest << YAML::Value << *thread.cppcRequest;

            if (thread.corePerfBoost)
                out << YAML::Key << YKeys::corePerfBoost << YAML::Value << *thread.corePerfBoost;

            if (thread.pstateCmd)
                out << YAML::Key << YKeys::pstateCmd << YAML::Value << *thread.pstateCmd;

            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const AMD::PStateCurrentLimit &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::curPStateLimit << YAML::Value << v.curPStateLimit
            << YAML::Key << YKeys::pstateMaxValue << YAML::Value << v.pstateMaxValue
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::optional<AMD::MSR> &v) {
        out << YAML::BeginMap;

        if (!v->cores.empty())
            out << YAML::Key << YKeys::cores << YAML::Value << v->cores;

        if (!v->threads.empty())
            out << YAML::Key << YKeys::threads << YAML::Value << v->threads;

        if (v->pstateCurrentLimit)
            out << YAML::Key << YKeys::pstateCurrentLimit << YAML::Value << *v->pstateCurrentLimit;

        if (v->cppcEnableBit)
            out << YAML::Key << YKeys::cppcEnableBit << YAML::Value << *v->cppcEnableBit;

        if (v->stapmLimit)
            out << YAML::Key << YKeys::stapmLimit << YAML::Value << *v->stapmLimit;

        if (v->fastLimit)
            out << YAML::Key << YKeys::fastLimit << YAML::Value << *v->fastLimit;

        if (v->slowLimit)
            out << YAML::Key << YKeys::slowLimit << YAML::Value << *v->slowLimit;

        if (v->tctlTemp)
            out << YAML::Key << YKeys::tctlTemp << YAML::Value << *v->tctlTemp;

        if (v->apuSlow)
            out << YAML::Key << YKeys::apuSlow << YAML::Value << *v->apuSlow;

        if (v->apuSkinTemp)
            out << YAML::Key << YKeys::apuSkinTemp << YAML::Value << *v->apuSkinTemp;

        if (v->dgpuSkinTemp)
            out << YAML::Key << YKeys::dgpuSkinTemp << YAML::Value << *v->dgpuSkinTemp;

        if (v->curveOptimizer)
            out << YAML::Key << YKeys::curveOptimizer << YAML::Value << *v->curveOptimizer;

        if (v->vrmCurrent)
            out << YAML::Key << YKeys::vrmCurrent << YAML::Value << *v->vrmCurrent;

        if (v->vrmSocCurrent)
            out << YAML::Key << YKeys::vrmSocCurrent << YAML::Value << *v->vrmSocCurrent;

        if (v->vrmMaxCurrent)
            out << YAML::Key << YKeys::vrmMaxCurrent << YAML::Value << *v->vrmMaxCurrent;

        if (v->vrmSocMaxCurrent)
            out << YAML::Key << YKeys::vrmSocMaxCurrent << YAML::Value << *v->vrmSocMaxCurrent;

        if (v->staticGfxClock)
            out << YAML::Key << YKeys::staticGfxClock << YAML::Value << *v->staticGfxClock;

        if (v->minGfxClock)
            out << YAML::Key << YKeys::minGfxClock << YAML::Value << *v->minGfxClock;

        if (v->maxGfxClock)
            out << YAML::Key << YKeys::maxGfxClock << YAML::Value << *v->maxGfxClock;

        if (v->powerProfile)
            out << YAML::Key << YKeys::powerProfile << YAML::Value << *v->powerProfile;

        out << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::PkgCstConfigControl &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::packageCStateLimit << YAML::Value << v.packageCStateLimit
            << YAML::Key << YKeys::maxCoreCState << YAML::Value << v.maxCoreCState
            << YAML::Key << YKeys::ioMwaitRedirectionEnable << YAML::Value << v.ioMwaitRedirectionEnable
            << YAML::Key << YKeys::cfgLock << YAML::Value << v.cfgLock
            << YAML::Key << YKeys::c3StateAutodemotionEnable << YAML::Value << v.c3StateAutodemotionEnable
            << YAML::Key << YKeys::c1StateAutodemotionEnable << YAML::Value << v.c1StateAutodemotionEnable
            << YAML::Key << YKeys::c3UndemotionEnable << YAML::Value << v.c3UndemotionEnable
            << YAML::Key << YKeys::c1UndemotionEnable << YAML::Value << v.c1UndemotionEnable
            << YAML::Key << YKeys::pkgcAutodemotionEnable << YAML::Value << v.pkgcAutodemotionEnable
            << YAML::Key << YKeys::pkgcUndemotionEnable << YAML::Value << v.pkgcUndemotionEnable
            << YAML::Key << YKeys::timedMwaitEnable << YAML::Value << v.timedMwaitEnable
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::vector<Intel::MSRCore> &v) {
        out << YAML::BeginSeq;

        for (const Intel::MSRCore &core: v) {
            out << YAML::BeginMap;

            if (core.pkgCstConfigControl)
                out << YAML::Key << YKeys::pkgCstConfigControl << YAML::Value << *core.pkgCstConfigControl;

            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::HWPCapabilities &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::lowestPerf << YAML::Value << v.lowestPerf
            << YAML::Key << YKeys::highestPerf << YAML::Value << v.highestPerf
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::HWPRequestPkg &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::min << YAML::Value << v.min
            << YAML::Key << YKeys::max << YAML::Value << v.max
            << YAML::Key << YKeys::desired << YAML::Value << v.desired
            << YAML::Key << YKeys::epp << YAML::Value << v.epp
            << YAML::Key << YKeys::acw << YAML::Value << v.acw
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::HWPRequest &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::min << YAML::Value << v.requestPkg.min
            << YAML::Key << YKeys::max << YAML::Value << v.requestPkg.max
            << YAML::Key << YKeys::desired << YAML::Value << v.requestPkg.desired
            << YAML::Key << YKeys::epp << YAML::Value << v.requestPkg.epp
            << YAML::Key << YKeys::acw << YAML::Value << v.requestPkg.acw
            << YAML::Key << YKeys::packageControl << YAML::Value << v.packageControl
            << YAML::Key << YKeys::acwValid << YAML::Value << v.acwValid
            << YAML::Key << YKeys::eppValid << YAML::Value << v.eppValid
            << YAML::Key << YKeys::desiredValid << YAML::Value << v.desiredValid
            << YAML::Key << YKeys::maxValid << YAML::Value << v.maxValid
            << YAML::Key << YKeys::minValid << YAML::Value << v.minValid
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::vector<Intel::MSRThread> &v) {
        out << YAML::BeginSeq;

        for (const Intel::MSRThread &thread: v) {
            out << YAML::BeginMap;

            if (thread.hwpCapapabilities)
                out << YAML::Key << YKeys::hwpCapapabilities << YAML::Value << *thread.hwpCapapabilities;

            if (thread.hwpRequest)
                out << YAML::Key << YKeys::hwpRequest << YAML::Value << *thread.hwpRequest;

            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::PkgPowerLimit &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::pl1 << YAML::Value << v.pl1
            << YAML::Key << YKeys::pl2 << YAML::Value << v.pl2
            << YAML::Key << YKeys::pl1Time << YAML::Value << v.pl1Time
            << YAML::Key << YKeys::pl2Time << YAML::Value << v.pl2Time
            << YAML::Key << YKeys::pl1Clamp << YAML::Value << v.pl1Clamp
            << YAML::Key << YKeys::pl2Clamp << YAML::Value << v.pl2Clamp
            << YAML::Key << YKeys::pl1Enable << YAML::Value << v.pl1Enable
            << YAML::Key << YKeys::pl2Enable << YAML::Value << v.pl2Enable
            << YAML::Key << YKeys::lock << YAML::Value << v.lock
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::VRCurrentConfig &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::pl4 << YAML::Value << v.pl4
            << YAML::Key << YKeys::lock << YAML::Value << v.lock
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::PP1CurrentConfig &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::limit << YAML::Value << v.limit
            << YAML::Key << YKeys::lock << YAML::Value << v.lock
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::TurboPowerCurrentLimit &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::tdpLimit << YAML::Value << v.tdpLimit
            << YAML::Key << YKeys::tdpLimitOverride << YAML::Value << v.tdpLimitOverride
            << YAML::Key << YKeys::tdcLimit << YAML::Value << v.tdcLimit
            << YAML::Key << YKeys::tdcLimitOverride << YAML::Value << v.tdcLimitOverride
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::TurboRatioLimit &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::maxRatioLimit1C << YAML::Value << v.maxRatioLimit1C
            << YAML::Key << YKeys::maxRatioLimit2C << YAML::Value << v.maxRatioLimit2C
            << YAML::Key << YKeys::maxRatioLimit3C << YAML::Value << v.maxRatioLimit3C
            << YAML::Key << YKeys::maxRatioLimit4C << YAML::Value << v.maxRatioLimit4C
            << YAML::Key << YKeys::maxRatioLimit5C << YAML::Value << v.maxRatioLimit5C
            << YAML::Key << YKeys::maxRatioLimit6C << YAML::Value << v.maxRatioLimit6C
            << YAML::Key << YKeys::maxRatioLimit7C << YAML::Value << v.maxRatioLimit7C
            << YAML::Key << YKeys::maxRatioLimit8C << YAML::Value << v.maxRatioLimit8C
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::MiscProcFeatures &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::enhancedSpeedStep << YAML::Value << v.enhancedSpeedStep
            << YAML::Key << YKeys::disableTurboMode << YAML::Value << v.disableTurboMode
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::PowerCtl &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::bdProcHot << YAML::Value << v.bdProcHot
            << YAML::Key << YKeys::c1eEnable << YAML::Value << v.c1eEnable
            << YAML::Key << YKeys::sapmImcC2Policy << YAML::Value << v.sapmImcC2Policy
            << YAML::Key << YKeys::fastBrkSnpEn << YAML::Value << v.fastBrkSnpEn
            << YAML::Key << YKeys::powerPerformancePlatformOverride << YAML::Value << v.powerPerformancePlatformOverride
            << YAML::Key << YKeys::disableEnergyEfficiencyOpt << YAML::Value << v.disableEnergyEfficiencyOpt
            << YAML::Key << YKeys::disableRaceToHaltOpt << YAML::Value << v.disableRaceToHaltOpt
            << YAML::Key << YKeys::prochotOutputDisable << YAML::Value << v.prochotOutputDisable
            << YAML::Key << YKeys::prochotConfigurableResponseEnable << YAML::Value << v.prochotConfigurableResponseEnable
            << YAML::Key << YKeys::vrThermAlertDisableLock << YAML::Value << v.vrThermAlertDisableLock
            << YAML::Key << YKeys::vrThermAlertDisable << YAML::Value << v.vrThermAlertDisable
            << YAML::Key << YKeys::ringEEDisable << YAML::Value << v.ringEEDisable
            << YAML::Key << YKeys::saOptimizationDisable << YAML::Value << v.saOptimizationDisable
            << YAML::Key << YKeys::ookDisable << YAML::Value << v.ookDisable
            << YAML::Key << YKeys::hwpAutonomousDisable << YAML::Value << v.hwpAutonomousDisable
            << YAML::Key << YKeys::cstatePrewakeDisable << YAML::Value << v.cstatePrewakeDisable
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::MiscPwrMgmt &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::eistHWCoordinationDisable << YAML::Value << v.eistHWCoordinationDisable
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::FIVRControl &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::cpu << YAML::Value << v.cpu
            << YAML::Key << YKeys::gpu << YAML::Value << v.gpu
            << YAML::Key << YKeys::cpuCache << YAML::Value << v.cpuCache
            << YAML::Key << YKeys::unslice << YAML::Value << v.unslice
            << YAML::Key << YKeys::sysAgent << YAML::Value << v.sysAgent
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Intel::MCHBARPkgRaplLimit &v) {
        out << YAML::BeginMap
            << YAML::Key << YKeys::pl1 << YAML::Value << v.pl1
            << YAML::Key << YKeys::pl2 << YAML::Value << v.pl2
            << YAML::Key << YKeys::pl1Time << YAML::Value << v.pl1Time
            << YAML::Key << YKeys::pl1Clamp << YAML::Value << v.pl1Clamp
            << YAML::Key << YKeys::pl1Enable << YAML::Value << v.pl1Enable
            << YAML::Key << YKeys::pl2Enable << YAML::Value << v.pl2Enable
            << YAML::Key << YKeys::lock << YAML::Value << v.lock
            << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::optional<Intel::MSR> &v) {
        out << YAML::BeginMap;

        if (!v->cores.empty())
            out << YAML::Key << YKeys::cores << YAML::Value << v->cores;

        if (!v->threads.empty())
            out << YAML::Key << YKeys::threads << YAML::Value << v->threads;

        if (v->pkgPowerLimit)
            out << YAML::Key << YKeys::pkgPowerLimit << YAML::Value << *v->pkgPowerLimit;

        if (v->vrCurrentCfg)
            out << YAML::Key << YKeys::vrCurrentCfg << YAML::Value << *v->vrCurrentCfg;

        if (v->pp1CurrentCfg)
            out << YAML::Key << YKeys::pp1CurrentCfg << YAML::Value << *v->pp1CurrentCfg;

        if (v->turboPowerCurrentLimit)
            out << YAML::Key << YKeys::turboPowerCurrentLimit << YAML::Value << *v->turboPowerCurrentLimit;

        if (v->turboRatioLimit)
            out << YAML::Key << YKeys::turboRatioLimit << YAML::Value << *v->turboRatioLimit;

        if (v->miscProcFeatures)
            out << YAML::Key << YKeys::miscProcFeatures << YAML::Value << *v->miscProcFeatures;

        if (v->powerCtl)
            out << YAML::Key << YKeys::powerCtl << YAML::Value << *v->powerCtl;

        if (v->miscPwrMgmt)
            out << YAML::Key << YKeys::miscPwrMgmt << YAML::Value << *v->miscPwrMgmt;

        if (v->hwpRequestPkg)
            out << YAML::Key << YKeys::hwpRequestPkg << YAML::Value << *v->hwpRequestPkg;

        if (v->fivrData)
            out << YAML::Key << YKeys::fivrData << YAML::Value << *v->fivrData;

        if (v->pp0Priority)
            out << YAML::Key << YKeys::pp0Priority << YAML::Value << *v->pp0Priority;

        if (v->pp1Priority)
            out << YAML::Key << YKeys::pp1Priority << YAML::Value << *v->pp1Priority;

        if (v->energyPerfBias)
            out << YAML::Key << YKeys::energyPerfBias << YAML::Value << *v->energyPerfBias;

        if (v->hwpEnable)
            out << YAML::Key << YKeys::hwpEnable << YAML::Value << *v->hwpEnable;

        if (v->hwpPkgCtlPolarity)
            out << YAML::Key << YKeys::hwpPkgCtlPolarity << YAML::Value << *v->hwpPkgCtlPolarity;

        if (v->mchbarPkgRaplLimit)
            out << YAML::Key << YKeys::mchbarPkgRaplLimit << YAML::Value << *v->mchbarPkgRaplLimit;

        out << YAML::EndMap;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const std::vector<FAN::Fan> &v) {
        out << YAML::BeginSeq;

        for (const FAN::Fan &fan: v) {
            out << YAML::BeginMap
                << YAML::Key << YKeys::index << YAML::Value << fan.index;

            if (fan.mode)
                out << YAML::Key << YKeys::mode << YAML::Value << *fan.mode;

            if (!fan.curve.empty()) {
                out << YAML::Key << YKeys::curve << YAML::Value << YAML::BeginSeq;

                for (const auto &[temp, speed]: fan.curve)
                    out << YAML::Flow << YAML::BeginSeq << temp << speed << YAML::EndSeq;

                out << YAML::EndSeq;
            }

            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        return out;
    }

    static YAML::Emitter &operator<<(YAML::Emitter &out, const Error &v) {
        out << static_cast<int>(v);
        return out;
    }

    std::string serializeData(const DeviceData &data) {
        YAML::Emitter yaml;

        yaml << YAML::BeginMap
             << YAML::Key << YKeys::os << YAML::Value << static_cast<int>(data.os)
             << YAML::Key << YKeys::cpu << YAML::Value << static_cast<int>(data.cpu);

        if (data.daemonInfo)
            yaml << YAML::Key << YKeys::daemonInfo << YAML::Value << data.daemonInfo;

        if (data.systemInfo)
            yaml << YAML::Key << YKeys::systemInfo << YAML::Value << data.systemInfo;

        if (data.cpuInfo)
            yaml << YAML::Key << YKeys::cpuInfo << YAML::Value << data.cpuInfo;

        if (!data.gpusInfo.empty())
            yaml << YAML::Key << YKeys::gpuInfo << YAML::Value << data.gpusInfo;

        if (data.linuxSysFs)
            yaml << YAML::Key << YKeys::sysFs << YAML::Value << data.linuxSysFs;

        if (data.amdMsr)
            yaml << YAML::Key << YKeys::amdMsr << YAML::Value << data.amdMsr;

        if (data.intelMsr)
            yaml << YAML::Key << YKeys::intelMsr << YAML::Value << data.intelMsr;

        if (!data.fans.empty())
            yaml << YAML::Key << YKeys::fans << YAML::Value << data.fans;

        if (!data.profiles.empty())
            yaml << YAML::Key << YKeys::profiles << YAML::Value << data.profiles;

        if (!data.errors.empty())
            yaml << YAML::Key << YKeys::errors << YAML::Value << data.errors;

        yaml << YAML::EndMap;
        return yaml.c_str();
    }
}