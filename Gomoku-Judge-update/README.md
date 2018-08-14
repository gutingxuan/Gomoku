# Gomoku
Judge program for Gomoku AI  

一、运行需要：
1、裁判程序基于python3，windows。

2、AI程序支持C++，python3，java，请配置好使用语言的环境变量。
   你可以：
   1) 直接将你的程序放到主文件夹gomoku-master下。
      对于C++程序，裁判程序通过g++编译，如果没有安装GNU，可以通过主文件夹下的mingw-get-setup安装，并将安装目录设置到环境变量路径中。
      对于java程序，环境变量路径为jdk所在路径。
   2) 或者你可以预先编译，并将编译结果放到主文件夹下。
      对于C++程序，编译结果可能是bot.exe。
      对于java程序，编译结果为Main.class和Main$Grid.class。

3、UI是基于python的一个模块pygame，如果装有pip可以通过pip install pygame简易安装。

二、使用说明：
1、主程序从标准输入中得到裁判程序发来的游戏历史信息，通过历史信息还原出当前的游戏局面，将这回合的输出x和y返回。
   详细规范说明见python,java和C++的示例程序，它们在主文件夹下，分别是bot.py, bot.java和bot.cpp。

2、裁判程序入口为main.py，需要提供三个参数，分别是游戏局数，程序一name，程序二name。
   1) 在终端以下格式的语句来运行裁判程序： 
		python main.py round player1_name player2_name
   2) 程序名作为参数输入时需要加上相应的后缀，如：
		python main.py 100 bot.py bot.cpp
   3) 如果提交的是预先编译过的结果，对于C++程序，运行示例为： python main.py 100 bot.py bot.exe
	  对于java程序，示例为： python main.py 100 bot.py Main.class
3、对局结果的log在终端查看，对局过程可以通过UI查看。 

三、参考
* [MinGW的安装&使用方法教程](http://blog.csdn.net/mlyjqx/article/details/75174688)