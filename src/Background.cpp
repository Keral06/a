#include "raylib.h"
#include "resource_dir.h"
#include <vector>
#include "Stage.cpp"


class Background : public Stage {
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

public:
    int time = 0;
    friend int main();
    int currentTime = GetTime();


    void Drawlevel1() {
        /* BeginDrawing();*/
        int x = 0;
        DrawTexture(suelo, 32, 0, WHITE);
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 0, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 0, WHITE);
                }

            }
            x = x - 32;

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
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 480, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 480, WHITE);
                }

            }
            x = x - 32;

        }
        y = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480, y, WHITE);
                }

            }
            y = y - 32;

        }
        y = 224;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 480, y, WHITE);
            y = y + 32;
        }
        y = 256;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, 0, y, WHITE);
            y = y + 32;
        }
        y = 224;
        DrawTexture(desierto2, 0, y, WHITE);
        x = 224;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, x, 480, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, x, 480, WHITE);
        x = 224;
        DrawTexture(desierto1, x, 0, WHITE);
        x = x + 32;
        DrawTexture(desierto2, x, 0, WHITE);
        x = x + 32;
        DrawTexture(desierto1, x, 0, WHITE);
        y = 32;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        y = 448;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 448;
        y = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        x = 64;
        y = 64;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_desierto, x, y, WHITE);
                y = y + 32;
            }
            y = 64;
            x = x + 32;
        }
        y = 64;
        DrawTexture(desierto4, 416, y, WHITE);
        y = 128;
        DrawTexture(desierto4, 416, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 416 - 96, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 192, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 416 - 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 192 - 32, y, WHITE);
        DrawTexture(desierto4, 416, y, WHITE);
        y = y + 64;
        DrawTexture(desierto4, 96, y, WHITE);
        DrawTexture(desierto4, 192, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 416, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 96, y, WHITE);

    }

    void Drawlevel2() {
        /* BeginDrawing();*/
        int x = 0;
        DrawTexture(suelo, 32, 0, WHITE);
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 0, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 0, WHITE);
                }

            }
            x = x - 32;

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
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 480, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 480, WHITE);
                }

            }
            x = x - 32;

        }
        y = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480, y, WHITE);
                }

            }
            y = y - 32;

        }
        y = 224;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 480, y, WHITE);
            y = y + 32;
        }
        y = 224;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 0, y, WHITE);
            y = y + 32;
        }
        x = 224;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, x, 480, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, x, 480, WHITE);
        x = 224;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto2, x, 0, WHITE);
            x = x + 32;
        }
        y = 32;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        y = 448;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 448;
        y = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        x = 64;
        y = 64;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_desierto, x, y, WHITE);
                y = y + 32;
            }
            y = 64;
            x = x + 32;
        }
        x = 128;
        y = 128;
        for (int i = 0; i < 2; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        y = y + 32;
        x = x - 64;
        DrawTexture(valla, x, y, WHITE);
        x = 352;
        y = 128;
        for (int i = 0; i < 2; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x - 32;
        }
        y = y + 32;
        x = x + 64;
        DrawTexture(valla, x, y, WHITE);
        x = 128;
        y = 352 + 32;
        for (int i = 0; i < 2; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        y = y - 32;
        x = x - 64;
        DrawTexture(valla, x, y, WHITE);
        x = 352;
        y = 352 + 32;
        for (int i = 0; i < 2; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x - 32;
        }
        y = y - 32;
        x = x + 64;
        DrawTexture(valla, x, y, WHITE);
        y = 64;
        DrawTexture(desierto4, 224, y, WHITE);
        DrawTexture(desierto4, 352, y, WHITE);
        y = 128;
        DrawTexture(desierto4, 96, y, WHITE);
        DrawTexture(desierto4, 224, y, WHITE);
        DrawTexture(desierto4, 416, y, WHITE);
        y = 192;
        DrawTexture(desierto4, 224, y, WHITE);
        y = 192 + 32;
        DrawTexture(desierto4, 224 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 64, y, WHITE);
        DrawTexture(desierto4, 96 + 64, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 480 - 96, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 96 + 64, y, WHITE);
        x = 96 + 96 + 64;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto4, x, y, WHITE);
            x = x + 32;
        }
        y = y + 32;
        DrawTexture(desierto4, 64, y, WHITE);
        DrawTexture(desierto4, x - 32, y, WHITE);
        y = y + 32;
        DrawTexture(desierto4, 96, y, WHITE);
        DrawTexture(desierto4, 224, y, WHITE);
    }
    void Drawlevel3() {

        /* BeginDrawing();*/
        int x = 0;
        DrawTexture(suelo, 32, 0, WHITE);
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 0, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 0, WHITE);
                }

            }
            x = x - 32;

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
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 0, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 0, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 480, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 480, WHITE);
                }

            }
            x = x - 32;

        }
        y = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, 480, y, WHITE);
                }

            }
            y = y - 32;
        }
        y = 32;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        y = 448;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            x = x + 32;
        }
        x = 448;
        y = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto3, x, y, WHITE);
            y = y + 32;
        }
        x = 64;
        y = 64;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(fondo_desierto, x, y, WHITE);
                y = y + 32;
            }
            y = 64;
            x = x + 32;
        }
        y = 224;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 480, y, WHITE);
            y = y + 32;
        }
        y = 224;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto1, 0, y, WHITE);
            y = y + 32;
        }
        x = 224;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, x, 480, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, x, 480, WHITE);
        x = 224;
        for (int i = 0; i < 2; i++) {
            DrawTexture(desierto1, x, 0, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, x, 0, WHITE);
        x = 32;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 416;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 32, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 32, WHITE);
                }

            }
            x = x + 32;

        }
        x = 32;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 448, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 448, WHITE);
                }

            }
            x = x + 32;

        }
        x = 416;
        for (int i = 0; i < 2; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 448, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 448, WHITE);
                }

            }
            x = x + 32;

        }
        x = 32;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 64, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 64, WHITE);
                }

            }
        }
        x = 448;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 64, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 64, WHITE);
                }

            }
        }
        x = 32;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 416, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 416, WHITE);
                }

            }
        }
        x = 448;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, 416, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, 416, WHITE);
                }

            }
        }
        DrawTexture(valla, 256, 128, WHITE);
        DrawTexture(valla, 256, 384, WHITE);
        DrawTexture(valla, 128, 256, WHITE);
        DrawTexture(valla, 384, 256, WHITE);
        DrawTexture(desierto4, 160, 96, WHITE);
        DrawTexture(desierto4, 320, 128, WHITE);
        DrawTexture(desierto4, 64, 160, WHITE);
        DrawTexture(desierto4, 224, 160, WHITE);
        DrawTexture(desierto4, 160, 192, WHITE);
        DrawTexture(desierto4, 320, 192, WHITE);
        DrawTexture(desierto4, 192, 256, WHITE);
        DrawTexture(desierto4, 96, 288, WHITE);
        DrawTexture(desierto4, 128, 352, WHITE);
        DrawTexture(desierto4, 256, 352, WHITE);
        DrawTexture(desierto4, 192, 384, WHITE);
        DrawTexture(desierto4, 352, 416, WHITE);
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

            ClearBackground(BLACK);

        }

    }

};