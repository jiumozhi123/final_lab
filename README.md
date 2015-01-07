Ubuntu系统：12.04

从github上下载代码，然后把final_lab-master.zip“解压到当前文件夹”并改名为final_lab，并把该文件夹copy到ubuntu系统某个地方，比如桌面上

打开一个shell，用命令找到文件夹final_lab，但并不进入这个文件夹，如果进入了可以执行cd ..退出

然后执行以下命令

mkdir Input（在final_lab的同级目录下建立输入文件夹）

mkdir Output（在final_lab的同级目录下建立输出文件夹）

dd if=/dev/zero of=Input/1G.img bs=1M count=1024（在Input文件夹下建立用二进制数字0填充的1G大小文件用于被传送，这个过程需要几分钟。注意文件名绝对不能错）

您也可以用您的文件来代替，但必须保证该文件在文件夹Input下，并且文件名为1G.img

建立好文件夹和1G大小文件后，cd final_lab进入final_lab文件夹

直接make编译，然后准备用socker server实现数据传送

执行./server （负责不断读取文件流并发送流）

再开一个shell，执行./client 127.0.0.1 （负责不断接收文件流并写入流）

然后程序会运行几分钟，读写流和发送接收流占用绝大部分时间

传送结束后，server端和client端会退出。如果中间遇到问题，它们也会退出并且在shell端打印错误报告

最后，接收到的文件被保存在Output文件夹下，文件传送所用的时间会记录在dbtime.time文件中