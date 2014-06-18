/**
 * @file rgb2yuv_novell_ch.c
 *
 * Implementation from Novell-ch
 * @see https://www.linux.org.ru/forum/development/10496233?lastmod=1403079647669#comment-10588399
 */

#include "rgb2yuv.h"

#define CLIP(X) ( (X) > 255 ? 255 : (X) < 0 ? 0 : X)
#define RGB2Y(R, G, B) CLIP(( (  66 * (R) + 129 * (G) +  25 * (B) + 128) >> 8) +  16)
#define RGB2U(R, G, B) CLIP(( ( -38 * (R) -  74 * (G) + 112 * (B) + 128) >> 8) + 128)
#define RGB2V(R, G, B) CLIP(( ( 112 * (R) -  94 * (G) -  18 * (B) + 128) >> 8) + 128)

void rgb2yuv_novell_ch(uint8_t *pixels, int count)
{
	int i, t;
	int y, u, v;
	int r, g, b;
	uint8_t *p = pixels;

	for (i = 0; i < count; i++)
	{
		t = i * 4;
		y = t + 1;
		u = y + 1;
		v = u + 1;
		r = p[t + 1];
		g = p[t + 2];
		b = p[t + 3];
		p[y] = RGB2Y(r,g,b);
		p[u] = RGB2U(r,g,b);
		p[v] = RGB2V(r,g,b);
	}
}
