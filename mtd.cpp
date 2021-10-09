#include <iostream>
#include <vector>
#include <fstream>
#include "cs225/PNG.h"
#include "mtd.h"
#include "graph.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <map>
#include <cmath>
#include <math.h>

using namespace std;

//Default constructor, initializes graph to be weighted, undirected.
MTD::MTD() : g_(true, false){
}

//Used for calculating weights based on lat/long
#define earthRadiusM 6371000.0

//Converts degrees to radians
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

//Converts radians back to degrees
double rad2deg(double rad) {
  return (rad * 180 / M_PI);
}

/**
 * haversine forumla in meters, used to calculate weights based on
 * distance between stops.
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusM * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//Initial construction of graph.
void MTD::constructGraph(){
    //Opens text file
    std::ifstream file("edges.txt");
    std::string str; 
    int num = 0;
    //Reads text file line by line; starting with the second line.
    while (std::getline(file, str)){
        if(num == 0 ) {num++;continue;}
        num++;
        string delimiter = ","; //Delimits by comma, set up in csv

        //pulls start
        string source_id = str.substr(0, str.find(delimiter));
        str.erase(0, str.find(delimiter) + delimiter.length());

        //pulls start latitude
        double source_lat = stod(str.substr(0, str.find(delimiter)));
        str.erase(0, str.find(delimiter) + delimiter.length());

        //pulls start longitude
        double source_long = stod(str.substr(0, str.find(delimiter)));
        str.erase(0, str.find(delimiter) + delimiter.length());

        //pulls destination
        string dest_id = str.substr(0, str.find(delimiter));
        str.erase(0, str.find(delimiter) + delimiter.length());

        //pulls destination latitude
        double dest_lat = stod(str.substr(0, str.find(delimiter)));
        str.erase(0, str.find(delimiter) + delimiter.length());
        
        //pulls destination logitude
        double dest_long = stod(str.substr(0, str.find(delimiter)));
        str.erase(0, str.find(delimiter) + delimiter.length());
        
        //remaining string is the route #
        string route = str;

        Vertex start, end;
        //Checks if start vertex exists
        if(map.find(source_id) != map.end()){
            start = map[source_id];
        }else{
            start = source_id;
            map[source_id] = start;
            g_.insertVertex(start);//adds if new vertex
        }
        //checks if destination vertex exists
        if(map.find(dest_id) != map.end()){
            end = map[dest_id];
        }else{
            end = dest_id;
            map[dest_id] = end;
            g_.insertVertex(end);//adds if new vertex
        }
        
        //Calculates distance between two points for weight
        double d = distanceEarth(source_lat, source_long, dest_lat, dest_long);
      
        //Inserts edge between 2 points and sets weight, label.
        g_.insertEdge(start, end);
        g_.setEdgeWeight(start, end, d);
        g_.setEdgeLabel(start, end, route);
     
    }

}

//Prompts user for stops and finds shortest path between them.
void MTD::getPath(){
    Vertex start, end;
    
    //i/o for source/destination
    cout << "Enter Starting Point: ";
    std::getline(std::cin, start);
    cout << "Enter Ending Point: ";
    std::getline(std::cin, end);
    
    //Checks if these inputs are valid stops
    if(map.find(start) == map.end() || map.find(end) == map.end()){
        cout << "Invalid Stops" << endl;
        return;
    }
    //Gets list of visited nodes in shortest path
    vector<Vertex> nodes = g_.shortestPath(start, end);
    cout << "" << endl;

    //Checks if no edges are present
    if(nodes.size() == 0 || nodes.size() == 1) {cout << "No such route exists" << endl; return;}

    //Outputs visualization of path a user must take to go between points
    for(unsigned j = 0; j < nodes.size()-1; j++){
        Edge e = g_.getEdge(nodes[j], nodes[j+1]);
        cout << "Take the " << e.getLabel() << " from " << e.source << " to " << e.dest << endl;
    }
    
}

void MTD::getLandmarkPath(){
    Vertex start, middle,  end;
    
    //i/o for source/destination
    cout << "Enter Starting Point: ";
    std::getline(std::cin, start);
    cout << "Enter Landmark: ";
    std::getline(std::cin, middle);
    cout << "Enter Ending Point: ";
    std::getline(std::cin, end);

    //Checks if these inputs are valid stops
    if(map.find(start) == map.end() || map.find(end) == map.end() || map.find(middle) == map.end()){
        cout << "Invalid Stops" << endl;
        return;
    }

    //Gets list of visited nodes in shortest path + landmark stop
    vector<Vertex> nodes = g_.landmarkPath(start, middle, end);
    cout << "" << endl;

    //Checks if no edges are present
    if(nodes.size() == 0 || nodes.size() == 1) {cout << "No such route exists" << endl; return;}

    //Outputs visualization of path a user must take to go between points
    for(unsigned j = 0; j < nodes.size()-1; j++){
        Edge e = g_.getEdge(nodes[j], nodes[j+1]);
        if(nodes[j] == middle){
            cout << "Take the " << e.getLabel() << " from *" << e.source << "* to " << e.dest << endl;
        } else if(nodes[j+1] == middle){
            cout << "Take the " << e.getLabel() << " from " << e.source << " to *" << e.dest << "*" <<  endl;
        }else cout << "Take the " << e.getLabel() << " from " << e.source << " to " << e.dest << endl;
    }

}