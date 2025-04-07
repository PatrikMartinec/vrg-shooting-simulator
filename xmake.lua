add_rules("mode.debug", "mode.release")
set_languages("cxx23")

add_includedirs("external/entt/single_include")
add_includedirs("external/glm")


target("vrg-shooting-simulator")
    set_kind("binary")
    add_files("src/*.cpp")
