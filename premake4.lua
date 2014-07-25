solution "libbulletml"
    configurations { "Debug", "Release" }
    platforms { "native", "x32", "x64" }

    project "libbulletml"
        language "C++"
        kind "StaticLib"

        buildoptions { "-std=c++11", "-fPIC" }

        includedirs { }
        files { "src/**" }

        targetdir "lib"
        targetname "bulletml"

        ---------------------------------------
        -- Link static libraries and config
        libdirs { }
        links { }

        ---------------------------------------
        -- Build rules
        configuration "Debug"
            defines "DEBUG"
            flags { "Symbols", "ExtraWarnings" }

        configuration "Release"
            flags { "Optimize", "ExtraWarnings" }

