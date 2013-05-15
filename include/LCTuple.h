#ifndef LCTuple_h
#define LCTuple_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <vector>


using namespace lcio ;
using namespace marlin ;

class TTree ;
class CWBranchesSet ;
class CollectionBranches;

/** Creates a simple column wise ntuple in a ROOT tree from LCIO collections.
 
 *  <h4>Input - Prerequisites</h4>
 *  Needs collections of MCParticles, ReconstructedParticles, Tracks, ....
 *  There can only be one collection of every type (users should copy all collections
 *  of a given type into one (subset) collection).
 *
 *  <h4>Output</h4> 
 *  A ROOT TTree with LCIO data in column wise ntuple format
 * 
 * @param MCParticleCollection  Name of the MCParticle collection
 * @param RecoCollection        Name of the ReconstructedParticleParticle collection
 * 
 * @author F. Gaede, DESY
 * @version $Id$
 */

class LCTuple : public Processor {
  
 public:
  
  virtual Processor*  newProcessor() { return new LCTuple ; }
  
  
  LCTuple() ;
  
  /** Called at the begin of the job before anything is read.
   * Use to initialize the processor, e.g. book histograms.
   */
  virtual void init() ;
  
  /** Called for every run.
   */
  virtual void processRunHeader( LCRunHeader* run ) ;
  
  /** Called for every event - the working horse.
   */
  virtual void processEvent( LCEvent * evt ) ; 
  
  
  virtual void check( LCEvent * evt ) ; 
  
  
  /** Called after data processing for clean up.
   */
  virtual void end() ;
  
  
 protected:

  /** Input collection name.
   */
  std::string _mcpColName ;
  std::string _recColName ;
  std::string _trkColName ;
  std::string _cluColName ;
  std::string _sthColName ;
  std::string _trhColName ;
  std::string _schColName ;
  std::string _vtxColName ;

  bool _mcpColWriteParameters ;
  bool _recColWriteParameters ;
  bool _trkColWriteParameters ;
  bool _cluColWriteParameters ;
  bool _sthColWriteParameters ;
  bool _trhColWriteParameters ;
  bool _schColWriteParameters ;
  bool _vtxColWriteParameters ;



  StringVec _relColNames ;
  StringVec _relPrefixes ;

  TTree* _tree ;

  CWBranchesSet* _evtBranches ;
  CollectionBranches* _mcpBranches ;
  CollectionBranches* _recBranches ;
  CollectionBranches* _trkBranches ;
  CollectionBranches* _cluBranches ;
  CollectionBranches* _sthBranches ;
  CollectionBranches* _trhBranches ;
  CollectionBranches* _schBranches ;
  CollectionBranches* _vtxBranches ;
  
  std::vector<CWBranchesSet*> _relBranchesVec ;
  
  int _nRun ;
  int _nEvt ;
} ;

#endif



