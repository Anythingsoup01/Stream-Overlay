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
    },

    link = {
        "gl",
        "glfw3"
    }
}
