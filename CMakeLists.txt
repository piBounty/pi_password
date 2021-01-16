cmake_minimum_required(VERSION 3.0)

project(pi_password LANGUAGES C)

add_executable(pi_password main.c derive_key.c pi_password.c)

find_package(OpenSSL REQUIRED)

target_link_libraries(pi_password PRIVATE OpenSSL::Crypto)

install(TARGETS pi_password RUNTIME DESTINATION bin)
