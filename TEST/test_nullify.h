/*	This test covers
		colorPercentDifference()
		colorPercentError()
		colorVectorDifference()
	
	These functions have a floating-point output
	between 0.0 and 1.0.
	
	0.0 will be returned if the colors are the same.
	1.0 will be returned only when (0,0,0) is compared to (1,1,1).
	
	colorPercentDifference() is the only function currently used in the program.
*/

#include <vector>
using namespace std;

#include "nullify.h"

bool test_colorPercentDifference() {
	bool test = true;
	float diff;
	printf("colorPercentDifference():\n");
	
	diff = colorPercentDifference(Color(0,0,0), Color(.75,.75,.75))
	if(diff < 0 || diff > 1)
		test = false;
	
	diff = colorPercentDifference(Color(.5,.5,.5), Color(.5,.5,.5))
	if(diff != 0)
		test = false;
	
	diff = colorPercentDifference(Color(0,0,0), Color(1,1,1))
	if(diff != 1)
		test = false;
	
	if(test) printf("Success\n"); else printf("Failure\n");
	return test;
}

bool test_colorPercentError() {
	bool test = true;
	float diff;
	printf("colorPercentError():\n");
	
	diff = colorPercentError(Color(0,0,0), Color(.75,.75,.75))
	if(diff < 0 || diff > 1)
		test = false;
	
	diff = colorPercentError(Color(.5,.5,.5), Color(.5,.5,.5))
	if(diff != 0)
		test = false;
	
	diff = colorPercentError(Color(0,0,0), Color(1,1,1))
	if(diff != 1)
		test = false;
	
	if(test) printf("Success\n"); else printf("Failure\n");
	return test;
}

bool test_colorVectorDifference() {
	bool test = true;
	float diff;
	printf("colorVectorDifference():\n");
	
	diff = colorVectorDifference(Color(0,0,0), Color(.75,.75,.75))
	if(diff < 0 || diff > 1)
		test = false;
	
	diff = colorVectorDifference(Color(.5,.5,.5), Color(.5,.5,.5))
	if(diff != 0)
		test = false;
	
	diff = colorVectorDifference(Color(0,0,0), Color(1,1,1))
	if(diff != 1)
		test = false;
	
	if(test) printf("Success\n"); else printf("Failure\n");
	return test;
}