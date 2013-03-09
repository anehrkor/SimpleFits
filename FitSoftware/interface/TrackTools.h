#ifndef TrackTools_h
#define TrackTools_h

#include "TMatrixT.h"
#include "TMatrixTSym.h"
#include "TVector3.h"
#include "TrackParticle.h"

class  TrackTools {
 public:
  TrackTools(){};
  virtual ~TrackTools(){};
  static TVector3 PropogateToZPosition(TrackParticle &p,double &z);
};
#endif

