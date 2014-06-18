/**
 * @file rgb2yuv_tables.c
 *
 * Modified version RGB2YUV from Novell-ch to use tables instead of multiply
 */

#include "rgb2yuv.h"

#define RGB2Y(R, G, B) ((( t66[R] + t129[G] +  t25[B] + 128) >> 8) +  16)
#define RGB2U(R, G, B) (((-t38[R] -  t74[G] + t112[B] + 128) >> 8) + 128)
#define RGB2V(R, G, B) (((t112[R] -  t94[G] -  t18[B] + 128) >> 8) + 128)

static int t66[256], t129[256], t25[256], t38[256];
static int t74[256], t112[256], t94[256], t18[256];

void rgb2yuv_tables_init(void)
{
	int i;

	for (i = 0; i <= 255; i++)
	{
		t66[i] = i * 66;
		t129[i] = i * 129;
		t25[i] = i * 25;
		t38[i] = i * 38;
		t74[i] = i * 74;
		t112[i] = i * 112;
		t94[i] = i * 94;
		t18[i] = i * 18;
	}
}

void rgb2yuv_tables(uint8_t *pixels, int count)
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
