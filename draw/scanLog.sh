logFile1=root/neutron_change.log

# --- scan full reconstruction
grep "The run consists" $logFile1 | awk 'NR==1{printf "Double_t neutronInEdep[nE]={"$10 ", "}; NR>1&&NR<12{printf $10 ", "}; NR==12{printf $10 "};\n"}'
grep "in Tumor volume" $logFile1 | awk 'NR==1{printf "Double_t TumorEdep[nE]={"$11 ", "}; NR>1&&NR<12{printf $11 ", "}; NR==12{printf $11 "};\n"}'
grep "in Body volume" $logFile1 | awk 'NR==1{printf "Double_t BodyEdep[nE]={"$11 ", "}; NR>1&&NR<12{printf $11 ", "}; NR==12{printf $11 "};\n"}'
grep "in Head volume" $logFile1 | awk 'NR==1{printf "Double_t HeadEdep[nE]={"$11 ", "}; NR>1&&NR<12{printf $11 ", "}; NR==12{printf $11 "};\n"}'
grep "in All (Tumor+Body+Head) volume" $logFile1 | awk 'NR==1{printf "Double_t AllEdep[nE]={"$12 ", "}; NR>1&&NR<12{printf $12 ", "}; NR==12{printf $12 "};\n"}'

grep "TumorEdep" $logFile1 | awk 'NR==1{printf "Double_t TumorEE[nE]={"$5 ", "}; NR>1&&NR<12{printf $5 ", "}; NR==12{printf $5 "};\n"}'
grep "BodyEdep" $logFile1 | awk 'NR==1{printf "Double_t BodyEE[nE]={"$5 ", "}; NR>1&&NR<12{printf $5 ", "}; NR==12{printf $5 "};\n"}'
grep "HeadEdep" $logFile1 | awk 'NR==1{printf "Double_t HeadEE[nE]={"$5 ", "}; NR>1&&NR<12{printf $5 ", "}; NR==12{printf $5 "};\n"}'
grep "AllEdep" $logFile1 | awk 'NR==1{printf "Double_t AllEE[nE]={"$5 ", "}; NR>1&&NR<12{printf $5 ", "}; NR==12{printf $5 "};\n"}'