#ifndef VertexBranches_h
#define VertexBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** VertexBranches holds branches created from VertexCollection
 * 
 * @author B. Vormwald, DESY
 */

class VertexBranches : public CollectionBranches {
  
public:
  VertexBranches() {} ;
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  virtual ~VertexBranches() {} ;

private:
  int    _nvt    {} ;
  int    _vtori[ LCT_VERTEX_MAX ]  {} ;
  int    _vtpri[ LCT_VERTEX_MAX ]  {} ;
  char   _vttyp[ LCT_VERTEX_MAX ][LCT_STRING_MAX]  {} ; //holds the algorithm type used for vertex finding

  float  _vtxxx[ LCT_VERTEX_MAX ]  {} ;
  float  _vtyyy[ LCT_VERTEX_MAX ]  {} ;
  float  _vtzzz[ LCT_VERTEX_MAX ]  {} ;
  float  _vtchi[ LCT_VERTEX_MAX ]  {} ;
  float  _vtprb[ LCT_VERTEX_MAX ]  {} ;

  int    _vtrpl[ LCT_VERTEX_MAX ]  {} ; //reco particle link

  float  _vtcov[ LCT_VERTEX_MAX ][6]  {} ;
  float  _vtpar[ LCT_VERTEX_MAX ][6]  {} ; //arbitrary value -- has to be checked if enough fields
} ;

#endif



