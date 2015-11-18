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
  printer.print(Printer::NameServer,'R',SignedMachine);

  Machines[SignedMachine] = v;
  SignedMachine++;
}

VendingMachine* NameServer::getMachine(unsigned int id) {
  unsigned int curMachine = MtoS[id];
  printer.print(Printer::NameServer,'N', id, MtoS[id]);
  MtoS[id] =(curMachine + 1) % NumVendingMachines;

  return Machines[curMachine];
}

VendingMachine** NameServer::getMachineList() {
  return Machines;
}

void NameServer::main() {
  printer.print(Printer::NameServer,'S');

  	for(;;) {
		_Accept(~NameServer) {
			break;
		} or _When( SignedMachine < NumVendingMachines)_Accept(VMregister) {

		} or _When( SignedMachine >= NumVendingMachines) _Accept(getMachine,getMachineList) {

		} 
	}
	printer.print(Printer::NameServer, 'F');
}




