#include "nameserver.h"
#include "vendingmachine.h"
#include "printer.h"

NameServer::NameServer(Printer &prt,unsigned int numVendingMachines,unsigned int numStudents)
    : printer(prt),
      NumStudents(numStudents),
      NumVendingMachines(numVendingMachines),
      SignedMachine(0) {
  Machines = new VendingMachine*[NumVendingMachines];
  MtoS = new unsigned int[NumStudents];
  for (unsigned int i = 0; i < NumStudents; i++) {
    MtoS[i] = i % NumVendingMachines;
  }
}

NameServer::~NameServer() {
  delete[] Machines;
  delete[] MtoS;
}

void NameServer::VMregister(VendingMachine *v) {
  //print;

  Machines[SignedMachine] = v;
  SignedMachine++;
}

VendingMachine* NameServer::getMachine(unsigned int id) {
  unsigned int curMachine = MtoS[id];
  //mPrinter.print(Printer::NameServer, (char)NewMachine, studentId, machineId);
  //print
  //prepare for next time 
  MtoS[id] =(curMachine + 1) % NumVendingMachines;

  return Machines[curMachine];
}

VendingMachine** NameServer::getMachineList() {
  return Machines;
}

void NameServer::main() {
  //mPrinter.print(Printer::NameServer, Printer::Starting);

  	for(;;) {
		_Accept(~NameServer) {
			break;
		} or _Accept(VMregister, getMachineList) {

		} or _When( SignedMachine >= NumVendingMachines) _Accept(getMachine) {

		} 
	}
	//printer->print(Printer::NameServer, 'F');
}




