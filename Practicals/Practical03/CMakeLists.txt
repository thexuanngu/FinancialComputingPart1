file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Practical03 ${sourcefiles} ${headerfiles})

target_link_libraries(Practical03 Utils)
