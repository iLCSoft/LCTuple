/*
 * =====================================================================================
 *
 *       Filename:  JetBranches.cc
 *
 *    Description:  See JetBranches.h for a description and a list of parameters
 *
 *        Version:  1.0
 *        Created:  20/56/2015 01:53:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Claude Duerig, Felix Mueller, Aliakbar Ebrahimi 
 *   Organization:  DESY
 *
 * =====================================================================================
 */


/* #####   HEADER FILE INCLUDES   ################################################### */
#include "JetBranches.h"
#include "Exceptions.h"
#include "marlin/VerbosityLevels.h"
#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/Vertex.h"

#include "TTree.h"
#include "TMath.h"
#include "UTIL/PIDHandler.h"

#include "EVENT/Vertex.h"

using namespace lcio;

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ############################ */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  JetBranches::initBranches
 *  Description:  Initilises branches to be filled later
 * =====================================================================================
 */
void JetBranches::initBranches( TTree* tree, const std::string& pre){
   
   // Display a debug message on DEBUG4 when entering this function
   streamlog_out(DEBUG4) << "Entering JetBranches::initBranches" << '\n';

   if( tree == 0 ){

	  throw lcio::Exception("  JetBranches::initBranches - invalid tree pointer !!! " ) ;
   }

   if (_writeparameters) CollectionBranches::initBranches(tree, (pre+"j").c_str());

   tree->Branch( (pre+"nj").c_str() , &_nj ,  (pre+"njet/I").c_str() ) ;


   // ------------ Default Jet parameters ------------------//
   tree->Branch( (pre+"jmox").c_str() , _jmox , (pre+"jmox["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jmoy").c_str() , _jmoy , (pre+"jmoy["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jmoz").c_str() , _jmoz , (pre+"jmoz["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jmas").c_str() , _jmas , (pre+"jmas["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jene").c_str() , _jene , (pre+"jene["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcha").c_str() , _jcha , (pre+"jcha["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov0").c_str() , _jcov0 , (pre+"jcov0["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov1").c_str() , _jcov1 , (pre+"jcov1["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov2").c_str() , _jcov2 , (pre+"jcov2["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov3").c_str() , _jcov3 , (pre+"jcov3["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov4").c_str() , _jcov4 , (pre+"jcov4["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov5").c_str() , _jcov5 , (pre+"jcov5["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov6").c_str() , _jcov6 , (pre+"jcov6["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov7").c_str() , _jcov7 , (pre+"jcov7["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov8").c_str() , _jcov8 , (pre+"jcov8["+pre+"njet]/F").c_str() ) ;
   tree->Branch( (pre+"jcov9").c_str() , _jcov9 , (pre+"jcov9["+pre+"njet]/F").c_str() ) ;

   //------------  Tagging Branches --------------//
   if(_writeTaggingParameters) { 
	  tree->Branch( (pre+"btag" ).c_str()  , &_btag  , (pre+"btag["+pre+"njet]/F").c_str() ) ;
	  tree->Branch( (pre+"ctag" ).c_str()  , &_ctag  , (pre+"ctag["+pre+"njet]/F").c_str() ) ;
	  tree->Branch( (pre+"otag" ).c_str()  , &_otag  , (pre+"otag["+pre+"njet]/F").c_str() ) ;
	  tree->Branch( (pre+"bctag" ).c_str() , &_bctag , (pre+"bctag["+pre+"njet]/F").c_str() ) ;
	  tree->Branch( (pre+"bcat" ).c_str()  , &_bcat  , (pre+"bcat["+pre+"njet]/F").c_str() ) ;

	  tree->Branch( (pre+"jnpid" ).c_str() , &_jnpid   ,  (pre+"jnpid/I").c_str() ) ;
	  tree->Branch( (pre+"npfojet").c_str(), &_njetpfo , (pre+"npfojet["+pre+"njet]/I").c_str() ) ;
   } // end if


   // ----------- Extra Parameters -------------//
   if(_writeExtraParameters) {
	  tree->Branch( (pre+"jevis" ).c_str() , &_jevis  , (pre+"jevis/F" ).c_str() ) ;
	  tree->Branch( (pre+"jPxvis").c_str() , &_jPxvis , (pre+"jPxvis/F").c_str() ) ;
	  tree->Branch( (pre+"jPyvis").c_str() , &_jPyvis , (pre+"jPyvis/F").c_str() ) ;
	  tree->Branch( (pre+"jPzvis").c_str() , &_jPzvis , (pre+"jPzvis/F").c_str() ) ;

	  tree->Branch( (pre+"jmom").c_str()   , _jmom    , (pre+"jmom["+pre+"njet]/F").c_str() ) ;
	  tree->Branch( (pre+"jcost").c_str()  , _jcost   , (pre+"jcost["+pre+"njet]/F").c_str() ) ;
	  tree->Branch( (pre+"jcosTheta").c_str() , &_jcosTheta , (pre+"jcosTheta/F").c_str() ) ;
	  tree->Branch( (pre+"jTheta").c_str() , &_jTheta , (pre+"jTheta/F").c_str() ) ;
	  tree->Branch( (pre+"jPtvis").c_str() , &_jPtvis , (pre+"jPtvis/F").c_str() ) ;
	  tree->Branch( (pre+"jmvis" ).c_str() , &_jmvis  , (pre+"jmvis/F" ).c_str() ) ;
	  tree->Branch( (pre+"jmmax" ).c_str() , &_jmmax  , (pre+"jmmax/F" ).c_str() ) ;
	  tree->Branch( (pre+"jEmiss").c_str() , &_jEmiss , (pre+"jEmiss/F").c_str() ) ;
	  tree->Branch( (pre+"jMmissq").c_str(), &_jMmissq, (pre+"jMmissq/F").c_str() ) ;
	  tree->Branch( (pre+"jMmiss").c_str() , &_jMmiss , (pre+"jMmiss/F").c_str() ) ;
   } // end if

} // end function JetBranches::initBranches
  

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  JetBranches::fill
 *  Description:  Fills branches with jet information
 * =====================================================================================
 */
void JetBranches::fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt )
{
  
   // Display a debug message on DEBUG4 when entering this function
   streamlog_out(DEBUG4) << "JetBranches::fill" << '\n';
   streamlog_out(DEBUG4) << "JetColExtra:" << _writeExtraParameters << '\n';
  
   double   Etot = evt->getParameters().getFloatVal("Energy");
  
   // Initilize local variables/arrays to zero
   _nj = 0;
   _jevis  = 0;
   _jPxvis = 0;
   _jPyvis = 0;
   _jPzvis = 0;
   _jmmax  = 0;
   _jTheta    = 0;
   _jcosTheta = 0;
   _jmvis     = 0;
   _jEmiss    = 0;
   _jMmissq   = 0;
   _jMmiss    = 0;

   pid = 0;
   ibtag = 0;
   ictag = 0;
   iotag = 0;
   ibcat = 0;
  
   for ( size_t i = 0; i < LCT_JET_MAX ; ++i ) {
	  _jmox[ i ] = 0;
	  _jmoy[ i ] = 0;
	  _jmoz[ i ] = 0;
	  _jmas[ i ] = 0;
	  _jene[ i ] = 0;
	  _jcha[ i ] = 0;
	  _jcov0[ i ] = 0;
	  _jcov1[ i ] = 0;
	  _jcov2[ i ] = 0;
	  _jcov3[ i ] = 0;
	  _jcov4[ i ] = 0;
	  _jcov5[ i ] = 0;
	  _jcov6[ i ] = 0;
	  _jcov7[ i ] = 0;
	  _jcov8[ i ] = 0;
	  _jcov9[ i ] = 0;
	  // Extra parameters
	  _jmom[ i ]  = 0;
	  _jcost[ i ] = 0;
	  // Tagging parameters
	  _btag[ i ] = 0 ;
	  _ctag[ i ] = 0 ;
	  _otag[ i ] = 0 ;
	  _njetpfo[ i ] = 0 ;
   }

   if( !col ) return ;

   if( col->getTypeName() != lcio::LCIO::RECONSTRUCTEDPARTICLE ){

	  std::string exStr("JetBranches::fill: invalid collection type : " ) ;

	  throw EVENT::Exception( exStr + col->getTypeName() ) ;
   } // end if

   if (_writeparameters) CollectionBranches::fill(col, evt);

   // Get number of jets
   _nj  = col->getNumberOfElements() ;
   streamlog_out(DEBUG4) << "number of jets: " << _nj << '\n';

   //--------- Flavour tagging -------------------------------------------------
   // Write flavor tagginf parameters if it is enabled in the steering file
   if(_writeTaggingParameters) { 
	  pid = new PIDHandler(col) ;
	  algo = pid->getAlgorithmID("lcfiplus");
	  ibtag  = pid->getParameterIndex (algo, "BTag") ;
	  ictag  = pid->getParameterIndex (algo, "CTag") ;
	  iotag  = pid->getParameterIndex (algo, "OTag") ;

	  ibcat  = pid->getParameterIndex (algo, "Category") ;

   } // end if

   //---------  create a helper vector with particleIDs first ------------------

   std::vector<lcio::ParticleID*> pidV ;
   pidV.reserve(  col->getNumberOfElements() * 4 ) ;

   for(size_t i=0 ; i < _nj ; ++i ) {

	  lcio::ReconstructedParticle* jet = static_cast<lcio::ReconstructedParticle*>( col->getElementAt( i) ) ;

	  const EVENT::ParticleIDVec & pids = jet->getParticleIDs() ;

	  for(size_t j=0, npid = pids.size() ; j<npid ; ++j) {

		 pidV.push_back( pids[j] ) ;

		 pids[j]->ext<CollIndex>() =  pidV.size() ;
	  } // end for
   } // end for

   _jnpid = pidV.size() ;

   //-------------------------------------------------------------------------


   //------  fill the Jets ----------------------------
   for(size_t i=0 ; i < _nj ; ++i) {

	  lcio::ReconstructedParticle* jet = static_cast<lcio::ReconstructedParticle*>( col->getElementAt(i) ) ;

	  // Write default jet parameters
	  _jmox[ i ] = jet->getMomentum()[0];
	  _jmoy[ i ] = jet->getMomentum()[1];
	  _jmoz[ i ] = jet->getMomentum()[2];
	  _jmas[ i ] = jet->getMass();
	  _jene[ i ] = jet->getEnergy();
	  _jcha[ i ] = jet->getCharge();
	  _jcov0[ i ] = jet->getCovMatrix()[0];
	  _jcov1[ i ] = jet->getCovMatrix()[1];
	  _jcov2[ i ] = jet->getCovMatrix()[2];
	  _jcov3[ i ] = jet->getCovMatrix()[3];
	  _jcov4[ i ] = jet->getCovMatrix()[4];
	  _jcov5[ i ] = jet->getCovMatrix()[5];
	  _jcov6[ i ] = jet->getCovMatrix()[6];
	  _jcov7[ i ] = jet->getCovMatrix()[7];
	  _jcov8[ i ] = jet->getCovMatrix()[8];
	  _jcov9[ i ] = jet->getCovMatrix()[9];

	  // write tagginf parameters if it is enabled
	  if(_writeTaggingParameters) {
		 std::vector< float > pidvec = pid->getParticleID (jet, algo).getParameters() ;

		 _btag[ i ] = pidvec[ibtag] ;
		 _ctag[ i ] = pidvec[ictag] ;
		 _otag[ i ] = pidvec[iotag] ;

		 _bctag[ i ] = _ctag[ i ] / ( _ctag[ i ] + _btag[ i ] );
		 _bcat[ i ]  = pidvec[ ibcat ] ;

		 _njetpfo[ i ] = jet->getParticles().size() ;
	  } // end if

	  // Calculate and write extra jet parameters if it is enabled
	  if(_writeExtraParameters) {
		 _jmom[ i ] = sqrt( pow(_jmox[i],2) + pow(_jmoy[i],2) + pow(_jmoz[i],2) );
		 _jcost[ i ]= _jmoz [i] / ( sqrt(pow(_jmox[i],2) + pow(_jmoy[i],2) + pow(_jmoz[i],2) ) );
		 _jmmax = (_jmom[ i ] > _jmmax) ? _jmom[ i ] : _jmmax;
		 _jevis += _jene[ i ] ;
		 _jPxvis+= _jmox[ i ] ;
		 _jPyvis+= _jmoy[ i ] ;
		 _jPzvis+= _jmoz[ i ] ;
	  } // end if

   }// end for loop

   // Delete the pid if it is created
   if(_writeTaggingParameters) {
	  delete pid;
   } // end if

   // Calculate some more extra parameters if enabled
   if(_writeExtraParameters) {
	  _jcosTheta = _jPzvis / ( sqrt( pow(_jPxvis,2) + pow(_jPyvis,2) + pow(_jPzvis,2) ) );
	  _jPtvis = sqrt( pow(_jPxvis,2) + pow(_jPyvis,2) );
	  _jTheta = atan2( sqrt( pow(_jPxvis,2) + pow(_jPyvis,2) ), _jPzvis);
	  _jmvis  = sqrt( pow(_jevis,2) - pow(_jPxvis,2) - pow(_jPyvis,2) - pow(_jPzvis,2) );
	  _jEmiss = Etot - _jevis;
	  _jMmissq = pow(_jEmiss,2)-pow(_jPxvis,2)-pow(_jPyvis,2)-pow(_jPzvis,2);
	  if (_jMmissq > 0 ) _jMmiss=sqrt(_jMmissq);
   } // end if

} // end function JetBranches::fill
