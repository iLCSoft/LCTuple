#ifndef PIDBranches_h
#define PIDBranches_h 1

#include "LCTupleConf.h" 

#include "CWBranchesSet.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** PIDBranches holds branches created from a ParticleID collection 
 * 
 * @author F. Gaede, DESY
 * @version $Id:$
 */

class PIDBranches : public CWBranchesSet {
  
public:
  
  PIDBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~PIDBranches() {} ;
  

private:
  
  int    _npid   ;
  int    _pityp[ LCT_PARTICLEID_MAX ] ;
  int    _pipdg[ LCT_PARTICLEID_MAX ] ;
  float  _pillh[ LCT_PARTICLEID_MAX ] ;
  int    _pialg[ LCT_PARTICLEID_MAX ] ;
} ;

#endif



