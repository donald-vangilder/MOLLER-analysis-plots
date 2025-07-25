# MOLLER-analysis-plots
This repository contains macros and configuration files necessary for plotting data from MOLLER simulations


Running these configurtion files through Panguin with the current file format will properly use every macro in the "******_macros" folders

To run these files in Panguin, use the following format:
/path/to/panguin -f /path/to/MOLLER-analysis-plots/(filename).cfg -r run_num

The run_num is the run number used for the simulation and assumes a root file format of "isu_sample_(run_num).root"

<img width="500" height="300" alt="BCMs" src="https://github.com/user-attachments/assets/035a46d6-8cac-4492-912f-9c9ff125afa1" />
<img width="500" height="300" alt="BPMs" src="https://github.com/user-attachments/assets/29c3aca8-1525-41d5-8049-e314b8bb5681" />
<img width="500" height="300" alt="All BCM trees" src="https://github.com/user-attachments/assets/254193e3-b406-450c-b2f1-8c315c2a0f13" />
<img width="500" height="300" alt="Asym Analysis" src="https://github.com/user-attachments/assets/b484b129-61c8-4d69-9cc6-d5322ab2ec6c" />
<img width="500" height="300" alt="Non-tq Yields" src="https://github.com/user-attachments/assets/1f735aa9-fe60-479a-a762-a8d22a939b46" />
<img width="500" height="300" alt="All Ring 5 Segments" src="https://github.com/user-attachments/assets/dd572105-17c4-48f3-9cc5-894214610c01" />
<img width="500" height="300" alt="All Ring 1-4,6 Segments" src="https://github.com/user-attachments/assets/7ef6d77c-4dd9-4ff4-927e-93e0dd13802a" />
<img width="500" height="300" alt="Ring 5 Segment types" src="https://github.com/user-attachments/assets/5b9d5492-fd43-4ac5-99bc-f7586d3ebd79" />


<img width="500" height="300" alt="la all_det_plot" src="https://github.com/user-attachments/assets/0d6ca4e8-f499-4350-b0cf-151c3de24c94" />
<img width="500" height="300" alt="image" src="https://github.com/user-attachments/assets/8bb7a688-eb59-4a4d-a8eb-e202e12815ef" />


The only macro that needs to be used without a configuration file is all_detector_plotter.C
This macro will plot information about a specific detector or beam monitor with the following format: all_analyzer_plotter("monitor_type","monitor_id", run_num)
For a more in-depth explanation of how to use this macro, it can be run as: all_analyzer_plotter("help")
This will explain the usable monitor types and monitor ids
