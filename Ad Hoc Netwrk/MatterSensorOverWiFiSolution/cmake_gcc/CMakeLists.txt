# Define minimal required version of CMake.
cmake_minimum_required(VERSION "3.25")

# Project definition
project(MatterSensorOverWiFiSolution)

include(ExternalProject)

ExternalProject_Add(MatterSensorOverWiFi
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../MatterSensorOverWiFi/cmake_gcc
  BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/../MatterSensorOverWiFi/cmake_gcc/build
  CMAKE_ARGS --preset project
  BUILD_COMMAND ${CMAKE_COMMAND} --build . --config $<CONFIG>
  INSTALL_COMMAND ""
  BUILD_ALWAYS true
  USES_TERMINAL_BUILD 1
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../MatterSensorOverWiFi/cmake_gcc
)


set(post_build_command )


add_custom_target(postbuild ALL
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
    COMMAND ${post_build_command}
)

add_dependencies(postbuild MatterSensorOverWiFi)

# BEGIN_SIMPLICITY_STUDIO_METADATA=eJx1UWFPwjAU/CtNv7uifltQQpjGJRszFqImLyG1e0Bla5e2OIzxv1uBCST4sde7e+/ufVGe5o9ZOkonrzM+mSZpMeNFNp2kxXiWF8ldRmPaH2zqinygdcroG6CXUQ8oQS1NqfQiAEM+SlOgg1uwoPs5N9XaB6ojQaddvHEqkJbeNzFjbdtG7XVk7IJd9XqX7CXPuFxiLS6Udl5oicE7KGJtxqJG1wiJO0JmpPC7DY68nKrEm4ukqZlzrBsdoTQ2OG03IqTv9vj+HZCOmZtyXeETztGGROiIKsMAV8moNXa1HR+Vwgug7Eic5AnOlVa/Dv8r/gRB0ljzjtITHUIFei68R8tRO2OLUO2zulcheHXIOIoBpi6UDrBsALiqm0pJ5T+5X5fKAAxL8mAkGaNv7QrgnGMX8vzvSSR2kqnrjZ0U12eH224B+v0D3QLLIg===END_SIMPLICITY_STUDIO_METADATA