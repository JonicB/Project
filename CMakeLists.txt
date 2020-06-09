cmake_minimum_required(VERSION 2.4)

project(CUBE)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

 
add_executable(main main.cpp Game.cpp GameEnd.cpp GameStart.cpp)
add_executable(game_test game_test.cpp Game.cpp GameEnd.cpp)
enable_testing()
add_test(game_test game_test)

find_package(SFML COMPONENTS graphics window system)
find_package(OpenGL)

target_link_libraries(main PUBLIC ${SFML_LIBRARIES} OpenGL::GL)
target_link_libraries(game_test PUBLIC ${SFML_LIBRARIES} OpenGL::GL)

include_directories(${SFML_INCLUDE_DIR})

enable_testing()
add_test(game_test game_test)