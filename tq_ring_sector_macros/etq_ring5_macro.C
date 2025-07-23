void etq_ring5_macro() {
    gDirectory->Delete("*");

    TTree* tree = (TTree*)gROOT->FindObject("evt");
    Long64_t nEntries = tree->GetEntries();
    tree->SetBranchStatus("*", false);

    std::cout << "\n\n\n\nAll Ring 5 Segments" << endl;

    std::vector<std::string> segments(28);
    for (int j=0; j<7; j++) {
        segments[4*j] = Form("closed %d", 4*j+1);
        segments[4*j+1] = Form("transition %d", 4*j+2);
        segments[4*j+2] = Form("open %d", 4*j+3);
        segments[4*j+3] = Form("transition %d", 4*j+4);
    }

    const char* detNames_l[28];
    const char* detNames_c[28];
    const char* detNames_r[28];
    TLeaf* leaf_r5l[28];
    TLeaf* leaf_r5c[28];
    TLeaf* leaf_r5r[28];

    Double_t vlmin[28], vlmax[28];
    Double_t vcmin[28], vcmax[28];
    Double_t vrmin[28], vrmax[28];
    for (int i = 0; i < 28; ++i) {
        vlmin[i] = vcmin[i] = vrmin[i] = 1e30;
        vlmax[i] = vcmax[i] = vrmax[i] = -1e30;
    }

    Double_t fmin = 1e30, fmax = -1e30;

    for (int i = 0; i < 28; ++i) {
        detNames_l[i] = Form("tq%02d_r5l", i+1);
        detNames_c[i] = Form("tq%02d_r5c", i+1);
        detNames_r[i] = Form("tq%02d_r5r", i+1);

        tree->SetBranchStatus(detNames_l[i], true);
        tree->SetBranchStatus(detNames_c[i], true);
        tree->SetBranchStatus(detNames_r[i], true);

        TBranch* br_l = tree->GetBranch(detNames_l[i]);
        TBranch* br_c = tree->GetBranch(detNames_c[i]);
        TBranch* br_r = tree->GetBranch(detNames_r[i]);

        leaf_r5l[i] = br_l->GetLeaf("hw_sum");
        leaf_r5c[i] = br_c->GetLeaf("hw_sum");
        leaf_r5r[i] = br_r->GetLeaf("hw_sum");
    }

    for (Long64_t ev = 0; ev < nEntries; ev += 100) {
        tree->GetEntry(ev);
        for (int i = 0; i < 28; ++i) {
            Double_t vl = leaf_r5l[i]->GetValue();
            if (std::isnan(vl)) continue;
            if (vl < vlmin[i]) vlmin[i] = vl;
            if (vl > vlmax[i]) vlmax[i] = vl;
            if (vl < fmin) fmin = vl;
            if (vl > fmax) fmax = vl;

            Double_t vc = leaf_r5c[i]->GetValue();
            if (std::isnan(vc)) continue;
            if (vc < vcmin[i]) vcmin[i] = vc;
            if (vc > vcmax[i]) vcmax[i] = vc;
            if (vc < fmin) fmin = vc;
            if (vc > fmax) fmax = vc;

            Double_t vr = leaf_r5r[i]->GetValue();
            if (std::isnan(vr)) continue;
            if (vr < vrmin[i]) vrmin[i] = vr;
            if (vr > vrmax[i]) vrmax[i] = vr;
            if (vr < fmin) fmin = vr;
            if (vr > fmax) fmax = vr;
        }
    }

    for (int i = 0; i < 28; ++i) {
        std::cout << detNames_l[i] << ":     Min = " << vlmin[i] << ", Max = " << vlmax[i] << std::endl;
        std::cout << detNames_c[i] << ":     Min = " << vcmin[i] << ", Max = " << vcmax[i] << std::endl;
        std::cout << detNames_r[i] << ":     Min = " << vrmin[i] << ", Max = " << vrmax[i] << std::endl;
    }

    std::cout << "First Pass:   Min = " << fmin << ", Max = " << fmax << endl;

    Double_t yrange = fmax - fmin;
    if (yrange < 1e-6) yrange = 1e-6;
    Double_t ymin = fmin - 0.1*yrange;
    Double_t ymax = fmax + 0.1*yrange;

    std::cout << "Histogram:    Min = " << ymin << ", Max = " << fmax << endl;

    TH2F* h = new TH2F("r5", "All Ring 5 Segments; ;Yield", 88, -2.5, 85.5, 1000, ymin, ymax);

    double tmin = 1e30;
    double tmax = -1e30;

    for (Long64_t ev = 0; ev < nEntries; ++ev) {
        tree->GetEntry(ev);

        for (int i = 0; i < 28; ++i) {
            Double_t vl = leaf_r5l[i]->GetValue();
            Double_t vc = leaf_r5c[i]->GetValue();
            Double_t vr = leaf_r5r[i]->GetValue();

            h->Fill(3*i+1, vl);
            h->Fill(3*i+2, vc);
            h->Fill(3*i+3, vr);

            if (vl < tmin) tmin = vl;
            if (vl > tmax) tmax = vl;
            if (vc < tmin) tmin = vc;
            if (vc > tmax) tmax = vc;
            if (vr < tmin) tmin = vr;
            if (vr > tmax) tmax = vr;
        }
    }

    for (int k=0; k<28; k++) {
        h->GetXaxis()->SetBinLabel(3*k+4, segments[k].c_str());
	h->GetXaxis()->SetLabelSize(0.02);
    }


    std::cout << "True Global:  Min = " << tmin << ", Max = " << tmax << endl;
    std::cout << "---------------------------------------------" << endl;

    h->SetStats(false);
    h->Draw("COLZ");

    for (int k=0; k<29; k++) {
        TLine *line = new TLine(3*k + 0.5, ymin, 3*k + 0.5, ymax);
        line->Draw();
    }
}
