add_library(savitar STATIC IMPORTED)
set_target_properties(savitar PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../../../src/libsavitar.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/../../../src"
)

add_executable(nested_table nested_table.cc)
target_link_libraries(nested_table libcuckoo savitar uuid pmem stdc++fs)

add_executable(hellohash hellohash.cc)
target_link_libraries(hellohash libcuckoo savitar uuid pmem stdc++fs)

add_executable(count_freq count_freq.cc)
target_link_libraries(count_freq libcuckoo savitar uuid pmem stdc++fs)

add_library(int_str_table STATIC int_str_table.cc)
target_link_libraries(int_str_table libcuckoo)

add_library(blob_blob_table STATIC blob_blob_table.cc)
target_link_libraries(blob_blob_table libcuckoo)

add_executable(c_hash c_hash.c)
target_link_libraries(c_hash int_str_table blob_blob_table savitar uuid pmem stdc++fs)

set_property(TARGET c_hash PROPERTY C_STANDARD 99)
