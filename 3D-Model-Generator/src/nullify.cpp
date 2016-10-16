#include <cmath>
using namespace std;

#include "ColoredVertexMatrix.h"

float color_diff(uint8 c1[3], uint8 c2[3]) {
	return sqrt( pow(c1[0] - c2[0], 2) + pow(c1[1] - c2[1], 2) + pow(c1[2] - c2[2], 2) );
}

float color_diff_2(uint8 c1[3], uint8 c2[3]) {
	float r1, g1, b1, r2, g2, b2,
		x1, y1, z1, x2, y2, z2,
		l1, a1, b1, l2, a2, b2,
		a1p, a2p,
		c1, c2, c, h1, h2, hp, t,
		l, dL, k1, k2, kL, sL, dC, kC, sC, dh, dH, kH, sH, rT;
		
	r1 = c1[0]/255.0;
	g1 = c1[1]/255.0;
	b1 = c1[2]/255.0;
	r2 = c2[0]/255.0;
	g2 = c2[1]/255.0;
	b2 = c2[2]/255.0;
	
	if(r1 > 0.04045) r1 = pow( (r1 + 0.055)/1.055, 2.4) * 100;
		else r1 = r1 / 0.1292;
	if(g1 > 0.04045) g1 = pow( (g1 + 0.055)/1.055, 2.4) * 100;
		else g1 = g1 / 0.1292;
	if(b1 > 0.04045) b1 = pow( (b1 + 0.055)/1.055, 2.4) * 100;
		else b1 = b1 / 0.1292;
	if(r2 > 0.04045) r2 = pow( (r2 + 0.055)/1.055, 2.4) * 100;
		else r2 = r2 / 0.1292;
	if(g2 > 0.04045) g2 = pow( (g2 + 0.055)/1.055, 2.4) * 100;
		else g2 = g2 / 0.1292;
	if(b2 > 0.04045) b2 = pow( (b2 + 0.055)/1.055, 2.4) * 100;
		else b2 = b2 / 0.1292;
	
	x1 = ( (r1 * 0.4124) + (g1 * 0.3576) + (b1 * 0.1805) ) / 95.047;
	y1 = ( (r1 * 0.2126) + (g1 * 0.7152) + (b1 * 0.0722) ) / 100.0;
	z1 = ( (r1 * 0.0193) + (g1 * 0.1192) + (b1 * 0.9505) ) / 108.833;
	x2 = ( (r2 * 0.4124) + (g2 * 0.3576) + (b2 * 0.1805) ) / 95.047;
	y2 = ( (r2 * 0.2126) + (g2 * 0.7152) + (b2 * 0.0722) ) / 100.0;
	z2 = ( (r2 * 0.0193) + (g2 * 0.1192) + (b2 * 0.9505) ) / 108.833;
	
	if(x1 > 0.008856) x1 = pow(x1, 1/3.0);
		else x1 = (7.787 * x1) + (16/116.0);
	if(y1 > 0.008856) y1 = pow(y1, 1/3.0);
		else y1 = (7.787 * y1) + (16/116.0);
	if(z1 > 0.008856) z1 = pow(z1, 1/3.0);
		else z1 = (7.787 * z1) + (16/116.0);
	if(x2 > 0.008856) x2 = pow(x2, 1/3.0);
		else x2 = (7.787 * x2) + (16/116.0);
	if(y2 > 0.008856) y2 = pow(y2, 1/3.0);
		else y2 = (7.787 * y2) + (16/116.0);
	if(z2 > 0.008856) z2 = pow(z2, 1/3.0);
		else z2 = (7.787 * z2) + (16/116.0);
	
	l1 = (116 * x1) - 16;
	a1 = 500 * (x1 - y1);
	b1 = 200 * (y1 - z1);
	l2 = (116 * x2) - 16;
	a2 = 500 * (x2 - y2);
	b2 = 200 * (y2 - z2);
	
	c1 = sqrt( pow(a1,2) + pow(b1,2) );
	c2 = sqrt( pow(a2,2) + pow(b2,2) );
	
	dL = l2 - l1;
	l = (l1 + l2) / 2.0;
	dC = c2 - c1;
	c = (c1 + c2) / 2.0;
	
	
	h1 = fmod( atan2(b1, a1p), 6.2831853072 );
	h2 = fmod( atan2(b2, a2p), 6.2831853072 );
	if(abs(h1 - h2) <= 3.14159265358) dh = h2 - h1;
	else if(abs(h1 - h2) > 3.14159265358 && h1 >= h2) dh = h2 - h1 + 6.2831853072;
	else dh = h2 - h1 - 6.2831853072;
	
	dH = 2 * sqrt(c1 * c2) * sin(dh / 2.0);
	
	if(abs(h1 - h2) <= 3.14159265358) hp = (h1 + h2)/2.0;
	else if(abs(h1 - h2) > 3.14159265358 && h1 >= h2) hp = h2 - h1 + 6.2831853072;
	else hp = h2 - h1 - 6.2831853072;
	
	t = 1 - (0.17 * cos(hp-0.523599) + (0.24 * cos(2*hp)) + (0.32 * cos( (3*hp)+0.10472 )) - (0.2 * cos( (4*hp)-1.09956 ));
	
	k1 = 0.045;
	k2 = 0.015;
	kL = 1;
	kC = 1;
	kH = 1;
	sL = 1 + (
		(0.015 * pow(l-50, 2))
		/ sqrt(20 + pow(l-50, 2))
	);
	sC = 1 + (0.045 * c);
	sH = 1 + (0.015 * c * t);
	
	rT = (180.0 / 3.14159265358) * (
		-2
		* sqrt(
			pow(c, 7) / ( pow(c, 7) + pow(25, 7) )
		)
		* sin(
			(3.14159265358 / 180.0) * (60
				* pow(2.7182818,
					-( (h - 275) / 25.0 )
				)
			)
		)
	);
	
	return sqrt(
		pow(
			(dL)/(kL * sL)
		,2)
		+ pow(
			(dC)/(kC * sC)
		,2)
		+ pow(
			(dH)/(kH * sH)
		,2)
		+ ( (rT) * ( (dC)/(kC * sC) ) * ( (dH)/(kH * sH) ) )
	);
}

//	thresh = [0, 100]
void nullify(ColoredVertexMatrix& image, uint8 c_null[3], float thresh) {
	for(unsigned long x=0; x<image.m_width; ++x) {
		for(unsigned long y=0; y<image.m_height; ++y) {
			for(unsigned long z=0; z<image.m_depth; ++z) {
				// if color difference is less than threshold
				if( color_diff_2(image.matrix[x][y][z], c_null) < thresh )
					// set color.alpha to zero
			}
		}
	}
}