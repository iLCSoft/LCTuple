#ifndef LCTuple_h
#define LCTuple_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <vector>
#include "MCParticleFromRelationBranches.h"

#include "JetBranches.h"
#include "PIDBranches.h"


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
  
  struct PIDBranchDef{
    std::string algoName{} ;
    std::string prefix{} ;
    std::vector<std::string> pNames{} ;
    std::vector<std::string> bNames{} ;
  } ;

 public:
  
  virtual Processor*  newProcessor() { return new LCTuple ; }
  
  
  LCTuple(const LCTuple &) = delete ;
  LCTuple& operator =(const LCTuple &) = delete ;
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

  void decodePIDBranchDefinitions() ;

  /** Input collection name.
   */
  std::string _mcpColName {};
  std::string _mcpRemoveOverlayColName {};
  std::string _recColName {};
  std::string _jetColName {};
  std::string _isolepColName {};  
  std::string _trkColName {};
  std::string _cluColName {};
  std::string _sthColName {};
  std::string _trhColName {};
  std::string _schColName {};
  std::string _cahColName {};
  std::string _vtxColName {};
  std::string _pfoRelName {};
  std::string _relName {};



  bool _mcpColWriteParameters {};
  bool _recColWriteParameters {};
  bool _jetColWriteParameters {};
  bool _isolepColWriteParameters {}; 
  bool _trkColWriteParameters {};
  bool _cluColWriteParameters {};
  bool _sthColWriteParameters {};
  bool _trhColWriteParameters {};
  bool _schColWriteParameters {};
  bool _cahColWriteParameters {};
  bool _vtxColWriteParameters {};


  bool _jetColExtraParameters {};                 /* Enables writing extra jet parameters */
  bool _jetColTaggingParameters {};               /* Enables writing jet tagging parameters */


  StringVec _relColNames {};
  StringVec _relPrefixes {};

  StringVec _pidBranchDefinition {};
  
  TTree* _tree {};

  CWBranchesSet* _evtBranches {};
  CollectionBranches* _mcpBranches {};
  CollectionBranches* _mcpremoveoverlayBranches {};
  CollectionBranches* _recBranches {};
//  CollectionBranches* _jetBranches {};
  JetBranches* _jetBranches {};
  CollectionBranches* _isolepBranches {};
  CollectionBranches* _trkBranches {};
  CollectionBranches* _cluBranches {};
  CollectionBranches* _sthBranches {};
  CollectionBranches* _trhBranches {};
  CollectionBranches* _schBranches {};
  CollectionBranches* _cahBranches {};
  CollectionBranches* _vtxBranches {};
  MCParticleFromRelationBranches* _mcRelBranches {};
  
  std::vector<PIDBranches*> _pidBranchesVec {};
  std::vector<CWBranchesSet*> _relBranchesVec {};
  
  int _nRun {};
  int _nEvt {};

  std::vector<PIDBranchDef> _pidBranchDefs {} ;
} ;

#endif
