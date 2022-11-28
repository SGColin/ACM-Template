while true; do
  ./maker
  ./Correct
  ./Wrong
  if diff Correct.out Wrong.out; then
    printf "AC\n";
  else
    printf "WA\n";
    exit 0;
  fi
done