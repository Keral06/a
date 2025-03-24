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
IZQUIERDA,
DIAGONAL1,
DIAGONAL2,
DIAGONAL3,
DIAGONAL4,
IDLE
};

class Colision {
public:

	Colision(Vector2 posicion) {

		float widthThing = posicion.x + 128;
		float HeightThing = posicion.y - 128;
		Square = { widthThing, HeightThing,35,56 };
	
	}
protected:
	Rectangle Square;



};

class Entity :public Colision {

public:
	Entity(int hp, int vel) : Colision(playerPos){
		this->hp = hp;
		this->vel = vel;
	
	}

	bool Alive() {
	
		return true;
	
	}
	Vector2 GetPosition() { return this->playerPos; }
	Direccion GetDir() { return this->dir; }

	int pos(){
	
		int a = GetRandomValue(1,4);
		return a;
	
	} 

	
protected:
	int hp;
	int vel;
	Vector2 playerPos;
	Direccion dir;
	bool status = Alive();
	



};
class Player : public Entity {

private:
	int lives;
	int coins;

public:

	Player(int hp, int vel) : Entity(1, 2) {

		this->coins = 0;
		this->lives = 3;

		this->dir = ARRIBA;
		playerPos = { ((float)screenWidth / 2) + 128 + 128 / 2, ((float)screenHeight / 2) + 128 / 2 };


	}


	void Movement() {

		if (IsKeyDown(KEY_RIGHT))
		{
			playerPos.x += 2.0f;
			dir = DERECHA;
		}
		if (IsKeyDown(KEY_LEFT))
		{
			playerPos.x -= 2.0f;
			dir = IZQUIERDA;
		}
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
		if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP))
		{
			playerPos.x += 0.5f;
			playerPos.y -= 0.5f;
			dir = DIAGONAL1;
		}
		if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP))
		{
			playerPos.x -= 0.5f;
			playerPos.y -= 0.5f;
			dir = DIAGONAL2;
		}
		if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT))
		{
			playerPos.x += 0.5f;
			playerPos.y += 0.5f;
			dir = DIAGONAL3;
		}
		if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT))
		{
			playerPos.y += 0.5f;
			playerPos.x -= 0.5f;
			dir = DIAGONAL4;
		}
		else {

			dir = IDLE;

		}
	}
	friend class Enemy;



};

class Enemy :public Entity {

public:
	Enemy(int hp, int vel) : Entity(hp, vel){
		int posicion = pos();
		if (posicion == 1) {

			playerPos = { ((float)screenWidth / 2) + 128 + 128 / 2,  128 / 2 };
		}
		if (posicion == 2) {
			playerPos = { 128 + 128 / 2, ((float)screenHeight / 2) + 128 / 2 };

		}
		if (posicion == 3) {

			playerPos = { ((float)screenWidth / 2) + 128 + 128 / 2,-128 / 2 };
		}
		if (posicion == 4) {
			playerPos = { -128 - 128 / 2, ((float)screenHeight / 2) + 128 / 2 };

		}
		
	
	}

	void MovementEnemy(Player p) {

		Vector2 player = p.GetPosition();
		if (playerPos.x < player.x) {
			playerPos.x -= vel;

		}
		else {
			playerPos.x += vel;

		}

		if (playerPos.y < player.y) {
			playerPos.y -= vel;

		}
		else {
			playerPos.y += vel;

		}

	}


protected:





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

class Shoot : public Entity{
public:
	Shoot(Player p) : Entity(1,1) {
	
		Vector2 shootFrom = p.GetPosition();

		shootFrom = { shootFrom.x / 2, shootFrom.y / 2 };

		while (status == true) {
			if (IsKeyDown(KEY_RIGHT))
			{
				playerPos.x += 2.0f;
				dir = DERECHA;
			}
			if (IsKeyDown(KEY_LEFT))
			{
				playerPos.x -= 2.0f;
				dir = IZQUIERDA;
			}
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
			if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP))
			{
				playerPos.x += 0.5f;
				playerPos.y -= 0.5f;
				dir = DIAGONAL1;
			}
			if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP))
			{
				playerPos.x -= 0.5f;
				playerPos.y -= 0.5f;
				dir = DIAGONAL2;
			}
			if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT))
			{
				playerPos.x += 0.5f;
				playerPos.y += 0.5f;
				dir = DIAGONAL3;
			}
			if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT))
			{
				playerPos.y += 0.5f;
				playerPos.x -= 0.5f;
				dir = DIAGONAL4;
			}


			 
		}

	
	
	
	}
public:




};



class level  {





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
	
	const int screenHeight = 800;
	const int screenWidth = 1280;
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
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);
		
		}
		else if (p.GetDir() == IZQUIERDA)
		{
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);

		}
		else if (p.GetDir() == DERECHA)
		{
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);

		}
		else if (p.GetDir() == DIAGONAL1)
		{
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);

		}
		else if (p.GetDir() == DIAGONAL2)
		{
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);

		}
		else if (p.GetDir() == DIAGONAL3)
		{
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);

		}
		else if (p.GetDir() == DIAGONAL4)
		{
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);

		}
		else {
		
			DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);
		}
		
		if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) ) {
		
			Shoot hola(p);
		
		}

		EndDrawing();
			
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(logo);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
