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

#include "AMDCoreData.h"
#include "AMDThreadData.h"
#include "../../../CPU/AMD/PStateCurrentLimit.h"

namespace PWTS::AMD {
    struct PWTSHARED_EXPORT [[nodiscard]] AMDData final {
        // package level
        ROData<PStateCurrentLimit> pstateCurrentLimit;
        RWData<int> stapmLimit;
        RWData<int> fastLimit;
        RWData<int> slowLimit;
        RWData<int> tctlTemp;
        RWData<int> apuSlow;
        RWData<int> apuSkinTemp;
        RWData<int> dgpuSkinTemp;
        RWData<int> curveOptimizer;
        RWData<int> vrmCurrent;
        RWData<int> vrmSocCurrent;
        RWData<int> vrmMaxCurrent;
        RWData<int> vrmSocMaxCurrent;
        RWData<int> staticGfxClock;
        RWData<int> minGfxClock;
        RWData<int> maxGfxClock;
        RWData<int> powerProfile;
        RWData<int> cppcEnableBit;

        // core level
        QList<AMDCoreData> coreData;

        // thread level
        QList<AMDThreadData> threadData;

        friend QDataStream &operator<<(QDataStream &ds, const AMDData &data) {
            ds << data.pstateCurrentLimit <<
                data.stapmLimit <<
                data.fastLimit <<
                data.slowLimit <<
                data.tctlTemp <<
                data.apuSlow <<
                data.apuSkinTemp <<
                data.dgpuSkinTemp <<
                data.curveOptimizer <<
                data.vrmCurrent <<
                data.vrmSocCurrent <<
                data.vrmMaxCurrent <<
                data.vrmSocMaxCurrent <<
                data.staticGfxClock <<
                data.minGfxClock <<
                data.maxGfxClock <<
                data.powerProfile <<
                data.cppcEnableBit <<
                data.coreData <<
                data.threadData;

            return ds;
        }

        friend QDataStream &operator>>(QDataStream &ds, AMDData &data) {
            ds >> data.pstateCurrentLimit >>
                data.stapmLimit >>
                data.fastLimit >>
                data.slowLimit >>
                data.tctlTemp >>
                data.apuSlow >>
                data.apuSkinTemp >>
                data.dgpuSkinTemp >>
                data.curveOptimizer >>
                data.vrmCurrent >>
                data.vrmSocCurrent >>
                data.vrmMaxCurrent >>
                data.vrmSocMaxCurrent >>
                data.staticGfxClock >>
                data.minGfxClock >>
                data.maxGfxClock >>
                data.powerProfile >>
                data.cppcEnableBit >>
                data.coreData >>
                data.threadData;

            return ds;
        }
    };
}
