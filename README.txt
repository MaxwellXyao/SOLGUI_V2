【SOL开源】SOLGUI_V2.x

定位：为一些手持设备及小屏设备提供人机交互的解决方案（目前只考虑专用于OLED12864屏）

V2.0.0008更新：
修复了printf函数格式符%f型只能有一个的bug，可以使用多个%f。
以下语句已经可以正常使用：

SOLGUI_printf(0,0,F6X8,"%f,%.1f,%.2f",1.444,2.433,3.3246);

SOLGUI_Widget_OptionText(0,"%f,%.1f,%.2f",1.444,2.433,3.3246);

SOLGUI_Widget_Text(0,0,F6X8,"%f,%.1f,%.2f",1.444,2.433,3.3246);





SOL.lab
2016-5-24
by MaxwellXyao
email:917286114@qq.com


