cmake_minimum_required(VERSION 3.13...3.27)

# set the SOURCE_CODE variable to the name of the C file
SET(SOURCE_CODE "code")

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
# or 
# include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${SOURCE_CODE}	C CXX ASM)

# Initialize the Raspberry Pi Pico PICO_SDK_PATH
pico_sdk_init()

add_executable(${SOURCE_CODE}
	${SOURCE_CODE}.c
	inc/ssd1306_i2c.c
)

pico_enable_stdio_uart(${SOURCE_CODE} 0)
pico_enable_stdio_usb(${SOURCE_CODE} 1)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${SOURCE_CODE} 
						pico_stdlib
						hardware_i2c
						hardware_adc)

# Create map/bin/hex/uf2 file in addition to ELF
pico_add_extra_outputs(${SOURCE_CODE})

	
message("PICO_SDK_PATH is set to: ${PICO_SDK_PATH}")
message("PICO_BOARD: ${PICO_BOARD}")










