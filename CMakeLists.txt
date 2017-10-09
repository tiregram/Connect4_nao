
cmake_minimum_required(VERSION 2.8)
project(con4)
link_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule)

find_package(qibuild)
include_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule/include )
add_definitions("-D_GLIBCXX_USE_CXX11_ABI=0")
file(GLOB_RECURSE C4_NAO_FILE src/*.cpp)

qi_create_bin(a ${C4_NAO_FILE})
qi_use_lib(a ALCOMMON ALPROXIES CONNECT4_RULE)


