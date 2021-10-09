#pragma once

#include <vector>
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

class Node {
    public:
        Node(int x, int y, bool isWall);
        bool isWall;
        int x_coord;
        int y_coord;

};