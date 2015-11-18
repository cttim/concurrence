#include <uC++.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watcardoffice.h"
#include "nameserver.h"
#include "vendingmachine.h"
#include "bottlingplant.h"
#include "student.h"
#include "MPRNG.h"

using namespace std;

void usage(char **argv) {
    cerr << "Usage: " << argv[0] << " [ config-file [ random-seed (> 0) ] ]"
    << endl;
    exit(EXIT_FAILURE);
}

int convert(char *argv){
  int a;
  stringstream ss(argv);
  ss>>a;
  if(ss.fail()){
    return -1;
  }
  else{
    return a;
  }
}


void uMain::main(){
  string file = "soda.config";

  int seed = getpid();
  if(argc > 1){
    file = string(argv[1]);
  }

  if(argc > 2){
    seed = convert(argv[2]);
    if(seed < 0){
      usage(argv);
    }
  }
    if(argc > 3){
        usage(argv);
    }
    
    ConfigParms cmp;
    
    processConfigFile(file.c_str(), cmp);
    
    Printer prt(cmp.numStudents, cmp.numVendingMachines, cmp.numCouriers);
    
    Bank bank(cmp.numStudents);
    
    Parent parent(prt, bank, cmp.numStudents, cmp.parentalDelay);
    
    WATCardOffice office(prt, bank, cmp.numCouriers);
    
    NameServer nameserver(prt, cmp.numVendingMachines, cmp.numStudents);
    
    VendingMachine *machine[cmp.numVendingMachines];
    
    //cout<<"start bottle"<<endl;
    BottlingPlant *bottleplant = new BottlingPlant(prt, nameserver, cmp.numVendingMachines, cmp.maxShippedPerFlavour, cmp.maxStockPerFlavour, cmp.timeBetweenShipments);
    //cout<<"end bottle"<<endl;
    Student *student[cmp.numStudents];
    
    //unsigned int id;
    
    for(unsigned int i=0; i<cmp.numVendingMachines; i++){
        machine[i] = new VendingMachine(prt, nameserver, i, cmp.sodaCost, cmp.maxStockPerFlavour);
    }
    
    for(unsigned int j=0; j<cmp.numStudents; j++){
        student[j] = new Student(prt, nameserver, office, j, cmp.maxPurchases);
    }
    
    for(unsigned int k=0; k<cmp.numStudents; k++){
        delete student[k];
    }
    
    delete bottleplant;
    
    for(unsigned int l=0; l<cmp.numVendingMachines; l++){
        delete machine[l];
    }
    
}
