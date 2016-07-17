workspace "libbulletml"
configurations { "debug", "release" }

project "libbulletml"
language "C++"
kind "StaticLib"

targetdir "lib/%{cfg.buildcfg}"

sysincludedirs {}

includedirs {}

libdirs {}

links {}

files {
   "src/**.cpp",
}

buildoptions {
   "-Wall",
   "-Wextra",
   "-pedantic",
   "-std=c++11"
}

filter "configurations:debug"
defines { "DEBUG" }
flags { "Symbols" }

filter "configurations:release"
defines { "NDEBUG" }
optimize "On"
