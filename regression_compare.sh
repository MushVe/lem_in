#!/bin/bash
for i in {1..100}
do
  ./lem-in < ./maps/flow_one/"flow-one_$i" > ./maps/flow_one_res/"flow_one_res_cmp_$i"

  ./lem-in < ./maps/flow_ten/"flow-ten_$i" > ./maps/flow_ten_res/"flow_ten_res_cmp_$i"

  ./lem-in < ./maps/flow_thousand/"flow-thousand_$i" > ./maps/flow_thousand_res/"flow_thousand_res_cmp_$i"
  
  ./lem-in < ./maps/Big/"big_$i" > ./maps/big_res/"big_res_cmp_$i"

  ./lem-in < ./maps/big_sup/"big-supperposition_$i" >> ./maps/big_sup_res/"big_sup_res_cmp_$i"
done