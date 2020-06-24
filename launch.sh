#!/bin/bash
#!/bin/bash
for i in {1..208}
do
  echo "flow-one_$i"
  ./lem-in < ./maps/flow_one/"flow-one_$i"

  echo "flow-ten_$i"
  ./lem-in < ./maps/flow_ten/"flow-ten_$i"

  echo "flow-thousand_$i" 
  ./lem-in < ./maps/flow_thousand/"flow-thousand_$i"
  
  echo "big_$i"
  ./lem-in < ./maps/Big/"big_$i"

  echo "big-supperposition_$i"
  ./lem-in < ./maps/big_sup/"big-supperposition_$i"
done