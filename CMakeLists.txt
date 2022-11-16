cmake_minimum_required(VERSION 3.14)
project(EDII)

set(ROOT_DIR "${PROJECT_SOURCE_DIR}/") # Editar mais tarde se necessário

# Arquivos de configuração dos diretórios
file(GLOB source_files src/ProductReview.cpp include/*.h)
add_library(edll ${source_files})
target_include_directories(edll PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
#add_subdirectory(src)
#add_subdirectory(include)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} edll)

enable_testing()
add_subdirectory(tests)

