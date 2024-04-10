cmake_minimum_required(VERSION 3.10)

# Setzen des Projektnamens und der Sprache
project(mDmRuntime CXX)

# Setzen der C++-Standardversion
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

# Hinzufügen des Verzeichnisses, das die .cpp und .h Dateien enthält
include_directories(${PROJECT_SOURCE_DIR}/src)

# Definition der Quelldateien für das Projekt
# Angenommen, Ihre Quelldateien befinden sich im Verzeichnis 'src'
file(GLOB SOURCES "src/*.cpp")

# Erstellen eines ausführbaren Programms mit dem Namen 'mDmRuntime'
add_executable(mDmRuntime ${SOURCES})

# Verlinke die SDL2 Bibliothek mit dem ausführbaren Ziel
target_link_libraries(mDmRuntime ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})