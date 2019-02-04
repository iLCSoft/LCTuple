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
#include "MCParticleRemoveOverlayBranches.h"
#include "MCParticleFromRelationBranches.h"
#include "RecoParticleBranches.h"
#include "TrackBranches.h"
#include "ClusterBranches.h"
#include "SimTrackerHitBranches.h"
#include "SimCalorimeterHitBranches.h"
#include "CalorimeterHitBranches.h"
#include "LCRelationBranches.h"
#include "TrackerHitBranches.h"
#include "VertexBranches.h"
#include "JetBranches.h"
#include "IsoLepBranches.h"


using namespace lcio ;
using namespace marlin ;


namespace LCTuple_helper {
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

}
using namespace LCTuple_helper ;

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

  registerInputCollection( LCIO::MCPARTICLE,
			   "MCParticleRemoveOverlayCollection" ,
			   "Name of the MCParticle collection where the overlay is removed"  ,
			   _mcpRemoveOverlayColName ,
			   std::string("")
			   );

  registerProcessorParameter( "WriteMCParticleCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _mcpColWriteParameters ,
			      false
			      );
  
  registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			   "RecoParticleCollection" , 
			   "Name of the ReconstructedParticle collection"  ,
			   _recColName ,
			   std::string("")
			   );

  registerProcessorParameter( "WriteRecoParticleCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _recColWriteParameters ,
			      false
			      );

  registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			   "JetCollection" , 
			   "Name of the Jet collection"  ,
			   _jetColName ,
			   std::string("")
			   );

  registerProcessorParameter( "WriteJetCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _jetColWriteParameters ,
			      false
			      );
			      
  registerProcessorParameter( "JetCollectionExtraParameters" ,
                              "Switch to write out extra parameters calculated using information from Jet Finder",
			      _jetColExtraParameters ,
			      false
			      );
			      
  registerProcessorParameter( "JetCollectionTaggingParameters" ,
                              "Switch to write out jet parameters coming from LCFIPlus tagging processor",
			      _jetColTaggingParameters ,
			      false
			      );
			      
			     
registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			   "IsoLepCollection" , 
			   "Name of the IsoLep collection"  ,
			   _isolepColName ,
			   std::string("")
			   );

registerProcessorParameter( "WriteIsoLepCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _isolepColWriteParameters ,
			      false
			      );

  registerInputCollection( LCIO::VERTEX,
			   "VertexCollection" , 
			   "Name of the Vertex collection"  ,
			   _vtxColName ,
			   std::string("")
			   );
  
  registerProcessorParameter( "WriteVertexCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _vtxColWriteParameters ,
			      false
			      );

  registerInputCollection( LCIO::TRACK,
			   "TrackCollection" , 
			   "Name of the Track collection"  ,
			   _trkColName ,
			   std::string("")
			   );

  registerProcessorParameter( "WriteTrackCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _trkColWriteParameters ,
			      false
			      );

  registerInputCollection( LCIO::CLUSTER,
			   "ClusterCollection" , 
			   "Name of the Cluster collection"  ,
			   _cluColName ,
			   std::string("")
			   );

  registerProcessorParameter( "WriteClusterCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _cluColWriteParameters ,
			      false
			      );

  registerInputCollection( LCIO::SIMTRACKERHIT,
			   "SimTrackerHitCollection" , 
			   "Name of the SimTrackerHit collection"  ,
			   _sthColName ,
			   std::string("")
			   );

  registerInputCollection( LCIO::TRACKERHIT,
			   "TrackerHitCollection" , 
			   "Name of the TrackerHit collection"  ,
			   _trhColName ,
			   std::string("")
			   );
  
   registerProcessorParameter( "WriteSimTrackerHitCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _sthColWriteParameters ,
			      false
			      );

 registerProcessorParameter( "WriteTrackerHitCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _trhColWriteParameters ,
			      false
			      );

  registerInputCollection( LCIO::SIMCALORIMETERHIT,
			   "SimCalorimeterHitCollection" , 
			   "Name of the SimCalorimeterHit collection"  ,
			   _schColName ,
			   std::string("")
			   );

  registerInputCollection( LCIO::CALORIMETERHIT,
			   "CalorimeterHitCollection" , 
			   "Name of the CalorimeterHit collection"  ,
			   _cahColName ,
			   std::string("")
			   );

  registerProcessorParameter( "WriteSimCalorimeterHitCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _schColWriteParameters ,
			      false
			      );
  

  registerProcessorParameter( "WriteCalorimeterHitCollectionParameters" ,
                              "Switch to write out collection parameters",
			      _cahColWriteParameters ,
			      false
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

  StringVec pidBranchDefinition = {"Algorithm:TOFEstimators50ps", "tof50",
				   "TOFFirstHit", "TOFClosestHits", "TOFClosestHitsError", "TOFFlightLength", "TOFLastTrkHit", "TOFLastTrkHitFlightLength", 
				   "fh",          "ch",             "che",                 "len",             "th",            "thl"  } ;

  registerProcessorParameter( "PIDBranchDefinition" , 
			      "Definition of PID branches added to the ReconstructedParticle branches - for every algorithm:  "
			      "Algorithm:Name branchPrefix Parameter0 branch0  Parameter1 branch1  Parameter2 branch2 ..."  ,
			      _pidBranchDefinition ,
			      pidBranchDefinition
			      );

  registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
  			   "PFOwithRelationCollection" ,
  			   "Name of the PFO collection with Relation"  ,
  			   _pfoRelName ,
  			   std::string("")
  	  	  	   );

  registerInputCollection( LCIO::LCRELATION,
  			    "LCRelationwithPFOCollections" ,
  			    "Names of LCRelation collections of PFO"  ,
  			    _relName ,
  			    std::string("")
  	  	  	  	);


  
}

//============================================================================================================================

void LCTuple::init() { 
  
  streamlog_out(DEBUG) << "   init called  - create TTree with name : "  <<  name().c_str()  << " with columnwise ntuple with LCIO data" << std::endl ;
  
  // usually a good idea to
  printParameters() ;
  
  _nRun = 0 ;
  _nEvt = 0 ;
  
  _tree = new TTree( name().c_str() , "columnwise ntuple with LCIO data") ;
  
  //=====================================================
  //    initialize the branches 
  
  _evtBranches =  0 ;
  _mcpBranches =  0 ;
  _mcpremoveoverlayBranches =  0 ;
  _recBranches =  0 ; 
  _jetBranches =  0 ;
  _isolepBranches = 0;
  _trkBranches =  0 ;
  _cluBranches =  0 ; 
  _sthBranches =  0 ;
  _trhBranches =  0 ;
  _schBranches =  0 ;
  _cahBranches =  0 ;
  _vtxBranches =  0 ;
  _mcRelBranches = 0 ;

  
  _evtBranches =  new EventBranches ;
  _evtBranches->initBranches( _tree ) ;
  
  
  if( _mcpColName.size() )  {
    _mcpBranches =  new MCParticleBranches ;
    _mcpBranches->writeParameters(_mcpColWriteParameters);
    _mcpBranches->initBranches( _tree ) ;
  }
  
  if( _mcpRemoveOverlayColName.size() )  {
    _mcpremoveoverlayBranches =  new MCParticleRemoveOverlayBranches ;
    _mcpremoveoverlayBranches->writeParameters(_mcpColWriteParameters);
    _mcpremoveoverlayBranches->initBranches( _tree ) ;
  }

  if( _recColName.size() ) {
    _recBranches =  new RecoParticleBranches ;
    _recBranches->writeParameters(_recColWriteParameters);
    _recBranches->initBranches( _tree ) ;

    decodePIDBranchDefinitions() ;

    for( auto d : _pidBranchDefs ) {

      _pidBranchesVec.push_back( new PIDBranches ) ;
      PIDBranches* pidb = _pidBranchesVec.back() ;
    
      pidb->defineBranches( d.algoName, d.pNames, d.bNames ) ;
      pidb->initBranches( _tree , d.prefix ) ;
    }
  }
  

  if( _jetColName.size() ) {
    _jetBranches = new JetBranches ;
    _jetBranches->writeParameters(_jetColWriteParameters);
	_jetBranches->writeExtraParameters(_jetColExtraParameters); /* pass the value to JetBranches */
	_jetBranches->writeTaggingParameters(_jetColTaggingParameters); /* pass the value to JetBranches */
    _jetBranches->initBranches( _tree );
  }

  if( _isolepColName.size() ) {
    _isolepBranches = new IsoLepBranches ;
    _isolepBranches->writeParameters(_isolepColWriteParameters);
    _isolepBranches->initBranches( _tree ) ;
  }

  if( _trkColName.size() ) {
    _trkBranches =  new TrackBranches ;
    _trkBranches->writeParameters(_trkColWriteParameters);
    _trkBranches->initBranches( _tree ) ;
  }
  
  if( _cluColName.size() ) {
    _cluBranches =  new ClusterBranches ;
    _cluBranches->writeParameters(_cluColWriteParameters);
    _cluBranches->initBranches( _tree ) ;
  }
  
  if( _sthColName.size() ) {
    _sthBranches =  new SimTrackerHitBranches ;
    _sthBranches->writeParameters(_sthColWriteParameters);
    _sthBranches->initBranches( _tree ) ;
  }

  if( _trhColName.size() ) {
    _trhBranches =  new TrackerHitBranches ;
    _trhBranches->writeParameters(_trhColWriteParameters);
    _trhBranches->initBranches( _tree ) ;
  }
  
  if( _schColName.size() ) {
    _schBranches =  new SimCalorimeterHitBranches ;
    _schBranches->writeParameters(_schColWriteParameters);
    _schBranches->initBranches( _tree ) ;
  }

  if( _cahColName.size() ) {
    _cahBranches =  new CalorimeterHitBranches ;
    _cahBranches->writeParameters(_cahColWriteParameters);
    _cahBranches->initBranches( _tree ) ;
  }

  if( _vtxColName.size() ) {
    _vtxBranches =  new VertexBranches ;
    _vtxBranches->writeParameters(_vtxColWriteParameters);
    _vtxBranches->initBranches( _tree ) ;
  }

  if( _pfoRelName.size() && _relName.size() )  {
      _mcRelBranches =  new MCParticleFromRelationBranches ;
      _mcRelBranches->writeParameters(_mcpColWriteParameters);
      _mcRelBranches->initBranches( _tree ) ;
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
streamlog_out(DEBUG) << "  okay!  " << std::endl ;
  }

}
//============================================================================================================================


void LCTuple::processRunHeader( LCRunHeader* /*run*/) { 
  _nRun++ ;
} 


//============================================================================================================================

void LCTuple::processEvent( LCEvent * evt ) { 
  
  //=====================================================
  // get the available collections from the event
  

  LCCollection* mcpCol =  getCollection ( evt , _mcpColName ) ;
  
  LCCollection* mcpRemoveOverlayCol =  getCollection ( evt , _mcpRemoveOverlayColName ) ;

  LCCollection* recCol =  getCollection ( evt , _recColName ) ;

  LCCollection* jetCol =  getCollection ( evt , _jetColName ) ;
  
  LCCollection* isolepCol =  getCollection ( evt , _isolepColName ) ;

  LCCollection* trkCol =  getCollection ( evt , _trkColName ) ;

  LCCollection* cluCol =  getCollection ( evt , _cluColName ) ;

  LCCollection* sthCol =  getCollection ( evt , _sthColName ) ;

  LCCollection* trhCol =  getCollection ( evt , _trhColName ) ;

  LCCollection* schCol =  getCollection ( evt , _schColName ) ;

  LCCollection* cahCol =  getCollection ( evt , _cahColName ) ;

  LCCollection* vtxCol =  getCollection ( evt , _vtxColName ) ;

  LCCollection* relCol =  getCollection ( evt , _relName ) ;

  LCCollection* pfoRelCol =  getCollection ( evt , _pfoRelName ) ;


  unsigned  nRel = _relColNames.size() ;
  
  std::vector<LCCollection*> relCols( nRel ) ;
  
  for( unsigned i=0; i < nRel ; ++i) {
    
    relCols[i]  =  getCollection ( evt , _relColNames[i] ) ;
  }
  
  //=====================================================
  //     add the collection index to the objects 

  addIndexToCollection( mcpCol );

  addIndexToCollection( mcpRemoveOverlayCol ) ;

  addIndexToCollection( recCol ) ;

  addIndexToCollection( jetCol ) ;
  
  addIndexToCollection( isolepCol ) ; 

  addIndexToCollection( trkCol ) ;

  addIndexToCollection( cluCol ) ;

  addIndexToCollection( vtxCol ) ;

  addIndexToCollection( relCol ) ;

  addIndexToCollection( pfoRelCol ) ;


  //================================================
  //    fill the ntuple arrays 
  
  _evtBranches->fill( 0 , evt ) ;
  
  if( mcpCol ) _mcpBranches->fill( mcpCol , evt ) ;
  
  if( mcpRemoveOverlayCol ) _mcpremoveoverlayBranches->fill( mcpRemoveOverlayCol , evt ) ;

  if( recCol ) {
    _recBranches->fill( recCol , evt ) ;

    for( auto pidb : _pidBranchesVec ) pidb->fill( recCol , evt ) ;
  }

  if( jetCol ) _jetBranches->fill (jetCol , evt ) ;		// @ebrahimi:  removed: && jetCol->getNumberOfElements()==2
  
  if( isolepCol ) _isolepBranches->fill (isolepCol , evt ) ;
  
  if( trkCol ) _trkBranches->fill( trkCol , evt ) ;
  
  if( cluCol ) _cluBranches->fill( cluCol , evt ) ;
  
  if( sthCol ) _sthBranches->fill( sthCol , evt ) ;

  if( trhCol ) _trhBranches->fill( trhCol , evt ) ;
  
  if( schCol ) _schBranches->fill( schCol , evt ) ;
  
  if( cahCol ) _cahBranches->fill( cahCol , evt ) ;
  
  if( vtxCol ) _vtxBranches->fill( vtxCol , evt ) ;

  if( relCol && pfoRelCol ) _mcRelBranches->fill( relCol, pfoRelCol , evt ) ;


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

void LCTuple::check( LCEvent * /*evt*/ ) { 
  // nothing to check here - could be used to fill checkplots in reconstruction processor
}


//============================================================================================================================

void LCTuple::end(){ 
  
  streamlog_out( MESSAGE ) << " processed " << _nEvt << " events in " << _nRun << " runs "
			   << std::endl ;

  delete _evtBranches ;
  delete _mcpBranches ;
  delete _mcpremoveoverlayBranches ;
  delete _recBranches ; 
  delete _jetBranches ;
  delete _isolepBranches ; 
  delete _trkBranches ; 
  delete _vtxBranches ; 
  delete _mcRelBranches ;
  
  for( auto pidb : _pidBranchesVec ) delete pidb ;
  
  for(unsigned i=0 , nRel =_relBranchesVec.size() ; i <nRel ; 
      delete _relBranchesVec[i++] )  ;
  
}



void LCTuple::decodePIDBranchDefinitions(){

  std::vector<int> algoStart ;
  const std::string algoString("Algorithm:" ) ; 

  if( !parameterSet( "PIDBranchDefinition") )
    return ;

  // count the algorithms
  for(unsigned i=0,N=_pidBranchDefinition.size();i<N;++i){
    if( _pidBranchDefinition[i].find(algoString) != std::string::npos ){
      algoStart.push_back(i) ;
    }
  }
  int algoNum = algoStart.size();
  _pidBranchDefs.resize( algoNum ) ;

  algoStart.push_back( _pidBranchDefinition.size() ) ; // add one start index after end of definition string

  for(unsigned i=0,N=_pidBranchDefs.size();i<N;++i){

    PIDBranchDef& d = _pidBranchDefs[i] ;
    int index = algoStart[i] ;

    d.algoName= _pidBranchDefinition[index].substr( algoString.size(),_pidBranchDefinition[index].size() ) ;
    ++index ;
    d.prefix  = _pidBranchDefinition[index++] ;


    streamlog_out( DEBUG5 ) << " found PID algorithm : " << d.algoName
			    << " branches will be created with prefix: " <<  d.prefix
			    << std::endl ;


    int nParam =  (algoStart[i+1]-index) / 2 ;

    streamlog_out( DEBUG5 ) << "       parameters: " ;

    for(int j=0;j<nParam;++j){
      d.pNames.push_back( _pidBranchDefinition[index++] ) ;
      streamlog_out( DEBUG5 ) << d.pNames.back() << " " ;
    }
    streamlog_out( DEBUG5 ) << std::endl ;

    streamlog_out( DEBUG5 ) << "       branch names: " ;

    for(int j=0;j<nParam;++j){
      d.bNames.push_back( _pidBranchDefinition[index++] ) ;
      streamlog_out( DEBUG5 ) << d.bNames.back() << " " ;
    }
    streamlog_out( DEBUG5 ) << std::endl ;
  } 
}
