@echo off
setlocal

set NDK_PATH="C:/A_TEMPS/Android_Studio/SDK/ndk/26.2.11394342"
set BUILD_PATH="build\Qt_6_7_3_Clang_x86_64-%1"
set JDK_PATH="C:/Program Files/Java/jdk-17"
set EMULATOR_NAME="emulator-5554"
set QT_KIT_PATH="C:/A_SOFTWARE/Qt/6.7.3/android_x86_64"
set QTC_PATH="%BUILD_PATH%\.qtc\package-manager"

if not exist %BUILD_PATH% ( mkdir %BUILD_PATH% )
if not exist %QTC_PATH% (
    mkdir %QTC_PATH%
    xcopy "C:\A_SOFTWARE\Qt\Tools\QtDesignStudio\share\qtcreator\package-manager" "%QTC_PATH%\" /E
)

cmake -S . ^
-B %BUILD_PATH% ^
-DANDROID_NDK:PATH=%NDK_PATH% ^
-DQT_HOST_PATH:PATH="C:/A_SOFTWARE/Qt/6.7.3/mingw_64" ^
-DQT_QMAKE_EXECUTABLE:FILEPATH="%QT_KIT_PATH%/bin/qmake.bat" ^
-DCMAKE_PROJECT_INCLUDE_BEFORE:FILEPATH="%BUILD_PATH%/.qtc/package-manager/auto-setup.cmake" ^
-DCMAKE_PREFIX_PATH:PATH="%QT_KIT_PATH%" ^
-DCMAKE_TOOLCHAIN_FILE:FILEPATH="%NDK_PATH%/build/cmake/android.toolchain.cmake" ^
-DCMAKE_C_COMPILER:FILEPATH="%NDK_PATH%/toolchains/llvm/prebuilt/windows-x86_64/bin/clang.exe" ^
-DCMAKE_CXX_COMPILER:FILEPATH="%NDK_PATH%/toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe" ^
-DQT_NO_GLOBAL_APK_TARGET_PART_OF_ALL:BOOL="ON" ^
-DANDROID_SDK_ROOT:PATH="C:/A_TEMPS/Android_Studio/SDK" ^
-DCMAKE_BUILD_TYPE:STRING="%1" ^
-DANDROID_ABI:STRING="x86_64" ^
-DANDROID_USE_LEGACY_TOOLCHAIN_FILE:BOOL="OFF" ^
-DCMAKE_FIND_ROOT_PATH:PATH="%QT_KIT_PATH%" ^
-DANDROID_PLATFORM:STRING="android-23" ^
-DCMAKE_CXX_FLAGS_INIT:STRING="-DQT_QML_DEBUG" ^
-DANDROID_STL:STRING="c++_shared" ^
-DCMAKE_GENERATOR:STRING=Ninja

cmake --build %BUILD_PATH% -j --target all

C:/A_SOFTWARE/Qt/6.7.3/mingw_64/bin/androiddeployqt.exe ^
--input %BUILD_PATH%/android-android_qt-deployment-settings.json ^
--output %BUILD_PATH%/android-build ^
--android-platform android-34 ^
--jdk %JDK_PATH% ^
--gradle

@REM adb -s %EMULATOR_NAME% pull /system/bin/app_process64 "%BUILD_PATH%/android-app-process/app_process"
@REM adb -s %EMULATOR_NAME% pull /system/bin/linker64 "%BUILD_PATH%/android-app-process/linker64"
@REM adb -s %EMULATOR_NAME% pull /system/lib64/libc.so "%BUILD_PATH%/android-app-process/libc.so"

endlocal