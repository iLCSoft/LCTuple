#ifndef ClusterBranches_h
#define ClusterBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** ClusterBranches holds branches created from a Cluster collection
 * 
 * @author F. Gaede, DESY
 * @version $Id: ClusterBranches.h 2945 2012-01-16 15:05:02Z gaede $
 */

class ClusterBranches : public CollectionBranches {
  
public:
  
  ClusterBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~ClusterBranches() {} ;
  

private:
  
  int   _nclu {};
  int   _nsd {};
  int   _clori[ LCT_CLUSTER_MAX ] {};
  int   _cltyp[ LCT_CLUSTER_MAX ] {};
  float _clene[ LCT_CLUSTER_MAX ] {};
  float _cleer[ LCT_CLUSTER_MAX ] {};
  float _clpox[ LCT_CLUSTER_MAX ] {};
  float _clpoy[ LCT_CLUSTER_MAX ] {};
  float _clpoz[ LCT_CLUSTER_MAX ] {};
  float _clper[ LCT_CLUSTER_MAX ][ 6] {}; // position error cov matrix
  float _clthe[ LCT_CLUSTER_MAX ] {};
  float _clphi[ LCT_CLUSTER_MAX ] {};
  float _clder[ LCT_CLUSTER_MAX ][ 3] {};  // direction error cov matrix
  float _clsha[ LCT_CLUSTER_MAX ][ 6] {};  // shape variable - fixed  to 6 for now 
  float _clsde[ LCT_CLUSTER_MAX ][12] {};  // subdetector fractions - limited to 12 
  
  // ignored for now:
  // EVENT::ClusterVec        _clusters ;
  // EVENT::CalorimeterHitVec _hits ;
  // EVENT::FloatVec          _weights ;
  
  // int    _npid   ;
  // int    _pityp[ LCT_PARTICLEID_MAX ] ;
  // int    _pipdg[ LCT_PARTICLEID_MAX ] ;
  // float  _pillh[ LCT_PARTICLEID_MAX ] ;
  // int    _pialg[ LCT_PARTICLEID_MAX ] ;
  
} ;

#endif



