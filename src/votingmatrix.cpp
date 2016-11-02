
#include "votingmatrix.h"
#include <vector>

VotingMatrix::VotingMatrix(int undivided_width, int undivided_height, int undivided_depth, ImportedImage image,float resolution_split) {

    m_width = undivided_width/resolution_split;
    m_height = undivided_height/resolution_split;
    m_depth = undivided_depth/resolution_split;

    m_image = image;
    m_resolution_split=resolution_split;
    initMatrix();
    for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {

            for (int k = 0; k < m_depth; k++) {

                matrix[i][j][k]=createElement(i*resolution_split,j*resolution_split,k*resolution_split);
            }
        }
    }

}

MatrixNode VotingMatrix::getValue(int x, int y, int z) {
    if (x < 0 || x >= m_width) {
        std::cerr << "error: x is out of bounds, x =" << x << "total width=" << m_width << std::endl;
        exit(1);
    }
    if (y < 0 || y >= m_height) {
        std::cerr << "error: y is out of bounds, y =" << y << "total height=" << m_height << std::endl;
        exit(1);
    }
    if (z < 0 || z >= m_depth) {
        std::cerr << "error: z is out of bounds, z =" << z << "total depth=" << m_depth << std::endl;
        exit(1);

    }
    return *matrix[x][y][z];

}

void VotingMatrix::setValue(int x, int y, int z, MatrixNode value) {
    if (x < 0 || x >= m_width) {
        std::cerr << "error: x is out of bounds, x =" << x << "total width=" << m_width << std::endl;
        return;
    }
    if (y < 0 || y >= m_height) {
        std::cerr << "error: y is out of bounds, y =" << y << "total height=" << m_height << std::endl;
        return;
    }
    if (z < 0 || z >= m_depth) {
        std::cerr << "error: z is out of bounds, z =" << z << "total depth=" << m_depth << std::endl;
        return;
    }
    matrix[x][y][z] = &value;
}

void VotingMatrix::initMatrix() {//creates a 3d matrix[width][height][depth] wtih all elements initialized to 0
    matrix =
        std::vector<std::vector<std::vector<MatrixNode*>>>(
            m_width,
            std::vector<std::vector<MatrixNode*>>(
                m_height,
                std::vector<MatrixNode*>(

                    m_depth, nullptr

                    )
                )
            );
}

MatrixNode *VotingMatrix::createElement(int i_wid, int j_hei, int k_dep) {
    //BANANA: there is a return statement for each of the image depth dimensions (for example an image with x and y has depth z)
        //each of these returns a new matrix node with a color value and a voting weight
        //we need to add a weight multiplier based on a 2d graph of (probably int values from 0 to 100?) and later do the same for depth



    //based on the position in the array and the images angle finds the correct color from the image and sets the colored vertex's weight
    //init local vars
    int image_width = m_image.getImageWidth()/m_resolution_split;
    int image_height = m_image.getImageHeight()/m_resolution_split;
    char u = m_image.getU();//images U and V values represent which of the cube's dimensions match with which of the image's
    char v = m_image.getV();
    float full_width=m_width*m_resolution_split;//width, height and depth of photo if it had full resolution
    float full_height=m_height*m_resolution_split;
    float full_depth=m_depth*m_resolution_split;

    if (u == 'x') {//true for all but the left and right faces
        if (image_width != m_width) {
            std::cerr << "error: image has width of " << image_width << "trying to project on a cube's width of" << m_width << std::endl;
            exit(1);
        }
        if (m_image.uIsInverted()) {
            i_wid = full_width - 1 - i_wid;
        }
        if (v == 'y') {// true for front and back views
            if (image_height != m_height) {
               // std::cerr << "error: image has height of " << image_height << "trying to project on a cube's height of" << m_height << std::endl;
                exit(1);
            }


            if (m_image.vIsInverted()) {
                j_hei = full_height - 1 - j_hei;
            }
            if (m_image.depthIsInverted()) {
                k_dep = full_depth - 1 - k_dep;
            }

            uint8_t *colors = m_image.getValue(i_wid, j_hei);
            return new MatrixNode(colors[0], colors[1], colors[2], ((float)k_dep)/full_depth);//BANANA

        }
        else if (v == 'z') {//true for up and down views
            if (image_height!= m_depth) {
                //std::cerr << "error: image has height of " << image_height << "trying to project on a cube's depth of" << m_depth << std::endl;

            }
            if (m_image.vIsInverted()) {
                k_dep = full_depth - 1 - k_dep;
            }
            if (m_image.depthIsInverted()) {
                j_hei = full_height - 1 - j_hei;
            }
            uint8_t *colors = m_image.getValue(i_wid, k_dep);
            return new MatrixNode(colors[0], colors[1], colors[2], ((float)j_hei)/full_height);//BANANA
        }
       // std::cerr << "error: image does not have the right angles UV= " <<u<<", "<<v <<std::endl;
                exit(1);
    }
    else if (u == 'z'&&v == 'y') {//left/right(same vertical axis)
        if (image_width != m_depth) {
      //      std::cerr << "error: image has width of " << image_width << "trying to project on a cube's depth of" << m_depth << std::endl;
        }
        if (m_image.getImageHeight() != m_height) {
      //      std::cerr << "error: image has height of " << image_height << "trying to project on a cube's height of" << m_height << std::endl;
        }
        if (m_image.uIsInverted()) {
            k_dep = full_depth - 1 - k_dep;

        }
        if (m_image.vIsInverted()) {
            j_hei = full_height - 1 - j_hei;
        }
        if (m_image.depthIsInverted()) {
            i_wid = full_width - 1 - i_wid;

        }else{
}
        uint8_t *colors = m_image.getValue(k_dep, j_hei);
        return new MatrixNode(colors[0], colors[1], colors[2], ((float)i_wid)/full_width);//BANANA
    }
    else {
        std::cerr << "error: image does not have the right angles UV= " <<u<<", "<<v <<std::endl;
                exit(1);
    }
}
void VotingMatrix::print(){//prints out every node in the resulting voting matrix
    for(int i=0; i<m_width;i++){

        for(int j=0; j<m_height;j++){

            std::cout<<"    y="<<j<<endl;

            for(int k=0; k<m_depth;k++){

                std::cout<<"        z="<<k<<endl;
                MatrixNode * node=matrix[i][j][k];
                std::cout<<"r:"<<(int)node->getColor(0)<<"g:"<<(int)node->getColor(1)<<"b:"<<(int)node->getColor(2)<<endl;

            }

        }

    }

}

    int VotingMatrix::getWidth() { return m_width; }
    int VotingMatrix::getHeight() { return m_height; }
    int VotingMatrix::getDepth() { return m_depth; }
