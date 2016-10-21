
#include "ColoredVertexMatrix.h"

ColoredVertexMatrix::ColoredVertexMatrix(unsigned int undivided_width, unsigned int undivided_height, unsigned int undivided_depth, std::vector<VotingMatrix> image_matrices ,float resolution_split ){
    m_width = undivided_width/resolution_split;
    m_height = undivided_height/resolution_split;
    m_depth = undivided_depth/resolution_split;
    color_contrast_tollerance = 30;
	matrix = std::vector<std::vector<std::vector<ColoredVertex>>>();
    for (unsigned int i = 0; i < m_width; i++) {
		matrix.push_back(std::vector<std::vector<ColoredVertex>>());
        for (unsigned int j = 0; j < m_height; j++) {

			matrix[i].push_back(std::vector<ColoredVertex>());
            for (unsigned int k = 0; k < m_depth; k++) {
                ColoredVertex temp = ColoredVertex(i, j, k);
				matrix[i][j].push_back( temp);
			}
		}
	}
	for (unsigned int i_im = 0; i_im < image_matrices.size(); i_im++) {
        cout<<"--------image" <<image_matrices.size()<<":"<<i_im<<endl;
        cout<<"wid: "<<m_width<<" len: "<<m_height<<" dep: "<<m_depth<<endl;
		//first go through with each voting array and add every element as a voter to the corresponding element in the main matrix
        for (unsigned int i = 0; i < m_width; i++) {

            for (unsigned int j = 0; j < m_height; j++) {

                for (unsigned int k = 0; k < m_depth; k++) {
					matrix[i][j][k].addVoter(image_matrices[i_im].getValue(i, j, k));
				}
			}
		}
		//next go through the main matrix and for each element find similar voters and add their weights together and set the color value to be the average of their values
		//


	}
    for (unsigned int i = 0; i < m_width; i++) {
        for (unsigned int j = 0; j < m_height; j++) {
            for (unsigned int k = 0; k < m_depth; k++) {
				matrix[i][j][k].setValueFromVoters(color_contrast_tollerance);

			}
		}
	}



}
