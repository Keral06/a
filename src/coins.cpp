#include "raylib.h"
#include "resource_dir.h"
#include <vector>
#include "colision.cpp"


class coins : public Colision {
private:
    Texture moneda1 = LoadTexture("items/128x128_moneda1.png");
    Vector2 pos;
public:


public:
    friend class Game;
    friend class Player;
    friend class Colision;
    friend bool PlayerPowerUp(Player& p, PowerUpLive& pp);
    coins(Vector2 position) : Colision(pos) {
        this->pos = position;

        DrawTexture(moneda1, pos.x, pos.y, WHITE);


    }
    //dibuja el item de monedas
    bool ColisionMoney(Player& p) {

        bool check = CheckCollisionRecs(this->Square, p.Square);
        return check;



    }
    //suma la moneda al jugador



    void UsePowerUp(Player& p) {
        p.coins++;


    }
    //suma la moneda al jugador
    void Draw() {


        DrawTexture(moneda1, pos.x, pos.y, WHITE);
        ColisionPlayer(pos);
    }
    //dibuja la textura y una colision alrededor para saber cuando el jugador recoge la moneda






};