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

# Current SDL version 2.0.9
fips_begin_module(sdl)
    if(FIPS_WINDOWS)
        fips_files_ex(SDL/src/ *.c 
            EXCEPT 
            video/qnx/* 
            joystick/iphoneos/* 
            thread/pthread/* 
            thread/generic/* 
            main/* 
            core/unix/* 
            core/linux/* 
            hidapi/mac/* 
            hidapi/linux/* 
            hidapi/android/* 
            hidapi/libusb/*
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

    if(FIPS_MACOS)
        fips_files_ex(SDL/src/ *.c *.m
            EXCEPT 
            video/qnx/* 
            render/opengles2/*
            haptic/windows/*
            joystick/iphoneos/* 
            thread/generic/*
            core/unix/* 
            hidapi/windows/* 
            hidapi/linux/* 
            hidapi/android/*
            hidapi/ios/*
            hidapi/libusb/*
        )
    endif()

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

    if(FIPS_EMSCRIPTEN)
        fips_files_ex(SDL/src/ *.c 
            EXCEPT 
            video/qnx/*
            render/opengles2/*
            haptic/windows/*
            joystick/iphoneos/*  
            thread/generic/* 
            hidapi/*
        )
    endif()

    fips_dir(.)

fips_end_module()
target_include_directories(sdl PUBLIC SDL/include SDL/src/hidapi/hidapi)
target_compile_definitions(sdl PUBLIC HAVE_LIBC _THREAD_SAFE)

if(FIPS_LINUX)
    # TODO: Add include path for config, maybe even a custom script to generate?
    target_compile_definitions(sdl PUBLIC USING_GENERATED_CONFIG_H)
endif()

# TODO: Remove test
fips_begin_app(hello cmdline)
    fips_files(main.cpp)
    fips_deps(sdl)
    
fips_end_app()

if (NOT FIPS_IMPORT)
    fips_finish()
endif()