#include "raylib.h"
#include "resource_dir.h"
#include <vector>

class Colision {
public:
    Colision(Vector2 posicion) {
        BeginDrawing();
        float widthThing = 32;
        float HeightThing = 32;

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