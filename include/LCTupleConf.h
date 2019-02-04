#ifndef LCTupleConf_h
#define LCTupleConf_h 1


#include "LCRTRelations.h"
//==== define user extension for index in collection

struct CollIndex : public lcrtrel::LCIntExtension<CollIndex> {} ;

//==== define user extension for collection IDs
struct CollID : public lcrtrel::LCIntExtension<CollID> {} ;



// ===== define constants needed for LCTuple =================


// =================================================================
//
//     maximum number of elements in colum wise ntuple
//
//         => ADJUST AS NEEDED !!!!!!
// =================================================================

#define LCT_COLLENTRIES_MAX       1000000
#define LCT_MCPARTICLE_MAX        1000000
#define LCT_RECOPARTICLE_MAX       100000
#define LCT_TRACK_MAX              100000
#define LCT_TRACKSTATE_MAX        1000000
#define LCT_CLUSTER_MAX            100000
#define LCT_RELATION_MAX          1000000
#define LCT_SIMTRACKERHIT_MAX     1000000
#define LCT_TRACKERHIT_MAX        1000000
#define LCT_SIMCALORIMETERHIT_MAX 1000000
#define LCT_CALORIMETERHIT_MAX    1000000
#define LCT_PARTICLEID_MAX        1000000
#define LCT_VERTEX_MAX               1000
#define LCT_JET_MAX				       20
#define LCT_JET_PARTICLES_MAX				  500
#define LCT_ISOLEP_MAX             100000

#define LCT_STRING_MAX       1024

#define LCT_PARAMETERS_MAX        1000
#define LCT_PARAMVALS_MAX         50



//-------------------------------------------------------------------


#endif
