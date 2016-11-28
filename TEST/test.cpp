#include "test_nullify.h"
#include "test_tools.h"

int main() {
	test_colorPercentDifference();
	test_colorPercentError();
	test_colorVectorDifference();
	
	test_updateMouse();
	test_setTool();
	test_setInvalidTool();
	test_makeRuler();
	test_deleteRuler();
	
	return 0;
}