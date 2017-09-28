#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "Box2D\Box2D\Box2D.h"

#ifdef _DEBUG
#pragma comment (lib, "Box2D/libx86/Debug/Box2D.lib")
#endif


// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it

	gravity = b2Vec2(0.0f, -9.81f);
	world = new b2World(gravity);



	// TODO 4: Create a a big static circle as "ground"
	//Body part (abstract)
	groundDef.type = b2_staticBody;
	groundDef.position.Set(PIXELS_TO_METERS(SCREEN_WIDTH / 2), PIXELS_TO_METERS(SCREEN_HEIGHT / 2));
	ground = world->CreateBody(&groundDef);
	//Circle fixture
	groundCircle.m_radius = PIXELS_TO_METERS(300);
	groundFixture.shape = &groundCircle;
	ground->CreateFixture(&groundFixture);




	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	world->Step(1.0f / 60.0f, 8, 3);
	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		mouseDef.type = b2_dynamicBody;
		mouseDef.position.Set(PIXELS_TO_METERS(App->input->GetMouseX()), PIXELS_TO_METERS(App->input->GetMouseY()));
		mouse = world->CreateBody(&mouseDef);
		//Circle fixture
		mouseCircle.m_radius = PIXELS_TO_METERS(80);
		mouseFixture.shape = &mouseCircle;
		mouseFixture.density = 1.0f;
		mouseFixture.friction = 0.3f;
		mouse->CreateFixture(&mouseFixture);
	}


	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	/*
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}*/

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}
