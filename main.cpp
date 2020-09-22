#include <iostream>
#include <ctime>
#include <exception>

#include "MultiGraph.h"
#include "Station.h"
#include "InputFiles.h"

using namespace std;

int main(int argc, char* argv[]){
    InputFiles ipf;
    shared_ptr<MultiGraph> multi;
    try{
        int indexI = ipf.checkOption(argc,argv);
        string outputName = ipf.getOutputName();
        multi = ipf.checkFile(argc,argv,indexI); 
    }catch(InputFiles::notEnoughArguments e){
        cerr << "The file does not has enough argument" << endl;
        exit(EXIT_FAILURE);
    }catch(InputFiles::fileNotOpen e){
        cerr << "The file is not open" << endl;
        exit(EXIT_FAILURE);
    }catch(InputFiles::trackError e){
        cerr << "This car does not exist in our NEVERLAND" << endl;
        exit(EXIT_FAILURE);
    }
    catch(InputFiles::wrongInput e){
        cerr << "The inputs are wrong" << endl;
        exit(EXIT_FAILURE);
    }
    
    string command,line;
    string space = " ";
    string source, destination, fileText;
    int index;
    bool isProper;

    while(true){
        try{
            isProper = true;
            getline(cin,line);
            index = line.find(space);
            if(index==-1){
                command = line;
                isProper = false;
            }
            else{
                command = line.substr(0,index);
                line = line.substr(index+1,line.size());
                index = line.find(space);
            }

            if(command=="load"){
                if(index==-1 && isProper){
                    bool temp = ipf.setLoad(line, multi);
                    if(temp == false){
                        multi->printError();
                    }
                    if(temp == true){
                        multi->printSuccess();
                    }
                }
                else{
                    throw InputFiles::wrongNumberOfArguments();
                }
                cout<<endl; 
            }
            else if(command=="outbound"){
                if(index==-1 && isProper){
                    if(multi->isInGraph(line)){
                        multi->printOutbound(line,"bus");
                        multi->printOutbound(line,"tram");
                        multi->printOutbound(line,"sprinter");
                        multi->printOutbound(line,"rail");
                    }
                    else{
                        cerr<<line<<" does not exist in the current network."<<endl;
                    }
                }
                else{
                    throw InputFiles::wrongNumberOfArguments();
                }
                cout<<endl;
            }
            else if(command=="inbound"){
                if(index==-1 && isProper){
                    if(multi->isInGraphOpposite(line)){
                        multi->printInbound(line,"bus");
                        multi->printInbound(line,"tram");
                        multi->printInbound(line,"sprinter");
                        multi->printInbound(line,"rail");
                    }
                    else{
                        cerr<<line<<" does not exist in the current network."<<endl;
                    }
                }
                else{
                    throw InputFiles::wrongNumberOfArguments();
                }
                cout<<endl;
            }

            else if(command=="uniExpress"){
                if(index!=-1){
                    source = line.substr(0,index);
                    line = line.substr(index+1,line.size());
                    index = line.find(space);
                    if(index==-1){
                        destination = line.substr(0,line.size());
                        if(multi->isInGraph(source) == false){
                            cerr<<source<<" does not exist in the current network."<<endl;
                        }
                        if(multi->isInGraphOpposite(destination) == false){
                            cerr<<destination<<" does not exist in the current network."<<endl;
                        }
                        if(multi->isInGraph(source) && multi->isInGraphOpposite(destination)){
                            destination = line.substr(0,line.size());
                            multi->printUniExpress(source,destination ,"bus");
                            multi->printUniExpress(source,destination,"tram");
                            multi->printUniExpress(source,destination,"sprinter");
                            multi->printUniExpress(source,destination,"rail");
                        }
                    }
                    else{
                        throw InputFiles::wrongNumberOfArguments();
                    }
                }
                else{
                    throw InputFiles::wrongNumberOfArguments();
                }
                cout<<endl;
            }
            else if(command=="multiExpress"){
                if(index!=-1){
                    source = line.substr(0,index);
                    line = line.substr(index+1,line.size());
                    index = line.find(space);
                    if(index==-1){
                        destination = line.substr(0,line.size());
                        if(multi->isInGraph(source) == false){
                            cerr<<source<<" does not exist in the current network."<<endl;
                        }
                        if(multi->isInGraphOpposite(destination) == false){
                            cerr<<destination<<" does not exist in the current network."<<endl;
                        }
                        if(multi->isInGraph(source) && multi->isInGraphOpposite(destination)){
                            multi->printMultiExpress(source,destination);
                        }
                    }
                    else{
                        throw InputFiles::wrongNumberOfArguments();
                    }
                }
                else{
                    throw InputFiles::wrongNumberOfArguments();
                }
                cout<<endl;
            }
            else if(command=="print"){
                if(index==-1 && !isProper){
                    multi->printGraph();
                }
                else{
                    throw InputFiles::wrongNumberOfArguments();
                }
                cout<<endl;
            }
            else if(command=="QUIT"){
                return 0;
            }
            else{
                throw InputFiles::wrongInput();
            }
        }catch(InputFiles::wrongNumberOfArguments e){
            cerr << "Wrong number of arguments! try again" << endl;
    }catch(InputFiles::wrongInput e){
        cerr << "This command not Exist! try again" << endl;
        }
    }
    return 0;
}