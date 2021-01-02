workspace "Hooligame"
    configurations { "Debug", "Release" }
    architecture "x86_64"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "Game"
    kind "ConsoleApp"
    language "C++"
    targetdir("bin/" .. outputdir)
    objdir("bin/obj/" .. outputdir)

    if os.host() == "windows" then
        -- build sgg
        os.execute "cd vendor\\sgg && build_sgg_x64.bat"

        -- copy dll on windows
        prebuildcommands {
            "{COPY} vendor/sgg/3rdparty/bin/*.dll %{cfg.targetdir}"
        }

        files { "src/**.h", "src/**.cpp" }
        includedirs { "src", "vendor/sgg/graphics/" }
        libdirs { "vendor/sgg/lib/" }

        filter "configurations:Debug"
            defines "DEBUG"
            runtime "Debug"
            symbols "On"
            links { "sggd" }

        filter "configurations:Release"
            defines "RELEASE"
            runtime "Release"
            optimize "On"
            links { "sgg" }

    elseif os.host() == "darwin" then
        os.execute "cd vendor/sgg; ./build_sgg_x64.sh"

        files { "src/**.h", "src/**.cpp" }
        includedirs { "src", "vendor/sgg/graphics/" }
        libdirs { "vendor/sgg/lib/" }

        filter "configurations:Debug"
            defines "DEBUG"
            runtime "Debug"
            symbols "On"
            links { "sggd", "GLEW", "SDL2", "SDL2_mixer", "freetype", "framework.dll", "OpenGL.framework" }

        filter "configurations:Release"
            defines "RELEASE"
            runtime "Release"
            optimize "On"
            links { "sgg", "GLEW", "SDL2", "SDL2_mixer", "freetype", "framework.dll", "OpenGL.framework" }
    end

