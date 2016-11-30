
#include "coloredvertexmatrix.h"

ColoredVertexMatrix::ColoredVertexMatrix(unsigned int undivided_width, unsigned int undivided_height, unsigned int undivided_depth, std::vector<VotingMatrix> image_matrices ,float resolution_split, uint8_t * background,float bg_bias){
    m_width = undivided_width/resolution_split;
    m_height = undivided_height/resolution_split;
    m_depth = undivided_depth/resolution_split;
    color_contrast_tollerance = 30;
	matrix = std::vector<std::vector<std::vector<ColoredVertex>>>();
    //create an empty 3d Matrix before starting voting
    for (unsigned int i = 0; i < m_width; i++) {
		matrix.push_back(std::vector<std::vector<ColoredVertex>>());
        for (unsigned int j = 0; j < m_height; j++) {
			matrix[i].push_back(std::vector<ColoredVertex>());
            for (unsigned int k = 0; k < m_depth; k++) {
                ColoredVertex temp = ColoredVertex(i, j, k,this,bg_bias);
				matrix[i][j].push_back( temp);
			}
		}
	}
    //go through with each voting array and add every element as a voter to the corresponding element in the main matrix
    for (unsigned int i_im = 0; i_im < image_matrices.size(); i_im++) {
        for (unsigned int i = 0; i < m_width; i++) {
            for (unsigned int j = 0; j < m_height; j++) {
                for (unsigned int k = 0; k < m_depth; k++) {
					matrix[i][j][k].addVoter(image_matrices[i_im].getValue(i, j, k));
				}
			}
		}
    }


    //go through the main matrix and for each element find similar voters and add their weights together and set the color value to be the average of their values
    for (unsigned int i = 0; i < m_width; i++) {
        for (unsigned int j = 0; j < m_height; j++) {
            for (unsigned int k = 0; k < m_depth; k++) {
				matrix[i][j][k].setValueFromVoters(color_contrast_tollerance);

			}
		}
	}

}
bool ColoredVertexMatrix::isValid(unsigned int x,unsigned int y,unsigned int z){
    if(x<0||x>=m_width||y<0||y>=m_height||z<0||z>=m_depth){
        return false;
    }
    ColoredVertex vert=getValue(x,y,z);
    if( vert.isNull() ||vert.getValue()[3]!=1){
        return false;
    }
    return true;

}

bool ColoredVertexMatrix::isFinal(unsigned int x,unsigned int y, unsigned int z){
    if(x<0||x>=m_width||y<0||y>=m_height||z<0||z>=m_depth){
        return false;
    }
    ColoredVertex vert=getValue(x,y,z);
    return vert.isFinal();

}



unsigned int ColoredVertexMatrix:: totalVerts(){
    unsigned int count=0;
    for (unsigned int i = 0; i < m_width; i++) {
        for (unsigned int j = 0; j < m_height; j++) {
            for (unsigned int k = 0; k < m_depth; k++) {
                if (isValid(i,i,k)){count++;}

            }
        }
    }
    return count;


}


ColoredVertexMatrix::ColoredVertexMatrix(ColoredVertexMatrix * original,int vertices_density_split){
    m_width=original->getWidth();
    m_height=original->getHeight();
    m_depth=original->getDepth();
    matrix = std::vector<std::vector<std::vector<ColoredVertex>>>();
    for (unsigned int i = 0; i < m_width; i++) {
        matrix.push_back(std::vector<std::vector<ColoredVertex>>());
        for (unsigned int j = 0; j < m_height; j++) {
            matrix[i].push_back(std::vector<ColoredVertex>());
            for (unsigned int k = 0; k < m_depth; k++) {
                ColoredVertex temp_vert=original->getValue(i,j, k).copy(this);
                if(original->getValue(i,j, k).isInside(vertices_density_split)){
                    temp_vert.getValue()[3]=0;
                }
                matrix[i][j].push_back( temp_vert);
            }
        }
    }
}
 ColoredVertexMatrix* ColoredVertexMatrix::getShell(int vertices_density_split){
        ColoredVertexMatrix *shell= new ColoredVertexMatrix(this,vertices_density_split);
        return shell;
    }

std::vector <float> ColoredVertexMatrix :: getListOfVertsAsFloats(){
    std::vector <float>list= std::vector<float>();
    for (unsigned int i = 0; i < m_width; i++) {
        for (unsigned int j = 0; j < m_height; j++) {
            for (unsigned int k = 0; k < m_depth; k++) {
                uint8_t* position=getValue(i,j,k).getValue();
                                if (getValue(i,j,k).getValue()[3] !=1){
                                list.push_back(position[0]);
                                list.push_back(position[1]);
                                list.push_back(position[2]);
        }
        }
        }
    }
    return list;
}
