workspace "Hooligame"
    configurations { "Debug", "Release" }
    architecture "x86_64"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "Game"
    kind "ConsoleApp"
    language "C++"
    targetdir("bin/" .. outputdir)
    objdir("bin/obj/" .. outputdir)

    files { "src/**.h", "src/**.cpp" }
    includedirs { "src/", "vendor/sgg/graphics/", "vendor/sgg/3rdparty/include/" }
    libdirs { "vendor/sgg/lib/" }

    -- copy assets to build dir
    postbuildcommands {
        "{COPY} assets/ %{cfg.targetdir}/assets"
    }

    if os.host() == "windows" then
        -- build sgg
        os.execute "cd vendor\\sgg && build_sgg_x64.bat"

        -- copy dll on windows
        prebuildcommands {
            "{COPY} vendor/sgg/3rdparty/bin/*.dll %{cfg.targetdir}"
        }

        filter "configurations:Debug"
            links { "sggd" }

        filter "configurations:Release"
            links { "sgg" }

    elseif os.host() == "macosx" then
        os.execute "cd vendor/sgg; ./build_sgg_macOS.sh"

        cppdialect "C++17"

        filter "configurations:Debug"
            links { "sggd", "GLEW", "SDL2", "SDL2_mixer", "freetype", "framework.dll", "OpenGL.framework" }

        filter "configurations:Release"
            links { "sgg", "GLEW", "SDL2", "SDL2_mixer", "freetype", "framework.dll", "OpenGL.framework" }
    end

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "On"

