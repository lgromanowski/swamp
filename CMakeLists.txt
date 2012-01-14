cmake_minimum_required(VERSION 2.6)
project(SWAMP)

set(CMAKE_CXX_FLAGS "-g -std=gnu++0x -O2 -Wall -Wextra -Wformat-security -Werror -I${CMAKE_HOME_DIRECTORY} -lpthread -D_GLIBCXX_USE_NANOSLEEP")

set(SWAMP_MAIN swamp.h swamp.cpp main.cpp)

set(SWAMP_UTILS_DIR "utils")
set(SWAMP_UTILS_HEADERS ${SWAMP_UTILS_DIR}/logger.h ${SWAMP_UTILS_DIR}/text_logger.h ${SWAMP_UTILS_DIR}/string_utils.h)
set(SWAMP_UTILS_SRC ${SWAMP_UTILS_DIR}/text_logger.cpp ${SWAMP_UTILS_DIR}/string_utils.cpp)
set(SWAMP_UTILS ${SWAMP_UTILS_HEADERS} ${SWAMP_UTILS_SRC})

set(SWAMP_SERVER_DIR "server")
set(SWAMP_SERVER_HEADERS ${SWAMP_SERVER_DIR}/connection.h ${SWAMP_SERVER_DIR}/server_listeners.h ${SWAMP_SERVER_DIR}/server.h)
set(SWAMP_SERVER_SRC ${SWAMP_SERVER_DIR}/connection.cpp ${SWAMP_SERVER_DIR}/server.cpp)
set(SWAMP_SERVER ${SWAMP_SERVER_HEADERS} ${SWAMP_SERVER_SRC})

set(SWAMP_CHARACTER_DIR "character")
set(SWAMP_CHARACTER_HEADERS ${SWAMP_CHARACTER_DIR}/character.h ${SWAMP_CHARACTER_DIR}/non_player_character.h ${SWAMP_CHARACTER_DIR}/player.h)
set(SWAMP_CHARACTER_SRC ${SWAMP_CHARACTER_DIR}/non_player_character.cpp ${SWAMP_CHARACTER_DIR}/player.cpp)
set(SWAMP_CHARACTER ${SWAMP_CHARACTER_HEADERS} ${SWAMP_CHARACTER_SRC})

set(SWAMP_SOURCES ${SWAMP_UTILS} ${SWAMP_SERVER} ${SWAMP_CHARACTER} ${SWAMP_MAIN})

add_executable(swamp_server ${SWAMP_SOURCES})


find_package(PostgreSQL)


set(EXTRA_LIBS pthread)
target_link_libraries(swamp_server ${EXTRA_LIBS})