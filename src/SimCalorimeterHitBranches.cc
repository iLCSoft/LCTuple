#include "SimCalorimeterHitBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/SimCalorimeterHit.h"
#include "EVENT/MCParticle.h"
#include "streamlog/streamlog.h"

#include "TTree.h"


void SimCalorimeterHitBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  SimCalorimeterHitBranches::initBranches - invalid tree pointer !!! " ) ;
  }


  tree->Branch( (pre+"nsch").c_str() , &_nsch , (pre+"nsch/I").c_str() ) ;
  
  tree->Branch( (pre+"scci0").c_str() , _scci0 , (pre+"scci0[nsch]/I").c_str() ) ;
  tree->Branch( (pre+"scci1").c_str() , _scci1 , (pre+"scci1[nsch]/I").c_str() ) ;
  tree->Branch( (pre+"scpox").c_str() , _scpox , (pre+"scpox[nsch]/F").c_str() ) ;
  tree->Branch( (pre+"scpoy").c_str() , _scpoy , (pre+"scpoy[nsch]/F").c_str() ) ;
  tree->Branch( (pre+"scpoz").c_str() , _scpoz , (pre+"scpoz[nsch]/F").c_str() ) ;
  tree->Branch( (pre+"scene").c_str() , _scene , (pre+"scene[nsch]/F").c_str() ) ;
  
  
}


void SimCalorimeterHitBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col ) return ;

  streamlog_out( DEBUG2 ) << " SimCalorimeterHitBranches::fill called ... " << std::endl ;

  if( col->getTypeName() != lcio::LCIO::SIMCALORIMETERHIT ){

    std::string exStr("SimCalorimeterHitBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }


  _nsch  = col->getNumberOfElements() ;
  
  for(int i=0 ; i < _nsch ; ++i){
    
    lcio::SimCalorimeterHit* hit = static_cast<lcio::SimCalorimeterHit*>( col->getElementAt(i) ) ;
    
    _scci0[i] = hit->getCellID0() ;
    _scci1[i] = hit->getCellID1() ;
    _scpox[i] = hit->getPosition()[0] ;
    _scpoy[i] = hit->getPosition()[1] ;
    _scpoz[i] = hit->getPosition()[2] ;
    _scene[i] = hit->getEnergy() ;
    
  }
}






















