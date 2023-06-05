#include "repo.h"
#include "draw.h"
#include <cstddef>
#include <fstream>
#include <cmath>

std::fstream logger("maintarget.log", std::fstream::app);
long globalTimerEventCount = 0;

ObjectDescription* repo = NULL;
ObjectDescription* luncher = NULL;
ObjectDescription* plain = NULL;


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
	o->x = randomFloat()*0.8;
	o->y = -0.8f;
	o->alpha = 45;
	o->dx = 0.0f;
	o->dy = 0.0f;
	o->lastShootTime = 0;
	o->shootEnable = false;
	o->enable = true;
	o->modelAndDraw = drawLuncher;
	luncher = add(o);
	return luncher;
}

ObjectDescription* CreatePlain()
{
	// init plain
	ObjectDescription* o = new ObjectDescription;
	o->kind = PLAIN;
	o->x = randomFloat();
	o->dx = 0.01f;
	o->y = 0.5f+0.4f*randomFloat();
	o->alpha = 180+randomFloat()*180;

	o->lastShootTime = 0;
	o->shootEnable = false;
	o->enable = true;
	o->modelAndDraw = drawPlain;
	plain = add(o);
	return plain;
}

ObjectDescription* CreateMissleLuncher(ObjectDescription* luncher)
{
	ObjectDescription* o = new ObjectDescription;
	o->kind = LUNCHER_MISSLE;
	o->alpha = luncher->alpha;
	o->dx = 0.02f*cos(luncher->alpha/180.0*3.1415f);
	o->dy = 0.02f*sin(luncher->alpha/180.0*3.1415f);
	o->x = luncher->x +50 * EXPLOSE*o->dx;
	o->y = luncher->y + 50 * EXPLOSE*o->dy;
	o->lastShootTime = getGlobalTimerEventCount();
	o->shootEnable = false;
	o->enable = true;
	o->modelAndDraw = drawMissleLuncher;
	return add(o);
}

ObjectDescription* CreateMisslePlain(ObjectDescription* plain)
{
	ObjectDescription* o = new ObjectDescription;
	o->kind = PLAIN_MISSLE;
	o->x = plain->x + plain->dx+2.0*EXPLOSE;
	o->y = plain->y;
	o->alpha = 0;
	o->dx = plain->dx;
	o->dy = 0.0f;
	o->lastShootTime = getGlobalTimerEventCount();
	o->shootEnable = false;
	o->enable = true;
	o->modelAndDraw = drawMisslePlain;
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
		switch (current->kind) {
		case LUNCHER_MISSLE:
		case PLAIN_MISSLE:
			logger << "MISSLE(" << current->x << "," << current->y << "," << current->enable << ");"; break;
		case PLAIN: logger << "PLAIN(" << current->x << "," << current->y << "," << current->enable << ");"; break;
		case LUNCHER: logger << "LUNCHER(" << current->x << "," << current->y << "," << current->enable << ");"; break;
		}

		if ((current->kind == PLAIN_MISSLE || current->kind == LUNCHER_MISSLE)&& current ->enable) {
			ObjectDescription* other = current -> next;

			while (other != NULL)  {
				double d = delta(current, other);
				if (other->enable  &&  d < EXPLOSE) {
					switch (other->kind) {
					case PLAIN: other->enable = current->kind == PLAIN_MISSLE;
								logger << "EXPOSED PLAIN(" << other->x << "," << other->y << "," << other->enable << ");";
								break;
					case LUNCHER: 
							other->enable = current->kind == LUNCHER_MISSLE;
							logger << "EXPLOSED LUNCHER(" << other->x << "," << other->y << "," << other->enable << ");";
							break;
					case BARRIER:
						other->enable = false;
						current->enable = false;
						break;
					}
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
	return luncher->enable && plain->enable;
}


ObjectDescription* getLuncher() {
	return luncher;
}

ObjectDescription* getPlain() {
	return plain;
}


ObjectDescription* CreateBarrier()
{
	ObjectDescription* res = repo;
	for (int i = 0; i < BARRIER_COUNT; i++) {
		ObjectDescription* o = new ObjectDescription;
		o->kind = BARRIER;
		o->x = randomFloat();
		o->y = randomFloat()*0.5;
		o->alpha = 0;
		o->dx = 0.0f;
		o->dy = 0.0f;
		o->enable = true;
		o->modelAndDraw = drawBarrier;
		res = add(o);
	}
	return res;
}
