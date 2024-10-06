set PACKAGE_NAME="com.example.game_test"
adb shell run-as %PACKAGE_NAME% mkdir test
adb shell run-as %PACKAGE_NAME% cp /data/local/tmp/lldb-server test/lldb-server
rem 获取 lldb-server 进程 ID
for /f "tokens=2" %%i in ('adb shell ps ^| findstr lldb-server') do (
    set PID=%%i
    goto :found
)
@REM exit /b 1
:found
rem 杀掉 lldb-server 进程
adb shell run-as %PACKAGE_NAME% kill -9 %PID%
adb shell am start -a android.intent.action.MAIN -D -n %PACKAGE_NAME%/.MainActivity
adb shell run-as %PACKAGE_NAME% ./test/lldb-server platform --server --listen unix-abstract:///data/local/tmp/debug.sock