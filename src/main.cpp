//copia

#include "raylib.h"


#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>  // Add this include for std::vector

const int screenWidth = 1024 / 2;
const int screenHeight = 1024 / 2;
class Player;
class Enemy;
class Mummy;
class Orc;
class Shoot;
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

        DrawRectangle(posicion.x, posicion.y, widthThing, HeightThing, BLANK);
        Square = { posicion.x,posicion.y, widthThing, HeightThing };

    }
    void ColisionPlayer(Vector2 posicion) {

        DrawRectangle(posicion.x, posicion.y, 64, 64, BLANK);
        Square.x = posicion.x;
        Square.y = posicion.y;


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

    }


    Vector2 GetPosition() const { return this->playerPos; }
    Direccion GetDir() const { return this->dir; }



    int pos() {

        int a = GetRandomValue(1, 4);
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
    bool status;

public:
    friend int main();
    friend class Game;
    Player(int hp, int vel) : Entity(hp, vel, { (float)screenWidth / 2, (float)screenHeight / 2 }) {
        this->coins = 0;
        this->lives = 3;
        this->dir = ARRIBA;
        dire = 1;
        status = true;
    }
    int dire;
    void Draw() {
        //BeginDrawing();

        if (status == true) {
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

       /* BeginDrawing();*/
        Texture Abajo1 = LoadTexture("64x64/personaje.adelante2.png");
        Texture Abajo2 = LoadTexture("64x64/personaje.adelante1.png");
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

    void Death() {}
    friend class Enemy;
    friend class Colision;
    friend class Ogre;
};

class Enemy : public Entity {
public:
    friend class Shoot;
    Enemy(int hp, int vel) : Entity(hp, vel, { 0,0 }) {
        int posicion = pos();
        if (posicion == 1) {
            playerPos = { ((float)screenWidth / 2), 64 };
        }
        else if (posicion == 2) {
            playerPos = { 64, ((float)screenHeight / 2) };

        }
        else if (posicion == 3) {

            playerPos = { ((float)screenWidth / 2), (float)screenHeight - 64 * 2 };
        }
        else {
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

class Ogre : public Enemy {
private:
    int dire = 0;

    Texture Mon1 = LoadTexture("64x64/128x128_zombie7.png");
    Texture Mon2 = LoadTexture("64x64/128x128_zombie6.png");
public:

    Ogre() : Enemy(3, 1) {




    }
    bool CheckColisions(Player& p) {

        bool check = CheckCollisionRecs(this->Square, p.Square);
        if (check == true) {

            p.status = false;
        }

        return p.status;

    }

    void Update(Player p) {

        if (p.playerPos.x > 0) {

            playerPos.x += vel;

        }
        else {

            playerPos.x -= vel;

        }

        if (p.playerPos.y > 0) {

            playerPos.y += vel;
        }
        else {

            playerPos.y -= vel;

        }

    }
    void Draw() {

        /*BeginDrawing();*/
        if (dire <= 50) {

            DrawTexture(Mon2, GetPosition().x, GetPosition().y, WHITE);


        }
        else {

            DrawTexture(Mon1, GetPosition().x, GetPosition().y, WHITE);

        }

        if (dire == 100) { dire = 0; }
        dire++;

        /*EndDrawing();*/

    }

    /*void ColisionMonster(Player p) override {









   }*/

    friend class Colision;

};
class Shoot : public Entity {
public:
    friend class Enemy;

    bool ColisionBullet(Enemy s) {

        bool Check = CheckCollisionRecs(this->Square, s.Square);

        return Check;


    }
    Shoot(Player p) : Entity(1, 1, p.GetPosition()) {
        playerPos = { p.GetPosition().x + 65 / 2, p.GetPosition().y + (64) };
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
        switch (dir) {
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
        ColisionPlayer(playerPos);


    }


};

class level {
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

    

    Stage() : level() {

        stage = 1;

    }
    void StageUp() {

        stage++;

    }

    int CheckStage() {

        return stage;

    }



};


class Game {
private:

    Texture bulletTex = LoadTexture("Bullet_1.png");

public:

    Game() {

        Stage stage();
        level Level();
        /*  BeginDrawing();*/

    }

    void GameStart(Player& p, std::vector<Ogre>& enemigo, std::vector<Shoot>& bullets, int& og, int& ayxi, int& dire, int& ogreaux, int& bulletaux) {

        ClearBackground(BLACK);
        /*BeginDrawing();*/
        BeginDrawing();

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
        int bulletSize = bullets.size();



        /*  BeginDrawing();
          ClearBackground(RAYWHITE);*/

        if (GetRandomValue(1, 40) == 1 && ogreaux < 2) {

            Ogre auxiliar;
            enemigo.push_back(auxiliar);
            ogreaux++;

        }
        int i = 0;
        if (ogreaux > 0) {
            while (i < ogreaux) {

                enemigo[i].CheckColisions(p);

                if (p.status == true) {

                    enemigo[i].MovementEnemy(p);


                }

                enemigo[i].Draw();

                i++;

            }
            i = 0;
            int j = 0;
            int aux = 0;
            while (i < ogreaux) {

                while (j < bulletSize) {
                    /*if (ogreaux > 0) {*/
                        if (bullets[j].ColisionBullet(enemigo[i]) == true) {
                            if (ogreaux == 1) {
                                enemigo.pop_back();
                                ogreaux--;
                            }

                            else if (ogreaux > 1) {
                                aux = i;
                                while (aux < ogreaux - 1) {

                                    enemigo[aux] = enemigo[aux + 1];
                                    aux++;

                                }
                                enemigo.pop_back();
                                ogreaux--;

                            }
                            
                            aux = j;
                            if (bulletSize == 1) {

                                bullets.pop_back();
                                bulletSize--;
                            }
                            else if (bulletSize > 1) {
                                while (aux < bulletSize - 1) {

                                    bullets[aux] = bullets[aux + 1];
                                    aux++;
                                }

                                bullets.pop_back();
                                bulletSize--;
                            }
                            if (ogreaux == 0) { j == bulletSize; }
                            bulletSize--;
                        }


                        j++;
                    }
                
                j = 0;
                i++;


            }
        }








        // Update and draw bullets using bullet texture
        for (auto& bullet : bullets) {
            bullet.UpdatePosition();
            DrawTexture(bulletTex, bullet.GetPosition().x, bullet.GetPosition().y, WHITE);
        }

        EndDrawing();


        // Set background color (framebuffer clear color)
/*  EndDrawing();*/
    }


};

class Background : public Stage {
private:

    Texture suelo = LoadTexture("stage/64x64_fondo_desierto.png");
    Texture arbol1 = LoadTexture("stage/64x64_cesped_desierto.png");
    Texture arbol2 = LoadTexture("stage/64x64_cesped_desierto2.png");

public:
    int time = 0;
    friend int main();
    int currentTime = GetTime();
    void Draw() {
       /* BeginDrawing();*/
        int x = 0;
        DrawTexture(suelo, 64, 0, WHITE);
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 0, WHITE);
                }

            }
            x = x + 64;

        }
        x = 1024;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 0, WHITE);
                }

            }
            x = x - 64;

        }
        int y = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0, y, WHITE);
                }

            }
            y = y + 64;

        }
        y = 1024;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0, y, WHITE);
                }

            }
            y = y - 64;

        }
        y = 1024;
        x = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, y, WHITE);
                }

            }
            x = x + 64;

        }

       /* EndDrawing();*/
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


    //Texture bulletTex = LoadTexture("Bullet_1.png");


    SetTargetFPS(60);
    Player p(1, 2);

    std::vector<Ogre>enemigo;
    int bulletaux;

    Background desierto;
    /* Ogre enemigo;*/

     //creation of enemy vector
    int og = 0;
    //vector<Ogre> ogres(og);
    int ayxi = 0;
    int ogreaux = 0;
    std::vector<Shoot> bullets;
    int dire = 1;
    Game game;
    while (!WindowShouldClose()) {


        game.GameStart(p, enemigo, bullets, og, ayxi, dire, ogreaux, bulletaux);
        desierto.Draw();
        
        /* ClearBackground(RAYWHITE);*/
      /*   ClearBackground(RAYWHITE);           */
       /*  EndDrawing();*/
         //p.Movement();
         //p.Draw();

         //// Handle bullet creation with arrow keys
         //if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) ||
         //    IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)) {
         //    // Add rate limiting for bullets
         //    static float shootTimer = 0.0f;
         //    if (shootTimer <= 0) {
         //        bullets.push_back(Shoot(p));
         //        shootTimer = 0.2f; // Shoot every 0.2 seconds while holding key
         //    }
         //    shootTimer -= GetFrameTime();
         //}

         //// Update and remove off-screen bullets
         //bullets.erase(
         //    std::remove_if(bullets.begin(), bullets.end(),
         //        [](const Shoot& bullet) {
         //            Vector2 pos = bullet.GetPosition();
         //            return pos.x < 0 || pos.x > screenWidth ||
         //                pos.y < 0 || pos.y > screenHeight;
         //        }
         //    ),
         //    bullets.end()
         //);

         //BeginDrawing();
         //ClearBackground(RAYWHITE);

         //// Draw player
         //
         //enemigo.CheckColisions(p);
         //if (p.status == true) {
         //    enemigo.MovementEnemy(p);


         //    ayxi++;
         //    if (ayxi == 100) { ayxi = 0; }
         //}






         //

         //enemigo.Draw();
         //
         //
         //// Update and draw bullets using bullet texture
         //for(auto& bullet : bullets) {
         //    bullet.UpdatePosition();
         //    DrawTexture(bulletTex, bullet.GetPosition().x, bullet.GetPosition().y, WHITE);
         //}
         //
         //EndDrawing();





         //primero hago una update de los que ya hay y despues lo que tendr�a que hacer es crear nuevos
        /* int aux = 0;
         while (aux < og) {

             ogres[aux].Update(p);
             ogres[aux].ColisionMonster(p);

         }*/

    }

    // Cleanup
  /*  UnloadTexture(logo);*/
   /* UnloadTexture(bulletTex);*/  // Don't forget to unload bullet texture
    CloseWindow();
    return 0;
}
