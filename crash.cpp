int func(void)
{
	int b;
	b = 1;
	return b;
}
int main(){
	func();
	int a[1024*1024*8];
	a[0] = 1;
	a[1024*1024*8 -1] = 1;
	return 0;
}
