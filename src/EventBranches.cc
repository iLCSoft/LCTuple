#include "EventBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/ParticleID.h"

#include "TTree.h"

#include <algorithm>

void EventBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  EventBranches::initBranches - invalid tree pointer !!! " ) ;
  }


  tree->Branch( (pre+"evevt").c_str() , &_evevt , (pre+"evevt/I").c_str() ) ;
  tree->Branch( (pre+"evrun").c_str() , &_evrun , (pre+"evrun/I").c_str() ) ;
  tree->Branch( (pre+"evwgt").c_str() , &_evwgt , (pre+"evwgt/F").c_str() ) ;
  tree->Branch( (pre+"evtim").c_str() , &_evtim , (pre+"evtim/L").c_str() ) ;
  tree->Branch( (pre+"evsig").c_str() , &_evsig , (pre+"evsig/F").c_str() ) ;
  tree->Branch( (pre+"evnch").c_str() , &_evnch , (pre+"evnch/I").c_str() ) ;
  tree->Branch( (pre+"evpro").c_str() , &_evpro , (pre+"evpro["+pre+"evnch]/C").c_str() ) ;

}
  

void EventBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  
  _evevt = evt->getEventNumber()  ;    
  _evrun = evt->getRunNumber()  ;
  _evwgt = evt->getWeight()  ;
  _evtim = evt->getTimeStamp()  ;
  
  _evsig = evt->getParameters().getFloatVal("CrossSection_fb")   ;
  

  std::string proc =  evt->getParameters().getStringVal("Process") ;
  _evnch = (int) proc.size()  ;
  
  for(int i=0 ; i < _evnch ; ++i ) {

    _evpro[i]  = proc[i]  ;
  }
}






















