cmake_minimum_required (VERSION 3.8)

project (GameProxy VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file("GameProxyConfig.h.in" "GameProxyConfig.h")

add_subdirectory (Server)
target_include_directories(Server PRIVATE "${CMAKE_SOURCE_DIR}/asio/include")
target_include_directories(Server PUBLIC "${PROJECT_BINARY_DIR}")

add_subdirectory (Client)
target_include_directories(Client PRIVATE "${CMAKE_SOURCE_DIR}/asio/include")
target_include_directories(Client PUBLIC "${PROJECT_BINARY_DIR}")