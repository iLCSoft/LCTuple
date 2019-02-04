#ifndef MCParticleBranches_h
#define MCParticleBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** MCParticleBranches holds branches created from MCParticleCollection
 * 
 * @author F. Gaede, DESY
 * @version $Id$
 */

class MCParticleBranches : public CollectionBranches {
  
public:
  
  MCParticleBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~MCParticleBranches() {} ;
  

private:
  
  int    _nmc  {} ;
  int    _mcori[ LCT_MCPARTICLE_MAX ] {};
  int    _mcpdg[ LCT_MCPARTICLE_MAX ] {};
  int    _mcgst[ LCT_MCPARTICLE_MAX ] {};
  int    _mcsst[ LCT_MCPARTICLE_MAX ] {};
  float  _mcvtx[ LCT_MCPARTICLE_MAX ] {};
  float  _mcvty[ LCT_MCPARTICLE_MAX ] {};
  float  _mcvtz[ LCT_MCPARTICLE_MAX ] {};
  float  _mcepx[ LCT_MCPARTICLE_MAX ] {};
  float  _mcepy[ LCT_MCPARTICLE_MAX ] {};
  float  _mcepz[ LCT_MCPARTICLE_MAX ] {};
  float  _mcmox[ LCT_MCPARTICLE_MAX ] {};
  float  _mcmoy[ LCT_MCPARTICLE_MAX ] {};
  float  _mcmoz[ LCT_MCPARTICLE_MAX ] {};
  float  _mcmas[ LCT_MCPARTICLE_MAX ] {};
  float  _mcene[ LCT_MCPARTICLE_MAX ] {};
  float  _mccha[ LCT_MCPARTICLE_MAX ] {};
  float  _mctim[ LCT_MCPARTICLE_MAX ] {};
  float  _mcspx[ LCT_MCPARTICLE_MAX ] {};
  float  _mcspy[ LCT_MCPARTICLE_MAX ] {};
  float  _mcspz[ LCT_MCPARTICLE_MAX ] {};
  int    _mccf0[ LCT_MCPARTICLE_MAX ] {};
  int    _mccf1[ LCT_MCPARTICLE_MAX ] {};
  int    _mcpa0[ LCT_MCPARTICLE_MAX ] {};
  int    _mcpa1[ LCT_MCPARTICLE_MAX ] {};
  int    _mcda0[ LCT_MCPARTICLE_MAX ] {};
  int    _mcda1[ LCT_MCPARTICLE_MAX ] {};
  int    _mcda2[ LCT_MCPARTICLE_MAX ] {};
  int    _mcda3[ LCT_MCPARTICLE_MAX ] {};
  int    _mcda4[ LCT_MCPARTICLE_MAX ] {};
} ;

#endif



