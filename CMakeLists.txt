#
# project: fips-sdl
#
if (NOT FIPS_IMPORT)
    cmake_minimum_required(VERSION 2.8)
    get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
    include("${FIPS_ROOT_DIR}/cmake/fips.cmake")
    project(fips-sdl)
    fips_setup()
endif()

# Current SDL version 2.0.16
fips_begin_module(SDL)
    if(FIPS_WINDOWS)
        fips_files_ex(SDL/src/ *.c 
            EXCEPT 
            audio/ps2/*
            video/qnx/*
            video/os2/* 
            joystick/iphoneos/* 
            thread/pthread/* 
            thread/generic/* 
            main/* 
            core/unix/* 
            core/linux/* 
            core/openbsd/*
            core/os2/*
            filesystem/psp/*
            filesystem/ps2/*
            hidapi/mac/* 
            hidapi/linux/* 
            hidapi/android/* 
            hidapi/libusb/*
            locale/emscripten/*
            locale/android/*
            locale/vita/*
            misc/android/*
            misc/unix/*
            misc/riscos/*
            misc/vita/*
            misc/emscripten/*
        )

        fips_files(
            thread/generic/SDL_syscond.c
        )

        fips_libs(
            gdi32.lib 
            opengl32.lib 
            user32.lib 
            kernel32.lib 
            advapi32.lib 
            winmm.lib 
            imm32.lib 
            ole32.lib 
            oleaut32.lib 
            version.lib 
            ws2_32.lib 
            wldap32.lib 
            shell32.lib 
            comdlg32.lib 
            setupapi.lib
        )
    endif()

    # Not tested
    if(FIPS_MACOS)
        fips_files_ex(SDL/src/ *.c *.m
            EXCEPT 
            video/qnx/* 
            render/opengles2/*
            haptic/windows/*
            joystick/iphoneos/* 
            thread/generic/*
            core/unix/*
            core/openbsd/*
            core/os2/*
            hidapi/windows/* 
            hidapi/linux/* 
            hidapi/android/*
            hidapi/ios/*
            hidapi/libusb/*
            locale/emscripten/*
            locale/android/*
            misc/android/*
            misc/unix/*
            misc/riscos/*
            misc/vita/*
        )
    endif()

    # Not tested
    if(FIPS_LINUX)
        fips_files_ex(SDL/src/ *.c *.m
            EXCEPT 
            video/qnx/* 
            render/opengles2/*
            haptic/windows/*
            joystick/iphoneos/* 
            thread/generic/*
            core/windows/* 
            hidapi/windows/* 
            hidapi/mac/*
            hidapi/android/*
            hidapi/ios/*
            hidapi/libusb/*
        )
    endif()

    fips_dir(.)

fips_end_module()
target_include_directories(SDL PUBLIC SDL/include SDL/src/hidapi/hidapi)
target_compile_definitions(SDL PUBLIC HAVE_LIBC _THREAD_SAFE)

if(FIPS_LINUX)
    # TODO: Add include path for config, maybe even a custom script to generate?
    target_compile_definitions(SDL PUBLIC USING_GENERATED_CONFIG_H)
endif()

if(FIPS_EMSCRIPTEN)
    message(FATAL_ERROR "When using Emscripten SDL must be linked via -s USE_SDL=2 instead.")
endif()

if (NOT FIPS_IMPORT)
    fips_finish()
endif()