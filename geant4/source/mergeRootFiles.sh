#!/bin/bash
hadd -f build/output.root build/output0_2000000events_10.8MeV_20cm_t{0..7}.root
## -f flag to overwrite the merged output file