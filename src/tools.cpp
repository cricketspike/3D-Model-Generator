#include "tools.h"

int Tool::selected = Tool::T_POINTER;
vector<double> Tool::data;

double Tool::MOUSE_X = 0;
double Tool::MOUSE_Y = 0;
int Tool::MODIFIER = 0;

Color Tool::color(1,1,1);
Color Tool::Null::color(1,1,1);
double Tool::Null::threshold = 1;
Color Tool::Model::color(0,0,0);

QWidget* Tool::WIDGET = nullptr;

SceneObject* Tool::selectObject() {
    for(size_t i=0; i<Scene::objects.size(); ++i) {
        if(Scene::objects[i]->collision(MOUSE_X, MOUSE_Y)) {
            Scene::selected = Scene::objects[i];
            return Scene::objects[i];
        }
    }
    return nullptr;
}

void Tool::set(int t) {
    data.clear();
    if(t < T_MAX_SIZE)
        selected = t;
    else
        selected = T_POINTER;
}

void Tool::onMouseLeftPress() {
    switch(selected) {
        case T_POINTER: {
            selectObject();
        } break;
        case T_RULER: {
            data.push_back(MOUSE_X);
            data.push_back(MOUSE_Y);
        } break;
        case T_CROP: {
        } break;
        case T_PICKER: {
            //QPixmap pmap = WIDGET->grab(QRect(QPoint(MOUSE_X, MOUSE_Y), QSize(1,1)));
            /*QImage image = pmap.toImage();
            QColor pixel = image.pixel(MOUSE_X,MOUSE_Y);
            color = Color(pixel.red()/255.0, pixel.green()/255.0, pixel.blue()/255.0);*/
        } break;
    }
}

void Tool::onMouseLeftRelease() {
    switch(selected) {
        case T_POINTER: {
            Scene::selected = nullptr;
        } break;
        case T_RULER: {
            Ruler* obj = new Ruler();
            obj->x = data[0];
            obj->y = data[1];
            if(MODIFIER & M_CTRL) {
                if(abs(data[0] - MOUSE_X) > abs(data[1] - MOUSE_Y)) {
                    obj->x2 = MOUSE_X;
                    obj->y2 = data[1];
                }
                else {
                    obj->x2 = data[0];
                    obj->y2 = MOUSE_Y;
                }
            }
            else {
                obj->x2 = MOUSE_X;
                obj->y2 = MOUSE_Y;
            }
            obj->color = color;
            Scene::objects.push_back(obj);
            data.clear();
        } break;
        case T_CROP: {
        } break;
        case T_PICKER: {
        } break;
    }
}


void Tool::onMouseRightPress() {
    switch(selected) {
        case T_POINTER: {
        } break;
        case T_RULER: {
            if(selectObject() != nullptr) {
                delete Scene::selected;
                for(auto i=Scene::objects.begin(); i != Scene::objects.end(); ++i) {
                    if((*i) == Scene::selected) {
                        Scene::objects.erase(i);
                        break;
                    }
                }
            }
            data.clear();
        } break;
        case T_CROP:
            break;
        case T_PICKER:
            break;
    }
}

void Tool::onMouseRightRelease() {}

void Tool::onMouseDrag() {
    switch(selected) {
        case T_POINTER: {
            if(Scene::selected != nullptr) {
                Scene::selected->x = MOUSE_X;
                Scene::selected->y = MOUSE_Y;
            }
        } break;
    }
}

void Tool::draw(QPainter& p) {
    QBrush brush(QColor(color.r*255.0,color.g*255.0,color.b*255.0));
    p.setPen(QPen(brush, 2));
    switch(selected) {
        case T_POINTER:
            break;
        case T_RULER:
            if(data.size() > 0) {
                p.drawEllipse(data[0]-5, data[1]-5, 10, 10);
                if(MODIFIER & M_CTRL) {
                    if(abs(data[0] - MOUSE_X) > abs(data[1] - MOUSE_Y))
                        p.drawLine(data[0], data[1], MOUSE_X, data[1]);
                    else
                        p.drawLine(data[0], data[1], data[0], MOUSE_Y);
                }
                else
                    p.drawLine(data[0], data[1], MOUSE_X, MOUSE_Y);
            }
            break;
        case T_CROP:
            break;
        case T_PICKER:
            //p.setPen(QPen(QColor((int)color.r*255,(int)color.g*255,(int)color.b*255)));
            //p.fillRect(MOUSE_X, MOUSE_Y, 10, 10, QColor((int)color.r*255,(int)color.g*255,(int)color.b*255));
            break;
        case T_PAINT:
            // do nothing
            break;
    }
}
