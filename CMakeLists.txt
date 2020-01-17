cmake_minimum_required(VERSION 3.14)

project(helloworld_ci_cd_test VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)

configure_file(version.h.vers ${PROJECT_SOURCE_DIR}/version.h)

add_executable(helloworld_ci_cd_test src/main.cpp)

add_library(helloworld_ci_cd_test_lib src/lib.cpp)

add_executable(unit_test_ci_cd src/test_version.cpp)

set_target_properties(
        helloworld_ci_cd_test helloworld_ci_cd_test_lib unit_test_ci_cd PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

set_target_properties(unit_test_ci_cd PROPERTIES
        COMPILE_DEFINiTIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(
        helloworld_ci_cd_test
        helloworld_ci_cd_test_lib
        Threads::Threads
)

target_link_libraries(
        unit_test_ci_cd
        ${Boost_LIBRARIES}
        helloworld_ci_cd_test_lib

)

install(TARGETS helloworld_ci_cd_test RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dimkysh@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHILIBDEPS ON)

include(CPack)

enable_testing()

add_test(unit_test unit_test_ci_cd)