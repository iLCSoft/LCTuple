#ifndef MergeCollections_h
#define MergeCollections_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <vector>


using namespace lcio ;
using namespace marlin ;


/** Helper processor that merges several input collections into a transient subset collections.
 *
 * @param InputCollections  Name of the input collections
 * @param OutputCollection  Name of the output collection
 * 
 * @author F. Gaede, DESY
 * @version $Id: MergeCollections.h 2946 2012-01-16 15:40:46Z gaede $
 */

class MergeCollections : public Processor {
  
 public:
  
  virtual Processor*  newProcessor() { return new MergeCollections ; }
  
  
  MergeCollections() ;
  
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
  StringVec   _inColNames ;
  std::string _outColName ; 


  int _nRun ;
  int _nEvt ;
} ;

#endif



