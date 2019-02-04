/*
 * =====================================================================================
 *
 *       Filename:  JetBranches.h
 *
 *    Description:  JetBranches holds branches created from a jet collection
 *					created by Satoru Jet Finder processor.
 *					JetBranches has two steerable parameters which are optionally
 *					set in the steering file:
 *					- writeExtraParameters: if set to TRUE, the fill function
 *					calculates some extra parameters using parameters provided
 *					by the jet finding algorithm. Default value is FALSE.
 *					See class data members for a list of extra parameters.
 *					- writeTaggingParameters: if set to TRUE, the fill function
 *					creates branches for jet parameters coming form flavor tagging
 *					processor. If no flavor tagging processr is used, this should
 *					be set to FALSE to prevent errors. Default value is FALSE.
 *					See class data members for a list of extra parameters.
 *
 *        Version:  1.0
 *        Created:  05/26/2015 02:35:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Claude Duerig, Felix Mueller, Aliakbar Ebrahimi 
 *   Organization:  DESY
 *
 * =====================================================================================
 */

#ifndef JetBranches_h
#define JetBranches_h 1

/* #####   HEADER FILE INCLUDES   ################################################### */
#include <vector>
#include "LCTupleConf.h" 
#include "UTIL/PIDHandler.h"

#include "CollectionBranches.h"


class TTree ;

namespace EVENT{
  class LCCollection ;
  class LCCEvent ;
}

/** JetBranches holds branches created from a ReconstructedParticle collection
 * 
 * @author F. Gaede, DESY
 * @version $Id: JetBranches.h 4433 2013-01-24 13:09:57Z boehmej $
 */


/*
 * =====================================================================================
 *        Class:  JetBranches
 *  Description:  holds branches created by a SatoruJetFinder processor
 * =====================================================================================
 */
class JetBranches : public CollectionBranches
{
   public:
	  /* ====================  LIFECYCLE     ======================================= */
      JetBranches () {};                        /* constructor */
      JetBranches(const JetBranches&) = delete ;
      JetBranches& operator=(const JetBranches&) = delete ;
	  virtual ~JetBranches() {} ;               /* Destructor */

	  /* ====================  ACCESSORS     ======================================= */

	  // Following two functions are used to access parameters set in a steering file
	  void writeExtraParameters(bool setextraparameters){ _writeExtraParameters = setextraparameters; };
	  void writeTaggingParameters(bool settaggingparameters){ _writeTaggingParameters = settaggingparameters; };

	  /* ====================  MUTATORS      ======================================= */

	  /* ====================  OPERATORS     ======================================= */

	  virtual void initBranches( TTree* tree, const std::string& prefix="" ) ; //const char*  prefix=0) ;
	  virtual void fill(const EVENT::LCCollection* col, EVENT::LCEvent* evt ) ;

   private:
	  /* ====================  METHODS       ======================================= */

	  /* ====================  DATA MEMBERS  ======================================= */

	  bool _writeExtraParameters {} ;               /* Whether to write calculated parameters */
      bool _writeTaggingParameters {} ;             /* Whether to write parameters from tagging processor */

      unsigned int    _nj {} ;                     /* Number of Jets */

	  // Deafault jet parameters
	  float  _jmox[ LCT_JET_MAX ] {} ;             /* Jet X-Momentum */
	  float  _jmoy[ LCT_JET_MAX ] {} ;             /* Jet Y-Momentum */
	  float  _jmoz[ LCT_JET_MAX ] {};             /* Jet Z-Momentum */
	  float  _jmas[ LCT_JET_MAX ] {};             /* Jet Mass */
	  float  _jene[ LCT_JET_MAX ] {};             /* Jet Energy */
	  float  _jcha[ LCT_JET_MAX ] {};             /* Jet Charge */
      float  _jcov0[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 0 */
      float  _jcov1[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 1 */
      float  _jcov2[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 2 */
      float  _jcov3[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 3 */
      float  _jcov4[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 4 */
      float  _jcov5[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 5 */
      float  _jcov6[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 6 */
      float  _jcov7[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 7 */
      float  _jcov8[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 8 */
      float  _jcov9[ LCT_JET_MAX ] {};            /* Jet Covariance matrix element 9 */

	  // Used for tagging parameters
      float  _btag[ LCT_JET_MAX ] {};             /* ? */
      float  _ctag[ LCT_JET_MAX ] {};             /* ? */
      float  _bctag[ LCT_JET_MAX ] {};            /* ? */
      float  _bcat[ LCT_JET_MAX ] {};             /* ? */
      float  _otag[ LCT_JET_MAX ] {};             /* ? */
	  int algo{};                                 /* ? */
	  int ibtag{};                                /* ? */
	  int ictag{};                                /* ? */
	  int iotag{};                                /* ? */
	  int ibcat{};                                /* ? */
	  lcio::PIDHandler *pid{};
      int _jnpid   {};                            /* ? */

	  // Used for extra parameters
	  float  _jevis {};			                /* Jet Visible Energy */
	  float  _jPxvis{};                           /* Jet Momentum (x-component) */
	  float  _jPyvis{};                           /* Jet Momentum (y-component) */
	  float  _jPzvis{};                           /* Jet Momentum (z-component) */
      float  _jPtvis{};                           /* Visible transverse momentum */
	  float  _jmom[ LCT_JET_MAX ]{} ;             /* Jet Total Momentum */
	  float  _jmmax{} ;                           /* Maximum mass of the Jets */
	  float  _jcost[ LCT_JET_MAX ] {};            /* ? */
	  float  _jTheta{};                           /* ? */
      float  _jcosTheta{};                        /* Angle between z-axis and jet */
      float  _jmvis{};                            /* Visible mass */
      float  _jEmiss{};                           /* Missing energy */
      float  _jMmiss{};                           /* Missing Mass */
      float  _jMmissq{};                          /* Missing mass squared */

      unsigned int _njetpfo[ LCT_JET_MAX ] {};             /* Number of PFOs in a jet */
      int _jetpfoori[ LCT_JET_MAX ][ LCT_JET_PARTICLES_MAX ] {} ; /* PFOs collection indexes for each jet */


}; /* -----  end of class JetBranches  ----- */

#endif
