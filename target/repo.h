#pragma once
#ifndef _repo
#define _repo
#include "draw.h"
#define EXPLOSE 0.01f


ObjectDescription* add(ObjectDescription* elem, ObjectDescription* repo);

ObjectDescription* CreateLuncher(ObjectDescription* repo);

ObjectDescription* CreateCannon(ObjectDescription* repo);

ObjectDescription* CreateMissleLuncher(ObjectDescription* repo, ObjectDescription* luncher);
ObjectDescription* CreateMissleCannon(ObjectDescription* repo, ObjectDescription* cannon);

void DrawAll(ObjectDescription* repo);
void CheckAllMisselAndTarget(ObjectDescription* repo);

float delta(ObjectDescription* current, ObjectDescription* other);
#endif // !_repo

