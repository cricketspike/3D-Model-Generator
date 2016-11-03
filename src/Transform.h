
#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform {
public:
	Transform(const glm::vec3 input_loc=glm::vec3(), glm::vec3 input_rot=glm::vec3(), glm::vec3 input_scale= glm::vec3(1.0f, 1.0f, 1.0f)) {//default pos,rot,scale = center, no rotation,normal scale
		m_loc = input_loc;
		m_rot = input_rot;
		m_scale = input_scale;
	}
	glm::vec3& getLoc() { return m_loc; }
	void setLoc(float x_in, float y_in, float z_in ) {
		m_loc.x = x_in;
		m_loc.y = y_in;
		m_loc.z = z_in;

	}
	glm::vec3& getRot() { return m_rot; }

	void setRot(float x_in, float y_in, float z_in) {
		m_rot.x = x_in;
		m_rot.y = y_in;
		m_rot.z = z_in;

	}
	glm::vec3& getScale() { return m_scale; }

	void setScale(float x_in, float y_in, float z_in) {
		m_scale.x = x_in;
		m_scale.y = y_in;
		m_scale.z = z_in;

	}
	glm::mat4 getModel() const {
		
		//to make a const function add const at the end, basically const functions cant change the classes feilds and const objects can only call const functions
		glm::mat4 locMatrix = glm::translate(m_loc);
		glm::mat4 rotXEulerMatrix = glm::rotate(m_rot.x, glm::vec3(1.0f, 0.0f, 0.0f));//pass in euler angles for quaternion
		glm::mat4 rotYEulerMatrix = glm::rotate(m_rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotZEulerMatrix = glm::rotate(m_rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scaleMatrix = glm::scale(m_scale);




		//multiplies in right to left order
		//order in matrix multiplication dictates which is done first

		glm::mat4 rotMatrix = rotZEulerMatrix*rotYEulerMatrix*rotXEulerMatrix;

		//scale first, then rotate,then move using(local or global?) directions
		return locMatrix*rotMatrix*scaleMatrix;

	}//total transform of object 4x4 matrix
protected:
private:
	glm::vec3 m_loc;
	glm::vec3 m_rot;
	glm::vec3 m_scale;

};

#endif // TRANSFORM_H
