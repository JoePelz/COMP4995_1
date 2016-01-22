#pragma once

#define DEFAULT_BITMAP "fields_medium.bmp"
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
#define MAP(x, y) (y * LockedRect.Pitch / 4 + x)
#define CLEAR_COLOR D3DCOLOR_XRGB(0, 0, 25)
#define FRAME_RATE_SMOOTHING 100

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#define WINDOWED_MODE 0
