include(FetchContent)

set(SFML_VERSION 3.1.0)
# imgui-sfml 3.0 supports Dear ImGui 1.91.x, but not the breaking 1.92 API.
set(IMGUI_VERSION 1.91.9b)
set(IMGUI_SFML_VERSION 3.0)

FetchContent_Declare(
    SFML
    URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_Declare(
    imgui
    URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_Declare(
  imgui-sfml
  URL "https://github.com/SFML/imgui-sfml/archive/v${IMGUI_SFML_VERSION}.zip"
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_MakeAvailable(sfml)

FetchContent_MakeAvailable(imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)

FetchContent_MakeAvailable(imgui-sfml)