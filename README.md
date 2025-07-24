# MOLLER-analysis-plots
This repository contains macros and configuration files necessary for plotting data from MOLLER simulations


Running these configurtion files through Panguin with the current file format will properly use every macro in the "******_macros" folders

To run these files in Panguin, use the following format:
/path/to/panguin -f /path/to/MOLLER-analysis-plots/(filename).cfg -r run_num

The run_num is the run number used for the simulation and assumes a root file format of "isu_sample_(run_num).root"


The only macro that needs to be used without a configuration file is all_detector_plotter.C
This macro will plot information about a specific detector or beam monitor with the following format: all_analyzer_plotter("monitor_type","monitor_id", "run_num")
For a more in-depth explanation of how to use this macro, it can be run as: all_analyzer_plotter("help")
This will explain the usable monitor types and monitor ids
