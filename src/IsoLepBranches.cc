#include "IsoLepBranches.h"
#include "RecoParticleBranches.h"
#include "JetBranches.h"
#include "MCParticleBranches.h"
#include "ClusterBranches.h"
#include "CollectionBranches.h"
#include "CreateRecoRelations.h"
#include "EventBranches.h"
#include "LCRelationBranches.h"
#include "LCTuple.h"
#include "LCTupleConf.h"
#include "MergeCollections.h"
#include "SimCalorimeterHitBranches.h"
#include "SimTrackerHitBranches.h"
#include "TrackBranches.h"
#include "VertexBranches.h"

#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include <IMPL/LCCollectionVec.h>
#include "TMath.h"
#include "TTree.h"
#include "TVector3.h"
#include "TLorentzVector.h"

void IsoLepBranches::initBranches( TTree* tree, const std::string& pre)  
{

  streamlog_out(DEBUG) << "IsoLepBranches::initBranches - start" << std::endl;
    
  if( tree == 0 ) throw lcio::Exception("  IsoLepBranches::initBranches - invalid tree pointer !!! " ) ; 
    
  if (_writeparameters) CollectionBranches::initBranches(tree, (pre+"iso").c_str());

  tree->Branch( (pre+"niso"    )   .c_str() , &_niso     ,    (pre+"niso/I"    )     .c_str() ) ;
  tree->Branch( (pre+"IsoEvis" )   .c_str() , &_IsoEvis  ,    (pre+"IsoEvis/F" )     .c_str() ) ;
  tree->Branch( (pre+"IsoPxvis")   .c_str() , &_IsoPxvis ,    (pre+"IsoPxvis/F")     .c_str() ) ;
  tree->Branch( (pre+"IsoPyvis")   .c_str() , &_IsoPyvis ,    (pre+"IsoPyvis/F")     .c_str() ) ;
  tree->Branch( (pre+"IsoPzvis")   .c_str() , &_IsoPzvis ,    (pre+"IsoPzvis/F")     .c_str() ) ;
  tree->Branch( (pre+"IsoPtvis")   .c_str() , &_IsoPtvis ,    (pre+"IsoPtvis/F")     .c_str() ) ;
  tree->Branch( (pre+"IsoTheta")   .c_str() , &_IsoTheta ,    (pre+"IsoTheta/F")     .c_str() ) ;
  tree->Branch( (pre+"IsoCosTheta").c_str() , &_IsoCosTheta , (pre+"IsoCosTheta/F")  .c_str() ) ;  
  tree->Branch( (pre+"IsoEmiss")   .c_str() , &_IsoEmiss ,    (pre+"IsoEmiss/F")     .c_str() ) ; 
  tree->Branch( (pre+"IsoMass" )   .c_str() , &_IsoMass  ,    (pre+"IsoMass/F" )     .c_str() ) ;
  tree->Branch( (pre+"IsoPtot")    .c_str() , &_IsoPtot ,     (pre+"IsoPtot/F" )     .c_str() ) ;
  
    streamlog_out(DEBUG) << "IsoLepBranches::initBranches - end"  << std:: endl;
}

void IsoLepBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt )  
{
            
	streamlog_out(DEBUG) << "IsoLepBranches::fill" << std::endl;
	    
	if( !col ) return ;

	if( col->getTypeName() != lcio::LCIO::RECONSTRUCTEDPARTICLE )
	{    	
		std::string exStr("IsoLepBranches::fill: invalid collection type : " ) ;
		throw EVENT::Exception( exStr + col->getTypeName() ) ; 
	}

	if (_writeparameters) CollectionBranches::fill(col, evt);

	_niso = col->getNumberOfElements() ;

	streamlog_out(DEBUG) << "niso: " << _niso << '\n' ;

	std::vector<lcio::ParticleID*> pidV ;

	pidV.reserve( col->getNumberOfElements() * 4 ) ;

	double   Etot = evt->getParameters().getFloatVal("Energy");
//	int Etot = 500 ;
	_IsoEvis    = 0 ; 
	_IsoPxvis   = 0 ;
	_IsoPyvis   = 0 ;
	_IsoPzvis   = 0 ;
	_IsoPtvis   = 0 ;
	_IsoTheta   = 0 ;
	_IsoCosTheta= 0 ;
	_IsoEmiss   = 0 ;
	_IsoMass    = 0 ;
	_IsoPtot    = 0 ;
	

	for( int i=0 ; i < _niso ; ++i )
	  {

	    lcio::ReconstructedParticle* isolep = static_cast<lcio::ReconstructedParticle*>( col->getElementAt(i) ) ;
	    
	    const EVENT::ParticleIDVec & pids = isolep->getParticleIDs() ;
	    
	    for(int j=0, npids = pids.size() ; j<npids ; ++j)
	    {
	      pidV.push_back( pids[j] ) ;
	      
	      pids[j]->ext<CollIndex>() =  pidV.size() ;
	    }

	    isotyp[ i ] = isolep->getType() ;
	    isomox[ i ] = isolep->getMomentum()[0] ;
	    isomoy[ i ] = isolep->getMomentum()[1] ;
	    isomoz[ i ] = isolep->getMomentum()[2] ;
	    isoene[ i ] = isolep->getEnergy() ;
	    isocha[ i ] = isolep->getCharge() ;
	    isoori[ i ] = isolep->ext<CollID>();
	    isoncl[ i ] = isolep->getClusters().size() ;
	    
	    _IsoEvis +=  isoene[ i ] ;
	    _IsoPxvis += isomox[ i ] ;
	    _IsoPyvis += isomoy[ i ] ;
	    _IsoPzvis += isomoz[ i ] ; 
  		
	}

	  _IsoPtot = sqrt(pow(_IsoPxvis,2)+pow(_IsoPyvis,2)+pow(_IsoPzvis,2)) ;
	  _IsoPtvis= sqrt(pow(_IsoPxvis,2)+pow(_IsoPyvis,2));
	  _IsoTheta = atan(sqrt(_IsoPxvis*_IsoPxvis + _IsoPyvis*_IsoPyvis) / _IsoPzvis) ;
	  _IsoCosTheta = _IsoPzvis/(sqrt(pow(_IsoPxvis,2)+pow(_IsoPyvis,2)+pow(_IsoPzvis,2))) ;
	  _IsoMass = sqrt(_IsoEvis*_IsoEvis - _IsoPxvis*_IsoPxvis - _IsoPyvis*_IsoPyvis - _IsoPzvis*_IsoPzvis) ;
	  _IsoEmiss += Etot - _IsoEvis ;
}
