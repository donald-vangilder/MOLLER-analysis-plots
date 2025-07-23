void bcm_target_all_tree_macro() {
        std::cout << "---------------------------------------" << endl;
        std::cout << "BCM target" << endl;


// evt tree
	TTree* tree1 = (TTree*)gROOT->FindObject("evt");
        Long64_t nEntries_evt = tree1->GetEntries();
        tree1->SetBranchStatus("*", false);
        std::cout << "evt tree" << endl;

	Double_t vmin_evt =  1e30, vmax_evt = -1e30;

	tree1->SetBranchStatus("bcm_target", true);
        TBranch* br_evt = tree1->GetBranch("bcm_target");
        TLeaf* bcm_leaf_evt = br_evt->GetLeaf("hw_sum");

        for (Long64_t ev = 0; ev < nEntries_evt; ev += 100) {
                tree1->GetEntry(ev);
                Double_t v_evt = bcm_leaf_evt->GetValue();
                if (std::isnan(v_evt)) continue;
                if (v_evt < vmin_evt) vmin_evt = v_evt;
                if (v_evt > vmax_evt) vmax_evt = v_evt;
        }

	std::cout << "bcm_target: Min = " << vmin_evt << ", Max = " << vmax_evt << std::endl;

        Double_t yrange_evt = vmax_evt - vmin_evt;
        if (yrange_evt < 1e-6) yrange_evt = 1e-6;
        Double_t ymin_evt = vmin_evt - 0.5*yrange_evt;
        Double_t ymax_evt = vmax_evt + 0.5*yrange_evt;
        std::cout << "Histogram:  Min = " << ymin_evt << ", Max = " << ymax_evt << endl;

	tree1->Draw("bcm_target.hw_sum>>h1_bcm_target(100,ymin_evt,ymax_evt)", "", "goff");
	TH1F* h1_bcm_target = (TH1F*)gDirectory->Get("h1_bcm_target");
	h1_bcm_target->SetTitle("Overlayed bcm_target tree yields;Yield;Counts");
        h1_bcm_target->SetLineColor(kBlue);
        h1_bcm_target->SetStats(false);
        h1_bcm_target->Draw("HIST");


// pr tree
        TTree* tree2 = (TTree*)gROOT->FindObject("pr");
        Long64_t nEntries_pr = tree2->GetEntries();
        tree2->SetBranchStatus("*", false);
        std::cout << "pr tree" << endl;

        Double_t vmin_pr =  1e30, vmax_pr = -1e30;

        tree2->SetBranchStatus("yield_bcm_target", true);
        TBranch* br_pr = tree2->GetBranch("yield_bcm_target");
        TLeaf* bcm_leaf_pr = br_pr->GetLeaf("hw_sum");

        for (Long64_t ev = 0; ev < nEntries_pr; ev += 10) {
                tree2->GetEntry(ev);
                Double_t v_pr = bcm_leaf_pr->GetValue();
                if (std::isnan(v_pr)) continue;
                if (v_pr < vmin_pr) vmin_pr = v_pr;
                if (v_pr > vmax_pr) vmax_pr = v_pr;
        }

        std::cout << "bcm_target: Min = " << vmin_pr << ", Max = " << vmax_pr << std::endl;

        Double_t yrange_pr = vmax_pr - vmin_pr;
        if (yrange_pr < 1e-6) yrange_pr = 1e-6;
        Double_t ymin_pr = vmin_pr - 0.5*yrange_pr;
        Double_t ymax_pr = vmax_pr + 0.5*yrange_pr;
        std::cout << "Histogram:  Min = " << ymin_pr << ", Max = " << ymax_pr << endl;

        tree2->Draw("yield_bcm_target.hw_sum>>h2_bcm_target(100,ymin_pr,ymax_pr)", "", "goff");
        TH1F* h2_bcm_target = (TH1F*)gDirectory->Get("h2_bcm_target");
        h2_bcm_target->Scale(2);
        h2_bcm_target->SetLineColor(kRed);
        h2_bcm_target->SetStats(false);
        h2_bcm_target->Draw("HIST SAME");


// mul tree
        TTree* tree3 = (TTree*)gROOT->FindObject("mul");
        Long64_t nEntries_mul = tree3->GetEntries();
        tree3->SetBranchStatus("*", false);
        std::cout << "mul tree" << endl;

        Double_t vmin_mul =  1e30, vmax_mul = -1e30;

        tree3->SetBranchStatus("yield_bcm_target", true);
        TBranch* br_mul = tree3->GetBranch("yield_bcm_target");
        TLeaf* bcm_leaf_mul = br_mul->GetLeaf("hw_sum");

        for (Long64_t ev = 0; ev < nEntries_mul; ++ev) {
                tree3->GetEntry(ev);
                Double_t v_mul = bcm_leaf_mul->GetValue();
                if (std::isnan(v_mul)) continue;
                if (v_mul < vmin_mul) vmin_mul = v_mul;
                if (v_mul > vmax_mul) vmax_mul = v_mul;
        }

        std::cout << "bcm_target: Min = " << vmin_mul << ", Max = " << vmax_mul << std::endl;

        Double_t yrange_mul = vmax_mul - vmin_mul;
        if (yrange_mul < 1e-6) yrange_mul = 1e-6;
        Double_t ymin_mul = vmin_mul - 0.5*yrange_mul;
        Double_t ymax_mul = vmax_mul + 0.5*yrange_mul;
        std::cout << "Histogram:  Min = " << ymin_mul << ", Max = " << ymax_mul << endl;

        tree3->Draw("yield_bcm_target.hw_sum>>h3_bcm_target(100,ymin_mul,ymax_mul)", "", "goff");
        TH1F* h3_bcm_target = (TH1F*)gDirectory->Get("h3_bcm_target");
	h3_bcm_target->Scale(64);
	h3_bcm_target->SetLineColor(kGreen);
	h3_bcm_target->SetMaximum(ymax_mul);
        h3_bcm_target->SetStats(false);
        h3_bcm_target->Draw("HIST SAME");


// legend
	TLegend* l = new TLegend(0.7, 0.7, 0.9, 0.9);
	l->AddEntry(h1_bcm_target, "evt tree", "l");
        l->AddEntry(h2_bcm_target, "pr tree x2", "l");
        l->AddEntry(h3_bcm_target, "mul tree x64", "l");
	l->Draw();
}
