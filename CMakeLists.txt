cmake_minimum_required (VERSION 2.8.11)
project (Connect4_nao)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
#set(CMAKE_CXX_STANDARD 11)
# lib build

file(GLOB_RECURSE C4_NAO_FILE src/*.cpp)
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule/include )
link_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule)

add_executable(c4nao ${C4_NAO_FILE})
target_link_libraries(c4nao c4rule)









