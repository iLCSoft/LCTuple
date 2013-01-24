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

  if (_writeparameters) CollectionBranches::initBranches(tree, (pre+"mc").c_str());

  tree->Branch( (pre+"nmcp").c_str() , &_nmc , (pre+"nmcp/I").c_str() ) ;

  tree->Branch( (pre+"mcori").c_str() , _mcori , (pre+"mcori["+pre+"nmcp]/I").c_str() ) ;

  tree->Branch( (pre+"mcpdg").c_str() , _mcpdg , (pre+"mcpdg["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcgst").c_str() , _mcgst , (pre+"mcgst["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcsst").c_str() , _mcsst , (pre+"mcsst["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcvtx").c_str() , _mcvtx , (pre+"mcvtx["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcvty").c_str() , _mcvty , (pre+"mcvty["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcvtz").c_str() , _mcvtz , (pre+"mcvtz["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcepx").c_str() , _mcepx , (pre+"mcepx["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcepy").c_str() , _mcepy , (pre+"mcepy["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcepz").c_str() , _mcepz , (pre+"mcepz["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcmox").c_str() , _mcmox , (pre+"mcmox["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcmoy").c_str() , _mcmoy , (pre+"mcmoy["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcmoz").c_str() , _mcmoz , (pre+"mcmoz["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcmas").c_str() , _mcmas , (pre+"mcmas["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcene").c_str() , _mcene , (pre+"mcene["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mccha").c_str() , _mccha , (pre+"mccha["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mctim").c_str() , _mctim , (pre+"mctim["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcspx").c_str() , _mcspx , (pre+"mcspx["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcspy").c_str() , _mcspy , (pre+"mcspy["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mcspz").c_str() , _mcspz , (pre+"mcspz["+pre+"nmcp]/F").c_str() ) ;
  tree->Branch( (pre+"mccf0").c_str() , _mccf0 , (pre+"mccf0["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mccf1").c_str() , _mccf1 , (pre+"mccf1["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcpa0").c_str() , _mcpa0 , (pre+"mcpa0["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcpa1").c_str() , _mcpa1 , (pre+"mcpa1["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcda0").c_str() , _mcda0 , (pre+"mcda0["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcda1").c_str() , _mcda1 , (pre+"mcda1["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcda2").c_str() , _mcda2 , (pre+"mcda2["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcda3").c_str() , _mcda3 , (pre+"mcda3["+pre+"nmcp]/I").c_str() ) ;
  tree->Branch( (pre+"mcda4").c_str() , _mcda4 , (pre+"mcda4["+pre+"nmcp]/I").c_str() ) ;
}
  

void MCParticleBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col ) return ;

  if( col->getTypeName() != lcio::LCIO::MCPARTICLE ){

    std::string exStr("MCParticleBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }

  if (_writeparameters) CollectionBranches::fill(col, evt);

  _nmc  = col->getNumberOfElements() ;
  
  for(int i=0 ; i < _nmc ; ++i){
    
    lcio::MCParticle* mcp = static_cast<lcio::MCParticle*>( col->getElementAt(i) ) ;

    _mcori[i] = mcp->ext<CollID>();

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
    _mcene[ i ] = mcp->getEnergy() ;
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

    const lcio::MCParticleVec& p1 = mcp->getDaughters() ;

 	 _mcda0[ i ] = ( p1.size() > 0 ?  p1[0]->ext<CollIndex>() - 1  :  -1 )  ;
    _mcda1[ i ] = ( p1.size() > 1 ?  p1[1]->ext<CollIndex>() - 1  :  -1 )  ;
	 _mcda2[ i ] = ( p1.size() > 2 ?  p1[2]->ext<CollIndex>() - 1  :  -1 )  ;
	 _mcda3[ i ] = ( p1.size() > 3 ?  p1[3]->ext<CollIndex>() - 1  :  -1 )  ;
	 _mcda4[ i ] = ( p1.size() > 4 ?  p1[4]->ext<CollIndex>() - 1  :  -1 )  ;

  }
}
