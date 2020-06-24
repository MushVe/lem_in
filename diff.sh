#!/bin/bash
for i in {1..100}
do
   diff ./maps/flow_one_res/"flow_one_res_cmp_$i" ./maps/flow_one_res/"flow_one_res_$i"

   diff ./maps/flow_ten_res/"flow_ten_res_cmp_$i" ./maps/flow_ten_res/"flow_ten_res_$i"

   diff ./maps/flow_thousand_res/"flow_thousand_res_cmp_$i" ./maps/flow_thousand_res/"flow_thousand_res_$i"
  
   diff ./maps/big_res/"big_res_cmp_$i" ./maps/big_res/"big_res_$i"

   diff ./maps/big_sup_res/"big_sup_res_cmp_$i" ./maps/big_sup_res/"big_sup_res_$i"
done