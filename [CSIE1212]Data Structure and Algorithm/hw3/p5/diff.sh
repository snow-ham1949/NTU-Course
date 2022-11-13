for i in {15..15};
do
    ./main < IO/$i.in > IO/test.out
    ./others < IO/$i.in > IO/test_others.out
    diff IO/test.out IO/test_others.out
done