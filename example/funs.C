

/** Function to sum up a quantity in a tree.
 *  call as 
 *     LCTuple->Draw("sum()","sum( mcene, Iteration$, nmcp,(mcgst==1) )") ;
 *
 */
float sum(float a=0., int iter=0, int N=0, bool cond=true){ 
  
  static float s = 0. ;
  static float r = 0. ;
  
  if(iter==0 && N==0)
    return r ;
  
  if( cond ) 
    s += a ;
  
  if( iter == N-1 ){
    
    r = s ;
    s = 0; 
    return 1 ;
  } 

  return 0 ;
}


/** Helper function for radius
 */
float r(float x,float y) { return sqrt(x*x+y*y) ; }


/** Helper function for subdet id
 */
int sub(int cellid){

  return ( (unsigned) cellid & 0x0000001f ) ;
}
