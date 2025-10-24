file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Practical02 ${sourcefiles} ${headerfiles})

target_link_libraries(Practical02 Utils)
