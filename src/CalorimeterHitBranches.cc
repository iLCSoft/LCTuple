#include "CalorimeterHitBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/CalorimeterHit.h"
#include "EVENT/MCParticle.h"
#include "streamlog/streamlog.h"

#include "TTree.h"


void CalorimeterHitBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  CalorimeterHitBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  if (_writeparameters) CollectionBranches::initBranches(tree, (pre+"cah").c_str());


  tree->Branch( (pre+"ncah").c_str() , &_ncah , (pre+"ncah/I").c_str() ) ;
  
  tree->Branch( (pre+"caori").c_str() , _caori , (pre+"caori["+pre+"ncah]/I").c_str() ) ;

  tree->Branch( (pre+"caci0").c_str() , _caci0 , (pre+"caci0["+pre+"ncah]/I").c_str() ) ;
  tree->Branch( (pre+"caci1").c_str() , _caci1 , (pre+"caci1["+pre+"ncah]/I").c_str() ) ;
  tree->Branch( (pre+"capox").c_str() , _capox , (pre+"capox["+pre+"ncah]/F").c_str() ) ;
  tree->Branch( (pre+"capoy").c_str() , _capoy , (pre+"capoy["+pre+"ncah]/F").c_str() ) ;
  tree->Branch( (pre+"capoz").c_str() , _capoz , (pre+"capoz["+pre+"ncah]/F").c_str() ) ;
  tree->Branch( (pre+"caene").c_str() , _caene , (pre+"caene["+pre+"ncah]/F").c_str() ) ;
  tree->Branch( (pre+"catim").c_str() , _catim , (pre+"catim["+pre+"ncah]/F").c_str() ) ;
  
  
}


void CalorimeterHitBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col ) return ;

  streamlog_out( DEBUG2 ) << " CalorimeterHitBranches::fill called ... " << std::endl ;

  if( col->getTypeName() != lcio::LCIO::CALORIMETERHIT ){

    std::string exStr("CalorimeterHitBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }

  if (_writeparameters) CollectionBranches::fill(col, evt);

  _ncah  = col->getNumberOfElements() ;
  
  for(int i=0 ; i < _ncah ; ++i){
    
    lcio::CalorimeterHit* hit = static_cast<lcio::CalorimeterHit*>( col->getElementAt(i) ) ;

    _caori[i] = hit->ext<CollID>();
    
    _caci0[i] = hit->getCellID0() ;
    _caci1[i] = hit->getCellID1() ;
    _capox[i] = hit->getPosition()[0] ;
    _capoy[i] = hit->getPosition()[1] ;
    _capoz[i] = hit->getPosition()[2] ;
    _caene[i] = hit->getEnergy() ;
    _catim[i] = hit->getTime() ;
    
  }
}






















