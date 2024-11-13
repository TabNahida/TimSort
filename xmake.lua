add_languages("cxx11")

target("timsort")
    set_kind("headeronly")
    set_encodings("utf-8")

    add_headerfiles("include/timsort.hpp")

target_end()

target("main")
    set_kind("binary")
    set_encodings("utf-8")

    add_files("src/main.cpp")
    add_includedirs("include")

    add_deps("timsort")
target_end()