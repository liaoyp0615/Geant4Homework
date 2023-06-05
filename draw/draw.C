#include "TChain.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooKeysPdf.h"
#include "RooChebychev.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooAbsData.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TLegend.h"
#include "TLegendEntry.h"
using namespace RooFit;

void SetGoodStyle();

void draw(){
	// global setting
	SetGoodStyle();
	TGaxis::SetMaxDigits(3);

	// special setting (comment out if not print the status)
	// gStyle->SetPadTopMargin(0.10);
    // gStyle->SetPadBottomMargin(0.19);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadRightMargin(0.15);
	// gStyle->SetOptStat(221112211);
	// gStyle->SetOptStat(2211);
	// gStyle->SetOptFit(1111);
	// gStyle->SetStatX(.999);
	// gStyle->SetStatY(.999);


	// --- read file
	TChain* t = new TChain("hits");
	TString filename = "output.root";
    t->Add( filename );

	// --- read branch
    Double_t        x;
    Double_t        y;
    Double_t        z;
    Double_t        e;
    Double_t        w;
    Double_t        tx;
    Double_t        ty;
    Double_t        tz;
    Double_t        te;
    Double_t        tw;
    Double_t        bx;
    Double_t        by;
    Double_t        bz;
    Double_t        be;
    Double_t        bw;
    Double_t        hx;
    Double_t        hy;
    Double_t        hz;
    Double_t        he;
    Double_t        hw;
    t->SetBranchAddress("x", &x);
    t->SetBranchAddress("y", &y);
    t->SetBranchAddress("z", &z);
    t->SetBranchAddress("e", &e);
    t->SetBranchAddress("w", &w);
    t->SetBranchAddress("tx", &tx);
    t->SetBranchAddress("ty", &ty);
    t->SetBranchAddress("tz", &tz);
    t->SetBranchAddress("te", &te);
    t->SetBranchAddress("tw", &tw);
    t->SetBranchAddress("bx", &bx);
    t->SetBranchAddress("by", &by);
    t->SetBranchAddress("bz", &bz);
    t->SetBranchAddress("be", &be);
    t->SetBranchAddress("bw", &bw);
    t->SetBranchAddress("hx", &hx);
    t->SetBranchAddress("hy", &hy);
    t->SetBranchAddress("hz", &hz);
    t->SetBranchAddress("he", &he);
    t->SetBranchAddress("hw", &hw);

	// --- define histograms (x,y,z,e)
    double AllHist[12] = { -15,10,50,  -5,7,50,  -30,30,50,  0,4,50};
    double TumorHist[12] = { -13,-3,50,  -5,5,50,  -5,5,50,  0,4,50};
    double BodyHist[12] = { -15,10,50,  -5,7,50,  -30,30,50,  0,4,50};
    double HeadHist[12] = { -12,12,50,  -12,12,50,  20,60,50,  0,4,50};

    TH2D* h_xy = new TH2D("h_xy",";x(cm);y(cm)", AllHist[2],AllHist[0],AllHist[1], AllHist[5],AllHist[3],AllHist[4]);
    TH2D* h_xz = new TH2D("h_xz",";x(cm);z(cm)", AllHist[2],AllHist[0],AllHist[1], AllHist[8],AllHist[6],AllHist[7]);
    TH2D* h_yz = new TH2D("h_yz",";y(cm);z(cm)", AllHist[5],AllHist[3],AllHist[4], AllHist[8],AllHist[6],AllHist[7]);
    TH1D* h_e = new TH1D("h_e",";e(MeV);",AllHist[11],AllHist[9],AllHist[10]);

    TH2D* ht_xy = new TH2D("ht_xy",";x(cm);y(cm)", TumorHist[2],TumorHist[0],TumorHist[1], TumorHist[5],TumorHist[3],TumorHist[4]);
    TH2D* ht_xz = new TH2D("ht_xz",";x(cm);z(cm)", TumorHist[2],TumorHist[0],TumorHist[1], TumorHist[8],TumorHist[6],TumorHist[7]);
    TH2D* ht_yz = new TH2D("ht_yz",";y(cm);z(cm)", TumorHist[5],TumorHist[3],TumorHist[4], TumorHist[8],TumorHist[6],TumorHist[7]);
    TH1D* ht_e = new TH1D("ht_e",";e(MeV);",TumorHist[11],TumorHist[9],TumorHist[10]);

    TH2D* hb_xy = new TH2D("hb_xy",";x(cm);y(cm)", BodyHist[2],BodyHist[0],BodyHist[1], BodyHist[5],BodyHist[3],BodyHist[4]);
    TH2D* hb_xz = new TH2D("hb_xz",";x(cm);z(cm)", BodyHist[2],BodyHist[0],BodyHist[1], BodyHist[8],BodyHist[6],BodyHist[7]);
    TH2D* hb_yz = new TH2D("hb_yz",";y(cm);z(cm)", BodyHist[5],BodyHist[3],BodyHist[4], BodyHist[8],BodyHist[6],BodyHist[7]);
    TH1D* hb_e = new TH1D("hb_e",";e(MeV);",BodyHist[11],BodyHist[9],BodyHist[10]);

    TH2D* hh_xy = new TH2D("hh_xy",";x(cm);y(cm)", HeadHist[2],HeadHist[0],HeadHist[1], HeadHist[5],HeadHist[3],HeadHist[4]);
    TH2D* hh_xz = new TH2D("hh_xz",";x(cm);z(cm)", HeadHist[2],HeadHist[0],HeadHist[1], HeadHist[8],HeadHist[6],HeadHist[7]);
    TH2D* hh_yz = new TH2D("hh_yz",";y(cm);z(cm)", HeadHist[5],HeadHist[3],HeadHist[4], HeadHist[8],HeadHist[6],HeadHist[7]);
    TH1D* hh_e = new TH1D("hh_e",";e(MeV);",HeadHist[11],HeadHist[9],HeadHist[10]);

    // --- fill the histograms
	int nloop = t->GetEntries();
	for(int i=0; i<nloop; i++){
		if(i%2000==0) cout<<"Entry:"<<i<<endl;
		t->GetEntry(i);

        if(e>0.){
            h_xy->Fill(x,y);
            h_xz->Fill(x,z);
            h_yz->Fill(y,z);
            h_e->Fill(e);
        }

        if(te>0.){
            ht_xy->Fill(tx,ty);
            ht_xz->Fill(tx,tz);
            ht_yz->Fill(ty,tz);
            ht_e->Fill(te);
        }

        if(be>0.){
            hb_xy->Fill(bx,by);
            hb_xz->Fill(bx,bz);
            hb_yz->Fill(by,bz);
            hb_e->Fill(be);
        }

        if(he>0.){
            hh_xy->Fill(hx,hy);
            hh_xz->Fill(hx,hz);
            hh_yz->Fill(hy,hz);
            hh_e->Fill(he);
        }
	}

    TCanvas *c1 = new TCanvas("c1","",1700, 1300);
    c1->Divide(2,2);
    c1->cd(1); h_xy->Draw("COLZ");
    c1->cd(2); h_xz->Draw("COLZ");
    c1->cd(3); h_yz->Draw("COLZ");
    c1->cd(4); h_e->Draw("hist");
    c1->Print("all.png");

    TCanvas *c2 = new TCanvas("c2","",1700, 1300);
    c2->Divide(2,2);
    c2->cd(1); ht_xy->Draw("COLZ");
    c2->cd(2); ht_xz->Draw("COLZ");
    c2->cd(3); ht_yz->Draw("COLZ");
    c2->cd(4); ht_e->Draw("hist");
    c2->Print("tumor.png");

    TCanvas *c3 = new TCanvas("c3","",1700, 1300);
    c3->Divide(2,2);
    c3->cd(1); hb_xy->Draw("COLZ");
    c3->cd(2); hb_xz->Draw("COLZ");
    c3->cd(3); hb_yz->Draw("COLZ");
    c3->cd(4); hb_e->Draw("hist");
    c3->Print("body.png");

    TCanvas *c4 = new TCanvas("c4","",1700, 1300);
    c4->Divide(2,2);
    c4->cd(1); hh_xy->Draw("COLZ");
    c4->cd(2); hh_xz->Draw("COLZ");
    c4->cd(3); hh_yz->Draw("COLZ");
    c4->cd(4); hh_e->Draw("hist");
    c4->Print("head.png");
// gPad->SetLogy(); 
}


void SetGoodStyle()
{
    // Good style
    TStyle *GoodStyle= new TStyle("Good","");

    // use plain black on white colors
    GoodStyle->SetFrameBorderMode(0);
    GoodStyle->SetCanvasBorderMode(0);
    GoodStyle->SetPadBorderMode(0);
    GoodStyle->SetPadColor(0);
    GoodStyle->SetCanvasColor(0);
    GoodStyle->SetStatColor(0);
    GoodStyle->SetTitleFillColor(0);

    // set the paper & margin sizes
    GoodStyle->SetPaperSize(20,26);
    GoodStyle->SetCanvasDefX(0);
    GoodStyle->SetCanvasDefY(0);

	// ---- oblong / rectangle
    GoodStyle->SetPadTopMargin(0.14);
    GoodStyle->SetPadBottomMargin(0.17);
    GoodStyle->SetPadLeftMargin(0.17);
    GoodStyle->SetPadRightMargin(0.05);
    GoodStyle->SetTitleOffset(0.92,"x");
    GoodStyle->SetTitleOffset(0.89,"y");
    GoodStyle->SetTitleOffset(1.2,"z");

    // use large Times-Roman fonts
    GoodStyle->SetTitleFont(132,"xyz");  // set the all 3 axes title font
    GoodStyle->SetTitleFont(132," ");    // set the pad title font
    GoodStyle->SetTitleSize(0.08,"xyz"); // set the 3 axes title size
    GoodStyle->SetTitleSize(0.06," ");   // set the pad title size
    GoodStyle->SetLabelFont(132,"xyz");
    GoodStyle->SetLabelSize(0.07,"xyz");
    GoodStyle->SetTextFont(132);
    GoodStyle->SetTextSize(0.08);
	GoodStyle->SetStatFont(132);
	GoodStyle->SetNdivisions(505,"XYZ");

	// use bold lines and markers
    GoodStyle->SetMarkerStyle(20);
    GoodStyle->SetMarkerSize(0.8);
    GoodStyle->SetHistLineWidth(2.);
    GoodStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

    //..Get rid of X error bars
    GoodStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
    GoodStyle->SetOptTitle(0);
    GoodStyle->SetOptStat(0);
    GoodStyle->SetOptFit(0);

    // put tick marks on top and RHS of plots
    GoodStyle->SetPadTickX(1);
    GoodStyle->SetPadTickY(1);

    gROOT->SetStyle("Good");
    gROOT->ForceStyle(kTRUE);
}
