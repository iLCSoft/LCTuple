#ifndef MCParticleFromRelationBranches_h
#define MCParticleFromRelationBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** MCParticleFromRelationBranches holds branches created from MCParticleCollection
 * 
 * @author F. Gaede, DESY
 * @version $Id: MCParticleFromRelationBranches.h 4433 2013-01-24 13:09:57Z boehmej $
 */

class MCParticleFromRelationBranches : public CollectionBranches {
  
public:
  
  MCParticleFromRelationBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  
  virtual void fill(const EVENT::LCCollection* colRel, const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~MCParticleFromRelationBranches() {} ;
  

private:
  
  int    _nmcfr   {} ;
  int    _mcfrori[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrpdg[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrgst[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrsst[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrvtx[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrvty[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrvtz[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrepx[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrepy[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrepz[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrmox[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrmoy[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrmoz[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrmas[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrene[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrcha[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrtim[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrspx[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrspy[ LCT_MCPARTICLE_MAX ] {} ;
  float  _mcfrspz[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrcf0[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrcf1[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrpa0[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrpa1[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrda0[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrda1[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrda2[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrda3[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrda4[ LCT_MCPARTICLE_MAX ] {} ;
  int    _mcfrover[ LCT_MCPARTICLE_MAX ] {} ;


  float _mcfrevis {} ;
  float _mcfrPxvis {} ;
  float _mcfrPyvis {} ;
  float _mcfrPzvis {} ;
  float _mcfrcosTheta {} ;
  float _mcfrTheta {} ;
  float _mcfrPtvis {} ;
  float _mcfrmvis {} ;
  float _mcfrEmiss {} ;
  float _mcfrmmis {} ;
  float _mcfrmmisNoOver {} ;

} ;

#endif



