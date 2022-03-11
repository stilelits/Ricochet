/*
 * Vector.h
 *
 *  Created on: Nov 22, 2017
 *      Author: tr_dawson
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <math.h>
#include <vector>

class Vector {
public:
 Vector(float dxNew, float dyNew);
 float dx;
 float dy;
 float magnitude;
 float getLength();
};
struct VectorComparer{
 bool operator()(const Vector* d1, const Vector* d2){
  return d1->magnitude < d2->magnitude;
 }
};
struct VectorVectorComparer{
 bool operator()(const std::vector<Vector*> &v1, const std::vector<Vector*> &v2){
  return v1[0]->magnitude < v2[0]->magnitude;
 }
};


#endif /* VECTOR_H_ */
