#ifndef MergeCollections_h
#define MergeCollections_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <vector>


using namespace lcio ;
using namespace marlin ;


/** Helper processor that merges several input collections into a transient subset collections. The names and optionally the IDs of the merged collections
 *  are stored in collection parameters MergedCollectionNames and MergedCollectionIDs.
 *
 * @param InputCollections    Name of the input collections
 * @param InputCollectionIDs  Optional IDs for input collections - if given, IDs will be added to all objects in merged collections as ext<CollID>()" 
 *                            - it is the users responsibility to ensure uniqueness of the IDs across the event ( and that ID != 0 ) 
 * @param OutputCollection    Name of the output collection
 * 
 * @author F. Gaede, DESY
 * @author B. Vormwald, DESY
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
  StringVec   _inColNames  {} ;
  IntVec      _inColIDs    {} ;
  std::string _outColName  {} ; 
  int         _collectionParameterIndex  {} ;

  int _nRun  {} ;
  int _nEvt  {} ;
} ;

#endif



