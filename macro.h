#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include "TSystem.h"
#include "TStopwatch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// El programa se debe modificar en función del número de archivos de entrada 
// y en dependencia del número de detectores que se ocupen
// Para preprocesar los row data utilizar $cat data1.txt | cut -f1,2 > run000.txt
using namespace std;

Int_t run = 3;   // Editar el numero de runs
Int_t  no_detector = 2; // editar el numero de detectores/columnas del archivo

void histo_generator(){

   Int_t entries, no_columna;
   Double_t valor;
   string linea;
   
   for (Int_t i = 1; i <= no_detector; i++){

      TFile *output = new TFile(Form("uncalib%d.root",i),"recreate");

      for(Int_t ii = 0; ii < run; ii++){
         //cout <<"i: "<<i<<endl; // checking
         TH1F *histo = new TH1F(Form("hist%d_%d",ii,i),"Histograms",4096,0,4096);
         //cout << "NOmbre histograma: " << histo->GetName()<<endl;  // checking
         TString infile = Form("DATA/run00%d.txt",ii);
         fstream in;
         //cout<<"ii: "<<ii<<"-> "<<infile<<endl;    // checking
         in.open(infile,ios::in);

         if(in.fail()){
         cout <<" No se pudo abrir el archivo de Entrada ";
         exit(1);
         }   
            entries = 0;
            while(getline(in,linea)){

               stringstream ss(linea);

               no_columna = 0;
               while (ss >> valor){

                  if(no_columna == i-1){
                     histo->Fill(valor);
                     break;
                  } 

               no_columna++; 

               }

              entries++;

            }
   
         histo->Write();
         //cout << "Name Histo write: "<< histo->GetName()<<endl;   // checking
         in.close();

      }

      output->Close();
      delete output;

      cout << Form("==> Root file - uncalib%d.root - was created!!!",i) << endl;

   }

cout << " " << endl;
}


void convert2simnra(){

   gSystem->Exec("rm -rf f2simnra");
   gSystem->Exec("mkdir f2simnra");

   for (Int_t i = 1; i <= no_detector; i++){

      TFile *finput = new TFile(Form("uncalib%d.root",i),"read");

      for(Int_t ii = 0; ii < run; ii++){

         TH1F *h;
         TH1F *hout;

         h = (TH1F*)finput->Get(Form("hist%d_%d",ii,i));
         hout = new TH1F(Form("hout%d_%d",ii,i),Form("hout%d_%d",ii,i),4096,0,4096);

         TString outfile = Form("f2simnra/hist%d_%d.txt",ii,i);
         fstream out;

         out.open(outfile,ios::out);

         if(out.fail()){
            cout <<" No se pudo abrir el archivo de Salida ";
            exit(1);
         }

         for(Int_t j = 1; j < h->GetNbinsX(); j++){
             
            Int_t n;
            n = h->GetBinContent(j);

            hout->SetBinContent(j,n);
            out << j << "\t" << n << endl;

         }

         out.close();
      }

      finput->Close();
      delete finput;
   }

cout << "==> The files for SIMNRA were created succesfully!!!" << endl;

}
