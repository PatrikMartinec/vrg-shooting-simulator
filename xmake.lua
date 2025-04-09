add_rules("mode.debug", "mode.release")
set_languages("cxx23")

add_includedirs("external/entt/single_include")
add_includedirs("external/glm")
add_includedirs("external/catch2")

target("vrg-shooting-simulator")
    set_kind("binary")
    add_files("src/main.cpp")
    add_includedirs("src")

target("tests")
    set_kind("binary")
    add_files("src/tests.cpp")
    add_files("external/catch2/catch_amalgamated.cpp")
    add_includedirs("src")
