#include "RecoParticleBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/Vertex.h"

#include "TTree.h"


void RecoParticleBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  RecoParticleBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  if (_writeparameters) CollectionBranches::initBranches(tree, (pre+"rc").c_str());

  tree->Branch( (pre+"nrec").c_str() , &_nrec ,  (pre+"nrec/I").c_str() ) ;

  tree->Branch( (pre+"rcori").c_str() , _rcori , (pre+"rcori["+pre+"nrec]/I").c_str() ) ;

  tree->Branch( (pre+"rccid").c_str() , _rccid , (pre+"rccid["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rctyp").c_str() , _rctyp , (pre+"rctyp["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rccov").c_str() , _rccov , (pre+"rccov["+pre+"nrec][10]/F").c_str() ) ;
  tree->Branch( (pre+"rcrpx").c_str() , _rcrpx , (pre+"rcrpx["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcrpy").c_str() , _rcrpy , (pre+"rcrpy["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcrpz").c_str() , _rcrpz , (pre+"rcrpz["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcgpi").c_str() , _rcgpi , (pre+"rcgpi["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcpiu").c_str() , _rcpiu , (pre+"rcpiu["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcnpi").c_str() , _rcnpi , (pre+"rcnpi["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcfpi").c_str() , _rcfpi , (pre+"rcfpi["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcmox").c_str() , _rcmox , (pre+"rcmox["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcmoy").c_str() , _rcmoy , (pre+"rcmoy["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcmoz").c_str() , _rcmoz , (pre+"rcmoz["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcmas").c_str() , _rcmas , (pre+"rcmas["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcene").c_str() , _rcene , (pre+"rcene["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rccha").c_str() , _rccha , (pre+"rccha["+pre+"nrec]/F").c_str() ) ;
  tree->Branch( (pre+"rcntr").c_str() , _rcntr , (pre+"rcntr["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcncl").c_str() , _rcncl , (pre+"rcncl["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcnrp").c_str() , _rcnrp , (pre+"rcnrp["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcftr").c_str() , _rcftr , (pre+"rcftr["+pre+"nrec]/I").c_str() ) ;

  tree->Branch( (pre+"rcvts").c_str() , _rcvts , (pre+"rcvts["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rcvte").c_str() , _rcvte , (pre+"rcvte["+pre+"nrec]/I").c_str() ) ;
  tree->Branch( (pre+"rccom").c_str() , _rccom , (pre+"rccom["+pre+"nrec]/I").c_str() ) ;

  tree->Branch( (pre+"npid").c_str() , &_npid , (pre+"npid/I").c_str() ) ;

  tree->Branch( (pre+"pityp").c_str() , _pityp , (pre+"pityp["+pre+"npid]/I").c_str() ) ;
  tree->Branch( (pre+"pipdg").c_str() , _pipdg , (pre+"pipdg["+pre+"npid]/I").c_str() ) ;
  tree->Branch( (pre+"pillh").c_str() , _pillh , (pre+"pillh["+pre+"npid]/F").c_str() ) ;
  tree->Branch( (pre+"pialg").c_str() , _pialg , (pre+"pialg["+pre+"npid]/I").c_str() ) ;
  
}
  

void RecoParticleBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  if( !col ) return ;

  if( col->getTypeName() != lcio::LCIO::RECONSTRUCTEDPARTICLE ){
    
    std::string exStr("RecoParticleBranches::fill: invalid collection type : " ) ;
    
    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }
  
  if (_writeparameters) CollectionBranches::fill(col, evt);

  _nrec  = col->getNumberOfElements() ;
  
  //---------  create a helper vector with particleIDs first -------------------------------

  std::vector<lcio::ParticleID*> pidV ;
  pidV.reserve(  col->getNumberOfElements() * 4 ) ;

  for(int i=0, nrec  = col->getNumberOfElements() ; i < nrec ; ++i ){
    
    lcio::ReconstructedParticle* rec = static_cast<lcio::ReconstructedParticle*>( col->getElementAt( i) ) ;

    const EVENT::ParticleIDVec & pids = rec->getParticleIDs() ;
      
    for(int j=0, npid = pids.size() ; j<npid ; ++j){
	
      pidV.push_back( pids[j] ) ;
	
      pids[j]->ext<CollIndex>() =  pidV.size() ;
    }
  }

  _npid = pidV.size() ;

  //----------  fill the particleIDs ---------------------------------------
  for(int i=0 ; i < _npid ; ++i){
    
    lcio::ParticleID* pid = pidV[i] ;
    
    _pityp[ i ] = pid->getType() ;
    _pipdg[ i ] = pid->getPDG() ;
    _pillh[ i ] = pid->getLikelihood() ;
    _pialg[ i ] = pid->getAlgorithmType() ;
  }



  //------  fill the Reconstructed particle ----------------------------
  for(int i=0 ; i < _nrec ; ++i){
    
    lcio::ReconstructedParticle* rec = static_cast<lcio::ReconstructedParticle*>( col->getElementAt(i) ) ;

    _rcori[i] = rec->ext<CollID>();
    
    _rccid[ i ] = rec->ext<CollID>() ;

    _rctyp[ i ] = rec->getType() ; 

    for( int j=0; j<10 ; ++j )
      _rccov[ i ][ j ]  = rec->getCovMatrix()[j] ;
    
    _rcrpx[ i ] = rec->getReferencePoint()[0] ;
    _rcrpy[ i ] = rec->getReferencePoint()[1] ;
    _rcrpz[ i ] = rec->getReferencePoint()[2] ;
    _rcgpi[ i ] = rec->getGoodnessOfPID() ;
    _rcpiu[ i ] = ( rec->getParticleIDUsed() ?   rec->getParticleIDUsed()->ext<CollIndex>() - 1  :  -1 )   ;

    _rcnpi[ i ] = rec->getParticleIDs().size() ; 
    _rcfpi[ i ] = ( rec->getParticleIDs().size() > 0 ?  rec->getParticleIDs()[0]->ext<CollIndex>() - 1  :  -1 )   ;

    _rcmox[ i ] = rec->getMomentum()[0] ;
    _rcmoy[ i ] = rec->getMomentum()[1] ;
    _rcmoz[ i ] = rec->getMomentum()[2] ;
    _rcmas[ i ] = rec->getMass() ;
    _rcene[ i ] = rec->getEnergy() ;
    _rccha[ i ] = rec->getCharge() ;

    _rcvts[ i ] = ( rec->getStartVertex() ?  rec->getStartVertex()->ext<CollIndex>() - 1  :  -1 )   ; 
    _rcvte[ i ] = ( rec->getEndVertex() ?  rec->getEndVertex()->ext<CollIndex>() - 1  :  -1 )   ; 
    _rccom[ i ] = rec->isCompound();

    _rcntr[ i ] = rec->getTracks().size() ; 
    _rcncl[ i ] = rec->getClusters().size() ; 

    _rcnrp[ i ] = rec->getParticles().size();

    _rcftr[ i ] = ( rec->getTracks().size() > 0 ?  rec->getTracks()[0]->ext<CollIndex>() - 1  :  -1 )   ;
    
  }

}
