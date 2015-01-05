从github上下载代码，然后把final_lab-master.zip解压到final_lab-master文件夹中，并copy到ubuntu系统某个地方

在文件夹final_lab-master的同级目录中建立文件夹Input和文件夹Output，这样我们就可以在同一个目录中看到3个文件夹了

每次传送文件前，需要把待传送文件copy到Input文件夹下。程序结束后，Output文件夹下也会得到同样的文件

每次传输文件前，还需要配置好文件名。直接进入文件夹final_lab-master，其中有个common.h文件，里面有2个宏定义Input和Output，分别定义待传送的文件路径和传送文件的目标路径。比如我之前传送的文件名是09.mp4。每次传送不同的文件时，都需要用gedit打开并修改这两个宏定义中最后的文件名。知道了这个原理，其实路径也是可以随意设定的

配置好路径和文件名后，先make clean清理（第一次可以不用），然后直接make编译

服务器端执行./server
（负责不断读取文件流并发送流）

客户端执行./client 127.0.0.1
（负责不断接收文件流并写入流）

因为本地实验环境是本机对本机，所以直接用文件流读写就可以copy文件了，事实上不需要用socket server通信。但socket server实际上是用来实现不同机之间的数据传输，只是我们的实验环境相对简单而已

传输结束后，server端和client端会退出。如果中间遇到问题，它们也会退出并在shell端打印错误报告。最后，文件传输所用的时间会记录在dbtime.time文件中