#include <stdio.h>
float side;
float area;
float volume;
void square(){area = side * side; }
void cube(){volume = area * side; }
int main(){
	side = 2;
	square();
	cube();
	printf("volume: %f\n", volume);
	return 0;
}


