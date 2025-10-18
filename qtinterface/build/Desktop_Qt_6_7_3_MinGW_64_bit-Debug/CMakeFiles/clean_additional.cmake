# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\copieeee_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\copieeee_autogen.dir\\ParseCache.txt"
  "copieeee_autogen"
  )
endif()
