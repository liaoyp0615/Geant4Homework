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
void MakeLegend2(TObject* h1, char * h1name,
        		TObject* h2, char * h2name,
        		double xlow, double ylow, double xhi, double yhi);
void MakeLegend3(TObject* h1, char * h1name,
        		TObject* h2, char * h2name,
                TObject* h3, char * h3name,
        		double xlow, double ylow, double xhi, double yhi);

void dist(){
	// global setting
	SetGoodStyle();
	TGaxis::SetMaxDigits(3);

	// special setting (comment out if not print the status)
	// gStyle->SetPadTopMargin(0.10);
    // gStyle->SetPadBottomMargin(0.19);
    // gStyle->SetPadLeftMargin(0.15);
    // gStyle->SetPadRightMargin(0.15);
	// gStyle->SetOptStat(221112211);
	// gStyle->SetOptStat(2211);
	// gStyle->SetOptFit(1111);
	// gStyle->SetStatX(.999);
	// gStyle->SetStatY(.999);

    TRandom3* ran = new TRandom3();
    TLatex lt;
    lt.SetNDC();
    lt.SetTextAngle(0);
    lt.SetTextSize(0.08);
    lt.SetTextColor(1);

    const int nE = 12;
    Double_t neutronInEdep[nE]={0.1, 0.5, 1, 5, 10, 50, 100, 1000, 10000, 100000, 1000000, 10000000};
    Double_t TumorEdep[nE]={273.883, 507.571, 816.859, 1148.13, 1541.44, 1849.21, 2285.48, 2641.02, 2866.7, 3134.36, 5069.34, 25605.};
    Double_t BodyEdep[nE]={1.40804, 2.79818, 4.11208, 5.44349, 6.77137, 7.98432, 9.20077, 10.3157, 11.6926, 15.0417, 34.1334, 125.752};
    Double_t HeadEdep[nE]={0.0249471, 0.0588974, 0.093829, 0.124865, 0.187808, 0.239395, 0.297241, 0.317535, 0.345088, 0.409845, 0.437819, 0.772505};
    Double_t AllEdep[nE]={2.05872, 4.06213, 6.03368, 8.04572, 10.1173, 11.9628, 13.9268, 15.6781, 17.6555, 22.2191, 48.4854, 184.41};
	Double_t TumorEE[nE]={372.346, 690.046, 1110.53, 1560.89, 2095.6, 2514.01, 3107.13, 3590.48, 3897.3, 4261.18, 6891.81, 34810.1};
    Double_t BodyEE[nE]={2824.26, 5612.59, 8248.02, 10918.6, 13582, 16015, 18454.9, 20691.3, 23453.1, 30170.6, 68464.8, 252234};
    Double_t HeadEE[nE]={12.0913, 28.5462, 45.4767, 60.5192, 91.0263, 116.029, 144.066, 153.902, 167.256, 198.642, 212.2, 374.415};
    Double_t AllEE[nE]={3208.7, 6331.18, 9404.03, 12540, 15768.6, 18645, 21706.1, 24435.7, 27517.7, 34630.4, 75568.9, 287419};
    Double_t TumorRatio[nE] = {};
    Double_t BodyRatio[nE] = {};
    Double_t HeadRatio[nE] = {};
    Double_t TumorDeE[nE] = {};
    Double_t BodyDeE[nE] = {};
    Double_t HeadDeE[nE] = {};
    for(int i=0; i<nE; i++){
        TumorRatio[i] = TumorEE[i] / AllEE[i] * 100.;
        BodyRatio[i] = BodyEE[i] / AllEE[i] * 100.;
        HeadRatio[i] = HeadEE[i] / AllEE[i] * 100.;
        cout << TumorRatio[i] << " " << BodyRatio[i] << " " << HeadRatio[i] << endl;

        TumorDeE[i] = TumorEE[i] / neutronInEdep[i] * 100;
        BodyDeE[i] = BodyEE[i] / neutronInEdep[i] * 100;
        HeadDeE[i] = HeadEE[i] / neutronInEdep[i] * 100;
    }

	TGraph g_tumor(nE, neutronInEdep, TumorEdep);
	TGraph g_body(nE, neutronInEdep, BodyEdep);
    TGraph g_head(nE, neutronInEdep, HeadEdep);
    TGraph g_all(nE, neutronInEdep, AllEdep);

    TGraph g_tumorR(nE, neutronInEdep, TumorRatio);
    TGraph g_bodyR(nE, neutronInEdep, BodyRatio);
    TGraph g_headR(nE, neutronInEdep, HeadRatio);

    TGraph g_tumorD(nE, neutronInEdep, TumorDeE);
    TGraph g_bodyD(nE, neutronInEdep, BodyDeE);
    TGraph g_headD(nE, neutronInEdep, HeadDeE);


    // --- draw
    TCanvas *c1 = new TCanvas("c1","",800, 600);
	TH2D* h1 = new TH2D("h1","", 10,0.01,100000000,10,0.01,100000);
    h1->GetXaxis()->CenterTitle(); h1->GetYaxis()->CenterTitle(); 
    h1->SetXTitle(Form("E_{beam}(neutron) / eV"));
    h1->SetYTitle(Form("Dose / nanoGy"));
    gPad->SetLogx(); gPad->SetLogy();
	h1->Draw();
	g_tumor.SetMarkerStyle(24); g_tumor.SetMarkerColor(4); g_tumor.Draw("P");
	g_body.SetMarkerStyle(20); g_body.SetMarkerColor(1); g_body.Draw("P");
	g_head.SetMarkerStyle(26); g_head.SetMarkerColor(2); g_head.Draw("P");
    g_all.SetMarkerStyle(20); g_all.SetMarkerColor(8); g_all.Draw("P");
    MakeLegend2(&g_tumor,"Tumor", &g_body,"Body",0.20,0.77,0.30,0.87);
    MakeLegend2(&g_head,"Head+Neck", &g_all,"All",0.20,0.67,0.30,0.77);
    c1->Print("figure/dist.png");
    c1->Print("figure/dist.eps");

    // --- draw
    TCanvas *c2 = new TCanvas("c2","",800, 600);
	TH2D* h2 = new TH2D("h2","", 10,0.01,100000000,10,-10,110.);
    h2->GetXaxis()->CenterTitle(); h2->GetYaxis()->CenterTitle(); 
    h2->SetXTitle(Form("E_{beam}(neutron) / eV"));
    h2->SetYTitle(Form("E_{dep} ratio / %%"));
    gPad->SetLogx();
	h2->Draw();
	g_tumorR.SetMarkerStyle(24); g_tumorR.SetMarkerColor(4); g_tumorR.Draw("P");
	g_bodyR.SetMarkerStyle(20); g_bodyR.SetMarkerColor(1); g_bodyR.Draw("P");
	g_headR.SetMarkerStyle(26); g_headR.SetMarkerColor(2); g_headR.Draw("P");
    MakeLegend3(&g_tumorR,"Tumor", &g_bodyR,"Body", &g_headR,"Head+Neck", 0.30,0.52,0.40,0.67);
    c2->Print("figure/ratio.png");
    c2->Print("figure/ratio.eps");

    // --- draw
    TCanvas *c3 = new TCanvas("c3","",800, 600);
	TH2D* h3 = new TH2D("h3","", 10,0.01,100000000,10,0.001,100000000.);
    h3->GetXaxis()->CenterTitle(); h3->GetYaxis()->CenterTitle(); 
    h3->SetXTitle(Form("E_{beam}(neutron) / eV"));
    h3->SetYTitle(Form("E_{dep} / E_{beam}"));
    gPad->SetLogx(); gPad->SetLogy();
	h3->Draw();
	g_tumorD.SetMarkerStyle(24); g_tumorD.SetMarkerColor(4); g_tumorD.Draw("P");
	g_bodyD.SetMarkerStyle(20); g_bodyD.SetMarkerColor(1); g_bodyD.Draw("P");
	g_headD.SetMarkerStyle(26); g_headD.SetMarkerColor(2); g_headD.Draw("P");
    MakeLegend3(&g_tumorD,"Tumor", &g_bodyD,"Body", &g_headD,"Head+Neck", 0.25,0.27,0.35,0.42);
    c3->Print("figure/Edep_E.png");
    c3->Print("figure/Edep_E.eps");
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
    GoodStyle->SetPadTopMargin(0.10);
    GoodStyle->SetPadBottomMargin(0.19);
    GoodStyle->SetPadLeftMargin(0.17);
    GoodStyle->SetPadRightMargin(0.05);
    GoodStyle->SetTitleOffset(1.02,"x");
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

void MakeLegend2(TObject* h1, char * h1name,
        		TObject* h2, char * h2name,
        		double xlow, double ylow, double xhi, double yhi)
{
    TLegend * leg = new TLegend(xlow, ylow, xhi, yhi);
	leg->SetFillStyle(0); leg->SetLineColor(0); leg->SetBorderSize(0);
    leg->SetShadowColor(0); leg->SetTextFont(132);  leg->SetTextAlign(12);  leg->SetTextSize(0.045);
	if(h1 && h1name) leg->AddEntry(h1, h1name);
    if(h2 && h2name) leg->AddEntry(h2, h2name);
	leg->SetTextFont(132);
    leg->Draw();
}

void MakeLegend3(TObject* h1, char * h1name,
        		TObject* h2, char * h2name,
                TObject* h3, char * h3name,
        		double xlow, double ylow, double xhi, double yhi)
{
    TLegend * leg = new TLegend(xlow, ylow, xhi, yhi);
	leg->SetFillStyle(0); leg->SetLineColor(0); leg->SetBorderSize(0);
    leg->SetShadowColor(0); leg->SetTextFont(132);  leg->SetTextAlign(12);  leg->SetTextSize(0.045);
	if(h1 && h1name) leg->AddEntry(h1, h1name);
    if(h2 && h2name) leg->AddEntry(h2, h2name);
    if(h3 && h3name) leg->AddEntry(h3, h3name);
	leg->SetTextFont(132);
    leg->Draw();
}