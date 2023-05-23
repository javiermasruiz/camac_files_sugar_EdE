
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include "TStopwatch.h"
#include "macro.h"

//  Los runs deben llamarse todos run000.txt y así sucesivamente para que 
//  funcione el programa.


void histo_generator();
void convert2simnra();


void macro(){  

   TStopwatch t;

   histo_generator();
   convert2simnra();

   t.Print();
}





