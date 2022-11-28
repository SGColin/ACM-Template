inline CN operator ! (const CN &a) {return mp(a.fr,-a.sc);}
inline CN operator + (const CN &a,const CN &b) {return mp(a.fr+b.fr,a.sc+b.sc);}
inline CN operator - (const CN &a,const CN &b) {return mp(a.fr-b.fr,a.sc-b.sc);}
inline CN operator * (const CN &a,const CN &b) {
	return mp(a.fr*b.fr-a.sc*b.sc,a.fr*b.sc+a.sc*b.fr);
}
__attribute__((constructor)) void FFTPre(){
	for (int i=0;i<(maxt>>1);i++) 
		wn[i+(maxt>>1)]=mp(cos(2*pi*i/maxt),sin(2*pi*i/maxt));
	for (int i=(maxt>>1)-1;i;i--) wn[i]=wn[i<<1];
}
void FFT(CN *a,int n,int f){
	CN x,y;
	if (f>0){
		for (int k=n>>1;k;k>>=1)
			for (int i=0;i<n;i+=k<<1)
				for (int j=0;j<k;j++){
					x=a[i+j];y=a[i+j+k];
					a[i+j+k]=(x-y)*wn[k+j];
					a[i+j]=x+y;
				}
	} else {
		for (int k=1;k<n;k<<=1)
			for (int i=0;i<n;i+=k<<1)
				for (int j=0;j<k;j++){
					x=a[i+j];y=a[i+j+k]*!wn[k+j];
					a[i+j+k]=x-y;
					a[i+j]=x+y;
				}
		for (int i=0;i<n;i++) a[i].fr/=n,a[i].sc/=n;
	}
}