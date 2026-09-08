cmake_minimum_required(VERSION 3.21)
project(APP)
file(GLOB sources src/*.cpp)
file(GLOB headers include/*.hpp)

include_directories(include/)

add_executable(${PROJECT_NAME} ${sources} ${headers}
        src/TempleAdventure.cpp
        include/TempleAdventure.hpp
        src/ApplicationController.cpp
        include/ApplicationController.hpp
        src/SceneController.cpp
        include/SceneController.hpp
        src/PlayerController.cpp
        include/PlayerController.hpp
        src/GuiController.cpp
        include/GuiController.hpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE matf-rg-engine)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
