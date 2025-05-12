#include "raylib.h"
#include "resource_dir.h"
#include <vector> 

/*declarar las medidas de la pantalla jugable y de la pantalla en general*/
const int screenWidth = 1024 / 2 + 32 * 2;
const int screenHeight = 1024 / 2 + 32;
const int playerScreenX = 1024 / 2;
const int playerScreenY = 1024 / 2;
// declarar las clases que se usaran
class Colision;
class Player;
class Enemy;
class Mummy;
class Orc;
class Shoot;
class Ogre;
class PowerUpLive;
class time;
class Title;
class Store;
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
    Sound Walk = LoadSound("sound effects/prairie king walk.ogg"); 
    Sound Die = LoadSound("sound effects/enemy death.ogg");

};
/*clase padre utilizada para declarar los valores (vida, velocidad) de tanto el player como los enemigos
tambien se utiliza para los sonidos de movimiento y muerte
*/
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
    Texture Humo1 = LoadTexture("effects/muerte.png");
    Texture Humo2 = LoadTexture("effects/muerte1.png");
    Texture Humo3 = LoadTexture("effects/muerte2.png");
    Texture Humo4 = LoadTexture("muerte3.png");
    Texture Humo5 = LoadTexture("muerte4.png");
    Sound death = LoadSound("song/cowboy_dead.wav");
    bool status;
    int bag;
    float deathStartTime = 0;

public:
    friend int main();
    friend class coins;
    friend class UI;
    friend class Game;
    friend class Orc;
    friend class Mariposa;
    friend class Coffee; 
    friend  bool PlayerPowerUpCoffee(Player& p, Coffee& pp);

    Player(int hp, int vel) : Entity(hp, vel, { (float)playerScreenX / 2, (float)playerScreenY / 2 }) {
        this->coins = 0;
        this->lives = 3;
        this->dir = ARRIBA;
        dire = 1;
        status = true;
        bag = 0;
    } //declara los valores iniciales del jugador
    int dire;
    void playerAgain() {

        this->coins = 0;
        this->lives = 3;
        this->dir = ARRIBA;
        dire = 1;
        status = true;
        bag = 0;

    }
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
    //dibuja el sprite indicado del jugador dependiendo de la direccion en la que se mueve
    void ResetPlayer() {

        playerPos = { (float)playerScreenX / 2, (float)playerScreenY / 2 };
        status = true;

    }
    //resetea al jugador cuando muere

    void Movement(int level) {

        /* BeginDrawing();*/
        Texture Abajo1 = LoadTexture("64x64/personaje.adelante2.png");
        Texture Abajo2 = LoadTexture("64x64/personaje.adelante1.png");
        bool moved = false;
        float nextX = playerPos.x;
        float nextY = playerPos.y;

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
                nextY -=vel;
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
                nextX +=vel;
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
                nextY -=vel;
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
                }

            }

            ColisionPlayer(playerPos);
            if (nextX >= 32 && nextX <= playerScreenX - 64 &&
                nextY >= 32 && nextY <= playerScreenY - 64) {

                if (level == 1) {


                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }
                else if (level == 2) {


                    if (nextX < 96 || (nextX > 188 && nextX < 288) || (nextX > 416)) {
                        /*if (nextY < 128 || (nextY > 160 && nextY < 256) || (nextY > 384)) {*/
                        playerPos.x = nextX;
                        playerPos.y = nextY;
                        /*}
                        else {

                        }*/



                    }
                    else if (nextX <= 188 || nextX >= 288) {

                        if (nextY > 384 || nextY < 96 || (nextY > 188 && nextY < 324)) {

                            playerPos.x = nextX;
                            playerPos.y = nextY;


                        }
                        else if (nextX <= 188 && nextX >= 158) {

                            if (nextY >= 160 && nextY <= 350) {

                                playerPos.x = nextX;
                                playerPos.y = nextY;

                            }

                        }
                        else if (nextX >= 288 && nextX <= 320) {

                            if (nextY >= 160 && nextY <= 350) {

                                playerPos.x = nextX;
                                playerPos.y = nextY;

                            }

                        }


                    }
                    else {



                    }




                }
                else if (level == 3) {
                    if (nextX > 384 || nextX < 96 || (nextX > 220 && nextX < 354)) {

                        if (nextY > 384 || nextY < 96 || (nextY > 220 && nextY < 354)) {

                            playerPos.x = nextX;
                            playerPos.y = nextY;


                        }
                        else {

                        }
  
                    }
                    else if ((nextX > 30 && nextX < 230))
                    {

                        if ((nextY > 30 && nextY < 230)) {

                            playerPos.x = nextX;
                            playerPos.y = nextY;


                        }
                    }
                    else if ((nextX > 260 && nextX < 448))
                    {

                        if ((nextY > 30 && nextY < 230)) {

                            playerPos.x = nextX;
                            playerPos.y = nextY;


                        }
                    }


                    
                    //if (nextX < 224 || (nextX > 256) || (nextX > 416)) {
                    //    /*if (nextY < 128 || (nextY > 160 && nextY < 256) || (nextY > 384)) {*/
                    //    playerPos.x = nextX;
                    //    playerPos.y = nextY;
                    //    /*}
                    //    else {

                    //    }*/



                    //}
                    //else if (nextX < 224  && nextX > 256 /*|| nextX <= 128 || nextX >= 384*/) {
                    //    if (nextY > 384 || nextY < 96 || (nextY > 188 && nextY < 324)/* || nextY <= 128*/) {
                    //        
                    //            playerPos.x = nextX;
                    //            playerPos.y = nextY;
                    //        
                    //        
                    //    }
                    //    else if (nextX >= 288 && nextX <= 320) {

                    //        if (nextY >= 160 && nextY <= 350) {

                    //            playerPos.x = nextX;
                    //            playerPos.y = nextY;

                    //        }

                    //    }
                    //    else {

                    //    }
                        //else if (nextX <= 250 && nextX >= 290)
                        //{
                        //    if (nextY <= 130 && nextY >= 170/* || nextY <= 128*/) {
                        //        playerPos.x = nextX;
                        //        playerPos.y = nextY;
                        //    }
                        //}




                }

                
            }
        }
    }


                


    
	//declara el movimiento del jugador dependiendo de la tecla que presione y la direccion en la que se mueve
    //declara las posiciones donde el jugador no puede acceder, colisiones
    void DeathAnim() {


        float currentTime = GetTime();
        float elapsed = currentTime - deathStartTime;

        if (elapsed < 0.1) {
            DrawTexture(Humo1, GetPosition().x, GetPosition().y, WHITE);
        }
        else if (elapsed < 0.2) {
            DrawTexture(Humo2, GetPosition().x, GetPosition().y, WHITE);
        }
        else if (elapsed < 0.3) {
            DrawTexture(Humo3, GetPosition().x, GetPosition().y, WHITE);
        }
        else if (elapsed < 0.4) {
            DrawTexture(Humo4, GetPosition().x, GetPosition().y, WHITE);
        }
        else if (elapsed < 0.5) {
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
        }
        lives--;

        deathStartTime = GetTime();
       

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
public:
    friend class Game;
    friend class Player;
    friend class Colision;
    friend bool PlayerPowerUp(Player& p, PowerUpLive& pp);
    PowerUpLive(Vector2 position) : Colision(pos) {
        this->pos = position;

        DrawTexture(vida, pos.x, pos.y, WHITE);


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


        DrawTexture(vida, pos.x, pos.y, WHITE);
        ColisionPlayer(pos);
    }
	//dibuja la textura y una colision alrededor para saber cuando el jugador la recoge


};
class ScreenNuke : public Colision {

private:
    Texture vida = LoadTexture("items/128x128_tumbacraneo.png");
    Vector2 pos;
public:
    friend class Game;
    friend class Player;
    friend class Colision;

    friend  bool PlayerPowerUpCoffee(Player& p, Coffee& pp);
    ScreenNuke(Vector2 position) : Colision(pos) {
        this->pos = position;

        DrawTexture(vida, pos.x, pos.y, WHITE);


    }
    //dibuja el item de vida +
    ScreenNuke(Player p) : Colision(pos) {

        

    }
    //suma la vida al jugador despues de recoger el item



    void UsePowerUp( std::vector<Ogre>& enemigo, std::vector <Orc>orcs, std::vector <Mariposa>marip) {

        int i = 0;

        while (enemigo.size() != 0) {
        
            enemigo.pop_back();
        
        
        }
        while (orcs.size() != 0) {
        
            orcs.pop_back();
        
        
        }
        while (marip.size() != 0) {
        
            marip.pop_back();
        
        }

    }
    
    //suma la vida
    void Draw() {


        DrawTexture(vida, pos.x, pos.y, WHITE);
        ColisionPlayer(pos);
    }
    //dibuja la textura y una colision alrededor para saber cuando el jugador la recoge






};
class Coffee : public Colision {
private:
    Texture vida = LoadTexture("items/128x128_taza.png");
    Vector2 pos;
public:
    friend class Game;
    friend class Player;
    friend class Colision;
 
    friend  bool PlayerPowerUpCoffee(Player& p, Coffee& pp);
    Coffee(Vector2 position) : Colision(pos) {
        this->pos = position;

        DrawTexture(vida, pos.x, pos.y, WHITE);


    }
    //dibuja el item de vida +
    Coffee(Player p) : Colision(pos) {

        p.vel += 2;

    }
    //suma la vida al jugador despues de recoger el item



    void UsePowerUp(Player& p) {
      
        p.vel += 2;

    }
    void StopUsing(Player p) {
    
        p.vel -= 2;
    
    
    }
    //suma la vida
    void Draw() {


        DrawTexture(vida, pos.x, pos.y, WHITE);
        ColisionPlayer(pos);
    }
    //dibuja la textura y una colision alrededor para saber cuando el jugador la recoge


};


class Enemy : public Entity {
public:
    friend class Shoot;
    friend int main();
    friend class coins;
    friend class UI;
    friend class Game;
    Enemy(int hp, int vel) : Entity(hp, vel, { 0,0 }) {
        int posicion = pos();
        if (posicion == 1) {
            playerPos = { ((float)playerScreenX / 2),32 };
        }
        else if (posicion == 2) {
            playerPos = { 32, ((float)playerScreenY / 2) };

        }
        else if (posicion == 3) {

            playerPos = { ((float)playerScreenX / 2), (float)playerScreenY - 64 };
        }
        else {
            playerPos = { (float)playerScreenX -64, ((float)playerScreenY / 2)};

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






        if (nextX >= 32 && nextX <= playerScreenX - 64 &&
                nextY >= 32 && nextY <= playerScreenY -64) {

                if (level == 1) {
                
                
                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }
                else if (level == 2) {


                    if (nextX < 96 || (nextX > 188 && nextX < 288) || (nextX > 416)) {
						/*if (nextY < 128 || (nextY > 160 && nextY < 256) || (nextY > 384)) {*/
							playerPos.x = nextX;
							playerPos.y = nextY;
						/*}
                        else {

                        }*/


                     
                    }
                    else if (nextX <= 188 || nextX >= 288) {
                    
                        if (nextY > 384 || nextY < 96 ||( nextY > 188 && nextY < 324)) {
                        
                            playerPos.x = nextX;
                            playerPos.y = nextY;
                        
                        
                        }
                        else if (nextX<=188 && nextX>=158) {
                        
                            if (nextY >= 160&& nextY <=350) {
                            
                                playerPos.x = nextX;
                                playerPos.y = nextY;
                            
                            }
                        
                        }
                        else if (nextX >= 288 && nextX<= 320){
                        
                            if (nextY >= 160 && nextY <= 350) {

                                playerPos.x = nextX;
                                playerPos.y = nextY;

                            }
                        
                        }
                    
                    
                    }
                    else {
                    
                    
                    
                   }
                    
               
                
                
                }
                
        }
           

        


        ColisionPlayer(playerPos);
    }
       
    
	//declara el movimiento del enemigo y la direccion en la que se mueve dependiendo de la posicion del jugador
    //declara las posiciones donde el enemigo no puede acceder, colisiones


    bool CheckColisions(Player& p) {

        bool check = CheckCollisionRecs(this->Square, p.Square);
        if (check == true) {

            p.status = false;
        }

        return p.status;

    }
	//chequea las colisiones 
protected:

  



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
    Orc() : Enemy(3, 1) {





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
    Mariposa() : Enemy(3, 1) {





    }
    //declara al enemigo
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






        if (nextX >= 32 && nextX <= playerScreenX - 64 &&
            nextY >= 32 && nextY <= playerScreenY - 64) {

          


                playerPos.x = nextX;
                playerPos.y = nextY;
            }
    
    
    }
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
        if (elapsed > 5) {
        
        
            return true;
        }

        return false;
    
    }
	//chequea si el ogro ha muerto hace mas de 5 segundos para eliminar la basura que deja

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
    

};

class Shoot : public Colision {

private:
    Vector2 playerPos;
    Sound shooter = LoadSound("sound effects/prairie king bullet.ogg");
    bool eliminate = false;
   
public:
    friend class Enemy;
    Direccion dir;
    Vector2 GetPosition() const { return this->playerPos; }
    bool ColisionBullet(Enemy s) {

        bool Check = CheckCollisionRecs(this->Square, s.Square);

        return Check;


    }
	//chequea si la bala colisiona con el enemigo

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
		//chequea si la bala ha salido de la pantalla

        if (nextX >= 32 && nextX <= playerScreenX - 32 &&
            nextY >= 32 && nextY <= playerScreenY - 32) {

            if (level == 1) {


                playerPos.x = nextX;
                playerPos.y = nextY;
            }
            else if (level == 2) {


                if (nextX < 96 || (nextX > 188 && nextX < 288) || (nextX > 416)) {
                    /*if (nextY < 128 || (nextY > 160 && nextY < 256) || (nextY > 384)) {*/
                    playerPos.x = nextX;
                    playerPos.y = nextY;
                    /*}
                    else {

                    }*/



                }
                else if (nextX <= 188 || nextX >= 288) {

                    if (nextY > 384 || nextY < 96 || (nextY > 188 && nextY < 324)) {

                        playerPos.x = nextX;
                        playerPos.y = nextY;


                    }
                    else if (nextX <= 188 && nextX >= 158) {

                        if (nextY >= 160 && nextY <= 350) {

                            playerPos.x = nextX;
                            playerPos.y = nextY;

                        }
                        else {
                        
                            eliminate = true;
                        }

                    }
                    else if (nextX >= 288 && nextX <= 320) {

                        if (nextY >= 160 && nextY <= 350) {

                            playerPos.x = nextX;
                            playerPos.y = nextY;

                        }
                        else {
                        
                            eliminate = true;
                        }

                    }
                    else {
                    
                        eliminate = true;
                    }


                }
                else {

                    eliminate = true;

                }




            }

        }
        else {
        
            eliminate = true;
        }
        ColisionBullet(playerPos);
		// Check si la bala colisiona con algo del escenario

    }

    void ColisionBullet(Vector2 posicion) {

        DrawRectangle(posicion.x, posicion.y, 3, 3, BLANK);
        Square.x = posicion.x;
        Square.y = posicion.y;


    }
	//dibuja un cuadrado invisible en el escenario para indicar la colision


};

class level {
protected:
    int levels;


public:

    level() {

        levels = 7;

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

        stage = 7;

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

        aux = aux+ help - tiempoFake;

        tiempoFinal = tiempoInicial + 80 + aux;
    }
    void pause() {
    
        tiempoFake = GetTime();
    
    }
    void DrawInicial() {

        //DrawRectangle(0, 1024 / 2, playerScreenX / 2, 32, GREEN);

    }
    void Draw() {
       
        DrawRectangle(0, 1024 / 2, barraAncho, 32, GREEN);

        double porcentaje = tiempoTranscurrido/ tiempoFinal ;

        barraAncho = (int)((playerScreenX) * (1 - porcentaje));
        /*DrawRectangle(0, 1024 / 2, barraAncho, 32, GREEN);*/

        
       
       

    }
    void IniciarTiempo() {

        tiempoInicial = GetTime();
        tiempoFinal = tiempoInicial +80.0f ;
        aux = 0;

    }
    void TiempoQueHaPasado() {
        float tiempoAhora = GetTime();
        tiempoTranscurrido = tiempoAhora - tiempoInicial - aux;


    }
    bool tiempo() {
        if (tiempoTranscurrido > tiempoFinal) {
            return true;
        }
        else { false; }

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
class Game {
private:

    int level;
    bool wonGame = false;
    int stage;
    bool tiempoFake = false;
    Texture bulletTex = LoadTexture("Bullet_1.png");
    std::vector<DeadOgre>dead;
    int deadogres;
    bool tiempoiniciado;
    Sound power = LoadSound("song/cowboy_powerup.wav");
    Sound Die = LoadSound("song/cowboy_dead.wav");
    bool gameover = false;
    float timesincedeletion = 0;
    float timeoflastdelete = 0;
    float timeOfLive = 0;
public:
    friend int main();
    Game() {
        deadogres = 0;
        level = 7;
        stage = 7;
        /*  BeginDrawing();*/
        std::vector<DeadOgre>dead;
        tiempoiniciado = false;
    }
	//declara el nivel y stage inicial
    void GameStart(Player& p, std::vector<Ogre>& enemigo, std::vector<Shoot>& bullets, int& og, int& ayxi, int& dire, int& ogreaux, int& bulletaux, time& Tiempo, std::vector<float>& auxTime, float& HelpMeTime, std::vector <PowerUpLive>& Lives, std::vector<coins>&money, std::vector <Orc>&orcs, std::vector <Mariposa>&marip) {
        if(p.status){
            ClearBackground(BLACK);
            /*BeginDrawing();*/
            BeginDrawing();
            if (tiempoiniciado == false) {

                Tiempo.IniciarTiempo();
                tiempoiniciado = true;
                Tiempo.DrawInicial();
            }
            else {

                Tiempo.TiempoQueHaPasado();
                Tiempo.Draw();


            }
           //empieza el tiempo, lo dibuja y lo va actualizando



            // Handle bullet creation with arrow keys
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) ||
                IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)) {
                // Add rate limiting for bullets
                static float shootTimer = 0.0f;
                if (shootTimer <= 0) {
                    bullets.push_back(Shoot(p));
                    shootTimer = 0.4f; // Shoot every 0.2 seconds while holding key
                }
                shootTimer -= GetFrameTime();


            }
			





            int bulletSize = bullets.size();



            if (level > 3) {
                int i = 0;
                if (GetRandomValue(1, 40) == 1 && enemigo.size() + orcs.size() + marip.size() < 15) {

                    Orc auxiliar;
                    orcs.push_back(auxiliar);
                    

                }
                if (orcs.size() > 0) {

                  
                    int j = 0;
                    int aux = 0;
                    while (i < orcs.size()) {

                        while (j < bullets.size()) {
                            if (i >= orcs.size()) {


                            }
                            else {

                                if (bullets[j].ColisionBullet(orcs[i]) == true) {

                                    DeadOgre auxiliari(orcs[i].GetPosition());
                                    dead.push_back(auxiliari);
                                    float timehelp = GetTime();
                                    auxTime.push_back(timehelp);
                                    deadogres++;
                                    

                                    int a = 0;
                                    if (GetRandomValue(1, 10) == 1 && Lives.size() == 0) {
                                        Vector2 ee = enemigo[i].GetPosition();
                                        PowerUpLive live(ee);
                                        Lives.push_back(live);
                                        timeOfLive = GetTime();
                                        a = 1;

                                    }




                                    if (orcs.size() == 1) {
                                        orcs[i].Death();
                                        orcs.pop_back();

                                    }

                                    else if (orcs.size() > 1) {

                                        aux = i;
                                        orcs[i].Death();;
                                        while (aux < orcs.size() - 1) {

                                            orcs[aux] = orcs[aux + 1];
                                            aux++;

                                        }
                                        orcs.pop_back();


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
                            if (orcs.size() == 0) { j = bulletSize; }

                            j++;
                        }

                        j = 0;
                        i++;


                    }


                }



                
               
               

            }
            if (level > 6) { //mariposa
                int i = 0;
                if (GetRandomValue(1, 40) == 1 && enemigo.size() + orcs.size()+ marip.size()< 15) {

                    Mariposa auxiliar;
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


                                    int a = 0;
                                    if (GetRandomValue(1, 10) == 1 && Lives.size() == 0) {
                                        Vector2 ee = marip[i].GetPosition();
                                        PowerUpLive live(ee);
                                        Lives.push_back(live);
                                        timeOfLive = GetTime();
                                        a = 1;

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


                if (level > 0) { //ogre
                    int i = 0;
                    if (GetRandomValue(1, 40) == 1 && enemigo.size() + orcs.size() + marip.size() < 15) {

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


                                        int a = 0;
                                        if (GetRandomValue(1, 10) == 1 && Lives.size() == 0) {
                                            Vector2 ee = enemigo[i].GetPosition();
                                            PowerUpLive live(ee);
                                            Lives.push_back(live);
                                            timeOfLive = GetTime();
                                            a = 1;

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




            }
            int i = 0;
            deadogres = dead.size();
           

            
			//actualiza la vida del jugador cada vez que recoge el power up de vida
            if (IsKeyDown(KEY_SPACE) && p.bag == 1) {
                p.bag--;
                PowerUpLive auxy(p);
                auxy.UsePowerUp(p);

            }




            i = 0;
            ogreaux = enemigo.size();
            while (i < ogreaux) {

                enemigo[i].CheckColisions(p);

                if (p.status == true) {

                    enemigo[i].MovementEnemy(p, this->level);


                }

                enemigo[i].Draw();

                i++;

            }
            i = 0;
            while (i < orcs.size()) {

                orcs[i].CheckColisions(p);

                if (p.status == true) {

                    orcs[i].MovementEnemy(p, this->level);


                }

                orcs[i].Draw();

                i++;

            }
            i = 0;
            while (i < marip.size()) {

                marip[i].CheckColisions(p);

                if (p.status == true) {

                    marip[i].MovementMariposa(p);


                }

                marip[i].Draw();

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
            p.Movement(this->level);
            p.Draw();

            if (p.status == false) {


                Tiempo.Draw();
                int x = 0;

                while (0 < enemigo.size()) {

                    enemigo.pop_back();
                    x++;
                }
                ogreaux = 0;
                x = 0;
                while (0 < bullets.size()) {
                    bullets.pop_back();
                    x++;


                }
                bulletSize = 0;
                x = 0;
                if (Lives.size() > 0) {
                
                    Lives.pop_back();
                
                }
                /* while (x < deadogres) {

                     dead.pop_back();
                     x++;

                 }
                 deadogres = 0;*/
                
                if (p.lives < 0) {
                    
                    
                     
                    
                    
                    
                    
                    int clean = 0;
                    while (clean < dead.size()) {

                        dead.pop_back();
                        clean++;

                    }

                }
                
                
               
            }
            if (Tiempo.tiempo() ==true && p.status == true) {
                ChangeLevel(Tiempo, p, enemigo, bullets, Lives);
            }
            EndDrawing();
        }
		// si el jugador muere o el tiempo se acaba, actualiza el juego, ya sea pasando de nivel o perdiendo la partida
        else {
        
            ClearBackground(BLACK);
            /*BeginDrawing();*/
            BeginDrawing();
            int i = 0;
            Tiempo.Draw();
            if (tiempoFake == false) {

                Tiempo.pause();
                tiempoFake = true;

            }
            
            while (i < dead.size()) {


                dead[i].Draw();
                if (dead[i].Delete() == true) {




                    dead.pop_back();


                }
                /*  float auxiliart = GetTime();*/

                i++;
              


            }
            i = 0;
            p.DeathAnim();
            if (p.status == true && p.lives < 0) {
                GameOver(p);
            }
            if(p.status==true) {
                Tiempo.NewTime();
                p.ResetPlayer();
                tiempoFake = false;
            }
            
           
            EndDrawing();
        
        
        }
		//reinicia los valores si el jugador pierde una vida
        
        // Set background color (framebuffer clear color)
/*  EndDrawing();*/
    }
    void ChangeLevel(time& Tiempo, Player& p, std::vector<Ogre>& enemigo, std::vector<Shoot>& bullets, std::vector <PowerUpLive>& Lives) {
        this->level++;


        tiempoiniciado = false;
        int x = 0;

        while ( enemigo.size()>0) {

            enemigo.pop_back();
           
        }
        
        x = 0;
        while (0 < bullets.size()) {
            bullets.pop_back();
            


        }
        
        x = 0;
        if (Lives.size() > 0) {

            Lives.pop_back();

        }
     





            int clean = 0;
            while (clean < dead.size()) {

                dead.pop_back();
                clean++;

            }

            float esperar = GetTime();
            float auxiliar = 0;

        p.ResetPlayer();
        if (this->level == 7) {

            wonGame = true;

        }
        
    
    
    }
	//cambia de nivel y reinicia los valores
    void GameWon() {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("You Won!", 40, screenHeight / 2, 40, WHITE);
        EndDrawing();
    
    }
    //pantalla de ganaste
    void GameOver(Player&p) {

        
        gameover = true;
        p.lives = 3;
        p.coins = 0;

    }
	//pantalla de perdiste
    void GameOverScreen(Player&p) {
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
    void Drawlevel4() {

        /* BeginDrawing();*/
        int x = 0;
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
        x = 224;
        y = 0;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(desierto1, x, y, WHITE);
            x = x + 32;
        }
        y = 224;
        x = 480;
        for (int i = 0; i < 3; i++)
        {
            DrawTexture(desierto1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto1, 0, 224, WHITE);
        y = 256;
        x = 0;
        for (int i = 0; i < 2; i++)
        {
            DrawTexture(desierto2, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto1, 224, 480, WHITE);
        DrawTexture(desierto2, 256, 480, WHITE);
        DrawTexture(desierto1, 288, 480, WHITE);
        x = 160;
        y = 160;
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
        x = 160;
        y = 352;
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
        x = 160;
        y = 160;
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
        y = 160;
        x = 352;
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
        DrawTexture(desierto4, 224, 64, WHITE);
        DrawTexture(desierto4, 288, 96, WHITE);
        DrawTexture(desierto4, 384, 128, WHITE);
        DrawTexture(desierto4, 96, 192, WHITE);
        DrawTexture(desierto4, 128, 192, WHITE);
        DrawTexture(desierto4, 224, 192, WHITE);
        DrawTexture(desierto4, 288, 192, WHITE);
        DrawTexture(desierto4, 224, 256, WHITE);
        DrawTexture(desierto4, 288, 256, WHITE);
        DrawTexture(desierto4, 288, 288, WHITE);
        DrawTexture(desierto4, 128, 320, WHITE);
        DrawTexture(desierto4, 64, 384, WHITE);
        DrawTexture(desierto4, 160, 384, WHITE);
        DrawTexture(desierto4, 224, 384, WHITE);
    }
    
    void Drawlevel5() {
        int x = 0;
        int y = 0;
        for (int i = 0; i < 8; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto2, 0, 96, WHITE);
        y = y + 32;
        for (int i = 0; i < 6; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(desierto2, x, y, WHITE);
        y = 0;
        for (int i = 0; i < 15; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, 32, y, WHITE);
        DrawTexture(desierto2, 160, y, WHITE);
        DrawTexture(desierto2, 352, y, WHITE);
        y = 480;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(desierto1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto2, 64, y, WHITE);
        DrawTexture(desierto2, 256, y, WHITE);
        x = 320;
        for (int i = 0; i < 3; i++) {
            DrawTexture(desierto2, x, y, WHITE);
            x = x + 32;
        }
        x = 480;
        y = 0;
        for (int i = 0; i < 15; i++) {
            DrawTexture(desierto2, x, y, WHITE);
            y =y + 32;
        }
        DrawTexture(desierto1, x, 96, WHITE);
        DrawTexture(desierto1, x, 160, WHITE);
        DrawTexture(desierto1, x, 192, WHITE);
        DrawTexture(desierto1, x, 288, WHITE);
        DrawTexture(desierto1, x, 352, WHITE);
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
        x = 0;
        y = 256;
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
        x = 160;
        y = 192;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, y, WHITE);
                }

            }
        }
        x = 320;
        y = 192;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol1, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol2, x, y, WHITE);
                }

            }
        }
        DrawTexture(valla, 256, 128, WHITE);
        x = 224;
        y = 384;
        for (int i = 0; i < 3; i++) {
            DrawTexture(valla, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(desierto4, 416, 64, WHITE);
        DrawTexture(desierto4, 128, 96, WHITE);
        DrawTexture(desierto4, 160, 128, WHITE);
        DrawTexture(desierto4, 192, 128, WHITE);
        DrawTexture(desierto4, 320, 128, WHITE);
        DrawTexture(desierto4, 352, 128, WHITE);
        DrawTexture(desierto4, 416, 128, WHITE);
        DrawTexture(desierto4, 192, 288, WHITE);
        DrawTexture(desierto4, 352, 288, WHITE);
        DrawTexture(desierto4, 352, 320, WHITE);
        DrawTexture(desierto4, 96, 352, WHITE);
        DrawTexture(desierto4, 192, 352, WHITE);
        DrawTexture(desierto4, 192, 384, WHITE);
        DrawTexture(desierto4, 352, 416, WHITE);
        DrawTexture(desierto4, 384, 416, WHITE);
    }

    void Drawlevel6(){
        int x = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 0, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 0, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 0, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 0, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 0, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 0, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 480, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 480, WHITE);
                }

            }
            x = x - 32;

        }
        y = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 480, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 480, y, WHITE);
                }

            }
            y = y - 32;
        }
        x = 64;
        y = 64;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(cesped4, x, y, WHITE);
                y = y + 32;
            }
            y = 64;
            x = x + 32;
        }
        y = 32;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        y = 448;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 448;
        y = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(cesped2, 0, 224, WHITE);
        x = 0;
        y = 256;
        for (int i = 0; i < 2; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        x = 224;
        y = 0;
        for (int i = 0; i < 2; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            x = x + 32;
        }
        DrawTexture(cesped2, x, y, WHITE);
        x = 480;
        y = 224;
        for (int i = 0; i < 2; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(cesped2, x, y, WHITE);
        DrawTexture(cesped1, 224, 480, WHITE);
        DrawTexture(cesped2, 256, 480, WHITE);
        DrawTexture(cesped1, 288, 480, WHITE);
        x = 32;
        y = 32;
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
        y = 32;
        x = 64;
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
        y = 96;
        x = 96;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }
        }
        y = 32;
        x = 448;
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
        y = 64;
        x = 448;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 96;
        x = 416;
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
        x = 32;
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
        x = 64;
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
        y = 384;
        x = 96;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 384;
        x = 416;
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
        y = 416;
        x = 448;
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
        y = 416;
        x = 384;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        DrawTexture(flores, 288, 64, WHITE);
        DrawTexture(flores, 256, 128, WHITE);
        DrawTexture(flores, 384, 128, WHITE);
        DrawTexture(flores, 352, 160, WHITE);
        DrawTexture(flores, 416, 160, WHITE);
        DrawTexture(flores, 192, 192, WHITE);
        DrawTexture(flores, 320, 192, WHITE);
        DrawTexture(flores, 192, 224, WHITE);
        DrawTexture(flores, 96, 256, WHITE);
        DrawTexture(flores, 96, 416, WHITE);
        DrawTexture(flores, 192, 416, WHITE);

    }

    void Drawlevel7() {
        int x = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 0, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 0, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 0, WHITE);
                }

            }
            x = x - 32;

        }
        int y = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 0, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 0, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 0, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 0, y, WHITE);
                }

            }
            y = y - 32;

        }
        x = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 480, WHITE);
                }

            }
            x = x + 32;

        }
        x = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, 480, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, 480, WHITE);
                }

            }
            x = x - 32;

        }
        y = 0;
        for (int i = 0; i < 7; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 480, y, WHITE);
                }

            }
            y = y + 32;

        }
        y = 480;
        for (int i = 0; i < 6; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, 480, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, 480, y, WHITE);
                }

            }
            y = y - 32;
        }
        x = 64;
        y = 64;
        for (int i = 0; i < 12; i++)
        {
            for (int i = 0; i < 12; i++) {
                DrawTexture(cesped4, x, y, WHITE);
                y = y + 32;
            }
            y = 64;
            x = x + 32;
        }
        y = 32;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        y = 448;
        x = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            x = x + 32;
        }
        x = 448;
        y = 32;
        for (int i = 0; i < 14; i++) {
            DrawTexture(cesped3, x, y, WHITE);
            y = y + 32;
        }
        x = 224;
        y = 0;
        for (int i = 0; i < 3; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            x = x + 32;
        }
        x = 480;
        y = 224;
        for (int i = 0; i < 3; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        x = 224;
        y = 480;
        for (int i = 0; i < 3; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            x = x + 32;
        }
        x = 0;
        y = 224;
        for (int i = 0; i < 2; i++) {
            DrawTexture(cesped1, x, y, WHITE);
            y = y + 32;
        }
        DrawTexture(cesped2, x, y, WHITE);
        DrawTexture(cesped3, 160, 384, WHITE);
        DrawTexture(cesped3, 128, 160, WHITE);
        y = 96;
        x = 64;
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
        x = 96;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 96;
        x = 352;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 192;
        x = 320;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 288;
        x = 320;
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
        x = 384;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        y = 384;
        x = 384;
        for (int i = 0; i < 1; i++) {
            if (currentTime % 2 == 0) {
                DrawTexture(arbol3, x, y, WHITE);
                int aftertime = GetTime();
                if (aftertime % 2 != 0) {
                    DrawTexture(arbol4, x, y, WHITE);
                }

            }

        }
        DrawTexture(tronco, 320, 256, WHITE);
        DrawTexture(tronco, 160, 288, WHITE);
        DrawTexture(tronco, 96, 384, WHITE);
        DrawTexture(tronco, 320, 384, WHITE);

        DrawTexture(flores, 160, 96, WHITE);
        DrawTexture(flores, 384, 96, WHITE);
        DrawTexture(flores, 256, 128, WHITE);
        DrawTexture(flores, 288, 128, WHITE);
        DrawTexture(flores, 384, 128, WHITE);
        DrawTexture(flores, 288, 160, WHITE);
        DrawTexture(flores, 320, 160, WHITE);
        DrawTexture(flores, 192, 192, WHITE);
        DrawTexture(flores, 192, 224, WHITE);
        DrawTexture(flores, 160, 320, WHITE);
        DrawTexture(flores, 256, 320, WHITE);
        DrawTexture(flores, 320, 320, WHITE);
        DrawTexture(flores, 416, 320, WHITE);
        DrawTexture(flores, 64, 352, WHITE);
        DrawTexture(flores, 160, 352, WHITE);
        DrawTexture(flores, 384, 416, WHITE);
    }
    void Drawlevel8() {

    }

    /* EndDrawing();*/
    void LevelDraw(Game g) {

        if (g.CheckLevel() == 1) {

            Drawlevel1();
        }
        else if (g.CheckLevel()==2) {

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
    friend int main();
    void draw(Player p) {
        DrawTexture(vida, 512, 64, WHITE);
        DrawTexture(moneda1, 512, 96, WHITE);
        DrawTexture(barra, 526, 12, WHITE);
        DrawTexture(reloj, 512, 512, WHITE);
        if (p.lives < 0) {
        
            DrawText("0", 512 + 32, 66, 20, WHITE);
        
        }
        else {
        
        DrawText(TextFormat("%i", p.lives), 512+32, 66, 20, WHITE);
        
        }
        DrawText(TextFormat("%i", p.coins), 512+32, 96, 20, WHITE);
       
    }

};
//classe dedicada a dibujar todo lo relacionado con la UI (vidas, monedas, etc)
class music {

private:
    Music Overworld;
    
    int starts;

public:

    music() {
        Overworld = LoadMusicStream("74.-Journey-Of-The-Prairie-King-_Overworld__1.mp3");;
        starts = 0;
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
    void stopmusic() {
    
        StopMusicStream(Overworld);
        starts = 0;
    }
    //para la musica




};

class Title{

private:
    //cabeza2
    Texture view = LoadTexture("cabeza2.png");
    //IMG_0971
    Texture Chachi = LoadTexture("pene.png");
    bool GameBegin = false;

    int alive = 0;
    float InicialTime = 0;
public:
    friend int main();
    Title() {}

    void Presentation() {
        BeginDrawing();
        ClearBackground(BLACK);
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
        
            DrawTexture(Chachi, screenWidth/2 - 64, screenHeight/2 - 64, WHITE);
        
        }
        else {
        
            DrawTexture(view,0, 0, WHITE);

            if (IsKeyDown(KEY_SPACE)) { GameBegin = true; }
        
        }

        EndDrawing();
    
    }

};





class Store {
private:

    Texture walkFrames[2];  // caminar
    Vector2 position = { 0, 0 };  // Valores temporales

    //imagen tienda
    Texture store = LoadTexture("tienda.png");
    //store man
    Texture storeman1 = LoadTexture("64x64/128x128_p4.png");  //animacion aparicion 1
    Texture storeman2 = LoadTexture("64x64/128x128_p4-1.png"); //animacion aparicion 2
    Texture storeman3 = LoadTexture("64x64/128x128_p4-2.png"); //quieto delante
    Texture storeman4 = LoadTexture("64x64/128x128_p4-3.png"); //quieto izquierda
    Texture storeman5 = LoadTexture("64x64/128x128_p4-4.png"); //quieto derecha

    float animTime = 0;
    const float animSpeed = 0.2f; // Velocidad cambio de frames
    const float walkSpeed = 100.0f; // Píxeles por segundo
    bool isWalking = true;
    int currentFrame = 0;

public:
    friend int main();
 
    //mostrar aparicion del storeman
    void aparicion(float deltaTime) {
        if (!isWalking) return;

        // Animación de caminar
        animTime += deltaTime;
        if (animTime >= animSpeed) {
            animTime = 0;
            currentFrame = (currentFrame + 1) % 2; // Alterna entre 0 y 1
        }

        // Movimiento hacia abajo
        position.y += walkSpeed * deltaTime;

        // Detenerse al llegar al centro 
        if (position.y >= GetScreenHeight() / 2 - walkFrames[0].height / 2) {
            position.y = GetScreenHeight() / 2 - walkFrames[0].height / 2;
            isWalking = false;
            currentFrame = 0; 
        }
    }
    //mostrar la tienda
    void Tienda() 
    {


    }

    void draw() 
    {

        // Dibujar aparicion del storeman
        DrawTexture(walkFrames[currentFrame], position.x, position.y, WHITE);


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

    Store a;

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
    std::vector <Orc>orcs;
    std::vector <Mariposa>marip;
    Title t;
    bool gameovertime = false;
    float GOtime = 0;
    while (!WindowShouldClose()){

        if (t.GameBegin) {
        
            if (!game.gameover) {
                if (!game.wonGame) {

                    player.OverworldPlayer();
                    game.GameStart(p, enemigo, bullets, og, ayxi, dire, ogreaux, bulletaux, ui, auxTime, HelpMeTime, Lives, money, orcs, marip);
                    desierto.LevelDraw(game);
                    ui.DrawInicial();
                    aa.draw(p);
                  
                }
                else {

                    game.GameWon();

                }



            }
            else {
                if (!gameovertime) {
                    GOtime = GetTime();
                
                    gameovertime = true;
                }
                game.GameOverScreen(p);
                player.stopmusic();

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
        
        
        
            t.Presentation();
        }
        

               

            
    }

            CloseAudioDevice();
            CloseWindow();
            return 0;
        

}
//inicia el juego utilizando todas las classes vistas anteriormente
