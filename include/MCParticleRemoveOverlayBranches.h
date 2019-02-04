#ifndef MCParticleRemoveOverlayBranches_h
#define MCParticleRemoveOverlayBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** MCParticleRemoveOverlayBranches holds branches created from MCParticleCollection
 * 
 * @author F. Mueller, DESY
 * @version $Id: MCParticleRemoveOverlayBranches.h 4433 2013-01-24 13:09:57Z boehmej $
 */

class MCParticleRemoveOverlayBranches : public CollectionBranches {
  
public:
  
  MCParticleRemoveOverlayBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  
  virtual void fill( const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~MCParticleRemoveOverlayBranches() {} ;
  

private:
  
  int    _nmcro    {} ;
  int    _mcroori[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcropdg[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcrogst[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcrosst[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcrovtx[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcrovty[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcrovtz[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcroepx[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcroepy[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcroepz[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcromox[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcromoy[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcromoz[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcromas[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcroene[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcrocha[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcrotim[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcrospx[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcrospy[ LCT_MCPARTICLE_MAX ]  {} ;
  float  _mcrospz[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcrocf0[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcrocf1[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcropa0[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcropa1[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcroda0[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcroda1[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcroda2[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcroda3[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcroda4[ LCT_MCPARTICLE_MAX ]  {} ;
  int    _mcroover[ LCT_MCPARTICLE_MAX ]  {} ;


  float _mcroevis  {} ;
  float _mcroPxvis {} ;
  float _mcroPyvis {} ;
  float _mcroPzvis {} ;
  float _mcrocosTheta {} ;
  float _mcroTheta {} ;
  float _mcroPtvis {} ;
  float _mcromvis {} ;
  float _mcroEmiss {} ;
  float _mcrommis {} ;

} ;

#endif



