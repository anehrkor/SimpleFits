#ifndef TrackHelixVertexFitter_h
#define TrackHelixVertexFitter_h

// system include files
#include <TMatrixT.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TVectorD.h>

#include "SimpleFits/FitSoftware/interface/Particle.h"
#include "SimpleFits/FitSoftware/interface/TrackParticle.h"
#include "SimpleFits/FitSoftware/interface/LorentzVectorParticle.h"
#include "SimpleFits/FitSoftware/interface/ErrorMatrixPropagator.h"

class TrackHelixVertexFitter : private ErrorMatrixPropagator {
 public:
  enum FreeVertexPar{x0=0,y0,z0,NFreeVertexPar};
  enum FreeTrackPar{kappa0=3,lambda0,phi0,NFreeTrackPar};
  enum ExtraPar{BField0=0,MassOffSet=1,NExtraPar=1};

  TrackHelixVertexFitter(std::vector<TrackParticle> &particles_);
  virtual ~TrackHelixVertexFitter();

   virtual bool Fit()=0;
   virtual double UpdateChisquare(TMatrixT<double> inpar);
   virtual double ChiSquare(){return chi2;}
   virtual double NDF(){return ndf;}
   LorentzVectorParticle GetMother(int pdgid);
   virtual std::vector<TrackParticle> GetReFitTracks();
   std::vector<LorentzVectorParticle> GetReFitLorentzVectorParticles();
   virtual TVector3 GetVertex();
   virtual TMatrixTSym<double> GetVertexError();

 protected:
   bool isFit;
   TMatrixT<double> par;
   TMatrixTSym<double> parcov;

 private:
   static TMatrixT<double> ComputePar(TMatrixT<double> &inpar);
   static TMatrixT<double> ComputeTrackPar(TMatrixT<double> &inpar,int p=0);
   static TMatrixT<double> ComputeLorentzVectorPar(TMatrixT<double> &inpar);
   static TMatrixT<double> ComputeMotherLorentzVectorPar(TMatrixT<double> &inpar);
   static void Computedxydz(TMatrixT<double> &inpar,int particle,double &c,double &lam,double &phi,double &x,double &y,double &z,double &s,double &dxy,double &dz);

   static int MeasuredValueIndex(int TrackPar,int Particle){
     return TrackPar+Particle*TrackParticle::NHelixPar;
   }
   static int FreeParIndex(int Par,int Particle){
     if(Par==x0 || Par==y0 || Par==z0) return Par;
     return Par+Particle*NFreeTrackPar;
   }

   std::vector<TrackParticle> particles;
   double chi2, ndf;
   TMatrixT<double> val;
   TMatrixTSym<double> cov;
   TMatrixTSym<double> cov_inv;
   int nParticles,nPar,nVal;

};
#endif

