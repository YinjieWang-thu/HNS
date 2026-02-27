#!/bin/bash
 

for ((i=1; i<=5; i++)); do

WRKSUBDIR=`printf %d $i`
echo $WRKSUBDIR
cd $WRKSUBDIR
python3 ../lambda_events.py

cd ..

done


