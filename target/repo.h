#pragma once
#ifndef _repo
#define _repo

#include "draw.h"
#define EXPLOSE 0.06f
#define BARRIER_COUNT 30
#define SHOOT_INTERVAL 40


long getGlobalTimerEventCount();

ObjectDescription* add(ObjectDescription* elem, ObjectDescription* repo);

ObjectDescription* CreateLuncher();

ObjectDescription* CreatePlain();

ObjectDescription* CreateMissleLuncher(ObjectDescription* luncher);
ObjectDescription* CreateMisslePlain(ObjectDescription* plain);


void DrawAll();
void CheckAllMisselAndTarget();

double delta(ObjectDescription* current, ObjectDescription* other);

float randomFloat();

bool isGameOn();

ObjectDescription* getLuncher();

ObjectDescription* getPlain();

ObjectDescription* CreateBarrier();


#endif // !_repo

