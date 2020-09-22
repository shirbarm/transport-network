#ifndef STATION_H
#define STATION_H

#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

class Station{
    private:
        string name;
        string vehicle;
        double transitTime;
        double stopTime;
        double wight;
        double dist;
        bool isVisited;
    public:
        Station(){}
        Station(string name, string vehicle, double transitTime, double stopTime, double wight);
        Station(const Station& lhs);
        Station(Station&& rhs);
        Station& operator=(const Station& lhs);
        Station& operator=(Station&& rhs);
        void setName(string name);
        string getName() const;
        void setVehicle(string vehicle);
        string getVehicle() const;
        void setTransitTime(double time);
        double getTransitTime() const;
        void setStopTime(double time);
        double getStopTime() const;
        void setIsVisited(bool visit);
        bool getIsVisited() const;
        void setDist(double dist);
        double getDist() const;
        void setWight(double wight);
        double getWight() const;
        virtual ~Station();
};
#endif