#ifndef CalorimeterHitBranches_h
#define CalorimeterHitBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** CalorimeterHitBranches holds branches created from LCRelations.
 * 
 * @author F. Gaede, DESY
 * @version $Id: CalorimeterHitBranches.h 2945 2012-01-16 15:05:02Z gaede $
 */

class CalorimeterHitBranches : public CollectionBranches {
  
public:
  
  CalorimeterHitBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~CalorimeterHitBranches() {} ;
  

private:
  
  int    _ncah  {} ;    
  
  int    _caori[ LCT_CALORIMETERHIT_MAX ] {} ;
		     
  int    _caci0[ LCT_CALORIMETERHIT_MAX ] {} ;
  int    _caci1[ LCT_CALORIMETERHIT_MAX ] {} ;
  float  _capox[ LCT_CALORIMETERHIT_MAX ] {} ;
  float  _capoy[ LCT_CALORIMETERHIT_MAX ] {} ;
  float  _capoz[ LCT_CALORIMETERHIT_MAX ] {} ;
  float  _caene[ LCT_CALORIMETERHIT_MAX ] {} ;
  float  _catim[ LCT_CALORIMETERHIT_MAX ] {} ;
  
} ;

#endif



