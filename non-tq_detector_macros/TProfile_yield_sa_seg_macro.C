void TProfile_yield_sa_seg_macro() {
        TTree* tree = (TTree*)gROOT->FindObject("mul");
        tree->ResetBranchAddresses();
        Long64_t nEntries = tree->GetEntries();

        Double_t hw_sum[28];
        for (int i=0; i<8; i++) {
                TString branch = Form("yield_sa%02d", i+1);
                tree->SetBranchAddress(branch, &hw_sum[i]);
        }

        TProfile* p = new TProfile ("tp_yield_saseg", "Small Angle Detector Yield vs Segment Number;;yield (V/uA)", 10, -0.5, 9.5, 0, 1);

        for (Long64_t ev = 0; ev < nEntries; ++ev) {
                tree->GetEntry(ev);
                for (int i = 0; i < 8; ++i) {
                        p->Fill(i+1,hw_sum[i]);
                }
        }

        gStyle->SetPalette(0);
        p->GetYaxis()->SetRangeUser(59.94e-3, 59.96e-3);
        p->SetStats(false);
        p->Draw();
}
