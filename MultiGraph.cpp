#include "MultiGraph.h"

Source::Source(string from, shared_ptr<Station> to){
    name = {from};
    shared_ptr<Station> s = to;
    destination.push_back(s);
}

Source::Source(const Source& lhs){
    this->name = lhs.name;
    this->destination= lhs.destination;
}

MultiGraph::MultiGraph(){}

MultiGraph::MultiGraph(const MultiGraph& lhs){
    this->graph = lhs.graph;
    this->opposite = lhs.opposite;
    this->outFile = lhs.outFile;
}

MultiGraph::~MultiGraph(){
    outFile->close();
}

bool MultiGraph::init(string file){
    outFile = make_shared<ofstream>();
    outFile->open(file.c_str());
    if(!outFile->is_open()){
        return false; 
    }
    return true; 
}

void MultiGraph::printError() const{
    cerr<<"ERROR opening the specified file"<<endl;
}

void MultiGraph::printSuccess()const{
    cout<<"Update was successful"<<endl;
}

void MultiGraph::addEdge(string graph1, string graph2, shared_ptr<Station> vertex1, shared_ptr<Station> vertex2){
    int size1 = graph.size();
    int flag = 0;
    for(int i = 0; i < size1; i++){
        if(graph.at(i)->name == graph1){
            int size2 = graph.at(i)->destination.size();
            for(int j = 0; j < size2; j++){ 
                if(graph.at(i)->destination.at(j)->getName() == graph2 && graph.at(i)->destination.at(j)->getVehicle() == vertex1->getVehicle()){ /* if the sourse and the destination is already in the graph */
                    if(graph.at(i)->destination.at(j)->getWight() > vertex1->getWight()){
                        graph.at(i)->destination.at(j)->setWight(vertex1->getWight());
                    }
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){ /* if this sourse is already in the graph but no destination */
                graph.at(i)->destination.push_back(vertex1);
                flag = 1;
            }
        }
    }
    if(flag == 0){ /* if the sourse and the destination no in the grapg */
        shared_ptr<Source> source = make_shared<Source>(graph1, vertex1);
        graph.push_back(source);
    }
    size1 = opposite.size();
    flag = 0;
    for(int i = 0; i < size1; i++){
        if(opposite.at(i)->name == graph2){
            int size2 = opposite.at(i)->destination.size();
            for(int j = 0; j < size2; j++){ 
                if(opposite.at(i)->destination.at(j)->getName() == graph1 && opposite.at(i)->destination.at(j)->getVehicle() == vertex2->getVehicle()){ /* if the sourse and the destination is already in the graph */
                    if(opposite.at(i)->destination.at(j)->getWight() > vertex2->getWight()){
                        opposite.at(i)->destination.at(j)->setWight(vertex2->getWight());
                    }
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){ /* if this sourse is already in the graph but no destination */
                opposite.at(i)->destination.push_back(vertex2);
                flag = 1;
            }
        }
    }
    if(flag == 0){ /* if the sourse and the destination no in the grapg */
        shared_ptr<Source> source = make_shared<Source>(graph2, vertex2);
        opposite.push_back(source);
    }
}

int MultiGraph::findMyIndex(string name) const{
    int size = graph.size();
    for(int i = 0; i < size; i++){
        
        if(name == graph.at(i)->name){
           return i;
        }
    }
    return -1;
}

int MultiGraph::findMyIndexOpposite(string name) const{
    int size = opposite.size();
    for(int i = 0; i < size; i++){
        if(name == opposite.at(i)->name){
           return i;
        }
    }
    return -1;
}

void MultiGraph::printOutbound(string name, string car){
    cout<<car<<": ";
    queue<shared_ptr<Station>> qu;  
    int indexInVec = findMyIndex(name);
    if(name == graph.at(indexInVec)->name){
        int size2 =  graph.at(indexInVec)->destination.size();
        for(int j = 0; j < size2; j++){
            if(graph.at(indexInVec)->destination.at(j)->getVehicle() == car){
                qu.push(graph.at(indexInVec)->destination.at(j));
                graph.at(indexInVec)->destination.at(j)->setIsVisited(true);
            }
        }
        if(qu.empty()){
           cout<<"no outbound travel"<<endl;
            return;
        }
    }
    while(!qu.empty()){
        string top = qu.front()->getName();
        if(qu.front()->getIsVisited()){
            indexInVec = findMyIndex(top);
            if(indexInVec != -1){
                int size2 =  graph.at(indexInVec)->destination.size();
                for(int j = 0; j < size2; j++){
                    if(graph.at(indexInVec)->destination.at(j)->getVehicle() == car){
                        if(!graph.at(indexInVec)->destination.at(j)->getIsVisited()){
                            if(graph.at(indexInVec)->destination.at(j)->getName() != name){
                                qu.push(graph.at(indexInVec)->destination.at(j));
                                graph.at(indexInVec)->destination.at(j)->setIsVisited(true);
                            }
                        }
                    }
                }
            }
        }
        cout << qu.front()->getName() << "\t";
        qu.pop();
    }
    int size = graph.size();
    for(int i = 0; i < size; i++){
        int size2 =  graph.at(i)->destination.size();
        for(int j = 0; j < size2; j++){
            graph.at(i)->destination.at(j)->setIsVisited(false);
        }
    }
    cout<<endl;
}

void MultiGraph::printInbound(string name, string car){
    cout<<car<<": ";
    queue<shared_ptr<Station>> qu;  
    int indexInVec = findMyIndexOpposite(name);
    if(name == opposite.at(indexInVec)->name){
        int size2 =  opposite.at(indexInVec)->destination.size();
        for(int j = 0; j < size2; j++){
            if(opposite.at(indexInVec)->destination.at(j)->getVehicle() == car){
                qu.push(opposite.at(indexInVec)->destination.at(j));
                opposite.at(indexInVec)->destination.at(j)->setIsVisited(true);
            }
        }
        if(qu.empty()){
            cout<<"no inbound travel"<<endl;
            return;
        }
    }
    while(!qu.empty()){
        string top = qu.front()->getName();
        if(qu.front()->getIsVisited()){
            indexInVec = findMyIndexOpposite(top);
            if(indexInVec != -1){
                int size2 =  opposite.at(indexInVec)->destination.size();
                for(int j = 0; j < size2; j++){
                    if(opposite.at(indexInVec)->destination.at(j)->getVehicle() == car){
                        if(!opposite.at(indexInVec)->destination.at(j)->getIsVisited()){
                            if(opposite.at(indexInVec)->destination.at(j)->getName() != name){
                                qu.push(opposite.at(indexInVec)->destination.at(j));
                                opposite.at(indexInVec)->destination.at(j)->setIsVisited(true);
                            }
                        }
                    }
                }
            }
        }
        cout << qu.front()->getName() << "\t";

        qu.pop();
    }
    int size = opposite.size();
    for(int i = 0; i < size; i++){
        int size2 =  opposite.at(i)->destination.size();
        for(int j = 0; j < size2; j++){
            opposite.at(i)->destination.at(j)->setIsVisited(false);
        }
    }
    cout<<endl;
}

void MultiGraph::sortByDistance(vector<shared_ptr<Station>>& vec){
    sort(vec.begin(), vec.end(), PriorityQueue);
}

void MultiGraph::printUniExpress(string from, string to, string car){
    int index = findMyIndex(from);
    vector<shared_ptr<Station>> vec;
    int size = graph.at(index)->destination.size();
    cout<<car<<": ";
    for(int i = 0; i < size; i++){
        if(graph.at(index)->destination.at(i)->getVehicle() == car){
            if(graph.at(index)->destination.at(i)->getName() == to){
                graph.at(index)->destination.at(i)->setDist(graph.at(index)->destination.at(i)->getWight());
            }
            else{
                graph.at(index)->destination.at(i)->setDist(graph.at(index)->destination.at(i)->getWight());
                vec.push_back(graph.at(index)->destination.at(i));
            }
            
        }
    }
    sortByDistance(vec);
    while(!vec.empty()){
        int indexVex = findMyIndex(vec.at(vec.size()-1)->getName());
        int distance = vec.at(vec.size()-1)->getDist();
        vec.pop_back();
        if(indexVex != -1){
            int size = graph.at(indexVex)->destination.size();
            for(int i = 0; i < size; i++){
                if(graph.at(indexVex)->destination.at(i)->getVehicle() == car){
                    if((graph.at(indexVex)->destination.at(i)->getDist())==-1 || (graph.at(indexVex)->destination.at(i)->getDist()) > (distance+graph.at(indexVex)->destination.at(i)->getWight())){
                        if(graph.at(indexVex)->destination.at(i)->getName() == to){
                            graph.at(indexVex)->destination.at(i)->setDist(distance+graph.at(indexVex)->destination.at(i)->getWight()+graph.at(indexVex)->destination.at(i)->getStopTime());
                        }
                        else{
                            graph.at(indexVex)->destination.at(i)->setDist((distance+graph.at(indexVex)->destination.at(i)->getWight()+graph.at(indexVex)->destination.at(i)->getStopTime()));
                            vec.push_back(graph.at(indexVex)->destination.at(i));
                        }
                    }
                }
            }
        }
        if(!vec.empty()){
            sortByDistance(vec);
        }
    }
    int minTrail = 0;
    size = graph.size();
    for(int i = 0; i < size; i++){
        int size2 =  graph.at(i)->destination.size();
        for(int j = 0; j < size2; j++){
            if(graph.at(i)->destination.at(j)->getName() == to && (graph.at(i)->destination.at(j)->getDist() != -1)){
                if(minTrail == 0 || (graph.at(i)->destination.at(j)->getDist() < minTrail)){
                    minTrail = graph.at(i)->destination.at(j)->getDist();
                }
            }
            graph.at(i)->destination.at(j)->setDist(-1);
        }
    }
    if(minTrail == 0){
        cout<<"route unavailable"<<endl;
    }else{
        cout<<minTrail<<endl;
    }
}

void MultiGraph::printMultiExpress(string from, string to){
    int indexG = findMyIndex(from);
    vector<shared_ptr<Station>> vec;
    int size = graph.at(indexG)->destination.size();
    for(int i = 0; i < size; i++){
        graph.at(indexG)->destination.at(i)->setDist(graph.at(indexG)->destination.at(i)->getWight());
        if(graph.at(indexG)->destination.at(i)->getName() != to){
            vec.push_back(graph.at(indexG)->destination.at(i));
        }
    }
    sortByDistance(vec);
    while(!vec.empty()){
        int indexVex = findMyIndex(vec.at(vec.size()-1)->getName());
        string car = vec.at(vec.size()-1)->getVehicle();
        string name = vec.at(vec.size()-1)->getName();
        int stopTime = vec.at(vec.size()-1)->getStopTime();
        int stopStation = vec.at(vec.size()-1)->getTransitTime();
        int distance = vec.at(vec.size()-1)->getDist();
        vec.at(vec.size()-1)->setIsVisited(true);
        vec.pop_back();
        if(indexVex != -1){
            int sizeVec = graph.at(indexVex)->destination.size();
            for(int j = 0; j < sizeVec; j++){
                checkWight(distance, graph.at(indexVex)->destination.at(j), to, stopTime, stopStation, car);
                if(graph.at(indexVex)->destination.at(j)->getName() != to && graph.at(indexVex)->destination.at(j)->getName() != from){
                    if(graph.at(indexVex)->destination.at(j)->getName() != name){
                        if(graph.at(indexVex)->destination.at(j)->getIsVisited()==false){
                            vec.push_back(graph.at(indexVex)->destination.at(j));
                            
                        }
                        
                    } 
                }
            }
        }
        if(!vec.empty()){
            sortByDistance(vec); 
        }
    }
    int minTrail = 0;
    int sizeGraph = graph.size();
    for(int k = 0; k < sizeGraph; k++){
        int sizeStation = graph.at(k)->destination.size();
        for(int m = 0; m < sizeStation; m++){
            if(graph.at(k)->destination.at(m)->getName() == to){
                if(graph.at(k)->destination.at(m)->getDist() != -1){
                    if(graph.at(k)->destination.at(m)->getDist() < minTrail || minTrail == 0){
                        minTrail = graph.at(k)->destination.at(m)->getDist();
                    }
                }
            }
            graph.at(k)->destination.at(m)->setDist(-1);
        }
    }
    if(minTrail == 0){
        cout<<"route unavailable"<<endl;
    }else{
        cout<<"the shortest trail is: "<<minTrail<<endl;
    }
}

void MultiGraph::checkWight(int num, shared_ptr<Station> station, string to, int stopTime, int stopStation, string car){
    if(station->getName() == to){
        if(station->getVehicle() == car){
            if((num+station->getWight()+stopTime < station->getDist()) || (station->getDist() == -1)){
                station->setDist(num+station->getWight()+stopTime);
                return;
            }
            else{
                return;
            } 
        if((num+station->getWight()+stopStation < station->getDist()) || (station->getDist() == -1)){
                station->setDist(num+station->getWight()+stopStation);
                return;
            }
            else{
                return;
            } 
        }
    }
    if(station->getVehicle() == car){
        if(((num+station->getWight()+station->getStopTime()) < station->getDist()) || (station->getDist() == -1)){
            station->setDist(num+station->getWight()+station->getStopTime());
            return;
        }
        else{ 
            return;
        }
    }
    if(((num+station->getWight()+station->getTransitTime()) < station->getDist()) || (station->getDist() == -1)){
        station->setDist(num+station->getWight()+station->getTransitTime());
        return;
    }
    else{
        return;
    }
}

void MultiGraph::printGraph()const{
    int size = graph.size();
    for(int i = 0; i < size; i++){
        *outFile<<endl;
        *outFile<<"from: "<<graph.at(i)->name<<endl;
        int size2 =  graph.at(i)->destination.size();
        for(int j = 0; j < size2; j++){
            *outFile<<graph.at(i)->destination.at(j)->getVehicle()<<": "<<graph.at(i)->destination.at(j)->getName()<<endl;;
        }
        *outFile<<"_______________________"<<endl;
    }
}

bool MultiGraph::isInGraph(string source){
    int index = findMyIndex(source);
    if(index!=-1){
        return true;
    }
    return false;
}

bool MultiGraph::isInGraphOpposite(string destination){
    int index = findMyIndexOpposite(destination);
    if(index!=-1){
        return true;
    }
    return false;
}