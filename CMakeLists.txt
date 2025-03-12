cmake_minimum_required(VERSION 3.10.0)
project(TOUHOU VERSION 0.1.0 LANGUAGES C CXX)

#设置可执行程序
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

#查找库
set(SDL2_DIR "C:/Users/王已萌/Desktop/library2/Library/SDL2")
set(SDL2_image_DIR "C:/Users/王已萌/Desktop/library2/Library/SDL2_image")
set(SDL2_mixer_DIR "C:/Users/王已萌/Desktop/library2/Library/SDL2_mixer")
set(SDL2_ttf_DIR "C:/Users/王已萌/Desktop/library2/Library/SDL2_ttf")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED) 
find_package(SDL2_ttf REQUIRED)   


add_executable(TOUHOU   "src/main.cpp"
                        "src/Game.cpp"
                        "src/Scene.cpp"
                        "src/SceneMain.cpp" 
                        "src/GameEvent.cpp"
                        "src/SceneTitle.cpp"
                        "src/SceneEnd.cpp"
                        )

#链接库
target_link_libraries(TOUHOU SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer
SDL2_ttf::SDL2_ttf)

