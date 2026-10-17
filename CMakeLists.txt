cmake_minimum_required(VERSION 3.23)

project(libPowerTuner VERSION 2.0 DESCRIPTION "PowerTuner client and daemon shared library" LANGUAGES CXX)

set(PROJECT_AUTHOR "kylon")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(OS_SRC "")

find_package(Qt6 6 REQUIRED COMPONENTS Core Network)

if (WIN32)
	configure_file(resources/cmake/windows/win.rc.in ${CMAKE_CURRENT_SOURCE_DIR}/win.rc)

	list(APPEND OS_SRC
		win.rc
	)
endif ()

add_library(${PROJECT_NAME} SHARED
    src/lib_export.h
    src/Utils.h
    src/Utils.cpp

    src/enums/Error.h
    src/enums/OSType.h
    src/enums/CPUVendor.h
    src/enums/GPUVendor.h
    src/enums/Feature.h
    src/enums/LogLevel.h

    src/Info/SystemInfo.h
    src/Info/CPUInfo.h
    src/Info/GPUInfo.h

    src/Include/Features.h
    src/Include/DaemonSettings.h

    src/Include/CPU/Intel/FIVRControl.h
    src/Include/CPU/Intel/HWPCapabilities.h
    src/Include/CPU/Intel/HWPRequest.h
    src/Include/CPU/Intel/HWPRequestPkg.h
    src/Include/CPU/Intel/MiscProcFeatures.h
    src/Include/CPU/Intel/MiscPwrMgmt.h
    src/Include/CPU/Intel/PkgPowerLimit.h
    src/Include/CPU/Intel/PowerCtl.h
    src/Include/CPU/Intel/PP1CurrentConfig.h
    src/Include/CPU/Intel/TurboPowerCurrentLimit.h
    src/Include/CPU/Intel/TurboRatioLimit.h
    src/Include/CPU/Intel/VRCurrentConfig.h
    src/Include/CPU/Intel/PkgCstConfigControl.h
    src/Include/CPU/Intel/TemperatureTarget.h
    src/Include/CPU/Intel/PkgThermalStatusInfo.h
    src/Include/CPU/Intel/MCHBARPkgRaplLimit.h

    src/Include/CPU/AMD/CPPCCapability1.h
    src/Include/CPU/AMD/CPPCRequest.h
    src/Include/CPU/AMD/PStateCurrentLimit.h

    src/Include/OS/Linux/CPUFrequencyLimits.h
    src/Include/OS/Linux/CPUScalingAvailableGovernors.h
    src/Include/OS/Linux/BlockDeviceQueueScheduler.h
    src/Include/OS/Linux/MiscPMDevice.h
    src/Include/OS/Linux/Intel/GPURPSLimits.h
    src/Include/OS/Linux/AMD/PState.h
    src/Include/OS/Linux/AMD/GPUDPMForcePerfLevel.h
    src/Include/OS/Linux/AMD/GPUODRanges.h

    src/Include/Data/FAN/FanData.h

    src/Include/Packets/DeviceInfoPacket.h
    src/Include/Packets/ClientPacket.h
    src/Include/Packets/DaemonPacket.h

    src/Include/Data/OS/Linux/LinuxData.h
    src/Include/Data/OS/Linux/LinuxThreadData.h
    src/Include/Data/OS/Linux/AMDData.h
    src/Include/Data/OS/Linux/AMDThreadData.h
    src/Include/Data/OS/Linux/IntelGPUData.h
    src/Include/Data/OS/Linux/AMDGPUData.h

    src/Include/Data/Vendor/Intel/IntelData.h
    src/Include/Data/Vendor/Intel/CoreData.h
    src/Include/Data/Vendor/Intel/ThreadData.h

    src/Include/Data/Vendor/AMD/AMDData.h
    src/Include/Data/Vendor/AMD/CoreData.h
    src/Include/Data/Vendor/AMD/ThreadData.h

    ${OS_SRC}
)
add_library("PWT::Lib" ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Network)

if (WIN32)
	target_compile_definitions(${PROJECT_NAME} PUBLIC PWT_LIBRARY)
else ()
	target_compile_definitions(${PROJECT_NAME} PRIVATE PWT_LIBRARY)
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    CXX_VISIBLITY_PRESET hidden
    VISIBILITY_INLINE_HIDDEN TRUE
    PREFIX ""
)

include(CheckIPOSupported)
check_ipo_supported(RESULT has_ipo OUTPUT ipo_error)
if (has_ipo)
	message(STATUS "${PROJECT_NAME}: IPO/LTO enabled")
	set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
