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

template<>
struct YAML::convert<LIBPWT::DaemonSettings> {
    static bool decode(const Node &node, LIBPWT::DaemonSettings &v) {
        const Node &startProfileN = node[LIBPWT::YKeys::startProfile];
        const Node &batteryProfileN = node[LIBPWT::YKeys::batteryProfile];
        const Node &psupplyProfileN = node[LIBPWT::YKeys::psupplyProfile];
        const Node &addressN = node[LIBPWT::YKeys::address];
        const Node &applyIntervalN = node[LIBPWT::YKeys::applyInterval];
        const Node &applyOnWakeFromSleepN = node[LIBPWT::YKeys::applyOnWake];
        const Node &ignoreBatteryEventN = node[LIBPWT::YKeys::ignoreBatteryEvt];
        const Node &logLvlN = node[LIBPWT::YKeys::logLevel];
        const Node &portN = node[LIBPWT::YKeys::port];

        if (startProfileN && startProfileN.IsScalar())
            v.startProfile = startProfileN.as<std::string>();

        if (batteryProfileN && batteryProfileN.IsScalar())
            v.batteryProfile = batteryProfileN.as<std::string>();

        if (psupplyProfileN && psupplyProfileN.IsScalar())
            v.powerSupplyProfile = psupplyProfileN.as<std::string>();

        if (addressN && addressN.IsScalar())
            v.address = addressN.as<std::string>();

        if (applyIntervalN && applyIntervalN.IsScalar())
            v.applyInterval = applyIntervalN.as<int>();

        if (applyOnWakeFromSleepN && applyOnWakeFromSleepN.IsScalar())
            v.applyOnWakeFromSleep = applyOnWakeFromSleepN.as<bool>();

        if (ignoreBatteryEventN && ignoreBatteryEventN.IsScalar())
            v.ignoreBatteryEvent = ignoreBatteryEventN.as<bool>();

        if (logLvlN && logLvlN.IsScalar())
            v.logLvl = static_cast<LIBPWT::LogLevel>(logLvlN.as<int>());

        if (portN && portN.IsScalar())
            v.port = static_cast<uint16_t>(portN.as<int>());

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Features> {
    static bool decode(const Node &node, LIBPWT::Features &v) {
        const Node &cpuN = node[LIBPWT::YKeys::cpu];
        const Node &gpuN = node[LIBPWT::YKeys::gpu];
        const Node &fanN = node[LIBPWT::YKeys::fan];

        if (cpuN && cpuN.IsSequence()) {
            for (const Node &feature: cpuN)
                v.cpu.insert(static_cast<LIBPWT::Feature>(feature.as<int>()));
        }

        if (gpuN && gpuN.IsMap()) {
            for (const detail::iterator_value &entry: gpuN) {
                if (!entry.first.IsScalar() || !entry.second.IsSequence())
                    return false;

                const int index = entry.first.as<int>();

                for (const Node &feature: entry.second)
                    v.gpu[index].insert(static_cast<LIBPWT::Feature>(feature.as<int>()));
            }
        }

        if (fanN && fanN.IsMap()) {
            for (const detail::iterator_value &entry: fanN) {
                if (!entry.first.IsScalar() || !entry.second.IsSequence())
                    return false;

                const int index = entry.first.as<int>();

                for (const Node &feature : entry.second)
                    v.fan[index].insert(static_cast<LIBPWT::Feature>(feature.as<int>()));
            }
        }

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::DaemonInfo> {
    static bool decode(const Node &node, LIBPWT::DaemonInfo &v) {
        const Node &verMajorN = node[LIBPWT::YKeys::versionMajor];
        const Node &verMinorN = node[LIBPWT::YKeys::versionMinor];
        const Node &dataPathN = node[LIBPWT::YKeys::dataPath];
        const Node &settingsN = node[LIBPWT::YKeys::settings];
        const Node &featuresN = node[LIBPWT::YKeys::features];

        if (verMajorN && verMajorN.IsScalar())
            v.versionMajor = verMajorN.as<int>();

        if (verMinorN && verMinorN.IsScalar())
            v.versionMinor = verMinorN.as<int>();

        if (dataPathN && dataPathN.IsScalar())
            v.dataPath = dataPathN.as<std::string>();

        if (settingsN && settingsN.IsMap())
            v.settings = settingsN.as<LIBPWT::DaemonSettings>();

        if (featuresN && featuresN.IsMap())
            v.features = node[LIBPWT::YKeys::features].as<LIBPWT::Features>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::SystemInfo> {
    static bool decode(const Node &node, LIBPWT::SystemInfo &v) {
        const Node &distributionN = node[LIBPWT::YKeys::distribution];
        const Node &kernelN = node[LIBPWT::YKeys::kernel];
        const Node &archN = node[LIBPWT::YKeys::arch];
        const Node &biosVersionN = node[LIBPWT::YKeys::biosVersion];
        const Node &biosVendorN = node[LIBPWT::YKeys::biosVendor];
        const Node &biosDateN = node[LIBPWT::YKeys::biosDate];
        const Node &ecVersionN = node[LIBPWT::YKeys::ecVersion];
        const Node &productN = node[LIBPWT::YKeys::product];
        const Node &manufacturerN = node[LIBPWT::YKeys::manufacturer];
        const Node &availableRamN = node[LIBPWT::YKeys::availableRam];
        const Node &swapMemoryN = node[LIBPWT::YKeys::swapMemory];

        if (distributionN && distributionN.IsScalar())
            v.distribution = distributionN.as<std::string>();

        if (kernelN && kernelN.IsScalar())
            v.kernel = kernelN.as<std::string>();

        if (archN && archN.IsScalar())
            v.arch = archN.as<std::string>();

        if (biosVersionN && biosVersionN.IsScalar())
            v.biosVersion = biosVersionN.as<std::string>();

        if (biosVendorN && biosVendorN.IsScalar())
            v.biosVendor = biosVendorN.as<std::string>();

        if (biosDateN && biosDateN.IsScalar())
            v.biosDate = biosDateN.as<std::string>();

        if (ecVersionN && ecVersionN.IsScalar())
            v.ecVersion = ecVersionN.as<std::string>();

        if (productN && productN.IsScalar())
            v.product = productN.as<std::string>();

        if (manufacturerN && manufacturerN.IsScalar())
            v.manufacturer = manufacturerN.as<std::string>();

        if (availableRamN && availableRamN.IsScalar())
            v.availableRam = availableRamN.as<std::string>();

        if (swapMemoryN && swapMemoryN.IsScalar())
            v.swapMemory = swapMemoryN.as<std::string>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::CPUInfo> {
    static bool decode(const Node &node, LIBPWT::CPUInfo &v) {
        const Node &brandN = node[LIBPWT::YKeys::brand];
        const Node &codenameN = node[LIBPWT::YKeys::codename];
        const Node &techNodeN = node[LIBPWT::YKeys::techNode];
        const Node &CPUStringN = node[LIBPWT::YKeys::CPUString];
        const Node &modelN = node[LIBPWT::YKeys::model];
        const Node &extModelN = node[LIBPWT::YKeys::extModel];
        const Node &familyN = node[LIBPWT::YKeys::family];
        const Node &extFamilyN = node[LIBPWT::YKeys::extFamily];
        const Node &coresN = node[LIBPWT::YKeys::cores];
        const Node &threadsN = node[LIBPWT::YKeys::threads];
        const Node &steppingN = node[LIBPWT::YKeys::stepping];
        const Node &l1DCacheN = node[LIBPWT::YKeys::l1DCache];
        const Node &l1ICacheN = node[LIBPWT::YKeys::l1ICache];
        const Node &l2CacheN = node[LIBPWT::YKeys::l2Cache];
        const Node &l3CacheN = node[LIBPWT::YKeys::l3Cache];
        const Node &l4CacheN = node[LIBPWT::YKeys::l4Cache];

        if (brandN && brandN.IsScalar())
            v.brand = brandN.as<std::string>();

        if (codenameN && codenameN.IsScalar())
            v.codename = codenameN.as<std::string>();

        if (techNodeN && techNodeN.IsScalar())
            v.techNode = techNodeN.as<std::string>();

        if (CPUStringN && CPUStringN.IsScalar())
            v.CPUString = CPUStringN.as<std::string>();

        if (modelN && modelN.IsScalar())
            v.model = modelN.as<int>();

        if (extModelN && extModelN.IsScalar())
            v.extModel = extModelN.as<int>();

        if (familyN && familyN.IsScalar())
            v.family = familyN.as<int>();

        if (extFamilyN && extFamilyN.IsScalar())
            v.extFamily = extFamilyN.as<int>();

        if (coresN && coresN.IsScalar())
            v.cores = coresN.as<int>();

        if (threadsN && threadsN.IsScalar())
            v.threads = threadsN.as<int>();

        if (steppingN && steppingN.IsScalar())
            v.stepping = steppingN.as<int>();

        if (l1DCacheN && l1DCacheN.IsScalar())
            v.l1DCache = l1DCacheN.as<std::string>();

        if (l1ICacheN && l1ICacheN.IsScalar())
            v.l1ICache = l1ICacheN.as<std::string>();

        if (l2CacheN && l2CacheN.IsScalar())
            v.l2Cache = l2CacheN.as<std::string>();

        if (l3CacheN && l3CacheN.IsScalar())
            v.l3Cache = l3CacheN.as<std::string>();

        if (l4CacheN && l4CacheN.IsScalar())
            v.l4Cache = l4CacheN.as<std::string>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::GPUInfo> {
    static bool decode(const Node &node, LIBPWT::GPUInfo &v) {
        const Node &vendorN = node[LIBPWT::YKeys::vendor];
        const Node &deviceIDN = node[LIBPWT::YKeys::deviceID];
        const Node &revisionIDN = node[LIBPWT::YKeys::revisionID];
        const Node &biosVersionN = node[LIBPWT::YKeys::biosVersion];
        const Node &indexN = node[LIBPWT::YKeys::index];

        if (vendorN && vendorN.IsScalar())
            v.vendor = static_cast<LIBPWT::GPUVendor>(vendorN.as<int>());

        if (deviceIDN && deviceIDN.IsScalar())
            v.deviceID = deviceIDN.as<std::string>();

        if (revisionIDN && revisionIDN.IsScalar())
            v.revisionID = revisionIDN.as<std::string>();

        if (biosVersionN && biosVersionN.IsScalar())
            v.biosVersion = biosVersionN.as<std::string>();

        if (indexN && indexN.IsScalar())
            v.index = indexN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::LNX::CPUSysFs> {
    static bool decode(const Node &node, LIBPWT::LNX::CPUSysFs &v) {
        const Node &microcodeN = node[LIBPWT::YKeys::microcode];
        const Node &onlineN = node[LIBPWT::YKeys::online];
        const Node &affectedCPUsN = node[LIBPWT::YKeys::affectedCPUs];
        const Node &cpuinfoMaxFreqN = node[LIBPWT::YKeys::cpuinfoMaxFreq];
        const Node &cpuinfoMinFreqN = node[LIBPWT::YKeys::cpuinfoMinFreq];
        const Node &scalingAvailableGovernorsN = node[LIBPWT::YKeys::scalingAvailableGovernors];
        const Node &scalingGovernorN = node[LIBPWT::YKeys::scalingGovernor];
        const Node &scalingMaxFreqN = node[LIBPWT::YKeys::scalingMaxFreq];
        const Node &scalingMinFreqN = node[LIBPWT::YKeys::scalingMinFreq];
        const Node &eppAvailablePreferencesN = node[LIBPWT::YKeys::energyPerformanceAvailablePreferences];
        const Node &eppN = node[LIBPWT::YKeys::energyPerformancePreference];

        if (microcodeN && microcodeN.IsScalar())
            v.microcode = microcodeN.as<int>();

        if (onlineN && onlineN.IsScalar())
            v.online = onlineN.as<bool>();

        if (affectedCPUsN && affectedCPUsN.IsSequence())
            v.affectedCPUs = affectedCPUsN.as<std::vector<int>>();

        if (cpuinfoMaxFreqN && cpuinfoMaxFreqN.IsScalar())
            v.cpuinfoMaxFreq = cpuinfoMaxFreqN.as<int>();

        if (cpuinfoMinFreqN && cpuinfoMinFreqN.IsScalar())
            v.cpuinfoMinFreq = cpuinfoMinFreqN.as<int>();

        if (scalingAvailableGovernorsN && scalingAvailableGovernorsN.IsSequence())
            v.scalingAvailableGovernors = scalingAvailableGovernorsN.as<std::vector<std::string>>();

        if (scalingGovernorN && scalingGovernorN.IsScalar())
            v.scalingGovernor = scalingGovernorN.as<std::string>();

        if (scalingMaxFreqN && scalingMaxFreqN.IsScalar())
            v.scalingMaxFreq = scalingMaxFreqN.as<int>();

        if (scalingMinFreqN && scalingMinFreqN.IsScalar())
            v.scalingMinFreq = scalingMinFreqN.as<int>();

        if (eppAvailablePreferencesN && eppAvailablePreferencesN.IsSequence())
            v.energyPerformanceAvailablePreferences = eppAvailablePreferencesN.as<std::vector<std::string>>();

        if (eppN && eppN.IsScalar())
            v.energyPerformancePreference = eppN.as<std::string>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::LNX::IntelGPU> {
    static bool decode(const Node &node, LIBPWT::Intel::LNX::IntelGPU &v) {
        const Node &gtMaxFreqMHzN = node[LIBPWT::YKeys::gtMaxFreqMHz];
        const Node &gtMinFreqMHzN = node[LIBPWT::YKeys::gtMinFreqMHz];
        const Node &gtRP0FreqMHzN = node[LIBPWT::YKeys::gtRP0FreqMHz];
        const Node &gtRPnFreqMHzN = node[LIBPWT::YKeys::gtRPnFreqMHz];
        const Node &gtBoostFreqMHzN = node[LIBPWT::YKeys::gtBoostFreqMHz];

        if (gtMaxFreqMHzN && gtMaxFreqMHzN.IsScalar())
            v.gtMaxFreqMHz = gtMaxFreqMHzN.as<int>();

        if (gtMinFreqMHzN && gtMinFreqMHzN.IsScalar())
            v.gtMinFreqMHz = gtMinFreqMHzN.as<int>();

        if (gtRP0FreqMHzN && gtRP0FreqMHzN.IsScalar())
            v.gtRP0FreqMHz = gtRP0FreqMHzN.as<int>();

        if (gtRPnFreqMHzN && gtRPnFreqMHzN.IsScalar())
            v.gtRPnFreqMHz = gtRPnFreqMHzN.as<int>();

        if (gtBoostFreqMHzN && gtBoostFreqMHzN.IsScalar())
            v.gtBoostFreqMHz = gtBoostFreqMHzN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::AMD::LNX::AMDGPU> {
    static bool decode(const Node &node, LIBPWT::AMD::LNX::AMDGPU &v) {
        const Node &sclkMaxFreqN = node[LIBPWT::YKeys::sclkMaxFreq];
        const Node &sclkMinFreqN = node[LIBPWT::YKeys::sclkMinFreq];
        const Node &powerDpmForcePerfLevelN = node[LIBPWT::YKeys::powerDpmForcePerfLevel];
        const Node &powerDpmStateN = node[LIBPWT::YKeys::powerDpmState];

        if (sclkMaxFreqN && sclkMaxFreqN.IsScalar())
            v.sclkMaxFreq = sclkMaxFreqN.as<int>();

        if (sclkMinFreqN && sclkMinFreqN.IsScalar())
            v.sclkMinFreq = sclkMinFreqN.as<int>();

        if (powerDpmForcePerfLevelN && powerDpmForcePerfLevelN.IsScalar())
            v.powerDpmForcePerfLevel = powerDpmForcePerfLevelN.as<std::string>();

        if (powerDpmStateN && powerDpmStateN.IsScalar())
            v.powerDpmState = powerDpmStateN.as<std::string>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::LNX::BlockDeviceQueueScheduler> {
    static bool decode(const Node &node, LIBPWT::LNX::BlockDeviceQueueScheduler &v) {
        const Node &deviceN = node[LIBPWT::YKeys::device];
        const Node &prettyNameN = node[LIBPWT::YKeys::prettyName];
        const Node &availableSchedulersN = node[LIBPWT::YKeys::availableSchedulers];
        const Node &schedulerN = node[LIBPWT::YKeys::scheduler];

        if (deviceN && deviceN.IsScalar())
            v.device = deviceN.as<std::string>();

        if (prettyNameN && prettyNameN.IsScalar())
            v.prettyName = prettyNameN.as<std::string>();

        if (availableSchedulersN && availableSchedulersN.IsSequence())
            v.availableSchedulers = availableSchedulersN.as<std::vector<std::string>>();

        if (schedulerN && schedulerN.IsScalar())
            v.scheduler = schedulerN.as<std::string>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::LNX::MiscPMDevice> {
    static bool decode(const Node &node, LIBPWT::LNX::MiscPMDevice &v) {
        const Node &nameN = node[LIBPWT::YKeys::name];
        const Node &controlN = node[LIBPWT::YKeys::control];
        const Node &controlValueN = node[LIBPWT::YKeys::controlValue];

        if (nameN && nameN.IsScalar())
            v.name = nameN.as<std::string>();

        if (controlN && controlN.IsScalar())
            v.control = controlN.as<std::string>();

        if (controlValueN && controlValueN.IsScalar())
            v.controlValue = controlValueN.as<std::string>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::LNX::SysFs> {
    static bool decode(const Node &node, LIBPWT::LNX::SysFs &v) {
        const Node &cpusN = node[LIBPWT::YKeys::cpus];
        const Node &intelGPUsN = node[LIBPWT::YKeys::intelGPUs];
        const Node &amdGPUsN = node[LIBPWT::YKeys::amdGPUs];
        const Node &smtControlN = node[LIBPWT::YKeys::smtControl];
        const Node &cpuIdleAvailableGovernorsN = node[LIBPWT::YKeys::cpuIdleAvailableGovernors];
        const Node &cpuIdleCurrentGovernorN = node[LIBPWT::YKeys::cpuIdleCurrentGovernor];
        const Node &blockDevicesQueSchedulerN = node[LIBPWT::YKeys::blockDevicesQueScheduler];
        const Node &miscPMDevicesN = node[LIBPWT::YKeys::miscPMDevices];
        const Node &amdPStateStatusN = node[LIBPWT::YKeys::amdPStateStatus];
        const Node &intelPStateMaxPerfPctN = node[LIBPWT::YKeys::intelPStateMaxPerfPct];
        const Node &intelPStateMinPerfPctN = node[LIBPWT::YKeys::intelPStateMinPerfPct];

        if (cpusN && cpusN.IsSequence())
            v.cpus = cpusN.as<std::vector<LIBPWT::LNX::CPUSysFs>>();

        if (intelGPUsN && intelGPUsN.IsMap()) {
            for (const detail::iterator_value &entry: intelGPUsN) {
                if (!entry.first.IsScalar() || !entry.second.IsMap())
                    return false;

                v.intelGPUs[entry.first.as<int>()] = entry.second.as<LIBPWT::Intel::LNX::IntelGPU>();
            }
        }

        if (amdGPUsN && amdGPUsN.IsMap()) {
            for (const detail::iterator_value &entry: amdGPUsN) {
                if (!entry.first.IsScalar() || !entry.second.IsMap())
                    return false;

                v.amdGPUs[entry.first.as<int>()] = entry.second.as<LIBPWT::AMD::LNX::AMDGPU>();
            }
        }

        if (smtControlN && smtControlN.IsScalar())
            v.smtControl = smtControlN.as<std::string>();

        if (cpuIdleAvailableGovernorsN && cpuIdleAvailableGovernorsN.IsSequence())
            v.cpuIdleAvailableGovernors = cpuIdleAvailableGovernorsN.as<std::vector<std::string>>();

        if (cpuIdleCurrentGovernorN && cpuIdleCurrentGovernorN.IsScalar())
            v.cpuIdleCurrentGovernor = cpuIdleCurrentGovernorN.as<std::string>();

        if (blockDevicesQueSchedulerN && blockDevicesQueSchedulerN.IsSequence())
            v.blockDevicesQueScheduler = blockDevicesQueSchedulerN.as<std::vector<LIBPWT::LNX::BlockDeviceQueueScheduler>>();

        if (miscPMDevicesN && miscPMDevicesN.IsSequence())
            v.miscPMDevices = miscPMDevicesN.as<std::vector<LIBPWT::LNX::MiscPMDevice>>();

        if (amdPStateStatusN && amdPStateStatusN.IsScalar())
            v.amdPStateStatus = amdPStateStatusN.as<std::string>();

        if (intelPStateMaxPerfPctN && intelPStateMaxPerfPctN.IsScalar())
            v.intelPStateMaxPerfPct = intelPStateMaxPerfPctN.as<int>();

        if (intelPStateMinPerfPctN && intelPStateMinPerfPctN.IsScalar())
            v.intelPStateMinPerfPct = intelPStateMinPerfPctN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::AMD::MSRCore> {
    static bool decode(const Node &node, LIBPWT::AMD::MSRCore &v) {
        const Node &curveOptimizerN = node[LIBPWT::YKeys::curveOptimizer];

        if (curveOptimizerN && curveOptimizerN.IsScalar())
            v.curveOptimizer = curveOptimizerN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::AMD::CPPCCapability1> {
    static bool decode(const Node &node, LIBPWT::AMD::CPPCCapability1 &v) {
        const Node &lowestPerfN = node[LIBPWT::YKeys::lowestPerf];
        const Node &lowNonLinearPerfN = node[LIBPWT::YKeys::lowNonLinearPerf];
        const Node &nominalPerfN = node[LIBPWT::YKeys::nominalPerf];
        const Node &highestPerfN = node[LIBPWT::YKeys::highestPerf];

        if (lowestPerfN && lowestPerfN.IsScalar())
            v.lowestPerf = lowestPerfN.as<int>();

        if (lowNonLinearPerfN && lowNonLinearPerfN.IsScalar())
            v.lowNonLinearPerf = lowNonLinearPerfN.as<int>();

        if (nominalPerfN && nominalPerfN.IsScalar())
            v.nominalPerf = nominalPerfN.as<int>();

        if (highestPerfN && highestPerfN.IsScalar())
            v.highestPerf = highestPerfN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::AMD::CPPCRequest> {
    static bool decode(const Node &node, LIBPWT::AMD::CPPCRequest &v) {
        const Node &maxPerfN = node[LIBPWT::YKeys::maxPerf];
        const Node &minPerfN = node[LIBPWT::YKeys::minPerf];
        const Node &desiredPerfN = node[LIBPWT::YKeys::desiredPerf];
        const Node &eppN = node[LIBPWT::YKeys::epp];

        if (maxPerfN && maxPerfN.IsScalar())
            v.maxPerf = maxPerfN.as<int>();

        if (minPerfN && minPerfN.IsScalar())
            v.minPerf = minPerfN.as<int>();

        if (desiredPerfN && desiredPerfN.IsScalar())
            v.desiredPerf = desiredPerfN.as<int>();

        if (eppN && eppN.IsScalar())
            v.epp = eppN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::AMD::MSRThread> {
    static bool decode(const Node &node, LIBPWT::AMD::MSRThread &v) {
        const Node &cppcCapability1N = node[LIBPWT::YKeys::cppcCapability1];
        const Node &cppcRequestN = node[LIBPWT::YKeys::cppcRequest];
        const Node &corePerfBoostN = node[LIBPWT::YKeys::corePerfBoost];
        const Node &pstateCmdN = node[LIBPWT::YKeys::pstateCmd];

        if (cppcCapability1N && cppcCapability1N.IsMap())
            v.cppcCapability1 = cppcCapability1N.as<LIBPWT::AMD::CPPCCapability1>();

        if (cppcRequestN && cppcRequestN.IsMap())
            v.cppcRequest = cppcRequestN.as<LIBPWT::AMD::CPPCRequest>();

        if (corePerfBoostN && corePerfBoostN.IsScalar())
            v.corePerfBoost = corePerfBoostN.as<int>();

        if (pstateCmdN && pstateCmdN.IsScalar())
            v.pstateCmd = pstateCmdN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::AMD::PStateCurrentLimit> {
    static bool decode(const Node &node, LIBPWT::AMD::PStateCurrentLimit &v) {
        const Node &curPStateLimitN = node[LIBPWT::YKeys::curPStateLimit];
        const Node &pstateMaxValueN = node[LIBPWT::YKeys::pstateMaxValue];

        if (curPStateLimitN && curPStateLimitN.IsScalar())
            v.curPStateLimit = curPStateLimitN.as<int>();

        if (pstateMaxValueN && pstateMaxValueN.IsScalar())
            v.pstateMaxValue = pstateMaxValueN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::AMD::MSR> {
    static bool decode(const Node &node, LIBPWT::AMD::MSR &v) {
        const Node &coresN = node[LIBPWT::YKeys::cores];
        const Node &threadsN = node[LIBPWT::YKeys::threads];
        const Node &pstateCurrentLimitN = node[LIBPWT::YKeys::pstateCurrentLimit];
        const Node &cppcEnableBitN = node[LIBPWT::YKeys::cppcEnableBit];
        const Node &stapmLimitN = node[LIBPWT::YKeys::stapmLimit];
        const Node &fastLimitN = node[LIBPWT::YKeys::fastLimit];
        const Node &slowLimitN = node[LIBPWT::YKeys::slowLimit];
        const Node &tctlTempN = node[LIBPWT::YKeys::tctlTemp];
        const Node &apuSlowN = node[LIBPWT::YKeys::apuSlow];
        const Node &apuSkinTempN = node[LIBPWT::YKeys::apuSkinTemp];
        const Node &dgpuSkinTempN = node[LIBPWT::YKeys::dgpuSkinTemp];
        const Node &curveOptimizerN = node[LIBPWT::YKeys::curveOptimizer];
        const Node &vrmCurrentN = node[LIBPWT::YKeys::vrmCurrent];
        const Node &vrmSocCurrentN = node[LIBPWT::YKeys::vrmSocCurrent];
        const Node &vrmMaxCurrentN = node[LIBPWT::YKeys::vrmMaxCurrent];
        const Node &vrmSocMaxCurrentN = node[LIBPWT::YKeys::vrmSocMaxCurrent];
        const Node &staticGfxClockN = node[LIBPWT::YKeys::staticGfxClock];
        const Node &minGfxClockN = node[LIBPWT::YKeys::minGfxClock];
        const Node &maxGfxClockN = node[LIBPWT::YKeys::maxGfxClock];
        const Node &powerProfileN = node[LIBPWT::YKeys::powerProfile];

        if (coresN && coresN.IsSequence())
            v.cores = coresN.as<std::vector<LIBPWT::AMD::MSRCore>>();

        if (threadsN && threadsN.IsSequence())
            v.threads = threadsN.as<std::vector<LIBPWT::AMD::MSRThread>>();

        if (pstateCurrentLimitN && pstateCurrentLimitN.IsMap())
            v.pstateCurrentLimit = pstateCurrentLimitN.as<LIBPWT::AMD::PStateCurrentLimit>();

        if (cppcEnableBitN && cppcEnableBitN.IsScalar())
            v.cppcEnableBit = cppcEnableBitN.as<int>();

        if (stapmLimitN && stapmLimitN.IsScalar())
            v.stapmLimit = stapmLimitN.as<int>();

        if (fastLimitN && fastLimitN.IsScalar())
            v.fastLimit = fastLimitN.as<int>();

        if (slowLimitN && slowLimitN.IsScalar())
            v.slowLimit = slowLimitN.as<int>();

        if (tctlTempN && tctlTempN.IsScalar())
            v.tctlTemp = tctlTempN.as<int>();

        if (apuSlowN && apuSlowN.IsScalar())
            v.apuSlow = apuSlowN.as<int>();

        if (apuSkinTempN && apuSkinTempN.IsScalar())
            v.apuSkinTemp = apuSkinTempN.as<int>();

        if (dgpuSkinTempN && dgpuSkinTempN.IsScalar())
            v.dgpuSkinTemp = dgpuSkinTempN.as<int>();

        if (curveOptimizerN && curveOptimizerN.IsScalar())
            v.curveOptimizer = curveOptimizerN.as<int>();

        if (vrmCurrentN && vrmCurrentN.IsScalar())
            v.vrmCurrent = vrmCurrentN.as<int>();

        if (vrmSocCurrentN && vrmSocCurrentN.IsScalar())
            v.vrmSocCurrent = vrmSocCurrentN.as<int>();

        if (vrmMaxCurrentN && vrmMaxCurrentN.IsScalar())
            v.vrmMaxCurrent = vrmMaxCurrentN.as<int>();

        if (vrmSocMaxCurrentN && vrmSocMaxCurrentN.IsScalar())
            v.vrmSocMaxCurrent = vrmSocMaxCurrentN.as<int>();

        if (staticGfxClockN && staticGfxClockN.IsScalar())
            v.staticGfxClock = staticGfxClockN.as<int>();

        if (minGfxClockN && minGfxClockN.IsScalar())
            v.minGfxClock = minGfxClockN.as<int>();

        if (maxGfxClockN && maxGfxClockN.IsScalar())
            v.maxGfxClock = maxGfxClockN.as<int>();

        if (powerProfileN && powerProfileN.IsScalar())
            v.powerProfile = powerProfileN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::PkgPowerLimit> {
    static bool decode(const Node &node, LIBPWT::Intel::PkgPowerLimit &v) {
        const Node &pl1N = node[LIBPWT::YKeys::pl1];
        const Node &pl2N = node[LIBPWT::YKeys::pl2];
        const Node &pl1TimeN = node[LIBPWT::YKeys::pl1Time];
        const Node &pl2TimeN = node[LIBPWT::YKeys::pl2Time];
        const Node &pl1ClampN = node[LIBPWT::YKeys::pl1Clamp];
        const Node &pl2ClampN = node[LIBPWT::YKeys::pl2Clamp];
        const Node &pl1EnableN = node[LIBPWT::YKeys::pl1Enable];
        const Node &pl2EnableN = node[LIBPWT::YKeys::pl2Enable];
        const Node &lockN = node[LIBPWT::YKeys::lock];

        if (pl1N && pl1N.IsScalar())
            v.pl1 = pl1N.as<int>();

        if (pl2N && pl2N.IsScalar())
            v.pl2 = pl2N.as<int>();

        if (pl1TimeN && pl1TimeN.IsScalar())
            v.pl1Time = pl1TimeN.as<int>();

        if (pl2TimeN && pl2TimeN.IsScalar())
            v.pl2Time = pl2TimeN.as<int>();

        if (pl1ClampN && pl1ClampN.IsScalar())
            v.pl1Clamp = pl1ClampN.as<bool>();

        if (pl2ClampN && pl2ClampN.IsScalar())
            v.pl2Clamp = pl2ClampN.as<bool>();

        if (pl1EnableN && pl1EnableN.IsScalar())
            v.pl1Enable = pl1EnableN.as<bool>();

        if (pl2EnableN && pl2EnableN.IsScalar())
            v.pl2Enable = pl2EnableN.as<bool>();

        if (lockN && lockN.IsScalar())
            v.lock = lockN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::VRCurrentConfig> {
    static bool decode(const Node &node, LIBPWT::Intel::VRCurrentConfig &v) {
        const Node &pl4N = node[LIBPWT::YKeys::pl4];
        const Node &lockN = node[LIBPWT::YKeys::lock];

        if (pl4N && pl4N.IsScalar())
            v.pl4 = pl4N.as<int>();

        if (lockN && lockN.IsScalar())
            v.lock = lockN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::PP1CurrentConfig> {
    static bool decode(const Node &node, LIBPWT::Intel::PP1CurrentConfig &v) {
        const Node &limitN = node[LIBPWT::YKeys::limit];
        const Node &lockN = node[LIBPWT::YKeys::lock];

        if (limitN && limitN.IsScalar())
            v.limit = limitN.as<int>();

        if (lockN && lockN.IsScalar())
            v.lock = lockN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::TurboPowerCurrentLimit> {
    static bool decode(const Node &node, LIBPWT::Intel::TurboPowerCurrentLimit &v) {
        const Node &tdpLimitN = node[LIBPWT::YKeys::tdpLimit];
        const Node &tdpLimitOverrideN = node[LIBPWT::YKeys::tdpLimitOverride];
        const Node &tdcLimitN = node[LIBPWT::YKeys::tdcLimit];
        const Node &tdcLimitOverrideN = node[LIBPWT::YKeys::tdcLimitOverride];

        if (tdpLimitN && tdpLimitN.IsScalar())
            v.tdpLimit = tdpLimitN.as<int>();

        if (tdpLimitOverrideN && tdpLimitOverrideN.IsScalar())
            v.tdpLimitOverride = tdpLimitOverrideN.as<bool>();

        if (tdcLimitN && tdcLimitN.IsScalar())
            v.tdcLimit = tdcLimitN.as<int>();

        if (tdcLimitOverrideN && tdcLimitOverrideN.IsScalar())
            v.tdcLimitOverride = tdcLimitOverrideN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::TurboRatioLimit> {
    static bool decode(const Node &node, LIBPWT::Intel::TurboRatioLimit &v) {
        const Node &maxRatioLimit1CN = node[LIBPWT::YKeys::maxRatioLimit1C];
        const Node &maxRatioLimit2CN = node[LIBPWT::YKeys::maxRatioLimit2C];
        const Node &maxRatioLimit3CN = node[LIBPWT::YKeys::maxRatioLimit3C];
        const Node &maxRatioLimit4CN = node[LIBPWT::YKeys::maxRatioLimit4C];
        const Node &maxRatioLimit5CN = node[LIBPWT::YKeys::maxRatioLimit5C];
        const Node &maxRatioLimit6CN = node[LIBPWT::YKeys::maxRatioLimit6C];
        const Node &maxRatioLimit7CN = node[LIBPWT::YKeys::maxRatioLimit7C];
        const Node &maxRatioLimit8CN = node[LIBPWT::YKeys::maxRatioLimit8C];

        if (maxRatioLimit1CN && maxRatioLimit1CN.IsScalar())
            v.maxRatioLimit1C = maxRatioLimit1CN.as<int>();

        if (maxRatioLimit2CN && maxRatioLimit2CN.IsScalar())
            v.maxRatioLimit2C = maxRatioLimit2CN.as<int>();

        if (maxRatioLimit3CN && maxRatioLimit3CN.IsScalar())
            v.maxRatioLimit3C = maxRatioLimit3CN.as<int>();

        if (maxRatioLimit4CN && maxRatioLimit4CN.IsScalar())
            v.maxRatioLimit4C = maxRatioLimit4CN.as<int>();

        if (maxRatioLimit5CN && maxRatioLimit5CN.IsScalar())
            v.maxRatioLimit5C = maxRatioLimit5CN.as<int>();

        if (maxRatioLimit6CN && maxRatioLimit6CN.IsScalar())
            v.maxRatioLimit6C = maxRatioLimit6CN.as<int>();

        if (maxRatioLimit7CN && maxRatioLimit7CN.IsScalar())
            v.maxRatioLimit7C = maxRatioLimit7CN.as<int>();

        if (maxRatioLimit8CN && maxRatioLimit8CN.IsScalar())
            v.maxRatioLimit8C = maxRatioLimit8CN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::MiscProcFeatures> {
    static bool decode(const Node &node, LIBPWT::Intel::MiscProcFeatures &v) {
        const Node &enhancedSpeedStepN = node[LIBPWT::YKeys::enhancedSpeedStep];
        const Node &disableTurboModeN = node[LIBPWT::YKeys::disableTurboMode];

        if (enhancedSpeedStepN && enhancedSpeedStepN.IsScalar())
            v.enhancedSpeedStep = enhancedSpeedStepN.as<bool>();

        if (disableTurboModeN && disableTurboModeN.IsScalar())
            v.disableTurboMode = disableTurboModeN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::PowerCtl> {
    static bool decode(const Node &node, LIBPWT::Intel::PowerCtl &v) {
        const Node &bdProcHotN = node[LIBPWT::YKeys::bdProcHot];
        const Node &c1eEnableN = node[LIBPWT::YKeys::c1eEnable];
        const Node &sapmImcC2PolicyN = node[LIBPWT::YKeys::sapmImcC2Policy];
        const Node &fastBrkSnpEnN = node[LIBPWT::YKeys::fastBrkSnpEn];
        const Node &powerPerformancePlatformOverrideN = node[LIBPWT::YKeys::powerPerformancePlatformOverride];
        const Node &disableEnergyEfficiencyOptN = node[LIBPWT::YKeys::disableEnergyEfficiencyOpt];
        const Node &disableRaceToHaltOptN = node[LIBPWT::YKeys::disableRaceToHaltOpt];
        const Node &prochotOutputDisableN = node[LIBPWT::YKeys::prochotOutputDisable];
        const Node &prochotConfigurableResponseEnableN = node[LIBPWT::YKeys::prochotConfigurableResponseEnable];
        const Node &vrThermAlertDisableLockN = node[LIBPWT::YKeys::vrThermAlertDisableLock];
        const Node &vrThermAlertDisableN = node[LIBPWT::YKeys::vrThermAlertDisable];
        const Node &ringEEDisableN = node[LIBPWT::YKeys::ringEEDisable];
        const Node &saOptimizationDisableN = node[LIBPWT::YKeys::saOptimizationDisable];
        const Node &ookDisableN = node[LIBPWT::YKeys::ookDisable];
        const Node &hwpAutonomousDisableN = node[LIBPWT::YKeys::hwpAutonomousDisable];
        const Node &cstatePrewakeDisableN = node[LIBPWT::YKeys::cstatePrewakeDisable];

        if (bdProcHotN && bdProcHotN.IsScalar())
            v.bdProcHot = bdProcHotN.as<bool>();

        if (c1eEnableN && c1eEnableN.IsScalar())
            v.c1eEnable = c1eEnableN.as<bool>();

        if (sapmImcC2PolicyN && sapmImcC2PolicyN.IsScalar())
            v.sapmImcC2Policy = sapmImcC2PolicyN.as<bool>();

        if (fastBrkSnpEnN && fastBrkSnpEnN.IsScalar())
            v.fastBrkSnpEn = fastBrkSnpEnN.as<bool>();

        if (powerPerformancePlatformOverrideN && powerPerformancePlatformOverrideN.IsScalar())
            v.powerPerformancePlatformOverride = powerPerformancePlatformOverrideN.as<bool>();

        if (disableEnergyEfficiencyOptN && disableEnergyEfficiencyOptN.IsScalar())
            v.disableEnergyEfficiencyOpt = disableEnergyEfficiencyOptN.as<bool>();

        if (disableRaceToHaltOptN && disableRaceToHaltOptN.IsScalar())
            v.disableRaceToHaltOpt = disableRaceToHaltOptN.as<bool>();

        if (prochotOutputDisableN && prochotOutputDisableN.IsScalar())
            v.prochotOutputDisable = prochotOutputDisableN.as<bool>();

        if (prochotConfigurableResponseEnableN && prochotConfigurableResponseEnableN.IsScalar())
            v.prochotConfigurableResponseEnable = prochotConfigurableResponseEnableN.as<bool>();

        if (vrThermAlertDisableLockN && vrThermAlertDisableLockN.IsScalar())
            v.vrThermAlertDisableLock = vrThermAlertDisableLockN.as<bool>();

        if (vrThermAlertDisableN && vrThermAlertDisableN.IsScalar())
            v.vrThermAlertDisable = vrThermAlertDisableN.as<bool>();

        if (ringEEDisableN && ringEEDisableN.IsScalar())
            v.ringEEDisable = ringEEDisableN.as<bool>();

        if (saOptimizationDisableN && saOptimizationDisableN.IsScalar())
            v.saOptimizationDisable = saOptimizationDisableN.as<bool>();

        if (ookDisableN && ookDisableN.IsScalar())
            v.ookDisable = ookDisableN.as<bool>();

        if (hwpAutonomousDisableN && hwpAutonomousDisableN.IsScalar())
            v.hwpAutonomousDisable = hwpAutonomousDisableN.as<bool>();

        if (cstatePrewakeDisableN && cstatePrewakeDisableN.IsScalar())
            v.cstatePrewakeDisable = cstatePrewakeDisableN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::MiscPwrMgmt> {
    static bool decode(const Node &node, LIBPWT::Intel::MiscPwrMgmt &v) {
        const Node &eistHWCoordinationDisableN = node[LIBPWT::YKeys::eistHWCoordinationDisable];

        if (eistHWCoordinationDisableN && eistHWCoordinationDisableN.IsScalar())
            v.eistHWCoordinationDisable = eistHWCoordinationDisableN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::HWPRequestPkg> {
    static bool decode(const Node &node, LIBPWT::Intel::HWPRequestPkg &v) {
        const Node &minN = node[LIBPWT::YKeys::min];
        const Node &maxN = node[LIBPWT::YKeys::max];
        const Node &desiredN = node[LIBPWT::YKeys::desired];
        const Node &eppN = node[LIBPWT::YKeys::epp];
        const Node &acwN = node[LIBPWT::YKeys::acw];

        if (minN && minN.IsScalar())
            v.min = minN.as<int>();

        if (maxN && maxN.IsScalar())
            v.max = maxN.as<int>();

        if (desiredN && desiredN.IsScalar())
            v.desired = desiredN.as<int>();

        if (eppN && eppN.IsScalar())
            v.epp = eppN.as<int>();

        if (acwN && acwN.IsScalar())
            v.acw = acwN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::FIVRControl> {
    static bool decode(const Node &node, LIBPWT::Intel::FIVRControl &v) {
        const Node &cpuN = node[LIBPWT::YKeys::cpu];
        const Node &gpuN = node[LIBPWT::YKeys::gpu];
        const Node &cpuCacheN = node[LIBPWT::YKeys::cpuCache];
        const Node &unsliceN = node[LIBPWT::YKeys::unslice];
        const Node &sysAgentN = node[LIBPWT::YKeys::sysAgent];

        if (cpuN && cpuN.IsScalar())
            v.cpu = cpuN.as<int>();

        if (gpuN && gpuN.IsScalar())
            v.gpu = gpuN.as<int>();

        if (cpuCacheN && cpuCacheN.IsScalar())
            v.cpuCache = cpuCacheN.as<int>();

        if (unsliceN && unsliceN.IsScalar())
            v.unslice = unsliceN.as<int>();

        if (sysAgentN && sysAgentN.IsScalar())
            v.sysAgent = sysAgentN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::MCHBARPkgRaplLimit> {
    static bool decode(const Node &node, LIBPWT::Intel::MCHBARPkgRaplLimit &v) {
        const Node &pl1N = node[LIBPWT::YKeys::pl1];
        const Node &pl2N = node[LIBPWT::YKeys::pl2];
        const Node &pl1TimeN = node[LIBPWT::YKeys::pl1Time];
        const Node &pl1ClampN = node[LIBPWT::YKeys::pl1Clamp];
        const Node &pl1EnableN = node[LIBPWT::YKeys::pl1Enable];
        const Node &pl2EnableN = node[LIBPWT::YKeys::pl2Enable];
        const Node &lockN = node[LIBPWT::YKeys::lock];

        if (pl1N && pl1N.IsScalar())
            v.pl1 = pl1N.as<int>();

        if (pl2N && pl2N.IsScalar())
            v.pl2 = pl2N.as<int>();

        if (pl1TimeN && pl1TimeN.IsScalar())
            v.pl1Time = pl1TimeN.as<int>();

        if (pl1ClampN && pl1ClampN.IsScalar())
            v.pl1Clamp = pl1ClampN.as<bool>();

        if (pl1EnableN && pl1EnableN.IsScalar())
            v.pl1Enable = pl1EnableN.as<bool>();

        if (pl2EnableN && pl2EnableN.IsScalar())
            v.pl2Enable = pl2EnableN.as<bool>();

        if (lockN && lockN.IsScalar())
            v.lock = lockN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::PkgCstConfigControl> {
    static bool decode(const Node &node, LIBPWT::Intel::PkgCstConfigControl &v) {
        const Node &packageCStateLimitN = node[LIBPWT::YKeys::packageCStateLimit];
        const Node &maxCoreCStateN = node[LIBPWT::YKeys::maxCoreCState];
        const Node &ioMwaitRedirectionEnableN = node[LIBPWT::YKeys::ioMwaitRedirectionEnable];
        const Node &cfgLockN = node[LIBPWT::YKeys::cfgLock];
        const Node &c3StateAutodemotionEnableN = node[LIBPWT::YKeys::c3StateAutodemotionEnable];
        const Node &c1StateAutodemotionEnableN = node[LIBPWT::YKeys::c1StateAutodemotionEnable];
        const Node &c3UndemotionEnableN = node[LIBPWT::YKeys::c3UndemotionEnable];
        const Node &c1UndemotionEnableN = node[LIBPWT::YKeys::c1UndemotionEnable];
        const Node &pkgcAutodemotionEnableN = node[LIBPWT::YKeys::pkgcAutodemotionEnable];
        const Node &pkgcUndemotionEnableN = node[LIBPWT::YKeys::pkgcUndemotionEnable];
        const Node &timedMwaitEnableN = node[LIBPWT::YKeys::timedMwaitEnable];

        if (packageCStateLimitN && packageCStateLimitN.IsScalar())
            v.packageCStateLimit = packageCStateLimitN.as<short>();

        if (maxCoreCStateN && maxCoreCStateN.IsScalar())
            v.maxCoreCState = maxCoreCStateN.as<short>();

        if (ioMwaitRedirectionEnableN && ioMwaitRedirectionEnableN.IsScalar())
            v.ioMwaitRedirectionEnable = ioMwaitRedirectionEnableN.as<bool>();

        if (cfgLockN && cfgLockN.IsScalar())
            v.cfgLock = cfgLockN.as<bool>();

        if (c3StateAutodemotionEnableN && c3StateAutodemotionEnableN.IsScalar())
            v.c3StateAutodemotionEnable = c3StateAutodemotionEnableN.as<bool>();

        if (c1StateAutodemotionEnableN && c1StateAutodemotionEnableN.IsScalar())
            v.c1StateAutodemotionEnable = c1StateAutodemotionEnableN.as<bool>();

        if (c3UndemotionEnableN && c3UndemotionEnableN.IsScalar())
            v.c3UndemotionEnable = c3UndemotionEnableN.as<bool>();

        if (c1UndemotionEnableN && c1UndemotionEnableN.IsScalar())
            v.c1UndemotionEnable = c1UndemotionEnableN.as<bool>();

        if (pkgcAutodemotionEnableN && pkgcAutodemotionEnableN.IsScalar())
            v.pkgcAutodemotionEnable = pkgcAutodemotionEnableN.as<bool>();

        if (pkgcUndemotionEnableN && pkgcUndemotionEnableN.IsScalar())
            v.pkgcUndemotionEnable = pkgcUndemotionEnableN.as<bool>();

        if (timedMwaitEnableN && timedMwaitEnableN.IsScalar())
            v.timedMwaitEnable = timedMwaitEnableN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::HWPCapabilities> {
    static bool decode(const Node &node, LIBPWT::Intel::HWPCapabilities &v) {
        const Node &lowestPerfN = node[LIBPWT::YKeys::lowestPerf];
        const Node &highestPerfN = node[LIBPWT::YKeys::highestPerf];

        if (lowestPerfN && lowestPerfN.IsScalar())
            v.lowestPerf = lowestPerfN.as<int>();

        if (highestPerfN && highestPerfN.IsScalar())
            v.highestPerf = highestPerfN.as<int>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::HWPRequest> {
    static bool decode(const Node &node, LIBPWT::Intel::HWPRequest &v) {
        const Node &requestPkgN = node[LIBPWT::YKeys::requestPkg];
        const Node &packageControlN = node[LIBPWT::YKeys::packageControl];
        const Node &acwValidN = node[LIBPWT::YKeys::acwValid];
        const Node &eppValidN = node[LIBPWT::YKeys::eppValid];
        const Node &desiredValidN = node[LIBPWT::YKeys::desiredValid];
        const Node &maxValidN = node[LIBPWT::YKeys::maxValid];
        const Node &minValidN = node[LIBPWT::YKeys::minValid];

        if (requestPkgN && requestPkgN.IsMap())
            v.requestPkg = requestPkgN.as<LIBPWT::Intel::HWPRequestPkg>();

        if (packageControlN && packageControlN.IsScalar())
            v.packageControl = packageControlN.as<bool>();

        if (acwValidN && acwValidN.IsScalar())
            v.acwValid = acwValidN.as<bool>();

        if (eppValidN && eppValidN.IsScalar())
            v.eppValid = eppValidN.as<bool>();

        if (desiredValidN && desiredValidN.IsScalar())
            v.desiredValid = desiredValidN.as<bool>();

        if (maxValidN && maxValidN.IsScalar())
            v.maxValid = maxValidN.as<bool>();

        if (minValidN && minValidN.IsScalar())
            v.minValid = minValidN.as<bool>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::MSRCore> {
    static bool decode(const Node &node, LIBPWT::Intel::MSRCore &v) {
        const Node &pkgCstConfigControlN = node[LIBPWT::YKeys::pkgCstConfigControl];

        if (pkgCstConfigControlN && pkgCstConfigControlN.IsMap())
            v.pkgCstConfigControl = pkgCstConfigControlN.as<LIBPWT::Intel::PkgCstConfigControl>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::MSRThread> {
    static bool decode(const Node &node, LIBPWT::Intel::MSRThread &v) {
        const Node &hwpCapapabilitiesN = node[LIBPWT::YKeys::hwpCapapabilities];
        const Node &hwpRequestN = node[LIBPWT::YKeys::hwpRequest];

        if (hwpCapapabilitiesN && hwpCapapabilitiesN.IsMap())
            v.hwpCapapabilities = hwpCapapabilitiesN.as<LIBPWT::Intel::HWPCapabilities>();

        if (hwpRequestN && hwpRequestN.IsMap())
            v.hwpRequest = hwpRequestN.as<LIBPWT::Intel::HWPRequest>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Intel::MSR> {
    static bool decode(const Node &node, LIBPWT::Intel::MSR &v) {
        const Node &coresN = node[LIBPWT::YKeys::cores];
        const Node &threadsN = node[LIBPWT::YKeys::threads];
        const Node &pkgPowerLimitN = node[LIBPWT::YKeys::pkgPowerLimit];
        const Node &vrCurrentCfgN = node[LIBPWT::YKeys::vrCurrentCfg];
        const Node &pp1CurrentCfgN = node[LIBPWT::YKeys::pp1CurrentCfg];
        const Node &turboPowerCurrentLimitN = node[LIBPWT::YKeys::turboPowerCurrentLimit];
        const Node &turboRatioLimitN = node[LIBPWT::YKeys::turboRatioLimit];
        const Node &miscProcFeaturesN = node[LIBPWT::YKeys::miscProcFeatures];
        const Node &powerCtlN = node[LIBPWT::YKeys::powerCtl];
        const Node &miscPwrMgmtN = node[LIBPWT::YKeys::miscPwrMgmt];
        const Node &hwpRequestPkgN = node[LIBPWT::YKeys::hwpRequestPkg];
        const Node &fivrDataN = node[LIBPWT::YKeys::fivrData];
        const Node &pp0PriorityN = node[LIBPWT::YKeys::pp0Priority];
        const Node &pp1PriorityN = node[LIBPWT::YKeys::pp1Priority];
        const Node &energyPerfBiasN = node[LIBPWT::YKeys::energyPerfBias];
        const Node &hwpEnableN = node[LIBPWT::YKeys::hwpEnable];
        const Node &hwpPkgCtlPolarityN = node[LIBPWT::YKeys::hwpPkgCtlPolarity];
        const Node &mchbarPkgRaplLimitN = node[LIBPWT::YKeys::mchbarPkgRaplLimit];

        if (coresN && coresN.IsSequence())
            v.cores = coresN.as<std::vector<LIBPWT::Intel::MSRCore>>();

        if (threadsN && threadsN.IsSequence())
            v.threads = threadsN.as<std::vector<LIBPWT::Intel::MSRThread>>();

        if (pkgPowerLimitN && pkgPowerLimitN.IsMap())
            v.pkgPowerLimit = pkgPowerLimitN.as<LIBPWT::Intel::PkgPowerLimit>();

        if (vrCurrentCfgN && vrCurrentCfgN.IsMap())
            v.vrCurrentCfg = vrCurrentCfgN.as<LIBPWT::Intel::VRCurrentConfig>();

        if (pp1CurrentCfgN && pp1CurrentCfgN.IsMap())
            v.pp1CurrentCfg = pp1CurrentCfgN.as<LIBPWT::Intel::PP1CurrentConfig>();

        if (turboPowerCurrentLimitN && turboPowerCurrentLimitN.IsMap())
            v.turboPowerCurrentLimit = turboPowerCurrentLimitN.as<LIBPWT::Intel::TurboPowerCurrentLimit>();

        if (turboRatioLimitN && turboRatioLimitN.IsMap())
            v.turboRatioLimit = turboRatioLimitN.as<LIBPWT::Intel::TurboRatioLimit>();

        if (miscProcFeaturesN && miscProcFeaturesN.IsMap())
            v.miscProcFeatures = miscProcFeaturesN.as<LIBPWT::Intel::MiscProcFeatures>();

        if (powerCtlN && powerCtlN.IsMap())
            v.powerCtl = powerCtlN.as<LIBPWT::Intel::PowerCtl>();

        if (miscPwrMgmtN && miscPwrMgmtN.IsMap())
            v.miscPwrMgmt = miscPwrMgmtN.as<LIBPWT::Intel::MiscPwrMgmt>();

        if (hwpRequestPkgN && hwpRequestPkgN.IsMap())
            v.hwpRequestPkg = hwpRequestPkgN.as<LIBPWT::Intel::HWPRequestPkg>();

        if (fivrDataN && fivrDataN.IsMap())
            v.fivrData = fivrDataN.as<LIBPWT::Intel::FIVRControl>();

        if (pp0PriorityN && pp0PriorityN.IsScalar())
            v.pp0Priority = pp0PriorityN.as<int>();

        if (pp1PriorityN && pp1PriorityN.IsScalar())
            v.pp1Priority = pp1PriorityN.as<int>();

        if (energyPerfBiasN && energyPerfBiasN.IsScalar())
            v.energyPerfBias = energyPerfBiasN.as<int>();

        if (hwpEnableN && hwpEnableN.IsScalar())
            v.hwpEnable = hwpEnableN.as<int>();

        if (hwpPkgCtlPolarityN && hwpPkgCtlPolarityN.IsScalar())
            v.hwpPkgCtlPolarity = hwpPkgCtlPolarityN.as<int>();

        if (mchbarPkgRaplLimitN && mchbarPkgRaplLimitN.IsMap())
            v.mchbarPkgRaplLimit = mchbarPkgRaplLimitN.as<LIBPWT::Intel::MCHBARPkgRaplLimit>();

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::FAN::Fan> {
    static bool decode(const Node &node, LIBPWT::FAN::Fan &v) {
        const Node &indexN = node[LIBPWT::YKeys::index];
        const Node &modeN = node[LIBPWT::YKeys::mode];
        const Node &curveN = node[LIBPWT::YKeys::curve];

        if (indexN && indexN.IsScalar())
            v.index = indexN.as<int>();

        if (modeN && modeN.IsScalar())
            v.mode = modeN.as<int>();

        if (curveN && curveN.IsSequence()) {
            for (const Node &pointN: curveN) {
                if (!pointN.IsSequence() || pointN.size() != 2)
                    return false;

                v.curve.emplace_back(pointN[0].as<int>(), pointN[1].as<int>());
            }
        }

        return true;
    }
};

template<>
struct YAML::convert<LIBPWT::Error> {
    static bool decode(const Node &node, LIBPWT::Error &v) {
        if (!node.IsScalar())
            return false;

        v = static_cast<LIBPWT::Error>(node.as<int>());
        return true;
    }
};

namespace LIBPWT {
    DeviceData deserializeData(const std::string &yaml) {
        try {
            const YAML::Node node = YAML::Load(yaml);
            DeviceData data{};

            if (!node.IsMap())
                return data;

            const YAML::Node &osN = node[YKeys::os];
            const YAML::Node &cpuN = node[YKeys::cpu];
            const YAML::Node &daemonInfoN = node[YKeys::daemonInfo];
            const YAML::Node &systemInfoN = node[YKeys::systemInfo];
            const YAML::Node &cpuInfoN = node[YKeys::cpuInfo];
            const YAML::Node &gpusInfoN = node[YKeys::gpuInfo];
            const YAML::Node &linuxSysfsN = node[YKeys::sysFs];
            const YAML::Node &amdMsrN = node[YKeys::amdMsr];
            const YAML::Node &intelMsrN = node[YKeys::intelMsr];
            const YAML::Node &fansN = node[YKeys::fans];
            const YAML::Node &profilesN = node[YKeys::profiles];
            const YAML::Node &errorsN = node[YKeys::errors];

            if (osN && osN.IsScalar())
                data.os = static_cast<OSType>(osN.as<int>());

            if (cpuN && cpuN.IsScalar())
                data.cpu = static_cast<CPUVendor>(cpuN.as<int>());

            if (daemonInfoN && daemonInfoN.IsMap())
                data.daemonInfo = daemonInfoN.as<DaemonInfo>();

            if (systemInfoN && systemInfoN.IsMap())
                data.systemInfo = systemInfoN.as<SystemInfo>();

            if (cpuInfoN && cpuInfoN.IsMap())
                data.cpuInfo = cpuInfoN.as<CPUInfo>();

            if (gpusInfoN && gpusInfoN.IsSequence())
                data.gpusInfo = gpusInfoN.as<std::vector<GPUInfo>>();

            if (linuxSysfsN && linuxSysfsN.IsMap())
                data.linuxSysFs = linuxSysfsN.as<LNX::SysFs>();

            if (amdMsrN && amdMsrN.IsMap())
                data.amdMsr = amdMsrN.as<AMD::MSR>();

            if (intelMsrN && intelMsrN.IsMap())
                data.intelMsr = intelMsrN.as<Intel::MSR>();

            if (fansN && fansN.IsSequence())
                data.fans = fansN.as<std::vector<FAN::Fan>>();

            if (profilesN && profilesN.IsSequence())
                data.profiles = profilesN.as<std::vector<std::string>>();

            if (errorsN && errorsN.IsSequence())
                data.errors = errorsN.as<std::vector<Error>>();

            return data;

        } catch (const YAML::Exception &) {
            return {};
        }
    }
}
