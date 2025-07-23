void etq_trans_ring1_macro() {
    TTree* tree = (TTree*)gROOT->FindObject("evt");
    Long64_t nEntries = tree->GetEntries();
    tree->SetBranchStatus("*", false);

    std::cout << "Transition Ring 1" << std::endl;

    const char* detNames[14];
    TLeaf* leaves[14];
    Double_t vmin[14], vmax[14];
    Double_t fmin = 1e30, fmax = -1e30;

    for (int i = 0; i < 14; ++i) {
        detNames[i] = Form("tq%02d_r1", 2*i+2);
        tree->SetBranchStatus(detNames[i], true);
        TBranch* br = tree->GetBranch(detNames[i]);
        leaves[i] = br->GetLeaf("hw_sum");
        vmin[i] = 1e30;
        vmax[i] = -1e30;
    }

    for (Long64_t ev = 0; ev < nEntries; ev += 100) {
        tree->GetEntry(ev);
        for (int i = 0; i < 14; ++i) {
            Double_t v = leaves[i]->GetValue();
            if (std::isnan(v)) continue;
            if (v < vmin[i]) vmin[i] = v;
            if (v > vmax[i]) vmax[i] = v;
            if (v < fmin) fmin = v;
            if (v > fmax) fmax = v;
        }
    }

    for (int i = 0; i < 14; ++i) {
        std::cout << detNames[i] << ":     Min = " << vmin[i] << ", Max = " << vmax[i] << std::endl;
    }

    std::cout << "First Pass:  Min = " << fmin << ", Max = " << fmax << std::endl;

    Double_t yrange = fmax - fmin;
    if (yrange < 1e-6) yrange = 1e-6;
    Double_t ymin = fmin - 0.5*yrange;
    Double_t ymax = fmax + 0.5*yrange;

    std::cout << "Histogram:   Min = " << ymin << ", Max = " << fmax << endl;

    TH2F* h = new TH2F("ring1t", "Ring 1 Transition Segments;Detector Number;Yield", 16, -0.5, 15.5, 100, ymin, ymax);

    double tmin = 1e30;
    double tmax = -1e30;

    for (Long64_t ev = 0; ev < nEntries; ++ev) {
        tree->GetEntry(ev);
        for (int i = 0; i < 14; ++i) {
            Double_t v = leaves[i]->GetValue();
            if (std::isnan(v)) continue;
            h->Fill(i+1, v);
            if (v < tmin) tmin = v;
            if (v > tmax) tmax = v;
        }
    }

    std::cout << "True Global: Min = " << tmin << ", Max = " << tmax << std::endl;
    std::cout << "---------------------------------------------" << endl;

    h->SetStats(false);
    h->Draw("COLZ");
}
