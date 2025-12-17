# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PIPAOProj_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PIPAOProj_autogen.dir\\ParseCache.txt"
  "PIPAOProj_autogen"
  )
endif()
