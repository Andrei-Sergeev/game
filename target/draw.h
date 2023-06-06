#pragma once
#ifndef _draw
#define _draw
typedef enum { LUNCHER, PLAIN, PLAIN_MISSLE, LUNCHER_MISSLE, BARRIER } OBJECTKIND;

struct ObjectDescription
{
	OBJECTKIND kind;
	float x, dx;
	float y, dy;
	int alpha;
	bool enable;
	int lastShootTime;
	bool shootEnable;
	void (*modelAndDraw)(ObjectDescription* elem);
	ObjectDescription* next;
};

void drawMisslePlain(ObjectDescription* model);
void drawMissleLuncher(ObjectDescription* model);

void drawLuncher(ObjectDescription* model);
void drawPlain(ObjectDescription* model);
void drawBarrier(ObjectDescription* model);
void drawCircle(float cx, float cy, float r, int num_segments);
void drawBack();
#endif // !_draw
