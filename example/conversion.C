
void conversion( const char* FILEN){

  TFile f(FILEN,"r") ;

   // draw gamma conversions in RZ
   LCTuple->Draw("sqrt(mcvtx*mcvtx+mcvty*mcvty):mcvtz","mcsst!=0&&abs(mcpdg==11)&&abs(mcvtz)<2500.&&sqrt(mcvtx*mcvtx+mcvty*mcvty)<2150.&&mcpa0!=-1&&mcpdg[mcpa0]==22","",10000,0) ;

   // or in r-phi
   //LCTuple->Draw("mcvtx:mcvty","mcsst!=0&&abs(mcpdg==11)&&abs(mcvtz)<2000.&&sqrt(mcvtx*mcvtx+mcvty*mcvty)<175.&&mcpdg[mcpa0]==22","") ;

}
