#define ID(x,y) (id[(x)+maxr][(y)+maxr])
DB Solve(){
	for (int i=1;i<=n;i++)
		for (int j=i+1,d=1;j<=n && d<=(R<<1);j++,d++){
			DB now=M[j][i]/M[i][i];
			for (int k=i,d=0;k<=n && d<=(R<<1);k++,d++) M[j][k]-=M[i][k]*now;
			M[j][0]-=M[i][0]*now;
		}
	for (int i=n;i;i--){
		ans[i]=M[i][0];
		for (int j=i+1;j<=n;j++) ans[i]-=M[i][j]*ans[j];
		ans[i]/=M[i][i];
	}
	return ans[ID(0,0)];
}

for (int x=-R;x<=R;x++) for (int y=-R;y<=R;y++) if (ok(x,y)) ID(x,y)=++n;
for (int x=-R;x<=R;x++)
	for (int y=-R;y<=R;y++){
		if (!ID(x,y)) continue;
		M[ID(x,y)][ID(x,y)]= ... ;
		M[ID(x,y)][0]= ... ;
		for (int f=0,xx,yy;f<4;f++)
			if (ID(xx=x+df[f][0],yy=y+df[f][1]))
				M[ID(x,y)][ID(xx,yy)]= ... ;
	}