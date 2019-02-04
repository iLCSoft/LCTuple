#ifndef IsoLepBranches_h
#define IsoLepBranches_h 1

#include "JetBranches.h"
#include "RecoParticleBranches.h"
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
#include <IMPL/LCCollectionVec.h>

class TTree ;

namespace EVENT{
	class LCCollection ;
	class LCCEvent ;
}

class IsoLepBranches : public CollectionBranches {
	
public:
	
	IsoLepBranches(){} ;
	
	virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
	
	virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ; 
	
	virtual ~IsoLepBranches() {} ;
	
	
private:
	int   _niso {} ;
	int   npid {} ;
	
	int   isonpi[ LCT_ISOLEP_MAX ] {} ;
    int   isotyp[ LCT_ISOLEP_MAX ] {} ;
	float isomox[ LCT_ISOLEP_MAX ] {} ;
	float isomoy[ LCT_ISOLEP_MAX ] {} ;
	float isomoz[ LCT_ISOLEP_MAX ] {} ;
	float isoene[ LCT_ISOLEP_MAX ] {} ;
	float isocha[ LCT_ISOLEP_MAX ] {} ;
	float isoncl[ LCT_ISOLEP_MAX ] {} ;
	int   isoori[ LCT_ISOLEP_MAX ] {} ;
	int   pipdg [ LCT_PARTICLEID_MAX ] {} ;

	float _IsoEmiss {} ;
	float _IsoMass {} ;
	float _IsoEvis {} ; 
	float _IsoPxvis {} ;
	float _IsoPyvis {} ;
	float _IsoPzvis {} ;
	float _IsoPtvis {} ;
	float _IsoTheta {} ;
 	float _IsoCosTheta {} ;
 	float _IsoPtot {} ;
	
} ;

#endif


