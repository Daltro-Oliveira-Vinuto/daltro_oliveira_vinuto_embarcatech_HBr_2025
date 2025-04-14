
if(NOT "/home/daltro/Codes/embedded/rp/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp/picotool-populate-gitinfo.txt" IS_NEWER_THAN "/home/daltro/Codes/embedded/rp/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp/picotool-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/daltro/Codes/embedded/rp/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp/picotool-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/daltro/Codes/embedded/rp/build/_deps/picotool-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/daltro/Codes/embedded/rp/build/_deps/picotool-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/bin/git"  clone --no-checkout --progress --config "advice.detachedHead=false" "https://github.com/raspberrypi/picotool.git" "picotool-src"
    WORKING_DIRECTORY "/home/daltro/Codes/embedded/rp/build/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/raspberrypi/picotool.git'")
endif()

execute_process(
  COMMAND "/bin/git"  checkout develop --
  WORKING_DIRECTORY "/home/daltro/Codes/embedded/rp/build/_deps/picotool-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'develop'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/daltro/Codes/embedded/rp/build/_deps/picotool-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/daltro/Codes/embedded/rp/build/_deps/picotool-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/daltro/Codes/embedded/rp/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp/picotool-populate-gitinfo.txt"
    "/home/daltro/Codes/embedded/rp/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp/picotool-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/daltro/Codes/embedded/rp/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp/picotool-populate-gitclone-lastrun.txt'")
endif()

