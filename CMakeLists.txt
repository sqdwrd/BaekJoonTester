cmake_minimum_required(VERSION 3.23)
project(BaekJoonTester)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_SHARED_LINKER_FLAGS "-lcurl")


include_directories(gumbo-get-element-by-id.c/src)
include_directories(gumbo-parser/src)

add_executable(BaekJoonTester
        gumbo-get-element-by-id.c/src/get-element-by-id.c
        gumbo-get-element-by-id.c/src/get-element-by-id.h
        gumbo-parser/src/attribute.c
        gumbo-parser/src/attribute.h
        gumbo-parser/src/char_ref.c
        gumbo-parser/src/char_ref.h
        gumbo-parser/src/error.c
        gumbo-parser/src/error.h
        gumbo-parser/src/gumbo.h
        gumbo-parser/src/insertion_mode.h
        gumbo-parser/src/parser.c
        gumbo-parser/src/parser.h
        gumbo-parser/src/string_buffer.c
        gumbo-parser/src/string_buffer.h
        gumbo-parser/src/string_piece.c
        gumbo-parser/src/string_piece.h
        gumbo-parser/src/tag.c
        gumbo-parser/src/tag_enum.h
        gumbo-parser/src/tag_gperf.h
        gumbo-parser/src/tag_sizes.h
        gumbo-parser/src/tag_strings.h
        gumbo-parser/src/token_type.h
        gumbo-parser/src/tokenizer.c
        gumbo-parser/src/tokenizer.h
        gumbo-parser/src/tokenizer_states.h
        gumbo-parser/src/utf8.c
        gumbo-parser/src/utf8.h
        gumbo-parser/src/util.c
        gumbo-parser/src/util.h
        gumbo-parser/src/vector.c
        gumbo-parser/src/vector.h
        main.c)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(BaekJoonTester ${CURL_LIBRARIES})