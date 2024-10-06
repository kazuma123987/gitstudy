@echo off
setlocal

type nul>tmp/get-pid.txt

for /f "tokens=2" %%a in ('adb shell pidof lldb-server') do (
  echo %%a >> tmp/get-pid.txt
  exit /b
)
endlocal
adb shell am start -D -n com.example.game_test/.MainActivity
jdb -connect com.sun.jdi.SocketAttach:port=8700,hostname=127.0.0.1
stop in com.google.androidgamesdk.GameActivity.onCreate(android.os.Bundle)
stop in com.example.game_test.MainActivity.OnCreate(android.os.Bundle)
run com.example.game_test.MainActivity