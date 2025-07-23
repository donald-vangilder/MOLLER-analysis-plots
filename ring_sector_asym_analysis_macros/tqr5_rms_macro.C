void tqr5_rms_macro() {
	TTree* tree = (TTree*)gROOT->FindObject("mul");
	Long64_t nEntries = tree->GetEntries();

        Double_t fmin =  1e30, fmax = -1e30;

        const char* detNames_l[28];
        const char* detNames_c[28];
        const char* detNames_r[28];
        TLeaf* leaves_l[28];
        TLeaf* leaves_c[28];
        TLeaf* leaves_r[28];
        Double_t vmin_l[28], vmax_l[28];
        Double_t vmin_c[28], vmax_c[28];
        Double_t vmin_r[28], vmax_r[28];
        Double_t rms_l[28];
        Double_t rms_c[28];
        Double_t rms_r[28];

        for (int i=0; i<28; ++i) {
                detNames_l[i] = Form("asym_tq%02d_r5l", i+1);
                detNames_c[i] = Form("asym_tq%02d_r5c", i+1);
                detNames_r[i] = Form("asym_tq%02d_r5r", i+1);

                tree->SetBranchStatus(detNames_l[i], true);
                tree->SetBranchStatus(detNames_c[i], true);
                tree->SetBranchStatus(detNames_r[i], true);

                TBranch* br_l = tree->GetBranch(detNames_l[i]);
                TBranch* br_c = tree->GetBranch(detNames_c[i]);
                TBranch* br_r = tree->GetBranch(detNames_r[i]);

                leaves_l[i] = br_l->GetLeaf("hw_sum");
                leaves_c[i] = br_c->GetLeaf("hw_sum");
                leaves_r[i] = br_r->GetLeaf("hw_sum");

                vmin_l[i] =  1e30;
                vmax_l[i] = -1e30;
                vmin_c[i] =  1e30;
                vmax_c[i] = -1e30;
                vmin_r[i] =  1e30;
                vmax_r[i] = -1e30;
        }


        for (int i=0; i<28; ++i) {
                TString branch_l = Form("asym_tq%02d_r5l", i+1);
                TString branch_c = Form("asym_tq%02d_r5c", i+1);
                TString branch_r = Form("asym_tq%02d_r5r", i+1);

                TString histname_l = Form("htq%02d_r5l", i+1);
                TString histname_c = Form("htq%02d_r5c", i+1);
                TString histname_r = Form("htq%02d_r5r", i+1);

                TString drawcmd_l = Form("%s>>%s(100, -1, 1)", branch_l.Data(), histname_l.Data());
                TString drawcmd_c = Form("%s>>%s(100, -1, 1)", branch_c.Data(), histname_c.Data());
                TString drawcmd_r = Form("%s>>%s(100, -1, 1)", branch_r.Data(), histname_r.Data());

                tree->Draw(drawcmd_l, "", "goff");
                tree->Draw(drawcmd_c, "", "goff");
                tree->Draw(drawcmd_r, "", "goff");

                TH1F* h1 = (TH1F*)gDirectory->Get(histname_l);
                if (h1) {
                        rms_l[i] = h1->GetRMS();
                } else {
                        rms_l[i] = 0;
                }
                if (rms_l[i] > fmax) fmax = rms_l[i];
                if (rms_l[i] < fmin) fmin = rms_l[i];

                TH1F* h2 = (TH1F*)gDirectory->Get(histname_c);
                if (h2) {
                        rms_c[i] = h2->GetRMS();
                } else {
                        rms_c[i] = 0;
                }
                if (rms_c[i] > fmax) fmax = rms_c[i];
                if (rms_c[i] < fmin) fmin = rms_c[i];

                TH1F* h3 = (TH1F*)gDirectory->Get(histname_r);
                if (h3) {
                        rms_r[i] = h3->GetRMS();
                } else {
                        rms_r[i] = 0;
                }
                if (rms_r[i] > fmax) fmax = rms_r[i];
                if (rms_r[i] < fmin) fmin = rms_r[i];
        }

        Double_t yrange = fmax - fmin;
        if (yrange < 1e-6) yrange = 1e-6;
        Double_t ymin = fmin - 0.1*yrange;
        Double_t ymax = fmax + 0.1*yrange;
        std::cout << "Histogram:   Min = " << ymin << ", Max = " << ymax << endl;

	TH2F* h = new TH2F("r5r", "Thin Quartz Ring 5 RMS Asymmetries vs Segment;Segment Number;RMS Asymmetry", 86, -0.5, 85.5, 1000, ymin, ymax);

	for (int i = 0; i < 28; ++i) {
                h->Fill(3*i+1, rms_l[i]);
                h->Fill(3*i+2, rms_c[i]);
                h->Fill(3*i+3, rms_r[i]);
        }

        gStyle->SetPalette(0);
	h->SetStats(false);
	h->Draw();
}
