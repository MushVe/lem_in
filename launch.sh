#!/bin/bash
#!/bin/bash
for i in {1..208}
do
  echo "flow-one_$i"
  cat ./maps/flow_one/"flow-one_$i" | grep lines
  ./lem-in < ./maps/flow_one/"flow-one_$i"

  echo "flow-ten_$i"
  cat ./maps/flow_ten/"flow-ten_$i" | grep lines
  ./lem-in < ./maps/flow_ten/"flow-ten_$i"

  echo "flow-thousand_$i"
  cat ./maps/flow_thousand/"flow-thousand_$i" | grep lines
  ./lem-in < ./maps/flow_thousand/"flow-thousand_$i"
  
  echo "big_$i"
  cat ./maps/Big/"big_$i" | grep lines
  ./lem-in < ./maps/Big/"big_$i"

  echo "big-supperposition_$i"
  cat ./maps/big_sup/"big-supperposition_$i" | grep lines
  ./lem-in < ./maps/big_sup/"big-supperposition_$i"
done
