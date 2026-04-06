cmake_minimum_required(VERSION 3.21)
project(assignment_6_1)

set(CMAKE_CXX_STANDARD 14)

if (APPLE)
    set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@1.1)
    include_directories(/opt/homebrew/opt/openssl@1.1/include)
    link_directories(/opt/homebrew/opt/openssl@1.1/lib)
endif (APPLE)

find_package(cpprestsdk REQUIRED)

add_executable(assignment_6_1 main.cpp)

target_link_libraries(assignment_6_1 PRIVATE cpprestsdk::cpprest)

# Additional libraries required for Unix (including Linux and macOS)
if (UNIX)
    target_link_libraries(assignment_6_1 PRIVATE crypto)
endif (UNIX)