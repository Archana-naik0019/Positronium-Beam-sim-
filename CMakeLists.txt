cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(PositroniumBeam)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})


file(GLOB sources *.cc)
file(GLOB headers *.hh)

add_executable(PositroniumBeam main.cc ${sources} ${headers})

target_link_libraries(PositroniumBeam ${Geant4_LIBRARIES})

file(GLOB MACRO_FILES macros *.mac)
file(GLOB DATA_FILES data *.dat)
file(COPY ${MACRO_FILES} ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# Enable ROOT output
#find_package(ROOT REQUIRED)
#target_link_libraries(PositroniumBeam ROOT::Core ROOT::Tree ROOT::Hist)

# Install build files
install(TARGETS PositroniumBeam DESTINATION bin)
