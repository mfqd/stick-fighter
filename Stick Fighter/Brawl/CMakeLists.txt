cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(Brawl)
add_executable(Brawl
        main.cpp
        utils.cpp utils.h
        bonhomme.cpp bonhomme.h)
ImagineUseModules(Brawl Graphics)
