void asym_la_seg_macro() {
        TTree* tree = (TTree*)gROOT->FindObject("mul");
        tree->ResetBranchAddresses();
        Long64_t nEntries = tree->GetEntries();

        Double_t hw_sum[42];
        for (int i=0; i<42; i++) {
                TString branch = Form("asym_la%02d", i+1);
                tree->SetBranchAddress(branch, &hw_sum[i]);
        }

        TH2F* h = new TH2F ("asym_laseg", "Large Angle Detector Asymmetry vs Segment Number;;Asymmetry (parts per thousand)", 44, -0.5, 43.5, 100, -1, 1);

        for (Long64_t ev = 0; ev < nEntries; ++ev) {
                tree->GetEntry(ev);
                for (int i = 0; i < 42; ++i) {
                        h->Fill(i+1,hw_sum[i]*1e3);
                }
        }

        gStyle->SetPalette(0);
        h->SetStats(false);
        h->Draw();
}
