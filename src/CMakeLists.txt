cmake_minimum_required(VERSION 3.20)

project(eosmechanics)

find_package(cdt)

add_contract( eosmechanics eosmechanics eosmechanics.cpp )
target_include_directories( eosmechanics PUBLIC ${CMAKE_SOURCE_DIR}/../include )