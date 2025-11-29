file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")

add_executable(Practical07 ${sourcefiles} ${headerfiles})

target_link_libraries(Practical07 MCLib)
target_link_libraries(Practical07 Utils)
