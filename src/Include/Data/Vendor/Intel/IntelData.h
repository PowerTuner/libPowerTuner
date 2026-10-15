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

#include <QList>

#include "IntelCoreData.h"
#include "IntelThreadData.h"
#include "../../../CPU/Intel/FIVRControlUV.h"
#include "../../../CPU/Intel/HWPRequestPkg.h"
#include "../../../CPU/Intel/MiscProcFeatures.h"
#include "../../../CPU/Intel/MiscPwrMgmt.h"
#include "../../../CPU/Intel/PkgPowerLimit.h"
#include "../../../CPU/Intel/PowerCtl.h"
#include "../../../CPU/Intel/PP1CurrentConfig.h"
#include "../../../CPU/Intel/TurboPowerCurrentLimit.h"
#include "../../../CPU/Intel/TurboRatioLimit.h"
#include "../../../CPU/Intel/VRCurrentConfig.h"
#include "../../../CPU/Intel/MCHBARPkgRaplLimit.h"

namespace PWTS::Intel {
    struct PWTSHARED_EXPORT [[nodiscard]] IntelData final {
        // package level
        RWData<PkgPowerLimit> pkgPowerLimit;
        RWData<VRCurrentConfig> vrCurrentCfg;
        RWData<PP1CurrentConfig> pp1CurrentCfg;
        RWData<TurboPowerCurrentLimit> turboPowerCurrentLimit;
        RWData<TurboRatioLimit> turboRatioLimit;
        RWData<MiscProcFeatures> miscProcFeatures;
        RWData<PowerCtl> powerCtl;
        RWData<MiscPwrMgmt> miscPwrMgmt;
        RWData<HWPRequestPkg> hwpRequestPkg;
        RWData<FIVRControlUV> undervoltData;
        RWData<int> pp0Priority;
        RWData<int> pp1Priority;
        RWData<int> energyPerfBias;
        RWData<int> hwpEnable;
        RWData<int> hwpPkgCtlPolarity;
        RWData<MCHBARPkgRaplLimit> mchbarPkgRaplLimit;

        // core level
        QList<IntelCoreData> coreData;

        // thread level
        QList<IntelThreadData> threadData;

        friend QDataStream &operator<<(QDataStream &ds, const IntelData &data) {
            ds << data.pkgPowerLimit <<
                data.vrCurrentCfg <<
                data.pp1CurrentCfg <<
                data.turboPowerCurrentLimit <<
                data.turboRatioLimit <<
                data.miscProcFeatures <<
                data.powerCtl <<
                data.miscPwrMgmt <<
                data.hwpRequestPkg <<
                data.undervoltData <<
                data.pp0Priority <<
                data.pp1Priority <<
                data.energyPerfBias <<
                data.hwpEnable <<
                data.hwpPkgCtlPolarity <<
                data.mchbarPkgRaplLimit <<
                data.coreData <<
                data.threadData;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, IntelData &data) {
            ds >> data.pkgPowerLimit >>
                data.vrCurrentCfg >>
                data.pp1CurrentCfg >>
                data.turboPowerCurrentLimit >>
                data.turboRatioLimit >>
                data.miscProcFeatures >>
                data.powerCtl >>
                data.miscPwrMgmt >>
                data.hwpRequestPkg >>
                data.undervoltData >>
                data.pp0Priority >>
                data.pp1Priority >>
                data.energyPerfBias >>
                data.hwpEnable >>
                data.hwpPkgCtlPolarity >>
                data.mchbarPkgRaplLimit >>
                data.coreData >>
                data.threadData;

            return ds;
        }
    };
}
