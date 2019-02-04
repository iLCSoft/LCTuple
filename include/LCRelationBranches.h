#ifndef LCRelationBranches_h
#define LCRelationBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** LCRelationBranches holds branches created from LCRelations.
 * 
 * @author F. Gaede, DESY
 * @version $Id$
 */

class LCRelationBranches : public CWBranchesSet {
  
public:
  
  LCRelationBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~LCRelationBranches() {} ;
  

private:
  
  int    _nrel  {} ;
  int    _from[ LCT_RELATION_MAX ] {};
  int    _to  [ LCT_RELATION_MAX ] {};
  float  _wgt [ LCT_RELATION_MAX ] {};

} ;

#endif



