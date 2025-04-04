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
class Player;
class Enemy;
class Mummy;
class Orc;
class Ogre;
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
        BeginDrawing();
		float widthThing = 64;
		float HeightThing = 64;

       DrawRectangle( posicion.x, posicion.y, widthThing, HeightThing, BLUE);
		Square = {posicion.x,posicion.y, widthThing, HeightThing };
	
	}

   void ColisionPlayer(Vector2 posicion) {

       DrawRectangle(posicion.x, posicion.y,64,64, BLUE);
       Square.x = posicion.x;
       Square.y = posicion.y;
    
    
    }

   //bool ColisionMonster(Player p) {

   //    bool Check = CheckCollisionRecs(p.Square, Square); 

   //    return Check;




   // }
  /* 
   void BulletColision(Entity p) {

       bool Check = CheckCollisionRecs(this->Square, p.Square);




   }*/



    

    
protected:
	Rectangle Square;



};

class Entity :public Colision {
public:
    Entity(int hp, int vel, Vector2 initialPos) : playerPos(initialPos), Colision(initialPos) {
        this->hp = hp;
        this->vel = vel;
        dir = IDLE;
       
    }

	
	Vector2 GetPosition() const { return this->playerPos; }
	Direccion GetDir() const { return this->dir; }

   

	int pos(){
	
		int a = GetRandomValue(1,4);
		return a;
	
	} 
    Direccion dir;
	
protected:
	int hp;
	int vel;
	Vector2 playerPos;
	
	
	



};
class Player : public Entity {

private:
	int lives;
	int coins;
    Texture Abajo1 = LoadTexture("64x64/personaje.adelante2.png");
    Texture Abajo = LoadTexture("64x64/personaje.adelante1.png");
    Texture Abajo2 = LoadTexture("64x64/personaje.adelante3.png");
    Texture Diagonal12 = LoadTexture("64x64/personaje.derecha2.png");
    Texture Diagonal13 = LoadTexture("64x64/personaje.derecha3.png");
    Texture Diagonal22 = LoadTexture("64x64/personaje.izquierda2.png");
    Texture Diagonal23 = LoadTexture("64x64/personaje.izquierda3.png");
    Texture Atras1 = LoadTexture("64x64/personaje.detras1.png");
    Texture Atras2 = LoadTexture("64x64/personaje.detras2.png");


    Texture Muerte1 = LoadTexture("effects/muerte1.png");
    Texture Muerte2 = LoadTexture("effects/muerte2.png");
    Texture Muerte3 = LoadTexture("effects/muerte3.png");
    Texture Muerte4 = LoadTexture("effects/muerte4.png");


    bool status;
    int animationDeathAssist;
public:
    friend int main();
	Player(int hp, int vel) : Entity(hp, vel, {(float)screenWidth/2, (float)screenHeight/2}) {
		this->coins = 0;
		this->lives = 3;
		this->dir = ARRIBA;
        dire = 1;
        status = true;
        animationDeathAssist = 0;
	}
    int dire;
    void Draw() {
        BeginDrawing();
        if(status==true){
            if (dir == DIAGONAL1) {
                if (dire <= 50) {

                    DrawTexture(Diagonal23, GetPosition().x, GetPosition().y, WHITE);


                }
                else {

                    DrawTexture(Diagonal22, GetPosition().x, GetPosition().y, WHITE);

                }
            }
            else if (dir == DIAGONAL2)
            {
                if (dire <= 50) {

                    DrawTexture(Diagonal12, GetPosition().x, GetPosition().y, WHITE);


                }
                else {

                    DrawTexture(Diagonal13, GetPosition().x, GetPosition().y, WHITE);

                }

            }
            else if (dir == DIAGONAL3)
            {
                if (dire <= 50) {

                    DrawTexture(Atras1, GetPosition().x, GetPosition().y, WHITE);

                }
                else {

                    DrawTexture(Atras2, GetPosition().x, GetPosition().y, WHITE);

                }
            }
            else if (dir == DIAGONAL4)
            {
                if (dire <= 50) {

                    DrawTexture(Atras1, GetPosition().x, GetPosition().y, WHITE);

                }
                else {

                    DrawTexture(Atras2, GetPosition().x, GetPosition().y, WHITE);

                }
            }
            else if (dir == ARRIBA)
            {
                if (dire <= 50) {

                    DrawTexture(Atras1, GetPosition().x, GetPosition().y, WHITE);


                }
                else {

                    DrawTexture(Atras2, GetPosition().x, GetPosition().y, WHITE);

                }
            }
            else if (dir == DERECHA)
            {
                if (dire <= 50) {

                    DrawTexture(Diagonal12, GetPosition().x, GetPosition().y, WHITE);


                }
                else {

                    DrawTexture(Diagonal13, GetPosition().x, GetPosition().y, WHITE);

                }
            }
            else if (dir == IZQUIERDA)
            {
                if (dire <= 50) {

                    DrawTexture(Diagonal12, GetPosition().x, GetPosition().y, WHITE);


                }
                else {

                    DrawTexture(Diagonal13, GetPosition().x, GetPosition().y, WHITE);

                }
            }
            else if (dir == ABAJO)
            {


                if (dire <= 50) {

                    DrawTexture(Abajo1, GetPosition().x, GetPosition().y, WHITE);


                }
                else {

                    DrawTexture(Abajo2, GetPosition().x, GetPosition().y, WHITE);

                }

            }
            else if (dir == IDLE) {

                DrawTexture(Abajo, GetPosition().x, GetPosition().y, WHITE);
            }
            dire++;
            if (dire == 100) { dire = 0; }

        }
    
    }
	void Movement() {

        
	    bool moved = false;
	    float nextX = playerPos.x;
	    float nextY = playerPos.y;
        
        if (status == true) {
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

            ColisionPlayer(playerPos);

            // Add bounds checking before applying movement
            if (nextX >= 0 && nextX <= screenWidth - 128 &&
                nextY >= 0 && nextY <= screenHeight - 128) {
                playerPos.x = nextX;
                playerPos.y = nextY;
            }
        }

        else {
        
            Death();
        
        
        
        
        
        }

  
	}
    void Death() {
    
        if (animationDeathAssist < 50) {
        
            DrawTexture(Muerte1, GetPosition().x, GetPosition().y, WHITE);
        
        }
        else if(animationDeathAssist>=50 && animationDeathAssist<100){
        
            DrawTexture(Muerte2, GetPosition().x, GetPosition().y, WHITE);
        
        }
        else if (animationDeathAssist >= 100 && animationDeathAssist < 150) {
        
            DrawTexture(Muerte3 , GetPosition().x, GetPosition().y, WHITE);
        
        }
    animationDeathAssist++;
    
    
         }
	friend class Enemy;
    friend class Colision;
    friend class Ogre;


};

class Enemy : public Entity {
public:
    Enemy(int hp, int vel) : Entity(hp, vel, {0,0}) {
        int posicion = 4; /*pos();*/
        if (posicion == 1) {
            playerPos = { ((float)screenWidth / 2), 64 };
        }else if (posicion == 2) {
			playerPos = { 64, ((float)screenHeight / 2)};

		}else if (posicion == 3) {

			playerPos = { ((float)screenWidth / 2), (float)screenHeight - 64*2};
		}else {
			playerPos = { +64, ((float)screenHeight / 2) };

			}
    }
    friend class Colision;
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
        ColisionPlayer(playerPos);
	}
    

protected:





};



class Orc : public Enemy{

public:

	Orc(int hp, int vel) :Enemy(1,1) {
	
		
	
	}

	

    friend class Colision;



};

class Ogre : public Enemy {
private:
    int dire = 0;

    Texture Mon1 = LoadTexture("64x64/128x128_zombie7.png");
    Texture Mon2 = LoadTexture("64x64/128x128_zombie6.png");
public:

	Ogre() : Enemy(3, 1) {
	
	
	
	
	}
    bool CheckColisions(Player &p) {
    
        bool check = CheckCollisionRecs(this->Square, p.Square);
        if (check == true) {
        
            p.status = false;
        }

        return p.status;
    
    }

    void Update(Player p) {

        if (p.playerPos.x > 0) {

            playerPos.x +=vel;

        }
        else {

            playerPos.x -=vel;

        }

        if (p.playerPos.y > 0) {

            playerPos.y +=vel;
        }
        else {

            playerPos.y -=vel;

        }

    }
    void Draw() {
    
    
        if (dire <= 50) {

            DrawTexture(Mon2, GetPosition().x, GetPosition().y, WHITE);


        }
        else {

            DrawTexture(Mon1, GetPosition().x, GetPosition().y, WHITE);

        }

        if (dire == 100) { dire = 0; }
        dire++;
    
    
    
    }

     /*void ColisionMonster(Player p) override {

        







    }*/

    friend class Colision;

};
class Mummy : public Enemy {
public:

	Mummy(int hp, int vel) : Enemy(6, 1) {




	}
    friend class Colision;


};

class Shoot : public Entity {
public:
    Shoot(Player p) : Entity(1, 1, p.GetPosition()) {
        playerPos = { p.GetPosition().x +65/2, p.GetPosition().y +(64)};
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
protected:
    int levels;


public:

    level() {

        levels = 1;

    }

   void LevelUp() {

        levels++;

    }

};
class Stage : public level {

protected:
    int stage;
public:

    Stage();

    /*Stage() : level() {

        stage = 1;

    }*/
    void StageUp() {

        stage++;

    }

   int CheckStage() {

       return stage;

    }



};
class Game {

public:

    Game(Player p) {

        Stage();


    }


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
    Player p(1, 2);
    Ogre enemigo;
    //creation of enemy vector
    int og = 0;
    //vector<Ogre> ogres(og);
    int ayxi = 0;

    std::vector<Shoot> bullets;
    int dire = 1;

    while (!WindowShouldClose()) {
        p.Movement();
        p.Draw();

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
        
        enemigo.CheckColisions(p);
        if (p.status == true) {
            enemigo.MovementEnemy(p);


            ayxi++;
            if (ayxi == 100) { ayxi = 0; }
        }

       




        

        enemigo.Draw();
        
        
        // Update and draw bullets using bullet texture
        for(auto& bullet : bullets) {
            bullet.UpdatePosition();
            DrawTexture(bulletTex, bullet.GetPosition().x, bullet.GetPosition().y, WHITE);
        }
        
        EndDrawing();




        
        //primero hago una update de los que ya hay y despues lo que tendría que hacer es crear nuevos
       /* int aux = 0;
        while (aux < og) {

            ogres[aux].Update(p);
            ogres[aux].ColisionMonster(p);

        }*/

    }
    
    // Cleanup
    UnloadTexture(logo);
    UnloadTexture(bulletTex);  // Don't forget to unload bullet texture
    CloseWindow();
    return 0;
}
