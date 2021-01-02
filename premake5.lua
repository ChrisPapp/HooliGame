workspace "Hooligame"
    configurations{"Debug", "Release"}
    architecture "x86_64"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "Game"
    kind "ConsoleApp"
    language "C++"
    targetdir("bin/" .. outputdir)
    objdir ("bin/obj/" .. outputdir)

    files { "src/**.h", "src/**.cpp"}
    includedirs { "src"}

    -- Build SGG
    if os.host() == "windows" then
        os.execute "cd vendor\\sgg && build_sgg_x64.bat"
        -- Copy dlls on windows
        prebuildcommands {
            "{COPY} vendor/sgg/3rdparty/bin/*.dll %{cfg.targetdir}"
        }
    elseif os.host() == "linux" then
        os.execute "cd vendor/sgg; ./build_sgg_x64.sh"
    else
        os.execute "cd vendor/sgg; ./build_sgg_macOS.sh" 
    end

    includedirs { "vendor/sgg/graphics/" }
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
