cmake_minimum_required(VERSION 2.8)
project (Connect4_nao)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 11)
# lib build
find_package(OpenCV REQUIRED)
find_package(qibuild)
#set(opencv_LIBS "opencv_calib3d  opencv_core opencv_dnn opencv_features2d opencv_flann opencv_highgui opencv_imgcodecs opencv_imgproc opencv_ml opencv_objdetect opencv_photo opencv_shape opencv_stitching opencv_superres opencv_video opencv_videoio opencv_videostab")


file(GLOB_RECURSE C4_NAO_FILE src/*.cpp)
include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule/include )
include_directories( ${CMAKE_SOURCE_DIR}/../Connect4_cv/include )
link_directories( ${CMAKE_SOURCE_DIR}/../connect4_rule)
link_directories( ${CMAKE_SOURCE_DIR}/../Connect4_cv)
#message(${OpenCV_DIR})

#add_executable(c4nao ${C4_NAO_FILE})

qi_create_bin(c4nao ${C4_NAO_FILE})
target_link_libraries(c4nao c4rule)
target_link_libraries(c4nao ${OpenCV_LIBS})
target_link_libraries(c4nao c4_cv)

message(${OpenCV_LIBS})
qi_use_lib(c4nao ALCOMMON ALPROXIES)
add_definitions("-D_GLIBCXX_USE_CXX11_ABI=0")






