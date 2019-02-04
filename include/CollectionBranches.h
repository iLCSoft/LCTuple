#ifndef CollectionBranches_h
#define CollectionBranches_h 1

#include "LCTupleConf.h" 

#include "CWBranchesSet.h"

#include <vector>
#include <string>

class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** Base class for branches of collections. It implements branches for collection parameters. The class has to be extended by specific branches of the different collection types.
 * 
 * @author B.Vormwald, DESY
 */

class CollectionBranches : public CWBranchesSet {

public:
  CollectionBranches() {} ;
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  virtual ~CollectionBranches() {} ;

  virtual void writeParameters(bool writeparameters){ _writeparameters=writeparameters; };

protected:
  bool _writeparameters{};

  int    _npar {} ;
  std::vector<std::string> _parName {};
  std::vector<std::string> _parOrigin {};
  int    _parOriginID[ LCT_PARAMETERS_MAX ] {};

  int    _parIntN[ LCT_PARAMETERS_MAX ] {};
  int    _parFloatN[ LCT_PARAMETERS_MAX ] {};
  int    _parStringN[ LCT_PARAMETERS_MAX ] {};

  int    _parIntVal[ LCT_PARAMETERS_MAX ][ LCT_PARAMVALS_MAX ] {};
  float  _parFloatVal[ LCT_PARAMETERS_MAX ][ LCT_PARAMVALS_MAX ] {};
  //Not yet implemented! 2D vector of strings not well supported by TTree
  //std::vector<std::vector<std::string> > _parStringVal;
  //char** _parStringVal[ LCT_PARAMETERS_MAX ][ LCT_PARAMVALS_MAX ][ LCT_STRING_MAX ] ;
} ;

#endif
