cmake_minimum_required(VERSION 3.21)
project(16_rest_client)

set(CMAKE_CXX_STANDARD 14)

if (APPLE)
    set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@1.1)
    include_directories(/opt/homebrew/opt/openssl@1.1/include)
    link_directories(/opt/homebrew/opt/openssl@1.1/lib)
endif (APPLE)

find_package(cpprestsdk REQUIRED)

add_executable(16_rest_client main.cpp)

target_link_libraries(16_rest_client PRIVATE cpprestsdk::cpprest)

# Additional libraries required for Unix (including Linux and macOS)
if (UNIX)
    target_link_libraries(16_rest_client PRIVATE crypto)
endif (UNIX)
