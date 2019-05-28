# asan-android-test
Example of enabling address sanitizer for android native project

Enabling the sanitizer is a matter of:
- Linking to the shared version of the c++ runtime
- Providing the needed compiler and linker flags
- Copying the asan shared libraries from the ndk toolchain dir to a place where they can be found and packaged
- Package the wrap.sh scripts in the APK's lib folder (They can be found in ndk's root dir)

Additionally, here we set up an additional build type in gradle, so all relevant operations are
only performed for the new "sanitize" build type, and won't affect either the debug or the release build.

General info on address sanitizer:
https://android-developers.googleblog.com/2017/08/android-bug-swatting-with-sanitizers.html

Main source of inspiration and information:
https://virtualrealitypop.com/oreo-ndk-secrets-7d075a9b084

On creating and packaging wrap.sh:
https://developer.android.com/ndk/guides/wrap-script#packaging_wrapsh

