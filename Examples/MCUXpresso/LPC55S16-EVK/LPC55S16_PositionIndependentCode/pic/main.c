
// This function is defined in mylib.c
extern unsigned int library_function( unsigned int x );

// These global variables will be in the bss section
unsigned int x;
unsigned int y;
unsigned int z = 0xdeadbeef;

int main ( void )
{
	x=7;
	y=8;
	z=library_function(77);

	while(1){
		
	}
}
