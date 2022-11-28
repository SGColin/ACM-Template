#define Rand() ((DB)rand()/RAND_MAX)
inline void Anneal(DB T){
	Clear(State);
	for (DB res;T>1e-14;T*=0.99){
		nextState=Change(State); // Change range is influence by T
		res=getres(State);
		if (res<ans) ans=res,ansState=State=nextState; else
		if (exp((ans-res)/T)>Rand()) State=nextState;
	}
}