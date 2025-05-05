#include "raylib.h"
#include "resource_dir.h"
#include <vector>
#include "level.cpp"

class Stage : public level {

protected:
    int stage;
public:



    Stage() : level() {

        stage = 3;

    }
    void StageUp() {

        stage++;

    }

    int CheckStage() {

        return stage;

    }



};