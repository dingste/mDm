cmake_minimum_required(VERSION 3.10)

# Setzen des Projektnamens und der Sprache
project(mDmRuntime CXX)

# Setzen der C++-Standardversion
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Hinzufügen des Verzeichnisses, das die .cpp und .h Dateien enthält
include_directories(${PROJECT_SOURCE_DIR}/src)

# Definition der Quelldateien für das Projekt
# Angenommen, Ihre Quelldateien befinden sich im Verzeichnis 'src'
file(GLOB SOURCES "src/*.cpp")

# Erstellen eines ausführbaren Programms mit dem Namen 'mDmRuntime'
add_executable(mDmRuntime ${SOURCES})

# Hier können Sie Bibliotheken verlinken, falls Ihr Projekt welche benötigt.
# Beispiel: target_link_libraries(mDmRuntime someLibrary)
