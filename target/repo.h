#pragma once
#ifndef _repo
#define _repo

#include "draw.h"
#define EXPLOSE 0.06f
#define BARRIER_COUNT 10
#define SHOOT_INTERVAL 40


long getGlobalTimerEventCount();

ObjectDescription* add(ObjectDescription* elem, ObjectDescription* repo);

ObjectDescription* CreateLuncher();

ObjectDescription* CreateCannon();

ObjectDescription* CreateMissleLuncher(ObjectDescription* luncher);
ObjectDescription* CreateMissleCannon(ObjectDescription* cannon);


void DrawAll();
void CheckAllMisselAndTarget();

double delta(ObjectDescription* current, ObjectDescription* other);

float randomFloat();

bool isGameOn();

ObjectDescription* getLuncher();

ObjectDescription* getCannon();

ObjectDescription* CreateBarrier(int side);


#endif // !_repo

