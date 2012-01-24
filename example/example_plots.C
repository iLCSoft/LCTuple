
void example_plots( const char* FILEN){

  TFile f(FILEN,"r") ;

  c1 = new TCanvas("C1","Some example plots from LCTuple",-5);
  c1->Clear();
  c1->Divide(3,3);

  int pad = 1 ;

  // draw gamma conversions in RZ
  c1->cd( pad++ ) ;
  LCTuple->Draw("sqrt(mcvtx*mcvtx+mcvty*mcvty):mcvtz","mcsst!=0&&abs(mcpdg==11)&&abs(mcvtz)<2500.&&sqrt(mcvtx*mcvtx+mcvty*mcvty)<2150.&&mcpa0!=-1&&mcpdg[mcpa0]==22","",10000,0) ;
  
  // or in r-phi
  c1->cd( pad++ ) ;
   LCTuple->Draw("mcvtx:mcvty","mcsst!=0&&abs(mcpdg==11)&&abs(mcvtz)<2000.&&sqrt(mcvtx*mcvtx+mcvty*mcvty)<175.&&mcpdg[mcpa0]==22","") ;
  
  
  // draw reconstructed energy vs true energy for true protons (recunstructed as charged ) 
  c1->cd( pad++ ) ;
  LCTuple->Draw("log10(rcene[r2mf[]]):log10(mcene[r2mt[]])","r2mw>0.99&&abs(rccha[r2mf[]])>0.5&&mcpdg[r2mt[]]==2212. ","",1000,0) ;
  
  // ...for electrons
  c1->cd( pad++ ) ;
  LCTuple->Draw("log10(rcene[r2mf[]]):log10(mcene[r2mt[]])","r2mw>0.99&&abs(rccha[r2mf[]])>0.5&&abs(mcpdg[r2mt[]])==11. ","",1000,0) ;
  
  // // and pions 
  c1->cd( pad++ ) ;
  LCTuple->Draw("log10(rcene[r2mf[]]):log10(mcene[r2mt[]])","r2mw>0.99&&abs(rccha[r2mf[]])>0.5&&abs(mcpdg[r2mt[]])==211. ","",1000,0) ;
  
  
  //c1->cd( pad++ ) ;
  //LCTuple->Draw("mcpdg[r2mt[]]","abs(pipdg[rcfpi[r2mf[]]])==13&&abs(mcpdg[r2mt[]])<1000.") ;

  // draw pid for true muons
  c1->cd( pad++ ) ;
  LCTuple->Draw("pipdg[rcfpi[r2mf[]]]","abs(mcpdg[r2mt[]])==13&&abs(pipdg[rcfpi[r2mf[]]])<1000.") ;


  // draw pt of charged reconstructed particles vs 1./omega of their track (using first track state of track)
  c1->cd( pad++ ) ;
  LCTuple->Draw("sqrt(rcmox*rcmox+rcmoy*rcmoy):1./abs(tsome[trfts[rcftr]])","abs(rccha)>0.5&&rcntr==1") ;


  // draw cluster energy vs. Reco energy of neutrals
  LCTuple->Draw("clene[r2ct[]]:rcene[r2cf[]]","rccha==0") ;
}
