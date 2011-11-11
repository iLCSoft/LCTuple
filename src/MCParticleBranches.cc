#include "MCParticleBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/MCParticle.h"

#include "TTree.h"


void MCParticleBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  MCParticleBranches::initBranches - invalid tree pointer !!! " ) ;
  }


  tree->Branch( (pre+"nmcp").c_str() , &_nmc , (pre+"nmcp/I").c_str() ) ;

  tree->Branch( (pre+"mcpdg").c_str() , _mcpdg , (pre+"mcpdg[nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcgst").c_str() , _mcgst , (pre+"mcgst[nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcsst").c_str() , _mcsst , (pre+"mcsst[nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcvtx").c_str() , _mcvtx , (pre+"mcvtx[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcvty").c_str() , _mcvty , (pre+"mcvty[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcvtz").c_str() , _mcvtz , (pre+"mcvtz[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcepx").c_str() , _mcepx , (pre+"mcepx[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcepy").c_str() , _mcepy , (pre+"mcepy[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcepz").c_str() , _mcepz , (pre+"mcepz[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcmox").c_str() , _mcmox , (pre+"mcmox[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcmoy").c_str() , _mcmoy , (pre+"mcmoy[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcmoz").c_str() , _mcmoz , (pre+"mcmoz[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcmas").c_str() , _mcmas , (pre+"mcmas[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mccha").c_str() , _mccha , (pre+"mccha[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mctim").c_str() , _mctim , (pre+"mctim[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcspx").c_str() , _mcspx , (pre+"mcspx[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcspy").c_str() , _mcspy , (pre+"mcspy[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcspz").c_str() , _mcspz , (pre+"mcspz[nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mccf0").c_str() , _mccf0 , (pre+"mccf0[nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mccf1").c_str() , _mccf1 , (pre+"mccf1[nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcpa0").c_str() , _mcpa0 , (pre+"mcpa0[nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcpa1").c_str() , _mcpa1 , (pre+"mcpa1[nmcp]/I").c_str() ) ;
}
  

void MCParticleBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( col->getTypeName() != lcio::LCIO::MCPARTICLE ){

    std::string exStr("MCParticleBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }


  _nmc  = col->getNumberOfElements() ;
  
  for(int i=0 ; i < _nmc ; ++i){
    
    lcio::MCParticle* mcp = static_cast<lcio::MCParticle*>( col->getElementAt(i) ) ;
    
    
    _mcpdg[ i ] = mcp->getPDG() ;
    _mcgst[ i ] = mcp->getGeneratorStatus() ;
    _mcsst[ i ] = mcp->getSimulatorStatus() ;
    _mcvtx[ i ] = mcp->getVertex()[0] ;
    _mcvty[ i ] = mcp->getVertex()[1] ;
    _mcvtz[ i ] = mcp->getVertex()[2] ;
    _mcepx[ i ] = mcp->getEndpoint()[0] ;
    _mcepy[ i ] = mcp->getEndpoint()[1] ;
    _mcepz[ i ] = mcp->getEndpoint()[2] ;
    _mcmox[ i ] = mcp->getMomentum()[0] ;
    _mcmoy[ i ] = mcp->getMomentum()[1] ;
    _mcmoz[ i ] = mcp->getMomentum()[2] ;
    _mcmas[ i ] = mcp->getMass() ;
    _mccha[ i ] = mcp->getCharge() ;
    _mctim[ i ] = mcp->getTime() ;
    _mcspx[ i ] = mcp->getSpin()[0] ;
    _mcspy[ i ] = mcp->getSpin()[1] ;
    _mcspz[ i ] = mcp->getSpin()[2] ;
    _mccf0[ i ] = mcp->getColorFlow()[0] ;
    _mccf1[ i ] = mcp->getColorFlow()[1] ;
    
    const lcio::MCParticleVec& p = mcp->getParents() ;

    // set the parents index - if parents exist; -1 otherwise
    _mcpa0[ i ] = ( p.size() > 0 ?  p[0]->ext<CollIndex>() - 1  :  -1 )  ;
    _mcpa1[ i ] = ( p.size() > 1 ?  p[1]->ext<CollIndex>() - 1  :  -1 )  ;

    // can we have more than two parents ????
    
  }
}






















