#include "LCTuple.h"

#include "TTree.h"

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"

#include "MCParticleBranches.h"



using namespace lcio ;
using namespace marlin ;


LCTuple aLCTuple ;


LCTuple::LCTuple() : Processor("LCTuple") {
  
  // modify processor description
  _description = "LCTuple creates a ROOT TTRee with a column wise ntuple from LCIO collections ...." ;
  
  
  // register steering parameters: name, description, class-variable, default value
  registerInputCollection( LCIO::MCPARTICLE,
			   "CollectionName" , 
			   "Name of the MCParticle collection"  ,
			   _mcpColName ,
			   std::string("MCParticle")
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

}


void LCTuple::processRunHeader( LCRunHeader* run) { 

    _nRun++ ;
} 



void LCTuple::processEvent( LCEvent * evt ) { 


  if( isFirstEvent() ) { 
    
    //=====================================================
    //    initialize the branches 

    _mcpBranches->initBranches( _tree ) ;
  }

  //=====================================================
  //     add the collection index to the objects 
  
  LCCollection* mcpCol = evt->getCollection( _mcpColName ) ;
  
  int nmc  = mcpCol->getNumberOfElements() ;

  for(int i=0 ; i < nmc ; ++i){
    
    lcio::MCParticle* mcp = static_cast<lcio::MCParticle*>( mcpCol->getElementAt(i) ) ;
    
    mcp->ext<CollIndex>() = i + 1 ;
  }  


  //================================================
  //    fill the ntuple arrays 
  
  _mcpBranches->fill( mcpCol , evt ) ;




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

