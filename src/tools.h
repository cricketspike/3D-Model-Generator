/* Usage
 * Toolbar is accessed using hotkeys on the number bar.
 * 1: Pointer
 * 2: Ruler
 * 3: Color Picker
 * 4: Mover
 * 0: Set Color
 * -: Set Model Color
 * =: Set Null Color
 *
 * Rulers can be created by selecting the Ruler tool
 * and clicking and dragging the left mouse button.
 * Rulers can be snapped by holding Control.
 * Rulers can be deleted by right clicking on a node.
 * Ruler nodes can be moved by selecting the Pointer tool
 * and dragging.
 *
 * The Color Picker tool is currently not functional.
 *
 * The Mover tool allows image offset to be modified or reset.
 * Images can be moved by clicking and dragging the left mouse button.
 * Images can be reset by clicking the right mouse button.
 *
 * `Set Model Color` sets Tool::Model::color.
 * `Set Null Color` sets Tool::Null::color.
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <QWidget>
#include <QPixmap>

#include "scene.h"

struct Tool {
	struct Null {
        static Color color;
        static double threshold;
	};

	struct Model {
        static Color color;
	};
	
	enum Tools {
        T_POINTER, T_RULER, T_PICKER, T_MOVER, T_CROP, T_PAINT, T_MAX_SIZE
	};
    enum Modifiers {
        M_CTRL= 0x01, M_SHIFT= 0x02
    };
	
    static QWidget* WIDGET;

    static int selected;
	static vector<double> data;
    static Color color;
	static double MOUSE_X, MOUSE_Y;
    static int MODIFIER;

    static void set(int t);
	static void updateMouse(double x, double y) { MOUSE_X = x; MOUSE_Y = y; }
	
	static SceneObject* selectObject();
	
    static void onMouseLeftPress();
    static void onMouseRightPress();
    static void onMouseLeftRelease();
    static void onMouseRightRelease();
    static void onMouseDrag();
    static void draw(QPainter& p);
};

#endif
