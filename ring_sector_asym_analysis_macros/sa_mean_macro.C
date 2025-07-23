void sa_mean_macro() {
	TTree* tree = (TTree*)gROOT->FindObject("mul");
	Long64_t nEntries = tree->GetEntries();
        tree->SetBranchStatus("*", false);

	const char* detNames[8];
	TLeaf* leaves[8];
	Double_t vmin[8], vmax[8];
	Double_t fmin =  1e30, fmax = -1e30;

	for (int i=0; i<8; ++i) {
	        detNames[i] = Form("asym_sa%02d", i+1);
	        tree->SetBranchStatus(detNames[i], true);
	        TBranch* br = tree->GetBranch(detNames[i]);
	        leaves[i] = br->GetLeaf("hw_sum");
	        vmin[i] =  1e30;
	        vmax[i] = -1e30;
	}

        Double_t mean[8];

        for (int i=0; i<8; ++i) {
                TString branch = Form("asym_sa%02d", i+1);
		TString histname = Form("hsa%d", i+1);
		TString drawcmd = Form("%s>>%s(100, -5e-3, 5e-3)", branch.Data(), histname.Data());
		tree->Draw(drawcmd, "", "goff");
        	TH1F* h1 = (TH1F*)gDirectory->Get(histname);
        	if (h1) {
            		mean[i] = h1->GetMean();
        	} else {
            		mean[i] = 0;
        	}
		if (mean[i] > fmax) fmax = mean[i];
                if (mean[i] < fmin) fmin = mean[i];
	}
        Double_t yrange = fmax - fmin;
        if (yrange < 1e-6) yrange = 1e-6;
        Double_t ymin = fmin - 0.1*yrange;
        Double_t ymax = fmax + 0.1*yrange;
        std::cout << "Histogram:   Min = " << ymin << ", Max = " << ymax << endl;

        TH2F* h = new TH2F ("sam", "Small Angle Detector Mean Asymmetries;Detector Number;Mean Asymmetry", 10, -0.5, 9.5, 1000, ymin, ymax);

       	for (int i = 0; i < 8; ++i) {
       		h->Fill(i+1, mean[i]);
	}

        gStyle->SetPalette(0);
        h->SetStats(false);
        h->Draw();
}
