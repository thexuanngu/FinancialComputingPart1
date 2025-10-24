file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Practical01 ${sourcefiles} ${headerfiles})

target_link_libraries(Practical01 Utils)
