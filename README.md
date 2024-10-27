#Library management system

## 简介

Library management system本来是我大一时的一个C语言实训作业，这是我的第一个比较完整的项目，觉得有纪念意义，于是想着保存下来。这个项目是仅使用C语言编写的。本项目主要用到的知识点有结构体，数据结构中的带有头结点的单链表，C语言的IO操作。

## 功能简介

![img](file:///E:/Library%20management%20system/截图/2.jpg)

### 1.登录

![img](file:///E:/Library%20management%20system/截图/1.jpg)

`用户名`：admin

`密码`：123456

### 2.录入图书信息

这是该图书管理系统的第一种初始化方式，允许用户通过键盘录入图书的信息。特别说明，ISBN不允许重复，在录入图书信息时，如果输入的ISBN在链表中其他书籍中已经存在，则不予通过。

![img](file:///E:/Library%20management%20system/截图/3.jpg)

### 3.浏览图书信息

当链表中有数据时，会将所有数据呈现出来，否则不会有数据。

![img](file:///E:/Library%20management%20system/截图/4.jpg)

### 4.图书信息修改

当图书信息录入有误时，允许用户通过ISBN或书名来唯一确定一本图书（这注定了该系统的小遗憾——不能有重名书籍），并对其的相关数据进行修改。

![img](file:///E:/Library%20management%20system/截图/5.jpg)

### 5.图书信息删除

允许用户通过ISBN来精确删除一本书籍的信息

![img](file:///E:/Library%20management%20system/截图/6.jpg)

### 6.追加图书信息

当用户想要新增书籍时，可以执行该操作，进行新增书籍。

![img](file:///E:/Library%20management%20system/截图/7.jpg)

### 7.导出图书信息

允许用户导出所有图书信息到本地

![img](file:///E:/Library%20management%20system/截图/8.jpg)

![img](file:///E:/Library%20management%20system/截图/9.jpg)

### 8.导入外部数据

这是该图书管理系统的第二种初始化方式，允许用户批量导入图书信息（后续操作不受影响），要导入的图书信息需要以规定的格式存放在规定的规定文件名的txt文本文件中。

![img](file:///E:/Library%20management%20system/截图/10.jpg)

![img](file:///E:/Library%20management%20system/截图/11.jpg)

### 9.修改用户密码

该系统可以修改用户密码，用户通过用户名和原始密码进入系统后，可以执行修改密码操作，修改后，直接退出图书管理系统，原始密码立即失效！

![img](file:///E:/Library%20management%20system/截图/12.jpg)

![img](file:///E:/Library%20management%20system/截图/13.jpg)

![img](file:///E:/Library%20management%20system/截图/14.jpg)

## 技术特点

`结构体定义`：书籍信息与用户均是使用结构体存储。

`C语言IO`：fprintf与fscanf用来写读文件，所有的信息都是存储在txt文件中。

`数据结构`：本项目主要用到的数据结构是带有头结点的单链表，主要操作便是链表的增删改查。

## 项目文件说明

`userInfo.txt`：存放用户的用户名与密码。

`books.txt`：存放初始化链表所需要的图书信息(在导入外部数据时使用)。

`booksInfo.txt`：导出的图书信息保存在该文件中。

## 使用说明

建议使用`dev c++`打开并编译运行

### 贡献和反馈

- 作为一个学生项目，Library management system 欢迎任何形式的贡献和反馈。
- 如果你有任何改进建议或发现了bug，请通过GitHub的Issues或Pull Requests与我联系。

### 许可

本项目采用 [MIT许可证](LICENSE)。详情请参阅 `LICENSE` 文件。

### 致谢

- 感谢所有对这个项目感兴趣的人。作为一个学生项目，Library management system可能存在不足之处，但你们的宽容和支持是我继续学习和改进的动力。

------

Simple Music Player 是一个不断学习和进步的项目。如果该项目有什么不好或错误的地方，还请多多包涵。Simple_Music_Player