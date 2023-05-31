#pragma once
#ifndef _draw
#define _draw
typedef enum { LUNCHER, CANNON, MISSLE, BARRIER } OBJECTKIND;

struct ObjectDescription
{
	OBJECTKIND kind;
	float x, dx;
	float y, dy;
	int alpha;
	bool enable;
	int lastShootTimeLuncher;
	int lastShootTimeCannon;
	bool shootLuncher;
	bool shootCannon;
	void (*modelAndDraw)(ObjectDescription* elem);
	ObjectDescription* next;
};

void drawMissleCannon(ObjectDescription* model);
void drawMissleLuncher(ObjectDescription* model);

void drawLuncher(ObjectDescription* model);
void drawCannon(ObjectDescription* model);
void drawBarrier(ObjectDescription* model);
#endif // !_draw
