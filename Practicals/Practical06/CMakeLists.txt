file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Practical06 ${sourcefiles} ${headerfiles})

target_link_libraries(Practical06 Utils)
