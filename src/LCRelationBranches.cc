#include "LCRelationBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/LCRelation.h"

#include "TTree.h"


void LCRelationBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  LCRelationBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  tree->Branch( (pre+"nrel").c_str() , &_nrel , (pre+"nrel/I").c_str() ) ;

  tree->Branch( (pre+"f").c_str() , _from , (pre+"f["+pre+"nrel]/I").c_str() ) ;
  tree->Branch( (pre+"t").c_str() , _to   , (pre+"t["+pre+"nrel]/I").c_str() ) ;
  tree->Branch( (pre+"w").c_str() , _wgt  , (pre+"w["+pre+"nrel]/F").c_str() ) ;
}
  

void LCRelationBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* /*evt*/ ){
  
  if( !col ) return ;

  if( col->getTypeName() != lcio::LCIO::LCRELATION ){

    std::string exStr("LCRelationBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }


  _nrel  = col->getNumberOfElements() ;
  
  for(int i=0 ; i < _nrel ; ++i){
    
    lcio::LCRelation* rel = static_cast<lcio::LCRelation*>( col->getElementAt(i) ) ;
    
    
    _from[ i ] = ( rel->getFrom()  ?  rel->getFrom()->ext<CollIndex>() - 1  :  -1 )  ;
    _to  [ i ] = ( rel->getTo()    ?  rel->getTo()->ext<CollIndex>()   - 1  :  -1 )  ;
    _wgt [ i ] =   rel->getWeight() ; 
    
  }
}






















