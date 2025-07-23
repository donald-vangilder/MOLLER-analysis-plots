void TProfile_asym_sa_seg_macro() {
        TTree* tree = (TTree*)gROOT->FindObject("mul");
        tree->ResetBranchAddresses();
        Long64_t nEntries = tree->GetEntries();

        Double_t hw_sum[28];
        for (int i=0; i<8; i++) {
                TString branch = Form("asym_sa%02d", i+1);
                tree->SetBranchAddress(branch, &hw_sum[i]);
        }

        TProfile* p = new TProfile ("tp_asym_saseg", "Small Angle Detector Asymmetry vs Segment Number;;Asymmetry", 10, -0.5, 9.5, -1, 1);

        for (Long64_t ev = 0; ev < nEntries; ++ev) {
                tree->GetEntry(ev);
                for (int i = 0; i < 8; ++i) {
                        p->Fill(i+1,hw_sum[i]*1e3);
                }
        }

        gStyle->SetPalette(0);
        p->SetStats(false);
        p->Draw();
}
