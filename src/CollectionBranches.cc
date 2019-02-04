#include "CollectionBranches.h"
#include "Exceptions.h"

#include "Exceptions.h"

#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "marlin/VerbosityLevels.h"

#include "TTree.h"

using namespace lcio ;
using namespace marlin ;

void CollectionBranches::initBranches( TTree* tree, const std::string& pre){

  if( tree == 0 ){
    throw lcio::Exception("  CollectionBranches::initBranches - invalid tree pointer !!! " ) ;
  }

  _parName    = std::vector<std::string>();
  _parOrigin  = std::vector<std::string>();

//   _parIntVal    = std::vector<std::vector<int> >();
//   _parFloatVal  = std::vector<std::vector<float> >();
//   _parStringVal = std::vector<std::vector<std::string> >();

  streamlog_out( DEBUG2 ) << "entered CollectionBranch init" <<  std::endl ;

  tree->Branch( (pre+"npar").c_str(),  &_npar,        (pre+"npar/I").c_str() ) ;
  tree->Branch( (pre+"pana").c_str(),  &_parName) ;
  tree->Branch( (pre+"paor").c_str(),  &_parOrigin) ;
  tree->Branch( (pre+"paod").c_str(),  _parOriginID,  (pre+"paod["+pre+"npar]/I").c_str() ) ;

  tree->Branch( (pre+"pain").c_str(),  _parIntN,      (pre+"pain["+pre+"npar]/I").c_str() ) ;
  tree->Branch( (pre+"paiv").c_str(),  _parIntVal,    (pre+"paiv["+pre+"npar][50]/I").c_str() ) ;

  tree->Branch( (pre+"pafn").c_str(),  _parFloatN,    (pre+"pafn["+pre+"npar]/I").c_str() ) ;
  tree->Branch( (pre+"pafv").c_str(),  _parFloatVal,  (pre+"pafv["+pre+"npar][50]/F").c_str() ) ;

  tree->Branch( (pre+"pasn").c_str(),  _parStringN,   (pre+"pasn["+pre+"npar]/I").c_str() ) ;
  //not yet implemented! 2D vector of strings not well supported by TTree
  //tree->Branch( (pre+"pasv").c_str(),  &_parStringVal) ;
  streamlog_out( DEBUG2 ) << "left CollectionBranch init" <<  std::endl ;

}


void CollectionBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* /*evt*/ ){

  if( !col ) return ;
  streamlog_out( DEBUG2 ) << "entered CollectionBranch fill" <<  std::endl ;

  StringVec mergedCollectionsNames;
  int nMergedCollections = col->getParameters().getStringVals("MergedCollection_NamesPresent",mergedCollectionsNames).size();

  IntVec mergedCollectionsIDs;
//  int nMergedCollectionsID = col->getParameters().getIntVals("MergedCollection_IDsPresent",mergedCollectionsIDs).size();

  streamlog_out( DEBUG2 ) << "found " << nMergedCollections << " merged collections" <<  std::endl ;

  int countparameters=0;
  StringVec intKeys ;
  StringVec floatKeys ;
  StringVec stringKeys ;
  int nIntParameters = col->getParameters().getIntKeys( intKeys ).size() ;
  int nFloatParameters = col->getParameters().getFloatKeys( floatKeys ).size() ;
  int nStringParameters = col->getParameters().getStringKeys( stringKeys ).size() ;

  streamlog_out( DEBUG2 ) << nIntParameters << " int parameters" <<  std::endl ;
  streamlog_out( DEBUG2 ) << nFloatParameters << " float parameters" <<  std::endl ;
  streamlog_out( DEBUG2 ) << nStringParameters << " string parameters" <<  std::endl ;

  _parName.clear();
  _parOrigin.clear();


  if (nMergedCollections != 0){
    for (int i=0; i<(nIntParameters+nFloatParameters+nStringParameters-8);i++){
      _parOriginID[i] = 0;
      _parIntN[i] = 0;
      _parFloatN[i] = 0;
      _parStringN[i] = 0;
      for (int k=0; k<LCT_PARAMVALS_MAX; k++){
        _parIntVal[i][k]=0;
        _parFloatVal[i][k]=0.;
      }
    }

    IntVec mergedCollectionsElements ;
    col->getParameters().getIntVals("MergedCollection_NElements",mergedCollectionsElements);

    IntVec mergedCollectionsIntParameters ;
    col->getParameters().getIntVals("MergedCollection_NIntParameters",mergedCollectionsIntParameters);

    IntVec mergedCollectionsFloatParameters ;
    col->getParameters().getIntVals("MergedCollection_NFloatParameters",mergedCollectionsFloatParameters);

    IntVec mergedCollectionsStringParameters ;
    col->getParameters().getIntVals("MergedCollection_NStringParameters",mergedCollectionsStringParameters);

    for (int j=0; j<nFloatParameters; j++){
      size_t found;
      std::string floatKeyCopy = floatKeys[j];
      found=floatKeyCopy.rfind("MergedCollection_");
      if (found!=std::string::npos) continue;
      for (int i=0; i<nMergedCollections; i++){
        found=floatKeyCopy.rfind(mergedCollectionsNames[i]);
        if (found!=std::string::npos) {
           floatKeyCopy.replace(found,mergedCollectionsNames[i].length()+1,"");
           _parName.push_back(floatKeyCopy);
           _parOrigin.push_back(mergedCollectionsNames[i]);
           _parOriginID[countparameters]=mergedCollectionsIDs[i];
           streamlog_out( DEBUG2 ) << "parameter " << countparameters << ": " << _parName.at(countparameters) << " origin: " << _parOrigin.at(countparameters) << std::endl ;
           FloatVec floatVec ;
           _parFloatN[countparameters]=col->getParameters().getFloatVals(floatKeys[j], floatVec ).size();
           for (unsigned k=0; k<floatVec.size(); k++) {
             _parFloatVal[countparameters][k] = floatVec[k];
             streamlog_out( DEBUG2 ) << "value " << _parFloatVal[countparameters][k] << std::endl ;
           }
           countparameters++;
        }
      }
    }

    for (int j=0; j<nIntParameters; j++){
      size_t found;
      std::string intKeyCopy = intKeys[j];
      found=intKeyCopy.rfind("MergedCollection_");
      if (found!=std::string::npos) continue;
      for (int i=0; i<nMergedCollections; i++){
        found=intKeyCopy.rfind(mergedCollectionsNames[i]);
        if (found!=std::string::npos) {
          intKeyCopy.replace(found,mergedCollectionsNames[i].length()+1,"");
          _parName.push_back(intKeyCopy);
          _parOrigin.push_back(mergedCollectionsNames[i]);
          _parOriginID[countparameters]=mergedCollectionsIDs[i];
          streamlog_out( DEBUG2 ) << "parameter " << countparameters << ": " << _parName.at(countparameters) << " origin: " << _parOrigin.at(countparameters) << std::endl ;
          IntVec intVec ;
          _parIntN[countparameters]=col->getParameters().getIntVals(intKeys[j], intVec ).size();
          for (unsigned k=0; k<intVec.size(); k++){
            _parIntVal[countparameters][k]=intVec[k];
            streamlog_out( DEBUG2 ) << "value " << _parIntVal[countparameters][k] << std::endl ;
          }
          countparameters++;
        }
      }
    }

    for (int j=0; j<nStringParameters; j++){
      size_t found;
      std::string stringKeyCopy = stringKeys[j];
      found=stringKeyCopy.rfind("MergedCollection_");
      if (found!=std::string::npos) continue;
      for (int i=0; i<nMergedCollections; i++){
        found=stringKeyCopy.rfind(mergedCollectionsNames[i]);
        if (found!=std::string::npos) {
          stringKeyCopy.replace(found,mergedCollectionsNames[i].length()+1,"");
          _parName.push_back(stringKeyCopy);
          _parOrigin.push_back(mergedCollectionsNames[i]);
          _parOriginID[countparameters]=mergedCollectionsIDs[i];
          streamlog_out( DEBUG2 ) << "parameter " << countparameters << ": " << _parName[countparameters] << " origin: " << _parOrigin[countparameters] << std::endl ;
          StringVec stringVec ;
          _parStringN[countparameters]=col->getParameters().getStringVals(stringKeys[j], stringVec ).size();
          for (unsigned k=0; k<stringVec.size(); k++){
            //strcpy(**_parStringVal[countparameters][k],stringVec[k].c_str());
            streamlog_out( DEBUG2 ) << "value " << stringVec[k] << std::endl ;
          }
          countparameters++;
        }
      }
    }
  }

  else {
    //init arrays
    for (int i=0; i<(nIntParameters+nFloatParameters+nStringParameters);i++){
      _parOriginID[i] = 0;
      _parOrigin.push_back("");

      _parIntN[i] = 0;
      _parFloatN[i] = 0;
      _parStringN[i] = 0;
      for (int k=0; k<LCT_PARAMVALS_MAX; k++){
        _parIntVal[i][k]=0;
        _parFloatVal[i][k]=0.;
      }
    }

    for (int j=0; j<nFloatParameters; j++){
      _parName.push_back(floatKeys[j]);
      streamlog_out( DEBUG2 ) << "parameter " << countparameters << ": " << _parName.at(countparameters) << " origin: " << _parOrigin.at(countparameters) << std::endl ;
      FloatVec floatVec ;
      _parFloatN[countparameters]=col->getParameters().getFloatVals(floatKeys[j], floatVec ).size();
      for (unsigned k=0; k<floatVec.size(); k++) _parFloatVal[countparameters][k] = floatVec[k];
      countparameters++;
    }

    for (int j=0; j<nIntParameters; j++){
      _parName.push_back(intKeys[j]);
      streamlog_out( DEBUG2 ) << "parameter " << countparameters << ": " << _parName[countparameters] << " origin: " << _parOrigin[countparameters] << std::endl ;
      IntVec intVec ;
      _parIntN[countparameters]=col->getParameters().getIntVals(intKeys[j], intVec).size();
      for (unsigned k=0; k<intVec.size(); k++) _parIntVal[countparameters][k]=intVec[k];
      countparameters++;
    }

    for (int j=0; j<nStringParameters; j++){
      _parName.push_back(stringKeys[j]);
      streamlog_out( DEBUG2 ) << "parameter " << countparameters << ": " << _parName[countparameters] << " origin: " << _parOrigin[countparameters] << std::endl ;
      StringVec stringVec ;
      _parStringN[countparameters]=col->getParameters().getStringVals(stringKeys[j], stringVec ).size();
      //not yet implemented!
      //for (unsigned k=0; k<stringVec.size(); k++) strcpy(**_parStringVal[countparameters][k],stringVec[k].c_str());
      countparameters++;
    }
  }
  _npar=countparameters;
  streamlog_out( DEBUG2 ) << "left CollectionBranch fill" <<  std::endl ;

}






















