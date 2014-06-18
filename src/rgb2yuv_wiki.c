/**
 * @file rgb2yuv_wiki.c
 *
 * RGB2YUV from Wikipedia
 */

#include "rgb2yuv.h"

#define RGB2Y(R, G, B) (0.299 * R + 0.587 * G + 0.114 * B)
#define RGB2U(R, G, B) (-0.14713 * R - 0.28886 * G + 0.436 * B + 128)
#define RGB2V(R, G, B) (0.615 * R - 0.51499 * G - 0.10001 * B + 128)

void rgb2yuv_wiki(uint8_t *pixels, int count)
{
	int t;
	int r, g, b;

	for (t = 0; t < count * 4; t += 4)
	{
		r = pixels[t + 1];
		g = pixels[t + 2];
		b = pixels[t + 3];
		pixels[t + 1] = RGB2Y(r,g,b);
		pixels[t + 2] = RGB2U(r,g,b);
		pixels[t + 3] = RGB2V(r,g,b);
	}

}

