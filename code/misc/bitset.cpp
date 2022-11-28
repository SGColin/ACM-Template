bitset<maxn> S;

S.count(); // count 1
S.any(); // if exist 1
S.none(); // if not exist 1
S.all(); // if not exist 0
S.flip(i); // S[i]^=1

S._Find_first(); // first S[j]=1
S._Find_next(i); // first S[j]=1(j>i)
for (int i=S._Find_first();i<S.size();i=S._Find_next(i));