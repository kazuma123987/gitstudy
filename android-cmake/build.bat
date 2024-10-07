@echo off
set ANDROID_NDK=C:/A_TEMPS/Android_Studio/SDK/ndk/24.0.8215888
if not exist build ( mkdir build )
cd build || exit
cmake -DANDROID_ABI="arm64-v8a" ^
	-DANDROID_NDK=%ANDROID_NDK% ^
	-DANDROID_PLATFORM=android-24 ^
	-DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%/build/cmake/android.toolchain.cmake ^
	-DCMAKE_BUILD_TYPE=%1 ^
	-DCMAKE_ANDROID_ARCH_ABI="arm64-v8a" ^
	-DCMAKE_ANDROID_NDK=%ANDROID_NDK% ^
	-DCMAKE_SYSTEM_NAME=Android ^
	-DCMAKE_SYSTEM_VERSION=24 ^
	-GNinja ^
	..
ninja -j8 all
