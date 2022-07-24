#pragma once

#include <emmintrin.h>

#define GAME_NAME "KILLDEATH"

#define C_RES_WIDTH	  512
#define C_RES_HEIGHT  384
#define C_BPP         32
#define C_AREA_MEMORY_SIZE (C_RES_WIDTH * C_RES_HEIGHT * (C_BPP/8))
#define C_RES_MIDDLE (C_RES_WIDTH / 2)

#define CAL_AVGFPS 100

#define SIMD

#define CHARS_ON_BITMAP 10;


#pragma warning(disable: 4820)

typedef struct GAMEBITMAP{
	BITMAPINFO BitmapInfo;
	void* Memory;
} GAMEBITMAP;

typedef struct PIXEL32 {
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
	unsigned char Alpha;
} PIXEL32;

typedef struct PERFORMANCEDATA {
	unsigned long long Total_Frames_Rendered;
	int CurrentFrame;
	float RawFramesPerSec;
	MONITORINFO MonitorInfo;
	long MonitorWidth;
	long MonitorHeight;
	long long PerfFrequency;
	BOOL DisplayFps;
} PERFORMANCEDATA;

typedef struct SWORD {
	int SwordPosX;
	int SwordPosY;
	int SwordPrevPosX;
	int SwordPrevPosY;
	float Angle;
}SWORD;

typedef struct MONSTER {
	GAMEBITMAP Image;
	int Health;
	int PosX;
	int PosY;
	int Y1;
	int Y2;
}MONSTER;

typedef enum GAMESTATE {
	TITLESCREEN,
	GAMESCREEN,
	OPTIONSCREEN
}GAMESTATE;

typedef struct MONSTERLIST {
	MONSTER Monster;
	char* Next;
}MONSTERLIST;



LRESULT CALLBACK MainWndProc(_In_ HWND WindowHandle, _In_ UINT Message, _Inout_ WPARAM wParam, _In_ LPARAM lParam);

DWORD CreateMainGameWindow(HANDLE Instance);

BOOL GameIsAlreadyRunning(void);

void ProcessPlayerInput(void);

void RenderFrameGraphics(void);

DWORD Load32ppBitMapFile(_In_ char* FileName, _In_ GAMEBITMAP* BitMap);

DWORD InitializeBitMaps(void);

void RenderSword(_In_ int x, _In_ int y, _In_ int prevX, _In_ int prevY);

void BitmapToBuffer(_In_ GAMEBITMAP* BitMap, _In_ unsigned int Xpos, _In_ unsigned int Ypos);

void MonsterSpawn(_In_ MONSTER Monster);

void OnMouseMove(int PosX, int PosY);

void DrawTitleScreen();

void DrawGameScreen();

void DrawMonsterHitBox(_In_ MONSTER Monster);

void StringToBuffer(_In_ char* String,_In_ GAMEBITMAP* BitMap, _In_ unsigned int Xpos, _In_ unsigned int Ypos);

#ifdef SIMD
void ClearScreen(_In_ __m128i Color);
#else
void ClearScreen(_In_ PIXEL32* Pixel);
#endif