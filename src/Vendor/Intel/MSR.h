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
#pragma once
#include <vector>

#include "MSRCore.h"
#include "MSRThread.h"
#include "Include/FIVRControl.h"
#include "Include/HWPRequestPkg.h"
#include "Include/MiscProcFeatures.h"
#include "Include/MiscPwrMgmt.h"
#include "Include/PkgPowerLimit.h"
#include "Include/PowerCtl.h"
#include "Include/PP1CurrentConfig.h"
#include "Include/TurboPowerCurrentLimit.h"
#include "Include/TurboRatioLimit.h"
#include "Include/VRCurrentConfig.h"
#include "Include/MCHBARPkgRaplLimit.h"

namespace LIBPWT::Intel {
    struct LIBPWT_EXPORT MSR final {
        std::vector<MSRCore> cores;
        std::vector<MSRThread> threads;
        std::optional<PkgPowerLimit> pkgPowerLimit;
        std::optional<VRCurrentConfig> vrCurrentCfg;
        std::optional<PP1CurrentConfig> pp1CurrentCfg;
        std::optional<TurboPowerCurrentLimit> turboPowerCurrentLimit;
        std::optional<TurboRatioLimit> turboRatioLimit;
        std::optional<MiscProcFeatures> miscProcFeatures;
        std::optional<PowerCtl> powerCtl;
        std::optional<MiscPwrMgmt> miscPwrMgmt;
        std::optional<HWPRequestPkg> hwpRequestPkg;
        std::optional<FIVRControl> fivrData;
        std::optional<int> pp0Priority;
        std::optional<int> pp1Priority;
        std::optional<int> energyPerfBias;
        std::optional<int> hwpEnable;
        std::optional<int> hwpPkgCtlPolarity;
        std::optional<MCHBARPkgRaplLimit> mchbarPkgRaplLimit;
    };
}
