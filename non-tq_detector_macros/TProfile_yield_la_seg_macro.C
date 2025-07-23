void TProfile_yield_la_seg_macro() {
        TTree* tree = (TTree*)gROOT->FindObject("mul");
        tree->ResetBranchAddresses();
        Long64_t nEntries = tree->GetEntries();

        Double_t hw_sum[42];
        for (int i=0; i<42; i++) {
                TString branch = Form("yield_la%02d", i+1);
                tree->SetBranchAddress(branch, &hw_sum[i]);
        }

        TProfile* p = new TProfile ("tp_yield_laseg", "Large Angle Detector Yield vs Segment Number;;yield (V/uA)", 44, -0.5, 43.5, 0, 1);

        for (Long64_t ev = 0; ev < nEntries; ++ev) {
                tree->GetEntry(ev);
                for (int i = 0; i < 42; ++i) {
                        p->Fill(i+1,hw_sum[i]);
                }
        }

        gStyle->SetPalette(0);
        p->GetYaxis()->SetRangeUser(59.94e-3, 59.96e-3);
        p->SetStats(false);
        p->Draw();
}
