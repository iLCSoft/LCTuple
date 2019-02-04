#ifndef CreateRecoRelations_h
#define CreateRecoRelations_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <vector>


using namespace lcio ;
using namespace marlin ;


/** Helper processor that creates LCReation collections for the relations to Tracks and Clusters of ReconstructedParticles
 *  to be used with LCTuple.
 *
 * @param  RecoCollection                Names of ReconstructedParticles input collections
 * @param  Reco2TracksRelationName       Name of output collection for relation ReconstructedParticles to Tracks
 * @param  Reco2ClusterRelationName      Name of output collection for relation ReconstructedParticles to Clusters
 * @param  Reco2RecoRelationName         Name of output collection for relation ReconstructedParticles to ReconstructedParticles
 * 
 * @author F. Gaede, DESY
 * @version $Id: CreateRecoRelations.h 2946 2012-01-16 15:40:46Z gaede $
 */

class CreateRecoRelations : public Processor {
  
 public:
  
  virtual Processor*  newProcessor() { return new CreateRecoRelations ; }
  
  
  CreateRecoRelations() ;
  
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

  std::string _inColReco {} ; 
  std::string _outColR2T {} ; 
  std::string _outColR2C {} ; 
  std::string _outColR2R {} ; 



  int _nRun {} ;
  int _nEvt {} ;
} ;

#endif



