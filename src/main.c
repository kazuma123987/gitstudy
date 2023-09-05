#include "app1.h"
#include "app2.h"
#include "app3.h"
#include "public1.h"
#include "public2.h"
#include "Static.h"

int main(int argc, char *argv[])
{
	printf("main: cmake\r\n");
	App1_print();
	App2_print();
	App3_print();
	Public1_print();
	Public2_print();
	Static_print();
	printf("main: end\r\n");
    return 0;
}
