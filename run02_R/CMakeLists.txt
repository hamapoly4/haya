cmake_minimum_required(VERSION 2.8.3)

project(step1)

set(run02_R app.cpp)

find_package(OpenCV REQUIRED)

include_directories(
	${OpenCV_INCLUDE_DIRS}
)

add_executable(app
	${run02_R}
)

target_link_libraries(app
	${OpenCV_LIBRARIES}
)
