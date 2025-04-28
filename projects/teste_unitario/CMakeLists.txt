cmake_minimum_required(VERSION 3.13...3.27)

# set the MAIN variable to the name of the C file
SET(MAIN "main")
SET(PICO_SDK_PATH "/home/daltro/pico-sdk")
SET(PICO_BOARD "pico_w")
SET(PICO_PLATFORM "rp2040")
SET(PICOTOOL_PATH "/usr/local/bin/picotool")

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
# or 
# include( ${PICO_SDK_PATH}/external/pico_sdk_import.cmake )

project(${MAIN}	C CXX ASM)

# Initialize the Raspberry Pi Pico PICO_SDK_PATH
pico_sdk_init()


# find_package(GTest REQUIRED)


add_executable(${MAIN}
	app/${MAIN}.c
	hal/temperature.c

)

pico_enable_stdio_uart(${MAIN} 0)
pico_enable_stdio_usb(${MAIN} 1)


# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${MAIN} 
						# ${GTEST_LIBRARIES}
						pico_stdlib
						hardware_adc
						)
include_directories (
	${GTEST_INCLUDE_DIRS}
	/usr/include 
	/user/local/include

	)

# include directories for header files
target_include_directories( ${MAIN} PRIVATE 
							include/

)

# Create map/bin/hex/uf2 file in addition to ELF
pico_add_extra_outputs(${MAIN})


# message("PICO_SDK_PATH is set to: ${PICO_SDK_PATH}")
# message("PICO_BOARD: ${PICO_BOARD}")










