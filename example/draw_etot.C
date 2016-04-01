#include "TFile.h"
#include "TTree.h"

void draw_etot( const char* FILEN ) {


  std::string pdfFile( std::string( FILEN ) + std::string( "_etot.pdf" ) ) ;

  TFile *f = new TFile(FILEN) ;
  TTree *MyLCTuple = (TTree*)f->Get("MyLCTuple") ;

  c1 = new TCanvas("C1","Total energy - McTruth vs. PFOs",-5);
  c1->Divide(1,2);

  c1->cd(1) ;
  MyLCTuple->Draw("sum()","sum( mcene, Iteration$, nmcp,(mcgst==1) )" ) ;       

  c1->cd(2) ;
  MyLCTuple->Draw("sum()","sum( rcene, Iteration$, nrec,(1) )") ;       


  c1->Print( pdfFile.c_str() ) ;

}


/** Function to sum up a quantity in a tree.
 *  call as 
 *     LCTuple->Draw("sum()","sum( mcene, Iteration$, nmcp,(mcgst==1) )") ;
 *
 */
float sum(float a=0., int iter=0, int N=0, bool cond=true){ 
  
  static float s = 0. ;
  static float r = 0. ;
  
  if(iter==0 && N==0)
    return r ;
  
  if( cond ) 
    s += a ;
  
  if( iter == N-1 ){
    
    r = s ;
    s = 0; 
    return 1 ;
  } 

  return 0 ;
}
