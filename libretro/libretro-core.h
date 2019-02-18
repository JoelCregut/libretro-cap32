#ifndef LIBRETRO_CORE_H
#define LIBRETRO_CORE_H 1

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>

// DEVICE AMSTRAD
#define RETRO_DEVICE_AMSTRAD_KEYBOARD RETRO_DEVICE_SUBCLASS(RETRO_DEVICE_KEYBOARD, 0)
#define RETRO_DEVICE_AMSTRAD_JOYSTICK RETRO_DEVICE_SUBCLASS(RETRO_DEVICE_JOYPAD, 1)

#define PORTS_NUMBER 2
#define ID_PLAYER1 0
#define ID_PLAYER2 1

extern unsigned amstrad_devices[ PORTS_NUMBER ];

#define TEX_MAX_WIDTH 768
#define TEX_MAX_HEIGHT 544

//LOG
#if  defined(__ANDROID__) || defined(ANDROID)
#include <android/log.h>
#define LOG_TAG "RetroArch.Frodo"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#else
#define LOGI printf
#endif

//TYPES

#define UINT16 uint16_t
#define UINT32 uint32_t
#define uint32 uint32_t
#define uint8 uint8_t

//SCREEN 16BITS
//#define M16B

#ifdef M16B
 #define PIXEL_BYTES 1
 #define PIXEL_TYPE UINT16
 #define PITCH 2
#else
 #define PIXEL_BYTES 2
 #define PIXEL_TYPE UINT32
 #define PITCH 4
#endif

extern PIXEL_TYPE *Retro_Screen;

#ifdef M16B
    #define RGB2COLOR(r, g, b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))
#else
    #define RGB2COLOR(r, g, b) (b | ((g << 8) | (r << 16)))
#endif

#define WINDOW_MAX_SIZE (768*544)

// BIT OPERATIONS - MACROS
#define BIT_SET(var, bit)    var  = 1 << bit
#define BIT_ADD(var, bit)    var |= 1 << bit
#define BIT_CLEAR(var, bit)  var &= ~(1 << bit)
#define BIT_CHECK(var, bit)  ((var >> bit) & 1)
#define BIT_TOGGLE(var, bit) var ^= 1 << bit


// RETROGUI STATUS - BIT WISE
#define GUI_DISABLED     0
#define GUI_KEYBOARD     1
#define GUI_MENU         2
#define GUI_STATUSBAR    4
extern int gui_status;


// COMPUTER/EMU STATUS - BIT WISE
#define COMPUTER_OFF     0
#define COMPUTER_BOOTING 1
#define COMPUTER_READY   2
#define COMPUTER_DIRTY   8
extern int emu_status;

typedef struct {
   int model;
   int ram;
   int lang;
   uint32_t padcfg[PORTS_NUMBER];
} computer_cfg_t;
extern computer_cfg_t retro_computer_cfg;

//VKBD
#define NPLGN 12
#define NLIGN 5
#define NLETT 5

typedef struct {
	char norml[NLETT];
	char shift[NLETT];
	int val;
} Mvk;

extern Mvk MVk[NPLGN*NLIGN*2];

//STRUCTURES
typedef struct{
     signed short x, y;
     unsigned short w, h;
} retro_Rect;

typedef struct{
     unsigned char *pixels;
     unsigned short w, h,pitch;
} retro_Surface;

typedef struct{
     unsigned char r,g,b;
} retro_pal;

//VARIABLES
extern int pauseg;

void retro_message(const char *text);

//SCREEN FUNCTIONS
extern int retro_getStyle();
extern int retro_getGfxBpp();
extern int retro_getGfxBps();

#endif
