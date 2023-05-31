#pragma once
#ifndef _repo
#define _repo
#include "draw.h"
#define EXPLOSE 0.06f
#define BARRIER_COUNT 10


ObjectDescription* add(ObjectDescription* elem, ObjectDescription* repo);

ObjectDescription* CreateLuncher(ObjectDescription* repo);

ObjectDescription* CreateCannon(ObjectDescription* repo);

ObjectDescription* CreateMissleLuncher(ObjectDescription* repo, ObjectDescription* luncher);
ObjectDescription* CreateMissleCannon(ObjectDescription* repo, ObjectDescription* cannon);

ObjectDescription* CreateBarrier(ObjectDescription* repo, int side);

void DrawAll(ObjectDescription* repo);
void CheckAllMisselAndTarget(ObjectDescription* repo);

double delta(ObjectDescription* current, ObjectDescription* other);

float randomFloat();


#endif // !_repo

