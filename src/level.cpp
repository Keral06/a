#include "raylib.h"
#include "resource_dir.h"
#include <vector>


class level {
protected:
    int levels;


public:

    level() {

        levels = 3;

    }

    void LevelUp() {

        levels++;

    }

};