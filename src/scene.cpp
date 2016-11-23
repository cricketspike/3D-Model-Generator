#include "scene.h"

SceneObject* Scene::selected = nullptr;
vector<SceneObject*> Scene::objects;

SceneObject::SceneObject() {
    x = y = 0;
}

SceneObject::~SceneObject() {}

void Scene::draw(QPainter& p) {
    for(size_t i=0; i<objects.size(); ++i)
        objects[i]->draw(p);
}

// ---- Ruler ---- //

Ruler::Ruler() {
    x2 = y2 = 0;
}

Ruler::~Ruler() {}

bool Ruler::collision(double mx, double my) {
    if( sqrt( pow(x - mx, 2) + pow(y - my, 2) ) <= 10 ) {
        return true;
    }
    else if( sqrt( pow(x2 - mx, 2) + pow(y2 - my, 2) ) <= 10 ) {
        double tx, ty;
        tx = x;
        ty = y;
        x = x2;
        y = y2;
        x2 = tx;
        y2 = ty;
        return true;
    }
    else
        return false;
}

void Ruler::draw(QPainter& p) {
    QBrush brush(QColor(color.r*255,color.g*255,color.b*255));
    p.setBrush(brush);
    p.setPen(QPen(brush, 2));
    p.drawEllipse(x-5, y-5, 10, 10);
    p.drawEllipse(x2-5, y2-5, 10, 10);
    p.drawLine(x, y, x2, y2);
}
