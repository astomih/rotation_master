cmake_minimum_required(VERSION 3.10)
# Create project
set(ProjectName "rotation_master")
project(${ProjectName})

# Compile option
set(CMAKE_BUILD_TYPE_INIT "Release")
set(CMAKE_C_COMPILER "emcc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLFW_INCLUDE_ES3 -DIMGUI_IMPL_OPENGL_ES3 -O2 \
    -s USE_WEBGL2=1 \
    -s FULL_ES3=1 \
    -s USE_GLFW=3"
	)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

# Create executable file
add_executable(${ProjectName}
    main.cpp
    container.h
    ui.h ui.cpp
)

## Add third party libraries
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
option(BUILD_TESTS "BUILD_TESTS" OFF)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(./test)
endif()
