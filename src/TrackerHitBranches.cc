#include "TrackerHitBranches.h"
#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/TrackerHit.h"
#include "EVENT/MCParticle.h"
#include "streamlog/streamlog.h"

#include "TTree.h"


void TrackerHitBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){

    throw lcio::Exception("  TrackerHitBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  if (_writeparameters) CollectionBranches::initBranches(tree, (pre+"st").c_str());

  tree->Branch( (pre+"ntrh").c_str() , &_ntrh , (pre+"ntrh/I").c_str() ) ;

  tree->Branch( (pre+"thori").c_str() , _thori , (pre+"thori["+pre+"ntrh]/I").c_str() ) ;
  tree->Branch( (pre+"thci0").c_str() , _thci0 , (pre+"thci0["+pre+"ntrh]/I").c_str() ) ;
  tree->Branch( (pre+"thci1").c_str() , _thci1 , (pre+"thci1["+pre+"ntrh]/I").c_str() ) ;
  tree->Branch( (pre+"thpox").c_str() , _thpox , (pre+"thpox["+pre+"ntrh]/D").c_str() ) ;
  tree->Branch( (pre+"thpoy").c_str() , _thpoy , (pre+"thpoy["+pre+"ntrh]/D").c_str() ) ;
  tree->Branch( (pre+"thpoz").c_str() , _thpoz , (pre+"thpoz["+pre+"ntrh]/D").c_str() ) ;
  tree->Branch( (pre+"thedp").c_str() , _thedp , (pre+"thedp["+pre+"ntrh]/F").c_str() ) ;
  tree->Branch( (pre+"thtim").c_str() , _thtim , (pre+"thtim["+pre+"ntrh]/F").c_str() ) ;
  
  tree->Branch( (pre+"thcov").c_str() , _thcov , (pre+"thcov["+pre+"ntrh][6]/F").c_str() ) ;

  tree->Branch( (pre+"thtyp").c_str() , _thtyp , (pre+"thtyp["+pre+"ntrh]/F").c_str() ) ;
  tree->Branch( (pre+"thqua").c_str() , _thqua , (pre+"thqua["+pre+"ntrh]/F").c_str() ) ;
  tree->Branch( (pre+"thede").c_str() , _thede , (pre+"thede["+pre+"ntrh]/F").c_str() ) ;

}
  

void TrackerHitBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ){
  

  streamlog_out( DEBUG ) << " TrackerHitBranches::fill called ... (col: " << col << ")" << std::endl ;

  if( !col ) return ;


  if( col->getTypeName() != lcio::LCIO::TRACKERHIT && col->getTypeName() != lcio::LCIO::TRACKERHITPLANE && col->getTypeName() != lcio::LCIO::TRACKERHITZCYLINDER ){

    std::string exStr("TrackerHitBranches::fill: invalid collection type : " ) ;

    throw EVENT::Exception( exStr + col->getTypeName() ) ; 
  }

  if (_writeparameters) CollectionBranches::fill(col, evt);

  _ntrh  = col->getNumberOfElements() ;
  
  for(int i=0 ; i < _ntrh ; ++i){
    
    lcio::TrackerHit* hit = static_cast<lcio::TrackerHit*>( col->getElementAt(i) ) ;

    _thori[i] = hit->ext<CollID>();

    _thci0[i] = hit->getCellID0() ;
    _thci1[i] = hit->getCellID1() ;
    _thpox[i] = hit->getPosition()[0] ;
    _thpoy[i] = hit->getPosition()[1] ;
    _thpoz[i] = hit->getPosition()[2] ;
    _thedp[i] = hit->getEDep() ;
    _thtim[i] = hit->getTime() ;

    for(int j=0;j<6;++j){
      _thcov[ i ][ j ] = hit->getCovMatrix()[j] ;
    }

    _thtyp[ i ] = hit->getType()      ;
    _thqua[ i ] = hit->getQuality()   ;
    _thede[ i ] = hit->getEDepError() ;
    
    //not yet...    virtual const LCObjectVec & getRawHits() const = 0;
  }
}






















