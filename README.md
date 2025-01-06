在当前目录下创建目录build并进入
打开cmd窗口
输入cmake .. -G"Visual Studio 17 2022" -AWin32
点击sln开始编程

若在Classes或Resources文件夹中添加、删除了文件，请在build目录下再次使用cmake build ..命令