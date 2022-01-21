cmake_minimum_required(VERSION 3.10)

# Create project
set(ProjectName "rotation_master")
project(${ProjectName})
# Create executable file
add_executable(${ProjectName}
    main.cpp
    container.h
    ui.h ui.cpp
)
if(EMSCRIPTEN)
# Compile option
set(CMAKE_BUILD_TYPE_INIT "Release")
set(CMAKE_C_COMPILER "emcc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -DGLFW_INCLUDE_ES3 \
    -DIMGUI_IMPL_OPENGL_ES3 -O2 \
    -s USE_WEBGL2=1 \
    -s FULL_ES3=1 \
    -s USE_GLFW=3"
)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

else()
# Compile option
set(CMAKE_INSTALL_PREFIX "./install/" CACHE STRING "install path" FORCE)
include(${CMAKE_SOURCE_DIR}/cmakes/compile_option.cmake)

## Add third party libraries
# For OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${ProjectName} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
target_link_libraries(${ProjectName} ${OPENGL_LIBRARIES})
target_include_directories(${ProjectName} PUBLIC ${OPENGL_INCLUDE_DIR})

# For GLFW
set(GLFW_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party/glfw/")
add_subdirectory(${GLFW_DIR})
target_link_libraries(${ProjectName} glfw ${GLFW_LIBRARIES})
target_include_directories(${ProjectName} PUBLIC "${GLFW_DIR}/include/")

# For GLEW
# add_definitions(-DBUILD_UTILS=off)
# add_definitions(-DGLEW_STATIC)
set(GLEW_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party/glew/")
add_subdirectory("${GLEW_DIR}/build/cmake/")
target_link_libraries(${ProjectName} glew_s)
target_include_directories(${ProjectName} PUBLIC "${GLEW_DIR}/include/")
endif()

# For ImGui (reference: example_glfw_opengl3/Makefile)
set(IMGUI_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party/imgui/")
add_library(ImGui
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp 
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
if(NOT EMSCRIPTEN)
target_link_libraries(ImGui glfw ${GLFW_LIBRARIES})
target_include_directories(ImGui PUBLIC "${GLFW_DIR}/include/")
endif()
target_include_directories(ImGui PUBLIC ${IMGUI_DIR} "${IMGUI_DIR}/backends")
target_link_libraries(${ProjectName} ImGui)

## Add my submodules
add_subdirectory(./matrix)
target_link_libraries(${ProjectName} Matrix)
add_subdirectory(./transformation_matrix)
target_link_libraries(${ProjectName} TransformationMatrix)
add_subdirectory(./gl_helper)
target_link_libraries(${ProjectName} GlHelper)

# Add test module
option(BUILD_TESTS "BUILD_TESTS" ON)
if(EMSCRIPTEN)
set(BUILD_TESTS OFF)
endif()

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(./test)
endif()
