#pragma once
#ifndef _repo
#define _repo
#include "draw.h"


ObjectDescription* add(ObjectDescription* elem, ObjectDescription* repo);

ObjectDescription* CreateLuncher(ObjectDescription* repo);

void DrawAll(ObjectDescription* repo);
#endif // !_repo

