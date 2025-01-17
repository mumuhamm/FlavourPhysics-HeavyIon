// Author: Stephan Hageboeck, CERN, May 2019
/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooJohnsonLocal.h,v 1.16 2007/07/12 20:30:49 wouter Exp $
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_JOHNSON
#define ROO_JOHNSON

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooConstVar.h"

class RooRealVar;

class RooJohnsonLocal final : public RooAbsPdf {
public:
  RooJohnsonLocal() = default;

  RooJohnsonLocal(const char *name, const char *title,
            RooAbsReal& mass, RooAbsReal& mu, RooAbsReal& sigma,
            RooAbsReal& gamma, RooAbsReal& delta,
            double massThreshold = -std::numeric_limits<double>::max());

  RooJohnsonLocal(const RooJohnsonLocal& other, const char* newName = nullptr);

  virtual ~RooJohnsonLocal() = default;

  TObject* clone(const char* newname) const override {
    return new RooJohnsonLocal(*this,newname);
  }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const override;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const override;

  Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK=kTRUE) const override;
  void generateEvent(Int_t code) override;

private:
  enum AnaInt_t {kMass = 1, kMean, kLambda, kGamma, kDelta};

  RooRealProxy _mass;
  RooRealProxy _mu;
  RooRealProxy _lambda;

  RooRealProxy _gamma;
  RooRealProxy _delta;

  double _massThreshold{-1.E300};

  Double_t evaluate() const override;
//  RooSpan<double> evaluateBatch(std::size_t begin, std::size_t end) const override;

  ClassDefInlineOverride(RooJohnsonLocal,1)
};

#endif

