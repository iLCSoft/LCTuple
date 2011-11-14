#include "RecoParticleBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"

#include "TTree.h"


void RecoParticleBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  RecoParticleBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  tree->Branch( (pre+"nrc").c_str() , &_nrc ,  (pre+"nrec/I").c_str() ) ;

  tree->Branch( (pre+"rctyp").c_str() , _rctyp , (pre+"rctyp[nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rccov").c_str() , _rccov , (pre+"rccov[nrec][10]/F").c_str() ) ;
  tree->Branch( (pre+"rcrpx").c_str() , _rcrpx , (pre+"rcrpx[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcrpy").c_str() , _rcrpy , (pre+"rcrpy[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcrpz").c_str() , _rcrpz , (pre+"rcrpz[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcgpi").c_str() , _rcgpi , (pre+"rcgpi[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcpiu").c_str() , _rcpiu , (pre+"rcpiu[nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcmox").c_str() , _rcmox , (pre+"rcmox[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcmoy").c_str() , _rcmoy , (pre+"rcmoy[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcmoz").c_str() , _rcmoz , (pre+"rcmoz[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcmas").c_str() , _rcmas , (pre+"rcmas[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcene").c_str() , _rcene , (pre+"rcene[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rccha").c_str() , _rccha , (pre+"rccha[nrec]/F").c_str() ) ;
  
  
}
  

void RecoParticleBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col ) return ;

  if( col->getTypeName() != lcio::LCIO::RECONSTRUCTEDPARTICLE ){
    
    std::string exStr("RecoParticleBranches::fill: invalid collection type : " ) ;
    
    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }
  
  
  _nrc  = col->getNumberOfElements() ;
  
  for(int i=0 ; i < _nrc ; ++i){
    
    lcio::ReconstructedParticle* rec = static_cast<lcio::ReconstructedParticle*>( col->getElementAt(i) ) ;
    
    
    _rctyp[ i ] = rec->getType() ; 

    for( int j=0; j<10 ; ++j )
      _rccov[ i ][ j ]  = rec->getCovMatrix()[j] ;
    
    _rcrpx[ i ] = rec->getReferencePoint()[0] ;
    _rcrpy[ i ] = rec->getReferencePoint()[1] ;
    _rcrpz[ i ] = rec->getReferencePoint()[2] ;
    _rcgpi[ i ] = rec->getGoodnessOfPID() ;
    _rcpiu[ i ] = ( rec->getParticleIDUsed() ?   rec->getParticleIDUsed()->ext<CollIndex>() - 1  :  -1 )   ;
    _rcmox[ i ] = rec->getMomentum()[0] ;
    _rcmoy[ i ] = rec->getMomentum()[1] ;
    _rcmoz[ i ] = rec->getMomentum()[2] ;
    _rcmas[ i ] = rec->getMass() ;
    _rcene[ i ] = rec->getEnergy() ;
    _rccha[ i ] = rec->getCharge() ;


      //    _reca1[ i ] = ( p.size() > 1 ?  p[1]->ext<CollIndex>() - 1  :  -1 )  ;

    // can we have more than two parents ????
    
  }
}






















