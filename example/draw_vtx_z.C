#include "TFile.h"
#include "TTree.h"


void draw_vtx_z( const char* FILEN ) {

  std::string pdfFile( std::string( FILEN ) + std::string( ".pdf" ) ) ;

  TFile *f = new TFile(FILEN) ;
  TTree *MyLCTuple = (TTree*)f->Get("MyLCTuple");

  c1 = new TCanvas("C1","Spread of vertex position in z - MCTruth and Reconstructed",-5);
  c1->Divide(1,3);
  c1->cd(1) ;
  MyLCTuple->Draw("mcvtz","mcgst==1&&abs(mcvtz)<2.") ;
  c1->cd(2) ;
  MyLCTuple->Draw("vtzzz","abs(vtzzz)<2.") ;
  c1->cd(3) ;
  MyLCTuple->Draw("mcvtz[10]-vtzzz","abs(mcvtz[10]-vtzzz)<.01") ;


  c1->Print( pdfFile.c_str() ) ;

}
