#include "PIDBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/Vertex.h"
#include <UTIL/PIDHandler.h>

#include "TTree.h"

using namespace lcio ;

void PIDBranches::defineBranches(const std::string& algorithmName,
				 const std::vector<std::string>& paramNames,
				 const std::vector<std::string>& branchNames) {
  
  if( paramNames.size() != branchNames.size() ){
    
    throw lcio::Exception("PIDBranches::setParameterNames inconsistent parameter and branch name vector lenghts !" ) ; 
  }
  _algorithmName = algorithmName ;
  _paramNames    = paramNames ;
  _branchNames   = branchNames ;
  _rcpiparam.resize( _branchNames.size() ) ;
}

void PIDBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  PIDBranches::initBranches - invalid tree pointer !!! " ) ;
  }
  tree->Branch( (pre+"rcpityp").c_str() , _rcpityp.data() , (pre+"rcpityp[nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcpipdg").c_str() , _rcpipdg.data() , (pre+"rcpipdg[nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcpillh").c_str() , _rcpillh.data() , (pre+"rcpillh[nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcpialg").c_str() , _rcpialg.data() , (pre+"rcpialg[nrec]/I").c_str() ) ;
  
  for(unsigned i=0,N=_branchNames.size(); i<N; ++i){

    tree->Branch( (pre+_branchNames[i]).c_str() , _rcpiparam[i].data() , (pre+_branchNames[i]+"[nrec]/F").c_str() ) ;
  }
  
}
  

void PIDBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* ){
  
  if( !col ) return ;

  if( col->getTypeName() != lcio::LCIO::RECONSTRUCTEDPARTICLE ){
    
    std::string exStr("PIDBranches::fill: invalid collection type : " ) ;
    
    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }
  
  int nrec  = col->getNumberOfElements() ;
  
  lcio::PIDHandler pidh( col );
  int algoID       = pidh.getAlgorithmID( _algorithmName );
  
  std::vector<int> algoIndices ;
  algoIndices.reserve(_paramNames.size() ) ; 

  for( auto name : _paramNames ){
    algoIndices.push_back(  pidh.getParameterIndex(algoID, name ) ) ;
  }
  
  //------  fill the requested PID information for the Reconstructed particle ----------------------------

  for(int i=0 ; i < nrec ; ++i){
    
    lcio::ReconstructedParticle* rec = static_cast<lcio::ReconstructedParticle*>( col->getElementAt(i) ) ;

    const ParticleID& pid    = pidh.getParticleID( rec , algoID ) ;
    const FloatVec&   params = pid.getParameters() ;

    _rcpityp[i] = pid.getType() ;
    _rcpipdg[i] = pid.getPDG() ;
    _rcpillh[i] = pid.getLikelihood() ;
    _rcpialg[i] = pid.getAlgorithmType() ;
    
    for(unsigned j=0,N=_branchNames.size(); j<N; ++j){
      _rcpiparam[j][i] = ( params.empty() ? -1 : params[ algoIndices[j] ] ) ;
    }

  }

}
