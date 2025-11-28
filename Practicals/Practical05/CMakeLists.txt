file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")

add_executable(Practical05 ${sourcefiles} ${inlinefiles} ${headerfiles})

target_link_libraries(Practical05 gtest)
target_link_libraries(Practical05 Utils)