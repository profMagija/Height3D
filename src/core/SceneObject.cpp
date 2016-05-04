
#include "Buffer.hpp"
#include "SceneObject.hpp"


using namespace std;

SceneObject::SceneObject(AbstractModel *_model, Texture *_texture, float _x, float _y, float _z, float _alpha, float _phi, float _a, float _b, float _c) 
{
	m_model = _model;
	m_texture = _texture; 
	m_x = _x; 
	m_y = _y;
	m_z = _z;
	m_alpha = _alpha;
	m_phi = _phi;
	m_a = _a;
	m_b = _a; 
	m_c = _c;

	vBuffer = new Buffer(GL_ARRAY_BUFFER );
	cBuffer = new Buffer( GL_ARRAY_BUFFER );
	tBuffer = new Buffer( GL_ARRAY_BUFFER );
	iBuffer = new Buffer( GL_ELEMENT_ARRAY_BUFFER );
}

SceneObject::~SceneObject() 
{
	delete vBuffer; 
	delete cBuffer; 
	delete tBuffer; 
	delete iBuffer; 
}
	
void SceneObject::move(Vector t) 
{
	m_x += t.getX();
	m_y += t.getY();
	m_z += t.getZ();
}

void SceneObject::rotate(float _alpha, float _phi) 
{
	m_alpha += _alpha; 
	m_phi += _phi;
}

Vector SceneObject::getPosition() 
{
	return Vector(m_x, m_y, m_z);
}
void SceneObject::setAttributes(Program* prog, int vLocation, int texCoordLocation, int vertexColorLocation, int modelLocation, int samplerLocation) 
{
	m_model->send(vBuffer, iBuffer, cBuffer, tBuffer);
	
	vBuffer->bind();
	prog->setAttributeArray(vLocation, 3);
	
	tBuffer->bind();
	prog->setAttributeArray(texCoordLocation, 2);
	
	cBuffer->bind();
	prog->setAttributeArray(vertexColorLocation, 4);

	// now we generate our model transformation
	Matrix S = Matrix::scale(m_a, m_b, m_c);
	Matrix RS = Matrix::rotation(m_phi, Vector(1.0, 0.0, 0.0)).mult(
		Matrix::rotation(m_alpha, Vector(0.0, 1.0, 0.0)).mult(S)
	);
	Matrix TRS = Matrix::translation(Vector(m_x, m_y, m_z)).mult(RS);
	prog->setUniformValue(modelLocation, TRS);

	// we bind our sampler 
	prog->setUniformValue(samplerLocation);

}
void SceneObject::bindTexture() 
{
	m_texture->bind();
}

void SceneObject::bindIndexBuffer() 
{
	iBuffer->bind();
}

void SceneObject::draw() 
{
	glDrawElements(GL_TRIANGLES, m_model->count(), GL_UNSIGNED_INT, 0);
}