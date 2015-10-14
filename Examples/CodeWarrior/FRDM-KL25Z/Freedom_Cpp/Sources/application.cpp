/*
 * main implementation: use this 'C++' sample to create your own application
 *
 */

/*#include <stdio.h>*/ /* uncomment to enable 'puts' below */

#include "application.h"

class counterclass
{
private:
  	int m_counter;
public:
	counterclass(void)
	{
		m_counter = 0;
	};
	void increment(void)
	{
		m_counter++;
	};
};

void APP_Run(void)
{
	counterclass myccounter;

	/* Enabling 'puts' below will use the UART/SCI of your target.
	 * Make sure you correctly set it up or how to use the Debug Console instead.
	 * See the targeting manual for details.
	 */
	/*puts("Hello (Kinetis) World in 'C++' from MKL25Z128 derivative!");*/

	for(;;) {
			myccounter.increment();
	}
}
