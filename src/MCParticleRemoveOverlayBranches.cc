#include "MCParticleRemoveOverlayBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/MCParticle.h"

#include "TTree.h"
#include "TMath.h"


void MCParticleRemoveOverlayBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  MCParticleRemoveOverlayBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  if (_writeparameters) CollectionBranches::initBranches(tree, (pre+"mcro").c_str());

  tree->Branch( (pre+"nmcrop").c_str() , &_nmcro , (pre+"nmcrop/I").c_str() ) ;

  tree->Branch( (pre+"mcroori").c_str() , _mcroori , (pre+"mcroori["+pre+"nmcrop]/I").c_str() ) ;

  tree->Branch( (pre+"mcropdg").c_str() , _mcropdg , (pre+"mcropdg["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcrogst").c_str() , _mcrogst , (pre+"mcrogst["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcrosst").c_str() , _mcrosst , (pre+"mcrosst["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcrovtx").c_str() , _mcrovtx , (pre+"mcrovtx["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcrovty").c_str() , _mcrovty , (pre+"mcrovty["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcrovtz").c_str() , _mcrovtz , (pre+"mcrovtz["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcroepx").c_str() , _mcroepx , (pre+"mcroepx["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcroepy").c_str() , _mcroepy , (pre+"mcroepy["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcroepz").c_str() , _mcroepz , (pre+"mcroepz["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcromox").c_str() , _mcromox , (pre+"mcromox["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcromoy").c_str() , _mcromoy , (pre+"mcromoy["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcromoz").c_str() , _mcromoz , (pre+"mcromoz["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcromas").c_str() , _mcromas , (pre+"mcromas["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcroene").c_str() , _mcroene , (pre+"mcroene["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcrocha").c_str() , _mcrocha , (pre+"mcrocha["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcrotim").c_str() , _mcrotim , (pre+"mcrotim["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcrospx").c_str() , _mcrospx , (pre+"mcrospx["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcrospy").c_str() , _mcrospy , (pre+"mcrospy["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcrospz").c_str() , _mcrospz , (pre+"mcrospz["+pre+"nmcrop]/F").c_str() ) ;
  tree->Branch( (pre+"mcrocf0").c_str() , _mcrocf0 , (pre+"mcrocf0["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcrocf1").c_str() , _mcrocf1 , (pre+"mcrocf1["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcropa0").c_str() , _mcropa0 , (pre+"mcropa0["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcropa1").c_str() , _mcropa1 , (pre+"mcropa1["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcroda0").c_str() , _mcroda0 , (pre+"mcroda0["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcroda1").c_str() , _mcroda1 , (pre+"mcroda1["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcroda2").c_str() , _mcroda2 , (pre+"mcroda2["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcroda3").c_str() , _mcroda3 , (pre+"mcroda3["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcroda4").c_str() , _mcroda4 , (pre+"mcroda4["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcroover").c_str() , _mcroover , (pre+"mcroover["+pre+"nmcrop]/I").c_str() ) ;
  tree->Branch( (pre+"mcroevis").c_str() , &_mcroevis , (pre+"mcroevis/F").c_str() ) ;
  tree->Branch( (pre+"mcrommis").c_str() , &_mcrommis , (pre+"mcrommis/F").c_str() ) ;
  tree->Branch( (pre+"mcroEmiss").c_str() , &_mcroEmiss , (pre+"mcroEmiss/F").c_str() ) ;
  tree->Branch( (pre+"mcromvis").c_str() , &_mcromvis , (pre+"mcromvis/F").c_str() ) ;
  tree->Branch( (pre+"mcrocosTheta").c_str() , &_mcrocosTheta , (pre+"mcrocosTheta/F").c_str() ) ;
  tree->Branch( (pre+"mcroPtvis").c_str() , &_mcroPtvis , (pre+"mcroPtvis/F").c_str() ) ;
  tree->Branch( (pre+"mcroTheta").c_str() , & _mcroTheta, (pre+"mcroTheta/F").c_str() ) ;
  tree->Branch( (pre+"mcroPxvis").c_str() , &_mcroPxvis , (pre+"mcroPxvis/F").c_str() ) ;
  tree->Branch( (pre+"mcroPyvis").c_str() , &_mcroPyvis , (pre+"mcroPyvis/F").c_str() ) ;
  tree->Branch( (pre+"mcroPzvis").c_str() , &_mcroPzvis , (pre+"mcroPzvis/F").c_str() ) ;

}
  

void MCParticleRemoveOverlayBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){


	if( !col ) return ;

  if( col->getTypeName() != lcio::LCIO::MCPARTICLE ){

    std::string exStr("MCParticleRemoveOverlayBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }

  if (_writeparameters) CollectionBranches::fill(col, evt);

  _nmcro  = 0;
  
  for(int i=0 ; i < col->getNumberOfElements() ; ++i){

	lcio::MCParticle *mcrop = static_cast<lcio::MCParticle*>( col->getElementAt(i) );
    if( !mcrop->isCreatedInSimulation() || ( mcrop->getMass()<0.1 &&  mcrop->getPDG()!=22 ) ) continue;
//	if( mcrop->isCreatedInSimulation() || mcrop->isOverlay())continue;
    _mcroori[i] = mcrop->ext<CollID>();

    _mcropdg[ i ] = mcrop->getPDG() ;
    _mcrogst[ i ] = mcrop->getGeneratorStatus() ;
    _mcrosst[ i ] = mcrop->getSimulatorStatus() ;
    _mcrovtx[ i ] = mcrop->getVertex()[0] ;
    _mcrovty[ i ] = mcrop->getVertex()[1] ;
    _mcrovtz[ i ] = mcrop->getVertex()[2] ;
    _mcroepx[ i ] = mcrop->getEndpoint()[0] ;
    _mcroepy[ i ] = mcrop->getEndpoint()[1] ;
    _mcroepz[ i ] = mcrop->getEndpoint()[2] ;
    _mcromox[ i ] = mcrop->getMomentum()[0] ;
    _mcromoy[ i ] = mcrop->getMomentum()[1] ;
    _mcromoz[ i ] = mcrop->getMomentum()[2] ;
    _mcromas[ i ] = mcrop->getMass() ;
    _mcroene[ i ] = mcrop->getEnergy() ;
    _mcrocha[ i ] = mcrop->getCharge() ;
    _mcrotim[ i ] = mcrop->getTime() ;
    _mcrospx[ i ] = mcrop->getSpin()[0] ;
    _mcrospy[ i ] = mcrop->getSpin()[1] ;
    _mcrospz[ i ] = mcrop->getSpin()[2] ;
    _mcrocf0[ i ] = mcrop->getColorFlow()[0] ;
    _mcrocf1[ i ] = mcrop->getColorFlow()[1] ;
    _mcroover[ i ] = mcrop->isOverlay();

    const lcio::MCParticleVec& p = mcrop->getParents() ;

    // set the parents index - if parents exist; -1 otherwise
    _mcropa0[ i ] = ( p.size() > 0 ?  p[0]->ext<CollIndex>() - 1  :  -1 )  ;
    _mcropa1[ i ] = ( p.size() > 1 ?  p[1]->ext<CollIndex>() - 1  :  -1 )  ;

    // can we have more than two parents ????

    const lcio::MCParticleVec& p1 = mcrop->getDaughters() ;

 	 _mcroda0[ i ] = ( p1.size() > 0 ?  p1[0]->ext<CollIndex>() - 1  :  -1 )  ;
    _mcroda1[ i ] = ( p1.size() > 1 ?  p1[1]->ext<CollIndex>() - 1  :  -1 )  ;
	 _mcroda2[ i ] = ( p1.size() > 2 ?  p1[2]->ext<CollIndex>() - 1  :  -1 )  ;
	 _mcroda3[ i ] = ( p1.size() > 3 ?  p1[3]->ext<CollIndex>() - 1  :  -1 )  ;
	 _mcroda4[ i ] = ( p1.size() > 4 ?  p1[4]->ext<CollIndex>() - 1  :  -1 )  ;
	 _nmcro++;
  }
  _mcroevis=0;
  _mcroPxvis=0;
  _mcroPyvis=0;
  _mcroPzvis=0;
  for(int irc=0; irc<_nmcro; ++irc){

	  _mcroevis += _mcroene[irc] ;
	  _mcroPxvis+= _mcromox[irc] ;
	  _mcroPyvis+= _mcromoy[irc] ;
	  _mcroPzvis+= _mcromoz[irc] ;
    }
    _mcrocosTheta= _mcroPzvis /(sqrt(pow(_mcroPxvis,2)+pow(_mcroPyvis,2)+pow(_mcroPzvis,2)));
    _mcroPtvis=sqrt(pow(_mcroPxvis,2)+pow(_mcroPyvis,2));
    _mcroTheta= atan2(sqrt(pow(_mcroPxvis,2)+pow(_mcroPyvis,2)), _mcroPzvis);
    _mcromvis= sqrt(pow(_mcroevis,2)-pow(_mcroPxvis,2)-pow(_mcroPyvis,2)-pow(_mcroPzvis,2));
    _mcroEmiss=350- _mcroevis;
    double temp = pow (350 - _mcroevis , 2) - pow (_mcroPxvis , 2) - pow (_mcroPyvis , 2) - pow (_mcroPzvis , 2);
    if (temp <0)
    {
    	temp=-temp;
    }
    _mcrommis = sqrt( temp );

}
