void amtq_closed_ring6_macro() {
    TTree* tree = (TTree*)gROOT->FindObject("mul");
    Long64_t nEntries = tree->GetEntries();
    tree->SetBranchStatus("*", false);

    std::cout << "Closed Ring 6" << endl;

    const char* detNames[7];
    TLeaf* leaves[7];
    Double_t vmin[7], vmax[7], av[7];
    Double_t fmin =  1e30, fmax = -1e30;

    for (int i = 0; i < 7; ++i) {
        detNames[i] = Form("asym_tq%02d_r6", 4*i+1);
        tree->SetBranchStatus(detNames[i], true);
        TBranch* br = tree->GetBranch(detNames[i]);
        leaves[i] = br->GetLeaf("hw_sum");
        vmin[i] =  1e30;
        vmax[i] = -1e30;
    }

    for (Long64_t ev = 0; ev < nEntries; ev += 10) {
        tree->GetEntry(ev);
        for (int i = 0; i < 7; ++i) {
            Double_t v = leaves[i]->GetValue();
            if (std::isnan(v)) continue;
            if (v < vmin[i]) vmin[i] = v;
            if (v > vmax[i]) vmax[i] = v;
            if (v < fmin) fmin = v;
            if (v > fmax) fmax = v;
        }
    }

    for (int i = 0; i < 7; ++i) {
        std::cout << detNames[i] << ": Min = " << vmin[i] << ", Max = " << vmax[i] << std::endl;
    }

    std::cout << "First Pass:   Min = " << fmin << ", Max = " << fmax << endl;

    Double_t yrange = fmax - fmin;
    if (yrange < 1e-6) yrange = 1e-6;
    Double_t ymin = fmin - 0.5*yrange;
    Double_t ymax= fmax + 0.5*yrange;

    std::cout << "Histogram:    Min = " << ymin << ", Max = " << fmax << endl;

    TH2F* h = new TH2F("ring6c", "Ring 6 Closed Segments;Detector Number;Asymmetry", 9, -0.5, 8.5, 1000, ymin, ymax);

    double tmin = 1e30;
    double tmax = -1e30;

    for (Long64_t ev = 0; ev < nEntries; ++ev) {
        tree->GetEntry(ev);
        for (int i = 0; i < 7; ++i) {
            Double_t v = leaves[i]->GetValue();
            if (std::isnan(v)) continue;
            h->Fill(i+1, v);
            if (v < tmin) tmin = v;
            if (v > tmax) tmax = v;
        }
    }


    std::cout << "True Global:  Min = " << tmin << ", Max = " << tmax << endl;
    std::cout << "---------------------------------------------" << endl;

    h->SetStats(false);
    h->Draw("COLZ");
}
