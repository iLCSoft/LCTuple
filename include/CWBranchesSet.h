#ifndef CWBranchesSet_h
#define CWBranchesSet_h 1

#include <string>

class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCEvent ;
}

/** CWBranchesSet holds a set of branches in a columnwise ntuple that are filled from one collection.
 *  and thus typically have the same number of entries.
 * 
 * @author F. Gaede, DESY
 * @version $Id$
 */

class CWBranchesSet {
  
 public:
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" )=0 ;

  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt )=0 ;

  virtual ~CWBranchesSet(){}

} ;

#endif



