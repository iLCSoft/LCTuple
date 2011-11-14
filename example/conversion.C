
void conversion( const char* FILEN){

  TFile f(FILEN,"r") ;

   // draw gamma conversions in RZ
   //LCTuple->Draw("sqrt(mcvtx*mcvtx+mcvty*mcvty):mcvtz","mcsst!=0&&abs(mcpdg==11)&&abs(mcvtz)<2500.&&sqrt(mcvtx*mcvtx+mcvty*mcvty)<2150.&&mcpa0!=-1&&mcpdg[mcpa0]==22","",10000,0) ;

   // or in r-phi
   //LCTuple->Draw("mcvtx:mcvty","mcsst!=0&&abs(mcpdg==11)&&abs(mcvtz)<2000.&&sqrt(mcvtx*mcvtx+mcvty*mcvty)<175.&&mcpdg[mcpa0]==22","") ;

   
   // draw reconstructed energy vs true energy for true protons (recunstructed as charged ) 
  LCTuple->Draw("log(rcene[r2mf[]])/log(10.):log(mcene[r2mt[]])/log(10.)","r2mw>0.99&&abs(rccha[r2mf[]])>0.5&&mcpdg[r2mt[]]==2212. ","",1000,0) ;

  // ...for electrons
  LCTuple->Draw("log(rcene[r2mf[]])/log(10.):log(mcene[r2mt[]])/log(10.)","r2mw>0.99&&abs(rccha[r2mf[]])>0.5&&abs(mcpdg[r2mt[]])==11. ","",1000,0) ;

  // and pions 
  LCTuple->Draw("log(rcene[r2mf[]])/log(10.):log(mcene[r2mt[]])/log(10.)","r2mw>0.99&&abs(rccha[r2mf[]])>0.5&&abs(mcpdg[r2mt[]])==211. ","",1000,0) ;


}
