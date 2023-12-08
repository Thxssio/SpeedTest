cmake_minimum_required(VERSION 3.0)

project(QRCodeDetect)

find_package(OpenCV REQUIRED)

add_executable(QRCodeDetect OpenCV.cpp)

target_link_libraries(QRCodeDetect PRIVATE ${OpenCV_LIBS})