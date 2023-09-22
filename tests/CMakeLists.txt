include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/*_test.cc
)

add_executable(
  ${PROJECT_NAME}_test 
  ${TEST_SOURCE_FILES}
)

target_link_libraries(
  ${PROJECT_NAME}_test
  ${PROJECT_NAME}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
