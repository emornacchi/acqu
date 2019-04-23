//--Author	JRM Annand   30th Aug 2003
//--Rev 	A.Starostin..24th Jan 2004  add theta,phi
//--Rev 	JRM Annand   30th Jan 2004  mod neighbour determination
//--Rev 	JRM Annand   21st Oct 2004  cluster time
//--Rev 	JRM Annand    9th Mar 2005  protected instead of private vars
//--Rev 	JRM Annand   14th Apr 2005  energy fraction central crystal
//--Rev 	JRM Annand    6th Jun 2005  up to 48 nearest neighbours
//--Rev 	JRM Annand   13th Jul 2005  add Merge function
//--Rev 	JRM Annand   19th Oct 2005  up to 64 nearest neighbours
//--Rev 	JRM Annand   12th May 2007  mean radius
//--Rev 	D Glazier    24th Aug 2007  Add IsTime check
//--Rev 	JRM Annand   20th Nov 2009  Adjustable energy weighting
//--Update	JRM Annand   17th Sep 2011  log energy weighting
//--Description
//                *** Acqu++ <-> Root ***
// Online/Offline Analysis of Sub-Atomic Physics Experimental Data 
//
// HitCluster_t
// Specimen for hit cluster determination in a segmented calorimeter
// Mean cluster position obtained from the sqrt(E) weighted sum
//
//---------------------------------------------------------------------------
#ifndef __HitCluster_t_h__
#define __HitCluster_t_h__

#include "TMath.h"
#include "TVector3.h"
#include "EnumConst.h"

class TA2ClusterDetector;

class HitCluster_t{
protected:
  TVector3* fMeanPosition;             // energy-weighted mean pos. of clust.
  UInt_t* fNeighbour;                  // indices of neighbouring elements
  UInt_t fIndex;                       // index of central element
  Double_t fEnergy;                    // Total energy deposited in cluster
  Double_t fCentralFrac;               // Fractional energy in central crystal
  Double_t fSqrtEtot;                  // Sum of sqrt( energy[i] )
  Double_t fTime;                      // Time of max-energy element of cluster
  Double_t fTheta;                     // Cluster's theta
  Double_t fPhi;                       // Cluster's phi
  Double_t fRadius;                    // energy-weighted "radius" of cluster
  UInt_t fNNeighbour;                  // # neighbour elements in array
  Int_t fMaxHits;                      // size of hits array
  UInt_t fNNearNeighbour;              // # nearest neighbours
  UInt_t* fHits;                       // indices of hit elements
  Double_t* fEnergies;                 // energies of hit elements  
  Double_t* fTimes;                    // times of hit elements  
  UInt_t fNhits;                       // # of hits in cluster
public:
  HitCluster_t(char* line, UInt_t index, Int_t sizefactor = 1);
  virtual ~HitCluster_t();
  virtual void ClusterDetermine( TA2ClusterDetector* ) = 0;
  virtual void Cleanup();
  virtual void BuildElementary(TA2ClusterDetector* det);
  virtual Bool_t IsNeighbour( UInt_t );
  virtual void Merge( HitCluster_t* );
  virtual Double_t OpeningAngle( HitCluster_t* );

  TVector3* GetMeanPosition(){ return fMeanPosition; }
  UInt_t* GetNeighbour(){ return fNeighbour; }
  UInt_t GetIndex(){ return fIndex; }
  Double_t GetEnergy(){ return fEnergy; }
  Double_t GetCentralFrac(){ return fCentralFrac; }
  Double_t GetSqrtEtot(){ return fSqrtEtot; }
  Double_t GetTime(){ return fTime; }
  Double_t GetTheta(){ return fTheta;}
  Double_t GetPhi(){ return fPhi;}
  Double_t GetRadius(){ return fRadius;}
  UInt_t GetNNeighbour(){ return fNNeighbour; }
  Int_t GetMaxHits(){ return fMaxHits; }
  UInt_t GetNNearNeighbour(){ return fNNearNeighbour; }
  UInt_t* GetHits(){ return fHits; }
  Double_t* GetEnergies(){ return fEnergies; }  
  Double_t* GetTimes(){ return fTimes; }  
  UInt_t GetNhits(){ return fNhits; }
  //
  UInt_t* GetNhitsPtr(){ return &fNhits; }
  Double_t* GetEnergyPtr(){ return &fEnergy; }
  Double_t* GetTimePtr(){ return &fTime; }
};

//---------------------------------------------------------------------------
inline void HitCluster_t::Cleanup()
{
  // End-of-Event cleanup
  fNhits = 0;
  *fHits = ENullHit;
  fEnergy = (Double_t)ENullHit;
  fTime = (Double_t)ENullHit;
}

//---------------------------------------------------------------------------
inline Bool_t HitCluster_t::IsNeighbour( UInt_t i )
{
  // Is element i a neighbour of the central cluster element
  UInt_t j;
  UInt_t* neighbour = fNeighbour;
  for(j=0; j<fNNeighbour; j++){
    if( i == *neighbour++ ) return ETrue;
  }
  return EFalse;
}

//---------------------------------------------------------------------------
inline void HitCluster_t::Merge( HitCluster_t* cl )
{
  // Merge cluster pointed to by cl with present cluster
  // merged-cluster position sqrt(Energy)-weighted sum of positions
  // merged-cluster Energy = sum of two energies

  Error("Merge", "Not implemented in base class!");
}

//---------------------------------------------------------------------------
inline Double_t HitCluster_t::OpeningAngle( HitCluster_t* cl )
{
  // Opening angle in deg. of cluster pointed to by cl with respect to
  // the present cluster
  return fMeanPosition->Angle( *(cl->GetMeanPosition()) ) * TMath::RadToDeg();
}

#endif
