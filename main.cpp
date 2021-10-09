#include <iostream>
#include <vector>
#include <fstream>
#include "cs225/PNG.h"
#include "node.h"
#include "graph.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <map>
#include <cmath>
#include <math.h>
#include "mtd.h"


using cs225::HSLAPixel;
using cs225::PNG;
using namespace std;


int main(){

    MTD mtd;
    mtd.constructGraph();

    string p; int s;
    cout << "Type 1 for Shortest Path, 2 for Landmark Path" << endl;
    getline(std::cin, p);
    s = stoi(p);
    if(s == 1) mtd.getPath();
    if(s == 2) mtd.getLandmarkPath();
    return 0;
}


