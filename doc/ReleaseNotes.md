# v01-07

# v01-04
* Added JetBranches which holds branches created from a jet collection created by Satoru Jet Finder processor. JetBranches has two steerable parameters which are optionally set in the steering file:
  * writeExtraParameters: if set to TRUE, the fill function calculates some extra parameters using parameters provided by the jet finding algorithm. Default value is FALSE. See class data members for a list of extra parameters.
  * writeTaggingParameters: if set to TRUE, the fill function creates branches for jet parameters coming form flavor tagging processor. If no flavor tagging processr is used, this should be set to FALSE to prevent errors. Default value is FALSE. See class data members for a list of extra parameters.
* Added isolated lepton branches
* Added MC particle from relation branches
* Added MC particle remove overlay branches

# v01-03-01
* add an example for creating an lctuple w/ simhits (F.Gaede)

# v01-03
* added support for TrackerHits

# v01-02
* (J.List) added some variables: MCParticle daughters: mcda0-mcda4 , Event parameters: evene, evpoe, evpop RecoParticles: cluster size: rcncl

# v01-01
* only change : create the TTree with the name of the processor (used to be hard coded LCTuple)

# v01-00
* first version creates CWNT for  MCParticles, ReconstructedParticles, Tracks, Clusters, LCRelations, Vertices
* optionally also SimTrackerHits and SimCalorimeterHits can be written to the ntuple
 
