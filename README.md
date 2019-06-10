# -
原创
《程序设计应用基础》课程设计计划书
设计
题目	权力的游戏
课题
构思	我们希望可以通过对C语言的了解来制作一个第三人称角色扮演(RPG)游戏，这个游戏以乔治·R·R·马丁的奇幻小说《冰与火之歌》的故事为背景，可以让玩家扮演一位角色在一个《冰与火之歌》的世界中活动，玩家负责扮演这个角色在一个结构化规则下通过一些行动令所扮演角色发展，玩家在这个过程中的成功与失败取决于一个规则或行动方针的形式系统，我们的目的就是去用C语言去表达这个形式系统。
课程
设计
目的	
通过对一系列心事系统的设计，培养我们对C语言的动手能力，使我们巩固《C语言程序设计》课程学习的内容，掌握编写程序的基本方法与过程，强化我们对C语言的理解，掌握运行一个C程序的基本步骤，包括编辑、编译、链接和运行。
设计
内容
与步
骤	1.	通过用户自定义的save和load函数来实现游戏的存档和加载。
2.	利用循环结构打印进度条，使用PlaySound函数插入背景音乐。
3.	进入地图界面，并显示健康游戏忠告。
4.	利用getchar()函数按任意键进入地图及菜单界面。
5.	通过If结构读取方向键的ASCII码值实现角色在地图中坐标的改变。
6.	在game.h中通过结构体定义了角色模块，地图模块，道具模块，势力模块，野怪模块 ，通过共用体定义不同道具类型。
成员
分工	组长：李  扬 负责程序的设计以及源程序的编译。
成员：石涔熠 负责程序设计报告的撰写。
成员：康鹏灏 负责进行答辩工作准备。
课程设计计划与进度安排	4月26日：小组讨论进行选题，构思出程序的总体框架。
5月6日：开始着手设计算法，并验证。
5月7日：程序设计与调试。
5月14日：程序集成与调试及最终测试与完善。 
5月15日：完成整个程序。
5月20日：完成课程设计报告。
设计考核要求	编写程序，调试，测试。
完成设计报告。
参与班级内部程序展示与答辩。
教师组织答辩。
权力的游戏
交通运输工程学院 交通运输类1802班 石涔熠 李扬 康鹏灏
摘要：掌握编程和程序调试的技巧通过程序的设计训练和提高我们的基本技能，掌握结构体的功能、编程软件操作的基本知识、键盘上特殊键的获取以及图形方式下光标的显示，提高编程兴趣与编程水平，学会如何正确的书写程序设计说明文档，提高解决实际问题的能力，巩固语法规则的理解和掌握，学会通过源程序写出流程图，提高自学以及查阅资料的能力。
关键词：角色扮演游戏；背景音乐；字体颜色；多文件编译；选择结构；结构体；条件语句；循环结构；指针；数组；共用体；随机数;枚举；联合体；文件的输入输出
1.引言
C语言作为一门最通用的语言,在过去很流行,将来依然会如此。几乎每一个理工科或者其他专业的学生毫不例外地要学习它。在大学里,很多学校都把谭浩强教授的《C程序设计》作为入门教材,这是绝佳的选择。然而,要更进一步,更全面而深入地学习呢?显然有点力不从心。本书正是为了弥补这个缺憾而写的,希望能对想比较全面而深入学习C语言程序设计的人有所帮助。从C语言产生到现在,它已经成为最重要和最流行的编程语言之一。在各种流行编程语言中,都能看到C语言的影子,如Java的语法与C语言基本相同。学习、掌握C语言是每一个计算机技术人员的基本功之一。C语言功能丰富、表达能力强、使用灵活方便、应用面广、目标程序效率高、可移植性好，既具有高级语言的优点，又具有低级语言的许多特点，既适于系统软件，又方便地用来写应用软件。
2.设计思路
为了更加全面的学习c语言，本游戏包含了多种功能，其中编程时主要使用结构体，同时也是用将游戏描述出来。在编程之前，我们先分析了游戏的规则原理，并用图文表示出来，以便使编程的思路更加清晰。然后我们设计程序思路流程框图，还原流程图，随后开始规划编程。最后对程序进行分析改进，并且总结此次课程设计的优点和哪些不足。






3.程序框图
















4.实验设计要求
在此课程设计中，我们所做的程序均需要事先自行设计，这使我们分析程序和编程调试两方面都能得到实际锻炼。自行上机操作是学好程序设计语言的一个极为重要的环节，因此我们要事先做好实验预习，阅读实验指导书和教材中的相关内容，分析并填写程序的空缺，并事先编制好设计为主的实验程序。自行操作时细心观察记录各种现象和结果，结束后认真分析和思考实验中的各种现象，在实验报告中对实验结果进行总结和讨论，最后做好课程设计报告，该报告包括对基本概念和基本原理的归纳总结、程序验证的结果、自行设计的程序清单、运行过程的现象和结果分析等。
5.设计分析与结果
首先，我们通过自定义函数来实现模块化编译，可以通过它们来实现该程序的主要功能。其函数如下图。
 
我们首先在游戏程序开头新增了读档以及新用户注册功能，此功能通过用户自定义的save和load函数来实现回归和注册功能，通过此功能可以满足新老用户的需求以及作为一个RPG游戏的基本登陆功能。
   

然后我们通过for循环打印进度条，来实现欢迎界面，在欢迎界面我们通过PlaySound函数来实现背景音乐的插入，欢迎界面如下图。
 
欢迎界面过后进入地图界面，并打印健康游戏忠告，通过getchar()函数来实现按任意键继续的功能。按下任意键之后进入菜单界面，在菜单界面内，我们通过If结构读取方向键的ASCII码值实现角色在地图中坐标的改变，每次坐标改变时，通过ShowMap()函数将当前地图清空并重新打印，打印到当前坐标时改变字体颜色及背景，打印完当前地名后，变为初始颜色和背景。并通过自定义的ShowMapInfo()函数来打印地图简介，通过switch()函数来实现游戏菜单。
 
功能一通过自定义的ShowPlayerInfo函数来打印角色结构体中的各项属性信息。包括角色姓名、HP装备以及装备属性，

 
功能二通过自定义的ShowMonster函数来显示地图上的野怪功能，通过Fight函数结合随机数来实现攻击力的变化，当某一方血量为零时结束战斗，按方向键返回地图，操作界面为下图。

 
功能三通过Trade函数来实现装备的购买。
 
功能四在游戏的最后，我们新增了游戏存档功能，通过输入字符X就可以实现游戏的存档，方便下次进入游戏。
 
6.总结与体会
这次的课程设计实验是对我们进入大学以来学习C语言结果的一次大考验。自己动手，发现问题和解决问题。并发现了许多自己的不足，平时没掌握的知识在实践中暴漏，经过不断的思考，查阅书籍和上网查资料及上机运行，解决了大部分问题，还稍微有些小问题。但是，我相信在今的学习中，一定能把它解决好。当今计算机应用在生活中可以说得是无处不在。因此作为二十一世纪的大学来说掌握程序开发技术是十分重要的，而C语言又是最常见，功能最强大的一种高级语言，因此做好C语言课程设计是十分必要的。
团队精神不可少，分工合作也是必须的，对本组人员进行整理，分析其特点，再分配任务，然后进行综合应用，最后对所需的资料及要编的程序进行整理得出最后程序。
