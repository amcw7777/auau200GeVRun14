/* **************************************************
 *  A class to create and save Npe production QA
 *  histograms.
 *
 *  Authors:  **Kunsu OH        (kunsuoh@gmail.com)
 *            Mustafa Mustafa (mmustafa@lbl.gov)
 *
 *  **Code Maintainer
 * **************************************************
 */


#ifndef __CINT__
#include <iostream>
#include <string>

#include "TFile.h"

#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "TColor.h"
#include "Rtypes.h"
#endif

using namespace std;

void setGraphicsStyle();
void plotPicoNpeProductionQa(string filename);
void setStyle(TH1F* h, Color_t, string ytitle);
void setStyle(TH2F* h, string xtitle, string ytitle);

void plotPicoNpeProductionQa(string filename)
{
    TFile* fInput = new TFile(filename.c_str());
    TH1F* h1TotalEventsInRun         = (TH1F*)fInput->Get("mh1TotalEventsInRun");
    TH1F* h1AverageHftTracksInRun    = (TH1F*)fInput->Get("mh1TotalHftTracksInRun")->Clone("h1AverageHftTracksInRun");
    TH1F* h1AverageGRefMultInRun     = (TH1F*)fInput->Get("mh1TotalGRefMultInRun")->Clone("h1AverageGRefMultInRun");
    TH1F* h1AverageElectronsInRun        = (TH1F*)fInput->Get("mh1TotalElectronsInRun")->Clone("h1AverageElectronsInRun");
    TH1F* h1AveragePartnersInRun        = (TH1F*)fInput->Get("mh1TotalPartnersInRun")->Clone("h1AveragePartnersInRun");
    TH1F* h1AveragePhECandidatesInRun = (TH1F*)fInput->Get("mh1TotalPhECandidatesInRun")->Clone("h1AveragePhECandidatesInRun");
    TH2F* h2NElectronsVsNPartners           = (TH2F*)fInput->Get("mh2NElectronsVsNPartners");
    TH2F* h2PairDcaVsPt              = (TH2F*)fInput->Get("mh2PairDcaVsPt");
    TH2F* h2InvariantMassVsPt              = (TH2F*)fInput->Get("mh2InvariantMassVsPt");
    TH2F* h2ConversionPosition             = (TH2F*)fInput->Get("mh2ConversionPosition");
    TH2F* h2ConversionPosition2             = (TH2F*)fInput->Get("mh2ConversionPositionQaCut");
    
    h1AverageHftTracksInRun->Divide(h1TotalEventsInRun);
    h1AverageGRefMultInRun->Divide(h1TotalEventsInRun);
    h1AverageElectronsInRun->Divide(h1TotalEventsInRun);
    h1AveragePartnersInRun->Divide(h1TotalEventsInRun);
    h1AveragePhECandidatesInRun->Divide(h1TotalEventsInRun);
    
    setStyle(h1AverageHftTracksInRun,1,"<HftMatchTrack>");
    setStyle(h1AverageGRefMultInRun,1,"<gRefMult>");
    setStyle(h1AverageElectronsInRun,1,"<nElectrons>");
    setStyle(h1AveragePartnersInRun,1,"<nPartners>");
    setStyle(h1AveragePhECandidatesInRun,1,"<Photonic electron pair>");
    
    setStyle(h2PairDcaVsPt,"p_{T} [GeV/c]","Pair DCA [cm]");
    setStyle(h2InvariantMassVsPt,"p_{T} [GeV/c]","Invariant mass [GeV/c^{2}]");
    setStyle(h2ConversionPosition,"Position X [cm]","Position Y [cm]");
    setStyle(h2ConversionPosition2,"Position X [cm]","Position Y [cm]");
    
    TCanvas* cv = new TCanvas("cv","cv",800,450);
    h1AverageHftTracksInRun->Draw(); cv->SaveAs("h1AverageHftTracksInRun.png");
    h1AverageGRefMultInRun->Draw(); cv->SaveAs("h1AverageGRefMultInRun.png");
    h1AverageElectronsInRun->Draw(); cv->SaveAs("h1AverageElectronsInRun.png");
    h1AveragePartnersInRun->Draw(); cv->SaveAs("h1AveragePartnersInRun.png");
    h1AveragePhECandidatesInRun->Draw(); cv->SaveAs("h1AveragePhECandidatesInRun.png");
    cv->SetLogz();
    h2NElectronsVsNPartners->Draw("colz"); cv->SaveAs("h2NElectronsVsNPartners.png");
    h2PairDcaVsPt->Draw("colz"); cv->SaveAs("h2PairDcaVsPt.png");
    h2InvariantMassVsPt->Draw("colz"); cv->SaveAs("h2InvariantMassVsPt.png");
    delete cv; TCanvas * cv = new TCanvas("cv","cv",800,800);
    cv->SetLogz();
    h2ConversionPosition->Draw("colz"); cv->SaveAs("h2ConversionPosition.png");
    h2ConversionPosition2->Draw("colz"); cv->SaveAs("h2ConversionPosition2.png");
    delete cv;
    
    fInput->Close();
}

void setStyle(TH1F* h,Color_t color,string title)
{
    h->GetYaxis()->SetTitle(title.c_str());
    h->SetMarkerStyle(20);
    h->SetLineColor(color);
    h->SetMarkerColor(color);
}

void setStyle(TH2F* h, string titleX,  string titleY)
{
    h->GetXaxis()->SetTitle(titleX.c_str());
    h->GetYaxis()->SetTitle(titleY.c_str());
}

void setGraphicsStyle()
{
    // **************************** Set graphic style ***************************************
    gStyle->SetEndErrorSize(5);
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(111);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetPalette(1);
    gStyle->SetCanvasColor(10);
    gStyle->SetFrameFillColor(10);
    gStyle->SetFillColor(4);
    TGaxis::SetMaxDigits(4);
    gStyle->SetPadTopMargin(0.055);
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadRightMargin(0.115);
    gStyle->SetPadLeftMargin(0.115);
    gStyle->SetLabelSize(0.035,"X");
    gStyle->SetLabelSize(0.035,"Y");
    gStyle->SetTitleSize(0.035,"X");
    gStyle->SetTitleSize(0.035,"Y");
    gStyle->SetTitleOffset(0.6,"X");
    gStyle->SetTitleOffset(0.6,"Y");
    gStyle->SetTitleFontSize(0.1);
    gStyle->SetTitleFont(132, "X");
    gStyle->SetTitleFont(132, "Y");
    gStyle->SetTitleFont(132, "Z");
    gStyle->SetTitleOffset(1.2, "Y");
    gStyle->SetStatFont(132);
    gStyle->SetStatFontSize(0.035);
    gStyle->SetStatBorderSize(0);
    gStyle->SetStatX(0.87);
    gStyle->SetStatY(0.87);
    
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t reds[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t greens[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blues[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    Int_t  FI = TColor::CreateGradientColorTable(NRGBs, stops, reds, greens, blues, NCont);
    gStyle->SetNumberContours(NCont);
    gStyle->UseCurrentStyle();
    // **************************************************************************************
}

