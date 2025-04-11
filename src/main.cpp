//copia

#include "raylib.h"


#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>  // Add this include for std::vector


const int screenWidth = 1024 / 2 + 32*2;


const int screenHeight = 1024 / 2 + 32;
class Player;
class Enemy;
class Mummy;
class Orc;
class Shoot;
class Ogre;
class time;
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
        float widthThing = 32;
        float HeightThing = 32;

        DrawRectangle(posicion.x, posicion.y, widthThing, HeightThing, BLANK);
        Square = { posicion.x,posicion.y, widthThing, HeightThing };

    }
    void ColisionPlayer(Vector2 posicion) {

        DrawRectangle(posicion.x, posicion.y, 32, 32, BLANK);
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
    void ResetPlayer() {
    
        playerPos = { (float)screenWidth / 2, (float)screenHeight / 2 };
        status = true;
    
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

    void Death() {
    
        lives--;
    
    }
    friend class Enemy;
    friend class Colision;
    friend class Ogre;
    friend class PowerUpLive;
};

class Enemy : public Entity {
public:
    friend class Shoot;
    Enemy(int hp, int vel) : Entity(hp, vel, { 0,0 }) {
        int posicion = pos();
        if (posicion == 1) {
            playerPos = { ((float)screenWidth / 2),32 };
        }
        else if (posicion == 2) {
            playerPos = { 32, ((float)screenHeight / 2) };

        }
        else if (posicion == 3) {

            playerPos = { ((float)screenWidth / 2), (float)screenHeight - 32 * 2 };
        }
        else {
            playerPos = { 32, ((float)screenHeight / 2) };

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
    Texture Death1 = LoadTexture("effects/128x128_hierba1.png");
    Texture Death2 = LoadTexture("effects/128x128_hierba2.png");
    Texture Death3 = LoadTexture("effects/128x128_hierba3.png");
    Texture Death4 = LoadTexture("effects/128x128_hierba4.png");
    Texture Death5 = LoadTexture("effects/128x128_hierba5.png");
    Texture Death6 = LoadTexture("effects/128x128_hierba6.png");
    

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

    //void Death() {
    //
    //
    //    /*int i = 0;

    //    while (i < 120) {
    //        if (i <= 20) {
    //            DrawTexture(Death1, GetPosition().x, GetPosition().y, WHITE);
    //        
    //        }else if(20 < 1 >= 40) {
    //            DrawTexture(Death2, GetPosition().x, GetPosition().y, WHITE);
    //        }
    //        else if (40 < i >= 60) {
    //        
    //            DrawTexture(Death3, GetPosition().x, GetPosition().y, WHITE);
    //        
    //        }
    //        else if (60 < i >= 80) {
    //        
    //            DrawTexture(Death4, GetPosition().x, GetPosition().y, WHITE);
    //        }
    //        else if (80 < i >= 100) {
    //        
    //            DrawTexture(Death5, GetPosition().x, GetPosition().y, WHITE);
    //        
    //        }
    //        else {
    //        
    //            DrawTexture(Death6, GetPosition().x, GetPosition().y, WHITE);
    //        
    //        }
    //    
    //    
    //    
    //        i++;
    //    }*/
    //    
    //
    //
    //}

    /*void ColisionMonster(Player p) override {









   }*/

    friend class Colision;

};
class PowerUpLive {
private:

public:

    PowerUpLive() {
    
    
    
    }

    void UsePowerUp( Player &p) {
        p.lives++;

    
    }


};

class DeadOgre {
private:
    Texture Mon1 = LoadTexture("effects/128x128_hierba6.png");
    Vector2 playerPos;
public:

    DeadOgre(Vector2 playerPos) {
        this->playerPos = playerPos;
    
    }

    void Draw() {
    
        DrawTexture(Mon1, playerPos.x, playerPos.y, WHITE);
    
    }



};
class Shoot : public Colision {

private:
    Vector2 playerPos;
   
public:
    friend class Enemy;
    Direccion dir;
    Vector2 GetPosition() const { return this->playerPos; }
    bool ColisionBullet(Enemy s) {

        bool Check = CheckCollisionRecs(this->Square, s.Square);

        return Check;


    }
    Shoot(Player p) : Colision(p.GetPosition()) {
        playerPos = { p.GetPosition().x + 32 / 2, p.GetPosition().y + (32) };
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
class time {
private:
    Texture barra = LoadTexture("ui/barra.png");
    Texture reloj = LoadTexture("ui/reloj.png");
    double tiempoInicial;
    double tiempoFinal;
    double tiempoTranscurrido;
    int barraAncho;
    int aux;
public:

    time() {

        tiempoFinal = 80.0;
        tiempoTranscurrido = 0;
        barraAncho = 520;
        aux = 0;
        tiempoInicial = 0;
    }
    void DrawInicial() {
    
        DrawRectangle(0, 1024 / 2, 1024/2, 32, GREEN);
    
    }
    void Draw() {
        
     
        double porcentaje = tiempoFinal/tiempoTranscurrido;
        barraAncho = (int)((1024/2) * (1 - porcentaje));
        
        if (barraAncho % 6 == 0) {


         DrawRectangle(0, 1024 / 2, barraAncho, 32, GREEN);

         aux = barraAncho;
        }
        else {
        
            DrawRectangle(0, 1024 / 2, aux, 32, GREEN);
        }
        
    }
    void IniciarTiempo() {

        tiempoInicial = GetTime();
        tiempoFinal = tiempoInicial + 10.0;

    }
    void TiempoQueHaPasado() {

        tiempoTranscurrido = tiempoFinal - GetTime();


    }
    void tiempo() {
        if (tiempoFinal = tiempoTranscurrido) {
            /*game over*/
        }

    }





};

class Game {
private:

    Texture bulletTex = LoadTexture("Bullet_1.png");
    std::vector<DeadOgre>dead;
    int deadogres;
    bool tiempoiniciado;
public:

    Game() {
        deadogres = 0;
        Stage stage();
        level Level();
        /*  BeginDrawing();*/
        std::vector<DeadOgre>dead;
        tiempoiniciado = false;
    }

    void GameStart(Player& p, std::vector<Ogre>& enemigo, std::vector<Shoot>& bullets, int& og, int& ayxi, int& dire, int& ogreaux, int& bulletaux, time &Tiempo, std:: vector<float>&auxTime, float &HelpMeTime) {
        if (tiempoiniciado == false) {
        
            Tiempo.IniciarTiempo();
            tiempoiniciado = true;
            Tiempo.DrawInicial();
        }
        else {
        
            Tiempo.TiempoQueHaPasado();
            Tiempo.Draw();
        
        
        }
        ClearBackground(BLACK);
        /*BeginDrawing();*/
        BeginDrawing();

        
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



        


        int bulletSize = bullets.size();



        /*  BeginDrawing();
          ClearBackground(RAYWHITE);*/

        if (GetRandomValue(1, 40) == 1 && ogreaux < 6) {

            Ogre auxiliar;
            enemigo.push_back(auxiliar);
            ogreaux++;

        }
        int i = 0;
        i = 0;// Update and remove off-screen bullets
        /*bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                [](const Shoot& bullet) {
                    Vector2 pos = bullet.GetPosition();
                    return pos.x < 0 || pos.x > screenWidth ||
                        pos.y < 0 || pos.y > screenHeight;
                }
            ),
            bullets.end()*/
            /* );*/

        while (i < bulletSize) {
            
            bullets[i].UpdatePosition();
            DrawTexture(bulletTex, bullets[i].GetPosition().x, bullets[i].GetPosition().y, WHITE);
            i++;
        }
       
        
        ogreaux = enemigo.size();
            i = 0;
            if (ogreaux > 0) {

                i = 0;
                int j = 0;
                int aux = 0;
                while (i < ogreaux) {

                    while (j < bulletSize) {
                        if (i >= ogreaux) {
                        
                        
                        }
                        else {
                        
                            if (bullets[j].ColisionBullet(enemigo[i]) == true) {
                                DeadOgre auxiliari(enemigo[i].GetPosition());
                                dead.push_back(auxiliari);
                                float timehelp = GetTime();
                                auxTime.push_back(timehelp);
                                deadogres++;
                                ogreaux = enemigo.size();
                                /* enemigo[i].Death();*/
                                if (ogreaux == 1) {
                                    enemigo.pop_back();
                                    
                                }

                                else if (ogreaux > 1) {
                                    aux = i;
                                    while (aux < ogreaux - 1) {

                                        enemigo[aux] = enemigo[aux + 1];
                                        aux++;

                                    }
                                    enemigo.pop_back();
                                    

                                }
                                ogreaux = enemigo.size();
                                bulletSize = bullets.size();
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
                                   
                                }
                                bulletSize = bullets.size();
                        
                            }
                       
                            
                        }

                        if (ogreaux == 0) { j = bulletSize; }

                        j++;
                    }

                    j = 0;
                    i++;


                }

            
             }
            i = 0;
            
            while (i < deadogres) {
            
            
                    dead[i].Draw();

                    float auxiliart = GetTime();

                    i++;
                    if (GetRandomValue(1,4)==2 && auxiliart - auxTime[deadogres - 1] > 5.0f) {
                    dead.pop_back();

                    auxTime.pop_back();
                    deadogres = dead.size();

                    HelpMeTime = GetTime();


                    }
            }
            i = 0;
            deadogres = dead.size();
            if (deadogres > 1) {

                if (deadogres == 10) {
                    int hh = 1;
                
                }
            }
                
              
           
            i = 0;
            ogreaux = enemigo.size();
            while (i < ogreaux) {

                enemigo[i].CheckColisions(p);

                if (p.status == true) {

                    enemigo[i].MovementEnemy(p);


                }

                enemigo[i].Draw();

                i++;

            }
            i = 0;
            bulletSize = bullets.size();
            while (i < bulletSize) {

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
           
            if (bulletSize > 20) {
                bulletSize = bullets.size();
            };
        p.Movement();
        p.Draw();
        EndDrawing();
        if (p.status == false) {
        
        
            p.Death();

            int x = 0;

            while (x < ogreaux) {
            
                enemigo.pop_back();
                x++;
            }
            ogreaux = 0;
            x = 0;
            while (x < bulletSize) {
                bullets.pop_back();
                x++;
            
            
            }
            bulletSize = 0;
            x = 0;
           /* while (x < deadogres) {
            
                dead.pop_back();
                x++;
            
            }
            deadogres = 0;*/
            tiempoiniciado = false;
            if (p.lives == 0) {
            
                GameOver();
            
            }
            else {
            p.ResetPlayer();
            
            }
        }

        // Set background color (framebuffer clear color)
/*  EndDrawing();*/
    }
    void GameOver() {
    
        DrawRectangle(0, 0, 520, 520, BLACK);
    
    
    }

};

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
    Texture vida = LoadTexture("items/128x128_cabeza.png");
    Texture monedaa = LoadTexture("items/128x128_moneda1");
public:
    int time = 0;
    friend int main();
    int currentTime = GetTime();
    void Drawlevel1() {
        /* BeginDrawing();*/
        int x = 0;
        DrawTexture(vida, 512, 64, WHITE);
        DrawTexture(monedaa, 512, 96, BLANK);
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

    }

   





        /* EndDrawing();*/


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

    time Tiempo();
    SetTargetFPS(60);
    Player p(1, 2);
    float HelpMeTime = 10;
    std::vector<Ogre>enemigo;
    int bulletaux;

    Background desierto;
    time ui;
    /* Ogre enemigo;*/

     //creation of enemy vector
    int og = 0;
    //vector<Ogre> ogres(og);
    int ayxi = 0;
    int ogreaux = 0;
    std::vector<Shoot> bullets;
    int dire = 1;
    Game game;
    std::vector<float>auxTime;
    while (!WindowShouldClose()) {



        game.GameStart(p, enemigo, bullets, og, ayxi, dire, ogreaux, bulletaux, ui, auxTime, HelpMeTime);
    
        desierto.Drawlevel1();
        ui.DrawInicial();

        
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
