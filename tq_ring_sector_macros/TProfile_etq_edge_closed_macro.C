void TProfile_etq_edge_closed_macro() {
        TTree* tree = (TTree*)gROOT->FindObject("evt");
        Long64_t nEntries = tree->GetEntries();
        tree->SetBranchStatus("*", false);

        std::cout << "Edge Closed" << endl;

        const char* l_detNames[7];
	const char* r_detNames[7];
        TLeaf* l_leaves[7];
	TLeaf* r_leaves[7];
        Double_t vlmin[7], vlmax[7];
        Double_t vrmin[7], vrmax[7];
	for (int i = 0; i < 7; ++i) {
        	vlmin[i] = vrmin[i] = 1e30;
        	vlmax[i] = vrmax[i] = -1e30;
	}

        Double_t fmin =  1e30, fmax = -1e30;

        for (int i=0; i<7; ++i) {
                l_detNames[i] = Form("tq%02d_r5l", 4*i+1);
                r_detNames[i] = Form("tq%02d_r5r", 4*i+1);

	        tree->SetBranchStatus(l_detNames[i], true);
                tree->SetBranchStatus(r_detNames[i], true);

                TBranch* l_br = tree->GetBranch(l_detNames[i]);
                TBranch* r_br = tree->GetBranch(r_detNames[i]);

                l_leaves[i] = l_br->GetLeaf("hw_sum");
                r_leaves[i] = r_br->GetLeaf("hw_sum");
        }

    	for (Long64_t ev = 0; ev < nEntries; ev += 100) {
        	tree->GetEntry(ev);
        	for (int i = 0; i < 7; ++i) {
            		Double_t vl = l_leaves[i]->GetValue();
            		if (std::isnan(vl)) continue;
            		if (vl < vlmin[i]) vlmin[i] = vl;
            		if (vl > vlmax[i]) vlmax[i] = vl;
            		if (vl < fmin) fmin = vl;
            		if (vl > fmax) fmax = vl;

        		Double_t vr = r_leaves[i]->GetValue();
        		if (std::isnan(vr)) continue;
        		if (vr < vrmin[i]) vrmin[i] = vr;
        		if (vr > vrmax[i]) vrmax[i] = vr;
        		if (vr < fmin) fmin = vr;
        		if (vr > fmax) fmax = vr;
        	}
	}

    	for (int i = 0; i < 7; ++i) {
        	std::cout << l_detNames[i] << ":    Min = " << vlmin[i] << ", Max = " << vlmax[i] << std::endl;
        	std::cout << r_detNames[i] << ":    Min = " << vrmin[i] << ", Max = " << vrmax[i] << std::endl;
    	}
    	std::cout << "First Pass:  Min = " << fmin << ", Max = " << fmax << endl;

    	Double_t yrange = fmax - fmin;
    	if (yrange < 1e-6) yrange = 1e-6;
    	Double_t ymin = fmin - 0.5*yrange;
    	Double_t ymax = fmax + 0.5*yrange;

    	std::cout << "Histogram:   Min = " << ymin << ", Max = " << fmax << endl;


        TProfile* h = new TProfile ("ec", "Edge Closed Segments;Detector Number;Yield", 16, -0.5, 15.5, ymin, ymax);

    	double tmin = 1e30;
    	double tmax = -1e30;

    	for (Long64_t ev = 0; ev < nEntries; ++ev) {
        	tree->GetEntry(ev);

        	for (int i = 0; i < 7; ++i) {
            		Double_t vl = l_leaves[i]->GetValue();
            		Double_t vr = r_leaves[i]->GetValue();

            		h->Fill(2*i+1, vl);
            		h->Fill(2*i+2, vr);

            		if (vl < tmin) tmin = vl;
            		if (vl > tmax) tmax = vl;
            		if (vr < tmin) tmin = vr;
            		if (vr > tmax) tmax = vr;
        	}
    	}

    	std::cout << "True Global: Min = " << tmin << ", Max = " << tmax << endl;
    	std::cout << "---------------------------------------------" << endl;

    	h->SetStats(false);
    	h->Draw("COLZ");
}
