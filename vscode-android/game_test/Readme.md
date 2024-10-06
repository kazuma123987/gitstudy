1. cd scripts; ./start_server.bat或者直接Ctrl+Shift+P启动start_server任务以建立lldb监听服务器
2. 直接运行launch任务即可
3. 移植.vscode scripts两个文件夹进行编译时，需要注意build.bat和start.bat的包名需要正确配置,另外.vscode的C/C++提示使用的NDK路径需要正确配置
4. 如果要使用pid进行连接(attach)，需要把launch.json的"program"删除,换成"pid",通过调试命令行(lldb)的"platform process list"查看app进程的pid号,因为adb执行lldb-server的run-as packageName会监听packageName名字的进程,之后修改launch.json的pid号就行了
5. adb shell am start -D -n com.example.game_test/.MainActivity的-D参数用来等待jdb连接，jdb连接后程序将自动运行，所以launch.json采用了先以Debug模式启动应用，然后lldb连接lldb-server监听到的进程，然后启动jdb -connect xxx[...] 以连接程序并正常运行，此时就会运行到cpp代码的断点处(如果有断点)
6. 包名(packageName)在build.gradle.kts(app)中获取,Activity的名字在AndroidManifest.xml中获取
7. jdb_start.bat中监听的端口可以在path/to/SDK/tools/monitor.bat中使用
