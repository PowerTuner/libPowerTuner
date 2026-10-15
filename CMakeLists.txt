cmake_minimum_required(VERSION 3.23)

project(libPowerTuner VERSION 2.0 DESCRIPTION "PowerTuner client and daemon shared library" LANGUAGES CXX)

set(PROJECT_AUTHOR "kylon")
set(CMAKE_CXX_STANDARD 20)
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
    src/DaemonSettings.h
    src/DaemonSettings.cpp
    src/Utils.h
    src/Utils.cpp

    src/Include/LogLevel.h
    src/Include/Feature.h
    src/Include/Features.h
    src/Include/SystemInfo.h
    src/Include/DynamicSystemInfo.h
    src/Include/OSType.h
    src/Include/DaemonCMD.h
    src/Include/DaemonError.h
    src/Include/PacketError.h

    src/Include/Types/MinMax.h
    src/Include/Types/ROData.h
    src/Include/Types/RWData.h

    src/Include/OS/Linux/CPUFrequencyLimits.h
    src/Include/OS/Linux/CPUScalingAvailableGovernors.h
    src/Include/OS/Linux/BlockDeviceQueSched.h
    src/Include/OS/Linux/MiscPMDevice.h
    src/Include/OS/Linux/Intel/GPURPSLimits.h
    src/Include/OS/Linux/AMD/AMDPStateData.h
    src/Include/OS/Linux/AMD/GPUDPMForcePerfLevel.h
    src/Include/OS/Linux/AMD/GPUODRanges.h

    src/Include/OS/Windows/PowerScheme.h
    src/Include/OS/Windows/PowerSchemesData.h
    src/Include/OS/Windows/PowerSchemeSetting.h
    src/Include/OS/Windows/PowerSchemeSettingData.h
    src/Include/OS/Windows/PowerSettingValue.h

    src/Include/CPU/Intel/FIVRControlUV.h
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

    src/Include/CPU/CpuInfo.h
    src/Include/CPU/CPUVendor.h

    src/Include/GPU/GpuInfo.h
    src/Include/GPU/GPUVendor.h

    src/Include/Data/FAN/FanData.h

    src/Include/Packets/DeviceInfoPacket.h
    src/Include/Packets/ClientPacket.h
    src/Include/Packets/DaemonPacket.h

    src/Include/Data/OS/Linux/LinuxData.h
    src/Include/Data/OS/Linux/LinuxThreadData.h
    src/Include/Data/OS/Linux/LinuxAMDData.h
    src/Include/Data/OS/Linux/LinuxAMDThreadData.h
    src/Include/Data/OS/Linux/LinuxIntelGPUData.h
    src/Include/Data/OS/Linux/LinuxAMDGPUData.h

    src/Include/Data/OS/Windows/WindowsData.h

    src/Include/Data/Vendor/Intel/IntelData.h
    src/Include/Data/Vendor/Intel/IntelCoreData.h
    src/Include/Data/Vendor/Intel/IntelThreadData.h

    src/Include/Data/Vendor/AMD/AMDData.h
    src/Include/Data/Vendor/AMD/AMDCoreData.h
    src/Include/Data/Vendor/AMD/AMDThreadData.h

    ${OS_SRC}
)
add_library("PWT::Lib" ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Network)

if (WIN32)
	target_compile_definitions(${PROJECT_NAME} PUBLIC PWT_LIBRARY)
else ()
	target_compile_definitions(${PROJECT_NAME} PRIVATE PWT_LIBRARY)
endif ()

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

set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION}
	CXX_VISIBLITY_PRESET hidden
	VISIBILITY_INLINE_HIDDEN TRUE
    PREFIX ""
)
