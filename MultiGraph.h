#ifndef MULTIGRAPG_H
#define MULTIGRAPG_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include<memory>
#include<queue>
#include<algorithm>
#include<fstream>
#include "Station.h"
using namespace std;

struct Source{
    string name;
    vector<shared_ptr<Station>> destination;
    Source(string from, shared_ptr<Station> to);
    Source(const Source& lhs);
    ~Source(){}
};

class MultiGraph{
    private:
        vector<shared_ptr<Source>> graph; //for question 2
        vector<shared_ptr<Source>> opposite; //for question 3
        shared_ptr<ofstream> outFile;

    public:
        MultiGraph();
        MultiGraph(const MultiGraph& lhs);
        MultiGraph(MultiGraph&& rhs)=default;
        MultiGraph& operator=(const MultiGraph& lhs)=default;
        MultiGraph& operator=(MultiGraph&& rhs)=default;
        bool init(string file);
        void addEdge(string graph1, string graph2, shared_ptr<Station> vertex1, shared_ptr<Station> vertex2);
        void printOutbound(string name, string car);
        void printInbound(string name, string car);
        int findMyIndex(string name) const;
        int findMyIndexOpposite(string name) const;
        void sortByDistance(vector<shared_ptr<Station>>& vec);
        void printUniExpress(string from, string to, string car);
        void printMultiExpress(string from, string to);
        void printGraph()const;
        void printError() const;
        void printSuccess()const;
        bool isInGraph(string source);
        bool isInGraphOpposite(string destination);
        void checkWight(int num, shared_ptr<Station> station, string to, int stopTime, int stopStation, string car);
        virtual ~MultiGraph();
        struct priorityQueue{
            bool operator()(shared_ptr<Station> i, shared_ptr<Station> j){
                return i->getDist() > j->getDist();
            }
        }PriorityQueue;
};
#endif