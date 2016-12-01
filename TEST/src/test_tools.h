/*	This test covers:
		updateMouse()
		set()
		<creating rulers>
		<deleting rulers>
*/

#include "tools.h"

bool test_updateMouse() {
	bool test = true;
	
	printf("updateMouse():\n");
	Tool::updateMouse(100,100);
	test = (Tool::MOUSE_X == 100 && Tool::MOUSE_Y == 100);
	
	if(test) printf("Success\n"); else printf("Failure\n");
	return test;
}

bool test_setTool() {
	bool test = true;
	
	printf("set() /Valid:\n");
	Tool::set(Tool::T_PICKER);
	test = (Tool::selected == Tool::T_PICKER);
	
	if(test) printf("Success\n"); else printf("Failure\n");
	return test;
}

bool test_setInvalidTool() {
	bool test = true;
	
	printf("set() /Invalid:\n");
	Tool::set(100);
	test = (Tool::selected == Tool::T_POINTER);
	
	if(test) printf("Success\n"); else printf("Failure\n");
	return test;
}

bool test_makeRuler() {
	bool test = true;
	printf("/Create Ruler:\n");
	
	Scene::objects.clear();
	
	Tool::set(Tool::T_RULER);
	Tool::updateMouse(15,15);
	Tool::onMouseLeftPress();
	
	Tool::updateMouse(30,30);
	Tool::onMouseLeftRelease();
	
        if(Scene::objects.size() > 0) {
		test = (((Ruler*)Scene::objects[0])->x == 15
			&& ((Ruler*)Scene::objects[0])->y == 15
			&& ((Ruler*)Scene::objects[0])->x2 == 30
			&& ((Ruler*)Scene::objects[0])->y2 == 30);
		}
	else
		test = false;
	
	Scene::objects.clear();
	if(test) printf("Success\n"); else printf("Failure\n");
	return test;
}

bool test_deleteRuler() {
	bool test = true;
	printf("/Delete Ruler:\n");
	
	Scene::objects.clear();
	
	Tool::set(Tool::T_RULER);
	Tool::updateMouse(15,15);
	Tool::onMouseLeftPress();
	
	Tool::updateMouse(30,30);
	Tool::onMouseLeftRelease();
	
	Tool::onMouseRightPress();
	Tool::onMouseRightRelease();
	
	test = (Scene::objects.size() == 0);
		
	Scene::objects.clear();
	if(test) printf("Success\n"); else printf("Failure\n");
	return test;
}
