#include "TrackBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/Track.h"
#include "marlin/VerbosityLevels.h"

#include "TTree.h"


void TrackBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  TrackBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  if (_writeparameters) CollectionBranches::initBranches(tree, (pre+"tr").c_str());

  tree->Branch( (pre+"ntrk").c_str() , &_ntrk ,  (pre+"ntrk/I").c_str() ) ;

  tree->Branch( (pre+"trori").c_str() , _trori , (pre+"trori["+pre+"ntrk]/I").c_str() ) ;

  tree->Branch( (pre+"trtyp").c_str() , _trtyp , (pre+"trtyp["+pre+"ntrk]/I").c_str() ) ;
  tree->Branch( (pre+"trch2").c_str() , _trch2 , (pre+"trch2["+pre+"ntrk]/F").c_str() ) ;
  tree->Branch( (pre+"trndf").c_str() , _trndf , (pre+"trndf["+pre+"ntrk]/I").c_str() ) ;
  tree->Branch( (pre+"tredx").c_str() , _tredx , (pre+"tredx["+pre+"ntrk]/F").c_str() ) ;
  tree->Branch( (pre+"trede").c_str() , _trede , (pre+"trede["+pre+"ntrk]/F").c_str() ) ;
  tree->Branch( (pre+"trrih").c_str() , _trrih , (pre+"trrih["+pre+"ntrk]/F").c_str() ) ;
  tree->Branch( (pre+"trshn").c_str() , _trshn , (pre+"trshn["+pre+"ntrk][12]/I").c_str() ) ;
  tree->Branch( (pre+"trnts").c_str() , _trnts , (pre+"trnts["+pre+"ntrk]/I").c_str() ) ;
  tree->Branch( (pre+"trfts").c_str() , _trfts , (pre+"trfts["+pre+"ntrk]/I").c_str() ) ;
  tree->Branch( (pre+"trsip").c_str() , _trsip , (pre+"trsip["+pre+"ntrk]/I").c_str() ) ;
  tree->Branch( (pre+"trsfh").c_str() , _trsfh , (pre+"trsfh["+pre+"ntrk]/I").c_str() ) ;
  tree->Branch( (pre+"trslh").c_str() , _trslh , (pre+"trslh["+pre+"ntrk]/I").c_str() ) ;
  tree->Branch( (pre+"trsca").c_str() , _trsca , (pre+"trsca["+pre+"ntrk]/I").c_str() ) ;

  tree->Branch( (pre+"ntrst").c_str() , &_ntrst , (pre+"ntrst/I").c_str() ) ;

  tree->Branch( (pre+"tsloc").c_str() , _tsloc , (pre+"tsloc["+pre+"ntrst]/I").c_str() ) ;
  tree->Branch( (pre+"tsdze").c_str() , _tsdze , (pre+"tsdze["+pre+"ntrst]/F").c_str() ) ;
  tree->Branch( (pre+"tsphi").c_str() , _tsphi , (pre+"tsphi["+pre+"ntrst]/F").c_str() ) ;
  tree->Branch( (pre+"tsome").c_str() , _tsome , (pre+"tsome["+pre+"ntrst]/F").c_str() ) ;
  tree->Branch( (pre+"tszze").c_str() , _tszze , (pre+"tszze["+pre+"ntrst]/F").c_str() ) ;
  tree->Branch( (pre+"tstnl").c_str() , _tstnl , (pre+"tstnl["+pre+"ntrst]/F").c_str() ) ;
  tree->Branch( (pre+"tscov").c_str() , _tscov , (pre+"tscov["+pre+"ntrst][15]/F").c_str() ) ;
  tree->Branch( (pre+"tsrpx").c_str() , _tsrpx , (pre+"tsrpx["+pre+"ntrst]/F").c_str() ) ;
  tree->Branch( (pre+"tsrpy").c_str() , _tsrpy , (pre+"tsrpy["+pre+"ntrst]/F").c_str() ) ;
  tree->Branch( (pre+"tsrpz").c_str() , _tsrpz , (pre+"tsrpz["+pre+"ntrst]/F").c_str() ) ;

}
  

void TrackBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col ) return ;
  
  if( col->getTypeName() != lcio::LCIO::TRACK ){
    
    std::string exStr("TrackBranches::fill: invalid collection type : " ) ;
    
    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }
  
  if (_writeparameters) CollectionBranches::fill(col, evt);

  _ntrk  = col->getNumberOfElements() ;
  
  //---------  create a helper vector with track states first -------------------------------
  std::vector<lcio::TrackState*> tsV ;
  tsV.reserve(  col->getNumberOfElements() * 4 ) ;
  
  for(int i=0, nrc  = col->getNumberOfElements() ; i < nrc ; ++i ){
    
    lcio::Track* trk = static_cast<lcio::Track*>( col->getElementAt( i) ) ;
    
    const EVENT::TrackStateVec & tss = trk->getTrackStates() ;
    
    for(int j=0, nts = tss.size() ; j<nts ; ++j){
      
      tsV.push_back( tss[j] ) ;
      
      tss[j]->ext<CollIndex>() =  tsV.size() ;
    }
  }

  _ntrst = tsV.size() ;

  streamlog_out( DEBUG ) <<  " total number of track states : " << _ntrst << std::endl  ; 
  //----------  fill the track states ---------------------------------------
  for(int i=0 ; i < _ntrst ; ++i){
    
    lcio::TrackState* ts = tsV[i] ;
    
    _tsloc[ i ] = ts->getLocation() ; 
    _tsdze[ i ] = ts->getD0() ;
    _tsphi[ i ] = ts->getPhi() ;
    _tsome[ i ] = ts->getOmega() ;
    _tszze[ i ] = ts->getZ0() ;
    _tstnl[ i ] = ts->getTanLambda() ;
    _tsrpx[ i ] = ts->getReferencePoint()[0] ;
    _tsrpy[ i ] = ts->getReferencePoint()[1] ;
    _tsrpz[ i ] = ts->getReferencePoint()[2] ;
    
    for(int j=0;j<15;++j){
      _tscov[ i ][ j ] = ts->getCovMatrix()[j] ;
    }
    
  }
  
  
  //------  fill the Tracks particle ----------------------------
  for(int i=0 ; i < _ntrk ; ++i){
    
    lcio::Track* trk = static_cast<lcio::Track*>( col->getElementAt(i) ) ;

    _trori[i] = trk->ext<CollID>();
    
    _trtyp[ i ] = trk->getType() ;
    _trch2[ i ] = trk->getChi2() ;
    _trndf[ i ] = trk->getNdf() ; 
    _tredx[ i ] = trk->getdEdx() ;
    _trede[ i ] = trk->getdEdxError() ;
    _trrih[ i ] = trk->getRadiusOfInnermostHit() ;

    _trnts[ i ] = trk->getTrackStates().size() ;
    _trfts[ i ] = ( _trnts[i]>0 ? trk->getTrackStates()[0]->ext<CollIndex>() -1  :  -1 )  ;

    const lcio::TrackState* ts ;

    ts = trk->getTrackState( lcio::TrackState::AtIP )  ;
    _trsip[ i ] = ( ts ?  ts->ext<CollIndex>() - 1 : -1 ) ;   
    
    ts = trk->getTrackState( lcio::TrackState::AtFirstHit ) ;
    _trsfh[ i ] = ( ts ?  ts->ext<CollIndex>() - 1 : -1 ) ;   
    
    ts =  trk->getTrackState( lcio::TrackState::AtLastHit ) ;
    _trslh[ i ] = ( ts ?  ts->ext<CollIndex>() - 1 : -1 ) ;   
    
    ts = trk->getTrackState( lcio::TrackState::AtCalorimeter ) ;
    _trsca[ i ] = ( ts ?  ts->ext<CollIndex>() - 1 : -1 ) ;   
    
    
    int nshn = ( trk->getSubdetectorHitNumbers().size()   <  12  ?  
		 trk->getSubdetectorHitNumbers().size()   :  12  ) ;
    
    for( int j=0; j<nshn ; ++j )
      _trshn[ i ][ j ]  = trk->getSubdetectorHitNumbers()[j] ;
    
  }
}






















