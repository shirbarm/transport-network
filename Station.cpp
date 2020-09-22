#include "Station.h"

Station::Station(string name, string vehicle, double transitTime, double stopTime, double wight){
    this->name = {name};
    this->vehicle = {vehicle};
    this->transitTime = {transitTime};
    this->stopTime = {stopTime};
    this->wight = {wight};
    isVisited = {false};
    dist = {-1};
}

Station::Station(const Station& lhs){
    this->name = {lhs.name};
    this->vehicle = {lhs.vehicle};
    this->transitTime = {lhs.transitTime};
    this->stopTime = {lhs.stopTime};
    this->wight = {lhs.wight};
    isVisited = {lhs.isVisited};
    dist = {lhs.dist};
}

Station::Station(Station&& rhs){
    this->name = {rhs.name};
    this->vehicle = {rhs.vehicle};
    this->transitTime = {rhs.transitTime};
    this->stopTime = {rhs.stopTime};
    this->wight = {rhs.wight};
    isVisited = {rhs.isVisited};
    dist = {rhs.dist};

    rhs.name={""};
    rhs.vehicle={""};
    rhs.transitTime={-1};
    rhs.stopTime={-1};
    rhs.wight={-1};
    rhs.isVisited={false};
    rhs.dist={-1};
}

Station& Station::operator=(const Station& lhs){
    if(this == &lhs){
        return *this;
    }
    this->name = {lhs.name};
    this->vehicle = {lhs.vehicle};
    this->transitTime = {lhs.transitTime};
    this->stopTime = {lhs.stopTime};
    this->wight = {lhs.wight};
    isVisited = {lhs.isVisited};
    dist = {lhs.dist};
    return *this;
}

Station& Station::operator=(Station&& rhs){
    swap(name,rhs.name);
    swap(vehicle,rhs.vehicle);
    swap(transitTime,rhs.transitTime);
    swap(stopTime,rhs.stopTime);
    swap(wight,rhs.wight);
    swap(isVisited,rhs.isVisited);
    swap(dist,rhs.dist);
    return *this;
}

void Station::setName(string name){
    this->name = name;
}

string Station::getName() const{
    return name;
}

void Station::setVehicle(string vehicle){
    this->vehicle = vehicle;
}

string Station::getVehicle() const{
    return vehicle;
}

void Station::setTransitTime(double time){
    transitTime = time;
}

double Station::getTransitTime() const{
    return transitTime;
}

void Station::setStopTime(double time){
    stopTime = time;
}

double Station::getStopTime() const{
    return stopTime;
}

void Station::setIsVisited(bool visit){
    isVisited = visit;
}

bool Station::getIsVisited() const{
    return isVisited;
}

void Station::setDist(double dist){
    this->dist = dist;
}

double Station::getDist() const{
    return dist;
}

void Station::setWight(double wight){
    this->wight = wight;
}

double Station::getWight() const{
    return wight;
}

Station::~Station(){}