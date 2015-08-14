#ifndef COLORS_HEADER
#define COLORS_HEADER
struct RGBA
{
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 0.7843137254901962f;
}RED, GREEN, BLUE, PINK;

struct twoBools
{
	bool rwo = 1;
	bool rwno = 0;
}tBOOLs;

void ColorizeMe()
{
	RED.r = 1;
	GREEN.g = 1;
	BLUE.b = 1;

	PINK.r = 0.5647058823529412f;
	PINK.b = 0.8274509803921569f;
}

#endif
