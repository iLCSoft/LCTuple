#include "MCParticleFromRelationBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/MCParticle.h"
#include <EVENT/LCRelation.h>
#include <EVENT/ReconstructedParticle.h>
#include "UTIL/LCRelationNavigator.h"

#include "TTree.h"
#include "TMath.h"


void MCParticleFromRelationBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  MCParticleFromRelationBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  if (_writeparameters) CollectionBranches::initBranches(tree, (pre+"mcfr").c_str());

  tree->Branch( (pre+"nmcfrp").c_str() , &_nmcfr , (pre+"nmcfrp/I").c_str() ) ;

  tree->Branch( (pre+"mcfrori").c_str() , _mcfrori , (pre+"mcfrori["+pre+"nmcfrp]/I").c_str() ) ;

  tree->Branch( (pre+"mcfrpdg").c_str() , _mcfrpdg , (pre+"mcfrpdg["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrgst").c_str() , _mcfrgst , (pre+"mcfrgst["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrsst").c_str() , _mcfrsst , (pre+"mcfrsst["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrvtx").c_str() , _mcfrvtx , (pre+"mcfrvtx["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrvty").c_str() , _mcfrvty , (pre+"mcfrvty["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrvtz").c_str() , _mcfrvtz , (pre+"mcfrvtz["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrepx").c_str() , _mcfrepx , (pre+"mcfrepx["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrepy").c_str() , _mcfrepy , (pre+"mcfrepy["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrepz").c_str() , _mcfrepz , (pre+"mcfrepz["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrmox").c_str() , _mcfrmox , (pre+"mcfrmox["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrmoy").c_str() , _mcfrmoy , (pre+"mcfrmoy["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrmoz").c_str() , _mcfrmoz , (pre+"mcfrmoz["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrmas").c_str() , _mcfrmas , (pre+"mcfrmas["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrene").c_str() , _mcfrene , (pre+"mcfrene["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrcha").c_str() , _mcfrcha , (pre+"mcfrcha["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrtim").c_str() , _mcfrtim , (pre+"mcfrtim["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrspx").c_str() , _mcfrspx , (pre+"mcfrspx["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrspy").c_str() , _mcfrspy , (pre+"mcfrspy["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrspz").c_str() , _mcfrspz , (pre+"mcfrspz["+pre+"nmcfrp]/F").c_str() ) ;
  tree->Branch( (pre+"mcfrcf0").c_str() , _mcfrcf0 , (pre+"mcfrcf0["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrcf1").c_str() , _mcfrcf1 , (pre+"mcfrcf1["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrpa0").c_str() , _mcfrpa0 , (pre+"mcfrpa0["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrpa1").c_str() , _mcfrpa1 , (pre+"mcfrpa1["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrda0").c_str() , _mcfrda0 , (pre+"mcfrda0["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrda1").c_str() , _mcfrda1 , (pre+"mcfrda1["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrda2").c_str() , _mcfrda2 , (pre+"mcfrda2["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrda3").c_str() , _mcfrda3 , (pre+"mcfrda3["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrda4").c_str() , _mcfrda4 , (pre+"mcfrda4["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrover").c_str() , _mcfrover , (pre+"mcfrover["+pre+"nmcfrp]/I").c_str() ) ;
  tree->Branch( (pre+"mcfrevis").c_str() , &_mcfrevis , (pre+"mcfrevis/F").c_str() ) ;
  tree->Branch( (pre+"mcfrmmis").c_str() , &_mcfrmmis , (pre+"mcfrmmis/F").c_str() ) ;
  tree->Branch( (pre+"mcfrEmiss").c_str() , &_mcfrEmiss , (pre+"mcfrEmiss/F").c_str() ) ;
  tree->Branch( (pre+"mcfrmvis").c_str() , &_mcfrmvis , (pre+"mcfrmvis/F").c_str() ) ;
  tree->Branch( (pre+"mcfrcosTheta").c_str() , &_mcfrcosTheta , (pre+"mcfrcosTheta/F").c_str() ) ;
  tree->Branch( (pre+"mcfrPtvis").c_str() , &_mcfrPtvis , (pre+"mcfrPtvis/F").c_str() ) ;
  tree->Branch( (pre+"mcfrTheta").c_str() , & _mcfrTheta, (pre+"mcfrTheta/F").c_str() ) ;
  tree->Branch( (pre+"mcfrPxvis").c_str() , &_mcfrPxvis , (pre+"mcfrPxvis/F").c_str() ) ;
  tree->Branch( (pre+"mcfrPyvis").c_str() , &_mcfrPyvis , (pre+"mcfrPyvis/F").c_str() ) ;
  tree->Branch( (pre+"mcfrPzvis").c_str() , &_mcfrPzvis , (pre+"mcfrPzvis/F").c_str() ) ;
  tree->Branch( (pre+"mcfrmmisNoOver").c_str() , &_mcfrmmisNoOver , (pre+"mcfrmmisNoOver/F").c_str() ) ;

}
  

void MCParticleFromRelationBranches::fill(const EVENT::LCCollection* colRel, const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col || !colRel) return ;

  if( col->getTypeName() != lcio::LCIO::RECONSTRUCTEDPARTICLE ){

    std::string exStr("MCParticleFromRelationBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }


  UTIL::LCRelationNavigator* relationNavigatorPFOMC= new UTIL::LCRelationNavigator( colRel );

  if (_writeparameters) CollectionBranches::fill(col, evt);

  _nmcfr  = col->getNumberOfElements() ;
  
   double tempevis=0;
   double tempPxvis=0;
   double tempPyvis=0;
   double tempPzvis=0;
  for(int i=0 ; i < _nmcfr ; ++i){
	EVENT::ReconstructedParticle *recParticle = static_cast<EVENT::ReconstructedParticle*>( col->getElementAt(i) );

	EVENT::LCObjectVec mcVec =  relationNavigatorPFOMC->getRelatedToObjects(recParticle) ;

	if (mcVec.size()==0) return;
    lcio::MCParticle* mcfrp = static_cast<lcio::MCParticle*>(mcVec[0]);
    _mcfrori[i] = mcfrp->ext<CollID>();

    _mcfrpdg[ i ] = mcfrp->getPDG() ;
    _mcfrgst[ i ] = mcfrp->getGeneratorStatus() ;
    _mcfrsst[ i ] = mcfrp->getSimulatorStatus() ;
    _mcfrvtx[ i ] = mcfrp->getVertex()[0] ;
    _mcfrvty[ i ] = mcfrp->getVertex()[1] ;
    _mcfrvtz[ i ] = mcfrp->getVertex()[2] ;
    _mcfrepx[ i ] = mcfrp->getEndpoint()[0] ;
    _mcfrepy[ i ] = mcfrp->getEndpoint()[1] ;
    _mcfrepz[ i ] = mcfrp->getEndpoint()[2] ;
    _mcfrmox[ i ] = mcfrp->getMomentum()[0] ;
    _mcfrmoy[ i ] = mcfrp->getMomentum()[1] ;
    _mcfrmoz[ i ] = mcfrp->getMomentum()[2] ;
    _mcfrmas[ i ] = mcfrp->getMass() ;
    _mcfrene[ i ] = mcfrp->getEnergy() ;
    _mcfrcha[ i ] = mcfrp->getCharge() ;
    _mcfrtim[ i ] = mcfrp->getTime() ;
    _mcfrspx[ i ] = mcfrp->getSpin()[0] ;
    _mcfrspy[ i ] = mcfrp->getSpin()[1] ;
    _mcfrspz[ i ] = mcfrp->getSpin()[2] ;
    _mcfrcf0[ i ] = mcfrp->getColorFlow()[0] ;
    _mcfrcf1[ i ] = mcfrp->getColorFlow()[1] ;
    _mcfrover[ i ] = mcfrp->isOverlay();
    if(!mcfrp->isOverlay())
    {
    	 tempevis += _mcfrene[i] ;
    	 tempPxvis+= _mcfrmox[i] ;
    	 tempPyvis+= _mcfrmoy[i] ;
    	 tempPzvis+= _mcfrmoz[i] ;
    }
    const lcio::MCParticleVec& p = mcfrp->getParents() ;

    // set the parents index - if parents exist; -1 otherwise
    _mcfrpa0[ i ] = ( p.size() > 0 ?  p[0]->ext<CollIndex>() - 1  :  -1 )  ;
    _mcfrpa1[ i ] = ( p.size() > 1 ?  p[1]->ext<CollIndex>() - 1  :  -1 )  ;

    // can we have more than two parents ????

    const lcio::MCParticleVec& p1 = mcfrp->getDaughters() ;

 	 _mcfrda0[ i ] = ( p1.size() > 0 ?  p1[0]->ext<CollIndex>() - 1  :  -1 )  ;
    _mcfrda1[ i ] = ( p1.size() > 1 ?  p1[1]->ext<CollIndex>() - 1  :  -1 )  ;
	 _mcfrda2[ i ] = ( p1.size() > 2 ?  p1[2]->ext<CollIndex>() - 1  :  -1 )  ;
	 _mcfrda3[ i ] = ( p1.size() > 3 ?  p1[3]->ext<CollIndex>() - 1  :  -1 )  ;
	 _mcfrda4[ i ] = ( p1.size() > 4 ?  p1[4]->ext<CollIndex>() - 1  :  -1 )  ;

  }
  _mcfrevis=0;
  _mcfrPxvis=0;
  _mcfrPyvis=0;
  _mcfrPzvis=0;
  for(int irc=0; irc<_nmcfr; ++irc){

	  _mcfrevis += _mcfrene[irc] ;
	  _mcfrPxvis+= _mcfrmox[irc] ;
	  _mcfrPyvis+= _mcfrmoy[irc] ;
	  _mcfrPzvis+= _mcfrmoz[irc] ;
    }
    _mcfrcosTheta= _mcfrPzvis /(sqrt(pow(_mcfrPxvis,2)+pow(_mcfrPyvis,2)+pow(_mcfrPzvis,2)));
    _mcfrPtvis=sqrt(pow(_mcfrPxvis,2)+pow(_mcfrPyvis,2));
    _mcfrTheta= atan2(sqrt(pow(_mcfrPxvis,2)+pow(_mcfrPyvis,2)), _mcfrPzvis);
    _mcfrmvis= sqrt(pow(_mcfrevis,2)-pow(_mcfrPxvis,2)-pow(_mcfrPyvis,2)-pow(_mcfrPzvis,2));
    _mcfrEmiss=350- _mcfrevis;
    double temp = pow (350 - _mcfrevis , 2) - pow (_mcfrPxvis , 2) - pow (_mcfrPyvis , 2) - pow (_mcfrPzvis , 2);
    if (temp <0)
    {
    	temp=400*400;
    }
    _mcfrmmis = sqrt( temp );
    if ((pow (350 - tempevis , 2) - pow (tempPxvis , 2) - pow (tempPyvis , 2) - pow (tempPzvis , 2)) < 0)
    {
      	_mcfrmmisNoOver = sqrt( -pow (350 - tempevis , 2) + pow (tempPxvis , 2) + pow (tempPyvis , 2) + pow (tempPzvis , 2) );

    }
    else
    	{
    	_mcfrmmisNoOver = sqrt( pow (350 - tempevis , 2) - pow (tempPxvis , 2) - pow (tempPyvis , 2) - pow (tempPzvis , 2) );
    	}
    delete relationNavigatorPFOMC;

}
