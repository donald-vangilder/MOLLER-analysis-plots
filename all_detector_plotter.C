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
                evt_branch_names[1] = monitor_type + monitor_id + "X.hw_sum";
                evt_branch_names[2] = monitor_type + monitor_id + "Y.hw_sum";

                std::vector<TString> non_evt_branch_names(8);
                non_evt_branch_names[0] = "yield_" + monitor_type + monitor_id + "WS.hw_sum";
                non_evt_branch_names[1] = "yield_" + monitor_type + monitor_id + "X.hw_sum";
                non_evt_branch_names[2] = "yield_" + monitor_type + monitor_id + "Y.hw_sum";
                non_evt_branch_names[3] = "asym_"+ monitor_type + monitor_id + "WS.hw_sum";
                non_evt_branch_names[4] = "diff_"+ monitor_type + monitor_id + "X.hw_sum";
                non_evt_branch_names[5] = "diff_"+ monitor_type + monitor_id + "Y.hw_sum";

                std::cout << "Making " << monitor_type << " Canvas" << std::endl;
                TCanvas* c = new TCanvas("c", monitor_type + " Plots", 1600, 1000);
                c->Divide(4, 5);

                std::vector<TString> title(24);

//              evt tree
                c->cd(1);
                tree1->Draw(evt_branch_names[0] + ">> h1(100)", "", "goff");
                TH1F* h1 = (TH1F*)gDirectory->Get("h1");
                title[0] = "evt " + evt_branch_names[0] + ";Yield;Counts";
                h1->SetTitle(title[0]);
                h1->Draw("HIST");

                c->cd(2);
                tree1->Draw(evt_branch_names[0] + ":Entry$ >> h2(100)", "", "goff");
                TH2F* h2 = (TH2F*)gDirectory->Get("h2");
                title[1] = "evt " + evt_branch_names[0] + " vs Time;Entry Number;Yield";
                h2->SetTitle(title[1]);
                h2->Draw("HIST");

                c->cd(3);
                tree1->Draw(evt_branch_names[1] + ":" + evt_branch_names[2] + ">> h3(100)", "", "goff");
                TH2F* h3 = (TH2F*)gDirectory->Get("h3");
                title[2] = "evt " + evt_branch_names[1] + " vs " + evt_branch_names[2] + ";" + evt_branch_names[2] + ";" + evt_branch_names[1];
                h3->SetTitle(title[2]);
                h3->Draw("HIST");

                c->cd(4);
                tree1->Draw(evt_branch_names[1] + "/" + evt_branch_names[2] + ":Entry$ >> h4(100)", "", "goff");
                TH2F* h4 = (TH2F*)gDirectory->Get("h4");
                title[3] = "evt " + evt_branch_names[1] + "/" + evt_branch_names[2] + " vs Time;Entry Number;" + evt_branch_names[1] + "/" + evt_branch_names[2];
                h4->SetTitle(title[3]);
                h4->Draw("HIST");

//              pr tree
                c->cd(5);
                tree2->Draw(non_evt_branch_names[0] + ">> h5(100)", "", "goff");
                TH1F* h5 = (TH1F*)gDirectory->Get("h5");
                title[4] = "pr " + non_evt_branch_names[0] + ";Yield;Counts";
                h5->SetTitle(title[4]);
                h5->Draw("HIST");

                c->cd(6);
                tree2->Draw(non_evt_branch_names[0] + ":Entry$ >> h6(100)", "", "goff");
                TH1F* h6 = (TH1F*)gDirectory->Get("h6");
                title[5] = "pr " + non_evt_branch_names[0] + " vs Time;Entry Number;Yield";
                h6->SetTitle(title[5]);
                h6->Draw("HIST");

                c->cd(7);
                tree2->Draw(non_evt_branch_names[1] + ":" + non_evt_branch_names[2] + ">> h7(100)", "", "goff");
                TH1F* h7 = (TH1F*)gDirectory->Get("h7");
                title[6] = "pr " + non_evt_branch_names[1] + " vs " + non_evt_branch_names[2] + ";" + evt_branch_names[2] + ";" + evt_branch_names[1];
                h7->SetTitle(title[6]);
                h7->Draw("HIST");

                c->cd(8);
                tree2->Draw(non_evt_branch_names[1] + "/" + non_evt_branch_names[2] + ":Entry$ >> h8(100)", "", "goff");
                TH1F* h8 = (TH1F*)gDirectory->Get("h8");
                title[7] = "pr " + non_evt_branch_names[1] + "/" + non_evt_branch_names[2] + " vs Time;Entry Number;" + evt_branch_names[1] + "/" + evt_branch_names[2];
                h8->SetTitle(title[7]);
                h8->Draw("HIST");

                c->cd(9);
                tree2->Draw(non_evt_branch_names[3] + ">> h9(100)", "", "goff");
                TH1F* h9 = (TH1F*)gDirectory->Get("h9");
                title[8] = "pr " + non_evt_branch_names[3] + ";Asymmetry;Counts";
                h9->SetTitle(title[8]);
                h9->Draw("HIST");

                c->cd(10);
                tree2->Draw(non_evt_branch_names[3] + ":Entry$ >> h10(100)", "", "goff");
                TH1F* h10 = (TH1F*)gDirectory->Get("h10");
                title[9] = "pr " + non_evt_branch_names[3] + " vs Time;Entry Number;Asymmetry";
                h10->SetTitle(title[9]);
                h10->Draw("HIST");

                c->cd(11);
                tree2->Draw(non_evt_branch_names[4] + ":" + non_evt_branch_names[5] + ">> h11(100)", "", "goff");
                TH1F* h11 = (TH1F*)gDirectory->Get("h11");
                title[10] = "pr " + non_evt_branch_names[4] + " vs " + non_evt_branch_names[5] + ";" + evt_branch_names[5] + ";" + evt_branch_names[4];
                h11->SetTitle(title[10]);
                h11->Draw("HIST");

                c->cd(12);
                tree2->Draw(non_evt_branch_names[4] + "/" + non_evt_branch_names[5] + ":Entry$ >> h12(100)", "", "goff");
                TH1F* h12 = (TH1F*)gDirectory->Get("h12");
                title[11] = "pr " + non_evt_branch_names[4] + "/" + non_evt_branch_names[5] + " vs Time;Entry Number;" + evt_branch_names[4] + "/" + evt_branch_names[5];
                h12->SetTitle(title[11]);
                h12->Draw("HIST");

//              mul tree
                c->cd(13);
                tree3->Draw(non_evt_branch_names[0] + ">> h13(100)", "", "goff");
                TH1F* h13 = (TH1F*)gDirectory->Get("h13");
                title[20] = "mul " + non_evt_branch_names[0] + ";Yield;Counts";
                h13->SetTitle(title[20]);
                h13->Draw("HIST");

                c->cd(14);
                tree3->Draw(non_evt_branch_names[0] + ":Entry$ >> h14(100)", "", "goff");
                TH1F* h14 = (TH1F*)gDirectory->Get("h14");
                title[13] = "mul " + non_evt_branch_names[0] + " vs Time;Entry Number;Yield";
                h14->SetTitle(title[13]);
                h14->Draw("HIST");

                c->cd(15);
                tree3->Draw(non_evt_branch_names[1] + ":" + non_evt_branch_names[2] + ">> h15(100)", "", "goff");
                TH1F* h15 = (TH1F*)gDirectory->Get("h15");
                title[14] = "mul " + non_evt_branch_names[1] + " vs " + non_evt_branch_names[2] + ";" + evt_branch_names[2] + ";" + evt_branch_names[1];
                h15->SetTitle(title[14]);
                h15->Draw("HIST");

                c->cd(16);
                tree3->Draw(non_evt_branch_names[1] + "/" + non_evt_branch_names[2] + ":Entry$ >> h16(100)", "", "goff");
                TH1F* h16 = (TH1F*)gDirectory->Get("h16");
                title[15] = "mul " + non_evt_branch_names[1] + "/" + non_evt_branch_names[2] + " vs Time;Entry Number;" + evt_branch_names[1] + "/" + evt_branch_names[2];
                h16->SetTitle(title[15]);
                h16->Draw("HIST");

                c->cd(17);
                tree3->Draw(non_evt_branch_names[3] + ">> h17(100)", "", "goff");
                TH1F* h17 = (TH1F*)gDirectory->Get("h17");
                title[16] = "mul " + non_evt_branch_names[3] + ";Asymmetry;Counts";
                h17->SetTitle(title[16]);
                h17->Draw("HIST");

                c->cd(18);
                tree3->Draw(non_evt_branch_names[3] + ":Entry$ >> h18(100)", "", "goff");
                TH1F* h18 = (TH1F*)gDirectory->Get("h18");
                title[17] = "mul " + non_evt_branch_names[3] + " vs Time;Entry Number;Asymmetry";
                h18->SetTitle(title[17]);
                h18->Draw("HIST");

                c->cd(19);
                tree3->Draw(non_evt_branch_names[4] + ":" + non_evt_branch_names[5] + ">> h19(100)", "", "goff");
                TH1F* h19 = (TH1F*)gDirectory->Get("h19");
                title[18] = "mul " + non_evt_branch_names[4] + " vs " + non_evt_branch_names[5] + ";" + evt_branch_names[5] + ";" + evt_branch_names[4];
                h19->SetTitle(title[18]);
                h19->Draw("HIST");

                c->cd(20);
                tree3->Draw(non_evt_branch_names[4] + "/" + non_evt_branch_names[5] + ":Entry$ >> h20(100)", "", "goff");
                TH1F* h20 = (TH1F*)gDirectory->Get("h20");
                title[19] = "mul " + non_evt_branch_names[4] + "/" + non_evt_branch_names[5] + " vs Time;Entry Number;" + evt_branch_names[4] + "/" + evt_branch_names[5];
                h20->SetTitle(title[19]);
                h20->Draw("HIST");
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
