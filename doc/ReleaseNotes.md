# v01-12

* 2019-03-26 Ete Remi ([PR#7](https://github.com/iLCSoft/LCTuple/pull/7))
  - Jet branches: added individual particles collection indices to a new output branch `pfoori`
  - Fixed various warning, making this package warning free

* 2018-05-04 Frank Gaede ([PR#5](https://github.com/iLCSoft/LCTuple/pull/5))
  - add possibility to store arbitrary PID parameters for the ReconstructedParticle branch
      - parameter and branches need to be defined in  `PIDBranchDefinition` parameter of LCTuple
      - see [../example/lctupletof.xml](../example/lctupletof.xml) for details

# v01-11

* 2018-03-13 Marko Petric ([PR#4](https://github.com/iLCSoft/LCTuple/pull/4))
  -  Fix for iLCSoft/LCIO#35

# v01-10

* 2017-11-06 Frank Gaede ([PR#3](https://github.com/ilcsoft/LCTuple/pull/3))
  - add CalorimeterHit::getTime() as 'catim'

# v01-09

* 2017-07-26 Frank Gaede ([PR#2](https://github.com/iLCSoft/LCTuple/pull/2))
  - add collection parameters to output collection in MergeCollections
         - add parameter CollectionParameterIndex
          - copy the collection parameters from the given input collection
             to the output collection
          - note: this is done in addition to the collection parameters from all
             collections that are added under a new name w/ the collection name
             prepended

# v01-08

# v01-08

 S.Sasikumar:
  - add parameter rcnrp ( ReconstructedParticle::getParticles().size() ) to RecoParticle branch
  

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
 
