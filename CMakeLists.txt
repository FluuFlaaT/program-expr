cmake_minimum_required(VERSION 2.8...3.13)
project(netcafe_manager)

set(CMAKE_CXX_STANDARD 17)

include_directories(./src/include)

add_executable(netcafe_manager src/core/main.c src/core/menu.c src/core/service.c src/core/global.c )

add_subdirectory(./src/card)
add_subdirectory(./src/core)
add_subdirectory(./src/billing)

target_link_libraries(netcafe_manager Card Core Billing)