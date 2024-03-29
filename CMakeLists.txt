cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME BattleCity)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/Renderer/ShaderProgram.cpp
    src/Renderer/ShaderProgram.h
    src/Renderer/Texture2D.cpp
    src/Renderer/Texture2D.h
    src/Renderer/sprite.cpp
    src/Renderer/sprite.h
    src/Renderer/AnimatedSprite.cpp
    src/Renderer/AnimatedSprite.h
    src/Renderer/VertexBuffer.cpp
    src/Renderer/VertexBuffer.h
    src/Renderer/IndexBuffer.cpp
    src/Renderer/IndexBuffer.h
    src/Renderer/VertexArray.cpp
    src/Renderer/VertexArray.h
    src/Renderer/VertexBufferLayout.cpp
    src/Renderer/VertexBufferLayout.h
    src/Renderer/Renderer.cpp
    src/Renderer/Renderer.h
    src/Resources/ResourceManager.cpp
    src/Resources/ResourceManager.h
    src/Resources/stb_image.h
    src/Game/Game.cpp
    src/Game/Game.h
    src/Game/Tank.cpp
    src/Game/Tank.h
)

#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BIULD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


#sub for glfw
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw) 

#sub for glad
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

#sub for glm
include_directories(external/glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)