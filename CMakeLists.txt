cmake_minimum_required(VERSION 3.2)     

project(Game001 CXX)  
          
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SOURCE_EXE Main.cpp)       

set(SOURCE_LIB GameObjects.h Logic.h Storage.h String.h Vector2f.h Manager.h Manager.cpp Storage.cpp Vector2f.cpp String.cpp GameObjects.cpp)            

add_library(foo STATIC ${SOURCE_LIB}) 

set_target_properties(foo PROPERTIES LINKER_LANGUAGE CXX)

add_executable(main ${SOURCE_EXE})   

target_link_libraries(main foo)       

target_link_libraries(main sfml-graphics sfml-audio)