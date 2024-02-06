cmake_minimum_required(VERSION 3.25)

# Notre projet est étiqueté r-type
project(r-type)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set (CMAKE_CXX_STANDARD 20)

### CPM INITIALISATION ###

set(CPM_DOWNLOAD_VERSION 0.38.5)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

### EXECUTABLE CREATION ###

# Crée des variables avec les fichiers à compiler
file(GLOB SRV_HEADER_FILES
    "server/headers/Network/*.hpp"
    "server/headers/*.hpp"
    "game/headers/*.hpp"
)

file(GLOB SRV_FILES
    "server/src/*.cpp"
    "server/src/Network/*.cpp"
    "game/src/*.cpp"
    "game/src/Components/*.cpp"
    "game/src/Systems/*.cpp"
)

file(GLOB CL_HEADER_FILES
    "client/headers/Client/*.hpp"
    "client/headers/Components/*.hpp"
    "client/headers/*.hpp"
    "game/headers/*.hpp"
)

file(GLOB CL_FILES
    "client/src/Client/*.cpp"
    "client/src/Components/*.cpp"
    "client/src/*.cpp"
    "game/src/*.cpp"
    "game/src/Components/*.cpp"
    "game/src/Systems/*.cpp"
)

# On indique que l'on veut un exécutable server et client compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(r-type_server ${SRV_FILES} ${SRV_HEADER_FILES})
add_executable(r-type_client ${CL_FILES}  ${CL_HEADER_FILES})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(r-type_server pthread sfml-graphics sfml-audio GuismusEngine)
    target_link_libraries(r-type_client sfml-graphics sfml-audio pthread GuismusEngine)
else()
    target_link_libraries(r-type_server sfml-graphics sfml-audio GuismusEngine)
    target_link_libraries(r-type_client sfml-graphics sfml-audio GuismusEngine)
endif()

### DEPENDENCES ###

#ASIO
CPMAddPackage (NAME asio GITHUB_REPOSITORY chriskohlhoff/asio GIT_TAG "asio-1-28-1")
include_directories(${asio_SOURCE_DIR}/asio/include/)

# SFML
CPMAddPackage(NAME SFML GITHUB_REPOSITORY SFML/SFML GIT_TAG "2.6.0")
include_directories(${SFML_SOURCE_DIR}/include/)
set_target_properties(sfml-audio PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

# GuismusEngine
CPMAddPackage(NAME GuismusEngine GITHUB_REPOSITORY Guismus/GuismusEngine GIT_TAG "v2.0.3")
include_directories(${GuismusEngine_SOURCE_DIR}/headers/)

# Json
CPMAddPackage(NAME Json GITHUB_REPOSITORY nlohmann/json GIT_TAG "v3.11.2")
include_directories(${Json_SOURCE_DIR}/include/)

# Ajouter les tags Valgrind
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  # Assurez-vous que les symboles de débogage sont présents
    find_program(VALGRIND "valgrind")
    if (VALGRIND)
        message(STATUS "Valgrind found: ${VALGRIND}")
        set(VALGRIND_FLAGS "--leak-check=full --show-leak-kinds=all")
        add_custom_target(valgrind
            COMMAND ${VALGRIND} ${VALGRIND_FLAGS} ./r-type_server
            DEPENDS r-type_server
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    else ()
        message(WARNING "Valgrind not found, valgrind target will not be available.")
    endif ()
endif ()
