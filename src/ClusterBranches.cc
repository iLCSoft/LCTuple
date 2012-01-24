#include "ClusterBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/Cluster.h"
#include "marlin/VerbosityLevels.h"

#include "TTree.h"


void ClusterBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  ClusterBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  tree->Branch( (pre+"nclu").c_str() , &_nclu ,  (pre+"nclu/I").c_str() ) ;
                                                                  
  tree->Branch( (pre+"cltyp").c_str() , _cltyp , (pre+"cltyp[nclu]/I").c_str() ) ;
  tree->Branch( (pre+"clene").c_str() , _clene , (pre+"clene[nclu]/F").c_str() ) ;
  tree->Branch( (pre+"cleer").c_str() , _cleer , (pre+"cleer[nclu]/F").c_str() ) ;
  tree->Branch( (pre+"clpox").c_str() , _clpox , (pre+"clpox[nclu]/F").c_str() ) ;
  tree->Branch( (pre+"clpoy").c_str() , _clpoy , (pre+"clpoy[nclu]/F").c_str() ) ;
  tree->Branch( (pre+"clpoz").c_str() , _clpoz , (pre+"clpoz[nclu]/F").c_str() ) ;
  tree->Branch( (pre+"clper").c_str() , _clper , (pre+"clper[nclu][6]/F").c_str() ) ;
  tree->Branch( (pre+"clthe").c_str() , _clthe , (pre+"clthe[nclu]/F").c_str() ) ;
  tree->Branch( (pre+"clphi").c_str() , _clphi , (pre+"clphi[nclu]/F").c_str() ) ;
  tree->Branch( (pre+"clder").c_str() , _clder , (pre+"clder[nclu][3]/F").c_str() ) ;
  tree->Branch( (pre+"clsha").c_str() , _clsha , (pre+"clsha[nclu][6]/F").c_str() ) ;
  tree->Branch( (pre+"clsde").c_str() , _clsde , (pre+"clsde[nclu][12]/F").c_str() ) ;

}
  

void ClusterBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col ) return ;
  
  if( col->getTypeName() != lcio::LCIO::CLUSTER ){
    
    std::string exStr("ClusterBranches::fill: invalid collection type : " ) ;
    
    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }
  
  _nclu  = col->getNumberOfElements() ;
  


  
  //------  fill the Clusters particle ----------------------------
  for(int i=0 ; i < _nclu ; ++i){
    

    lcio::Cluster* clu = static_cast<lcio::Cluster*>( col->getElementAt(i) ) ;

    //    std::cout << " filling cluster " << i << " from evt: " <<  evt->getEventNumber() << std::endl ;

    _cltyp[ i ] = clu->getType() ;
    _clene[ i ] = clu->getEnergy() ;
    _cleer[ i ] = clu->getEnergyError() ;
    _clpox[ i ] = clu->getPosition()[0] ;
    _clpoy[ i ] = clu->getPosition()[1] ;
    _clpoz[ i ] = clu->getPosition()[2] ;

    for( int j=0; j < 6 ; ++j ) 
      _clper[ i ][ j ]  = clu->getPositionError()[j] ; // position error cov matrix
    
    _clthe[ i ] = clu->getITheta() ;
    _clphi[ i ] = clu->getIPhi() ;
    
    _clder[ i ][ 0 ] = clu->getDirectionError()[0] ; 
    _clder[ i ][ 1 ] = clu->getDirectionError()[1] ; 
    _clder[ i ][ 2 ] = clu->getDirectionError()[2] ; 
    
    unsigned nsh = ( clu->getShape().size() > 6 ?  6  :  clu->getShape().size() ) ;
    
    for( unsigned j=0; j < nsh ; ++j ) 
      _clsha[ i ][ j ]  = clu->getShape()[j] ; // position error cov matrix
    
    
    unsigned nsd = ( clu->getSubdetectorEnergies().size() > 12 ?  12  :  clu->getSubdetectorEnergies().size() ) ;
    
    for( unsigned j=0; j < nsd ; ++j ) 
      _clsde[ i ][ j ]  = clu->getSubdetectorEnergies()[j] ; // position error cov matrix
    
  }
  
}






















