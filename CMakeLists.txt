cmake_minimum_required(VERSION 3.14)
project(EDII)

set(ROOT_DIR "${PROJECT_SOURCE_DIR}/") # Editar mais tarde se necessário
set(CMAKE_CXX_STANDARD 17)

# Arquivos de configuração dos diretórios
file(GLOB source_files include/*.h src/ProductReview.cpp src/ArvoreB.cpp src/ArvoreVP.cpp src/reader.cpp src/List.cpp src/Multinode.cpp src/huffman.cpp)
add_library(edll ${source_files})
target_include_directories(edll PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} edll)

enable_testing()
add_subdirectory(tests)

