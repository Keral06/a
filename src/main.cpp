/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>  // Add this include for std::vector

const int screenWidth = 1280;
const int screenHeight = 800;

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
    Entity(int hp, int vel, Vector2 initialPos) : playerPos(initialPos), Colision(initialPos) {
        this->hp = hp;
        this->vel = vel;
        dir = IDLE;
        status = true;
    }

	bool Alive() {
	
		return true;
	
	}
	Vector2 GetPosition() const { return this->playerPos; }
	Direccion GetDir() const { return this->dir; }

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

	Player(int hp, int vel) : Entity(hp, vel, {(float)screenWidth/2, (float)screenHeight/2}) {
		this->coins = 0;
		this->lives = 3;
		this->dir = ARRIBA;
	}


	void Movement() {
	    bool moved = false;
	    float nextX = playerPos.x;
	    float nextY = playerPos.y;
	    
	    if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W))
	    {
	        nextX += 2.0f;
	        nextY -= 2.0f;
	        dir = DIAGONAL1;
	        moved = true;
	    }
	    else if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W))
	    {
	        nextX -= 2.0f;
	        nextY -= 2.0f;
	        dir = DIAGONAL2;
	        moved = true;
	    }
	    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
	    {
	        nextX += 2.0f;
	        nextY += 2.0f;
	        dir = DIAGONAL3;
	        moved = true;
	    }
	    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
	    {
	        nextX -= 2.0f;
	        nextY += 2.0f;
	        dir = DIAGONAL4;
	        moved = true;
	    }
	    else if (IsKeyDown(KEY_D))
	    {
	        nextX += 2.0f;
	        dir = DERECHA;
	        moved = true;
	    }
	    else if (IsKeyDown(KEY_A))
	    {
	        nextX -= 2.0f;
	        dir = IZQUIERDA;
	        moved = true;
	    }
	    else if (IsKeyDown(KEY_W))
	    {
	        nextY -= 2.0f;
	        dir = ARRIBA;
	        moved = true;
	    }
	    else if (IsKeyDown(KEY_S))
	    {
	        nextY += 2.0f;
	        dir = ABAJO;
	        moved = true;
	    }

	    if (!moved) {
	        dir = IDLE;
	    }
	    
	    // Add bounds checking before applying movement
	    if (nextX >= 0 && nextX <= screenWidth - 128 &&
	        nextY >= 0 && nextY <= screenHeight - 128) {
	        playerPos.x = nextX;
	        playerPos.y = nextY;
	    }
	}
	friend class Enemy;



};

class Enemy : public Entity {
public:
    Enemy(int hp, int vel) : Entity(hp, vel, {0,0}) {
        int posicion = pos();
        if (posicion == 1) {
            playerPos = { ((float)screenWidth / 2) + 128,  128 / 2 };
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
	        playerPos.x += vel;  // Changed from -= to +=
	    }
	    else {
	        playerPos.x -= vel;  // Changed from += to -=
	    }

	    if (playerPos.y < player.y) {
	        playerPos.y += vel;  // Changed from -= to +=
	    }
	    else {
	        playerPos.y -= vel;  // Changed from += to -=
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

class Shoot : public Entity {
public:
    Shoot(Player p) : Entity(1, 1, p.GetPosition()) {
        playerPos = p.GetPosition();
        // Set direction based on arrow keys instead of player direction
        if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP)) {
            dir = DIAGONAL1;
        }
        else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP)) {
            dir = DIAGONAL2;
        }
        else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_DOWN)) {
            dir = DIAGONAL3;
        }
        else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_DOWN)) {
            dir = DIAGONAL4;
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            dir = DERECHA;
        }
        else if (IsKeyDown(KEY_LEFT)) {
            dir = IZQUIERDA;
        }
        else if (IsKeyDown(KEY_UP)) {
            dir = ARRIBA;
        }
        else if (IsKeyDown(KEY_DOWN)) {
            dir = ABAJO;
        }
        else {
            dir = p.GetDir(); // Fallback to player direction if no arrow key pressed
        }
    }
    
    // Add method to update bullet position
    void UpdatePosition() {
        switch(dir) {
            case ARRIBA:
                playerPos.y -= 5.0f;
                break;
            case ABAJO:
                playerPos.y += 5.0f;
                break;
            case DERECHA:
                playerPos.x += 5.0f;
                break;
            case IZQUIERDA:
                playerPos.x -= 5.0f;
                break;
            case DIAGONAL1:
                playerPos.x += 5.0f;
                playerPos.y -= 5.0f;
                break;
            case DIAGONAL2:
                playerPos.x -= 5.0f;
                playerPos.y -= 5.0f;
                break;
            case DIAGONAL3:
                playerPos.x += 5.0f;
                playerPos.y += 5.0f;
                break;
            case DIAGONAL4:
                playerPos.x -= 5.0f;
                playerPos.y += 5.0f;
                break;
            default:
                break;
        }
    }
};

class level  {





};






int main() {
    // Tell the window to use vsync and work on high DPI displays
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    // Create the window and OpenGL context
    InitWindow(screenWidth, screenHeight, "Hello Raylib");

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
    SearchAndSetResourceDir("resources");

    // Load a texture from the resources directory
    Texture logo = LoadTexture("sprites/personaje/128x128_persona7.png");
    Texture bulletTex = LoadTexture("Bullet_1.png");
    
    SetTargetFPS(60);
    
    Player p(1,2);
    std::vector<Shoot> bullets;
    
    while (!WindowShouldClose()) {
        p.Movement();
        
        // Handle bullet creation with arrow keys
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || 
            IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)) {
            // Add rate limiting for bullets
            static float shootTimer = 0.0f;
            if (shootTimer <= 0) {
                bullets.push_back(Shoot(p));
                shootTimer = 0.2f; // Shoot every 0.2 seconds while holding key
            }
            shootTimer -= GetFrameTime();
        }
        
        // Update and remove off-screen bullets
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                [](const Shoot& bullet) {
                    Vector2 pos = bullet.GetPosition();
                    return pos.x < 0 || pos.x > screenWidth ||
                           pos.y < 0 || pos.y > screenHeight;
                }
            ),
            bullets.end()
        );
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw player
        DrawTexture(logo, p.GetPosition().x, p.GetPosition().y, WHITE);
        
        // Update and draw bullets using bullet texture
        for(auto& bullet : bullets) {
            bullet.UpdatePosition();
            DrawTexture(bulletTex, bullet.GetPosition().x, bullet.GetPosition().y, WHITE);
        }
        
        EndDrawing();
    }
    
    // Cleanup
    UnloadTexture(logo);
    UnloadTexture(bulletTex);  // Don't forget to unload bullet texture
    CloseWindow();
    return 0;
}
