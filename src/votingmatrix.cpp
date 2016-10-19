
#include "VotingMatrix.h"
#include <vector>

VotingMatrix::VotingMatrix(int undivided_width, int undivided_height, int undivided_depth, ImportedImage image,float resolution_split) {

    m_width = undivided_width/resolution_split;
    m_height = undivided_height/resolution_split;
    m_depth = undivided_depth/resolution_split;

    cout<<"init start:"<<" w: "<<m_width<<" h:"<<m_height<<" d: "<<m_depth<<endl;
    m_image = image;
    m_resolution_split=resolution_split;
    initMatrix();
    for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {

            for (int k = 0; k < m_depth; k++) {

                matrix[i][j][k]=createElement(i,j,k);
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
    int image_width = m_image.getImageWidth()/m_resolution_split;
    int image_height = m_image.getImageHeight()/m_resolution_split;
    char u = m_image.getU();
    char v = m_image.getV();


    if (u == 'x') {
        if (image_width != m_width) {
            std::cerr << "error: image has width of " << image_width << "trying to project on a cube's width of" << m_width << std::endl;
            exit(1);
        }
        if (m_image.uIsInverted()) {
            i_wid = m_width - 1 - i_wid;
        }
        if (v == 'y') {//front/back
            if (image_height != m_height) {
               // std::cerr << "error: image has height of " << image_height << "trying to project on a cube's height of" << m_height << std::endl;
                exit(1);
            }


            if (m_image.vIsInverted()) {
                j_hei = m_height - 1 - j_hei;
            }
            if (m_image.depthIsInverted()) {
                k_dep = m_depth - 1 - k_dep;
            }

            uint8_t *colors = m_image.getValue(i_wid, j_hei);

            return new MatrixNode(colors[0], colors[1], colors[2], k_dep);

        }
        else if (v == 'z') {//up/down (same horizontal axis)
            if (image_height!= m_depth) {
                //std::cerr << "error: image has height of " << image_height << "trying to project on a cube's depth of" << m_depth << std::endl;

            }
            if (m_image.vIsInverted()) {
                j_hei = m_depth - 1 - j_hei;
            }
            if (m_image.depthIsInverted()) {
                k_dep = m_height - 1 - k_dep;
            }
            uint8_t *colors = m_image.getValue(i_wid, j_hei);
            return new MatrixNode(colors[0], colors[1], colors[2], m_depth);
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
            i_wid = m_depth - 1 - i_wid;
        }
        if (m_image.vIsInverted()) {
            j_hei = m_height - 1 - j_hei;
        }
        if (m_image.depthIsInverted()) {
            k_dep = m_width - 1 - k_dep;

        }
        uint8_t *colors = m_image.getValue(k_dep, j_hei);
        return new MatrixNode(colors[0], colors[1], colors[2], m_depth);
    }
    else {
        std::cerr << "error: image does not have the right angles UV= " <<u<<", "<<v <<std::endl;
                exit(1);
    }
}
void VotingMatrix::print(){
    for(int i=0; i<m_width;i++){

        std::cout<<"x="<<i<<endl;
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
