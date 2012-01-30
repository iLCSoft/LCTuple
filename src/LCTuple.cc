#include "LCTuple.h"

#include "TTree.h"

#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/LCRelation.h>
#include <IMPL/LCCollectionVec.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"

#include "EventBranches.h"
#include "MCParticleBranches.h"
#include "RecoParticleBranches.h"
#include "TrackBranches.h"
#include "ClusterBranches.h"
#include "SimTrackerHitBranches.h"
#include "SimCalorimeterHitBranches.h"
#include "LCRelationBranches.h"
#include "VertexBranches.h"



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

/** helper for setting the index extension */
inline void addIndexToCollection( lcio::LCCollection* col ){
  
  if( col == 0 ) {  
    return ; 
  }
    
  for(int i=0, n  = col->getNumberOfElements() ; i < n; ++i ){
    
    col->getElementAt( i )->ext<CollIndex>() = i + 1 ; 
  }  
}
//------------------------------------------------------------------------------------------------


LCTuple aLCTuple ;


LCTuple::LCTuple() : Processor("LCTuple") {
  
  // modify processor description
  _description = "LCTuple creates a ROOT TTRee with a column wise ntuple from LCIO collections ...." ;
  
  
  // register steering parameters: name, description, class-variable, default value
  registerInputCollection( LCIO::MCPARTICLE,
			   "MCParticleCollection" , 
			   "Name of the MCParticle collection"  ,
			   _mcpColName ,
			   std::string("")
			   );
  
  registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			   "RecoParticleCollection" , 
			   "Name of the ReconstructedParticle collection"  ,
			   _recColName ,
			   std::string("")
			   );

  registerInputCollection( LCIO::VERTEX,
			   "VertexCollection" , 
			   "Name of the Vertex collection"  ,
			   _vtxColName ,
			   std::string("")
			   );
  
  registerInputCollection( LCIO::TRACK,
			   "TrackCollection" , 
			   "Name of the Track collection"  ,
			   _trkColName ,
			   std::string("")
			   );

  registerInputCollection( LCIO::CLUSTER,
			   "ClusterCollection" , 
			   "Name of the Cluster collection"  ,
			   _cluColName ,
			   std::string("")
			   );

  registerInputCollection( LCIO::SIMTRACKERHIT,
			   "SimTrackerHitCollection" , 
			   "Name of the SimTrackerHit collection"  ,
			   _sthColName ,
			   std::string("")
			   );
  
  registerInputCollection( LCIO::SIMCALORIMETERHIT,
			   "SimCalorimeterHitCollection" , 
			   "Name of the SimCalorimeterHit collection"  ,
			   _schColName ,
			   std::string("")
			   );
  
  
  StringVec relColNames ;
  registerInputCollections( LCIO::LCRELATION,
			    "LCRelationCollections" , 
			    "Names of LCRelation collections - need parallel prefix names in RelPrefixes"  ,
			    _relColNames ,
			    relColNames
			    );
  
  StringVec relPrefixes ;
  registerProcessorParameter( "LCRelationPrefixes" , 
			      " Names of prefixes for variables from LCRelation collections - "
			      "needs to be parallel to LCRelationCollections (one prefix per collection)"  ,
			      _relPrefixes ,
			      relPrefixes
			      );
  
  
}

//============================================================================================================================

void LCTuple::init() { 
  
  streamlog_out(DEBUG) << "   init called  " << std::endl ;
  
  // usually a good idea to
  printParameters() ;
  
  _nRun = 0 ;
  _nEvt = 0 ;
  
  _tree = new TTree( "LCTuple" , "columnwise ntuple with LCIO data") ;
  
  //=====================================================
  //    initialize the branches 
  
  _evtBranches =  0 ;
  _mcpBranches =  0 ;
  _recBranches =  0 ; 
  _trkBranches =  0 ;
  _cluBranches =  0 ; 
  _sthBranches =  0 ;
  _schBranches =  0 ;
  _vtxBranches =  0 ;
  
  _evtBranches =  new EventBranches ;
  _evtBranches->initBranches( _tree ) ;
  
  
  if( _mcpColName.size() )  {
    _mcpBranches =  new MCParticleBranches ;
    _mcpBranches->initBranches( _tree ) ;
  }
  
  if( _recColName.size() ) {
    _recBranches =  new RecoParticleBranches ;
    _recBranches->initBranches( _tree ) ;
  }

  if( _trkColName.size() ) {
    _trkBranches =  new TrackBranches ;
    _trkBranches->initBranches( _tree ) ;
  }
  
  if( _cluColName.size() ) {
    _cluBranches =  new ClusterBranches ;
    _cluBranches->initBranches( _tree ) ;
  }
  
  if( _sthColName.size() ) {
    _sthBranches =  new SimTrackerHitBranches ;
    _sthBranches->initBranches( _tree ) ;
  }
  
  if( _schColName.size() ) {
    _schBranches =  new SimCalorimeterHitBranches ;
    _schBranches->initBranches( _tree ) ;
  }

  if( _vtxColName.size() ) {
    _vtxBranches =  new VertexBranches ;
    _vtxBranches->initBranches( _tree ) ;
  }

  
  unsigned nRel =  _relColNames.size()  ;
  
  if( nRel != _relPrefixes.size() ){
    
    std::stringstream ss ;
    ss  << " collection parameters LCRelationCollections and LCRelationPrefixes don't have the same length : " 
	<<   nRel  << " != " <<  _relPrefixes.size()
	<< "\n  specify one prefix for every LCRelation collection !" ;
    
    throw Exception( ss.str() ) ;
  }
  
  _relBranchesVec.resize( nRel ) ;
  
  for(unsigned i=0 ; i <nRel ; ++i) {
    
    streamlog_out(DEBUG) << " initialize relation branches for collection " << _relColNames[i] << " - with prefix \"" 
			 << _relPrefixes[i] << "\"" << std::endl ;  
    
    _relBranchesVec[i] =  new LCRelationBranches ;
    _relBranchesVec[i]->initBranches( _tree ,  _relPrefixes[i] ) ;
  }
  
}
//============================================================================================================================


void LCTuple::processRunHeader( LCRunHeader* run) { 
  
  _nRun++ ;
} 


//============================================================================================================================

void LCTuple::processEvent( LCEvent * evt ) { 
  
  
  
  //=====================================================
  // get the available collections from the event
  
  LCCollection* mcpCol =  getCollection ( evt , _mcpColName ) ;
  
  LCCollection* recCol =  getCollection ( evt , _recColName ) ;

  LCCollection* trkCol =  getCollection ( evt , _trkColName ) ;

  LCCollection* cluCol =  getCollection ( evt , _cluColName ) ;

  LCCollection* sthCol =  getCollection ( evt , _sthColName ) ;

  LCCollection* schCol =  getCollection ( evt , _schColName ) ;

  LCCollection* vtxCol =  getCollection ( evt , _vtxColName ) ;

  unsigned  nRel = _relColNames.size() ;
  
  std::vector<LCCollection*> relCols( nRel ) ;
  
  for( unsigned i=0; i < nRel ; ++i) {
    
    relCols[i]  =  getCollection ( evt , _relColNames[i] ) ;
  }
  
  //=====================================================
  //     add the collection index to the objects 

  addIndexToCollection( mcpCol ) ;

  addIndexToCollection( recCol ) ;

  addIndexToCollection( trkCol ) ;

  addIndexToCollection( cluCol ) ;

  addIndexToCollection( vtxCol ) ;

  //================================================
  //    fill the ntuple arrays 
  
  _evtBranches->fill( 0 , evt ) ;
  
  if( mcpCol ) _mcpBranches->fill( mcpCol , evt ) ;
  
  if( recCol ) _recBranches->fill( recCol , evt ) ;
  
  if( trkCol ) _trkBranches->fill( trkCol , evt ) ;
  
  if( cluCol ) _cluBranches->fill( cluCol , evt ) ;
  
  if( sthCol ) _sthBranches->fill( sthCol , evt ) ;
  
  if( schCol ) _schBranches->fill( schCol , evt ) ;
  
  if( vtxCol ) _vtxBranches->fill( vtxCol , evt ) ;

  for( unsigned i=0; i < nRel ; ++i) {

    if( relCols[i] == 0 )
      continue ;

    streamlog_out(DEBUG) << " filling branches for relation collection :" << _relColNames[i] 
			 << " at " << relCols[i] << std::endl ; 

    _relBranchesVec[i]->fill( relCols[i]  , evt ) ;
  }

  //================================================
  
  _tree->Fill() ;
  
  //================================================

  streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		       << "   in run:  "          << evt->getRunNumber()   << std::endl ;
  
  
  _nEvt ++ ;
}


//============================================================================================================================

void LCTuple::check( LCEvent * evt ) { 
  // nothing to check here - could be used to fill checkplots in reconstruction processor
}


//============================================================================================================================

void LCTuple::end(){ 
  
  streamlog_out( MESSAGE ) << " processed " << _nEvt << " events in " << _nRun << " runs "
			   << std::endl ;

  delete _evtBranches ;
  delete _mcpBranches ;
  delete _recBranches ; 
  delete _trkBranches ; 
  delete _vtxBranches ; 
  
  for(unsigned i=0 , nRel =_relBranchesVec.size() ; i <nRel ; 
      delete _relBranchesVec[i++] )  ;
  
}

