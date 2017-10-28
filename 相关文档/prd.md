# 需求文档 #

###  1.项目名称 ###
      CanTool装置的开发
###  2.项目开发者 ###
      成员一：李琦
      成员二：柴军
      成员三：刘训瀚
      成员四：魏潇
###  3.项目开发环境 ###

      Windows平台


###  4.实现功能 ###
+ 能够搜索到本机所有可使用的COM口，并在弹出式ComboBox中以列表方式让用户选择CanTool装置在上位机中映射的COM口。并设置相应COM口波特率115200、数据位数8、停止位数1。这些设定内容可保存到CanToolApp设定文件中，供下次使用。
+ 能够实现CANtool装置的CAN速率设置、进入CAN工作状态（Open）、进入CAN初始化状态（ Close）。这些设定内容可保存到CanToolApp设定文件中，供下次使用。
+ 能够对接收到的多个CAN信息，通过CAN信息及CAN信号数据库进行解析，将CAN信息原始数据进行显示。并能对CAN信息中的CAN信号的物理值实时数据进行显示。
+ 搭建“CAN信息Message描述数据库”和“CAN信号Signal描述数据库”，App可以加载“CAN信息Message描述数据库”和“CAN信号Signal描述数据库”，从而完成CAN信号数据的解析。
+ 确定CAN信号在CAN信息中的排列方式
###  5.功能模块图 ###  
![cantool](https://github.com/li77/CanTool/blob/cj/CanToolApp.png?raw=true)
