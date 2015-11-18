#ifndef VendingMachine_H
#define VendingMachine_H
#include <uC++.h>

/*forward declare:
printer, nameserver ,watcard
*/

_Monitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {

    void main();
    Printer& printer;
    NameServer& nameServer;
    unsigned int Id;
    unsigned int SodaCost;
    unsigned int MaxStockPerFlavour;
    unsigned int *Instock;
    bool filling;

  public:
    enum Flavours {Apple,Orange,Peach,Mango,NumFlavour};                 // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();

 
};

#endif // VendingMachine_H