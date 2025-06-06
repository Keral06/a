
#include "raylib.h"
#include "resource_dir.h"
#include <vector> 
/*declarar las medidas de la pantalla jugable y de la pantalla en general*/
const int screenWidth = 1024 / 2 + 32 * 2;
const int screenHeight = 1024 / 2 + 64;
const int playerScreenX = 1024 / 2;
const int playerScreenY = 1024 / 2;
// declarar las clases que se usaran
class Boss;
class Colision;
class Player;
class Enemy;
class Mummy;
class Orc;
class Store;
class Shoot;
class Ogre;
class PowerUpLive;
class time;
class Title;
class Store;
class coins;
class HeavyMachineGun;
class ScreenNuke;
class Coffee;
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
//direccion usada para el movimiento del jugador y enemigo y las balas




class Colision {
public:
    Colision(Vector2 posicion) {
        
        float widthThing = 96 - 64;
        float HeightThing = 64 - 32;

        DrawRectangle(posicion.x, posicion.y, widthThing, HeightThing, BLANK);
        Square = { posicion.x,posicion.y, widthThing, HeightThing };

    }
    //dibuja un cuadrado invisible en el escenario para indicar la colision
    void ColisionPlayer(Vector2 posicion) {

        DrawRectangle(posicion.x, posicion.y, 32, 32, BLANK);
        Square.x = posicion.x;
        Square.y = posicion.y;


    }
    //dibuja un cuadrado invisible encima del jugador para poder detectar la colision
protected:
    Rectangle Square;
};

class Entity :public Colision {
public:
    Entity(int hp, float vel, Vector2 initialPos) : playerPos(initialPos), Colision(initialPos) {
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
    float vel;
    Vector2 playerPos;
    Sound Walk = LoadSound("sound effects/prairie king walk.ogg");
    Sound Die = LoadSound("sound effects/enemy death.ogg");

};
/*clase padre utilizada para declarar los valores (vida, velocidad) de tanto el player como los enemigos
tambien se utiliza para los sonidos de movimiento y muerte
*/
class Player : public Entity {

private:
    bool logEffectActive = false;
    float logEffectStartTime = 0.0f;
    Texture2D contento = LoadTexture("64x64/personaje.contento.png");
    Texture2D victoria = LoadTexture("64x64/personaje.saludo.png");
    bool followingGoofer = false;
    int lives;
    int money;
    Texture Abajo1 = LoadTexture("64x64/personaje.adelante2.png");
    Texture Abajo = LoadTexture("64x64/personaje.adelante1.png");
    Texture Abajo2 = LoadTexture("64x64/personaje.adelante3.png");
    Texture Diagonal12 = LoadTexture("64x64/personaje.derecha2.png");
    Texture Diagonal13 = LoadTexture("64x64/personaje.derecha3.png");
    Texture Diagonal22 = LoadTexture("64x64/personaje.izquierda2.png");
    Texture Diagonal23 = LoadTexture("64x64/personaje.izquierda3.png");
    Texture Atras1 = LoadTexture("64x64/personaje.detras1.png");
    Texture Atras2 = LoadTexture("64x64/personaje.detras2.png");
    Texture Comprar = LoadTexture("64x64/personaje.contento.png");
    Texture Humo1 = LoadTexture("effects/muerte.png");
    Texture Humo2 = LoadTexture("effects/muerte1.png");
    Texture Humo3 = LoadTexture("effects/muerte2.png");
    Texture Humo4 = LoadTexture("muerte3.png");
    Texture Humo5 = LoadTexture("muerte4.png");
    Sound death = LoadSound("song/cowboy_dead.wav");
    bool status;
    int bag = 0;
    float deathStartTime = 0;
    bool estaContento = false;
    float tiempoContento = 0.0f;

public:
    friend int main();
    friend class coins;
    friend class UI;
    friend class Game;
    friend class Orc;
    friend class Mariposa;
    friend class coins;
    friend class Coffee;
    friend Store;
    friend  bool PlayerPowerUpCoffee(Player& p, Coffee& pp);
    friend bool PlayerPowerUpHMG(Player& p, HeavyMachineGun& pp);
    friend bool PlayerPowerUpScreenNuke(Player& p, ScreenNuke& pp);
    friend bool PlayerPowerUpScreenMoney(Player& p, coins& pp);


    Player(int hp, int vel) : Entity(hp, vel, { (float)(playerScreenX + 128) / 2, 240 }) {
        this->money = 0;
        this->lives = 3;
        this->dir = ARRIBA;
        dire = 1;
        status = true;
        bag = 0;
    } //declara los valores iniciales del jugador
    int dire;
    void Unload() {
    
        UnloadTexture(contento);
        UnloadTexture(victoria);
        UnloadTexture(Abajo1);
        UnloadTexture(Abajo);
        UnloadTexture(Abajo2);
        UnloadTexture(Diagonal12);
        UnloadTexture(Diagonal13);
        UnloadTexture(Diagonal22);
        UnloadTexture(Diagonal23);
        UnloadTexture(Atras1);
        UnloadTexture(Atras2);
        UnloadTexture(Comprar);
        UnloadTexture(Humo1);
        UnloadTexture(Humo2);
        UnloadTexture(Humo3);
        UnloadTexture(Humo4);
        UnloadTexture(Humo5);
    }
    void playerAgain() {

        this->money = 0;
        this->lives = 3;
        this->dir = ARRIBA;
        this->vel = 2;
        dire = 1;
        status = true;
        bag = 0;

    }

    void SetContento(bool feliz) {
        estaContento = feliz;
        if (feliz) tiempoContento = 0.0f;
    }

    void Update() {

        if (estaContento) {
            float frameTime = GetFrameTime();
            tiempoContento += GetFrameTime();
            if (tiempoContento >= 1.0f) {  // Duración de 1 segundo
                estaContento = false;
            }
        }
    }


    void Draw() {
        float now = GetTime();
        if (logEffectActive) {
            if (now - logEffectStartTime < 10.0f) {
                DrawTexture(contento, GetPosition().x, GetPosition().y, WHITE);
                return;  // Prevent drawing other sprites while happy
            }
            else {
                logEffectActive = false;  // End effect
            }
        }
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

                    DrawTexture(Diagonal23, GetPosition().x, GetPosition().y, WHITE);

                }
                else {

                    DrawTexture(Diagonal22, GetPosition().x, GetPosition().y, WHITE);

                }
            }
            else if (dir == DIAGONAL4)
            {
                if (dire <= 50) {

                    DrawTexture(Diagonal12, GetPosition().x, GetPosition().y, WHITE);

                }
                else {

                    DrawTexture(Diagonal13, GetPosition().x, GetPosition().y, WHITE);

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

                    DrawTexture(Diagonal22, GetPosition().x, GetPosition().y, WHITE);


                }
                else {

                    DrawTexture(Diagonal23, GetPosition().x, GetPosition().y, WHITE);

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
    //dibuja el sprite indicado del jugador dependiendo de la direccion en la que se mueve
    void ResetPlayer(int level) {


        status = true;
        if (level == 5) {
            playerPos = { (float)(playerScreenX + 128) / 2, 240 };
            status = true;
        }
        else {

            playerPos = { (float)(playerScreenX + 128) / 2, 240 };
        }

    }
    //resetea al jugador cuando muere

    void Movement(int level) {


        Texture Abajo1 = LoadTexture("64x64/personaje.adelante2.png");
        Texture Abajo2 = LoadTexture("64x64/personaje.adelante1.png");
        bool moved = false;
        float nextX = playerPos.x;
        float nextY = playerPos.y;
        if (logEffectActive && (GetTime() - logEffectStartTime < 10.0f)) {
            return;
        }
        if (status == true) {

            if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W))
            {
                nextX += vel;
                nextY -= vel;;
                dir = DIAGONAL1;
                moved = true;

            }
            else if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W))
            {
                nextX -= vel;
                nextY -= vel;
                dir = DIAGONAL2;
                moved = true;

            }
            else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
            {
                nextX += vel;
                nextY += vel;
                dir = DIAGONAL3;
                moved = true;

            }
            else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
            {
                nextX -= vel;
                nextY += vel;
                dir = DIAGONAL4;
                moved = true;

            }
            else if (IsKeyDown(KEY_D))
            {
                nextX += vel;
                dir = DERECHA;
                moved = true;

            }
            else if (IsKeyDown(KEY_A))
            {
                nextX -= vel;
                dir = IZQUIERDA;
                moved = true;

            }
            else if (IsKeyDown(KEY_W))
            {
                nextY -= vel;
                dir = ARRIBA;
                moved = true;

            }
            else if (IsKeyDown(KEY_S))
            {
                nextY += vel;
                dir = ABAJO;
                moved = true;


            }

            if (!moved) {
                dir = IDLE;

                StopSound(Walk);
            }
            else {
                if (!IsSoundPlaying(Walk)) {
                    PlaySound(Walk);
                }//sonidos del jugador cuando se mueve

            }



            if (level == 1) {
                Rectangle lado1 = { 64, 32, 32, 512 };
                Rectangle lado2 = { 64, 32, 512, 32 };
                Rectangle lado3 = { 544, 32, 32, 512 };
                Rectangle lado4 = { 64, 512, 512, 32 };


                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones nivel 1
            else if (level == 2) {
                Rectangle lado1 = { 192, 160, 64, 32 };
                Rectangle lado2 = { 192, 160, 32, 64 };
                Rectangle lado3 = { 192, 416, 64, 32 };
                Rectangle lado4 = { 192, 384, 32, 64 };
                Rectangle lado5 = { 384, 160, 64, 32 };
                Rectangle lado6 = { 416, 160, 32, 64 };
                Rectangle lado7 = { 384, 416, 64, 32 };
                Rectangle lado8 = { 416, 384, 32, 64 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado6) &&
                    !CheckCollisionRecs(nextPlayerPos, lado7) &&
                    !CheckCollisionRecs(nextPlayerPos, lado8) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones nivel 2
            else if (level == 3) {
                Rectangle lado1 = { 320, 160, 32, 32 };
                Rectangle lado2 = { 320, 416, 32, 32 };
                Rectangle lado3 = { 192, 288, 32, 32 };
                Rectangle lado4 = { 448, 288, 32, 32 };
                Rectangle lado5 = { 96, 64, 64, 32 };
                Rectangle lado6 = { 96, 64, 32, 64 };
                Rectangle lado7 = { 512, 64, 32, 64 };
                Rectangle lado8 = { 480, 64, 64, 32 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };
                Rectangle lado13 = { 96, 448, 32, 64 };
                Rectangle lado14 = { 96, 480, 64, 32 };
                Rectangle lado15 = { 512, 448, 32, 64 };
                Rectangle lado16 = { 480, 480, 64, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado6) &&
                    !CheckCollisionRecs(nextPlayerPos, lado7) &&
                    !CheckCollisionRecs(nextPlayerPos, lado8) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12) &&
                    !CheckCollisionRecs(nextPlayerPos, lado13) &&
                    !CheckCollisionRecs(nextPlayerPos, lado14) &&
                    !CheckCollisionRecs(nextPlayerPos, lado15) &&
                    !CheckCollisionRecs(nextPlayerPos, lado16)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }


            }//colisiones nivel 3
            else if (level == 4) {
                Rectangle lado1 = { 224, 192, 96, 32 };
                Rectangle lado2 = { 352, 192, 96, 32 };
                Rectangle lado3 = { 224, 192, 32, 96 };
                Rectangle lado4 = { 416, 192, 32, 96 };
                Rectangle lado5 = { 224, 320, 32, 96 };
                Rectangle lado6 = { 224, 384, 96, 32 };
                Rectangle lado7 = { 352, 384, 96, 32 };
                Rectangle lado8 = { 416, 320, 32, 96 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado6) &&
                    !CheckCollisionRecs(nextPlayerPos, lado7) &&
                    !CheckCollisionRecs(nextPlayerPos, lado8) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }


            }//colisiones nivel 4
            else if (level == 5) {
                Rectangle lado1 = { 320, 160, 32, 32 };
                Rectangle lado2 = { 224, 224, 32, 32 };
                Rectangle lado3 = { 384, 224, 32, 32 };
                Rectangle lado4 = { 288, 416, 96, 32 };
                Rectangle lado5 = { 64, 288, 512, 32 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones boss
            else if (level == 51) {
                Rectangle lado1 = { 320, 160, 32, 32 };
                Rectangle lado2 = { 224, 224, 32, 32 };
                Rectangle lado3 = { 384, 224, 32, 32 };
                Rectangle lado4 = { 288, 416, 96, 32 };
                Rectangle lado5 = { 64, 288, 246, 32 };
                Rectangle lado6 = { 362, 288, 256, 32 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado6) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones boss
            else if (level == 6) {
                Rectangle lado1 = { 96, 64, 96, 32 };
                Rectangle lado2 = { 96, 64, 32, 96 };
                Rectangle lado3 = { 160, 128, 32, 32 };
                Rectangle lado4 = { 480, 64, 32, 32 };
                Rectangle lado5 = { 512, 64, 32, 64 };
                Rectangle lado6 = { 480, 128, 32, 32 };
                Rectangle lado7 = { 96, 448, 32, 96 };
                Rectangle lado8 = { 96, 480, 96, 32 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };
                Rectangle lado13 = { 160, 416, 32, 32 };
                Rectangle lado14 = { 480, 416, 32, 96 };
                Rectangle lado15 = { 448, 448, 32, 32 };
                Rectangle lado16 = { 512, 448, 32, 64 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado6) &&
                    !CheckCollisionRecs(nextPlayerPos, lado7) &&
                    !CheckCollisionRecs(nextPlayerPos, lado8) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12) &&
                    !CheckCollisionRecs(nextPlayerPos, lado13) &&
                    !CheckCollisionRecs(nextPlayerPos, lado14) &&
                    !CheckCollisionRecs(nextPlayerPos, lado15) &&
                    !CheckCollisionRecs(nextPlayerPos, lado16)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones nivel 6
            else if (level == 7) {
                Rectangle lado1 = { 128, 128, 32, 32 };
                Rectangle lado2 = { 160, 160, 32, 32 };
                Rectangle lado3 = { 416, 128, 32, 32 };
                Rectangle lado4 = { 384, 224, 32, 32 };
                Rectangle lado5 = { 384, 288, 32, 64 };
                Rectangle lado6 = { 224, 320, 32, 32 };
                Rectangle lado7 = { 448, 352, 32, 32 };
                Rectangle lado8 = { 160, 416, 32, 32 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };
                Rectangle lado13 = { 384, 416, 32, 32 };
                Rectangle lado14 = { 448, 416, 32, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado6) &&
                    !CheckCollisionRecs(nextPlayerPos, lado7) &&
                    !CheckCollisionRecs(nextPlayerPos, lado8) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12) &&
                    !CheckCollisionRecs(nextPlayerPos, lado13) &&
                    !CheckCollisionRecs(nextPlayerPos, lado14)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones nivel 7
            else if (level == 8) {
                Rectangle lado1 = { 64, 192, 120, 32 };
                Rectangle lado2 = { 224, 192, 88, 32 };
                Rectangle lado3 = { 352, 192, 88, 32 };
                Rectangle lado4 = { 480, 192, 88, 32 };
                Rectangle lado5 = { 64, 352, 120, 32 };
                Rectangle lado6 = { 224, 352, 88, 32 };
                Rectangle lado7 = { 352, 352, 88, 32 };
                Rectangle lado8 = { 480, 352, 88, 32 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado6) &&
                    !CheckCollisionRecs(nextPlayerPos, lado7) &&
                    !CheckCollisionRecs(nextPlayerPos, lado8) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones nivel 8

            else if (level == 9) {
                Rectangle lado1 = { 192, 160, 64, 64 };
                Rectangle lado2 = { 192, 352, 64, 32 };
                Rectangle lado3 = { 192, 416, 64, 32 };
                Rectangle lado4 = { 384, 160, 32, 64 };
                Rectangle lado5 = { 448, 160, 32, 64 };
                Rectangle lado6 = { 384, 352, 32, 32 };
                Rectangle lado7 = { 448, 352, 32, 32 };
                Rectangle lado8 = { 384, 416, 32, 32 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };
                Rectangle lado13 = { 448, 416, 32, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado6) &&
                    !CheckCollisionRecs(nextPlayerPos, lado7) &&
                    !CheckCollisionRecs(nextPlayerPos, lado8) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12) &&
                    !CheckCollisionRecs(nextPlayerPos, lado13)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones nivel 9

            else if (level == 10) {
                Rectangle lado1 = { 64, 64, 224, 32 };
                Rectangle lado2 = { 384, 64, 192, 32 };
                Rectangle lado3 = { 64, 480, 224, 32 };
                Rectangle lado4 = { 384, 480, 192, 64 };
                Rectangle lado5 = { 320, 224, 32, 12 };
                Rectangle lado6 = { 256, 288, 32, 32 };
                Rectangle lado7 = { 384, 288, 32, 32 };
                Rectangle lado8 = { 320, 320, 32, 32 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado3) &&
                    !CheckCollisionRecs(nextPlayerPos, lado4) &&
                    !CheckCollisionRecs(nextPlayerPos, lado5) &&
                    !CheckCollisionRecs(nextPlayerPos, lado6) &&
                    !CheckCollisionRecs(nextPlayerPos, lado7) &&
                    !CheckCollisionRecs(nextPlayerPos, lado8) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones nivel 10
            else if (level == 11) {
                Rectangle lado1 = { 64, 64, 512, 32 };
                Rectangle lado2 = { 64, 480, 512, 32 };
                Rectangle lado9 = { 64, 32, 32, 512 };
                Rectangle lado10 = { 64, 32, 512, 32 };
                Rectangle lado11 = { 544, 32, 32, 512 };
                Rectangle lado12 = { 64, 512, 512, 32 };

                Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


                if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                    !CheckCollisionRecs(nextPlayerPos, lado2) &&
                    !CheckCollisionRecs(nextPlayerPos, lado9) &&
                    !CheckCollisionRecs(nextPlayerPos, lado10) &&
                    !CheckCollisionRecs(nextPlayerPos, lado11) &&
                    !CheckCollisionRecs(nextPlayerPos, lado12)) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }

            }//colisiones nivel 11
            ColisionPlayer(playerPos);
        }
    }






    //declara el movimiento del jugador dependiendo de la tecla que presione y la direccion en la que se mueve
    //declara las posiciones donde el jugador no puede acceder, colisiones
    void DeathAnim() {


        float currentTime = GetTime();
        float elapsed = currentTime - deathStartTime;

        if (elapsed < 0.2) {
            DrawTexture(Humo1, GetPosition().x, GetPosition().y, WHITE);
        }
        else if (elapsed < 0.3) {
            DrawTexture(Humo2, GetPosition().x, GetPosition().y, WHITE);
        }
        else if (elapsed < 0.4) {
            DrawTexture(Humo3, GetPosition().x, GetPosition().y, WHITE);
        }
        else if (elapsed < 0.5) {
            DrawTexture(Humo4, GetPosition().x, GetPosition().y, WHITE);
        }
        else if (elapsed < 0.6) {
            DrawTexture(Humo5, GetPosition().x, GetPosition().y, WHITE);
        }
        if (elapsed > 2) {

            status = true;


        }
        //else {
        //    // Animation finished
        //    status = true;
        //    ResetPlayer();
        //    // Optionally trigger a respawn or game over screen here
        //}
    }
    //animacion de muerte del jugador
    void Death() {

        if (!IsSoundPlaying(death)) {
            PlaySound(death); // Play the sound only if it�s not already playing
            lives--;

            deathStartTime = GetTime();
        }


    }
    //resetea al jugador despues de morir



    friend class Enemy;
    friend class Colision;
    friend class Ogre;
    friend class PowerUpLive;
    friend bool PlayerPowerUp(Player& p, PowerUpLive& pp);
};

class PowerUpLive : public Colision {
private:
    Texture vida = LoadTexture("items/128x128_cabeza.png");
    Vector2 pos;
    float appearTime;
public:
    friend class Game;
    friend class Player;
    friend class Colision;
    friend bool PlayerPowerUp(Player& p, PowerUpLive& pp);
    PowerUpLive(Vector2 position) : Colision(pos) {
        this->pos = position;

        DrawTexture(vida, pos.x, pos.y, WHITE);
        appearTime = GetTime();

    }
    //dibuja el item de vida +
    PowerUpLive(Player p) : Colision(pos) {

        p.lives++;

    }
    //suma la vida al jugador despues de recoger el item



    void UsePowerUp(Player& p) {
        p.lives++;


    }
    //suma la vida
    void Draw() {


        DrawTexture(vida, pos.x, pos.y, WHITE); //lo dibuja en la posicion en la que ha muerto el monstruo
        ColisionPlayer(pos);
    }
    //dibuja la textura y una colision alrededor para saber cuando el jugador la recoge


};

class Coffee : public Colision {
private:
    Texture vida = LoadTexture("items/128x128_taza.png");
    Vector2 pos;
    float appearTime;
public:
    friend class Game;
    friend class Player;
    friend class Colision;

    friend  bool PlayerPowerUpCoffee(Player& p, Coffee& pp);
    Coffee(Vector2 position) : Colision(pos) {
        this->pos = position;

        DrawTexture(vida, pos.x, pos.y, WHITE);
        appearTime = GetTime();

    }
    //dibuja el item de vida +
    Coffee(Player p) : Colision(pos) {



    }
    //suma la vida al jugador despues de recoger el item



    void UsePowerUp(Player& p) {

        p.vel += 0.2;

    }
    void StopUsing(Player p) {

        p.vel -= 0.2;


    }
    //suma la vida
    void Draw() {


        DrawTexture(vida, pos.x, pos.y, WHITE);
        ColisionPlayer(pos);
    }
    //dibuja la textura y una colision alrededor para saber cuando el jugador la recoge


};
int currentLevel;


class Store {
    Texture walkFrames[2];  // caminar
    Texture storemanTextures[5];
    Texture store;
    Texture botas[3];
    Texture pistola[3];
    Texture caja[3];

    Vector2 position = { 255 + 65, 0 };
    float animTime = 0;
    const float animSpeed = 0.2f; // Velocidad cambio de frames
    const float walkSpeed = 100.0f;
    bool isWalking = true;
    int currentFrame = 0;
    bool hasAppeared = false;

    const int precios[3] = { 8, 10, 15 }; // Precios de los items
    int itemSeleccionado = -1; //  ninguno seleccionado
    const float rangoCompra = 50.0f;
    float tiempoTiendaAbierta = 0.0f;
    const float tiempoMaximoTienda = 20.0f; // segundos abierta
    bool estaCerrando = false;

    std::vector<int> inventario;
    const Vector2 inventarioPos = { 20, 400 };
    const float espacioentreitems = 35.0f;
    const int maxItemsVisible = 5;

    float ultimaCompraTime = 0.0f;
    const float compraCooldown = 1.0f;
    bool puedeComprar = true;
    Texture texturaContento;
    bool jugadorContento = false;
    float tiempoContento = 0.0f;
    const float duracionContento = 1.5f;
    Sound buy = LoadSound("song/cowboy_secret.wav");
    Sound walking = LoadSound("song/Cowboy_Footsteps.wav");

    int nivelBotas = 1;
    int nivelPistola = 1;
    int nivelCubo = 1;
    const int preciosBotas[3] = { 8, 20, 10 };
    const int preciosPistola[3] = { 10, 20, 30 };
    const int preciosCubo[3] = { 15, 30, 45 };
    int primero = 0;



public:
    friend int main();
    friend coins;
    friend Player;
    friend Entity;
    friend Colision;
    friend Game;
    Store() {
        // Cargar texturas de caminata
        walkFrames[0] = LoadTexture("64x64/128x128_p4.png");
        walkFrames[1] = LoadTexture("64x64/128x128_p4-1.png");

        // Cargar todas las texturas del tendero
        storemanTextures[0] = LoadTexture("64x64/128x128_p4.png");
        storemanTextures[1] = LoadTexture("64x64/128x128_p4-1.png");
        storemanTextures[2] = LoadTexture("64x64/128x128_p4-2.png");
        storemanTextures[3] = LoadTexture("64x64/128x128_p4-3.png");
        storemanTextures[4] = LoadTexture("64x64/128x128_p4-4.png");

        //textura del fondo tienda
        store = LoadTexture("tienda_red.png");

        //textura de las cosas de la tienda 
        botas[0] = LoadTexture("tienda/botas.png");

        botas[1] = LoadTexture("tienda/botas2.png");
        botas[2] = LoadTexture("tienda/cabeza.png");
        pistola[0] = LoadTexture("tienda/pistola.png");
        pistola[1] = LoadTexture("tienda/pistola2.png");
        pistola[2] = LoadTexture("tienda/pistola3.png");
        caja[0] = LoadTexture("tienda/cubo.png");
        caja[1] = LoadTexture("tienda/cubo2.png");
        caja[2] = LoadTexture("tienda/cubo3.png");


        texturaContento = LoadTexture("64x64/personaje_contento.jpg");

    }




    void aparecer(float deltaTime) {


        if (!isWalking) return;

        // Animación de caminar
        animTime += deltaTime;
        if (animTime >= animSpeed) {
            animTime = 0;
            currentFrame = (currentFrame + 1) % 2;
        }

        // Movimiento hacia abajo
        position.y += walkSpeed * deltaTime;

        // Detenerse al llegar a pos 200
        if (position.y >= 200)
        {
            position.y = 200;
            isWalking = false;
            hasAppeared = true;
            currentFrame = 0;
        }

    }




    void desaparecer(float deltaTime) {
        if (!isWalking) return;

        // Animación de caminar
        animTime += deltaTime;
        if (animTime >= animSpeed) {
            animTime = 0;
            currentFrame = (currentFrame + 1) % 2;
        }

        // Movimiento hacia arriba 
        position.y -= walkSpeed * deltaTime;

        // Verificar si ha salido completamente de pantalla
        if (position.y <= 0) {
            position.y = 0;
            isWalking = false;
            hasAppeared = false;
            estaCerrando = false;
            tiempoTiendaAbierta = 0.0f;
            currentFrame = 0;

            itemSeleccionado = -1;
        }
    }

    void DrawInventario() {
        // Solo dibujar si hay items
        if (inventario.empty()) return;
        for (size_t i = 0; i < inventario.size(); i++) {
            int itemIndex = inventario[i];
            Vector2 itemPos = {
                inventarioPos.x,
                inventarioPos.y + (i * espacioentreitems) // Usar spacing negativo para apilar hacia arriba
            };

            // Dibujar el itrm
            switch (inventario[i]) {
            case 0: // Botas
                DrawTextureEx(botas[nivelBotas - 1], itemPos, 0, 0.7f, WHITE);
                break;
            case 1: // Pistola
                DrawTextureEx(pistola[nivelPistola - 1], itemPos, 0, 0.7f, WHITE);
                break;
            case 2: // Cubo
                DrawTextureEx(caja[nivelCubo - 1], itemPos, 0, 0.7f, WHITE);
                break;
            }
        }
    }



    void Compra(Vector2 playerPos, int& playerCoins, bool& tiendaActiva, float& vel, float& powerRate, int& bulletDamage, int level, int& lives) {
        if (!tiendaActiva) return;
        float currentTime = GetTime();


        if (currentTime - ultimaCompraTime < compraCooldown) return;

        itemSeleccionado = -1;
        Vector2 itemPositions[3] = { {210,250},{260,250},{310,250} };

        for (int i = 0; i < 3; i++) {
            if (CheckCollisionCircles(playerPos, rangoCompra, itemPositions[i], 0)) {
                itemSeleccionado = i;


                int precioActual = 0;
                bool puedeComprar = false;

                // Determinar precio según nivel
                switch (i) {
                case 0: // Botas
                    if (nivelBotas <= 3) {
                        precioActual = preciosBotas[nivelBotas - 1];
                        puedeComprar = playerCoins >= precioActual;
                    }
                    break;
                case 1: // Pistola
                    if (nivelPistola <= 3) {
                        precioActual = preciosPistola[nivelPistola - 1];
                        puedeComprar = playerCoins >= precioActual;
                    }
                    break;
                case 2: // Cubo
                    if (nivelCubo <= 3) {
                        precioActual = preciosCubo[nivelCubo - 1];
                        puedeComprar = playerCoins >= precioActual;
                    }
                    break;
                }

                if (puedeComprar && inventario.size() < maxItemsVisible) {
                    playerCoins -= precioActual;
                    inventario.push_back(i);
                    if (!IsSoundPlaying(buy)) PlaySound(buy);
                    ultimaCompraTime = currentTime;
                    jugadorContento = true;
                    tiempoContento = 0.0f;
                    if (i == 1) {
                        if (primero == 0 || primero == 1) {

                            vel += 0.5;

                        }
                        else if (primero == 2) {
                            lives++;
                        }
                        primero++;

                    }if (i == 2) {

                        powerRate -= 0.1;
                    }if (i == 2) {

                        bulletDamage += 1;
                    }

                    // Cerrar tienda inmediatamente después de comprar
                    CerrarTienda(tiendaActiva);
                }
                break;
            }
        }
    }

    void Update(float deltaTime, bool& tiendaActiva) {
        if (!hasAppeared && !estaCerrando) {
            aparecer(deltaTime); // 
            tiendaActiva = false;
        }
        else if (hasAppeared && !estaCerrando) {
            tiendaActiva = true;
            // Lógica mientras la tienda está abierta
            tiempoTiendaAbierta += deltaTime;
            if (tiempoTiendaAbierta >= tiempoMaximoTienda) { //si en un tiempo no hay ningun paso se cierra la tienda
                CerrarTienda(tiendaActiva);
            }
        }
        else if (estaCerrando) {
            desaparecer(deltaTime); // Salida
            tiendaActiva = false;
        }

        if (jugadorContento) {
            tiempoContento += deltaTime;
            if (tiempoContento >= duracionContento) {
                jugadorContento = false;
            }
        }
    }


    void CerrarTienda(bool& tiendaActiva) {
        estaCerrando = true;
        isWalking = true;
        tiendaActiva = false;
        tiempoTiendaAbierta = 0.0f;
    }

    void Draw() {
        // Dibujar al tendero 



        if (estaCerrando) {
            // Usar animación de caminar cuando se está yendo
            DrawTexture(walkFrames[currentFrame], position.x, position.y, WHITE);
        }
        else if (hasAppeared) {
            // Dibujar tendero quieto (textura de frente) cuando está en la tienda
            DrawTexture(storemanTextures[2], position.x, position.y, WHITE);

            // dibujar la tienda y los items cuando el tendero está quieto
            DrawTexture(store, 190, 230, WHITE);

            // Dibujar botas (posición 210,250)
            DrawTexture(botas[nivelBotas - 1], 210, 250, WHITE);
            DrawText(TextFormat("%d", preciosBotas[nivelBotas - 1]), 220, 280, 20, BLACK);

            // Dibujar pistola (posición 260,250)
            DrawTexture(pistola[nivelPistola - 1], 260, 250, WHITE);
            DrawText(TextFormat("%d", preciosPistola[nivelPistola - 1]), 270, 280, 20, BLACK);

            // Dibujar cubo (posición 310,250)
            DrawTexture(caja[nivelCubo - 1], 310, 250, WHITE);
            DrawText(TextFormat("%d", preciosCubo[nivelCubo - 1]), 320, 280, 20, BLACK);
        }
        else {
            // Dibujar animación de aparición (caminando hacia abajo)
            DrawTexture(walkFrames[currentFrame], position.x, position.y, WHITE);
        }

        DrawInventario(); //permanente

    }








};

class Enemy : public Entity {
public:
    friend class Shoot;
    Texture vida = LoadTexture("items/128x128_tumbacraneo.png");
    Texture humoo1 = LoadTexture("effects/128x128_piedra11.png");
    Texture humoo2 = LoadTexture("effects/128x128_piedra2.png");

    Texture humoo3 = LoadTexture("effects/128x128_piedra3.png");

    Texture humoo4 = LoadTexture("effects/128x128_piedra4.png");
    bool isSNfinished = false;
    Texture humoo5 = LoadTexture("effects/128x128_piedra5.png");
    friend int main();
    friend class coins;
    friend class UI;
    friend class Game;
    int SNstart_time;
    Enemy(int hp, float vel) : Entity(hp, vel, { 0, 0 }) {
        if (currentLevel == 11) {
            int posicion = GetRandomValue(1, 2);  // Only two spawn points
            if (posicion == 1) {
                playerPos = { 64, ((float)(playerScreenY + 64) / 2) };
            }
            else {
                playerPos = { (float)(playerScreenX + 32), ((float)(playerScreenY + 64) / 2) };
            }
        }
        else {
            int posicion = pos();
            if (posicion == 1) {
                playerPos = { ((float)(playerScreenX + 128) / 2), 32 };
            }
            else if (posicion == 2) {
                playerPos = { 64, ((float)(playerScreenY + 64) / 2) };
            }
            else if (posicion == 3) {
                playerPos = { ((float)(playerScreenX + 128) / 2), (float)playerScreenY };
            }
            else {
                playerPos = { (float)(playerScreenX + 32), ((float)(playerScreenY + 64) / 2) };
            }
        }
    }
    void unload() {
        UnloadTexture(vida);
        UnloadTexture(humoo1);
        UnloadTexture(humoo2);
        UnloadTexture(humoo3);
        UnloadTexture(humoo4);
        UnloadTexture(humoo5);
    
    }
    void SNAnim() {
        float currentTime = GetTime();
        float elapsed = currentTime - SNstart_time;

        if (elapsed < 0.1) {
            DrawTexture(humoo1, playerPos.x, playerPos.y, WHITE);
        }
        else if (elapsed < 0.2) {
            DrawTexture(humoo2, playerPos.x, playerPos.y, WHITE);
        }
        else if (elapsed < 0.3) {
            DrawTexture(humoo3, playerPos.x, playerPos.y, WHITE);
        }
        else if (elapsed < 0.4) {
            DrawTexture(humoo4, playerPos.x, playerPos.y, WHITE);
        }
        else if (elapsed < 0.5) {
            DrawTexture(humoo5, playerPos.x, playerPos.y, WHITE);
        }

        else {
            // Animation finished
            isSNfinished = true;
            // Optionally trigger a respawn or game over screen here
        }

    }

    //declara la posicion inicial del enemigo y sus atributos (velocidad, vida)
    friend class Colision;
    void MovementEnemy(Player p, int level) {
        Vector2 player = p.GetPosition();
        float nextY = playerPos.y;
        float nextX = playerPos.x;
        if (playerPos.x < player.x) {
            nextX += vel;  // Changed from -= to +=
        }
        else {
            nextX -= vel;  // Changed from += to -=
        }

        if (playerPos.y < player.y) {
            nextY += vel;  // Changed from -= to +=
        }
        else {
            nextY -= vel;  // Changed from += to -=
        }


        if (level == 1) {
            Rectangle lado1 = { 64, 32, 32, 224 };
            Rectangle lado2 = { 64, 32, 224, 32 };
            Rectangle lado3 = { 544, 32, 32, 224 };
            Rectangle lado4 = { 64, 512, 224, 32 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado3) &&
                !CheckCollisionRecs(nextPlayerPos, lado4) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }



        }
        else if (level == 2) {
            Rectangle lado1 = { 192, 160, 64, 32 };
            Rectangle lado2 = { 192, 160, 32, 64 };
            Rectangle lado3 = { 192, 416, 64, 32 };
            Rectangle lado4 = { 192, 384, 32, 64 };
            Rectangle lado5 = { 384, 160, 64, 32 };
            Rectangle lado6 = { 416, 160, 32, 64 };
            Rectangle lado7 = { 384, 416, 64, 32 };
            Rectangle lado8 = { 416, 384, 32, 64 };
            Rectangle lado9 = { 64, 32, 32, 224 };
            Rectangle lado10 = { 64, 32, 224, 32 };
            Rectangle lado11 = { 544, 32, 32, 224 };
            Rectangle lado12 = { 64, 512, 224, 32 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado3) &&
                !CheckCollisionRecs(nextPlayerPos, lado4) &&
                !CheckCollisionRecs(nextPlayerPos, lado5) &&
                !CheckCollisionRecs(nextPlayerPos, lado6) &&
                !CheckCollisionRecs(nextPlayerPos, lado7) &&
                !CheckCollisionRecs(nextPlayerPos, lado8) &&
                !CheckCollisionRecs(nextPlayerPos, lado9) &&
                !CheckCollisionRecs(nextPlayerPos, lado10) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado12) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }


        }
        else if (level == 3) {
            Rectangle lado1 = { 320, 160, 32, 32 };
            Rectangle lado2 = { 320, 416, 32, 32 };
            Rectangle lado3 = { 192, 288, 32, 32 };
            Rectangle lado4 = { 448, 288, 32, 32 };
            Rectangle lado5 = { 96, 64, 64, 32 };
            Rectangle lado6 = { 96, 64, 32, 64 };
            Rectangle lado7 = { 512, 64, 32, 64 };
            Rectangle lado8 = { 480, 64, 64, 32 };
            Rectangle lado9 = { 64, 32, 32, 224 };
            Rectangle lado10 = { 64, 32, 224, 32 };
            Rectangle lado11 = { 544, 32, 32, 224 };
            Rectangle lado12 = { 64, 512, 224, 32 };
            Rectangle lado13 = { 96, 448, 32, 64 };
            Rectangle lado14 = { 96, 480, 64, 32 };
            Rectangle lado15 = { 512, 448, 32, 64 };
            Rectangle lado16 = { 480, 480, 64, 32 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado3) &&
                !CheckCollisionRecs(nextPlayerPos, lado4) &&
                !CheckCollisionRecs(nextPlayerPos, lado5) &&
                !CheckCollisionRecs(nextPlayerPos, lado6) &&
                !CheckCollisionRecs(nextPlayerPos, lado7) &&
                !CheckCollisionRecs(nextPlayerPos, lado8) &&
                !CheckCollisionRecs(nextPlayerPos, lado9) &&
                !CheckCollisionRecs(nextPlayerPos, lado10) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado12) &&
                !CheckCollisionRecs(nextPlayerPos, lado13) &&
                !CheckCollisionRecs(nextPlayerPos, lado14) &&
                !CheckCollisionRecs(nextPlayerPos, lado15) &&
                !CheckCollisionRecs(nextPlayerPos, lado16) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }
        }
        else if (level == 4) {
            Rectangle lado1 = { 224, 192, 86, 32 };
            Rectangle lado2 = { 362, 192, 96, 32 };
            Rectangle lado3 = { 224, 192, 32, 86 };
            Rectangle lado4 = { 426, 192, 32, 96 };
            Rectangle lado5 = { 224, 320, 32, 86 };
            Rectangle lado6 = { 224, 384, 86, 32 };
            Rectangle lado7 = { 362, 384, 96, 32 };
            Rectangle lado8 = { 426, 320, 32, 96 };
            Rectangle lado9 = { 64, 32, 32, 224 };
            Rectangle lado10 = { 64, 32, 224, 32 };
            Rectangle lado11 = { 544, 32, 32, 224 };
            Rectangle lado12 = { 64, 512, 224, 32 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado3) &&
                !CheckCollisionRecs(nextPlayerPos, lado4) &&
                !CheckCollisionRecs(nextPlayerPos, lado5) &&
                !CheckCollisionRecs(nextPlayerPos, lado6) &&
                !CheckCollisionRecs(nextPlayerPos, lado7) &&
                !CheckCollisionRecs(nextPlayerPos, lado8) &&
                !CheckCollisionRecs(nextPlayerPos, lado9) &&
                !CheckCollisionRecs(nextPlayerPos, lado10) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado12) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }

        }
        else if (level == 6) {
            Rectangle lado1 = { 96, 64, 96, 32 };
            Rectangle lado2 = { 96, 64, 32, 96 };
            Rectangle lado3 = { 160, 128, 32, 32 };
            Rectangle lado4 = { 480, 64, 32, 32 };
            Rectangle lado5 = { 512, 64, 32, 64 };
            Rectangle lado6 = { 480, 128, 32, 32 };
            Rectangle lado7 = { 96, 448, 32, 96 };
            Rectangle lado8 = { 96, 480, 96, 32 };
            Rectangle lado9 = { 64, 32, 32, 224 };
            Rectangle lado10 = { 64, 32, 224, 32 };
            Rectangle lado11 = { 544, 32, 32, 224 };
            Rectangle lado12 = { 64, 512, 224, 32 };
            Rectangle lado13 = { 160, 416, 32, 32 };
            Rectangle lado14 = { 480, 416, 32, 96 };
            Rectangle lado15 = { 448, 448, 32, 32 };
            Rectangle lado16 = { 512, 448, 32, 64 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado3) &&
                !CheckCollisionRecs(nextPlayerPos, lado4) &&
                !CheckCollisionRecs(nextPlayerPos, lado5) &&
                !CheckCollisionRecs(nextPlayerPos, lado6) &&
                !CheckCollisionRecs(nextPlayerPos, lado7) &&
                !CheckCollisionRecs(nextPlayerPos, lado8) &&
                !CheckCollisionRecs(nextPlayerPos, lado9) &&
                !CheckCollisionRecs(nextPlayerPos, lado10) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado12) &&
                !CheckCollisionRecs(nextPlayerPos, lado13) &&
                !CheckCollisionRecs(nextPlayerPos, lado14) &&
                !CheckCollisionRecs(nextPlayerPos, lado15) &&
                !CheckCollisionRecs(nextPlayerPos, lado16) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }
        }

        else if (level == 7) {
            Rectangle lado1 = { 128, 128, 32, 32 };
            Rectangle lado2 = { 160, 160, 32, 32 };
            Rectangle lado3 = { 416, 128, 32, 32 };
            Rectangle lado4 = { 384, 224, 32, 32 };
            Rectangle lado5 = { 384, 288, 32, 64 };
            Rectangle lado6 = { 224, 320, 32, 32 };
            Rectangle lado7 = { 448, 352, 32, 32 };
            Rectangle lado8 = { 160, 416, 32, 32 };
            Rectangle lado9 = { 64, 32, 32, 224 };
            Rectangle lado10 = { 64, 32, 224, 32 };
            Rectangle lado11 = { 544, 32, 32, 224 };
            Rectangle lado12 = { 64, 512, 224, 32 };
            Rectangle lado13 = { 384, 416, 32, 32 };
            Rectangle lado14 = { 448, 416, 32, 32 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado3) &&
                !CheckCollisionRecs(nextPlayerPos, lado4) &&
                !CheckCollisionRecs(nextPlayerPos, lado5) &&
                !CheckCollisionRecs(nextPlayerPos, lado6) &&
                !CheckCollisionRecs(nextPlayerPos, lado7) &&
                !CheckCollisionRecs(nextPlayerPos, lado8) &&
                !CheckCollisionRecs(nextPlayerPos, lado9) &&
                !CheckCollisionRecs(nextPlayerPos, lado10) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado12) &&
                !CheckCollisionRecs(nextPlayerPos, lado13) &&
                !CheckCollisionRecs(nextPlayerPos, lado14) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }
        }
        else if (level == 8) {
            Rectangle lado1 = { 64, 192, 120, 32 };
            Rectangle lado2 = { 224, 192, 88, 32 };
            Rectangle lado3 = { 352, 192, 88, 32 };
            Rectangle lado4 = { 480, 192, 88, 32 };
            Rectangle lado5 = { 64, 352, 120, 32 };
            Rectangle lado6 = { 224, 352, 88, 32 };
            Rectangle lado7 = { 352, 352, 88, 32 };
            Rectangle lado8 = { 480, 352, 88, 32 };
            Rectangle lado9 = { 64, 32, 32, 224 };
            Rectangle lado10 = { 64, 32, 224, 32 };
            Rectangle lado11 = { 544, 32, 32, 224 };
            Rectangle lado12 = { 64, 512, 224, 32 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado3) &&
                !CheckCollisionRecs(nextPlayerPos, lado4) &&
                !CheckCollisionRecs(nextPlayerPos, lado5) &&
                !CheckCollisionRecs(nextPlayerPos, lado6) &&
                !CheckCollisionRecs(nextPlayerPos, lado7) &&
                !CheckCollisionRecs(nextPlayerPos, lado8) &&
                !CheckCollisionRecs(nextPlayerPos, lado9) &&
                !CheckCollisionRecs(nextPlayerPos, lado10) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado12) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }
        }
        else if (level == 9) {
            Rectangle lado1 = { 192, 160, 64, 64 };
            Rectangle lado2 = { 192, 352, 64, 32 };
            Rectangle lado3 = { 192, 416, 64, 32 };
            Rectangle lado4 = { 384, 160, 32, 64 };
            Rectangle lado5 = { 448, 160, 32, 64 };
            Rectangle lado6 = { 384, 352, 32, 32 };
            Rectangle lado7 = { 448, 352, 32, 32 };
            Rectangle lado8 = { 384, 416, 32, 32 };
            Rectangle lado9 = { 64, 32, 32, 224 };
            Rectangle lado10 = { 64, 32, 224, 32 };
            Rectangle lado11 = { 544, 32, 32, 224 };
            Rectangle lado12 = { 64, 512, 224, 32 };
            Rectangle lado13 = { 448, 416, 32, 32 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado3) &&
                !CheckCollisionRecs(nextPlayerPos, lado4) &&
                !CheckCollisionRecs(nextPlayerPos, lado5) &&
                !CheckCollisionRecs(nextPlayerPos, lado6) &&
                !CheckCollisionRecs(nextPlayerPos, lado7) &&
                !CheckCollisionRecs(nextPlayerPos, lado8) &&
                !CheckCollisionRecs(nextPlayerPos, lado9) &&
                !CheckCollisionRecs(nextPlayerPos, lado10) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado12) &&
                !CheckCollisionRecs(nextPlayerPos, lado13) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }
        }
        else if (level == 10) {
            Rectangle lado1 = { 64, 64, 224, 32 };
            Rectangle lado2 = { 384, 64, 192, 32 };
            Rectangle lado3 = { 64, 480, 224, 32 };
            Rectangle lado4 = { 384, 480, 192, 64 };
            Rectangle lado5 = { 320, 224, 32, 12 };
            Rectangle lado6 = { 256, 288, 32, 32 };
            Rectangle lado7 = { 384, 288, 32, 32 };
            Rectangle lado8 = { 320, 320, 32, 32 };
            Rectangle lado9 = { 64, 32, 32, 224 };
            Rectangle lado10 = { 64, 32, 224, 32 };
            Rectangle lado11 = { 544, 32, 32, 224 };
            Rectangle lado12 = { 64, 512, 224, 32 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado3) &&
                !CheckCollisionRecs(nextPlayerPos, lado4) &&
                !CheckCollisionRecs(nextPlayerPos, lado5) &&
                !CheckCollisionRecs(nextPlayerPos, lado6) &&
                !CheckCollisionRecs(nextPlayerPos, lado7) &&
                !CheckCollisionRecs(nextPlayerPos, lado8) &&
                !CheckCollisionRecs(nextPlayerPos, lado9) &&
                !CheckCollisionRecs(nextPlayerPos, lado10) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado12) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }
        }
        else if (level == 11) {
            Rectangle lado1 = { 64, 64, 512, 32 };
            Rectangle lado2 = { 64, 480, 512, 32 };
            Rectangle lado9 = { 64, 32, 32, 224 };
            Rectangle lado10 = { 64, 32, 224, 32 };
            Rectangle lado11 = { 544, 32, 32, 224 };
            Rectangle lado12 = { 64, 512, 224, 32 };
            Rectangle lado17 = { 384, 32, 192, 32 };
            Rectangle lado18 = { 64, 352, 32, 192 };
            Rectangle lado19 = { 384, 512, 192, 32 };
            Rectangle lado20 = { 544, 352, 32, 192 };

            Rectangle nextPlayerPos = { nextX, nextY, 32, 32 };


            if (!CheckCollisionRecs(nextPlayerPos, lado1) &&
                !CheckCollisionRecs(nextPlayerPos, lado2) &&
                !CheckCollisionRecs(nextPlayerPos, lado9) &&
                !CheckCollisionRecs(nextPlayerPos, lado10) &&
                !CheckCollisionRecs(nextPlayerPos, lado11) &&
                !CheckCollisionRecs(nextPlayerPos, lado12) &&
                !CheckCollisionRecs(nextPlayerPos, lado17) &&
                !CheckCollisionRecs(nextPlayerPos, lado18) &&
                !CheckCollisionRecs(nextPlayerPos, lado19) &&
                !CheckCollisionRecs(nextPlayerPos, lado20)) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }
        }



        ColisionPlayer(playerPos);
    }



    //declara el movimiento del enemigo y la direccion en la que se mueve dependiendo de la posicion del jugador
    //declara las posiciones donde el enemigo no puede acceder, colisiones


    bool CheckColisions(Player& p) { //mira si ha coli

        bool check = CheckCollisionRecs(this->Square, p.Square);
        if (check == true) {

            p.status = false;
        }

        return p.status;

    }
    //chequea las colisiones 
};
class Orc : public Enemy {

private:
    int dire = 0;
    bool status = true;
    Texture Mon1 = LoadTexture("64x64/128x128_vaca.png");
    Texture Mon2 = LoadTexture("64x64/128x128_vaca2.png");

    float deathStartTime = 0;

public:
    friend class PowerUpLive;
    friend class Game;
    Orc() : Enemy(3, 1) {}
    //declara al enemigo
    void Death() {

        if (!IsSoundPlaying(Die)) {
            PlaySound(Die); // Play the sound only if it�s not already playing
        }
        deathStartTime = GetTime();

    }
    //declara la muerte y el sonido de muerte del enemigo


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
    //actualiza la posicion y direcion del enemigo dependiendo de la posicion del jugador
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
    }
    //dibuja el sprite y animacion del enemigo


    friend class Colision;
};

class Ogre : public Enemy {
private:
    int dire = 0;
    bool status = true;
    Texture Mon1 = LoadTexture("64x64/128x128_zombie7.png");
    Texture Mon2 = LoadTexture("64x64/128x128_zombie6.png");

    float deathStartTime = 0;

public:
    friend class PowerUpLive;
    friend class Game;
    Ogre() : Enemy(3, 1) {





    }
    //declara al enemigo
    void Death() {

        if (!IsSoundPlaying(Die)) {
            PlaySound(Die); // Play the sound only if it�s not already playing
        }
        deathStartTime = GetTime();

    }
    //declara la muerte y el sonido de muerte del enemigo


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
    //actualiza la posicion y direcion del enemigo dependiendo de la posicion del jugador
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



    }
    //dibuja el sprite y animacion del enemigo


    friend class Colision;

};
class Mariposa : public Enemy {
private:
    int dire = 0;
    bool status = true;
    Texture Mon1 = LoadTexture("64x64/128x128_mariposa1.png");
    Texture Mon2 = LoadTexture("64x64/128x128_mariposa2.png");

    float deathStartTime = 0;

public:
    friend class PowerUpLive;
    friend class Game;
    Mariposa() : Enemy(1, 1) {





    }
    //declara al enemigo
    void SetPosition(Vector2 pos) {
        playerPos = pos;
        Square = { playerPos.x, playerPos.y, 32, 32 };
    }


    void MovementMariposa(Player p) {


        Vector2 player = p.GetPosition();
        float nextY = playerPos.y;
        float nextX = playerPos.x;
        if (playerPos.x < player.x) {
            nextX += vel;  // Changed from -= to +=
        }
        else {
            nextX -= vel;  // Changed from += to -=
        }

        if (playerPos.y < player.y) {
            nextY += vel;  // Changed from -= to +=
        }
        else {
            nextY -= vel;  // Changed from += to -=
        }


        playerPos.x = nextX;
        playerPos.y = nextY;

        ColisionPlayer(playerPos);
        Square = { playerPos.x, playerPos.y, 32, 32 };
    }
    void Death() {

        if (!IsSoundPlaying(Die)) {
            PlaySound(Die); // Play the sound only if it�s not already playing
        }
        deathStartTime = GetTime();
        status = false;
    }
    //declara la muerte y el sonido de muerte del enemigo


    void Update(Player p) {
        if (!status) return;
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
    //actualiza la posicion y direcion del enemigo dependiendo de la posicion del jugador
    void Draw() {
        if (!status) return;
        /*BeginDrawing();*/
        if (dire <= 50) {

            DrawTexture(Mon2, GetPosition().x, GetPosition().y, WHITE);


        }
        else {

            DrawTexture(Mon1, GetPosition().x, GetPosition().y, WHITE);

        }

        if (dire == 100) { dire = 0; }
        dire++;



    }
    //dibuja el sprite y animacion del enemigo


    friend class Colision;

};

class ScreenNuke : public Colision {

private:

    Texture vida = LoadTexture("items/128x128_tumbacraneo.png");
    Vector2 pos;
    float appearTime;
public:
    friend class Game;
    friend class Player;
    friend class Colision;
    bool inInventry = false;
    bool started = false;
    bool firstTryenemy = true;
    bool firstTryorcs = true;
    bool firsttrymarip = true;
    bool finished = false;
    friend  bool PlayerPowerUpScreenNuke(Player& p, ScreenNuke& pp);
    ScreenNuke(Vector2 position) : Colision(pos) {
        this->pos = position;

        DrawTexture(vida, pos.x, pos.y, WHITE);
        appearTime = GetTime();

    }
    //dibuja el item de vida +
    ScreenNuke(Player p) : Colision(pos) {



    }
    //suma la vida al jugador despues de recoger el item
    ScreenNuke() : Colision(pos) {



    }


    void UsePowerUp(std::vector<Ogre>& enemigo, std::vector <Orc>& orcs, std::vector <Mariposa>& marip) {

        int i = 0;

        while (enemigo.size() > i) {
            int h = i;
            if (firstTryenemy) { //hace un timer para ver cuando ha empezado a eliminarse en cada personaje individualmente

                while (i < enemigo.size()) {
                    enemigo[i].SNstart_time = GetTime();
                    i++;
                }
                i = h;
                firstTryenemy = false;
            }
            enemigo[i].SNAnim(); //animacion del humo de cuando se eliminan
            if (enemigo[i].isSNfinished) { //si se ha acabado se elimina el personaje de la misma manera que vista anteriormente
                int j = i;
                if (enemigo.size() == 1) {

                    enemigo.pop_back();

                }
                else if (enemigo.size() > 1) {
                    while (j < enemigo.size() - 1) {
                        enemigo[j] = enemigo[j + 1];
                        j++;
                    }

                    enemigo.pop_back();

                }

            }

            i++;
        }
        i = 0;
        while (orcs.size() > i) {
            if (firstTryorcs) {

                while (i < orcs.size()) {
                    orcs[i].SNstart_time = GetTime();
                    i++;
                }
                i = 0;
                firstTryorcs = false;
            }
            orcs[i].SNAnim();
            if (orcs[i].isSNfinished) {

                int j = i;
                if (orcs.size() == 1) {

                    orcs.pop_back();

                }
                else if (orcs.size() > 1) {
                    while (j < orcs.size() - 1) {
                        orcs[j] = orcs[j + 1];
                        j++;
                    }

                    enemigo.pop_back();

                }

            }

            i++;
        }
        while (marip.size() > i) {
            if (firsttrymarip) {

                while (i < marip.size()) {
                    marip[i].SNstart_time = GetTime();
                    i++;
                }
                firsttrymarip = false;
                i = 0;
            }
            marip[i].SNAnim();
            if (marip[i].isSNfinished) {

                int j = i;
                if (marip.size() == 1) {

                    marip.pop_back();

                }
                else if (marip.size() > 1) {
                    while (j < marip.size() - 1) {
                        marip[j] = marip[j + 1];
                        j++;
                    }

                    marip.pop_back();

                }

            }

            i++;
        }
        if (marip.size() == 0 && enemigo.size() == 0 && orcs.size() == 0) {
            finished = true;
            started = false;
            firstTryenemy = true;
            firstTryorcs = true;
            firsttrymarip = true;
        }
    }

    //suma la vida
    void Draw() {


        DrawTexture(vida, pos.x, pos.y, WHITE);
        ColisionPlayer(pos);
    }
    //dibuja la textura y una colision alrededor para saber cuando el jugador la recoge






};
class DeadOgre {
private:
    Texture Mon1 = LoadTexture("effects/128x128_hierba6.png");
    Vector2 playerPos;
    Texture Death1 = LoadTexture("effects/128x128_hierba1.png");
    Texture Death2 = LoadTexture("effects/128x128_hierba2.png");
    Texture Death3 = LoadTexture("effects/128x128_hierba3.png");
    Texture Death4 = LoadTexture("effects/128x128_hierba4.png");
    Texture Death5 = LoadTexture("effects/128x128_hierba5.png");
    Texture Death6 = LoadTexture("effects/128x128_hierba6.png");
    float deathStartTime = 0;
    float kDeadLifetime = 3.0f;
    bool isFinished = false;
public:

    DeadOgre(Vector2 playerPos) {
        this->playerPos = playerPos;
        deathStartTime = GetTime();

    }
    //declara la posicion del ogro muerto
    void Draw() {
        if (isFinished == false) {

            DeathAnim();

        }
        else {
            DrawTexture(Mon1, playerPos.x, playerPos.y, WHITE);


        }

    }
    //dibuja la animacion del ogro muerto si muere
    bool Delete() {
        float currentTime = GetTime();
        float elapsed = currentTime - deathStartTime;
        //si el tiempo que ha pasado es este, pues se limpia para que no haya siempre monstruo
        if (elapsed > 10.0f) {
            return true;
        }
        return false;
    }


    void DeathAnim() {


        float currentTime = GetTime();
        float elapsed = currentTime - deathStartTime;

        if (elapsed < 0.1) {
            DrawTexture(Death1, playerPos.x, playerPos.y, WHITE);

        }
        else if (elapsed < 0.2) {
            DrawTexture(Death2, playerPos.x, playerPos.y, WHITE);
        }
        else if (elapsed < 0.3) {
            DrawTexture(Death3, playerPos.x, playerPos.y, WHITE);
        }
        else if (elapsed < 0.4) {
            DrawTexture(Death4, playerPos.x, playerPos.y, WHITE);
        }
        else if (elapsed < 0.5) {
            DrawTexture(Death5, playerPos.x, playerPos.y, WHITE);
        }
        else if (elapsed < 0.6) {
            DrawTexture(Death6, playerPos.x, playerPos.y, WHITE);
        }
        else {
            // Animation finished
            isFinished = true;
            // Optionally trigger a respawn or game over screen here
        }
    }
    //animacion de muerte del ogro

    friend class Game;
};
class Boss : public Enemy {
private:
    Texture Boss1 = LoadTexture("64x64/boss1.png");
    Texture Boss2 = LoadTexture("64x64/boss2.png");
    Texture Boss3 = LoadTexture("64x64/boss3.png");
    Texture Boss4 = LoadTexture("64x64/boss4.png");
    Texture bulletTex = LoadTexture("Bullet_1.png");
    Texture Dialogo = LoadTexture("ui/dialogo.png");
    Texture Death1 = LoadTexture("effects/128x128_piedra1.png");
    Texture Death2 = LoadTexture("effects/128x128_piedra2.png");
    Texture Death3 = LoadTexture("effects/128x128_piedra3.png");
    Texture Death4 = LoadTexture("effects/128x128_piedra4.png");
    Texture Death5 = LoadTexture("effects/128x128_piedra5.png");
    Texture Contento = LoadTexture("64x64/personaje.contento.png");
    bool isAlive;
    int frameCounter;
    bool moving;
    int direction = 1;
    float introStartTime = 0;
    bool Intro = true;
    float deathStartTime;
    bool status;
    bool deathAnimationFinished = false;
    float lastMoveTime = 0.0f;
    float pauseStartTime = 0.0f;
    bool isPaused = false;
    bool deathHandled = false;
    float deathTime = 0.0f;
    Texture Goofer1 = LoadTexture("64x64/p3_11.png");
    Texture Goofer2 = LoadTexture("64x64/p3_10.png");
    Texture Goofer3 = LoadTexture("64x64/p3_9.png");
    Texture Goofer4 = LoadTexture("64x64/p3_5.png");
    Texture Goofer5 = LoadTexture("64x64/p3_6.png");
    Texture Goofer6 = LoadTexture("64x64/p3_7.png");
    Texture cosa = LoadTexture("128x128_112.png");
    bool showGoofer = false;
    int gooferFrame = 0;
    float gooferStartTime = 0.0f;
    Vector2 gooferPos = { 320, 0 };
    float lastGooferUpdateTime = 0;
public:
    friend Game;
    Boss() : Enemy(50, 2), isAlive(true), frameCounter(0), moving(false) {
        playerPos = { (float)(320), 448 };
        introStartTime = GetTime();
        Intro = true;
        status = true;

    }//constructor del boss
    void DrawGoofer(Player& player, int& level, int& currentLevel) {
        float currentTime = GetTime();

        if (currentTime - lastGooferUpdateTime > 0.2f) {
            gooferFrame++;
            lastGooferUpdateTime = currentTime;
            gooferPos.y += 15;
        }//hacer que los goofers vallan hacia abajo
        if (gooferPos.y + 32 >= screenHeight) {
            player.ResetPlayer(6);
            level = 6;
            currentLevel = 6;
            showGoofer = false;
            gooferPos.y = 0;
            return;
        }
        Texture current;
        Texture current2;
        int frame = ((int)(GetTime() * 5)) % 4;

        if (frame == 0) {
            current = Goofer1;
        }
        else if (frame == 1) {
            current = Goofer2;
        }
        else if (frame == 2) {
            current = Goofer3;
        }
        else {
            current = Goofer2;
        }//animacion goofers
        DrawTexture(current, gooferPos.x, gooferPos.y, WHITE);

        int frame2 = ((int)(GetTime() * 5)) % 4;
        if (frame == 0) {
            current2 = Goofer4;
        }
        else if (frame == 1) {
            current2 = Goofer5;
        }
        else if (frame == 2) {
            current2 = Goofer6;
        }
        else {
            current2 = Goofer5;
        }//animacion goofers

        DrawTexture(current2, gooferPos.x + 16, gooferPos.y + 64, WHITE);
        DrawTexture(current2, gooferPos.x - 16, gooferPos.y + 64, WHITE);
        DrawTexture(current, gooferPos.x, gooferPos.y, WHITE);
        DrawTexture(cosa, gooferPos.x - 16, gooferPos.y + 32, WHITE);
        DrawTexture(Contento, gooferPos.x - 16, gooferPos.y + 32, WHITE);
    }


    void Death() {
        if (!IsSoundPlaying(Die)) {
            PlaySound(Die);
        }
        this->playerPos = playerPos;
        deathStartTime = GetTime();
        DrawDeathAnim();
        status = false;
        //funcion para la muerte del bos


    }
    void DrawHealthBar() {
        const int barWidth = 510;
        const int barHeight = 20;
        const int barX = 64;
        const int barY = 550;

        float healthRatio = (float)hp / 50.0f;
        int currentBarWidth = (int)(barWidth * healthRatio);


        DrawRectangle(barX, barY, barWidth, barHeight, BLACK);
        DrawRectangle(barX, barY, currentBarWidth, barHeight, RED);
        //dibuja y reduce la barra de vida del boss
    }

    void DrawDeathAnim() {
        float currentTime = GetTime();
        float elapsed = currentTime - deathStartTime;

        if (elapsed < 0.1f) {
            DrawTexture(Death1, playerPos.x, playerPos.y, WHITE);
        }
        else if (elapsed < 0.2f) {
            DrawTexture(Death2, playerPos.x, playerPos.y, WHITE);
            DrawTexture(Death1, playerPos.x + 32, playerPos.y, WHITE);
            DrawTexture(Death1, playerPos.x, playerPos.y + 32, WHITE);
        }
        else if (elapsed < 0.3f) {
            DrawTexture(Death3, playerPos.x, playerPos.y, WHITE);
            DrawTexture(Death2, playerPos.x + 32, playerPos.y, WHITE);
            DrawTexture(Death2, playerPos.x, playerPos.y + 32, WHITE);
            DrawTexture(Death1, playerPos.x - 32, playerPos.y, WHITE);
            DrawTexture(Death1, playerPos.x, playerPos.y - 32, WHITE);
        }
        else if (elapsed < 0.4f) {
            DrawTexture(Death4, playerPos.x, playerPos.y, WHITE);
            DrawTexture(Death3, playerPos.x + 32, playerPos.y, WHITE);
            DrawTexture(Death3, playerPos.x, playerPos.y + 32, WHITE);
            DrawTexture(Death2, playerPos.x - 32, playerPos.y, WHITE);
            DrawTexture(Death2, playerPos.x, playerPos.y - 32, WHITE);
            DrawTexture(Death1, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death1, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death1, playerPos.x + 16, playerPos.y + 16, WHITE);
            DrawTexture(Death1, playerPos.x + 16, playerPos.y + 16, WHITE);
        }
        else if (elapsed < 0.5f) {
            DrawTexture(Death5, playerPos.x, playerPos.y, WHITE);
            DrawTexture(Death4, playerPos.x + 32, playerPos.y, WHITE);
            DrawTexture(Death4, playerPos.x, playerPos.y + 32, WHITE);
            DrawTexture(Death3, playerPos.x - 32, playerPos.y, WHITE);
            DrawTexture(Death3, playerPos.x, playerPos.y - 32, WHITE);
            DrawTexture(Death2, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death2, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death1, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death1, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death1, playerPos.x - 16, playerPos.y - 16, WHITE);
            DrawTexture(Death1, playerPos.x - 16, playerPos.y - 16, WHITE);
            DrawTexture(Death2, playerPos.x + 16, playerPos.y + 16, WHITE);
            DrawTexture(Death2, playerPos.x + 16, playerPos.y + 16, WHITE);
        }
        else if (elapsed < 0.6f) {
            DrawTexture(Death5, playerPos.x + 32, playerPos.y, WHITE);
            DrawTexture(Death5, playerPos.x, playerPos.y + 32, WHITE);
            DrawTexture(Death4, playerPos.x - 32, playerPos.y, WHITE);
            DrawTexture(Death4, playerPos.x, playerPos.y - 32, WHITE);
            DrawTexture(Death3, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death3, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death2, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death2, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death1, playerPos.x, playerPos.y, WHITE);
            DrawTexture(Death2, playerPos.x - 16, playerPos.y - 16, WHITE);
            DrawTexture(Death2, playerPos.x - 16, playerPos.y - 16, WHITE);
            DrawTexture(Death3, playerPos.x + 16, playerPos.y + 16, WHITE);
            DrawTexture(Death3, playerPos.x + 16, playerPos.y + 16, WHITE);
        }
        else if (elapsed < 0.7f) {
            DrawTexture(Death5, playerPos.x - 32, playerPos.y, WHITE);
            DrawTexture(Death5, playerPos.x, playerPos.y - 32, WHITE);
            DrawTexture(Death4, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death4, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death3, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death3, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death2, playerPos.x, playerPos.y, WHITE);
            DrawTexture(Death3, playerPos.x - 16, playerPos.y - 16, WHITE);
            DrawTexture(Death3, playerPos.x - 16, playerPos.y - 16, WHITE);
            DrawTexture(Death4, playerPos.x + 16, playerPos.y + 16, WHITE);
            DrawTexture(Death4, playerPos.x + 16, playerPos.y + 16, WHITE);
        }
        else if (elapsed < 0.8f) {
            DrawTexture(Death5, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death5, playerPos.x + 32, playerPos.y + 32, WHITE);
            DrawTexture(Death4, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death4, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death3, playerPos.x, playerPos.y, WHITE);
            DrawTexture(Death4, playerPos.x - 16, playerPos.y - 16, WHITE);
            DrawTexture(Death4, playerPos.x - 16, playerPos.y - 16, WHITE);
            DrawTexture(Death5, playerPos.x + 16, playerPos.y + 16, WHITE);
            DrawTexture(Death5, playerPos.x + 16, playerPos.y + 16, WHITE);
        }
        else if (elapsed < 0.9f) {
            DrawTexture(Death5, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death5, playerPos.x - 32, playerPos.y - 32, WHITE);
            DrawTexture(Death4, playerPos.x, playerPos.y, WHITE);
            DrawTexture(Death5, playerPos.x - 16, playerPos.y - 16, WHITE);
            DrawTexture(Death5, playerPos.x - 16, playerPos.y - 16, WHITE);
        }
        else if (elapsed < 1.0f) {
            DrawTexture(Death5, playerPos.x, playerPos.y, WHITE);
        }
        else {

            deathAnimationFinished = true;

        }

    }//animacion de muerte del boss


    void Update(Player& p) {
        if (!status) return;

        float now = GetTime();

        if (Intro) {
            if (now - introStartTime < 340.0f) {
                moving = false;
                DrawTexture(Dialogo, 310, 360, WHITE);
                return;
            }
            else {
                Intro = false;
                moving = true;
                lastMoveTime = now;
            }
        }//la intro donde habla y esta quieto

        if (!isPaused && now - lastMoveTime >= 6.0f) {
            isPaused = true;
            pauseStartTime = now;
            moving = false;
        }
        else if (isPaused && now - pauseStartTime >= 4.0f) {
            isPaused = false;
            lastMoveTime = now;
            moving = true;

        }//hace que cada 6 segundos pare durante 4 segundes y se quede en su idle sin disparar

        if (moving) {
            playerPos.x += direction * vel;
            if (playerPos.x < 96 || playerPos.x > screenWidth - 64) direction *= -1;
            return;
        }//movimiento del boss hacia los lados





    }

    void Draw() {
        if (!status && deathAnimationFinished) {
            return;
        }

        if (!status && !deathAnimationFinished) {
            DrawDeathAnim();
            return;
        }//dibuja la animacion de muerte si el boss muere i la animacion no se ha ejecutado

        frameCounter++;
        Texture current;

        if (moving) {
            current = (frameCounter / 30 % 2 == 0) ? Boss3 : Boss4;
        }
        else {
            current = (frameCounter / 30 % 2 == 0) ? Boss1 : Boss2;
        }//animacion del movimiento de los lados del boss

        DrawTexture(current, playerPos.x, playerPos.y, WHITE);



    }




    bool IsAlive() const { return isAlive; }




};

class Shoot : public Colision {

private:
    Vector2 playerPos;
    Sound shooter = LoadSound("sound effects/prairie king bullet.ogg");
    bool eliminate = false;
    Texture bulletTex = LoadTexture("Bullet_1.png");
    bool isEnemyBullet;

public:
    friend class Enemy;
    Direccion dir;
    Vector2 GetPosition() const { return this->playerPos; }

    bool ColisionBullet(const Enemy& s) {

        return CheckCollisionRecs(this->Square, s.Square);

    }
    //chequea si la bala colisiona con el enemigo

    Shoot(Boss b) : Colision(b.GetPosition()) {
        if (!IsSoundPlaying(shooter)) {
            PlaySound(shooter); // Play the sound only if it�s not already playing
        }
        playerPos = { b.GetPosition().x + 32 / 2, b.GetPosition().y + (16) };

        // Set direction based on arrow keys instead of player direction
        dir = ARRIBA;
        isEnemyBullet = true;

    }

    //declara las direcciones y teclas asignadas a disparar
    friend class Game;
    // Add method to update bullet position




    Shoot(Player p) : Colision(p.GetPosition()) {
        if (!IsSoundPlaying(shooter)) {
            PlaySound(shooter); // Play the sound only if it�s not already playing
        }
        playerPos = { p.GetPosition().x + 32 / 2, p.GetPosition().y + (16) };

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
        isEnemyBullet = false;
    }
    //declara las direcciones y teclas asignadas a disparar
    friend class Game;
    // Add method to update bullet position
    void UpdatePosition(int level) {

        float nextX = playerPos.x;
        float nextY = playerPos.y;


        switch (dir) {
        case ARRIBA:
            nextY -= 5.0f;
            break;
        case ABAJO:
            nextY += 5.0f;
            break;
        case DERECHA:
            nextX += 5.0f;
            break;
        case IZQUIERDA:
            nextX -= 5.0f;
            break;
        case DIAGONAL1:
            nextX += 5.0f;
            nextY -= 5.0f;
            break;
        case DIAGONAL2:
            nextX -= 5.0f;
            nextY -= 5.0f;
            break;
        case DIAGONAL3:
            nextX += 5.0f;
            nextY += 5.0f;
            break;
        case DIAGONAL4:
            nextX -= 5.0f;
            nextY += 5.0f;
            break;
        default:
            break;



        }
        Rectangle nextBulletPos = { nextX, nextY, 3, 3 };

        std::vector<Rectangle> walls;

        if (level == 1) {
            walls = {
                 { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                 { 544, 32, 32, 512 }, { 64, 512, 512, 32 }
            };
        }
        else if (level == 2) {
            walls = {
                { 192, 160, 64, 32 }, { 192, 160, 32, 64 },
                { 192, 416, 64, 32 }, { 192, 384, 32, 64 },
                { 384, 160, 64, 32 }, { 416, 160, 32, 64 },
                { 384, 416, 64, 32 }, { 416, 384, 32, 64 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 },
                { 384, 160, 64, 32 }, { 416, 160, 32, 64 },
                { 384, 416, 64, 32 }, { 416, 384, 32, 64 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 }
            };
        }
        else if (level == 3) {
            walls = {
                { 320, 160, 32, 32 }, { 320, 416, 32, 32 },
                { 192, 288, 32, 32 }, { 448, 288, 32, 32 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 },
                { 96, 64, 64, 32 }, { 96, 64, 32, 64 },
                { 512, 64, 32, 64 }, { 480, 64, 64, 32 },
                { 64, 32, 32, 224 }, { 64, 32, 224, 32 },
                { 544, 32, 32, 224 }, { 64, 512, 224, 32 },
                { 96, 448, 32, 64 }, { 96, 480, 64, 32 },
                { 512, 448, 32, 64 }, { 480, 480, 64, 32 }
            };
        }
        else if (level == 4) {
            walls = {
                { 224, 192, 96, 32 }, { 352, 192, 96, 32 },
                { 224, 192, 32, 96 }, { 416, 192, 32, 96 },
                { 224, 320, 32, 96 }, { 224, 384, 96, 32 },
                { 352, 384, 96, 32 }, { 416, 320, 32, 96 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 }


            };

        }
        else if (level == 5) {
            walls = {
            { 320, 160, 32, 32 }, { 224, 224, 32, 32 },
            { 384, 224, 32, 32 }, { 288, 416, 96, 32 }, { 64, 32, 32, 512 },
            { 64, 32, 512, 32 }, { 544, 32, 32, 512 },
            { 64, 512, 512, 32 }

            };


        }
        else if (level == 6) {
            walls = {
                { 96, 64, 96, 32 }, { 96, 64, 32, 96 },
                { 160, 128, 32, 32 }, { 480, 64, 32, 32 },
                { 512, 64, 32, 64 }, { 480, 128, 32, 32 },
                { 96, 448, 32, 96 }, { 96, 480, 96, 32 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 },
                { 160, 416, 32, 32 }, { 480, 416, 32, 96 },
                { 448, 448, 32, 32 }, { 512, 448, 32, 64 }


            };



        }
        else if (level == 7) {
            walls = {
                { 128, 128, 32, 32 }, { 160, 160, 32, 32 },
                { 416, 128, 32, 32 }, { 384, 224, 32, 32 },
                { 384, 288, 32, 64 }, { 224, 320, 32, 32 },
                { 448, 352, 32, 32 }, { 160, 416, 32, 32 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 },
                { 384, 416, 32, 32 }, { 448, 416, 32, 32 }
            };


        }
        else if (level == 8) {
            walls = {
                { 64, 192, 120, 32 }, { 224, 192, 88, 32 },
                { 352, 192, 88, 32 }, { 480, 192, 88, 32 },
                { 64, 352, 120, 32 }, { 224, 352, 88, 32 },
                { 352, 352, 88, 32 }, { 480, 352, 88, 32 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 },


            };


        }

        else if (level == 9) {
            walls = {
                { 192, 160, 64, 64 }, { 192, 352, 64, 32 },
                { 192, 416, 64, 32 }, { 384, 160, 32, 64 },
                { 448, 160, 32, 64 }, { 384, 352, 32, 32 },
                { 448, 352, 32, 32 }, { 384, 416, 32, 32 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 },
                { 448, 416, 32, 32 },

            };

        }

        else if (level == 10) {
            walls = {
                { 64, 64, 224, 32 }, { 384, 64, 192, 32 },
                { 64, 480, 224, 32 }, { 384, 480, 192, 64 },
                { 320, 224, 32, 12 }, { 256, 288, 32, 32 },
                { 384, 288, 32, 32 }, { 320, 320, 32, 32 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 },


            };
        }
        else if (level == 11) {
            walls = {
                { 64, 64, 512, 32 }, { 64, 480, 512, 32 },
                { 64, 32, 32, 512 }, { 64, 32, 512, 32 },
                { 544, 32, 32, 512 }, { 64, 512, 512, 32 },


            };


        }



        for (const auto& wall : walls) {
            if (CheckCollisionRecs(nextBulletPos, wall)) {
                eliminate = true;
                return;
            }
        }


        playerPos.x = nextX;
        playerPos.y = nextY;
        this->Square = { playerPos.x, playerPos.y, 3, 3 };
        ColisionBullet(playerPos);
    }


    void ColisionBullet(Vector2 posicion) {

        DrawRectangle(posicion.x, posicion.y, 3, 3, BLANK);
        Square.x = posicion.x;
        Square.y = posicion.y;


    }
    void Draw() {

        DrawTexture(bulletTex, playerPos.x, playerPos.y, WHITE);



    }



};





class level {
protected:
    int levels;


public:

    level() {

        levels = 11;

    }

    void LevelUp() {

        levels++;

    }

};
//classe para indicar el sistema de niveles
class Stage : public level {

protected:
    int stage;
public:



    Stage() : level() {

        stage = 11;

    }
    void StageUp() {

        stage++;

    }

    int CheckStage() {

        return stage;

    }



};
//dibuja la stage correpondiente al nivel
class time {
private:


    double tiempoInicial;
    double tiempoFinal;
    double tiempoTranscurrido;
    int barraAncho;

    float tiempoFake;
    float aux = 0;
public:


    time() {

        tiempoFinal = 80.0f;
        tiempoTranscurrido = 0;
        barraAncho = 512;

        tiempoInicial = 0;
    }
    void NewTime() {



        float help = GetTime();

        aux = aux + help - tiempoFake; //auxiliar es el auxiliar anterior mas el tiempo que ha pasado desde la pausa, que es el tiempofake restado al tiempoo actual

        tiempoFinal = tiempoInicial + 80 + aux;
    } //sumamos eso al tiempofinal, ya que es el tiempo que ha estado en pausa
    void pause() {

        tiempoFake = GetTime(); //miramos en que mmento a parado

    }
    void DrawInicial() {

        //DrawRectangle(0, 1024 / 2, playerScreenX / 2, 32, GREEN);

    }
    void Draw() {

        DrawRectangle(96, 8, barraAncho, 16, GREEN); //la barra del tiempo es así de ancha, y dependiendo del tiempo que ha pasado se irá reduciendo

        double porcentaje = tiempoTranscurrido / tiempoFinal;

        barraAncho = (int)((playerScreenX - 32) * (1 - porcentaje));






    }
    void IniciarTiempo() {

        tiempoInicial = GetTime(); //el tiempo inicial es el que hay cuando empieza el nivel, y cada nivel son 1.20 min aprox
        tiempoFinal = tiempoInicial + 80.0f;
        aux = 0;

    }
    void TiempoQueHaPasado() {
        float tiempoAhora = GetTime();
        tiempoTranscurrido = tiempoAhora - tiempoInicial - aux; //mira en que momento concreto nos encontramos


    }
    bool tiempo() {
        if (tiempoTranscurrido > tiempoFinal) {
            return true;
        }
        else { return false; }

    }

    float TiempoActual() {

        TiempoQueHaPasado();
        return tiempoTranscurrido;

    }





};
//dibuja una barra de tiempo que conforme passa el tiempo se va reduciendo
class coins : public Colision {
private:
    Texture moneda1 = LoadTexture("items/128x128_moneda1.png");
    Texture moneda5 = LoadTexture("items/128x128_moneda_s.png");
    Vector2 pos;
    int moneda = 0;
    float appearTime;



public:
    friend class Game;
    friend class Player;
    friend class Colision;
    friend bool PlayerPowerUpScreenMoney(Player& p, coins& pp);
    coins(Vector2 position) : Colision(pos) {
        this->pos = position;
        int aux = GetRandomValue(1, 5);
        if (aux == 1) {

            DrawTexture(moneda5, pos.x, pos.y, WHITE);
            moneda = 5;

        }
        else {


            DrawTexture(moneda1, pos.x, pos.y, WHITE);
            moneda = 1;

        }

        appearTime = GetTime();

    }
    //dibuja el item de monedas
    bool ColisionMoney(Player& p) {

        bool check = CheckCollisionRecs(this->Square, p.Square);
        return check;



    }
    //suma la moneda al jugador



    void UsePowerUp(Player& p) {
        if (moneda == 1) {

            p.money++;

        }
        else {

            p.money += 5;

        }


    }
    //suma la moneda al jugador
    void Draw() {
        if (moneda == 1) {

            DrawTexture(moneda1, pos.x, pos.y, WHITE);


        }
        else {


            DrawTexture(moneda5, pos.x, pos.y, WHITE);


        }
        ColisionPlayer(pos);
    }
    //dibuja la textura y una colision alrededor para saber cuando el jugador recoge la moneda






};

class HeavyMachineGun : public Colision {

private:

    Vector2 pos;
    Texture wow = LoadTexture("items/128x128_mun.png");
    float appearTime;
public:
    friend class Game;
    HeavyMachineGun(Vector2 vector) : Colision(pos) {

        appearTime = GetTime();
        this->pos = vector;
    }

    HeavyMachineGun(Player p) : Colision(pos) {

    }
    void UsePowerUp(float& powerRate) {

        powerRate -= 0.05;

    }

    void StopUsing(float& powerRate) {

        powerRate += 0.05;


    }


    void Draw() {



        DrawTexture(wow, pos.x, pos.y, WHITE);
        ColisionPlayer(pos);

    }
    friend bool PlayerPowerUpHMG(Player& p, HeavyMachineGun& pp);

};

class Game {
private:
    Texture2D tronco = LoadTexture("items/128x128_e.png");
    Vector2 logPos = { 0, 0 };
    bool showLog = false;
    bool logOnPlayer = false;
    int punteroDraw;

    int level;
    bool wonGame = false;
    bool SNInUse = false;
    int stage;
    bool tiempoFake = false;
    Texture puntero = LoadTexture("64x64/128x128_puntero.png");
    Texture vida = LoadTexture("items/128x128_cabeza.png");
    Texture cafee = LoadTexture("items/128x128_taza.png");
    Texture pistola = LoadTexture("items/128x128_mun.png");
    Texture destructor = LoadTexture("items/128x128_tumbacraneo.png");
    std::vector<DeadOgre>dead;
    int deadogres;
    bool tiempoiniciado;
    Sound power = LoadSound("song/cowboy_powerup.wav");
    Sound explosion = LoadSound("cowboy_explosion.wav");
    Sound Die = LoadSound("song/cowboy_dead.wav");
    Sound Hit = LoadSound("song/cowboy_monsterhit.wav");/*cowboy_monsterhit.wa*/
    bool gameover = false;
    float timesincedeletion = 0;
    float timeoflastdelete = 0;
    float timeOfLive = 0;
    int bagItem = 0;
    int bagItemAux = 0;
    float powerRate = 0.4;
    int timeCafeInicial;
    int timeCafeFinal;
    int HMGTimeInicial;
    int HMGTimeFinal;
    int cafeEnUso = 0;
    int HMGEnUso = 0;
    Boss boss;
    bool bossFight = false;
    bool tiendaActiva = false;
    bool ChangingLevel = false;
    Vector2 He;
    ScreenNuke gameNuke;
    bool firstRound = true;
    int bulletDamage = 1;



public:
    friend Boss;
    friend int main();
    Game() {
        deadogres = 0;

        level = 1;
        stage = 1;        /*  BeginDrawing();*/
        std::vector<DeadOgre>dead;
        tiempoiniciado = false;


        ScreenNuke gameNuke();
    }
    //declara el nivel y stage inicial
    void GameStart(Player& p, Boss& b, std::vector<Ogre>& enemigo, std::vector<Shoot>& bullets, int& og, int& ayxi, int& dire, int& ogreaux, int& bulletaux, time& Tiempo, std::vector<float>& auxTime, float& HelpMeTime, std::vector <PowerUpLive>& Lives, std::vector<coins>& money, std::vector <Orc>& orcs, std::vector <Mariposa>& marip, std::vector<Coffee>& cafe, std::vector <ScreenNuke>& SN, std::vector <HeavyMachineGun>& gun, Store& tienda)
    {
        int monstersize = enemigo.size() + marip.size() + orcs.size();
        if (p.status && (!ChangingLevel || monstersize != 0) && !tiendaActiva) {
            ClearBackground(BLACK);
            /*BeginDrawing();*/
            BeginDrawing();
            if (tiempoiniciado == false) { // si el tiempo no ha iniciado
                if (firstRound) { //y es la primera ronda, hace que la bolsa sea 0 y que ya no sea la primera ronda
                    p.bag = 0;
                    firstRound = false;
                }
                Tiempo.IniciarTiempo(); //inicia el tiempo (entrar en función para explicación, esto irá pasando por todo el código)
                tiempoiniciado = true; //para que no vuelva a iniciar el tiempo en un futuro

            }
            else { //si el tiempo ya ha sido iniciado

                Tiempo.TiempoQueHaPasado();
                Tiempo.Draw();



            }

            //empieza el tiempo, lo dibuja y lo va actualizando
            if (boss.showGoofer) {
                DrawRectangle(64, 32, GetScreenWidth(), GetScreenHeight(), BLACK);
                boss.DrawGoofer(p, level, currentLevel);
                showLog = false;
                EndDrawing();
                return;
            }

            if (level == 11) {
                currentLevel = 11;//para las colisiones del nivel 11

            }
            if (showLog) {
                if (logOnPlayer) {
                    Vector2 playerPos = p.GetPosition();
                    DrawTexture(tronco, playerPos.x, playerPos.y - 32, WHITE); // 40 pixels above
                }
                else {
                    DrawTexture(tronco, 320, 352, WHITE);
                }
            }//muestra el tronco de la victoria
            if (showLog && !p.logEffectActive) {
                Rectangle playerRect = { p.GetPosition().x, p.GetPosition().y, 32, 32 };
                Rectangle logRect = { 320, 352, 32, 32 };

                if (CheckCollisionRecs(playerRect, logRect)) {
                    p.logEffectActive = true;

                    p.logEffectStartTime = GetTime();
                    logOnPlayer = true;
                }
            }//cuando el player colisiona con el tronco, el tronco se pone en su cabeza y el player cambia de sprite
            if (p.logEffectActive && (GetTime() - p.logEffectStartTime >= 2.0f)) {
                p.logEffectActive = false;

                boss.showGoofer = true;
                boss.gooferStartTime = GetTime();
                boss.gooferPos = { p.GetPosition().x, 0 };
            }//para mostrar el goofer

            // Handle bullet creation with arrow keys

            //para las bullets

            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) ||
                IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)) {
                //el timer de cuando ha de esperar una bullet para volver a ser lanzada es el power rate, por eso hay upgrades para disminuirlo
                static float shootTimer = powerRate;
                if (shootTimer <= 0) {
                    bullets.push_back(Shoot(p));
                    shootTimer = powerRate; // Shoot every 0.2 seconds while holding key

                }
                shootTimer -= GetFrameTime();


            }

            //lo mismo que el anterior pero es para el boss
            int a = GetTime();
            if ((level == 5) && a > 17.0f && boss.status && boss.IsAlive() && !boss.isPaused) {
                static float shootTimer = powerRate;

                if (shootTimer <= 0) {
                    bullets.push_back(Shoot(boss));
                    shootTimer = powerRate;
                }

                shootTimer -= GetFrameTime();
            }


            int i = 0;

            while (i < bullets.size()) {

                bullets[i].UpdatePosition(level);
                bullets[i].Draw();
                Rectangle bulletRect = { bullets[i].GetPosition().x, bullets[i].GetPosition().y, 3, 3 };
                Rectangle playerHitbox = { p.GetPosition().x, p.GetPosition().y, 32, 32 };
                Rectangle BossHitbox = { p.GetPosition().x, p.GetPosition().y, 32, 32 };

                if (bullets[i].isEnemyBullet && CheckCollisionRecs(bulletRect, playerHitbox) && p.status) {
                    p.status = false;
                    bullets[i].eliminate = true;
                }//detecta que la bala es del enemigo i mata al player cuando le da
                if (!bullets[i].isEnemyBullet &&

                    CheckCollisionRecs(bulletRect, { boss.GetPosition().x, boss.GetPosition().y, 32, 32 })) {
                    if (bulletDamage = 1) {
                        boss.hp--;
                        bullets[i].eliminate = true;

                    }
                    else if (bulletDamage = 2) {
                        boss.hp--;
                        boss.hp--;
                        bullets[i].eliminate = true;
                    }
                    else {
                        boss.hp--;
                        boss.hp--;
                        boss.hp--;
                        bullets[i].eliminate = true;

                    }





                }//detecta que la bala es del player i le resta vida al boss dependiendo de la pistola que tenga el player
                if (boss.hp <= 0 && boss.status == true) {

                    boss.Death();


                }//cuando el boss llega a 0 de vida activa la funcion de muerte
                if ((level == 5 || level == 51) && !boss.status && !boss.deathHandled) {

                    float elapsed = GetTime() - boss.deathTime;

                    if (elapsed > 2.0f) {
                        level = 51;
                        Lives.push_back(PowerUpLive(boss.GetPosition()));
                        showLog = true;

                        boss.deathHandled = true;
                    }//hace que salga el tronco de la victoria y que el boss dropee una vida
                }




                if (bullets[i].eliminate) {
                    bullets.erase(bullets.begin() + i);
                }
                else {
                    i++;
                }



            }

            tienda.DrawInventario(); //dibuja lo que tiene el jugador en el inventario
            i = 0;
            while (i < dead.size()) { //los cosas que sueltan los monstruos al morir

                if (dead[i].Delete()) {

                    if (dead.size() == 1) {

                        dead.pop_back();
                        //si solo hay uno hay poop back pero si hay más de uno, lo que hacemos es que el que se ha de eliminar es suplantado por el siguiente, y al último le hacemos pop_back
                    }
                    else {
                        int j = i;
                        while (j < dead.size() - 1) {

                            dead[j] = dead[j + 1];
                            j++;
                        }

                    }


                }
                i++;
            }



            int bulletSize = bullets.size();




            if (level > 3 && level != 5 && level != 51 && !SNInUse) { //este aparece en todos los niveles a partir del 3, menos en el del boss, y cuando esta en uso el screen nuke no pueden hacer nada
                int i = 0;
                if (GetRandomValue(1, 40) == 1 && enemigo.size() + orcs.size() + marip.size() < 6 + level && !ChangingLevel) { //hacemos que el máximo de enemigos son 8 mas el nivel en el que se encuentran para que haya mas dificultad

                    Orc auxiliar;
                    orcs.push_back(auxiliar);


                }
                if (orcs.size() > 0) { //aqui lo que hacemos es mirar bullet a bullet si ha chocado con un orco


                    int j = 0;
                    int aux = 0;
                    while (i < orcs.size()) {

                        while (j < bullets.size()) {
                            if (i >= orcs.size()) {


                            }
                            else {

                                if (bullets[j].ColisionBullet(orcs[i]) == true) { //si choca creamos un goop verde, el DeadOgre, y 
                                    orcs[i].hp -= bulletDamage;
                                    if (orcs[i].hp < 0) {

                                        DeadOgre auxiliari(orcs[i].GetPosition());
                                        dead.push_back(auxiliari);
                                        float timehelp = GetTime();
                                        auxTime.push_back(timehelp);
                                        deadogres++;
                                        //de manera random puede aparecer un power up

                                        int a = GetRandomValue(1, 10);
                                        if (a == 1 && Lives.size() == 0) {
                                            Vector2 ee = orcs[i].GetPosition();
                                            PowerUpLive live(ee);
                                            Lives.push_back(live);

                                        }
                                        else if (a == 2 && cafe.size() == 0) {
                                            Vector2 ee = orcs[i].GetPosition();
                                            Coffee live(ee);
                                            cafe.push_back(live);


                                        }
                                        else if (a == 3 && money.size() == 0) {
                                            Vector2 ee = orcs[i].GetPosition();
                                            coins live(ee);
                                            money.push_back(live);



                                        }
                                        else if (a == 4 && cafe.size() == 0) {
                                            Vector2 ee = orcs[i].GetPosition();
                                            Coffee live(ee);
                                            cafe.push_back(live);



                                        }
                                        else if (a == 5 && SN.size() == 0) {
                                            Vector2 ee = orcs[i].GetPosition();
                                            ScreenNuke live(ee);
                                            SN.push_back(live);


                                        }
                                        else if (a == 6 && gun.size() == 0) {
                                            Vector2 ee = orcs[i].GetPosition();
                                            HeavyMachineGun live(ee);
                                            gun.push_back(live);


                                        }


                                        if (orcs.size() == 1) {
                                            orcs[i].Death();
                                            orcs.pop_back();

                                        }

                                        else if (orcs.size() > 1) {

                                            aux = i;
                                            orcs[i].Death();
                                            while (aux < orcs.size() - 1) {

                                                orcs[aux] = orcs[aux + 1]; //eliminamos de la misma manera que anteriormente
                                                aux++;

                                            }
                                            orcs.pop_back();


                                        }

                                    }
                                    else {
                                        if (!IsSoundPlaying(Hit)) { //hace un sonido diferente si no ha muerto pero le han golpeado
                                            PlaySound(Hit);
                                        }

                                    }


                                    bulletSize = bullets.size();
                                    aux = j;
                                    if (bullets.size() == 1) {

                                        bullets.pop_back();
                                        bulletSize--;
                                    }
                                    else if (bullets.size() > 1) {
                                        while (aux < bullets.size() - 1) { //eliminamos de la misma manera
                                            bullets[aux] = bullets[aux + 1];
                                            aux++;
                                        }

                                        bullets.pop_back();

                                    }
                                    bulletSize = bullets.size();

                                }


                            }
                            // chequea si la bala colisiona con el ogro
                            if (orcs.size() == 0) { j = bulletSize; }

                            j++;
                        }

                        j = 0;
                        i++;


                    }


                }







            }



            if (level == 5 && !bossFight) {
                bossFight = true;
            }
            else if (level > 5 && !bossFight || level < 5 && !bossFight) {
                bossFight = false;
            }//activa/descativa la boss fight dependiendo del nivel
            //es el mismo código que el orco

            if (level > 5 && level != 5 && level != 51 && !SNInUse) {
                if (GetRandomValue(1, 40) == 1 && enemigo.size() + orcs.size() + marip.size() < 15 && !ChangingLevel) {
                    Mariposa auxiliar;

                    // Random border spawn position
                    int border = GetRandomValue(1, 4);  // 1=Top, 2=Bottom, 3=Left, 4=Right
                    Vector2 spawnPos;

                    switch (border) {
                    case 1: spawnPos = { (float)GetRandomValue(64, 544), 32 }; break;
                    case 2: spawnPos = { (float)GetRandomValue(64, 544), 544 }; break;
                    case 3: spawnPos = { 64, (float)GetRandomValue(32, 544) }; break;
                    case 4: spawnPos = { 544, (float)GetRandomValue(32, 544) }; break;
                    }

                    auxiliar.SetPosition(spawnPos);  // Set manually after creation
                    marip.push_back(auxiliar);
                }


                if (marip.size() > 0) {


                    int j = 0;
                    int aux = 0;
                    while (i < marip.size()) {

                        while (j < bullets.size()) {

                            if (i >= marip.size()) {


                            }
                            else {

                                if (bullets[j].ColisionBullet(marip[i]) == true) {

                                    DeadOgre auxiliari(marip[i].GetPosition());
                                    dead.push_back(auxiliari);
                                    float timehelp = GetTime();
                                    auxTime.push_back(timehelp);
                                    deadogres++;


                                    int a = GetRandomValue(1, 10);
                                    if (a == 1 && Lives.size() == 0) {
                                        Vector2 ee = marip[i].GetPosition();
                                        PowerUpLive live(ee);
                                        Lives.push_back(live);





                                    }
                                    else if (a == 2 && cafe.size() == 0) {
                                        Vector2 ee = marip[i].GetPosition();
                                        Coffee live(ee);
                                        cafe.push_back(live);






                                    }
                                    else if (a == 3 && money.size() == 0) {
                                        Vector2 ee = marip[i].GetPosition();
                                        coins live(ee);
                                        money.push_back(live);




                                    }
                                    else if (a == 4 && cafe.size() == 0) {
                                        Vector2 ee = marip[i].GetPosition();
                                        Coffee live(ee);
                                        cafe.push_back(live);







                                    }
                                    else if (a == 5 && SN.size() == 0) {
                                        Vector2 ee = marip[i].GetPosition();
                                        ScreenNuke live(ee);
                                        SN.push_back(live);







                                    }
                                    else if (a == 6 && gun.size() == 0) {
                                        Vector2 ee = marip[i].GetPosition();
                                        HeavyMachineGun live(ee);
                                        gun.push_back(live);







                                    }




                                    if (marip.size() == 1) {
                                        marip[i].Death();
                                        marip.pop_back();

                                    }

                                    else if (marip.size() > 1) {

                                        aux = i;
                                        marip[i].Death();;
                                        while (aux < marip.size() - 1) {

                                            marip[aux] = marip[aux + 1];
                                            aux++;

                                        }
                                        marip.pop_back();


                                    }

                                    bulletSize = bullets.size();
                                    aux = j;
                                    if (bullets.size() == 1) {

                                        bullets.pop_back();
                                        bulletSize--;
                                    }
                                    else if (bullets.size() > 1) {
                                        while (aux < bullets.size() - 1) {
                                            bullets[aux] = bullets[aux + 1];
                                            aux++;
                                        }

                                        bullets.pop_back();

                                    }
                                    bulletSize = bullets.size();

                                }


                            }
                            // chequea si la bala colisiona con el ogro
                            if (marip.size() == 0) { j = bulletSize; }

                            j++;
                        }

                        j = 0;
                        i++;


                    }


                }







            }//este también hace lo mismo
            if (level != 5 && level != 51 && !SNInUse) { //ogre
                int i = 0;
                if (GetRandomValue(1, 40) == 1 && enemigo.size() + orcs.size() + marip.size() < 15 && !ChangingLevel) {

                    Ogre auxiliar;
                    enemigo.push_back(auxiliar);


                }
                if (enemigo.size() > 0) {


                    int j = 0;
                    int aux = 0;
                    while (i < enemigo.size()) {

                        while (j < bullets.size()) {
                            if (i >= enemigo.size()) {


                            }
                            else {

                                if (bullets[j].ColisionBullet(enemigo[i]) == true) {

                                    DeadOgre auxiliari(enemigo[i].GetPosition());
                                    dead.push_back(auxiliari);
                                    float timehelp = GetTime();
                                    auxTime.push_back(timehelp);
                                    deadogres++;



                                    int Random = GetRandomValue(1, 10);
                                    if (Random == 1 && Lives.size() == 0) {
                                        Vector2 ee = enemigo[i].GetPosition();
                                        PowerUpLive live(ee);
                                        Lives.push_back(live);





                                    }
                                    else if (Random == 2 && cafe.size() == 0) {
                                        Vector2 ee = enemigo[i].GetPosition();
                                        Coffee live(ee);
                                        cafe.push_back(live);






                                    }
                                    else if (Random == 3) {
                                        Vector2 ee = enemigo[i].GetPosition();
                                        coins live(ee);
                                        money.push_back(live);




                                    }
                                    else if (Random == 4 && cafe.size() == 0) {
                                        Vector2 ee = enemigo[i].GetPosition();
                                        Coffee live(ee);
                                        cafe.push_back(live);







                                    }
                                    else if (Random == 5 && SN.size() == 0) {
                                        Vector2 ee = enemigo[i].GetPosition();
                                        ScreenNuke live(ee);
                                        SN.push_back(live);







                                    }
                                    else if (Random == 6 && gun.size() == 0) {
                                        Vector2 ee = enemigo[i].GetPosition();
                                        HeavyMachineGun live(ee);
                                        gun.push_back(live);







                                    }




                                    if (enemigo.size() == 1) {
                                        enemigo[i].Death();
                                        enemigo.pop_back();

                                    }

                                    else if (enemigo.size() > 1) {

                                        aux = i;
                                        enemigo[i].Death();;
                                        while (aux < enemigo.size() - 1) {

                                            enemigo[aux] = enemigo[aux + 1];
                                            aux++;

                                        }
                                        enemigo.pop_back();


                                    }

                                    bulletSize = bullets.size();
                                    aux = j;
                                    if (bullets.size() == 1) {

                                        bullets.pop_back();
                                        bulletSize--;
                                    }
                                    else if (bullets.size() > 1) {
                                        while (aux < bullets.size() - 1) {
                                            bullets[aux] = bullets[aux + 1];
                                            aux++;
                                        }

                                        bullets.pop_back();

                                    }
                                    bulletSize = bullets.size();

                                }


                            }
                            // chequea si la bala colisiona con el ogro
                            if (enemigo.size() == 0) { j = bulletSize; }

                            j++;
                        }

                        j = 0;
                        i++;


                    }


                }







            }

            i = 0;
            deadogres = dead.size();
            while (i < dead.size()) {

                dead[i].Draw();
                i++;

            }
            //dibujar los power ups y olos elimina si han pasado más de 10 segundos (es lo mismo en todos pero solo explico el de Lives)

            int auxiliarPowerUps = 0;
            while (auxiliarPowerUps < Lives.size()) {
                Lives[auxiliarPowerUps].Draw();
                float helperDrawer = GetTime();
                if (helperDrawer - Lives[auxiliarPowerUps].appearTime > 10) {
                    Lives.pop_back();
                }
                auxiliarPowerUps++;

            }
            auxiliarPowerUps = 0;
            while (auxiliarPowerUps < gun.size()) {
                gun[auxiliarPowerUps].Draw();
                float helperDrawer = GetTime();
                if (helperDrawer - gun[auxiliarPowerUps].appearTime > 10) {
                    gun.pop_back();
                }

                auxiliarPowerUps++;
            }
            auxiliarPowerUps = 0;
            while (auxiliarPowerUps < SN.size()) {
                if (!SN[auxiliarPowerUps].inInventry) {



                    SN[auxiliarPowerUps].Draw();
                    float helperDrawer = GetTime();
                    if (helperDrawer - SN[auxiliarPowerUps].appearTime > 10) {

                        SN.pop_back();
                    }
                    auxiliarPowerUps++;
                }
            }
            auxiliarPowerUps = 0;
            while (auxiliarPowerUps < money.size()) {

                money[auxiliarPowerUps].Draw();
                float helperDrawer = GetTime();
                if (helperDrawer - money[auxiliarPowerUps].appearTime > 10) {
                    int zz = auxiliarPowerUps;
                    while (zz < money.size() - 1) {
                        money[zz] = money[zz + 1];
                        zz++;
                    }
                    money.pop_back();
                }
                auxiliarPowerUps++;
            }
            auxiliarPowerUps = 0;
            while (auxiliarPowerUps < cafe.size()) {

                cafe[auxiliarPowerUps].Draw();
                float helperDrawer = GetTime();
                if (helperDrawer - cafe[auxiliarPowerUps].appearTime > 10) {
                    cafe.pop_back();
                }
                auxiliarPowerUps++;
            }
            auxiliarPowerUps = 0;

            //mirar si ha colisionado contra un power up

            while (auxiliarPowerUps < Lives.size()) {

                if (PlayerPowerUp(p, Lives[auxiliarPowerUps])) { //mira si se han chocado, y si lo han hecho gana una vida

                    Lives[0].UsePowerUp(p);
                    Lives.pop_back();



                }
                auxiliarPowerUps++;
                if (!IsSoundPlaying(power)) {
                    PlaySound(power);
                }
            }
            auxiliarPowerUps = 0;
            while (auxiliarPowerUps < gun.size()) {

                if (PlayerPowerUpHMG(p, gun[auxiliarPowerUps])) {
                    if (p.bag == 1) {
                        gun[0].UsePowerUp(powerRate);
                        gun.pop_back(); //aqui lo que hace es que se elimina despues de usar el power up, ya que si hay un elemento en la bolsa usa al chocarse
                        HMGEnUso = 1;
                        HMGTimeInicial = GetTime(); //esto es porque dura unos 12 segundos
                    }
                    else {

                        p.bag++;
                        bagItem = 2;
                        gun.pop_back();


                    }
                    if (!IsSoundPlaying(power)) {
                        PlaySound(power);
                    }
                }
                auxiliarPowerUps++;

            }
            if (HMGEnUso == 1) {
                HMGTimeFinal = GetTime(); //si esta en uso mira todo el rato si han pasado los 12 segundos, si han pasado crea un auxiliar para que el power rate vuelva a ser normal
                if (HMGTimeFinal - HMGTimeInicial > 12) {
                    HeavyMachineGun Aux(p.playerPos);
                    Aux.StopUsing(powerRate);
                    HMGEnUso = 0;
                    HMGTimeInicial = 0;


                }

            }
            auxiliarPowerUps = 0;
            while (auxiliarPowerUps < SN.size()) {

                if (PlayerPowerUpScreenNuke(p, SN[auxiliarPowerUps])) {
                    int a = 0;
                    if (p.bag == 1) {
                        SN.pop_back();
                        gameNuke.started = true;
                        gameNuke.finished = false; //el game nuke es una animacion, cuando empieza a estaren uso le damos a started, ya que va a ser un buvle
                        SNInUse = true;

                    }
                    else {

                        p.bag++;
                        bagItem = 3;
                        SN.pop_back();


                    }
                    if (!IsSoundPlaying(power)) {
                        PlaySound(power);
                    }
                }



                auxiliarPowerUps++;

            }

            auxiliarPowerUps = 0;
            while (auxiliarPowerUps < money.size()) {

                if (PlayerPowerUpScreenMoney(p, money[auxiliarPowerUps])) {
                    money[auxiliarPowerUps].UsePowerUp(p);
                    int lala = auxiliarPowerUps;
                    if (money.size() == 1) {



                    }
                    else {

                        while (lala < money.size() - 1) {
                            money[lala] = money[lala + 1];
                            lala++;

                        }

                    }
                    money.pop_back();
                }
                auxiliarPowerUps++;
                if (!IsSoundPlaying(power)) {
                    PlaySound(power);
                }
            }
            auxiliarPowerUps = 0;
            while (auxiliarPowerUps < cafe.size()) {

                if (PlayerPowerUpCoffee(p, cafe[auxiliarPowerUps])) {
                    if (p.bag == 1) {
                        if (cafeEnUso == 1) { //mismo que con la pistola
                            timeCafeFinal = GetTime();
                            cafe.pop_back();

                        }
                        else {


                            cafe[0].UsePowerUp(p);
                            cafe.pop_back();
                            cafeEnUso = 1;
                            timeCafeInicial = GetTime();
                        }
                    }
                    else {

                        p.bag++;
                        bagItem = 4;
                        cafe.pop_back();

                    }
                    if (!IsSoundPlaying(power)) {
                        PlaySound(power);
                    }
                }
                auxiliarPowerUps++;

            }

            auxiliarPowerUps = 0;
            if (timeCafeFinal - timeCafeInicial > 16) {
                Coffee Aux(p.playerPos);
                Aux.StopUsing(p);



            }

            if (IsKeyDown(KEY_SPACE) && p.bag == 1) {
                if (bagItem == 2) { //mira si hay algo en la bolsa y el personaje quiere usarlo

                    if (HMGEnUso == 1) {
                        HMGTimeInicial = GetTime();

                    }
                    else {
                        HeavyMachineGun Aux(p.playerPos);
                        Aux.UsePowerUp(this->powerRate);
                        HMGEnUso = 1;


                    }



                }
                else if (bagItem == 3) {

                    gameNuke.started = true;
                    gameNuke.finished = false;

                    SNInUse = true;
                }
                else if (bagItem == 4) {

                    if (cafeEnUso == 1) {
                        timeCafeInicial = GetTime();

                    }
                    else {
                        Coffee Aux(p.playerPos);
                        Aux.UsePowerUp(p);
                        cafeEnUso = 1;

                    }

                }
                p.bag = 0;
                bagItem = 0;
            }



            //aqui hace que los enemigos se muevan y se pinten, si esta en uso el Screen Nuke no se pintan
            i = 0;
            ogreaux = enemigo.size();
            while (i < enemigo.size()) {

                enemigo[i].CheckColisions(p);

                if (p.status == true && !SNInUse) {

                    enemigo[i].MovementEnemy(p, this->level);


                }
                if (!SNInUse) {



                    enemigo[i].Draw();
                }



                i++;

            }
            i = 0;
            while (i < orcs.size()) {

                orcs[i].CheckColisions(p);

                if (p.status == true && !SNInUse) {

                    orcs[i].MovementEnemy(p, this->level);


                }
                if (!SNInUse) {

                    orcs[i].Draw();

                }

                i++;

            }
            i = 0;
            while (i < marip.size()) {

                marip[i].CheckColisions(p);

                if (p.status == true && !SNInUse) {

                    marip[i].MovementMariposa(p);


                }

                if (!SNInUse) {

                    marip[i].Draw();

                }


                i++;

            }
            i = 0;
            bulletSize = bullets.size();


            if (gameNuke.started && !gameNuke.finished && SNInUse) {
                gameNuke.UsePowerUp(enemigo, orcs, marip);
                if (!IsSoundPlaying(explosion)) {
                    PlaySound(explosion);
                }
                bagItem = 0;

            }
            if (gameNuke.finished) {

                SNInUse = false; //si ha acabado de eliminar a todos deja de estar en uso
            }
            i = 0;

            while (i < bulletSize) { //mira si las bullets se han ido

                if (0 > bullets[i].GetPosition().x || GetScreenWidth() < bullets[i].GetPosition().x || GetScreenHeight() < bullets[i].GetPosition().y || 0 > bullets[i].GetPosition().y) {
                    bulletSize = bullets.size();
                    int p = i;
                    if (bulletSize == 1) {

                        bullets.pop_back();
                        bulletSize = 0;

                    }
                    else {

                        while (p < bulletSize - 1) {

                            bullets[p] = bullets[p + 1];
                            p++;
                        }

                        bullets.pop_back();


                    }
                    bulletSize = bullets.size();
                }
                i++;
            }


            p.Movement(this->level);
            p.Draw();

            if (p.status == false) {
                p.bag = 0; //si ha muerto el personaje deja de usar todos los power ups
                if (cafeEnUso == 1) {

                    Coffee aux(p);
                    aux.StopUsing(p);

                    cafeEnUso = 0;
                }
                if (HMGEnUso == 1) {
                    HeavyMachineGun Aux(p.playerPos);
                    Aux.StopUsing(this->powerRate);
                    HMGEnUso = 1;


                }
                p.Death();
                Tiempo.Draw();
                int x = 0;
                //elimina todos los power ups y enemigos
                while (0 < enemigo.size()) {

                    enemigo.pop_back();
                    x++;
                }
                x = 0;
                while (0 < marip.size()) {

                    marip.pop_back();
                    x++;
                }
                x = 0;
                while (0 < orcs.size()) {

                    orcs.pop_back();
                    x++;
                }
                ogreaux = 0;
                x = 0;
                while (0 < bullets.size()) {
                    bullets.pop_back();
                    x++;


                }
                while (0 < Lives.size()) {

                    Lives.pop_back();
                }
                while (0 < SN.size()) {

                    SN.pop_back();
                }
                while (0 < gun.size()) {

                    gun.pop_back();
                }while (0 < cafe.size()) {

                    cafe.pop_back();
                }
                while (0 < money.size()) {

                    money.pop_back();
                }
                bulletSize = 0;
                x = 0;
                if (Lives.size() > 0) {

                    Lives.pop_back();

                }

                deadogres = 0;

                if (p.lives < 0) { //si se ha acabado las vidas se limpia el suelo tmn si no, no

                    while (0 < dead.size()) {

                        dead.pop_back();


                    }

                }



            }
            if (bossFight && boss.IsAlive()) {
                boss.Update(p);
                boss.Draw();
                if (boss.IsAlive()) {
                    boss.DrawHealthBar();
                }


            }

            if (p.bag == 1) { //dibuja en el inventario
                if (bagItem == 1) {
                    DrawTexture(vida, 14, 12, WHITE);

                }
                else if (bagItem == 2) {

                    DrawTexture(pistola, 14, 12, WHITE);
                }
                else if (bagItem == 3) {
                    DrawTexture(destructor, 14, 12, WHITE);

                }
                else if (bagItem == 4) {
                    DrawTexture(cafee, 14, 12, WHITE);

                }

            }


            if (Tiempo.tiempo() == true && p.status == true) { //si ha acabado el
                ChangingLevel = true;

            }
            EndDrawing();
        }


        // si el jugador muere 
        else if (!p.status) {

            ClearBackground(BLACK);
            if (cafeEnUso == 1) {

                Coffee aux(p);
                aux.StopUsing(p);

                cafeEnUso = 0;
            }
            if (HMGEnUso == 1) {
                HeavyMachineGun Aux(p.playerPos);
                Aux.StopUsing(this->powerRate);
                HMGEnUso = 1;


            }
            /*BeginDrawing();*/
            BeginDrawing();
            int i = 0;
            Tiempo.Draw();
            if (tiempoFake == false) { //esto es porque mientras esta muerto el tiempo no avanza, así que hacemos un tiempo que se une

                Tiempo.pause();
                tiempoFake = true;

            }
            while (0 < Lives.size()) {

                Lives.pop_back();
            }
            while (0 < SN.size()) {

                SN.pop_back();
            }
            while (0 < gun.size()) {

                gun.pop_back();
            }while (0 < cafe.size()) {

                cafe.pop_back();
            }while (0 < money.size()) {
                money.pop_back();

            }

            while (i < dead.size()) {

                dead[i].DeathAnim();
                dead[i].Draw();
                if (dead[i].Delete() == true) {




                    dead.pop_back();


                }


                i++;



            }
            if (p.lives >= 0) { //s no es la muerte definitiva hacemos una animacion

                p.DeathAnim();

            }
            i = 0;
            if (ChangingLevel == true && tiendaActiva == true) { ChangingLevel == true; tiendaActiva == true; }
            if (p.lives < 0) { //si hay menos de 0 es game over
                GameOver(p);
            }
            if (p.status == true) {
                Tiempo.NewTime(); //hacemos el nuevo tiempo inicial
                p.ResetPlayer(level); //reset player a la posicion y tiempofake es falso por si vuelve a pasar
                tiempoFake = false;
            }


            EndDrawing();


        }

        if (ChangingLevel && !tiendaActiva && monstersize == 0) { //si el nivel se esta cambiando, el personaje tiene que ir hasta el final de la pantalla para ir al siguiente nivel
            ClearBackground(BLACK);
            BeginDrawing();
            p.Movement(level);
            p.Draw();
            punteroDraw++;
            if (cafeEnUso == 1) {

                Coffee aux(p);
                aux.StopUsing(p);

                cafeEnUso = 0;
            }
            if (HMGEnUso == 1) {
                HeavyMachineGun Aux(p.playerPos);
                Aux.StopUsing(this->powerRate);
                HMGEnUso = 1;


            }
            int i = 0;

            if (punteroDraw % 120 != 0) {

                DrawTexture(puntero, 350, 510, WHITE);


            }
            if (p.playerPos.y > 475) {

                if (p.playerPos.x > 288 && p.playerPos.x < 384) {


                    ChangeLevel(Tiempo, p, enemigo, bullets, Lives);
                    ChangingLevel = false;

                }

            }
            EndDrawing();
        }

        if ((level == 2 || level == 4 || level == 6 || level == 8 || level == 9 || level == 11) && monstersize == 0 && ChangingLevel && p.status) //mira si las conficiones se cumplen para la tienda
        {
            tiendaActiva = true;

        }
        else
        {
            tiendaActiva = false;
        }

        if (tiendaActiva && monstersize == 0 && p.status)
        {
            if (cafeEnUso == 1) {

                Coffee aux(p);
                aux.StopUsing(p);

                cafeEnUso = 0;
            }
            if (HMGEnUso == 1) {
                HeavyMachineGun Aux(p.playerPos);
                Aux.StopUsing(this->powerRate);
                HMGEnUso = 1;


            }
            ClearBackground(BLACK);

            BeginDrawing();
            p.Movement(this->level);
            float deltaTime = GetFrameTime();
            tienda.Update(deltaTime, this->tiendaActiva);
            tienda.Compra(p.GetPosition(), p.money, this->tiendaActiva, p.vel, this->powerRate, this->bulletDamage, level, p.lives); // Lógica de compra


            tienda.Draw();
            p.Draw();
            punteroDraw++;
            int i = 0;

            if (punteroDraw % 120 != 0) {

                DrawTexture(puntero, 350, 510, WHITE);


            }
            if (p.playerPos.y > 475) {

                if (p.playerPos.x > 288 && p.playerPos.x < 384) {


                    ChangeLevel(Tiempo, p, enemigo, bullets, Lives);
                    ChangingLevel = false;

                }

            }
            EndDrawing();
        }
        //reinicia los valores si el jugador pierde una vida

        // Set background color (framebuffer clear color)
/*  EndDrawing();*/
    }
    void ChangeLevel(time& Tiempo, Player& p, std::vector<Ogre>& enemigo, std::vector<Shoot>& bullets, std::vector <PowerUpLive>& Lives) {
        this->level++;
        //

        tiempoiniciado = false;
        int x = 0;

        //limpia cuando se cambia de nivel y suma al nivel para cambiarlo






        int clean = 0;
        while (clean < dead.size()) {

            dead.pop_back();
            clean++;

        }

        float esperar = GetTime();
        float auxiliar = 0;

        p.ResetPlayer(level);
        if (this->level == 12) {

            wonGame = true;

        }



    }
    //cambia de nivel y reinicia los valores
    void GameWon() { //si ha ganado dibuja que ha ganado
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText("You Won!", 40, screenHeight / 2, 40, WHITE);
        EndDrawing();

    }
    //pantalla de ganaste
    void GameOver(Player& p) {


        gameover = true; //todo lo del personaje vuelve a lo normal
        p.lives = 3;
        p.money = 0;
        p.vel = 2;
        powerRate = 0.4;

    }
    //pantalla de perdiste
    void GameOverScreen(Player& p) { //screen de gameover, reinicia al jugador (l reiniciamos varias veces por si acaso)
        ClearBackground(BLACK);
        /*BeginDrawing();*/
        BeginDrawing();

        DrawText("Game Over", 40, screenHeight / 2, 40, WHITE);

        EndDrawing();

        p.playerAgain();


    }
    int CheckLevel() {
        return level;


    }

    int CheckStage() {
        return stage;

    }
    //pantalla de cuando pierdes poder reiniciar el juego


};
//por alguna razón no me dejaba hacer lo del power up clision en la clase, así que aqui tienes tods
bool PlayerPowerUp(Player& p, PowerUpLive& pp) {

    bool check = CheckCollisionRecs(p.Square, pp.Square);
    if (check == true) {
        return true;
    }
    else {
        return false;
    }



}
bool PlayerPowerUpCoffee(Player& p, Coffee& pp) {

    bool check = CheckCollisionRecs(p.Square, pp.Square);
    if (check == true) {
        return true;
    }
    else {
        return false;
    }



}
bool PlayerPowerUpHMG(Player& p, HeavyMachineGun& pp) {

    bool check = CheckCollisionRecs(p.Square, pp.Square);
    if (check == true) {
        return true;
    }
    else {
        return false;
    }



}
bool PlayerPowerUpScreenNuke(Player& p, ScreenNuke& pp) {

    bool check = CheckCollisionRecs(p.Square, pp.Square);
    if (check == true) {
        return true;
    }
    else {
        return false;
    }



}
bool PlayerPowerUpScreenMoney(Player& p, coins& pp) {

    bool check = CheckCollisionRecs(p.Square, pp.Square);
    if (check == true) {
        return true;
    }
    else {
        return false;
    }



}

class Background : public Stage { //dibuja los backgrounds dependiendo del nivel
private:

    Texture suelo = LoadTexture("stage/64x64_fondo_desierto.png");
    Texture arbol1 = LoadTexture("stage/64x64_cesped_desierto.png");
    Texture arbol2 = LoadTexture("stage/64x64_cesped_desierto2.png");
    Texture desierto1 = LoadTexture("stage/desierto1.png");
    Texture desierto2 = LoadTexture("stage/desierto2.png");
    Texture desierto3 = LoadTexture("stage/desierto3.png");
    Texture desierto4 = LoadTexture("stage/desierto4.png");
    Texture fondo_desierto = LoadTexture("stage/fondo_desierto.png");
    Texture valla = LoadTexture("stage/madera.png");
    Texture lago1 = LoadTexture("stage/lago1.png");
    Texture lago2 = LoadTexture("stage/lago2.png");
    Texture flores = LoadTexture("stage/flores.png");
    Texture arbol3 = LoadTexture("stage/arbol.png");
    Texture arbol4 = LoadTexture("stage/arbol2.png");
    Texture cesped1 = LoadTexture("stage/cesped1.png");
    Texture cesped2 = LoadTexture("stage/cesped2.png");
    Texture cesped3 = LoadTexture("stage/cesped3.png");
    Texture cesped4 = LoadTexture("stage/cesped4.png");
    Texture tronco = LoadTexture("stage/tronco.png");
    Texture lago3 = LoadTexture("stage/lago11.png");
    Texture lago4 = LoadTexture("stage/lago22.png");
    Texture puente = LoadTexture("stage/barras.png");
    Texture balas = LoadTexture("stage/piedra4.png");
    Texture tumba1 = LoadTexture("stage/tumba1.png");
    Texture tumba2 = LoadTexture("stage/tumba2.png");
    Texture piedra1 = LoadTexture("stage/piedra1.png");
    Texture piedra2 = LoadTexture("stage/piedra2.png");
    Texture piedra3 = LoadTexture("stage/piedra3.png");
    Texture valla2 = LoadTexture("stage/valla2.png");
    Texture lago5 = LoadTexture("stage/camino1.png");
    Texture lago6 = LoadTexture("stage/camino2.png");
    Texture puente2 = LoadTexture("stage/puente2.png");
    Texture fondo_piedra = LoadTexture("stage/fondo_piedra.png");

public:
    int time = 0;
    friend int main();
    int currentTime = GetTime();


    void Drawlevel1() {
        int x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0 + 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480 + 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        y = 256;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 480 + 64, y, WHITE);
            y = y + 32;
        }
        y = 256 + 32;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, 64, y, WHITE);
            y = y + 32;
        }
        y = 256;
        DrawTexture(desierto2, 0 + 64, y, WHITE);
        x = 224 + 64;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, x, 512, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, x, 512, WHITE);
        x = 224 + 64;
        DrawTexture(desierto1, x, 32, WHITE);
        x = x + 32;
        DrawTexture(desierto2, x, 32, WHITE);
        x = x + 32;
        DrawTexture(desierto1, x, 32, WHITE);
        y = 64;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        y = 448 + 32;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 448 + 64;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        x = 64 + 64;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_desierto, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 96;
        DrawTexture(desierto4, 416 + 64, y, WHITE);
        y = 160;
        DrawTexture(desierto4, 416 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 416 - 96 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 192 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 416 - 64 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 192 - 32 + 64, y, WHITE);
        DrawTexture(desierto4, 416 + 64, y, WHITE);
        y = y + 64;
        DrawTexture(desierto4, 96 + 64, y, WHITE);
        DrawTexture(desierto4, 192 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 416 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 96 + 64, y, WHITE);

    }

    void Drawlevel2() {
        /* BeginDrawing();*/
        int x = 0 + 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0 + 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 0 + 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480 + 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        y = 224 + 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 480 + 64, y, WHITE);
            y = y + 32;
        }
        y = 224 + 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 0 + 64, y, WHITE);
            y = y + 32;
        }
        x = 224 + 64;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, x, 512, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, x, 512, WHITE);
        x = 224 + 64;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto2, x, 32, WHITE);
            x = x + 32;
        }
        y = 64;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        y = 448 + 32;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 448 + 64;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        x = 64 + 64;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_desierto, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        x = 128 + 64;
        y = 160;
        for (int i = 0; i < 2; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        y = y + 32;
        x = x - 64;
        DrawTexture(valla, x, y, WHITE);
        x = 352 + 64;
        y = 160;
        for (int i = 0; i < 2; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x - 32;
        }
        y = y + 32;
        x = x + 64;
        DrawTexture(valla, x, y, WHITE);
        x = 128 + 64;
        y = 352 + 64;
        for (int i = 0; i < 2; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        y = y - 32;
        x = x - 64;
        DrawTexture(valla, x, y, WHITE);
        x = 352 + 64;
        y = 352 + 64;
        for (int i = 0; i < 2; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x - 32;
        }
        y = y - 32;
        x = x + 64;
        DrawTexture(valla, x, y, WHITE);
        y = 96;
        DrawTexture(desierto4, 224 + 64, y, WHITE);
        DrawTexture(desierto4, 352 + 64, y, WHITE);
        y = 160;
        DrawTexture(desierto4, 96 + 64, y, WHITE);
        DrawTexture(desierto4, 224 + 64, y, WHITE);
        DrawTexture(desierto4, 416 + 64, y, WHITE);
        y = 192 + 32;
        DrawTexture(desierto4, 224 + 64, y, WHITE);
        y = 192 + 64;
        DrawTexture(desierto4, 224 + 128, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 64 + 64, y, WHITE);
        DrawTexture(desierto4, 96 + 128, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 480 - 96 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 96 + 64 + 64, y, WHITE);
        x = 96 + 96 + 64 + 64;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto4, x, y, WHITE);
            x = x + 32;
        }
        y = y + 32;
        DrawTexture(desierto4, 64 + 64, y, WHITE);
        DrawTexture(desierto4, x - 32 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 96 + 64, y, WHITE);
        DrawTexture(desierto4, 224 + 64, y, WHITE);
    }
    void Drawlevel3() {

        /* BeginDrawing();*/
        int x = 0 + 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 0 + 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 480 + 32;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0 + 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 0 + 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 0 + 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480 + 64, y, WHITE);
                }

            }
            y = y - 32;
        }
        y = 64;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        y = 448 + 32;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 448 + 64;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        x = 64 + 64;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_desierto, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 224 + 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 480 + 64, y, WHITE);
            y = y + 32;
        }
        y = 256;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 0 + 64, y, WHITE);
            y = y + 32;
        }
        x = 224 + 64;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, x, 512, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, x, 512, WHITE);
        x = 224 + 64;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, x, 32, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, x, 32, WHITE);
        x = 32 + 64;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 64, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 64, WHITE);
                }

            }
            x = x + 32;

        }
        x = 416 + 64;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 64, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 64, WHITE);
                }

            }
            x = x + 32;

        }
        x = 32 + 64;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 448 + 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 448 + 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 416 + 64;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 448 + 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 448 + 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 32 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 64 + 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 96, WHITE);
                }

            }
        }
        x = 448 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 96, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 96, WHITE);
                }

            }
        }
        x = 32 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 416 + 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 416 + 32, WHITE);
                }

            }
        }
        x = 448 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 416 + 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 416 + 32, WHITE);
                }

            }
        }
        DrawTexture(valla, 256 + 64, 128 + 32, WHITE);
        DrawTexture(valla, 256 + 64, 384 + 32, WHITE);
        DrawTexture(valla, 128 + 64, 256 + 32, WHITE);
        DrawTexture(valla, 384 + 64, 256 + 32, WHITE);
        DrawTexture(desierto4, 160 + 64, 96 + 32, WHITE);
        DrawTexture(desierto4, 320 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 64 + 64, 160 + 32, WHITE);
        DrawTexture(desierto4, 224 + 64, 160 + 32, WHITE);
        DrawTexture(desierto4, 160 + 64, 192 + 32, WHITE);
        DrawTexture(desierto4, 320 + 64, 192 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 256 + 32, WHITE);
        DrawTexture(desierto4, 96 + 64, 288 + 32, WHITE);
        DrawTexture(desierto4, 128 + 64, 352 + 32, WHITE);
        DrawTexture(desierto4, 256 + 64, 352 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 384 + 32, WHITE);
        DrawTexture(desierto4, 352 + 64, 416 + 32, WHITE);
    }
    void Drawlevel4() {

        /* BeginDrawing();*/
        int x = 0 + 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0 + 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 0 + 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 0 + 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 480 + 32;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480 + 64, y, WHITE);
                }

            }
            y = y - 32;
        }
        y = 32 + 32;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        y = 448 + 32;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 448 + 64;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        x = 64 + 64;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_desierto, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        x = 224 + 64;
        y = 32;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(desierto1, x, y, WHITE);
            x = x + 32;
        }
        y = 224 + 32;
        x = 480 + 64;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(desierto1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto1, 0 + 64, 256, WHITE);
        y = 256 + 32;
        x = 0 + 64;
        for (int i = 0; i < 2; i++)
        {
            DrawTexture(desierto2, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto1, 224 + 64, 512, WHITE);
        DrawTexture(desierto2, 256 + 64, 512, WHITE);
        DrawTexture(desierto1, 288 + 64, 512, WHITE);
        x = 160 + 64;
        y = 192;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        x = x + 32;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        x = 160 + 64;
        y = 352 + 32;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        x = x + 32;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        x = 160 + 64;
        y = 160 + 32;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(valla, x, y, WHITE);
            y = y + 32;
        }
        y = y + 32;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(valla, x, y, WHITE);
            y = y + 32;
        }
        y = 192;
        x = 352 + 64;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(valla, x, y, WHITE);
            y = y + 32;
        }
        y = y + 32;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(valla, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto4, 224 + 64, 64 + 32, WHITE);
        DrawTexture(desierto4, 288 + 64, 96 + 32, WHITE);
        DrawTexture(desierto4, 384 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 96 + 64, 192 + 32, WHITE);
        DrawTexture(desierto4, 128 + 64, 192 + 32, WHITE);
        DrawTexture(desierto4, 224 + 64, 192 + 32, WHITE);
        DrawTexture(desierto4, 288 + 64, 192 + 32, WHITE);
        DrawTexture(desierto4, 224 + 64, 256 + 32, WHITE);
        DrawTexture(desierto4, 288 + 64, 256 + 32, WHITE);
        DrawTexture(desierto4, 288 + 64, 288 + 32, WHITE);
        DrawTexture(desierto4, 128 + 64, 320 + 32, WHITE);
        DrawTexture(desierto4, 64 + 64, 384 + 32, WHITE);
        DrawTexture(desierto4, 160 + 64, 384 + 32, WHITE);
        DrawTexture(desierto4, 224 + 64, 384 + 32, WHITE);
    }

    void Drawlevel5() {
        int x = 0 + 64;
        int y = 32;
        for (int i = 0; i < 8; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto2, 64, 128, WHITE);
        y = y + 32;
        for (int i = 0; i < 6; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto2, x, y, WHITE);
        y = 32;
        for (int i = 0; i < 15; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, 32 + 64, y, WHITE);
        DrawTexture(desierto2, 160 + 64, y, WHITE);
        DrawTexture(desierto2, 352 + 64, y, WHITE);
        y = 512;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, 64 + 64, y, WHITE);
        DrawTexture(desierto2, 256 + 64, y, WHITE);
        x = 320 + 64;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto2, x, y, WHITE);
            x = x + 32;
        }
        x = 480 + 64;
        y = 32;
        for (int i = 0; i < 16; i++) {
            DrawTexture(desierto2, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto1, x, 96 + 32, WHITE);
        DrawTexture(desierto1, x, 160 + 32, WHITE);
        DrawTexture(desierto1, x, 192 + 32, WHITE);
        DrawTexture(desierto1, x, 288 + 32, WHITE);
        DrawTexture(desierto1, x, 352 + 32, WHITE);
        x = 64 + 64;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_desierto, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 64;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        y = 448 + 32;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 448 + 64;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        x = 0 + 64;
        y = 288;
        for (int i = 0; i < 2; i++) {
            DrawTexture(lago2, x, y, WHITE);
            x = x + 32;
        }
        for (int i = 0; i < 5; i++) {
            DrawTexture(lago1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago2, x, y, WHITE);
        x = x + 32;
        DrawTexture(lago1, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 4; i++) {
            DrawTexture(lago2, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago1, x, y, WHITE);
        x = x + 32;
        DrawTexture(lago2, x, y, WHITE);
        x = x + 32;
        DrawTexture(lago1, x, y, WHITE);
        x = 160 + 64;
        y = 192 + 32;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, y, WHITE);
                }

            }
        }
        x = 320 + 64;
        y = 192 + 32;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, y, WHITE);
                }

            }
        }
        DrawTexture(valla, 256 + 64, 160, WHITE);
        x = 224 + 64;
        y = 384 + 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto4, 416 + 64, 64 + 32, WHITE);
        DrawTexture(desierto4, 128 + 64, 96 + 32, WHITE);
        DrawTexture(desierto4, 160 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 320 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 352 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 416 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 288 + 32, WHITE);
        DrawTexture(desierto4, 352 + 64, 288 + 32, WHITE);
        DrawTexture(desierto4, 352 + 64, 320 + 32, WHITE);
        DrawTexture(desierto4, 96 + 64, 352 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 352 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 384 + 32, WHITE);
        DrawTexture(desierto4, 352 + 64, 416 + 32, WHITE);
        DrawTexture(desierto4, 384 + 64, 416 + 32, WHITE);
    }
    void Drawlevel51() {
        int x = 0 + 64;
        int y = 32;
        for (int i = 0; i < 8; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto2, 64, 128, WHITE);
        y = y + 32;
        for (int i = 0; i < 6; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto2, x, y, WHITE);
        y = 32;
        for (int i = 0; i < 15; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, 32 + 64, y, WHITE);
        DrawTexture(desierto2, 160 + 64, y, WHITE);
        DrawTexture(desierto2, 352 + 64, y, WHITE);
        y = 512;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, 64 + 64, y, WHITE);
        DrawTexture(desierto2, 256 + 64, y, WHITE);
        x = 320 + 64;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto2, x, y, WHITE);
            x = x + 32;
        }
        x = 480 + 64;
        y = 32;
        for (int i = 0; i < 16; i++) {
            DrawTexture(desierto2, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto1, x, 96 + 32, WHITE);
        DrawTexture(desierto1, x, 160 + 32, WHITE);
        DrawTexture(desierto1, x, 192 + 32, WHITE);
        DrawTexture(desierto1, x, 288 + 32, WHITE);
        DrawTexture(desierto1, x, 352 + 32, WHITE);
        x = 64 + 64;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_desierto, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 64;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        y = 448 + 32;
        x = 32 + 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 448 + 64;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        x = 0 + 64;
        y = 288;
        for (int i = 0; i < 2; i++) {
            DrawTexture(lago2, x, y, WHITE);
            x = x + 32;
        }
        for (int i = 0; i < 5; i++) {
            DrawTexture(lago1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago2, x, y, WHITE);
        x = x + 32;
        DrawTexture(lago1, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 4; i++) {
            DrawTexture(lago2, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago1, x, y, WHITE);
        x = x + 32;
        DrawTexture(lago2, x, y, WHITE);
        x = x + 32;
        DrawTexture(lago1, x, y, WHITE);
        x = 160 + 64;
        y = 192 + 32;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, y, WHITE);
                }

            }
        }
        x = 320 + 64;
        y = 192 + 32;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, y, WHITE);
                }

            }
        }
        DrawTexture(valla, 256 + 64, 160, WHITE);
        x = 224 + 64;
        y = 384 + 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto4, 416 + 64, 64 + 32, WHITE);
        DrawTexture(desierto4, 128 + 64, 96 + 32, WHITE);
        DrawTexture(desierto4, 160 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 320 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 352 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 416 + 64, 128 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 288 + 32, WHITE);
        DrawTexture(desierto4, 352 + 64, 288 + 32, WHITE);
        DrawTexture(desierto4, 352 + 64, 320 + 32, WHITE);
        DrawTexture(desierto4, 96 + 64, 352 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 352 + 32, WHITE);
        DrawTexture(desierto4, 192 + 64, 384 + 32, WHITE);
        DrawTexture(desierto4, 352 + 64, 416 + 32, WHITE);
        DrawTexture(desierto4, 384 + 64, 416 + 32, WHITE);
        DrawTexture(puente, 320, 288, WHITE);
    }

    void Drawlevel6() {
        int x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 544, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 544, y, WHITE);
                }

            }
            y = y - 32;
        }
        x = 128;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(cesped4, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 64;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        y = 480;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 512;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(cesped2, 64, 256, WHITE);
        x = 0 + 64;
        y = 288;
        for (int i = 0; i < 2; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        x = 224 + 64;
        y = 32;
        for (int i = 0; i < 2; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(cesped2, x, y, WHITE);
        x = 480 + 64;
        y = 256;
        for (int i = 0; i < 2; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(cesped2, x, y, WHITE);
        DrawTexture(cesped1, 224 + 64, 512, WHITE);
        DrawTexture(cesped2, 256 + 64, 512, WHITE);
        DrawTexture(cesped1, 288 + 64, 512, WHITE);
        x = 32 + 64;
        y = 64;
        for (int i = 0; i < 3; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 64;
        x = 64 + 64;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }
            x = x + 32;

        }
        y = 128;
        x = 96 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }
        }
        y = 64;
        x = 448 + 64;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }
            x = x - 32;

        }
        y = 96;
        x = 448 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 128;
        x = 416 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 448;
        x = 32 + 64;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 448 + 32;
        x = 64 + 64;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }
            x = x + 32;

        }
        y = 416;
        x = 96 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 416;
        x = 416 + 64;
        for (int i = 0; i < 3; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 448;
        x = 448 + 64;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 448;
        x = 384 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        DrawTexture(flores, 288 + 64, 64 + 32, WHITE);
        DrawTexture(flores, 256 + 64, 128 + 32, WHITE);
        DrawTexture(flores, 384 + 64, 128 + 32, WHITE);
        DrawTexture(flores, 352 + 64, 160 + 32, WHITE);
        DrawTexture(flores, 416 + 64, 160 + 32, WHITE);
        DrawTexture(flores, 192 + 64, 192 + 32, WHITE);
        DrawTexture(flores, 320 + 64, 192 + 32, WHITE);
        DrawTexture(flores, 192 + 64, 224 + 32, WHITE);
        DrawTexture(flores, 96 + 64, 256 + 32, WHITE);
        DrawTexture(flores, 96 + 64, 416 + 32, WHITE);
        DrawTexture(flores, 192 + 64, 416 + 32, WHITE);

    }

    void Drawlevel7() {
        int x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 0 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 0 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 0 + 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 0 + 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480 + 64;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 480 + 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 480 + 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 480 + 64, y, WHITE);
                }

            }
            y = y - 32;
        }
        x = 64 + 64;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(cesped4, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 64;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        y = 480;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 448 + 64;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        x = 224 + 64;
        y = 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            x = x + 32;
        }
        x = 480 + 64;
        y = 224 + 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        x = 224 + 64;
        y = 512;
        for (int i = 0; i < 3; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            x = x + 32;
        }
        x = 0 + 64;
        y = 256;
        for (int i = 0; i < 2; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(cesped2, x, y, WHITE);
        DrawTexture(cesped3, 160 + 64, 416, WHITE);
        DrawTexture(cesped3, 128 + 64, 192, WHITE);
        y = 128;
        x = 64 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 160;
        x = 96 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 128;
        x = 352 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 224;
        x = 320 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 320;
        x = 320 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 352;
        x = 384 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 384 + 32;
        x = 384 + 64;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        DrawTexture(tronco, 320 + 64, 256 + 32, WHITE);
        DrawTexture(tronco, 160 + 64, 288 + 32, WHITE);
        DrawTexture(tronco, 96 + 64, 384 + 32, WHITE);
        DrawTexture(tronco, 320 + 64, 384 + 32, WHITE);

        DrawTexture(flores, 160 + 64, 96 + 32, WHITE);
        DrawTexture(flores, 384 + 64, 96 + 32, WHITE);
        DrawTexture(flores, 256 + 64, 128 + 32, WHITE);
        DrawTexture(flores, 288 + 64, 128 + 32, WHITE);
        DrawTexture(flores, 384 + 64, 128 + 32, WHITE);
        DrawTexture(flores, 288 + 64, 160 + 32, WHITE);
        DrawTexture(flores, 320 + 64, 160 + 32, WHITE);
        DrawTexture(flores, 192 + 64, 192 + 32, WHITE);
        DrawTexture(flores, 192 + 64, 224 + 32, WHITE);
        DrawTexture(flores, 160 + 64, 320 + 32, WHITE);
        DrawTexture(flores, 256 + 64, 320 + 32, WHITE);
        DrawTexture(flores, 320 + 64, 320 + 32, WHITE);
        DrawTexture(flores, 416 + 64, 320 + 32, WHITE);
        DrawTexture(flores, 64 + 64, 352 + 32, WHITE);
        DrawTexture(flores, 160 + 64, 352 + 32, WHITE);
        DrawTexture(flores, 384 + 64, 416 + 32, WHITE);
    }
    void Drawlevel8() {
        int x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 5; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 544, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 5; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 544, y, WHITE);
                }

            }
            y = y - 32;
        }
        x = 128;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(cesped4, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 64;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        y = 480;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 512;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        x = 288;
        y = 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            x = x + 32;
        }
        x = 64;
        y = 256;
        for (int i = 0; i < 3; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        x = 288;
        y = 512;
        for (int i = 0; i < 3; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            x = x + 32;
        }
        x = 544;
        y = 256;
        DrawTexture(cesped2, x, y, WHITE);
        y = y + 32;
        for (int i = 0; i < 2; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        x = 64;
        y = 192;
        for (int i = 0; i < 2; i++) {
            DrawTexture(lago4, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago3, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(puente, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 1; i++) {
            DrawTexture(lago3, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago4, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago3, x, y, WHITE);
        x = x + 32;
        DrawTexture(puente, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 1; i++) {
            DrawTexture(lago3, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago4, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago3, x, y, WHITE);
        x = x + 32;
        DrawTexture(puente, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 1; i++) {
            DrawTexture(lago3, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago4, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago3, x, y, WHITE);
        x = 64;
        y = 352;
        for (int i = 0; i < 2; i++) {
            DrawTexture(lago4, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago3, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(puente, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 1; i++) {
            DrawTexture(lago3, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago4, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago3, x, y, WHITE);
        x = x + 32;
        DrawTexture(puente, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 1; i++) {
            DrawTexture(lago3, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago4, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago3, x, y, WHITE);
        x = x + 32;
        DrawTexture(puente, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 1; i++) {
            DrawTexture(lago3, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago4, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago3, x, y, WHITE);
        DrawTexture(flores, 160, 96, WHITE);
        DrawTexture(flores, 352, 128, WHITE);
        DrawTexture(flores, 320 + 64, 128, WHITE);
        DrawTexture(flores, 384 + 64, 128, WHITE);
        DrawTexture(flores, 416 + 64, 160, WHITE);
        DrawTexture(flores, 96 + 64, 224, WHITE);
        DrawTexture(flores, 352 + 64, 224, WHITE);
        DrawTexture(flores, 96 + 64, 256, WHITE);
        DrawTexture(flores, 288 + 64, 288, WHITE);
        DrawTexture(flores, 384 + 64, 288, WHITE);
        DrawTexture(flores, 288 + 64, 320, WHITE);
        DrawTexture(flores, 96 + 64, 416, WHITE);
        DrawTexture(flores, 224 + 64, 416, WHITE);
        DrawTexture(flores, 288 + 64, 416, WHITE);
    }
    void Drawlevel9() {
        int x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 544, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 544, y, WHITE);
                }

            }
            y = y - 32;
        }
        x = 128;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_piedra, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 64;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            x = x + 32;
        }
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            y = y + 32;
        }
        y = 480;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            x = x + 32;
        }
        x = 512;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            y = y + 32;
        }
        x = 288;
        y = 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(piedra1, x, y, WHITE);
            x = x + 32;
        }
        x = 64;
        y = 256;
        for (int i = 0; i < 3; i++) {
            DrawTexture(piedra1, x, y, WHITE);
            y = y + 32;
        }
        x = 288;
        y = 512;
        for (int i = 0; i < 2; i++) {
            DrawTexture(piedra1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(piedra2, x, y, WHITE);
        x = 544;
        y = 256;
        DrawTexture(piedra2, x, y, WHITE);
        y = y + 32;
        DrawTexture(piedra1, x, y, WHITE);
        y = y + 32;
        DrawTexture(piedra2, x, y, WHITE);
        y = 160;
        x = 192;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 160;
        x = 224;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 160;
        x = 384;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 160;
        x = 448;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 352;
        x = 192;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            x = x + 32;

        }
        y = 416;
        x = 192;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            x = x + 32;

        }
        y = 352;
        x = 384;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            x = x + 64;

        }
        y = 416;
        x = 384;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            x = x + 64;

        }
        DrawTexture(balas, 160, 160, WHITE);
        DrawTexture(balas, 288, 160, WHITE);
        DrawTexture(balas, 256, 192, WHITE);
        DrawTexture(balas, 480, 192, WHITE);
        DrawTexture(balas, 288, 288, WHITE);
        DrawTexture(balas, 384, 288, WHITE);
        DrawTexture(balas, 480, 320, WHITE);
        DrawTexture(balas, 256, 352, WHITE);
        DrawTexture(balas, 128, 416, WHITE);
        DrawTexture(balas, 448, 448, WHITE);

    }
    void Drawlevel10() {
        int x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 544, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 544, y, WHITE);
                }

            }
            y = y - 32;
        }
        x = 128;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_piedra, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 64;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            x = x + 32;
        }
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            y = y + 32;
        }
        y = 480;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            x = x + 32;
        }
        x = 512;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            y = y + 32;
        }
        x = 64;
        y = 64;
        for (int i = 0; i < 3; i++) {
            DrawTexture(lago5, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago6, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago5, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(puente2, x, y, WHITE);
            x = x + 32;
        }
        for (int i = 0; i < 3; i++) {
            DrawTexture(lago5, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago6, x, y, WHITE);
            x = x + 32;
        }
        x = 64;
        y = 480;
        for (int i = 0; i < 3; i++) {
            DrawTexture(lago5, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago6, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(lago5, x, y, WHITE);
        x = x + 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(puente2, x, y, WHITE);
            x = x + 32;
        }
        for (int i = 0; i < 3; i++) {
            DrawTexture(lago5, x, y, WHITE);
            x = x + 32;
            DrawTexture(lago6, x, y, WHITE);
            x = x + 32;
        }
        x = 288;
        y = 32;
        for (int i = 0; i < 3; i++) {
            DrawTexture(piedra1, x, y, WHITE);
            x = x + 32;
        }
        x = 288;
        y = 512;
        for (int i = 0; i < 3; i++) {
            DrawTexture(piedra1, x, y, WHITE);
            x = x + 32;
        }
        x = 544;
        y = 256;
        for (int i = 0; i < 3; i++) {
            DrawTexture(piedra1, x, y, WHITE);
            y = y + 32;
        }
        x = 64;
        y = 256;
        for (int i = 0; i < 2; i++) {
            DrawTexture(piedra1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(piedra2, x, y, WHITE);
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 320, 224, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 320, 224, WHITE);
                }

            }
        }
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 256, 288, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 256, 288, WHITE);
                }

            }
        }
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 384, 288, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 384, 288, WHITE);
                }

            }
        }
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 320, 320, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 320, 320, WHITE);
                }

            }
        }
        DrawTexture(balas, 192, 96, WHITE);
        DrawTexture(balas, 416, 96, WHITE);
        DrawTexture(balas, 416, 128, WHITE);
        DrawTexture(balas, 224, 160, WHITE);
        DrawTexture(balas, 256, 160, WHITE);
        DrawTexture(balas, 320, 192, WHITE);
        DrawTexture(balas, 480, 192, WHITE);
        DrawTexture(balas, 192, 288, WHITE);
        DrawTexture(balas, 384, 320, WHITE);
        DrawTexture(balas, 192, 352, WHITE);
        DrawTexture(balas, 160, 384, WHITE);
        DrawTexture(balas, 384, 384, WHITE);
        DrawTexture(balas, 480, 384, WHITE);
        DrawTexture(balas, 352, 448, WHITE);

    }
    void Drawlevel11() {
        int x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 32, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 64, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 64, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 64, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 64;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 512, WHITE);
                }

            }
            x = x + 32;

        }
        x = 544;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, 512, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, 512, WHITE);
                }

            }
            x = x - 32;

        }
        y = 32;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 544, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 512;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, 544, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, 544, y, WHITE);
                }

            }
            y = y - 32;
        }
        x = 128;
        y = 96;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_piedra, x, y, WHITE);
                y = y + 32;
            }
            y = 96;
            x = x + 32;
        }
        y = 64;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            x = x + 32;
        }
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            y = y + 32;
        }
        y = 480;
        x = 96;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            x = x + 32;
        }
        x = 512;
        y = 64;
        for (int i = 0; i < 14; i++) {
            DrawTexture(piedra3, x, y, WHITE);
            y = y + 32;
        }
        y = 32;
        x = 64;
        for (int i = 0; i < 16; i++) {
            DrawTexture(valla2, x, y, WHITE);
            x = x + 32;
        }
        y = 512;
        x = 64;
        for (int i = 0; i < 16; i++) {
            DrawTexture(valla2, x, y, WHITE);
            x = x + 32;
        }
        y = 256;
        x = 64;
        for (int i = 0; i < 3; i++) {
            DrawTexture(piedra1, x, y, WHITE);
            y = y + 32;
        }
        y = 256;
        x = 544;
        for (int i = 0; i < 3; i++) {
            DrawTexture(piedra1, x, y, WHITE);
            y = y + 32;
        }
        y = 64;
        x = 128;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            x = x + 64;

        }
        y = 480;
        x = 128;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(tumba1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(tumba2, x, y, WHITE);
                }

            }
            x = x + 64;

        }
        DrawTexture(balas, 128, 96, WHITE);
        DrawTexture(balas, 288, 128, WHITE);
        DrawTexture(balas, 352, 128, WHITE);
        DrawTexture(balas, 224, 192, WHITE);
        DrawTexture(balas, 192, 288, WHITE);
        DrawTexture(balas, 384, 320, WHITE);
        DrawTexture(balas, 192, 354, WHITE);
        DrawTexture(balas, 128, 416, WHITE);
        DrawTexture(balas, 256, 416, WHITE);
        DrawTexture(balas, 288, 448, WHITE);

    }


    /* EndDrawing();*/
    void LevelDraw(Game g) {

        if (g.CheckLevel() == 1) {

            Drawlevel1();
        }
        else if (g.CheckLevel() == 2) {

            Drawlevel2();

        }
        else if (g.CheckLevel() == 3) {

            Drawlevel3();

        }
        else if (g.CheckLevel() == 4) {

            Drawlevel4();

        }
        else if (g.CheckLevel() == 5) {

            Drawlevel5();

        }

        else if (g.CheckLevel() == 6) {

            Drawlevel6();

        }
        else if (g.CheckLevel() == 7) {

            Drawlevel7();

        }
        else if (g.CheckLevel() == 8) {

            Drawlevel8();

        }
        else if (g.CheckLevel() == 9) {

            Drawlevel9();

        }
        else if (g.CheckLevel() == 10) {

            Drawlevel10();

        }
        else if (g.CheckLevel() == 11) {

            Drawlevel11();

        }
        else if (g.CheckLevel() == 51) {

            Drawlevel51();

        }
        else if (g.CheckLevel() == 12) {

            ClearBackground(BLACK);

        }

    }

};
//toda esta classe esta dedicada a dibujar el fondo y sus animaciones
class UI {
private:
    Texture reloj = LoadTexture("ui/reloj.png");
    Texture vida = LoadTexture("items/128x128_cabeza.png");
    Texture moneda1 = LoadTexture("items/128x128_moneda1.png");
    Texture barra = LoadTexture("ui/barra.png");
public:
    friend int main();//dibuja la UI dependiendo de la vida y money del jugador
    void draw(Player p) {
        DrawTexture(vida, 0, 64, WHITE);
        DrawTexture(moneda1, 0, 96, WHITE);
        DrawTexture(barra, 14, 12, WHITE);
        DrawTexture(reloj, 70, 8, WHITE);
        if (p.lives < 0) {

            DrawText("0", 0 + 36, 72, 20, WHITE);

        }
        else {

            DrawText(TextFormat("%i", p.lives), 0 + 36, 71, 20, WHITE);

        }
        DrawText(TextFormat("%i", p.money), 0 + 36, 103, 20, WHITE);

    }

};
//classe dedicada a dibujar todo lo relacionado con la UI (vidas, monedas, etc)
class music {

private:
    Music Overworld;
    Music BossTrack;
    int bossStarted = 0;
    int starts;

public:

    music() {
        Overworld = LoadMusicStream("74.-Journey-Of-The-Prairie-King-_Overworld__1.mp3");
        BossTrack = LoadMusicStream("75.-Journey-Of-The-Prairie-King-_The-Outlaw_.ogg");
        starts = 0;
        bossStarted = 0;
    }

    void BossPlayer() {
        UpdateMusicStream(BossTrack);
        if (bossStarted == 0) {
            PlayMusicStream(BossTrack);
            bossStarted = 1;
        }
        if (GetMusicTimePlayed(BossTrack) / GetMusicTimeLength(BossTrack) > 1) {
            bossStarted = 0;
        }
    }

    //carga la musica
    void OverworldPlayer() {
        UpdateMusicStream(Overworld);
        if (starts == 0) {

            PlayMusicStream(Overworld);
            starts = 1;
        }
        UpdateMusicStream(Overworld);
        if (GetMusicTimePlayed(Overworld) / GetMusicTimeLength(Overworld) > 1) {

            starts = 0;
        }







    }
    //inicia la musica y la resetea si se acaba
    void StopAllMusic() {
        StopMusicStream(Overworld);
        StopMusicStream(BossTrack);
        starts = 0;
        bossStarted = 0;
    }

    //para la musica




};

class Title {

private:
    //cabeza2
    Texture view = LoadTexture("cabeza2.png");
    //IMG_0971
    Texture Chachi = LoadTexture("pene.png");
    bool GameBegin = false;
    Texture Instruct = LoadTexture("mov.png");
    int alive = 0;
    bool instructions = false;
    float InicialTime = 0;
public:
    friend int main();
    Title() {}

    void Presentation() {
        ClearBackground(BLACK);
        BeginDrawing();
        if (alive != 0) {
            InicialTime = GetTime();





        }
        float TimeNow = GetTime();
        float timepassed = TimeNow - InicialTime;

        if (timepassed < 5) {

            DrawText("This is an imitation of the game \n Journey of the prairie king", 0, 0, 20, WHITE);
            DrawText("Projecte 1, CITM, 1r Videojocs", 0, 40, 20, RED);
            DrawText("Irene, Queralt, Jiayi", 0, 60, 20, RED);




        }
        else if (timepassed < 10) {

            DrawTexture(Chachi, screenWidth / 2 - 64, screenHeight / 2 - 64, WHITE);

        }
        else {

            DrawTexture(view, 0, 0, WHITE);

            DrawText("Press the letter I for the instructions. Press it again for them to go away.\n And be able to start the game", 0, 490, 20, WHITE);
            if (IsKeyPressed(KEY_I)) { instructions = !instructions; }
            if (!instructions) {

                if (IsKeyDown(KEY_SPACE)) { GameBegin = true; }

            }
            else {


                DrawTexture(Instruct, 0, 0, WHITE);
            }

        }

        EndDrawing();

    }

};






//dibuja la pantalla de inicio y el texto
int main()
{
    // Tell the window to use vsync and work on high DPI displays
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitAudioDevice();
    // Create the window and OpenGL context
    InitWindow(screenWidth, screenHeight, "Hello Raylib");

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
    SearchAndSetResourceDir("resources");

    // Load a texture from the resources directory
    Texture logo = LoadTexture("sprites/personaje/128x128_persona7.png");


    //Texture bulletTex = LoadTexture("Bullet_1.png");
    std::vector<coins>money;
    time Tiempo();
    SetTargetFPS(60);
    Player p(1, 2);
    float HelpMeTime = 10;
    std::vector<Ogre>enemigo;
    int bulletaux;
    Boss b;




    Store tienda;
    Background desierto;
    time ui;
    UI aa;
    /* Ogre enemigo;*/
    music player;
    //creation of enemy vector
    int og = 0;
    //vector<Ogre> ogres(og);
    int ayxi = 0;
    int ogreaux = 0;
    std::vector<Shoot> bullets;
    int dire = 1;
    Game game;
    std::vector<float>auxTime;
    std::vector <PowerUpLive>Lives;
    std::vector<Coffee>cafe;
    std::vector <ScreenNuke>SN;
    std::vector <HeavyMachineGun>gun;

    std::vector <Orc>orcs;
    std::vector <Mariposa>marip;
    Title t;
    bool gameovertime = false;
    float GOtime = 0;
    bool tiendaActiva = false;
    while (!WindowShouldClose()) {

        if (t.GameBegin) {

            if (!game.gameover) {
                if (!game.wonGame) {

                    if (game.CheckLevel() == 5) { //mira que cancion 

                        player.BossPlayer();
                    }
                    else {

                        player.OverworldPlayer();
                    }
                    ui.DrawInicial();
                    game.GameStart(p, b, enemigo, bullets, og, ayxi, dire, ogreaux, bulletaux, ui, auxTime, HelpMeTime, Lives, money, orcs, marip, cafe, SN, gun, tienda);
                    desierto.LevelDraw(game);
                    aa.draw(p);


                }

                else {

                    game.GameWon();




                }



            }
            else {
                if (!gameovertime) {//ha acabado el juego y mira si han pasado 3 segundos para volver a la pantalla de inicio
                    GOtime = GetTime();

                    gameovertime = true;
                }
                game.GameOverScreen(p);
                player.StopAllMusic();

                float newTime = GetTime();
                float difference = newTime - GOtime;
                if (difference > 3) {

                    t.GameBegin = false;
                    gameovertime = false;
                    game.gameover = false;

                }
            }




        }
        else {


            //la presentacion del juego
            t.Presentation();
        }





    }
    p.Unload();
   

    CloseAudioDevice();
    CloseWindow();
    return 0;

};