#include "SimTrackerHitBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/SimTrackerHit.h"
#include "EVENT/MCParticle.h"
#include "streamlog/streamlog.h"

#include "TTree.h"


void SimTrackerHitBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  SimTrackerHitBranches::initBranches - invalid tree pointer !!! " ) ;
  }


  tree->Branch( (pre+"nsth").c_str() , &_nsth , (pre+"nsth/I").c_str() ) ;

  tree->Branch( (pre+"stci0").c_str() , _stci0 , (pre+"stci0[nsth]/I").c_str() ) ;
  tree->Branch( (pre+"stci1").c_str() , _stci1 , (pre+"stci1[nsth]/I").c_str() ) ;
  tree->Branch( (pre+"stpox").c_str() , _stpox , (pre+"stpox[nsth]/D").c_str() ) ;
  tree->Branch( (pre+"stpoy").c_str() , _stpoy , (pre+"stpoy[nsth]/D").c_str() ) ;
  tree->Branch( (pre+"stpoz").c_str() , _stpoz , (pre+"stpoz[nsth]/D").c_str() ) ;
  tree->Branch( (pre+"stedp").c_str() , _stedp , (pre+"stedp[nsth]/F").c_str() ) ;
  tree->Branch( (pre+"sttim").c_str() , _sttim , (pre+"sttim[nsth]/F").c_str() ) ;
  tree->Branch( (pre+"stmox").c_str() , _stmox , (pre+"stmox[nsth]/F").c_str() ) ;
  tree->Branch( (pre+"stmoy").c_str() , _stmoy , (pre+"stmoy[nsth]/F").c_str() ) ;
  tree->Branch( (pre+"stmoz").c_str() , _stmoz , (pre+"stmoz[nsth]/F").c_str() ) ;
  tree->Branch( (pre+"stptl").c_str() , _stptl , (pre+"stptl[nsth]/F").c_str() ) ;
  tree->Branch( (pre+"stmcp").c_str() , _stmcp , (pre+"stmcp[nsth]/I").c_str() ) ;


}
  

void SimTrackerHitBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col ) return ;

  streamlog_out( DEBUG2 ) << " SimTrackerHitBranches::fill called ... " << std::endl ;

  if( col->getTypeName() != lcio::LCIO::SIMTRACKERHIT ){

    std::string exStr("SimTrackerHitBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }


  _nsth  = col->getNumberOfElements() ;
  
  for(int i=0 ; i < _nsth ; ++i){
    
    lcio::SimTrackerHit* hit = static_cast<lcio::SimTrackerHit*>( col->getElementAt(i) ) ;
    
    _stci0[i] = hit->getCellID0() ;
    _stci1[i] = hit->getCellID1() ;
    _stpox[i] = hit->getPosition()[0] ;
    _stpoy[i] = hit->getPosition()[1] ;
    _stpoz[i] = hit->getPosition()[2] ;
    _stedp[i] = hit->getEDep() ;
    _sttim[i] = hit->getTime() ;
    _stmox[i] = hit->getMomentum()[0] ;
    _stmoy[i] = hit->getMomentum()[1] ;
    _stmoz[i] = hit->getMomentum()[2] ;
    _stptl[i] = hit->getPathLength() ;
    _stmcp[i] = ( hit->getMCParticle() ? hit->getMCParticle()->ext<CollIndex>() -1 : -1 )  ;
    
  }
}






















