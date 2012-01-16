#ifndef SimTrackerHitBranches_h
#define SimTrackerHitBranches_h 1

#include "LCTupleConf.h" 

#include "CWBranchesSet.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** SimTrackerHitBranches holds branches created from LCRelations.
 * 
 * @author F. Gaede, DESY
 * @version $Id: SimTrackerHitBranches.h 2945 2012-01-16 15:05:02Z gaede $
 */

class SimTrackerHitBranches : public CWBranchesSet {
  
public:
  
  SimTrackerHitBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~SimTrackerHitBranches() {} ;
  

private:
  
  int    _nsth   ;
  int    _stci0[ LCT_SIMTRACKERHIT_MAX ] ;
  int    _stci1[ LCT_SIMTRACKERHIT_MAX ] ;
  double _stpox[ LCT_SIMTRACKERHIT_MAX ] ;
  double _stpoy[ LCT_SIMTRACKERHIT_MAX ] ;
  double _stpoz[ LCT_SIMTRACKERHIT_MAX ] ;
  float  _stedp[ LCT_SIMTRACKERHIT_MAX ] ;
  float  _sttim[ LCT_SIMTRACKERHIT_MAX ] ;
  float  _stmox[ LCT_SIMTRACKERHIT_MAX ] ;
  float  _stmoy[ LCT_SIMTRACKERHIT_MAX ] ;
  float  _stmoz[ LCT_SIMTRACKERHIT_MAX ] ;
  float  _stptl[ LCT_SIMTRACKERHIT_MAX ] ;
  int    _stmcp[ LCT_SIMTRACKERHIT_MAX ] ;

} ;

#endif



