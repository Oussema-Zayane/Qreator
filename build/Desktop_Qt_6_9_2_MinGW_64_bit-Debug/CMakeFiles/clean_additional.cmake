# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\esprit_horizon_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\esprit_horizon_autogen.dir\\ParseCache.txt"
  "esprit_horizon_autogen"
  )
endif()
