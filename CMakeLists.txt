# cmake_minimum_required (VERSION 2.8.11)
# project (Connect4_nao)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
# # set(CMAKE_CXX_STANDARD 11)
# # lib build

# file(GLOB_RECURSE C4_NAO_FILE src/*.cpp)
# include_directories( ${CMAKE_SOURCE_DIR}/include )

# include_directories( ~/nao/ctc/libnaoqi/include)
# link_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule)

# #link_directories( ${CMAKE_SOURCE_DIR}/../NaoSDK/ctc-linux64-atom-2.1.4.13/libnaoqi/include)

# add_executable(c4nao ${C4_NAO_FILE})
# target_link_libraries(c4nao c4rule)

cmake_minimum_required(VERSION 3.8)
project(con4)
link_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule)

find_package(qibuild)
include_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule/include )
add_definitions("-D_GLIBCXX_USE_CXX11_ABI=0")
file(GLOB_RECURSE C4_NAO_FILE src/*.cpp)

qi_create_bin(a ${C4_NAO_FILE})
qi_use_lib(a ALCOMMON ALPROXIES CONNECT4_RULE)

