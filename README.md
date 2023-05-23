# Macro for pre-process the row data acquired from CAMAC adquisition system

## The macro needs to have a folder named DATA with all the runs inside, besides we need to set up to the code the numbers of runs and the numbers of detectors used in the experiments:
## Steps:
1. Open "macro.h" and set up the variable "run" & "no_detectors"
2. Run the macro using ROOT Cern 
3. The output create the .root files in the main directory and the individual histograms in a folder named "f2simnra" corresponding to the data from each individual detector
