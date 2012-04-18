#include "VertexBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/Vertex.h"
#include "EVENT/ReconstructedParticle.h"

#include "TTree.h"


void VertexBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){
    throw lcio::Exception("  VertexBranches::initBranches - invalid tree pointer !!! " ) ;
  }
  tree->Branch( (pre+"nvt").c_str()   ,  &_nvt , (pre+"nvt/I").c_str() ) ;
  tree->Branch( (pre+"vtpri").c_str() , _vtpri , (pre+"vtpri[nvt]/I").c_str() ) ;
  tree->Branch( (pre+"vtrpl").c_str() , _vtrpl , (pre+"vtrpl[nvt]/I").c_str() ) ;
  tree->Branch( (pre+"vttyp").c_str() , _vttyp , (pre+"vttyp[nvt][32]/C").c_str() ) ;
  tree->Branch( (pre+"vtxxx").c_str() , _vtxxx , (pre+"vtxxx[nvt]/F").c_str() ) ;
  tree->Branch( (pre+"vtyyy").c_str() , _vtyyy , (pre+"vtyyy[nvt]/F").c_str() ) ;
  tree->Branch( (pre+"vtzzz").c_str() , _vtzzz , (pre+"vtzzz[nvt]/F").c_str() ) ;
  tree->Branch( (pre+"vtchi").c_str() , _vtchi , (pre+"vtchi[nvt]/F").c_str() ) ;
  tree->Branch( (pre+"vtprb").c_str() , _vtprb , (pre+"vtprb[nvt]/F").c_str() ) ;
  tree->Branch( (pre+"vtcov").c_str() , _vtcov , (pre+"vtcov[nvt][6]/F").c_str() ) ;
  //  tree->Branch( (pre+"vtpar").c_str() , _vtpar , (pre+"vtpar[nvt][6]/F").c_str() ) ;
}


void VertexBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  if( !col ) return ;
  if( col->getTypeName() != lcio::LCIO::VERTEX ){
    std::string exStr("VertexBranches::fill: invalid collection type : " ) ;
    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }

  _nvt  = col->getNumberOfElements() ;

  for(int i=0 ; i < _nvt ; ++i){
    lcio::Vertex* vtx = static_cast<lcio::Vertex*>( col->getElementAt(i) ) ;

    _vtpri[i] = vtx->isPrimary();
    _vtrpl[i] = (vtx->getAssociatedParticle() ?  vtx->getAssociatedParticle()->ext<CollIndex>() - 1  :  -1 ); 
    strcpy(_vttyp[i],vtx->getAlgorithmType().c_str());
    _vtxxx[i] = vtx->getPosition()[0];
    _vtyyy[i] = vtx->getPosition()[1];
    _vtzzz[i] = vtx->getPosition()[2];
    _vtchi[i] = vtx->getChi2();
    _vtprb[i] = vtx->getProbability();
    for(int j=0; j<6 ; ++j) _vtcov[ i ][ j ]  = vtx->getCovMatrix()[j] ;
    //    for(int j=0; j<6 ; ++j) _vtpar[ i ][ j ]  = vtx->getParameters()[j] ;
  }
}






















