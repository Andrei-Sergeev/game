#include "repo.h"
#include "draw.h"
#include <cstddef>
#include <cmath>


ObjectDescription* add(ObjectDescription* elem, ObjectDescription* repo) {

	elem->next = repo;
	repo = elem;
	return repo;
};

ObjectDescription* CreateLuncher(ObjectDescription* repo)
{
	// init luncher
	ObjectDescription* o = new ObjectDescription;
	o->kind = LUNCHER;
	o->x = 0.5f;
	o->y = 0.0f;
	o->alpha = 0.0f;
	o->dx = 0;
	o->dy = 0;
	o->lastShootTimeLuncher = 0;
	o->shootLuncher = false;
	o->enable = true;
	o->modelAndDraw = drawLuncher;
	return add(o, repo);
}

ObjectDescription* CreateCannon(ObjectDescription* repo)
{
	// init cannon
	ObjectDescription* o = new ObjectDescription;
	o->kind = CANNON;
	o->x = -0.5f;
	o->y = 0.0f;
	o->alpha = 0.0f;
//	o->dx = 0;
//	o->dy = 0;
	o->dx = 0.01;
	o->dy = 0.02;

	o->lastShootTimeCannon = 0;
	o->shootCannon = false;
	o->enable = true;
	o->modelAndDraw = drawCannon;
	return add(o, repo);
}

ObjectDescription* CreateMissleLuncher(ObjectDescription* repo, ObjectDescription* luncher)
{
	ObjectDescription* o = new ObjectDescription;
	o->kind = MISSLE;
	o->x = luncher->x - 2*EXPLOSE;
	o->y = luncher->y;
	o->alpha = 0.0f;
	o->dx = -0.01f;
	o->dy = 0.0f;
	o->lastShootTimeLuncher = 0;
	o->shootLuncher = false;
	o->enable = true;
	o->modelAndDraw = drawMissleLuncher;
	return add(o, repo);
};

ObjectDescription* CreateMissleCannon(ObjectDescription* repo, ObjectDescription* cannon)
{
	ObjectDescription* o = new ObjectDescription;
	o->kind = MISSLE;
	o->x = cannon->x + 2*EXPLOSE;
	o->y = cannon->y;
	o->alpha = 0.0f;
	o->dx = 0.01f;
	o->dy = 0.0f;
	o->lastShootTimeCannon = 0;
	o->shootCannon = false;
	o->enable = true;
	o->modelAndDraw = drawMissleCannon;
	return add(o, repo);
}
ObjectDescription* CreateBarrier(ObjectDescription* repo, int side)
{
	ObjectDescription* res = repo;
	for (int i = 0; i < BARRIER_COUNT; i++) {
		ObjectDescription* o = new ObjectDescription;
		o->kind = BARRIER;
		o->x = fabs(randomFloat())*side;
		o->y = randomFloat();
		o->alpha = 0.0f;
		o->dx = 0.0f;
		o->dy = 0.0f;
		o->enable = true;
		o->modelAndDraw = drawBarrier;
		res = add(o, res);
	}
	return res;
}
;


void DrawAll(ObjectDescription* repo) {
	ObjectDescription* current = repo;

	while (current != NULL) {
		if (current->enable) {
			current->modelAndDraw(current);
		}
		current = current->next;
	}

}


void CheckAllMisselAndTarget (ObjectDescription* repo) {

	ObjectDescription* current = repo;

	while (current != NULL) {
		   //current->modelAndDraw(current);

		if (current->kind == MISSLE) {
			ObjectDescription* other = current -> next;

			while (other != NULL)  {
				if (other->enable  && delta(current, other) < EXPLOSE) {
					other->enable = false;
					current->enable = false;
				}
				other = other->next;
			}
		}
	    current = current->next;
	}
}

double delta(ObjectDescription* current, ObjectDescription* other)
{
	return sqrt(pow(current->x - other->x, 2) + pow(current->y - other->y, 2));
}


float randomFloat()
{
	return  -0.9f + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2;
}