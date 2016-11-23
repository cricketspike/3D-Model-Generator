#ifndef MATRIXNODE_H
#define MATRIXNODE_H
#include<cstdint>
#include<cassert>

class MatrixNode {
public:
	MatrixNode(uint8_t red, uint8_t blue, uint8_t green,float weight_value) {
		colors = new uint8_t[3];
		colors[0] = red;
		colors[1] = blue;
		colors[2] = green;
		weight = weight_value;
	}
    uint8_t getColor(int RGorB_ZeroToTwo) {
		//0R 1G 2B
		if (RGorB_ZeroToTwo > 2)
		{
			std::cerr << "ERROR RGorB_ZeroToTwo must be between 1(red) and 2(blue)";
	}
		return colors[RGorB_ZeroToTwo];
	}
    uint8_t colorContrast(MatrixNode otherMatrix){
		int dif = 0;
		for (int i = 0; i < 3; i++) {
			dif += colors[i] - otherMatrix.getColor(i);
		}
		return abs(dif);
	}

    uint8_t colorContrast(uint8_t red, uint8_t  green, uint8_t blue) {
		int dif = 0;
		dif += colors[0] - red;
		dif += colors[1] - green;
		dif += colors[2] - blue;
		return abs(dif);
	}
	float getWeight() { return weight; }
    void printValues(){

std::cout<<"R:"<<(int)colors[0]<<" G:"<<(int)colors[1]<<" B:"<<(int)colors[2]<<weight<<std::endl;
    }
protected:

private:
	float weight;
	uint8_t * colors;


};
#endif // !MATRIXNODE_H
