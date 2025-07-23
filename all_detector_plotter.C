void all_detector_plotter(TString monitor_type, TString monitor_id, int run_num) {

	std::vector<TString> monitor_types;
	monitor_types.push_back("bcm");
        monitor_types.push_back("bpm");
        monitor_types.push_back("la");
        monitor_types.push_back("pd");
        monitor_types.push_back("sa");
        monitor_types.push_back("sm");
        monitor_types.push_back("tq");

	if (std::find(monitor_types.begin(), monitor_types.end(), monitor_type) == monitor_types.end()) {
		std::cout << "ERROR: Monitor Type Not Found\nAcceptable Monitor Types: ";
		for (const auto& type : monitor_types) {
			std::cout << type << " ";
		}
		std::cout << std::endl;
		return;
	}

	int monitor_size;
	if (monitor_type == "sa") monitor_size = 8;
	else if (monitor_type == "sm") monitor_size = 28;
	else if (monitor_type == "pd") monitor_size = 28;
	else if (monitor_type == "la") monitor_size = 42;



	std::vector<TString> selected_ids;
	if (monitor_type == "bcm") {
		selected_ids.push_back("1h02a"); selected_ids.push_back("1h02b"); selected_ids.push_back("1h04a"); selected_ids.push_back("1h12a");
		selected_ids.push_back("1h12b"); selected_ids.push_back("1h12c"); selected_ids.push_back("1h13");  selected_ids.push_back("1h15");
		selected_ids.push_back("target"); selected_ids.push_back("0l02");
	} else if (monitor_type == "bpm") {
	        selected_ids.push_back("1c10"); selected_ids.push_back("1c11");  selected_ids.push_back("1c12");  selected_ids.push_back("1c16");
		selected_ids.push_back("1c20"); selected_ids.push_back("1p02b"); selected_ids.push_back("1p03a"); selected_ids.push_back("1h01");
                selected_ids.push_back("1h02"); selected_ids.push_back("1h02");  selected_ids.push_back("1h04");  selected_ids.push_back("1h05");
		selected_ids.push_back("1h11"); selected_ids.push_back("1h14"); selected_ids.push_back("target"); selected_ids.push_back("0i01a");
		selected_ids.push_back("1i04"); selected_ids.push_back("1i02");  selected_ids.push_back("0i01");  selected_ids.push_back("1i06");
                selected_ids.push_back("0i02"); selected_ids.push_back("0i02a"); selected_ids.push_back("0i05");  selected_ids.push_back("0i07");
                selected_ids.push_back("0l01"); selected_ids.push_back("0l02");  selected_ids.push_back("0l03");  selected_ids.push_back("0l04");
                selected_ids.push_back("0l05"); selected_ids.push_back("0l06");  selected_ids.push_back("0l07");  selected_ids.push_back("0l08");
                selected_ids.push_back("0l09"); selected_ids.push_back("0l10");  selected_ids.push_back("2i02");  selected_ids.push_back("2i01");
	} else if (monitor_type == "tq") {
	        for (int i = 1; i <= 28; ++i) {
                        selected_ids.push_back(Form("%02d_r1", i));
                        selected_ids.push_back(Form("%02d_r2", i));
                        selected_ids.push_back(Form("%02d_r3", i));
                        selected_ids.push_back(Form("%02d_r4", i));
                        selected_ids.push_back(Form("%02d_r5l", i));
                        selected_ids.push_back(Form("%02d_r5c", i));
                        selected_ids.push_back(Form("%02d_r5r", i));
                        selected_ids.push_back(Form("%02d_r6", i));
	        }
	} else if (monitor_type == "sa"|| monitor_type == "sm"|| monitor_type == "pd"|| monitor_type == "la") {
	        for (int i =1; i <= monitor_size; ++i) {
	                selected_ids.push_back(Form("%02d", i));
	        }
	}


        if (std::find(selected_ids.begin(), selected_ids.end(), monitor_id) == selected_ids.end()) {
		if (monitor_type == "sa"|| monitor_type == "sm"|| monitor_type == "pd"|| monitor_type == "la" || monitor_type == "tq") {
	                std::cout << "ERROR: " << monitor_type << " Detector Not Found\nAcceptable " << monitor_type << " Detectors: ";
		} else {
			std::cout << "ERROR: " << monitor_type << " Not Found\nAcceptable " << monitor_type << "s: ";
		}
                for (const auto& id : selected_ids) {
                        std::cout << id << "    ";
                }
                std::cout << std::endl;
                return;
        }

        TFile* f = TFile::Open(Form("$QW_ROOTFILES/isu_sample_%d.root", run_num));

        TTree* tree1 = (TTree*)f->Get("evt");
        TTree* tree2 = (TTree*)f->Get("pr");
        TTree* tree3 = (TTree*)f->Get("mul");


	if (monitor_type == "bpm") {
                std::cout << "Setting " << monitor_type << " Branches" << std::endl;
		std::vector<TString> evt_branch_names(8);
                evt_branch_names[0] = monitor_type + monitor_id + "WS.hw_sum";
                evt_branch_names[1] = monitor_type + monitor_id + "Elli.hw_sum";
                evt_branch_names[2] = monitor_type + monitor_id + "XP.hw_sum";
                evt_branch_names[3] = monitor_type + monitor_id + "XM.hw_sum";
                evt_branch_names[4] = monitor_type + monitor_id + "YP.hw_sum";
                evt_branch_names[5] = monitor_type + monitor_id + "YM.hw_sum";
                evt_branch_names[6] = monitor_type + monitor_id + "X.hw_sum";
                evt_branch_names[7] = monitor_type + monitor_id + "Y.hw_sum";

		std::vector<TString> non_evt_branch_names(8);
                non_evt_branch_names[0] = "yield_" + monitor_type + monitor_id + "WS.hw_sum";
                non_evt_branch_names[1] = "yield_" + monitor_type + monitor_id + "Elli.hw_sum";
                non_evt_branch_names[2] = "yield_" + monitor_type + monitor_id + "X.hw_sum";
                non_evt_branch_names[3] = "yield_" + monitor_type + monitor_id + "Y.hw_sum";
                non_evt_branch_names[4] = "asym_"+ monitor_type + monitor_id + "WS.hw_sum";
                non_evt_branch_names[5] = "asym_"+ monitor_type + monitor_id + "Elli.hw_sum";
                non_evt_branch_names[6] = "diff_"+ monitor_type + monitor_id + "X.hw_sum";
                non_evt_branch_names[7] = "diff_"+ monitor_type + monitor_id + "Y.hw_sum";

                std::cout << "Making " << monitor_type << " Canvas" << std::endl;
                TCanvas* c = new TCanvas("c", monitor_type + " Plots", 1600, 1000);
	        c->Divide(4, 6);

		std::vector<TString> title(24);

		for (int i =1; i <= 8; ++i) {
	                c->cd(i);
	                TString h_name = Form("h%d", i);
			if (gDirectory->Get(h_name)) gDirectory->Get(h_name)->Delete();
			tree1->Draw(evt_branch_names[i-1] + ">>" + h_name + "(100)", "", "goff");
	                TH1F* h = (TH1F*)gDirectory->Get(h_name);
	                title[i-1] = "evt " + evt_branch_names[i-1] + ";yield;counts";
	                h->SetTitle(title[i-1]);
	                h->Draw("HIST");
		}

                for (int i =9; i <= 16; ++i) {
                        c->cd(i);
                        TString h_name = Form("h%d", i);
                        if (gDirectory->Get(h_name)) gDirectory->Get(h_name)->Delete();
                        tree2->Draw(non_evt_branch_names[i-9] + ">>" + h_name + "(100)", "", "goff");
                        TH1F* h = (TH1F*)gDirectory->Get(h_name);
                        title[i-1] = "evt " + non_evt_branch_names[i-9] + ";yield;counts";
                        h->SetTitle(title[i-1]);
                        h->Draw("HIST");
                }

                for (int i =17; i <= 24; ++i) {
                        c->cd(i);
                        TString h_name = Form("h%d", i);
                        if (gDirectory->Get(h_name)) gDirectory->Get(h_name)->Delete();
                        tree3->Draw(non_evt_branch_names[i-17] + ">>" + h_name + "(100)", "", "goff");
                        TH1F* h = (TH1F*)gDirectory->Get(h_name);
                        title[i-1] = "evt " + non_evt_branch_names[i-17] + ";yield;counts";
                        h->SetTitle(title[i-1]);
                        h->Draw("HIST");
                }
        }

	if (monitor_type == "bcm" || monitor_type == "sa" || monitor_type == "sm" ||
	    monitor_type == "pd"  || monitor_type == "la" || monitor_type == "tq") {
                std::cout << "Setting " << monitor_type <<" Branches" << std::endl;
                TString evt_branch_name = monitor_type + monitor_id + ".hw_sum";
                TString yield_branch_name = "yield_" + monitor_type + monitor_id + ".hw_sum";
                TString asym_branch_name = "asym_"+ monitor_type + monitor_id + ".hw_sum";

                std::cout << "Making " << monitor_type << " Canvas" << std::endl;
		TCanvas* c = new TCanvas("c", monitor_type + " Plots", 1600, 800);
		c->Divide(4, 3);

		c->cd(1);
		tree1->Draw(evt_branch_name + ">>h1(100)", "", "goff");
	        TH1F* h1 = (TH1F*)gDirectory->Get("h1");
		TString title1 = "evt " + monitor_type + monitor_id + ";yield;counts";
	        h1->SetTitle(title1);
	        h1->Draw("HIST");

                c->cd(5);
                tree2->Draw(yield_branch_name + ">>h2(100)", "", "goff");
                TH1F* h2 = (TH1F*)gDirectory->Get("h2");
                TString title2 = "pr " + monitor_type + monitor_id + ";yield;counts";
                h2->SetTitle(title2);
                h2->Draw("HIST");

                c->cd(7);
                tree2->Draw(asym_branch_name + ">>h3(100)", "", "goff");
                TH1F* h3 = (TH1F*)gDirectory->Get("h3");
                TString title3 = "pr " + monitor_type + monitor_id + ";asym;counts";
                h3->SetTitle(title3);
                h3->Draw("HIST");

                c->cd(9);
                tree3->Draw(yield_branch_name + ">>h4(100)", "", "goff");
                TH1F* h4 = (TH1F*)gDirectory->Get("h4");
                TString title4 = "mul " + monitor_type + monitor_id + ";yield;counts";
                h4->SetTitle(title4);
                h4->Draw("HIST");

                c->cd(11);
                tree3->Draw(asym_branch_name + ">>h5(100)", "", "goff");
                TH1F* h5 = (TH1F*)gDirectory->Get("h5");
                TString title5 = "mul " + monitor_type + monitor_id + ";asym;counts";
                h5->SetTitle(title5);
                h5->Draw("HIST");

                c->cd(2);
		tree1->Draw(evt_branch_name + ":Entry$>>h6(100)", "", "goff");
		TH1F* h6 = (TH1F*)gDirectory->Get("h6");
		TString title6 = "evt " + monitor_type + monitor_id + ";event;yield";
                h6->SetTitle(title6);
		h6->Draw("HIST");

                c->cd(6);
                tree2->Draw(yield_branch_name + ":Entry$>>h7(100)", "", "goff");
                TH1F* h7 = (TH1F*)gDirectory->Get("h7");
                TString title7 = "pr " + monitor_type + monitor_id + ";event;yield";
                h7->SetTitle(title7);
                h7->Draw("HIST");

                c->cd(8);
                tree2->Draw(asym_branch_name + ":Entry$>>h8(100)", "", "goff");
                TH1F* h8 = (TH1F*)gDirectory->Get("h8");
                TString title8 = "pr " + monitor_type + monitor_id + ";event;asym";
                h8->SetTitle(title8);
                h8->Draw("HIST");

                c->cd(10);
                tree3->Draw(yield_branch_name + ":Entry$>>h9(100)", "", "goff");
                TH1F* h9 = (TH1F*)gDirectory->Get("h9");
                TString title9 = "mul " + monitor_type + monitor_id + ";event;yield";
                h9->SetTitle(title9);
                h9->Draw("HIST");

                c->cd(12);
                tree3->Draw(asym_branch_name + ":Entry$>>h10(100)", "", "goff");
                TH1F* h10 = (TH1F*)gDirectory->Get("h10");
                TString title10 = "mul " + monitor_type + monitor_id + ";event;asym";
                h10->SetTitle(title10);
                h10->Draw("HIST");
	}
}

void all_detector_plotter(TString help_command) {
	if (help_command == "help" || help_command == "Help") {
                std::cout << "This plotter will display some information about a selected detector or beam monitor";
		std::cout << "Inputs should be formatted as:\nall_analyzer_plotter(\"monitor_type\",\"monitor_id\", \"run_num\")\n\n";
		std::cout << "Accepted monitor_type:\nbcm, bpm, sa, sm, pd, la, tq\n\n";
                std::cout << "Accepted bcm monitor_id:\n1h02a 1h02b 1h04a 1h12a 1h12b 1h12c 1h13 1h15\n\n";
		std::cout << "Accepted bpm monitor_id:\n1c10 1c11 1c12 1c16 1c20 1p02b 1p03a 1h01 1h02 1h02 1h04 1h05 1h11 1h14 target";
		std::cout << " 0i01a 1i04 1i02 0i01 1i06 0i02 0i02a 0i05 0i07 0l01 0l02 0l03 0l04 0l05 0l06 0l07 0l08 0l09 0l10 2i02 2i01\n\n";
		std::cout << "Accepted sa monitor_id:\n1, 2, 3, 4, 5, 6, 7, 8\n\n";
                std::cout << "Accepted sm monitor_id:\n1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28\n\n";
                std::cout << "Accepted pd monitor_id:\n1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28\n\n";
                std::cout << "Accepted la monitor_id:\n1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,";
		std::cout << " 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42\n\n";
                std::cout << "Accepted tq monitor_id:\n";
		for (int i = 1; i <= 28; ++i) {
                        std::cout << Form("%02d_r1, ", i);
                        std::cout << Form("%02d_r2, ", i);
                        std::cout << Form("%02d_r3, ", i);
                        std::cout << Form("%02d_r4, ", i);
                        std::cout << Form("%02d_r5l, ", i);
                        std::cout << Form("%02d_r5c, ", i);
                        std::cout << Form("%02d_r5r, ", i);
                        std::cout << Form("%02d_r6\n", i);
                }
		std::cout << "\nrun_num is the run number of the simulation\nThis assumes that the file is formatted like: isu_sample_[run_num].root\n";
		std::cout << "Ex: An input of 1234 for run_num assumes that a file exists called isu_sample_1234.root\n";
	}
}
