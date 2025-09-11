# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appSkybox_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appSkybox_autogen.dir\\ParseCache.txt"
  "appSkybox_autogen"
  )
endif()
