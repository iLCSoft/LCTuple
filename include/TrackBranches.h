#ifndef TrackBranches_h
#define TrackBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** TrackBranches holds branches created from a Track collection
 * 
 * @author F. Gaede, DESY
 * @version $Id$
 */

class TrackBranches : public CollectionBranches {
  
public:
  
  TrackBranches() {} ;
  
  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~TrackBranches() {} ;
  

private:
  
  int   _ntrk  {} ;

  int   _trori[ LCT_TRACK_MAX ]  {} ;

  int   _trtyp[ LCT_TRACK_MAX ]  {} ;
  float _trch2[ LCT_TRACK_MAX ]  {} ;
  int   _trndf[ LCT_TRACK_MAX ]  {} ; 
  float _tredx[ LCT_TRACK_MAX ]  {} ;
  float _trede[ LCT_TRACK_MAX ]  {} ;
  float _trrih[ LCT_TRACK_MAX ]  {} ;
  int   _trshn[ LCT_TRACK_MAX ][12]  {} ;
  int   _trnts[ LCT_TRACK_MAX ]  {} ;
  int   _trfts[ LCT_TRACK_MAX ]  {} ;
  int   _trsip[ LCT_TRACK_MAX ]  {} ;   // track stat atIP
  int   _trsfh[ LCT_TRACK_MAX ]  {} ;   // track stat atFirstHit
  int   _trslh[ LCT_TRACK_MAX ]  {} ;   // track stat atLastHit
  int   _trsca[ LCT_TRACK_MAX ]  {} ;   // track stat atCalorimeter

  int   _ntrst  {} ;
  int   _tsloc[ LCT_TRACKSTATE_MAX ]  {} ; 
  float _tsdze[ LCT_TRACKSTATE_MAX ]  {} ;
  float _tsphi[ LCT_TRACKSTATE_MAX ]  {} ;
  float _tsome[ LCT_TRACKSTATE_MAX ]  {} ;
  float _tszze[ LCT_TRACKSTATE_MAX ]  {} ;
  float _tstnl[ LCT_TRACKSTATE_MAX ]  {} ;
  float _tscov[ LCT_TRACKSTATE_MAX ] [15]  {} ;
  float _tsrpx[ LCT_TRACKSTATE_MAX ]  {} ;
  float _tsrpy[ LCT_TRACKSTATE_MAX ]  {} ;
  float _tsrpz[ LCT_TRACKSTATE_MAX ]  {} ;

  // EVENT::TrackVec _tracks ;
  // EVENT::TrackerHitVec _hits ;
  
} ;

#endif



