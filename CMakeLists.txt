cmake_minimum_required(VERSION 3.23)

project(libPowerTuner VERSION 2.0 DESCRIPTION "PowerTuner client and daemon shared library" LANGUAGES CXX)

set(PROJECT_AUTHOR "kylon")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OS_SRC "")

set(YAML_BUILD_SHARED_LIBS OFF)
add_subdirectory(src/extern/yaml-cpp EXCLUDE_FROM_ALL)

if (WIN32)
	configure_file(resources/cmake/windows/win.rc.in ${CMAKE_CURRENT_SOURCE_DIR}/win.rc)

	list(APPEND OS_SRC
		win.rc
	)
endif ()

add_library(${PROJECT_NAME} SHARED
    src/lib_export.h
    src/Features.h
    src/DaemonSettings.h
    src/DeviceData.h
    src/YamlKeys.h
    src/Utils.h
    src/Utils.cpp
    src/Serialize.h
    src/Serialize.cpp
    src/Deserialize.cpp

    src/enums/Error.h
    src/enums/OSType.h
    src/enums/CPUVendor.h
    src/enums/GPUVendor.h
    src/enums/Feature.h
    src/enums/LogLevel.h

    src/Info/SystemInfo.h
    src/Info/CPUInfo.h
    src/Info/GPUInfo.h
    src/Info/DaemonInfo.h

    src/OS/Linux/Includes/BlockDeviceQueueScheduler.h
    src/OS/Linux/Includes/MiscPMDevice.h
    src/OS/Linux/Includes/IntelGPU.h
    src/OS/Linux/Includes/AMDGPU.h
    src/OS/Linux/SysFs.h
    src/OS/Linux/CPUSysFs.h

    src/Vendor/Intel/Include/FIVRControl.h
    src/Vendor/Intel/Include/HWPCapabilities.h
    src/Vendor/Intel/Include/HWPRequest.h
    src/Vendor/Intel/Include/HWPRequestPkg.h
    src/Vendor/Intel/Include/MiscProcFeatures.h
    src/Vendor/Intel/Include/MiscPwrMgmt.h
    src/Vendor/Intel/Include/PkgPowerLimit.h
    src/Vendor/Intel/Include/PowerCtl.h
    src/Vendor/Intel/Include/PP1CurrentConfig.h
    src/Vendor/Intel/Include/TurboPowerCurrentLimit.h
    src/Vendor/Intel/Include/TurboRatioLimit.h
    src/Vendor/Intel/Include/VRCurrentConfig.h
    src/Vendor/Intel/Include/PkgCstConfigControl.h
    src/Vendor/Intel/Include/TemperatureTarget.h
    src/Vendor/Intel/Include/PkgThermalStatusInfo.h
    src/Vendor/Intel/Include/MCHBARPkgRaplLimit.h
    src/Vendor/Intel/MSR.h
    src/Vendor/Intel/MSRCore.h
    src/Vendor/Intel/MSRThread.h

    src/Vendor/AMD/Include/CPPCCapability1.h
    src/Vendor/AMD/Include/CPPCRequest.h
    src/Vendor/AMD/Include/PStateCurrentLimit.h
    src/Vendor/AMD/MSR.h
    src/Vendor/AMD/MSRCore.h
    src/Vendor/AMD/MSRThread.h

    src/FAN/Fan.h

    ${OS_SRC}
)
add_library("PWT::Lib" ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)

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
