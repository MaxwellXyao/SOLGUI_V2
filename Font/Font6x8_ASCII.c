#include"Font6x8_ASCII.h"
#include"SOLGUI_Type.h"
#include"Font_Macro.h"


//########################【6x8字库】########################
const u8 _Font6x8[][8] = {
/* 空格 */
 {
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}

/*  !  */
 ,{
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   ________,
   X_______,
   ________}


/*  "  */
 ,{
   X_X_____,
   X_X_____,
   X_X_____,
   ________,
   ________,
   ________,
   ________,
   ________}

/* #  */
 ,{
   _X_X____,
   _X_X____,
   XXXXX___,
   _X_X____,
   XXXXX___,
   _X_X____,
   _X_X____,
   ________}

/*  $  */
 ,{
   __X_____,
   _XXXX___,
   X_X_____,
   _XXX____,
   __X_X___,
   XXXX____,
   __X_____}

/*  %  */
 ,{
   XX______,
   XX__X___,
   ___X____,
   __X_____,
   _X______,
   X__XX___,
   ___XX___,
   ________}

/*  &  */
 ,{
   _XX_____,
   X__X____,
   X_X_____,
   _X______,
   X_X_X___,
   X__X____,
   _XX_X___,
   ________}

/*  '  */
 ,{
   XX______,
   _X______,
   X_______,
   ________,
   ________,
   ________,
   ________,
   ________}

/*  (  */
 ,{
   __X_____,
   _X______,
   X_______,
   X_______,
   X_______,
   _X______,
   __X_____,
   ________}

/*  )  */
 ,{
   X_______,
   _X______,
   __X_____,
   __X_____,
   __X_____,
   _X______,
   X_______,
   ________}

/*  *  */
 ,{
   ________,
   _X_X____,
   __X_____,
   XXXXX___,
   __X_____,
   _X_X____,
   ________,
   ________}

 ,{
   ________,
   __X_____,
   __X_____,
   XXXXX___,
   __X_____,
   __X_____,
   ________,
   ________}

 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   XX______,
   _X______,
   X_______}

 ,{
   ________,
   ________,
   ________,
   XXXXX___,
   ________,
   ________,
   ________,
   ________}

 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   XX______,
   XX______,
   ________}

 ,{
   ________,
   ____X___,
   ___X____,
   __X_____,
   _X______,
   X_______,
   ________,
   ________}

/* 0 */
 ,{
   _XXX____,
   X___X___,
   X__XX___,
   X_X_X___,
   XX__X___,
   X___X___,
   _XXX____,
   ________}

/* 1 */
 ,{
   __X_____,
   _XX_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   _XXX____,
   ________}

/* 2 */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   __XX____,
   _X______,
   X_______,
   XXXXX___,
   ________}

/* 3 */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   __XX____,
   ____X___,
   X___X___,
   _XXX____,
   ________}

/* 4 */
 ,{
   ___X____,
   __XX____,
   _X_X____,
   X__X____,
   XXXXX___,
   ___X____,
   ___X____,
   ________}

/* 5 */
 ,{
   XXXXX___,
   X_______,
   XXXX____,
   ____X___,
   ____X___,
   X___X___,
   _XXX____,
   ________}

/* 6 */
 ,{
   __XX____,
   _X______,
   X_______,
   XXXX____,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* 7 */
 ,{
   XXXXX___,
   ____X___,
   ___X____,
   __X_____,
   _X______,
   _X______,
   _X______,
   ________}

/* 8 */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   _XXX____,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* 9 */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   _XXXX___,
   ____X___,
   ___X____,
   _XX_____,
   ________}

/* ':' 3a */
 ,{
   ________,
   XX______,
   XX______,
   ________,
   XX______,
   XX______,
   ________,
   ________}

/* ';' 3b */
 ,{
   ________,
   ________,
   XX______,
   XX______,
   ________,
   XX______,
   _X______,
   X_______}


/* '<' 3c */
 ,{
   ___X____,
   __X_____,
   _X______,
   X_______,
   _X______,
   __X_____,
   ___X____,
   ________}

/* '=' 3d */
 ,{
   ________,
   ________,
   XXXXX___,
   ________,
   XXXXX___,
   ________,
   ________,
   ________}

/* '>' */
 ,{
   X_______,
   _X______,
   __X_____,
   ___X____,
   __X_____,
   _X______,
   X_______,
   ________}

/* '?' */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   ___X____,
   __X_____,
   ________,
   __X_____,
   ________}

/* @ */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   _XX_X___,
   X_X_X___,
   X_X_X___,
   _XXX____,
   ________}

/* A */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   XXXXX___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* B */
 ,{
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   ________}

/* C */
 ,{
   _XXX____,
   X___X___,
   X_______,
   X_______,
   X_______,
   X___X___,
   _XXX____,
   ________}

/* D */
 ,{
   XXX_____,
   X__X____,
   X___X___,
   X___X___,
   X___X___,
   X__X____,
   XXX_____,
   ________}

/* E */
 ,{
   XXXXX___,
   X_______,
   X_______,
   XXXX____,
   X_______,
   X_______,
   XXXXX___,
   ________}

/* F */
 ,{
   XXXXX___,
   X_______,
   X_______,
   XXXX____,
   X_______,
   X_______,
   X_______,
   ________}

/* G */
 ,{
   _XXX____,
   X___X___,
   X_______,
   X_______,
   X__XX___,
   X___X___,
   _XXXX___,
   ________}

/* H */
 ,{
   X___X___,
   X___X___,
   X___X___,
   XXXXX___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* I */
 ,{
   XXX_____,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   XXX_____,
   ________}

/* J */
 ,{
   __XXX___,
   ___X____,
   ___X____,
   ___X____,
   ___X____,
   X__X____,
   _XX_____,
   ________}

/* K */
 ,{
   X___X___,
   X__X____,
   X_X_____,
   XX______,
   X_X_____,
   X__X____,
   X___X___,
   ________}

/* L */
 ,{
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   XXXXX___,
   ________}

/* M */
 ,{
   X___X___,
   XX_XX___,
   X_X_X___,
   X_X_X___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* N */
 ,{
   X___X___,
   X___X___,
   XX__X___,
   X_X_X___,
   X__XX___,
   X___X___,
   X___X___,
   ________}

/* O */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* P */
 ,{
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   X_______,
   X_______,
   X_______,
   ________}

/* Q */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   X___X___,
   X_X_X___,
   X__X____,
   _XX_X___,
   ________}

/* R */
 ,{
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   X_X_____,
   X__X____,
   X___X___,
   ________}

/* S */
 ,{
   _XXX____,
   X___X___,
   X_______,
   _XXX____,
   ____X___,
   X___X___,
   _XXX____,
   ________}

/* T */
 ,{
   XXXXX___,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   ________}

/* U */
 ,{
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* V */
 ,{
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   ________}

/* W */
 ,{
   X___X___,
   X___X___,
   X___X___,
   X_X_X___,
   X_X_X___,
   X_X_X___,
   _X_X____,
   ________}

/* X */
 ,{
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   _X_X____,
   X___X___,
   X___X___,
   ________}

/* Y */
 ,{
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   ________}

/* Z */
 ,{
   XXXXX___,
   ____X___,
   ___X____,
   __X_____,
   _X______,
   X_______,
   XXXXX___,
   ________}

/* 5b */
 ,{
   XXX_____,
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   XXX_____,
   ________}

/* 5c */
 ,{
   ________,
   X_______,
   _X______,
   __X_____,
   ___X____,
   ____X___,
   ________,
   ________}

/* 5d */
 ,{
   XXX_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   XXX_____,
   ________}

/* 5e */
 ,{
   __X_____,
   _X_X____,
   X___X___,
   ________,
   ________,
   ________,
   ________,
   ________}

/* 5f */
 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   XXXXX___,
   ________}

/* 60 */
 ,{
   X_______,
   _X______,
   __X_____,
   ________,
   ________,
   ________,
   ________,
   ________}

/* a */
 ,{
   ________,
   ________,
   _XXX____,
   ____X___,
   _XXXX___,
   X___X___,
   _XXXX___,
   ________}

/* b */
 ,{
   X_______,
   X_______,
   X_XX____,
   XX__X___,
   X___X___,
   X___X___,
   XXXX____,
   ________}

/* c */
 ,{
   ________,
   ________,
   _XX_____,
   X__X____,
   X_______,
   X__X____,
   _XX_____,
   ________}

/* d */
 ,{
   ____X___,
   ____X___,
   _XX_X___,
   X__XX___,
   X___X___,
   X___X___,
   _XXXX___,
   ________}

/* e */
 ,{
   ________,
   ________,
   _XXX____,
   X___X___,
   XXXXX___,
   X_______,
   _XXX____,
   ________}

/* f */
 ,{
   __X_____,
   _X_X____,
   _X______,
   XXX_____,
   _X______,
   _X______,
   _X______,
   ________}

/* g */
 ,{
   ________,
   ________,
   _XXXX___,
   X___X___,
   X___X___,
   _XXXX___,
   ____X___,
   _XXX____}

/* h */
 ,{
   X_______,
   X_______,
   X_XX____,
   XX__X___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* i */
 ,{
   _X______,
   ________,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   ________}

/* j */
 ,{
   __X_____,
   ________,
   _XX_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   XX______}

/* k */
 ,{
   X_______,
   X_______,
   X__X____,
   X_X_____,
   XX______,
   X_X_____,
   X__X____,
   ________}

/* l */
 ,{
   XX______,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   XXX_____,
   ________}

/* m */
 ,{
   ________,
   ________,
   XX_X____,
   X_X_X___,
   X_X_X___,
   X___X___,
   X___X___,
   ________}

/* n */
 ,{
   ________,
   ________,
   X_XX____,
   XX_X____,
   X__X____,
   X__X____,
   X__X____,
   ________}

/* o */
 ,{
   ________,
   ________,
   _XX_____,
   X__X____,
   X__X____,
   X__X____,
   _XX_____,
   ________}

/* p */
 ,{
   ________,
   ________,
   XXX_____,
   X__X____,
   X__X____,
   XXX_____,
   X_______,
   X_______}

/* q */
 ,{
   ________,
   ________,
   _XXX____,
   X__X____,
   X__X____,
   _XXX____,
   ___X____,
   ___X____}

/* r */
 ,{
   ________,
   ________,
   _X_X____,
   _XX_____,
   _X______,
   _X______,
   _X______,
   ________}

/* s */
 ,{
   ________,
   ________,
   _XXX____,
   X_______,
   _XX_____,
   ___X____,
   XXX_____,
   ________}

/* t */
 ,{
   _X______,
   _X______,
   XXX_____,
   _X______,
   _X______,
   _X______,
   _XX_____,
   ________}

/* u */
 ,{
   ________,
   ________,
   X__X____,
   X__X____,
   X__X____,
   X__X____,
   _XXX____,
   ________}

/* v */
 ,{
   ________,
   ________,
   X___X___,
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   ________}

/* w */
 ,{
   ________,
   ________,
   X___X___,
   X___X___,
   X_X_X___,
   X_X_X___,
   _X_X____,
   ________}

/* X */
 ,{
   ________,
   ________,
   X___X___,
   _X_X____,
   __X_____,
   _X_X____,
   X___X___,
   ________}

/* y */
 ,{
   ________,
   ________,
   X__X____,
   X__X____,
   X__X____,
   _XXX____,
   ___X____,
   _XX_____}

/* z */
 ,{
   ________,
   ________,
   XXXXX___,
   ___X____,
   __X_____,
   _X______,
   XXXXX___,
   ________}

/* { */
 ,{
   __X_____,
   _X______,
   _X______,
   X_______,
   _X______,
   _X______,
   __X_____,
   ________}

/* | */
 ,{
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   ________}

/* } */
 ,{
   X_______,
   _X______,
   _X______,
   __X_____,
   _X______,
   _X______,
   X_______,
   ________}

/* ~ */
 ,{
   _XX_X___,
   X__X____,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}
   
/* DELETE */
 ,{
   XXXXXX__,
   XXXXXX__,
   XXXXXX__,
   XXXXXX__,
   XXXXXX__,
   XXXXXX__,
   XXXXXX__,
   ________}
//------------【系统图标】
/* 0x80 Up*/
 ,{
   ________,
   __X_____,
   _XXX____,
   X_X_X___,
   __X_____,
   __X_____,
   ________,
   ________}
/* 0x81 Down*/
,{
   ________,
   __X_____,
   __X_____,
   X_X_X___,
   _XXX____,
   __X_____,
   ________,
   ________} 
/* 0x82 Left*/
 ,{
   ________,
   ___X____,
   __X_____,
   _XXXX___,
   __X_____,
   ___X____,
   ________,
   ________} 
/* 0x83 Right*/
 ,{
   ________,
   __X_____,
   ___X____,
   _XXXX___,
   ___X____,
   __X_____,
   ________,
   ________}
/* 0x84 OK*/
 ,{
   ________,
   _X_X____,
   _X__X___,
   _XXXXX__,
   ____X___,
   ___X____,
   ________,
   ________}
/* 0x85 Back*/
 ,{
   ________,
   __X_____,
   _X______,
   XXXXX___,
   _X__X___,
   __X_X___,
   ________,
   ________}
/* 0x86 Cursor*/
 ,{
   ________,
   XXX_____,
   XXXX____,
   XXXXX___,
   XXXX____,
   XXX_____,
   ________,
   ________}
//--------【条转至页】
/* 0x87 Gotopage*/
 ,{
   ________,
   ___X____,
   ___XX___,
   ___XXX__,
   ___XX___,
   ___X____,
   ________,
   ________}
//--------【EDIT】
/* 0x88 edit*/
 ,{
   ________,
   X_______,
   _X______,
   __X_____,
   _X______,
   X_______,
   __XXXX__,
   ________}
/* 0x89 hide*/
 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   X_X_X___,
   ________}
//--------【状态】
///* 0x87 off1*/
// ,{
//   ________,
//   ________,
//   _X__X___,
//   __XX____,
//   __XX____,
//   _X__X___,
//   ________,
//   ________}
///* 0x88 on1*/
// ,{
//   ________,
//   ________,
//   _____X__,
//   X___X___,
//   _X_X____,
//   __X_____,
//   ________,
//   ________}
///* 0x89 off2*/
// ,{
//   ________,
//   _XXXX___,
//   X____X__,
//   X____X__,
//   X____X__,
//   X____X__,
//   _XXXX___,
//   ________}
///* 0x8a on2*/
// ,{
//   ________,
//   _XXXX___,
//   XXXXXX__,
//   XXXXXX__,
//   XXXXXX__,
//   XXXXXX__,
//   _XXXX___,
//   ________}
//--------【选表】
///* 0x87 list*/
// ,{
//   ________,
//   XXXXX___,
//   X___X___,
//   XXXXX___,
//   X_X_X___,
//   X___X___,
//   XXXXX___,
//   ________}
//--------【文件】
///* 0x89 Folder*/
// ,{
//   ________,
//   XXXX____,
//   X__X____,
//   XXXXXX__,
//   X____X__,
//   X____X__,
//   XXXXXX__,
//   ________}
//
///* 0x90 File*/
// ,{
//   ________,
//   XXXX____,
//   X___X___,
//   X____X__,
//   X_XX_X__,
//   X____X__,
//   XXXXXX__,
//   ________}
//--------【其他】
///* 0x91 temperature*/
// ,{
//   ________,
//   __X_____,
//   _X_X____,
//   _X_X____,
//   _XXX____,
//   XXXXX___,
//   _XXX____,
//   ________}
///* 0x92 degree Celsius*/
// ,{
//   ________,
//   _X______,
//   X_X_____,
//   _X__XX__,
//   ___X____,
//   ___X____,
//   ____XX__,
//   ________}
///* 0x93 degrees fahrenheit*/
// ,{
//   ________,
//   _X______,
//   X_X_____,
//   _X_XXX__,
//   ___X____,
//   ___XXX__,
//   ___X____,
//   ________}

};











