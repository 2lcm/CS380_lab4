#ifndef RIGTFORM_H
#define RIGTFORM_H

#include <iostream>
#include <cassert>

#include "matrix4.h"
#include "quat.h"

class RigTForm {
  Cvec3 t_; // translation component
  Quat r_;  // rotation component represented as a quaternion

public:
  RigTForm() : t_(0) {
    assert(norm2(Quat(1,0,0,0) - r_) < CS175_EPS2);
  }

  RigTForm(const Cvec3& t, const Quat& r) {
    //TODO
	  t_ = t;
	  r_ = r;
  }

  explicit RigTForm(const Cvec3& t) {
    // TODO
	  t_ = t;
	  r_ = Quat(1, 0, 0, 0);
  }

  explicit RigTForm(const Quat& r) {
    // TODO
	  t_ = Cvec3(0, 0, 0);
	  r_ = r;
  }

  Cvec3 getTranslation() const {
    return t_;
  }

  Quat getRotation() const {
    return r_;
  }

  RigTForm& setTranslation(const Cvec3& t) {
    t_ = t;
    return *this;
  }

  RigTForm& setRotation(const Quat& r) {
    r_ = r;
    return *this;
  }

  Cvec4 operator * (const Cvec4& a) const {
    // TODO
	  Matrix4 tt;
	  tt(0, 3) = this->getTranslation()[0];
	  tt(1, 3) = this->getTranslation()[1];
	  tt(2, 3) = this->getTranslation()[2];

	  return (tt * quatToMatrix(this->getRotation())) * a;
	  //return rigTFormToMatrix(*this) * a;

  }

  RigTForm operator * (const RigTForm& a) const {
    // TODO
	  RigTForm res;
	  Quat r1 = this->getRotation();
	  Quat r2 = a.getRotation();
	  Cvec4 tmp;
	  Cvec3 tmp2;
	  Cvec3 t1 = this->getTranslation();
	  Cvec3 t2 = a.getTranslation();

	  tmp = Cvec4(t1, 1) + (r1 * Cvec4(t2, 1));
	  tmp2 = Cvec3(tmp[0], tmp[1], tmp[2]);

	  res.setTranslation(tmp2);
	  res.setRotation(r1 * r2);
	  return res;	
	
  }
};

inline RigTForm inv(const RigTForm& tform) {
  // TODO
	RigTForm res;
	Cvec4 tmp;
	tmp = inv(tform.getRotation()) * Cvec4(tform.getTranslation(), 1);
	res.setTranslation(Cvec3(-tmp[0], -tmp[1], -tmp[2]));
	res.setRotation(inv(tform.getRotation()));
	return res;
}

inline RigTForm transFact(const RigTForm& tform) {
  return RigTForm(tform.getTranslation());
}

inline RigTForm linFact(const RigTForm& tform) {
  return RigTForm(tform.getRotation());
}

inline Matrix4 rigTFormToMatrix(const RigTForm& tform) {
  // TODO
	Matrix4 tt;
	Cvec3 asdf = tform.getTranslation();
	tt(0, 3) = asdf[0];
	tt(1, 3) = asdf[1];
	tt(2, 3) = asdf[2];
	
	return tt * quatToMatrix(tform.getRotation());
}

#endif
