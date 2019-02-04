#include "CreateRecoRelations.h"

#include "EVENT/ReconstructedParticle.h"
#include "IMPL/LCCollectionVec.h"
#include "UTIL/LCRelationNavigator.h"

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"

using namespace lcio ;
using namespace marlin ;


/** helper function to get collection safely */
inline lcio::LCCollection* getCollection(lcio::LCEvent* evt, const std::string name ){
  
  if( name.size() == 0 )
    return 0 ;
  
  try{
    
    return evt->getCollection( name ) ;
    
  } catch( lcio::DataNotAvailableException& e ){
    
    streamlog_out( DEBUG2 ) << "getCollection :  DataNotAvailableException : " << name <<  std::endl ;
    
    return 0 ;
  }
}

//------------------------------------------------------------------------------------------------


CreateRecoRelations aCreateRecoRelations ;


CreateRecoRelations::CreateRecoRelations() : Processor("CreateRecoRelations") {
  
  // modify processor description
  _description = "CreateRecoRelations creates transient collections with realtions from  ReconstructedParticles to Tracks and Clusters" ;
  

  registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			   "RecoCollection" , 
			   "Names of ReconstructedParticles input collections" ,
			   _inColReco ,
			   std::string("PandoraPFOs")
			   );
  
  registerOutputCollection( LCIO::LCRELATION,
			    "Reco2TracksRelationName" , 
			    "Name of output collection for relation ReconstructedParticles to Tracks" ,
			    _outColR2T ,
			    std::string("Reco2TracksRelation")
			    );
  
  registerOutputCollection(  LCIO::LCRELATION,
			     "Reco2ClusterRelationName" , 
			     "Name of output collection for relation ReconstructedParticles to Clusters" ,
			     _outColR2C ,
			     std::string("Reco2ClustersRelation")
			     );
  
  registerOutputCollection(  LCIO::LCRELATION,
			     "Reco2RecoRelationName" , 
			     "Name of output collection for relation ReconstructedParticles to ReconstructedParticles" ,
			     _outColR2R ,
			     std::string("Reco2RecoRelation")
			     );
  
  
}

//============================================================================================================================

void CreateRecoRelations::init() { 
  
  streamlog_out(DEBUG) << "   init called  " << std::endl ;
  
  // usually a good idea to
  printParameters() ;
  
  _nRun = 0 ;
  _nEvt = 0 ;
  
}
//============================================================================================================================


void CreateRecoRelations::processRunHeader( LCRunHeader* /*run*/) { 
  
  _nRun++ ;
} 


//============================================================================================================================

void CreateRecoRelations::processEvent( LCEvent * evt ) { 
  
  
  LCCollection* col  =  getCollection ( evt , _inColReco ) ;
  
  LCRelationNavigator relT( LCIO::RECONSTRUCTEDPARTICLE, LCIO::TRACK ) ;
  LCRelationNavigator relC( LCIO::RECONSTRUCTEDPARTICLE, LCIO::TRACK ) ;
  LCRelationNavigator relR( LCIO::RECONSTRUCTEDPARTICLE, LCIO::TRACK ) ;


  int nEle = ( col ?  col->getNumberOfElements() : 0 ) ; 
  
  for(int i=0; i < nEle ; ++i){
    
    ReconstructedParticle* part = static_cast<ReconstructedParticle*>( col->getElementAt(i) ) ;
    
    for(unsigned j=0, n = part->getTracks().size() ; j<n ; ++j){
      
      relT.addRelation( part , part->getTracks()[ j ]  , 1. ) ;
    } 
    
    for(unsigned j=0, n = part->getClusters().size() ; j<n ; ++j){
      
      relC.addRelation( part , part->getClusters()[ j ]  , 1. ) ;
    } 
    
    for(unsigned j=0, n = part->getParticles().size() ; j<n ; ++j){
      
      relR.addRelation( part , part->getParticles()[ j ]  , 1. ) ;
    } 
  }
  

  LCCollectionVec* outColR2T = (LCCollectionVec*) relT.createLCCollection() ;
  LCCollectionVec* outColR2C = (LCCollectionVec*) relC.createLCCollection() ;
  LCCollectionVec* outColR2R = (LCCollectionVec*) relR.createLCCollection() ;

  outColR2T->setTransient( true ) ;
  outColR2C->setTransient( true ) ;
  outColR2R->setTransient( true ) ;

  evt->addCollection( outColR2T, _outColR2T   ) ;
  evt->addCollection( outColR2C, _outColR2C   ) ;
  evt->addCollection( outColR2R, _outColR2R   ) ;
  

  streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		       << "   in run:  "          << evt->getRunNumber()   << std::endl ;
  
  
  _nEvt ++ ;
}

//============================================================================================================================

void CreateRecoRelations::check( LCEvent * /*evt*/ ) { 
  // nothing to check here - could be used to fill checkplots in reconstruction processor
}


//============================================================================================================================

void CreateRecoRelations::end(){ 
  
  streamlog_out( MESSAGE ) << " processed " << _nEvt << " events in " << _nRun << " runs "
			   << std::endl ;

}

