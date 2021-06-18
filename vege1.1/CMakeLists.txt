cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(vege)

set(Qt5_DIR /home/y3/Qt5.9.0/5.9/gcc_64/lib/cmake/Qt5)
set(Qt5Widgets_DIR /home/y3/Qt5.9.0/5.9/gcc_64/lib/cmake/Qt5Widgets)
set(Qt5Gui_DIR /home/y3/Qt5.9.0/5.9/gcc_64/lib/cmake/Qt5Gui)
set(Qt5Core_DIR /home/y3/Qt5.9.0/5.9/gcc_64/lib/cmake/Qt5Core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS} ")
set(Torch_DIR "/mnt/hgfs/vmgx/vege/ourvege/vege1.0/veges/libtorch/share/cmake/Torch")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Qt5 REQUIRED Widgets Core Gui)
qt5_wrap_ui(UI_HEADERS mainwindow.ui 
    drawing.ui 
    dialogw.ui)  # 通过 ui 文件生成对应的头文件
set_target_properties(Qt5::Core Qt5::Gui PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")


message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

message(STATUS "Torch library status:")
message(STATUS "    version: ${TORCH_VERSION}")
message(STATUS "    libraries: ${TORCH_LIBRARIES}")
message(STATUS "    include path: ${TORCH_INCLUDE_DIRS}")
set(lib_DIR /usr/lib/x84_64-linux-gnu)
link_directories(${lib_DIR})
include_directories(  ${OpenCV_INCLUDE_DIRS}  ${TORCH_INCLUDE_DIRS} ${JSON_INC_PATH} include)
add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    drawing.cpp 
    dialogw.cpp 
    drawing.h 
    header.h 
    dialogw.h 
    ${UI_HEADERS}
)

target_link_libraries(${PROJECT_NAME} "${TORCH_LIBRARIES}"  Qt5::Widgets Qt5::Core Qt5::Gui)

target_link_libraries(${PROJECT_NAME} ${TORCH_LIBRARIES} ${OpenCV_LIBS} ${jsoncpp_lib} libjsoncpp.a)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)


