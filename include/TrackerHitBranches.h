#ifndef TrackerHitBranches_h
#define TrackerHitBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** TrackerHitBranches holds branches created from LCRelations.
 * 
 * @author F. Gaede, DESY
 * @version $Id:$
 */

class TrackerHitBranches : public CollectionBranches {
  
public:
  
  TrackerHitBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~TrackerHitBranches() {} ;
  

private:
  
  int    _ntrh    {} ;
  int    _thori[ LCT_TRACKERHIT_MAX ]  {} ;
  int    _thci0[ LCT_TRACKERHIT_MAX ]  {} ;
  int    _thci1[ LCT_TRACKERHIT_MAX ]  {} ;
  double _thpox[ LCT_TRACKERHIT_MAX ]  {} ;
  double _thpoy[ LCT_TRACKERHIT_MAX ]  {} ;
  double _thpoz[ LCT_TRACKERHIT_MAX ]  {} ;
  float  _thedp[ LCT_TRACKERHIT_MAX ]  {} ;
  float  _thtim[ LCT_TRACKERHIT_MAX ]  {} ;

  float  _thcov[ LCT_TRACKERHIT_MAX ][6]  {} ;

  float  _thtyp[ LCT_TRACKERHIT_MAX ]  {} ;
  float  _thqua[ LCT_TRACKERHIT_MAX ]  {} ;
  float  _thede[ LCT_TRACKERHIT_MAX ]  {} ;

} ;

#endif



