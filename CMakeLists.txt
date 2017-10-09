cmake_minimum_required(VERSION 2.8)

project(con4)

find_package(qibuild)

# add this to avoid compilation error with c++11 because
# NAO is deprecated and is not C++ 11 compliant
add_definitions("-D_GLIBCXX_USE_CXX11_ABI=0")

# get all cpp file
file(GLOB_RECURSE C4_NAO_FILE src/*.cpp)

qi_create_bin(a ${C4_NAO_FILE})
qi_use_lib(a ALCOMMON ALPROXIES CONNECT4_RULE)


