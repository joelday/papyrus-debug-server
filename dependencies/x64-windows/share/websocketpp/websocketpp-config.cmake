# - Config file for the websocketpp package
# It defines the following variables
#  WEBSOCKETPP_FOUND - indicates that the module was found
#  WEBSOCKETPP_INCLUDE_DIR - include directories


macro(set_and_check)
  set(${ARGV})
endmacro()

set_and_check(WEBSOCKETPP_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../include")
set(WEBSOCKETPP_FOUND TRUE)

#This is a bit of a hack, but it works well. It also allows continued support of CMake 2.8
if(${CMAKE_VERSION} VERSION_GREATER 3.0.0 OR ${CMAKE_VERSION} VERSION_EQUAL 3.0.0)
  add_library(websocketpp::websocketpp INTERFACE IMPORTED)
  set_target_properties(websocketpp::websocketpp PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${WEBSOCKETPP_INCLUDE_DIR}")
endif()
