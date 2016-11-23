#ifndef SCENE_H
#define SCENE_H

#include <vector>
using namespace std;

#include <QPainter>

#include "color.h"

struct SceneObject {
    double x, y;
    Color color;
    SceneObject();
    ~SceneObject();
    virtual bool collision(double mx, double my) = 0;
    virtual void draw(QPainter& p) = 0;
};

struct Scene {
	static vector<SceneObject*> objects;
	static SceneObject* selected;
    static void draw(QPainter& p);
};

// ---- Ruler ---- //

struct Ruler : public SceneObject {
    double x2, y2;

    Ruler();
    ~Ruler();
    bool collision(double mx, double my);
    void draw(QPainter& p);
};

#endif
