Workspace = {
    name = "overlay-wks"
}

Project = {
    name = "overlay",
    kind = "ConsoleApp",
    language = "C++",
    dialect = "20",

    files = {
        "src/*.cpp",
    },

    includedirs = {
        "include",
        "pch",
        "dep/GLFW/include",
        "dep/ImGui",
        "dep/glad/include",
        "dep/yaml/include",
    },

    links = {
        "GL",
        "Glad",
        "glfw",
        "ImGui",
        "yaml-cpp",
    }
}


External = "dep/glad"
External = "dep/GLFW"
External = "dep/ImGui"
External = "dep/yaml"
