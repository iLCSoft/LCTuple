// draw sim hits
#include "TFile.h"
#include "TTree.h"


/** Helper function for radius
 */
float r(float x,float y) { return sqrt(x*x+y*y) ; }


/** Helper function for subdet id
 */
int sub(int cellid){

  return ( (unsigned) cellid & 0x0000001f ) ;
}


//------------------------------------------------------

void draw_simhits( const char* FILEN ) {
  
  TFile *f = new TFile(FILEN) ;
  TTree *MyLCTuple = (TTree*)f->Get("MyLCTuple");
  
  c1 = new TCanvas("C1","Some example plots from LCTuple",1000 , 1000 );
  //  c1->Divide(1,2);
  //  c1->cd(1) ;
  
  int max = 1000 ;
  
  MyLCTuple->Draw("r(scpox,scpoy):scpoz","r(scpox,scpoy)<5500.&abs(scpoz)<5000.","",max) ;
  
  MyLCTuple->Draw("r(stpox,stpoy):stpoz","r(stpox,stpoy)<5500.&abs(stpoz)<5000.","same",max) ;
  
  c1->Print("simhits.gif");
  
  
  MyLCTuple->Draw("scpox:scpoy","r(scpox,scpoy)<5500&abs(scpoz)<2400.","",max) ;
  
  MyLCTuple->Draw("stpox:stpoy","r(stpox,stpoy)<5500.&abs(stpoz)<2400.&&(stci0&0x001f)!=3","same",max) ;
  
  c1->Print("simhits_barrel.gif");
  
  
}
