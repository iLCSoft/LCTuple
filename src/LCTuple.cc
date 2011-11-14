#include "LCTuple.h"

#include "TTree.h"

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/LCRelation.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"

#include "MCParticleBranches.h"
#include "RecoParticleBranches.h"
#include "LCRelationBranches.h"



using namespace lcio ;
using namespace marlin ;



/** helper function to get collection safely */
inline lcio::LCCollection* getCollection(lcio::LCEvent* evt, const std::string name ){

  if( name.size() == 0 )
    return 0 ;

  try{
    
    return evt->getCollection( name ) ;
    
  } catch( lcio::DataNotAvailableException& e ){
    
    return 0 ;
  }
}



LCTuple aLCTuple ;


LCTuple::LCTuple() : Processor("LCTuple") {
  
  // modify processor description
  _description = "LCTuple creates a ROOT TTRee with a column wise ntuple from LCIO collections ...." ;
  
  
  // register steering parameters: name, description, class-variable, default value
  registerInputCollection( LCIO::MCPARTICLE,
			   "MCParticleCollection" , 
			   "Name of the MCParticle collection"  ,
			   _mcpColName ,
			   std::string("MCParticle")
			   );

  registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			   "RecoParticleCollection" , 
			   "Name of the ReconstructedParticle collection"  ,
			   _recColName ,
			   std::string("PandoraPFOs")
			   );

  registerInputCollection( LCIO::LCRELATION,
			   "RecoMCTruthCollection" , 
			   "Name of the RecoMCTruth relation collection"  ,
			   _rmtColName ,
			   std::string("RecoMCTruthLink")
			   );
}



void LCTuple::init() { 

    streamlog_out(DEBUG) << "   init called  " << std::endl ;

    // usually a good idea to
    printParameters() ;

    _nRun = 0 ;
    _nEvt = 0 ;

    _tree = new TTree( "LCTuple" , "column wise ntuple with LCIO data") ;
   
    _mcpBranches =  new MCParticleBranches() ;
    _recBranches =  new RecoParticleBranches() ;
    _rmtBranches =  new LCRelationBranches() ;

}


void LCTuple::processRunHeader( LCRunHeader* run) { 

    _nRun++ ;
} 



void LCTuple::processEvent( LCEvent * evt ) { 


  if( isFirstEvent() ) { 
    
    //=====================================================
    //    initialize the branches 

    _mcpBranches->initBranches( _tree ) ;

    _recBranches->initBranches( _tree ) ;

    _rmtBranches->initBranches( _tree , "r2m" ) ;

  }

  //=====================================================
  //     add the collection index to the objects 
  
  LCCollection* mcpCol =  getCollection ( evt , _mcpColName ) ;

  LCCollection* recCol =  getCollection ( evt , _recColName ) ;

  LCCollection* rmtCol =  getCollection ( evt , _rmtColName ) ;

  if( mcpCol != 0 ) {
    
    for(int i=0, nmc  = mcpCol->getNumberOfElements() ; i < nmc ; ++i ){
      
      static_cast<lcio::MCParticle*>( mcpCol->getElementAt( i) )->ext<CollIndex>() = i + 1 ; 
    }  
  }

  if( recCol != 0 ) {
    
    for(int i=0, nrc  = recCol->getNumberOfElements() ; i < nrc ; ++i ){
      
      static_cast<lcio::ReconstructedParticle*>( recCol->getElementAt( i) )->ext<CollIndex>() = i + 1 ; 
    }  
  }
  
  //================================================
  //    fill the ntuple arrays 
  
  _mcpBranches->fill( mcpCol , evt ) ;

  _recBranches->fill( recCol , evt ) ;

  _rmtBranches->fill( rmtCol , evt ) ;
  //================================================
  _tree->Fill() ;


  streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		       << "   in run:  " << evt->getRunNumber() << std::endl ;
  
  
  _nEvt ++ ;
}



void LCTuple::check( LCEvent * evt ) { 
  // nothing to check here - could be used to fill checkplots in reconstruction processor
}


void LCTuple::end(){ 
  
  streamlog_out( MESSAGE ) << " processed " << _nEvt << " events in " << _nRun << " runs "
			   << std::endl ;

  delete  _mcpBranches  ;
  
}

