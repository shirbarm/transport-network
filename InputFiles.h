#ifndef InputFiles_H
#define InputFiles_H

#include<iostream>
#include<fstream>
#include<sstream>

#include "MultiGraph.h"
#include "Station.h"

using namespace std;
/*operator = ,copy c'tor and move semantic no need*/        
class InputFiles{
    private:
        double bus;
        double tram;
        double sprinter;
        double rail;
        double intercity;
        double centraal;
        double stad;
        string outputName;
        shared_ptr<MultiGraph> multigraph;
        
    public:
        InputFiles();
        int checkOption(int argc, char* argv[]);
        shared_ptr<MultiGraph> checkFile(int argc, char* argv[], int index);
        string checkString(double number, string name);
        string checkKindOfTrack(string track);
        double getStopTime(string track) const;
        bool setLoad(string nameFile, shared_ptr<MultiGraph> multi);
        void buildVertex(string source,string destination,double weight,double stopStation,double stopTime,string car);
        string getOutputName() const;
        virtual ~InputFiles(){}

    class fileNotOpen{};
    class fileNotExist{};
    class trackError{};
    class trackNotProper{};
    class notEnoughArguments{};
    class wrongInput{};
    class wrongNumberOfArguments{};
};


#endif