
cmake_minimum_required(VERSION 3.17)
project(test)
find_package(OpenCV REQUIRED)
file(GLOB_RECURSE SRC src/*.cpp)
list(APPEND SRC "main.cpp") 
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC include)