#include "InputFiles.h"

InputFiles::InputFiles(){
    multigraph = make_shared<MultiGraph>();
    bus = 1;
    tram = 2;
    sprinter = 3;
    rail = 5;
    intercity = 15;
    centraal = 10;
    stad = 5;
    outputName = "";
}

int InputFiles::checkOption(int argc, char* argv[]){
    int existI = 0;
    int existC = 0;
    int existO = 0;
    bool initProper;
    if(argc < 2){
        throw notEnoughArguments();
    }
    for(int i=0; i<argc;i++){
        string found = argv[i];
        if(found=="-i"){
            existI=i;
        }
        else if(found=="-c"){
            existC=i;
        }
        if(found=="-o"){
            existO=i;
        }
    }

    if(existO!=0){
        if(argv[existO+1] != NULL){
            string openFile = argv[existO+1];
            initProper = multigraph->init(openFile);
            if(!initProper){
                throw fileNotOpen();
            }
            outputName = openFile;
        }
        else{
            throw notEnoughArguments();
        }
    }
    else{
        initProper = multigraph->init("output.dat");
        if(!initProper){
            throw fileNotOpen();
        }
        outputName = "output.dat";
    }
    if(existC != 0){
        if(argv[existC+1] != NULL){
            ifstream config;
            config.open(argv[existC+1]);
            if(!config.is_open()){
                throw fileNotOpen();
            }
            string space = " ";
            double number;
            int indexSpace;
            string line,tempString,num,toChange;
            while(getline(config,line)){
                indexSpace = line.find(space);
                tempString = line.substr(0,indexSpace);
                num = line.substr(indexSpace+1,line.size());
                stringstream ss(num);
                ss>>number;
                toChange = checkString(number,tempString);
                if(toChange == "error"){
                    throw trackError();
                }
            }
            config.close();
        }
    }
    if(existI == 0){
        throw notEnoughArguments();
    }
    return existI;
}

shared_ptr<MultiGraph> InputFiles::checkFile(int argc, char* argv[],int index){
    ifstream openFile;
    string fileName,found;
    for(int i=index+1; i<argc;i++){
        found = argv[i];
        if(found=="-c" || found=="-o"){
            break;
        }
        fileName = argv[i];
        string kind = checkKindOfTrack(fileName);
        if(kind=="error"){
            throw trackError();
        }

        openFile.open(argv[i]);
        if(!openFile.is_open()){
            throw fileNotOpen();
        }
        string line;
        string tab = "\t";
        string source, destination, length;
        string prefix1="IC",prefix2="CS";
        double weight, kindDestination;
        int indexInLine;
        double stopTime = getStopTime(kind);
        while(getline(openFile,line)){
            indexInLine = line.find(tab);
            source = line.substr(0,indexInLine);
            line = line.substr(indexInLine+1,line.size());
            indexInLine = line.find(tab);
            destination = line.substr(0,indexInLine);
            length = line.substr(indexInLine+1,line.size());
            stringstream ss(length);
            ss>>weight;
            if(weight <= 0){
                throw wrongInput();
            }
            if(destination.at(0)=='I' && destination.at(1)=='C'){
                kindDestination = intercity;
            }
            
            else if(destination.at(0)=='C' && destination.at(1)=='S'){
                kindDestination = centraal;
            }
            else{
                kindDestination = stad;
            }

            buildVertex(source,destination,weight,kindDestination,stopTime,kind);
        }
        openFile.close();
    }
    return multigraph;
}

bool InputFiles::setLoad(string nameFile, shared_ptr<MultiGraph> multi){
    ifstream openFile;
    string kind = checkKindOfTrack(nameFile);
    if(kind=="error"){
        return false;
    }
    openFile.open(nameFile.c_str());
    if(!openFile.is_open()){
        return false;
    }
    string line;
    string tab = "\t";
    string source, destination, length;
    string prefix1="IC",prefix2="CS";
    double weight, kindDestination;
    int indexInLine;
    double stopTime = getStopTime(kind);
    while(getline(openFile,line)){
        indexInLine = line.find(tab);
        source = line.substr(0,indexInLine);
        line = line.substr(indexInLine+1,line.size());
        indexInLine = line.find(tab);
        destination = line.substr(0,indexInLine);
        length = line.substr(indexInLine+1,line.size());
        stringstream ss(length);
        ss>>weight;
        if(weight <= 0){
            return false;
        }
        if(destination.at(0)=='I' && destination.at(1)=='C'){
            kindDestination = intercity;
        }
        
        else if(destination.at(0)=='C' && destination.at(1)=='S'){
            kindDestination = centraal;
        }
        else{
            kindDestination = stad;
        }
        shared_ptr<Station> s1 = make_shared<Station>(source,kind,kindDestination,stopTime,weight);
        shared_ptr<Station> s2 = make_shared<Station>(destination,kind,kindDestination,stopTime,weight);
        multi->addEdge(source,destination,s2,s1);
    }
    openFile.close();
    return true;
}

void InputFiles::buildVertex(string source,string destination,double weight,double stopStation,double stopTime,string car){
    shared_ptr<Station> s1 = make_shared<Station>(source,car,stopStation,stopTime,weight);
    shared_ptr<Station> s2 = make_shared<Station>(destination,car,stopStation,stopTime,weight);
    multigraph->addEdge(source,destination,s2,s1);
}
 
string InputFiles::checkKindOfTrack(string track){
    if(track.at(0) == 'b'){
        track = track.substr(0,3);
        if(track=="bus"){
            return "bus";
        }
    }
    else if(track.at(0) == 't'){
        track = track.substr(0,4);
        if(track=="tram"){
            return "tram";
        }
    }
    else if(track.at(0) == 's'){
        track = track.substr(0,8);
        if(track=="sprinter"){
            return "sprinter";
        }
    }
    else if(track.at(0) == 'r'){
        track = track.substr(0,4);
        if(track=="rail"){
            return "rail";
        }
    }
    return "error";
}

double InputFiles::getStopTime(string track) const{
    if(track=="bus"){
        return bus;
    }
    if(track=="tram"){
        return tram;
    }
    if(track=="sprinter"){
        return sprinter;
    }
    if(track=="rail"){
        return rail;
    }
    return -1;
}

string InputFiles::checkString(double number, string name){
    if(number < 0 || name.size() > 32){
        return "error";
    }
    if(name=="bus"){
        bus = number;
        return "goodInput";
    }
    if(name=="tram"){
        tram = number;
        return "goodInput";
    }
    if(name=="sprinter"){
        sprinter = number;
        return "goodInput";
    }
    if(name=="rail"){
        rail = number;
        return "goodInput";
    }
    if(name=="intercity"){
        intercity = number;
        return "goodInput";
    }
    if(name=="centraal"){
        centraal = number;
        return "goodInput";
    }
    if(name=="stad"){
        stad = number;
        return "goodInput";
    }
    return "error";
}

string InputFiles::getOutputName() const{
    return outputName;
}