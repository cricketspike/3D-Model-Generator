#include "Matrix_2D.h"
Matrix_2D::Matrix_2D(unsigned int width, unsigned int height, char u, char v, bool invert_u, bool invert_v, bool invert_depth){

	m_width = width;
	m_height = height;
	m_u=u;
	m_v=v;
	m_invert_u= invert_u;
	m_invert_v= invert_v;
	m_invert_depth=invert_depth;
	initArray();
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			if (m_u == 'x') {
				uint8_t *temp = new uint8_t [3]{ 0x01 , 0x01 , 0x01 };
				setValue(i, j, temp);
			}else if (m_v == 'y') {
				uint8_t *temp = new uint8_t[3]{ 0x01 , 0x01 , 0x01 };
				setValue(i, j,temp);
			}else
			{
                uint8_t *temp = new uint8_t[3]{  0x01 ,0x01 ,0x01 };
					setValue(i, j, temp);
			}

			
		}
	}

}

uint8_t* Matrix_2D::getValue(unsigned int u, unsigned int v) {
	if (u<0 || u >= m_width) {
		std::cerr << "error: u is out of bounds, u =" << u << "total 2D width=" << m_width << std::endl;
		exit(1);
	}
	if (v<0 || v >= m_height) {
		std::cerr << "error: y is out of bounds, y =" << v << "total 2D height=" << m_height << std::endl;
		exit(1);
	}
	return matrix[u][v];

}

void Matrix_2D::setValue(unsigned int u,unsigned int v, uint8_t* value) {
	if (u<0 || u >= m_width) {
		std::cerr << "error: u is out of bounds, u =" << u << "total 2D width=" << m_width << std::endl;	return;
	}
	if (v<0 || v >= m_height) {
		std::cerr << "error: y is out of bounds, y =" << v << "total 2D height=" << m_height << std::endl;
		return;
	}
	matrix[u][v] = value;
}



void Matrix_2D::initArray() {//creates a 3d matrix[width][height][depth] wtih all elements initialized to 0
	matrix = 
		std::vector<std::vector<uint8_t*>>(
			m_width,
			std::vector<uint8_t*>(
				m_height,
				0
			)
		);


}
int Matrix_2D::getImageWidth() {
	return m_width;
}
int Matrix_2D::getImageHeight() {
	return m_height;


}
char Matrix_2D::getU() { return m_u; }
char Matrix_2D::getV() { return m_v; }
bool Matrix_2D::invertU() { return m_invert_u; }
bool Matrix_2D::invertV() { return m_invert_v; }
bool Matrix_2D::invertDepth(){ return m_invert_depth; }
