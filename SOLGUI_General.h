#ifndef SOLGUI_GENERAL_H
#define SOLGUI_GENERAL_H

//##############################【参数】##############################
#define X_WIDTH         128		//X像素长
#define Y_WIDTH         64		//Y像素长
#define Y_PAGE			8		//Y方向页长度

#define SOLGUI_Fabs(num) (num<0)?-num:num						//用于数字显示，绝对值	

//###########################【内部】##############################
char SOLGUI_Find_Max(char input[],char num); 					//找数组最大值
char SOLGUI_Find_Min(char input[],char num); 					//找数组最大值
void SOLGUI_Graph_Wave_Init(void);								//波形RAM初始化
void SOLGUI_Show_Char(unsigned char x,unsigned char y,unsigned char ch,unsigned char mode);	 
void SOLGUI_Show_String(unsigned char x,unsigned char y,unsigned char *str,unsigned char mode);	

//##############################【API】##############################

/*----------------------------
屏幕上点的坐标：（左下角为零点）
	x：0~127
	y：0~63
----------------------------*/

//----------【基本操作】
void SOLGUI_Init(void);	 		//显示增强模块初始化
void SOLGUI_Refresh_GRAM(void);	//刷新GRAM																	

//----------【字符显示】
void SOLGUI_printf(unsigned char x,unsigned char y,unsigned char mode,const unsigned char* str,...);//格式化输出到屏幕（(x,y)显示坐标，mode=1正常，mode=0反白）
/*-------------------------------------------------------------------
【格式化输出】
此处的printf功能是PC上printf的一个子集
因此格式用法和PC的prinf一样：

0x01:格式符：
	%s,%S:字符串
	%c,%C:单个字符

	%f,%F:double浮点数（每个格式化字符串只能有一个，默认留3位小数）

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

//----------【图形显示】
void SOLGUI_DrawPoint(unsigned char x,unsigned char y,unsigned char t);	//画点，t=1点亮；t=0熄灭.

void SOLGUI_Graph_line(		unsigned char x0,unsigned char y0,		 //画线	（mode：0擦除线，1实线，2点线，3短划线）
							unsigned char xEnd,unsigned char yEnd,
							unsigned char mode
							);

void SOLGUI_Graph_Circle(	unsigned char x0,unsigned char y0,		//画圆（圆心，半径，1点亮0熄灭）
							unsigned char r,
							unsigned char mode
							);			

void SOLGUI_Graph_pictrue( 	unsigned char x,			//句柄x坐标	 		//图片(图标的句柄点在左上角)
							unsigned char y,			//句柄y坐标
							unsigned char x_len,		//图形长
							unsigned char y_len,		//图形宽
							unsigned char *pic,			//图(转换为一维数组)
							unsigned char mode 			//显示方式：1正常显示，0高亮显示
							);
/*---------------------------------------------------------------------------------------------
【注意！！！图片应储存为1维数组，取模方式列行式：数据水平，字节垂直，从左到右，从上到下扫描】
---------------------------------------------------------------------------------------------*/

//----------【图表显示】
							
void SOLGUI_Plot_Bar(			unsigned char x,			//句柄x坐标	 	//数值条(显示数值相对大小)
								unsigned char y,			//句柄y坐标
								unsigned char x_len,		//图形长
								unsigned char y_len,		//图形宽
								int graduated_max,			//标尺最大值
								int graduated_min,			//标尺最小值
								int Var_in,					//值输入
								unsigned char mode 			//样式：0填充条，1平衡条
);

void SOLGUI_Plot_Oscillogram(	unsigned char x,			//句柄x坐标	 //波形图
								unsigned char y,			//句柄y坐标
								unsigned char x_len,		//图形长
								unsigned char y_len,		//图形宽
								int graduated_max,			//上标尺
								int graduated_min,			//下标尺（负数有bug）
								unsigned char dis_num,		//要显示的数据个数
								int wave_in[]				//波形数组
								);

void SOLGUI_Plot_Waveform(		unsigned char x,			//句柄x坐标	 //波形图表(显示数值时域波动)
								unsigned char y,			//句柄y坐标
								unsigned char x_len,		//图形长
								unsigned char y_len,		//图形宽
								int graduated_max,			//标尺最大值
								int graduated_min,			//标尺最小值（负数有bug）
								unsigned char channel,		//使用通道(1,2)
								int Var_in					//欲显示波形的变量
								);
	
	

#endif
