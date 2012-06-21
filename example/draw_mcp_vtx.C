// draw mcp vertices

void draw_mcp_vtx( const char* FILEN ) {
 TFile f(FILEN) ;
 c1 = new TCanvas("C1","Some example plots from LCTuple",-5);
 c1->Divide(1,2);
 c1->cd(1) ;
 LCTuple->Draw("sqrt(mcvtx*mcvtx+mcvty*mcvty):mcvtz","mcsst!=0&&abs(mcvtz)<2500.&&sqrt(mcvtx*mcvtx+mcvty*mcvty)<2150.&&mcpa0!=-1","",10000,0) ;
 c1->cd(2) ;
 LCTuple->Draw("sqrt(mcvtx*mcvtx+mcvty*mcvty):mcvtz","mcsst!=0&&abs(mcvtz)<2400.&&sqrt(mcvtx*mcvtx+mcvty*mcvty)<1842.&&mcpa0!=-1","",10000,0) ;
 c1->SaveAs("mcp_vtx.gif");
}
