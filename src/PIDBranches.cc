#include "PIDBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/ParticleID.h"

#include "TTree.h"


void PIDBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  PIDBranches::initBranches - invalid tree pointer !!! " ) ;
  }


  tree->Branch( (pre+"npid").c_str() , &_npid , (pre+"npid/I").c_str() ) ;

  tree->Branch( (pre+"pityp").c_str() , _pityp , (pre+"pityp[npid]/I").c_str() ) ;
  tree->Branch( (pre+"pipdg").c_str() , _pipdg , (pre+"pipdg[npid]/I").c_str() ) ;
  tree->Branch( (pre+"pillh").c_str() , _pillh , (pre+"pillh[npid]/F").c_str() ) ;
  tree->Branch( (pre+"pialg").c_str() , _pialg , (pre+"pialg[npid]/I").c_str() ) ;

}
  

void PIDBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col ) return ;

  if( col->getTypeName() != "ParticleID" ){

    std::string exStr("PIDBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }


  _npid  = col->getNumberOfElements() ;
  
  for(int i=0 ; i < _npid ; ++i){
    
    lcio::ParticleID* pid = static_cast<lcio::ParticleID*>( col->getElementAt(i) ) ;
    
    
    _pityp[ i ] = pid->getType() ;
    _pipdg[ i ] = pid->getPDG() ;
    _pillh[ i ] = pid->getLikelihood() ;
    _pialg[ i ] = pid->getAlgorithmType() ;
    
  }
}






















