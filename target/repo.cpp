#include "repo.h"
#include "draw.h"
#include <cstddef>
#include <fstream>
#include <cmath>

std::fstream logger("maintarget.log", std::fstream::app);
long globalTimerEventCount = 0;

ObjectDescription* repo = NULL;
ObjectDescription* luncher = NULL;
ObjectDescription* cannon = NULL;


long getGlobalTimerEventCount() {
	return globalTimerEventCount;
}


ObjectDescription* add(ObjectDescription* elem) {

	elem->next = repo;
	repo = elem;
	return repo;
};

ObjectDescription* CreateLuncher()
{
	// init luncher
	ObjectDescription* o = new ObjectDescription;
	o->kind = LUNCHER;
	o->x = 0.5f;
	o->y = 0.0f;
	o->alpha = 0;
	o->dx = 0;
	o->dy = 0;
	o->lastShootTime = 0;
	o->shootEnable = false;
	o->enable = true;
	o->modelAndDraw = drawLuncher;
	luncher = add(o);
	return luncher;
}

ObjectDescription* CreateCannon()
{
	// init cannon
	ObjectDescription* o = new ObjectDescription;
	o->kind = CANNON;
	o->x = -0.5f;
	o->y = 0.0f;
	o->alpha = 0;
//	o->dx = 0;
//	o->dy = 0;
	o->dx = 0.01f;
	o->dy = 0.01f;

	o->lastShootTime = 0;
	o->shootEnable = false;
	o->enable = true;
	o->modelAndDraw = drawCannon;
	cannon = add(o);
	return cannon;
}

ObjectDescription* CreateMissleLuncher(ObjectDescription* luncher)
{
	ObjectDescription* o = new ObjectDescription;
	o->kind = MISSLE;
	o->x = luncher->x - 2*EXPLOSE;
	o->y = luncher->y;
	o->alpha = 0;
	o->dx = -0.01f;
	o->dy = 0.0f;
	o->lastShootTime = 0;
	o->shootEnable = false;
	o->enable = true;
	o->modelAndDraw = drawMissleLuncher;
	return add(o);
}

ObjectDescription* CreateMissleCannon(ObjectDescription* cannon)
{
	ObjectDescription* o = new ObjectDescription;
	o->kind = MISSLE;
	o->x = cannon->x + cannon->dx+2.0*EXPLOSE;
	o->y = cannon->y;
	o->alpha = 0;
	o->dx = 0.01f;
	o->dy = 0.0f;
	o->lastShootTime = 0;
	o->shootEnable = false;
	o->enable = true;
	o->modelAndDraw = drawMissleCannon;
	return add(o);
}


void DrawAll() {
	ObjectDescription* current = repo;

	while (current != NULL) {
		if (current->enable) {
			current->modelAndDraw(current);
		}
		current = current->next;
	}
	globalTimerEventCount++;
}


void CheckAllMisselAndTarget () {

	logger << globalTimerEventCount << ">";
	ObjectDescription* current = repo;

	while (current != NULL) {
		   //current->modelAndDraw(current);
		switch (current->kind) {
		case MISSLE: logger << "MISSLE(" << current->x << "," << current->y << "," << current->enable<<");";
		case CANNON: logger << "CANNON(" << current->x << "," << current->y << "," << current->enable << ");";
		case LUNCHER: logger << "LUNCHER(" << current->x << "," << current->y << "," << current->enable << ");";
		}

		if (current->kind == MISSLE && current ->enable) {
			ObjectDescription* other = current -> next;

			while (other != NULL)  {
				double d = delta(current, other);
				if (other->enable  &&  d < EXPLOSE) {
					switch (other->kind) {
						case CANNON: logger << "EXPOSED CANNON(" << other->x << "," << other->y << "," << other->enable << ");";
						case LUNCHER: logger << "EXPLOSED LUNCHER(" << other->x << "," << other->y << "," << other->enable << ");";
					}
					other->enable = false;
					current->enable = false;
				}
				other = other->next;
			}
		}
	    current = current->next;
	}
	logger << std::endl;
}

double delta(ObjectDescription* current, ObjectDescription* other)
{
	float ddx = current->x - other->x;
	float ddy = current->y - other->y;
	return sqrt(ddx*ddx + ddy*ddy);
}


float randomFloat()
{
	return  -0.9f + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2;
}

bool isGameOn() {
	return luncher->enable && cannon->enable;
}


ObjectDescription* getLuncher() {
	return luncher;
}

ObjectDescription* getCannon() {
	return cannon;
}


ObjectDescription* CreateBarrier(int side)
{
	ObjectDescription* res = repo;
	for (int i = 0; i < BARRIER_COUNT; i++) {
		ObjectDescription* o = new ObjectDescription;
		o->kind = BARRIER;
		o->x = fabs(randomFloat()) * side;
		o->y = randomFloat();
		o->alpha = 0;
		o->dx = 0.0f;
		o->dy = 0.0f;
		o->enable = true;
		o->modelAndDraw = drawBarrier;
		res = add(o);
	}
	return res;
}
