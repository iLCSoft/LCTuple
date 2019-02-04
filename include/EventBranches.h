#ifndef EventBranches_h
#define EventBranches_h 1

#include "LCTupleConf.h" 

#include "CWBranchesSet.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** EventBranches holds branches with data from LCEvent.
 * 
 * @author F. Gaede, DESY
 * @version $Id$
 */

class EventBranches : public CWBranchesSet {
  
public:
  
  EventBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~EventBranches() {} ;
  

private:

  int    _evevt {} ;    
  int    _evrun {} ;
  float  _evwgt {} ;
  long   _evtim {} ;
  float  _evsig {} ;
  float 	_evene {}	;
  float 	_evpoe {}	;
  float 	_evpop {} ;
  int   	_evnch {} ;
  char _evpro[LCT_STRING_MAX] {} ;
} ;

#endif



