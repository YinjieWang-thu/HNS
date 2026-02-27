#!/bin/bash
 
INPUTFILE="jam.inp"

for ((i=$1; i<=$2; i++)); do

WRKSUBDIR=`printf %d $i`
# echo $WRKSUBDIR
rm -rf $WRKSUBDIR
mkdir $WRKSUBDIR
cd $WRKSUBDIR

echo "Main:numberOfEvents = 2000000 ! number of events to generate

Random:setSeed = on
Random:seed = "$(printf %d 0x$(xxd -l 3 -ps -c 10 /dev/urandom))"

Cascade:TimeStepSize = 0.1
Cascade:TimeStep = 200

MeanField:mode=0
MeanField:optPotential = 0

111:mayDecay = off    ! pi0
221:mayDecay = off    ! eta
311:mayDecay = off    ! K0
321:mayDecay = off    ! K+
333:mayDecay = off    ! phi
3122:mayDecay = off   ! Lambda0
3212:mayDecay = off   ! Sigma0
3112:mayDecay = off   ! Sigma-
3222:mayDecay = off   ! Sigma+
3322:mayDecay = off   ! Xi0
3312:mayDecay = off   ! Xi-
3334:mayDecay = off   ! Omega-

Beams:beamA = p+
Beams:beamB = p+
Beams:eCM = 
Beams:bmin = 0
Beams:bmax = 0

Analysis:printFreq = 100
Analysis:collision = on
Analysis:timeDependenceFlow = off
Analysis:timeDependenceDensity = off
Analysis:Potentials = off
Analysis:yCut = 1
Analysis:yCutFoward = 1
Analysis:yCutMax = 3

" > $INPUTFILE

# echo $INPUTFILE

time jam -v 0 > log &

cd ..

done


