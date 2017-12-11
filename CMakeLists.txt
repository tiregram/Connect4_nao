cmake_minimum_required(VERSION 2.8)
project (Connect4_nao)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-stdlib=libc++")
add_definitions("-D_GLIBCXX_USE_CXX11_ABI=0")

find_package(OpenCV REQUIRED)
find_package(qibuild)
find_package(Threads)

file(GLOB_RECURSE C4_NAO_FILE src/*.cpp)
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule/include )
include_directories( ${CMAKE_SOURCE_DIR}/../Connect4_cv/include )
include_directories( ${CMAKE_SOURCE_DIR}/../Connect4_cv/include )

link_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule)
link_directories( ${CMAKE_SOURCE_DIR}/../Connect4_cv)

qi_create_bin(c4nao ${C4_NAO_FILE})

target_link_libraries(c4nao c4rule)
target_link_libraries(c4nao ${OpenCV_LIBS})
target_link_libraries(c4nao c4_cv)
target_link_libraries(c4nao ${CMAKE_THREAD_LIBS_INIT})

qi_use_lib(c4nao ALCOMMON ALPROXIES)



