#ifndef SOLGUI_INCLUDE_H
#define SOLGUI_INCLUDE_H

//#########################【SOLGUI版本信息】############################
#define SOLGUI_VERSION "2.0"

//##########################【SOLGUI源文件】############################
//-----------【移植设置】
#include"SOLGUI_Type.h"
#include"SOLGUI_Config.h"

//-----------【中间层】
#include"SOLGUI_Common.h"
#include"SOLGUI_Printf.h"
#include"SOLGUI_GBasic.h"
#include"SOLGUI_Picture.h"
//-----------【应用层】
#include"SOLGUI_Menu.h"
#include"SOLGUI_Widget.h"

/*##########################【使用说明】##########################
【1】字符串的格式化输出:

SOLGUI_printf(21,26,F8X10,"helloworld!");

此处的SOLGUI_printf功能是PC上printf的一个子集
因此格式用法和PC的prinf一样：

0x01:格式符：
	%s,%S:字符串
	%c,%C:单个字符

	%f,%F:double浮点数（每个格式化字符串只能带有一个，默认留3位小数）

	%b,%B:整型二进制
	%o,%O:整型八进制
	%d,%D:整型十进制（可有正负）
	%u,%U:整型十进制（可有正负）
	%x,%X:整型十六进制

0x02:参数（只有这三种）
	%07d：补零（数字最小显示长读7格，不足则用0在前面补齐）
	%-7d：左对齐（数字最小显示长度7格，不足则用空格在后面补齐）
	%.4f: 保留小数位数（保留4位小数，最多保留7位）

-------------------------------------------------------------------*/

#endif
