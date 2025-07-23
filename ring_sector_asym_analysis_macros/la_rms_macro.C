void la_rms_macro() {
	TTree* tree = (TTree*)gROOT->FindObject("mul");
	Long64_t nEntries = tree->GetEntries();
        tree->SetBranchStatus("*", false);

	const char* detNames[42];
	TLeaf* leaves[42];
	Double_t vmin[42], vmax[42];
	Double_t fmin =  1e30, fmax = -1e30;

	for (int i=0; i<42; ++i) {
	        detNames[i] = Form("asym_la%02d", i+1);
	        tree->SetBranchStatus(detNames[i], true);
	        TBranch* br = tree->GetBranch(detNames[i]);
	        leaves[i] = br->GetLeaf("hw_sum");
	        vmin[i] =  1e30;
	        vmax[i] = -1e30;
	}

        Double_t rms[42];

        for (int i=0; i<42; ++i) {
                TString branch = Form("asym_la%02d", i+1);
		TString histname = Form("hla%d", i+1);
		TString drawcmd = Form("%s>>%s(100, -5e-3, 5e-3)", branch.Data(), histname.Data());
		tree->Draw(drawcmd, "", "goff");
        	TH1F* h1 = (TH1F*)gDirectory->Get(histname);
        	if (h1) {
            		rms[i] = h1->GetRMS();
        	} else {
            		rms[i] = 0;
        	}
		if (rms[i] > fmax) fmax = rms[i];
                if (rms[i] < fmin) fmin = rms[i];
	}
        Double_t yrange = fmax - fmin;
        if (yrange < 1e-6) yrange = 1e-6;
        Double_t ymin = fmin - 0.1*yrange;
        Double_t ymax = fmax + 0.1*yrange;
        std::cout << "Histogram:   Min = " << ymin << ", Max = " << ymax << endl;

        TH2F* h = new TH2F ("lam", "Large Angle Detector RMS Asymmetries;Detector Number;RMS Asymmetry", 44, -0.5, 43.5, 1000, ymin, ymax);

       	for (int i = 0; i < 42; ++i) {
       		h->Fill(i+1, rms[i]);
	}

        gStyle->SetPalette(0);
        h->SetStats(false);
        h->Draw();
}
