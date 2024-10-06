adb push bin/%1 /data/local/tmp/
adb shell chmod 755 /data/local/tmp/%1
@REM adb shell setenforce 0
adb forward tcp:9090 tcp:9090
@REM adb shell "pkill lldb-server"
adb shell "/data/local/tmp/lldb-server platform --listen 'localhost:9090' --server &"