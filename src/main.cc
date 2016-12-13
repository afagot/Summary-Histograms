#include "../include/fonctions.h"

using namespace std;

int main(int argc ,char *argv[]){
	stringstream converter;
	converter << argv[0];
	string program;
	converter >> program;
	converter.clear();

	if(argc != 1){
			cout << "[Integrals] expects to have 1 parameter\n";
			cout << "[Offline] USAGE is : " << program << "\n";
			return -1;
	} else if(argc == 1){
		//path to the intput file
		string path = "/home/alex/Desktop/RPCs/Lyon_Electronics/Alexis_DATA/Data/Muon-Acceptance/Results/High-Stat-RPC-Thr/";

		//Loop over the different data files (different inclination beta (b) )
		for(int b=4; b<=20; b+=2){
			string ROOTinputName = path + intTostring(b) + "/Results-" + intTostring(b) + ".root";

			TFile ROOTinput(ROOTinputName.c_str(),"READ");

			//Define the 2D histograms to be built
			TH2I* ProfEvol_ts = new TH2I("ProfEvol_ts","Hit profile evolution with increasing T_{scint}",32,0.5,32.5,10,-2.5,47.5);
			ProfEvol_ts->GetXaxis()->SetTitle("Strip");
			ProfEvol_ts->GetYaxis()->SetTitle("T_{scint} (mm)");
			TH2I* ProfEvol_ts_f = new TH2I("ProfEvol_ts_f","Forward hit profile evolution with increasing T_{scint}",32,0.5,32.5,10,-2.5,47.5);
			ProfEvol_ts_f->GetXaxis()->SetTitle("Strip");
			ProfEvol_ts_f->GetYaxis()->SetTitle("T_{scint} (mm)");
			TH2I* ProfEvol_ts_b = new TH2I("ProfEvol_ts_b","Backward hit profile evolution with increasing T_{scint}",32,0.5,32.5,10,-2.5,47.5);
			ProfEvol_ts_b->GetXaxis()->SetTitle("Strip");
			ProfEvol_ts_b->GetYaxis()->SetTitle("T_{scint} (mm)");

			TH2F* RPCDistEvol_ts = new TH2F("RPCDistEvol_ts","RPC path evolution with increasing T_{scint}",100,0,10,10,-2.5,47.5);
			RPCDistEvol_ts->GetXaxis()->SetTitle("Path through gas volume (mm)");
			RPCDistEvol_ts->GetYaxis()->SetTitle("T_{scint} (mm)");
			TH2F* RPCDistEvol_ts_f = new TH2F("RPCDistEvol_ts_f","Forward RPC path  evolution with increasing T_{scint}",100,0,10,10,-2.5,47.5);
			RPCDistEvol_ts_f->GetXaxis()->SetTitle("Path through gas volume (mm)");
			RPCDistEvol_ts_f->GetYaxis()->SetTitle("T_{scint} (mm)");
			TH2F* RPCDistEvol_ts_b = new TH2F("RPCDistEvol_ts_b","Backward RPC path  evolution with increasing T_{scint}",100,0,10,10,-2.5,47.5);
			RPCDistEvol_ts_b->GetXaxis()->SetTitle("Path through gas volume (mm)");
			RPCDistEvol_ts_b->GetYaxis()->SetTitle("T_{scint} (mm)");

			for(int ts=0; ts<=45; ts+=5){
				string profName = "prof-" + intTostring(ts) + "-2.000";
				string profName_f = "prof_f-" + intTostring(ts) + "-2.000";
				string profName_b = "prof_b-" + intTostring(ts) + "-2.000";

				TH1I* Profile = (TH1I*)ROOTinput.Get(profName.c_str());
				TH1I* Profile_f = (TH1I*)ROOTinput.Get(profName_f.c_str());
				TH1I* Profile_b = (TH1I*)ROOTinput.Get(profName_b.c_str());

				int nBinsProfile = Profile->GetNbinsX();

				for(int bp=0; bp<nBinsProfile; bp++){
					int strip = Profile->GetBinCenter(bp+1);
					int nevts = Profile->GetBinContent(bp+1);
					int nevts_f = Profile_f->GetBinContent(bp+1);
					int nevts_b = Profile_b->GetBinContent(bp+1);

					ProfEvol_ts->Fill(strip,ts,nevts);
					ProfEvol_ts_f->Fill(strip,ts,nevts_f);
					ProfEvol_ts_b->Fill(strip,ts,nevts_b);
				}

				string rpcdistName = "rpc-distance-" + intTostring(ts) + "-2.000";
				string rpcdistName_f = "rpc-distance_f-" + intTostring(ts) + "-2.000";
				string rpcdistName_b = "rpc-distance_b-" + intTostring(ts) + "-2.000";

				TH1F* RPCDistance = (TH1F*)ROOTinput.Get(rpcdistName.c_str());
				TH1F* RPCDistance_f = (TH1F*)ROOTinput.Get(rpcdistName_f.c_str());
				TH1F* RPCDistance_b = (TH1F*)ROOTinput.Get(rpcdistName_b.c_str());

				int nBinsRpcDist = RPCDistance->GetNbinsX();

				for(int br=0; br<nBinsRpcDist; br++){
					float distance = RPCDistance->GetBinCenter(br+1);
					int nevts = RPCDistance->GetBinContent(br+1);
					int nevts_f = RPCDistance_f->GetBinContent(br+1);
					int nevts_b = RPCDistance_b->GetBinContent(br+1);

					RPCDistEvol_ts->Fill(distance,ts,nevts);
					RPCDistEvol_ts_f->Fill(distance,ts,nevts_f);
					RPCDistEvol_ts_b->Fill(distance,ts,nevts_b);
				}
			}

			string pevolPDF_ts = "pdf/ProfEvol-ts" + intTostring(b) + ".pdf";
			string pevolSVG_ts = "svg/ProfEvol-ts" + intTostring(b) + ".svg";
			string pevolPDF_ts_f = "pdf/ProfEvol_f-ts" + intTostring(b) + ".pdf";
			string pevolSVG_ts_f = "svg/ProfEvol_f-ts" + intTostring(b) + ".svg";
			string pevolPDF_ts_b = "pdf/ProfEvol_b-ts" + intTostring(b) + ".pdf";
			string pevolSVG_ts_b = "svg/ProfEvol_b-ts" + intTostring(b) + ".svg";

			TCanvas* C_ProfEvol_ts = new TCanvas("C_ProfEvol_ts","C_ProfEvol");
			C_ProfEvol_ts->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			ProfEvol_ts->Draw("COLZ");
			C_ProfEvol_ts->SaveAs(pevolPDF_ts.c_str());
			C_ProfEvol_ts->SaveAs(pevolSVG_ts.c_str());

			TCanvas* C_ProfEvol_ts_f = new TCanvas("C_ProfEvol_ts_f","C_ProfEvol_f");
			C_ProfEvol_ts_f->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			ProfEvol_ts_f->Draw("COLZ");
			C_ProfEvol_ts_f->SaveAs(pevolPDF_ts_f.c_str());
			C_ProfEvol_ts_f->SaveAs(pevolSVG_ts_f.c_str());

			TCanvas* C_ProfEvol_ts_b = new TCanvas("C_ProfEvol_ts_b","C_ProfEvol_b");
			C_ProfEvol_ts_b->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			ProfEvol_ts_b->Draw("COLZ");
			C_ProfEvol_ts_b->SaveAs(pevolPDF_ts_b.c_str());
			C_ProfEvol_ts_b->SaveAs(pevolSVG_ts_b.c_str());

			string rpcdPDF_ts = "pdf/RPCDistEvol-ts" + intTostring(b) + ".pdf";
			string rpcdSVG_ts = "svg/RPCDistEvol-ts" + intTostring(b) + ".svg";
			string rpcdPDF_ts_f = "pdf/RPCDistEvol_f-ts" + intTostring(b) + ".pdf";
			string rpcdSVG_ts_f = "svg/RPCDistEvol_f-ts" + intTostring(b) + ".svg";
			string rpcdPDF_ts_b = "pdf/RPCDistEvol_b-ts" + intTostring(b) + ".pdf";
			string rpcdSVG_ts_b = "svg/RPCDistEvol_b-ts" + intTostring(b) + ".svg";

			TCanvas* C_RPCDistEvol_ts = new TCanvas("C_RPCDistEvol_ts","C_RPCDistEvol");
			C_RPCDistEvol_ts->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			RPCDistEvol_ts->Draw("COLZ");
			C_RPCDistEvol_ts->SaveAs(rpcdPDF_ts.c_str());
			C_RPCDistEvol_ts->SaveAs(rpcdSVG_ts.c_str());

			TCanvas* C_RPCDistEvol_ts_f = new TCanvas("C_RPCDistEvol_ts_f","C_RPCDistEvol_f");
			C_RPCDistEvol_ts_f->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			RPCDistEvol_ts_f->Draw("COLZ");
			C_RPCDistEvol_ts_f->SaveAs(rpcdPDF_ts_f.c_str());
			C_RPCDistEvol_ts_f->SaveAs(rpcdSVG_ts_f.c_str());

			TCanvas* C_RPCDistEvol_ts_b = new TCanvas("C_RPCDistEvol_ts_b","C_RPCDistEvol_b");
			C_RPCDistEvol_ts_b->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			RPCDistEvol_ts_b->Draw("COLZ");
			C_RPCDistEvol_ts_b->SaveAs(rpcdPDF_ts_b.c_str());
			C_RPCDistEvol_ts_b->SaveAs(rpcdSVG_ts_b.c_str());

			//*************************************************************************************************

			//Define the 2D histograms to be built
			TH2I* ProfEvol_tr = new TH2I("ProfEvol","Hit profile evolution with increasing T_{RPC}",32,0.5,32.5,5,1.875,3.125);
			ProfEvol_tr->GetXaxis()->SetTitle("Strip");
			ProfEvol_tr->GetYaxis()->SetTitle("T_{RPC} (mm)");
			TH2I* ProfEvol_tr_f = new TH2I("ProfEvol_f","Forward hit profile evolution with increasing T_{RPC}",32,0.5,32.5,5,1.875,3.125);
			ProfEvol_tr_f->GetXaxis()->SetTitle("Strip");
			ProfEvol_tr_f->GetYaxis()->SetTitle("T_{RPC} (mm)");
			TH2I* ProfEvol_tr_b = new TH2I("ProfEvol_b","Backward hit profile evolution with increasing T_{RPC}",32,0.5,32.5,5,1.875,3.125);
			ProfEvol_tr_b->GetXaxis()->SetTitle("Strip");
			ProfEvol_tr_b->GetYaxis()->SetTitle("T_{RPC} (mm)");

			TH2F* RPCDistEvol_tr = new TH2F("RPCDistEvol","RPC path evolution with increasing T_{RPC}",100,0,10,5,1.875,3.125);
			RPCDistEvol_tr->GetXaxis()->SetTitle("Path through gas volume (mm)");
			RPCDistEvol_tr->GetYaxis()->SetTitle("T_{RPC} (mm)");
			TH2F* RPCDistEvol_tr_f = new TH2F("RPCDistEvol_f","Forward RPC path  evolution with increasing T_{RPC}",100,0,10,5,1.875,3.125);
			RPCDistEvol_tr_f->GetXaxis()->SetTitle("Path through gas volume (mm)");
			RPCDistEvol_tr_f->GetYaxis()->SetTitle("T_{RPC} (mm)");
			TH2F* RPCDistEvol_tr_b = new TH2F("RPCDistEvol_b","Backward RPC path  evolution with increasing T_{RPC}",100,0,10,5,1.875,3.1255);
			RPCDistEvol_tr_b->GetXaxis()->SetTitle("Path through gas volume (mm)");
			RPCDistEvol_tr_b->GetYaxis()->SetTitle("T_{RPC} (mm)");

			for(int tr=0; tr<5; tr++){
				float RPCthr = 2. + (float)(tr*0.25);

				string profName = "prof-00-" + floatTostring(RPCthr);
				string profName_f = "prof_f-00-" + floatTostring(RPCthr);
				string profName_b = "prof_b-00-" + floatTostring(RPCthr);

				TH1I* Profile = (TH1I*)ROOTinput.Get(profName.c_str());
				TH1I* Profile_f = (TH1I*)ROOTinput.Get(profName_f.c_str());
				TH1I* Profile_b = (TH1I*)ROOTinput.Get(profName_b.c_str());

				int nBinsProfile = Profile->GetNbinsX();

				for(int bp=0; bp<nBinsProfile; bp++){
					int strip = Profile->GetBinCenter(bp+1);
					int nevts = Profile->GetBinContent(bp+1);
					int nevts_f = Profile_f->GetBinContent(bp+1);
					int nevts_b = Profile_b->GetBinContent(bp+1);

					ProfEvol_tr->Fill(strip,RPCthr,nevts);
					ProfEvol_tr_f->Fill(strip,RPCthr,nevts_f);
					ProfEvol_tr_b->Fill(strip,RPCthr,nevts_b);
				}

				string rpcdistName = "rpc-distance-00-" + floatTostring(RPCthr);
				string rpcdistName_f = "rpc-distance_f-00-" + floatTostring(RPCthr);
				string rpcdistName_b = "rpc-distance_b-00-" + floatTostring(RPCthr);

				TH1F* RPCDistance = (TH1F*)ROOTinput.Get(rpcdistName.c_str());
				TH1F* RPCDistance_f = (TH1F*)ROOTinput.Get(rpcdistName_f.c_str());
				TH1F* RPCDistance_b = (TH1F*)ROOTinput.Get(rpcdistName_b.c_str());

				int nBinsRpcDist = RPCDistance->GetNbinsX();

				for(int br=0; br<nBinsRpcDist; br++){
					float distance = RPCDistance->GetBinCenter(br+1);
					int nevts = RPCDistance->GetBinContent(br+1);
					int nevts_f = RPCDistance_f->GetBinContent(br+1);
					int nevts_b = RPCDistance_b->GetBinContent(br+1);

					RPCDistEvol_tr->Fill(distance,RPCthr,nevts);
					RPCDistEvol_tr_f->Fill(distance,RPCthr,nevts_f);
					RPCDistEvol_tr_b->Fill(distance,RPCthr,nevts_b);
				}
			}

			string pevolPDF_tr = "pdf/ProfEvol-tr" + intTostring(b) + ".pdf";
			string pevolSVG_tr = "svg/ProfEvol-tr" + intTostring(b) + ".svg";
			string pevolPDF_tr_f = "pdf/ProfEvol_f-tr" + intTostring(b) + ".pdf";
			string pevolSVG_tr_f = "svg/ProfEvol_f-tr" + intTostring(b) + ".svg";
			string pevolPDF_tr_b = "pdf/ProfEvol_b-tr" + intTostring(b) + ".pdf";
			string pevolSVG_tr_b = "svg/ProfEvol_b-tr" + intTostring(b) + ".svg";

			TCanvas* C_ProfEvol_tr = new TCanvas("C_ProfEvol_tr","C_ProfEvol");
			C_ProfEvol_tr->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			ProfEvol_tr->Draw("COLZ");
			C_ProfEvol_tr->SaveAs(pevolPDF_tr.c_str());
			C_ProfEvol_tr->SaveAs(pevolSVG_tr.c_str());

			TCanvas* C_ProfEvol_tr_f = new TCanvas("C_ProfEvol_tr_f","C_ProfEvol_f");
			C_ProfEvol_tr_f->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			ProfEvol_tr_f->Draw("COLZ");
			C_ProfEvol_tr_f->SaveAs(pevolPDF_tr_f.c_str());
			C_ProfEvol_tr_f->SaveAs(pevolSVG_tr_f.c_str());

			TCanvas* C_ProfEvol_tr_b = new TCanvas("C_ProfEvol_tr_b","C_ProfEvol_b");
			C_ProfEvol_tr_b->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			ProfEvol_tr_b->Draw("COLZ");
			C_ProfEvol_tr_b->SaveAs(pevolPDF_tr_b.c_str());
			C_ProfEvol_tr_b->SaveAs(pevolSVG_tr_b.c_str());

			string rpcdPDF_tr = "pdf/RPCDistEvol-tr" + intTostring(b) + ".pdf";
			string rpcdSVG_tr = "svg/RPCDistEvol-tr" + intTostring(b) + ".svg";
			string rpcdPDF_tr_f = "pdf/RPCDistEvol_f-tr" + intTostring(b) + ".pdf";
			string rpcdSVG_tr_f = "svg/RPCDistEvol_f-tr" + intTostring(b) + ".svg";
			string rpcdPDF_tr_b = "pdf/RPCDistEvol_b-tr" + intTostring(b) + ".pdf";
			string rpcdSVG_tr_b = "svg/RPCDistEvol_b-tr" + intTostring(b) + ".svg";

			TCanvas* C_RPCDistEvol_tr = new TCanvas("C_RPCDistEvol_tr","C_RPCDistEvol");
			C_RPCDistEvol_tr->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			RPCDistEvol_tr->Draw("COLZ");
			C_RPCDistEvol_tr->SaveAs(rpcdPDF_tr.c_str());
			C_RPCDistEvol_tr->SaveAs(rpcdSVG_tr.c_str());

			TCanvas* C_RPCDistEvol_tr_f = new TCanvas("C_RPCDistEvol_tr_f","C_RPCDistEvol_f");
			C_RPCDistEvol_tr_f->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			RPCDistEvol_tr_f->Draw("COLZ");
			C_RPCDistEvol_tr_f->SaveAs(rpcdPDF_tr_f.c_str());
			C_RPCDistEvol_tr_f->SaveAs(rpcdSVG_tr_f.c_str());

			TCanvas* C_RPCDistEvol_tr_b = new TCanvas("C_RPCDistEvol_tr_b","C_RPCDistEvol_b");
			C_RPCDistEvol_tr_b->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			RPCDistEvol_tr_b->Draw("COLZ");
			C_RPCDistEvol_tr_b->SaveAs(rpcdPDF_tr_b.c_str());
			C_RPCDistEvol_tr_b->SaveAs(rpcdSVG_tr_b.c_str());

			//*****************************************************************************************

			//Define the 2D histograms to be built
			TH2I* Integral = new TH2I("Integral","Integrated event evolution",10,-2.5,47.5,5,1.875,3.125);
			Integral->GetXaxis()->SetTitle("T_{scint} (mm)");
			Integral->GetYaxis()->SetTitle("T_{RPC} (mm)");

			TH2F* Ratio_backward = new TH2F("Ratio_backward","Backward muon ratio evolution",10,-2.5,47.5,5,1.875,3.125);
			Ratio_backward->GetXaxis()->SetTitle("T_{scint} (mm)");
			Ratio_backward->GetYaxis()->SetTitle("T_{RPC} (mm)");

			TH2F* Ratio_missed = new TH2F("Ratio_missed","Missed muon ratio evolution",10,-2.5,47.5,5,1.875,3.125);
			Ratio_missed->GetXaxis()->SetTitle("T_{scint} (mm)");
			Ratio_missed->GetYaxis()->SetTitle("T_{RPC} (mm)");

			TH2F* Peak_ratio = new TH2F("Peak_ratio","Peak ratio evolution",10,-2.5,47.5,5,1.875,3.125);
			Peak_ratio->GetXaxis()->SetTitle("T_{scint} (mm)");
			Peak_ratio->GetYaxis()->SetTitle("T_{RPC} (mm)");

			TH2I* Peak_Distance = new TH2I("Peak_Distance","Peak distance evolution",10,-2.5,47.5,5,1.875,3.125);
			Peak_Distance->GetXaxis()->SetTitle("T_{scint} (mm)");
			Peak_Distance->GetYaxis()->SetTitle("T_{RPC} (mm)");

			for(int ts=0; ts<=45; ts+=5){
				for(int tr=0; tr<5; tr++){
					float RPCthr = 2.+ (float)(tr*0.25);

					string profName = "prof-" + intTostring(ts) + "-" + floatTostring(RPCthr);
					string profName_f = "prof_f-" + intTostring(ts) + "-" + floatTostring(RPCthr);
					string profName_b = "prof_b-" + intTostring(ts) + "-" + floatTostring(RPCthr);

					TH1I* Profile = (TH1I*)ROOTinput.Get(profName.c_str());
					TH1I* Profile_f = (TH1I*)ROOTinput.Get(profName_f.c_str());
					TH1I* Profile_b = (TH1I*)ROOTinput.Get(profName_b.c_str());

					int nMuons = Profile->GetEntries();
					Integral->Fill(ts,RPCthr,nMuons);

					float backRatio = (float)(Profile_b->GetEntries()/nMuons);
					Ratio_backward->Fill(ts,RPCthr,backRatio);

					float missRatio = (float)(Profile->Integral(1,16)/nMuons);
					Ratio_missed->Fill(ts,RPCthr,missRatio);

					float peakRatio = (float)(Profile_f->GetMaximum()/Profile_b->GetMaximum());
					Peak_ratio->Fill(ts,RPCthr,peakRatio);

					int peakDist = Profile_b->GetMaximumBin() - Profile_f->GetMaximumBin();
					Peak_Distance->Fill(ts,RPCthr,peakDist);
				}


			}

			string integralPDF = "pdf/Integral-" + intTostring(b) + ".pdf";
			string integralSVG = "svg/Integral-" + intTostring(b) + ".svg";

			TCanvas* C_Intergral = new TCanvas("C_Intergral","C_Intergral");
			C_Intergral->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			Integral->Draw("COLZ");
			C_Intergral->SaveAs(integralPDF.c_str());
			C_Intergral->SaveAs(integralSVG.c_str());

			string rbackPDF = "pdf/Ratio_Backward-" + intTostring(b) + ".pdf";
			string rbackSVG = "svg/Ratio_Backward-" + intTostring(b) + ".svg";

			TCanvas* C_Ratio_Backward = new TCanvas("C_Ratio_Backward","C_Ratio_Backward");
			C_Ratio_Backward->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			Ratio_backward->Draw("COLZ");
			C_Ratio_Backward->SaveAs(rbackPDF.c_str());
			C_Ratio_Backward->SaveAs(rbackSVG.c_str());

			string rmissedPDF = "pdf/Ratio_Missed-" + intTostring(b) + ".pdf";
			string rmissedSVG = "svg/Ratio_Missed-" + intTostring(b) + ".svg";

			TCanvas* C_Ratio_Missed = new TCanvas("C_Ratio_Missed","C_Ratio_Missed");
			C_Ratio_Missed->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			Ratio_missed->Draw("COLZ");
			C_Ratio_Missed->SaveAs(rmissedPDF.c_str());
			C_Ratio_Missed->SaveAs(rmissedSVG.c_str());

			string pratioPDF = "pdf/Peak_Ratio-" + intTostring(b) + ".pdf";
			string pratioSVG = "svg/Peak_Ratio-" + intTostring(b) + ".svg";

			TCanvas* C_Peak_Ratio = new TCanvas("C_Peak_Ratio","C_Peak_Ratio");
			C_Peak_Ratio->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			Peak_ratio->Draw("COLZ");
			C_Peak_Ratio->SaveAs(pratioPDF.c_str());
			C_Peak_Ratio->SaveAs(pratioSVG.c_str());

			string pdistPDF = "pdf/Peak_Distance-" + intTostring(b) + ".pdf";
			string pdistSVG = "svg/Peak_Distance-" + intTostring(b) + ".svg";

			TCanvas* C_Peak_Distance = new TCanvas("C_Peak_Distance","C_Peak_Distance");
			C_Peak_Distance->cd(0);
			gStyle->SetOptStat("0");
			gStyle->SetPalette(87);
			Peak_Distance->Draw("COLZ");
			C_Peak_Distance->SaveAs(pdistPDF.c_str());
			C_Peak_Distance->SaveAs(pdistSVG.c_str());
		}

		return 0;
	}
}
