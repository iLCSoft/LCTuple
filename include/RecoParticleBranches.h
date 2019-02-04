#ifndef RecoParticleBranches_h
#define RecoParticleBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** RecoParticleBranches holds branches created from a ReconstructedParticle collection
 * 
 * @author F. Gaede, DESY
 * @version $Id$
 */

class RecoParticleBranches : public CollectionBranches {
  
public:
  
  RecoParticleBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~RecoParticleBranches() {} ;
  

private:
  
  int    _nrec  {} ;
  int    _rcori[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rccid[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rctyp[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rccov[ LCT_RECOPARTICLE_MAX ][10]  {} ;
  float  _rcrpx[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rcrpy[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rcrpz[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rcgpi[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rcpiu[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rcnpi[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rcfpi[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rcmox[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rcmoy[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rcmoz[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rcmas[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rcene[ LCT_RECOPARTICLE_MAX ]  {} ;
  float  _rccha[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rcntr[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rcncl[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rcnrp[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rcftr[ LCT_RECOPARTICLE_MAX ]  {} ;

  int    _rcvts[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rcvte[ LCT_RECOPARTICLE_MAX ]  {} ;
  int    _rccom[ LCT_RECOPARTICLE_MAX ]  {} ;

  int    _npid    {} ;
  int    _pityp[ LCT_PARTICLEID_MAX ]  {} ;
  int    _pipdg[ LCT_PARTICLEID_MAX ]  {} ;
  float  _pillh[ LCT_PARTICLEID_MAX ]  {} ;
  int    _pialg[ LCT_PARTICLEID_MAX ]  {} ;

  // EVENT::ReconstructedParticleVec _particles ;
  // EVENT::ClusterVec _clusters ;
  // EVENT::TrackVec _tracks ;
  
  
} ;

#endif



