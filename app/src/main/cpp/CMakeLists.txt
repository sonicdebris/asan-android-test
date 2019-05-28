cmake_minimum_required(VERSION 3.10.2)

# A function to retrieve the architecture from the ABI
# (neither ANDROID_ARCH_NAME nor CMAKE_SYSTEM_PROCESSOR work for this)

function(get_architecture ABI ARCH)
    if (ABI STREQUAL armeabi-v7a)
        set(${ARCH} arm PARENT_SCOPE)
    elseif(ABI STREQUAL arm64-v8a)
        set(${ARCH} aarch64 PARENT_SCOPE)
    elseif(ABI STREQUAL x86)
        set(${ARCH} i686 PARENT_SCOPE)
    elseif(ABI STREQUAL x86_64)
        set(${ARCH} x86_64 PARENT_SCOPE)
    else()
        message(FATAL_ERROR "Unsupported ABI")
    endif()
endfunction()


# NATIVE LIBRARY SETUP

add_library(native-lib SHARED native-lib.cpp )
target_link_libraries(native-lib PRIVATE log)

# Enable address sanitizer only for debug builds
# Ideally we would use debug type properties and generator expressions,
# But with add_custom_command that becomes kind of convoluted

if (SANITIZE)

    message("Enabling sanitizer in native library")

    target_compile_options(native-lib PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_libraries(native-lib PRIVATE -fsanitize=address)

    # Asan libs are "somewhere" in the toolchain's root, we try to find the
    # right one for the current architecture and copy it to the libs output dir
    # (so that it will be packed in the apk):

    get_architecture(${ANDROID_ABI} ARCH)
    file(GLOB_RECURSE ASAN_SRC ${ANDROID_TOOLCHAIN_ROOT}/*.asan*${ARCH}*-android.so)
    set(ASAN_DEST ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

    add_custom_command(
            TARGET native-lib PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${ASAN_SRC} ${ASAN_DEST}
    )

endif()
