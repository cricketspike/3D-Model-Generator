using namespace std;
#incloude <vector>



void importside::setPixels() {
    if ( false == pic.isNull() )
    {
        std::cout << "Test" << std::endl;
        pixels = vector<vector<uint8*>>();
        for ( int row = 0; row < img.height(); ++row ){
            pixels.push_back(vector<uint8*>());
            for ( int col = 0; col < img.width(); ++col ){
                QColor clrCurrent( img.pixel( col, row ) );
                uint8 *data = new uint8 [3] {clrCurrent.red,
                                             clrCurrent.green,
                                             clrCurrent.blue};
                pixels[row].push_back(data);
            }
        }
    }
}

void box::setup(vector<QImage> images) {
    for (int count = 0; count < 6; count++){
        importside side = new importside();
        side.setPic(images[count]);
        side.face(count);
        side.setPixels();
        if(count == 0){
            side.setX(false);
            side.setY(false);
            char temp = 'x';
            side.setU(temp);
            temp = 'y';
            side.setV(temp);
        } else if (count == 1){
            side.setX(false);
            side.setY(false);
            char temp = 'x';
            side.setU(temp);
            temp = 'z';
            side.setV(temp);
        }  else if (count == 2){
            side.setX(true);
            side.setY(false);
            char temp = 'x';
            side.setU(temp);
            temp = 'y';
            side.setV(temp);
        } else if (count == 3){
            side.setX(false);
            side.setY(true);
            char temp = 'x';
            side.setU(temp);
            temp = 'z';
            side.setV(temp);
        } else if (count == 4){
            side.setX(true);
            side.setY(false);
            char temp = 'z';
            side.setU(temp);
            temp = 'y';
            side.setV(temp);
        } else if (count == 5){
            side.setX(false);
            side.setY(false);
            char temp = 'z';
            side.setU(temp);
            temp = 'y';
            side.setV(temp);
        }
        sides.push_back(side);
    }
}
