find_package(GTest CONFIG REQUIRED)

add_executable(unittest unittest.cpp)
target_link_libraries(unittest PRIVATE libvscphelper GTest::gtest)
