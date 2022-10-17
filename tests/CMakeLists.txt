# Arquivo de configuração dos testes
add_definitions(-DTEST_CASE=1)

add_executable(radix radixsort.cc)
target_link_libraries(radix PUBLIC edll)