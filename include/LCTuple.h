#ifndef LCTuple_h
#define LCTuple_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <string>


using namespace lcio ;
using namespace marlin ;

class TTree ;
class CWBranchesSet ;

/** Creates a simple column wise ntuple in a ROOT tree from LCIO collections.
 
 *  <h4>Input - Prerequisites</h4>
 *  Needs the collection of MCParticles.
 *
 *  <h4>Output</h4> 
 *  A ROOT TTree with LCIO data in column wise ntuple format
 * 
 * @param MCParticleCollection  Name of the MCParticle collection
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

  TTree* _tree ;

  CWBranchesSet* _mcpBranches ;

  int _nRun ;
  int _nEvt ;
} ;

#endif



