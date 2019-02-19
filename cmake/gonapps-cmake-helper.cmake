macro(gonapps_setVersion version soversion)
set(version ${version})
set(soversion ${soversion})
string(REPLACE "." ";" version_list ${version})
list(GET version_list 0 version_major)
list(GET version_list 1 version_minor)
list(GET version_list 2 version_patch)
endmacro()

macro(gonapps_setBuildType)
option(BUILD_WITH_COVERAGE "Build with coverage" OFF)
if(${BUILD_WITH_COVERAGE})
  message("** Build with coverage")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
  set(CMAKE_BUILD_TYPE "Debug")
endif()
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "CMAKE_BUILD_TYPE" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "MinSizeRel" "Release" "RelWithDebInfo")
endif()
message("** Build type is ${CMAKE_BUILD_TYPE}")
string(TOUPPER ${CMAKE_BUILD_TYPE} build_type)
endmacro()

macro(gonapps_genAuthors)
execute_process(COMMAND git fetch --all)
execute_process(COMMAND sh -c "git branch -a | grep remotes/origin/master | wc -l" ERROR_QUIET OUTPUT_VARIABLE master_branch_exists)
if(master_branch_exists EQUAL 1)
  message("** Branch origin/master exists, enable automatic AUTHORS generation")
  execute_process(COMMAND git shortlog -nse --no-merges origin/master OUTPUT_FILE "${CMAKE_SOURCE_DIR}/AUTHORS")
endif()
endmacro()
