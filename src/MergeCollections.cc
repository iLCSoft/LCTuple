#include "MergeCollections.h"

#include <IMPL/LCCollectionVec.h>
#include <IMPL/LCParametersImpl.h>

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


MergeCollections aMergeCollections ;


MergeCollections::MergeCollections() : Processor("MergeCollections") {
  
  // modify processor description
  _description = "MergeCollections creates a transient subset collection that merges all input collections " ;

  
  StringVec colNames ;
  registerProcessorParameter( "InputCollections" , 
			      "Names of all input collections" ,
			      _inColNames ,
			      colNames
			      );
  
  registerProcessorParameter( "OutputCollection" , 
			      "Name of output collection" ,
			      _outColName ,
			      std::string("MergedCollection")
			      );
  
  
}

//============================================================================================================================

void MergeCollections::init() { 
  streamlog_out(DEBUG) << "   init called  " << std::endl ;

  // usually a good idea to
  printParameters() ;

  _nRun = 0 ;
  _nEvt = 0 ;
}
//============================================================================================================================


void MergeCollections::processRunHeader( LCRunHeader* run) { 
  _nRun++ ;
}


//============================================================================================================================

void MergeCollections::processEvent( LCEvent * evt ) { 
  StringVec colNamesPresent;
  IntVec colNElements;
  IntVec colNIntParam;
  IntVec colNFloatParam;
  IntVec colNStringParam;

  unsigned nCol = _inColNames.size() ;

  //--- copy existing collections to a vector first
  std::vector<LCCollection*> colVec ;

  for( unsigned i=0; i < nCol ; ++i) {
    LCCollection* col  =  getCollection ( evt , _inColNames[i] ) ;

    if( col != 0 ){ 
      colVec.push_back( col ) ;
      colNamesPresent.push_back(_inColNames[i]);
    } else {
      streamlog_out(DEBUG2) << " input collection missing : " << _inColNames[i] << std::endl ;
    }
  }

  // ---- now loop over existing collections 
  LCCollectionVec* outCol = 0 ;
  nCol = colVec.size() ;

  for( unsigned k=0; k < nCol ; ++k) {
    LCCollection* col  =  colVec[k] ;
    if( k == 0 ){
      // copy collection flags from first collections
      outCol = new LCCollectionVec( col->getTypeName() )  ;
      outCol->setFlag( col->getFlag() ) ;
    }
    int nEle = col->getNumberOfElements() ;
    for(int j=0; j < nEle ; ++j){
      outCol->addElement(  col->getElementAt(j) ) ;
    }

    int intParams = 0;
    int floatParams = 0;
    int stringParams = 0;

    StringVec intKeys ;
    int nIntParameters = col->getParameters().getIntKeys( intKeys ).size() ;
    for(int i=0; i< nIntParameters ; i++ ){
      IntVec intVec ;
      col->getParameters().getIntVals(  intKeys[i], intVec ) ;
      const std::string newIntKey = colNamesPresent[k]+"_"+intKeys[i];
      outCol->parameters().setValues(newIntKey,intVec);
      intParams++;
    }

    StringVec floatKeys ;
    int nFloatParameters = col->getParameters().getFloatKeys( floatKeys ).size() ;
    for(int i=0; i< nFloatParameters ; i++ ){
      FloatVec floatVec ;
      col->getParameters().getFloatVals(  floatKeys[i], floatVec ) ;
      const std::string newFloatKey = colNamesPresent[k]+"_"+floatKeys[i];
      outCol->parameters().setValues(newFloatKey,floatVec);
      floatParams++;
    }

    StringVec stringKeys ;
    int nStringParameters = col->getParameters().getStringKeys( stringKeys ).size() ;
    for(int i=0; i< nStringParameters ; i++ ){
      StringVec stringVec ;
      col->getParameters().getStringVals(  stringKeys[i], stringVec ) ;
      const std::string newStringKey = colNamesPresent[k]+"_"+stringKeys[i];
      outCol->parameters().setValues(newStringKey,stringVec);
      stringParams++;
    }
    colNElements.push_back(nEle);
    colNIntParam.push_back(intParams);
    colNFloatParam.push_back(floatParams);
    colNStringParam.push_back(stringParams);
  }

  outCol->parameters().setValues("MergedCollection_InputCollections",colNamesPresent);
  outCol->parameters().setValues("MergedCollection_NElements",colNElements);
  outCol->parameters().setValues("MergedCollection_NIntParameters",colNIntParam);
  outCol->parameters().setValues("MergedCollection_NFloatParameters",colNFloatParam);
  outCol->parameters().setValues("MergedCollection_NStringParameters",colNStringParam);

  if( outCol ) {
    outCol->setTransient( false ) ;
    outCol->setSubset( true ) ;
    evt->addCollection( outCol, _outColName   ) ;
  }

  streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		       << "   in run:  "          << evt->getRunNumber()   << std::endl ;

  _nEvt ++ ;
}

//============================================================================================================================

void MergeCollections::check( LCEvent * evt ) { 
  // nothing to check here - could be used to fill checkplots in reconstruction processor
}


//============================================================================================================================

void MergeCollections::end(){
  streamlog_out( MESSAGE ) << " processed " << _nEvt << " events in " << _nRun << " runs "
			   << std::endl ;
}

