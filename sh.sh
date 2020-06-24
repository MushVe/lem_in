#!/bin/bash
#!/bin/bash
for i in {1..1000}
do
   ./generator --flow-one > ./maps/"flow-one_$i" 
   ./generator --flow-ten > ./maps/"flow-ten_$i" 
   ./generator --flow-thousand > ./maps/"flow-thousand_$i" 
   ./generator --big > ./maps/"big_$i" 
   ./generator --big-superposition > ./maps/"big-supperposition_$i" 
done