#define EOLN(x) ((x)==10 || (x)==13 || (x)==EOF)
inline char readc(){
	static char buf[1<<16],*l=buf,*r=buf;
	return l==r && (r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?EOF:*l++;
}
template<typename T> int readi(T &x){
	T tot=0;char ch=readc(),lst='+';
	while (!isdigit(ch)) {if (ch==EOF) return EOF;lst=ch;ch=readc();}
	while (isdigit(ch)) tot=(tot<<3)+(tot<<1)+(ch^48),ch=readc();
	lst=='-'?x=-tot:x=tot;return EOLN(ch);
}
struct fastO{
	int si;char buf[1<<16];
	fastO() {si=0;}
	void putc(char ch){
		if (si==(1<<16)) fwrite(buf,1,si,stdout),si=0;
		buf[si++]=ch;
	}
	~fastO() {fwrite(buf,1,si,stdout);}
}fo;
#define putc fo.putc
template<typename T> void writei(T x,char ch='\n'){
	static int len=0,buf[100];
	if (x<0) putc('-'),x=-x;
	do buf[len++]=x%10,x/=10; while (x);
	while (len) putc(buf[--len]+48);
	if (ch) putc(ch);
}