void yield_sm_seg_macro() {
        TTree* tree = (TTree*)gROOT->FindObject("mul");
        tree->ResetBranchAddresses();
        Long64_t nEntries = tree->GetEntries();

        Double_t hw_sum[28];
        for (int i=0; i<28; i++) {
                TString branch = Form("yield_sm%02d", i+1);
                tree->SetBranchAddress(branch, &hw_sum[i]);
        }

        TH2F* h = new TH2F ("yield_smseg", "Shower Max Detector Yield vs Segment Number;;yield (V/uA) ", 30, -0.5, 29.5, 1000, 5.95e-2, 6.05e-2);

        for (Long64_t ev = 0; ev < nEntries; ++ev) {
                tree->GetEntry(ev);
                for (int i = 0; i < 28; ++i) {
                        h->Fill(i+1,hw_sum[i]);
                }
        }

        gStyle->SetPalette(0);
        h->SetStats(false);
        h->Draw();
}
