cmake_minimum_required(VERSION "3.16.3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "./build/debug")

project(melon_example)

find_package(range-v3 REQUIRED)
find_package(fmt REQUIRED) 
find_package(melon REQUIRED)



# project name and configuration
add_executable(${PROJECT_NAME} "src/example.cpp")

target_link_libraries(${PROJECT_NAME} range-v3::range-v3)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} melon::melon)


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/melon)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/melon/include)