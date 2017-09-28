#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D\Box2D\Box2D.h"

#ifdef _DEBUG
#pragma comment (lib, "Box2D/libx86/Debug/Box2D.lib")
#endif

#define SCALE 0.01f // 1 meter = 100 pixels
#define METERS_TO_PIXELS(x) x/SCALE // pixels
#define PIXELS_TO_METERS(x) x*SCALE // meters

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:
	// World & Gravity
	b2Vec2 gravity;
	b2World* world;

	// (Static)
	// Body
	b2BodyDef groundDef;
	b2Body* ground;
	// Circle
	b2CircleShape groundCircle;
	b2FixtureDef groundFixture;

	// (Dynamic)
	// Body
	b2BodyDef mouseDef;
	b2Body* mouse;
	// Circle
	b2CircleShape mouseCircle;
	b2FixtureDef mouseFixture;

	bool debug;
};