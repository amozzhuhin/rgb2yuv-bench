#include <time.h>

#include "rgb2yuv.h"
#include <stdlib.h>
#include <stdio.h>

#define PIXELS_COUNT	(100 * 1000 * 1000)

static uint8_t pixels_wiki[4 * PIXELS_COUNT];
static uint8_t pixels_novel_ch[4 * PIXELS_COUNT];
static uint8_t pixels_tables[4 * PIXELS_COUNT];
static uint8_t pixels_tables64[4 * PIXELS_COUNT];

int main(int argc, char *argv[])
{
	struct timespec now;
	clock_t start, finish;

	clock_gettime(CLOCK_REALTIME, &now);
	srand(now.tv_nsec);

	// prepare input buffers

	int i;
	for (i = 0; i < 4 * PIXELS_COUNT; i++)
	{
		uint8_t x = ((i % 4) * rand());
		pixels_wiki[i] = x;
		pixels_novel_ch[i] = x;
		pixels_tables[i] = x;
		pixels_tables64[i] = x;
	}

	// run conversations

	start = clock();
	rgb2yuv_wiki(pixels_wiki, PIXELS_COUNT);
	finish = clock();
	printf("rgb2yuv_wiki: %.3f sec\n", (float) (finish - start) / CLOCKS_PER_SEC);

	start = clock();
	rgb2yuv_novell_ch(pixels_novel_ch, PIXELS_COUNT);
	finish = clock();
	printf("rgb2yuv_novell_ch: %.3f sec\n", (float) (finish - start) / CLOCKS_PER_SEC);

	start = clock();
	rgb2yuv_tables_init();
	rgb2yuv_tables(pixels_tables, PIXELS_COUNT);
	finish = clock();
	printf("rgb2yuv_tables: %.3f sec\n", (float) (finish - start) / CLOCKS_PER_SEC);

	start = clock();
	rgb2yuv_tables64_init();
	rgb2yuv_tables64(pixels_tables64, PIXELS_COUNT);
	finish = clock();
	printf("rgb2yuv_tables64: %.3f sec\n", (float) (finish - start) / CLOCKS_PER_SEC);

#ifdef PRINT_PIXELS
	for (i = 0; i < 4 * PIXELS_COUNT; i++)
	{
		printf("%d: %d %d %d %d\n", i, pixels_wiki[i], pixels_novel_ch[i], pixels_tables[i], pixels_tables64[i]);
	}
#endif

	return 0;
}
