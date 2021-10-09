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
using namespace std;



class MTD {
    public:
        MTD(); //Default Constructor
        Graph g_;
        map<string, Vertex> map;
        /**
         * Constructs a graph from edges.txt and stores output
         * in g_
         */
        void constructGraph();
        /**
         * Prompts user for two verticies, verifies that they exist,
         * and finds the shortest path between them, which is 
         * outputted through standard output.
         */
        void getPath();
        /**
         * Prompts user for 3 verticies, verifies that they exist,
         * and finds the shortest path with a landmark
         * between them, which is  outputted through standard output.
         */
        void getLandmarkPath();
};