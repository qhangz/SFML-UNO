#include "UNO.h"

int main()
{
	UNO uno;
	while (uno.window.isOpen())
	{
		uno.Run();
	}
	return 0;
}
