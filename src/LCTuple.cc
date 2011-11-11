#include "LCTuple.h"

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"


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
			   _colName ,
			   std::string("MCParticle")
			   );
}



void LCTuple::init() { 

    streamlog_out(DEBUG) << "   init called  " << std::endl ;

    // usually a good idea to
    printParameters() ;

    _nRun = 0 ;
    _nEvt = 0 ;

}


void LCTuple::processRunHeader( LCRunHeader* run) { 

    _nRun++ ;
} 



void LCTuple::processEvent( LCEvent * evt ) { 


  if( isFirstEvent() ) { 
    
  }
  LCCollection* col = evt->getCollection( _colName ) ;
  
  
  // Alternativelly if you do not want Marlin to exit in case of a non-existing collection
  // use the following (commented out) code:
  //LCCollection* col = NULL;
  //try{
  //    col = evt->getCollection( _colName );
  //}
  //catch( lcio::DataNotAvailableException e )
  //{
  //    streamlog_out(WARNING) << _colName << " collection not available" << std::endl;
  //    col = NULL;
  //}
  
  // this will only be entered if the collection is available
  if( col != NULL ){
    
    int nMCP = col->getNumberOfElements()  ;
    
    for(int i=0; i< nMCP ; i++){
      
      MCParticle* p = dynamic_cast<MCParticle*>( col->getElementAt( i ) ) ;
      
      // fill histogram from LCIO data :
      //      hMCPEnergy->fill( p->getEnergy() ) ;

    } 
  }
  
  
  
  //-- note: this will not be printed if compiled w/o MARLINDEBUG=1 !
  
  streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		       << "   in run:  " << evt->getRunNumber() << std::endl ;
  
  
  
  _nEvt ++ ;
}



void LCTuple::check( LCEvent * evt ) { 
  // nothing to check here - could be used to fill checkplots in reconstruction processor
}


void LCTuple::end(){ 
  
  //   std::cout << "LCTuple::end()  " << name() 
  // 	    << " processed " << _nEvt << " events in " << _nRun << " runs "
  // 	    << std::endl ;
  
}

