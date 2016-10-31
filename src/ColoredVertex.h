#ifndef COLOREDVERTEX_H
#define COLOREDVERTEX_H
#include<stdio.h>
#include<iostream>
#include"votingmatrix.h"
#include <vector>
class ColoredVertexMatrix;
class VotingNode {
public:

	void addVoter(MatrixNode voter) {
		voters.push_back(voter);
		float red = 0, green = 0, blue = 0, count = 0;
		//set colors to be the average value

        for(int i=0; i<voters.size();  i++) {
			count++;
            red += voters[i].getColor(0);
            green += voters[i].getColor(1);
            blue += voters[i].getColor(2);
		}
		colors[0] = round(red / count);
		colors[1] = round(green / count);
		colors[2] = round(blue / count);
	}
	uint8_t getColor(int RGorB_ZeroToTwo) {
		//0R 1G 2B
		if (RGorB_ZeroToTwo > 2)
		{
			std::cerr << "ERROR RGorB_ZeroToTwo must be between 1(red) and 2(blue)";
		}
		return colors[RGorB_ZeroToTwo];
	}
	float getWeight() {
		float weight = 0;
        foreach(MatrixNode v , voters) {
			weight += v.getWeight();
		}
		return weight;

	}

    void printValues(){

        std::cout<<"R:"<<(int)colors[0]<<" G:"<<(int)colors[1]<<" B:"<<(int)colors[2]<<"Weight:"<<getWeight()<<std::endl;
    }

private:
	std::vector<MatrixNode> voters;
	uint8_t colors[3];



};


class ColoredVertex {//represents a color at a certain point on the Matrix
public:
    ColoredVertex(){
        is_null=true;
        //this is just  placeholder until he obejct is taken by an actual vertex
    }
    ColoredVertex(int w, int h, int d, ColoredVertexMatrix *par_cvm);
    uint8_t* getValue();
    void addVoter(MatrixNode voter) ;
    void setValueFromVoters(int grouping_tollerance);
    bool isInside();
    int getX();
    int getY();
    int getZ();
    void printVert();
    ColoredVertex copy(ColoredVertexMatrix* cvm);
    bool isNull(){return is_null;}
    void setValue(uint8_t* v);
protected:


private:
    bool is_null=false;
    bool smooth=true;
            ColoredVertexMatrix * cvm;
	uint8_t* value;
	std::vector<std::vector<ColoredVertex>> faces;
	std::vector<MatrixNode> voters;
    int width, height, depth;

};
#endif
