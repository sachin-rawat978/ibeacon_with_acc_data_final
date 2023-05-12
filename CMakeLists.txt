# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(peripheral)

# set(PM_STATIC_YML_FILE
#   ${CMAKE_CURRENT_SOURCE_DIR}/boards/pm_static_${BOARD}.yml
#   )

target_sources(app PRIVATE
  src/main.c  
 )

# Include application application event headers
# zephyr_library_include_directories(src/events)

# NORDIC SDK APP START

# target_sources(app PRIVATE		
# 		src/events/config_event.c
# )

# target_sources(app PRIVATE		
# 		src/modules/sensor_simulated.c		
# )
# NORDIC SDK APP END

# # Preinitialization related to Thingy:53 DFU
# target_sources_ifdef(CONFIG_BOARD_THINGY53_NRF5340_CPUAPP app PRIVATE
#   boards/thingy53.c
# )
# target_sources_ifdef(CONFIG_BOARD_THINGY53_NRF5340_CPUAPP_NS app PRIVATE
#   boards/thingy53.c
# )

# Added External BSEC Library  
# set(LIB_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/BSEC_2.2.0.0_Generic_Release_30052022/algo/normal_version/bin/gcc/Cortex_M33F)
# target_include_directories(app PUBLIC ${LIB_DIR})

# zephyr_library_link_libraries(${LIB_DIR}/libalgobsec.a)