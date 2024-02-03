for i in {1..24}
do
  ((idx = i * 5 + 1895))
  ((idx2 = i + 3))
  echo "`sed 's/[\t ][\t ]*/ /g'  < igrf.dat | cut -d' ' -f 1,2,3,$idx2`" > igrf_$((idx)).dat
done
