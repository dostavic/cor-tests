set(BINARY InfilGenerator_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.hpp *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC InfilGenerator_lib gtest)
target_link_libraries(${BINARY} PUBLIC InfilGenerator_lib gmock)