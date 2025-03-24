/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

const int screenWidth = 800;
const int screenHeight = 450;

enum Direccion 
{
ARRIBA,
ABAJO,
DERECHA,
IZQUIERDA
};

class Entity {

public:
	Entity(int hp, int vel) {
		this->hp = hp;
		this->vel = vel;
	
	}

	bool Alive() {
	
		return true;
	
	}

	virtual void Movement() = 0;
protected:
	int hp;
	int vel;



};

class Enemy :public Entity {

public:
	Enemy(int hp, int vel) : Entity(hp, vel){
	
	
	
	}

protected:





};

class Player : public Entity {

private:
	int lives;
	int coins;
	Vector2 playerPos;
	Direccion dir;
public:

	Player(int hp, int vel) : Entity(1,2) {
	
		this->coins = 0;
		this->lives = 3;

		this->dir = ARRIBA;
		playerPos = { (float)screenWidth / 2, (float)screenHeight / 2 };

	
	}

	Vector2 GetPosition() { return this->playerPos; }
	Direccion GetDir() { return this->dir; }
	void Movement() override {
	
		if (IsKeyDown(KEY_RIGHT)) { playerPos.x += 2.0f; }
		if (IsKeyDown(KEY_LEFT)) { playerPos.x -= 2.0f; }
		if (IsKeyDown(KEY_UP)) 
		{ 
			playerPos.y -= 2.0f; 
			dir = ARRIBA;
		}
		if (IsKeyDown(KEY_DOWN)) 
		{ 
			playerPos.y += 2.0f; 
			dir = ABAJO;
		}
	}


};

class Orc : public Enemy{

public:

	Orc(int hp, int vel) :Enemy(1,1) {
	
	
	
	}


};

class Ogre : public Enemy {
public:

	Ogre(int hp, int vel) : Enemy(3, 1) {
	
	
	
	
	}


};
class Mummy : public Enemy {
public:

	Mummy(int hp, int vel) : Enemy(6, 1) {




	}


};


int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture logo = LoadTexture("sprites/personaje/128x128_persona7.png");
	
	const int screenWidth = 800;
	const int screenHeight = 450;
	SetTargetFPS(60);

	int seconds = 4;

		//Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
	// game loop
		Player p(1,2);
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{



		p.Movement();
			


		//-------------------------------------- DRAWING -------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);
		if (p.GetDir() == ARRIBA)
		{
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);
		}
		else if (p.GetDir() == ABAJO) 
		{
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, RED);
		
		}
		//DrawCircleV(p.GetPosition(), 50, MAROON);

		EndDrawing();
			
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(logo);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
