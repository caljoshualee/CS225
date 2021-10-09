#include "node.h"

#include <vector>
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

Node::Node(int x, int y, bool IW){
    x_coord = x;
    y_coord = y;
    isWall = IW;
}