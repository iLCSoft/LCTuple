#ifndef PIDBranches_h
#define PIDBranches_h 1

#include "LCTupleConf.h" 

#include "CollectionBranches.h"
#include <vector>
#include <array>
#include <string>

class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** PIDBranches holds branches for ParticleID objects attached to the  elements of the ReconstructedParticle collection
 * 
 * @author F. Gaede, DESY
 * @version $Id$
 */

class PIDBranches : public CollectionBranches {
  
public:
  
  PIDBranches() {} ;
  
  void defineBranches(const std::string& algorithmName,
		      const std::vector<std::string>& paramNames,
		      const std::vector<std::string>& branchNames) ;

  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ;
  
  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;
  
  virtual ~PIDBranches() {} ;
  

private:
  std::string _algorithmName{} ;
  std::vector<std::string> _paramNames{} ;
  std::vector<std::string> _branchNames{} ;
  
  std::array<int  , LCT_RECOPARTICLE_MAX > _rcpityp{} ;
  std::array<int  , LCT_RECOPARTICLE_MAX > _rcpipdg{} ;
  std::array<float, LCT_RECOPARTICLE_MAX > _rcpillh{} ;
  std::array<int  , LCT_RECOPARTICLE_MAX > _rcpialg{} ;

  std::vector< std::array< float,LCT_RECOPARTICLE_MAX > > _rcpiparam{} ;


} ;

#endif



