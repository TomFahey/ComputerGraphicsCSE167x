#include "shape.h"

Shape::Shape() : Obj2Wrld(Transform(mat4(1))), Wrld2Obj(Transform(mat4(1))), invertSurface(false) {}
Shape::Shape(Transform O2W, Transform W2O, bool invertSurface) : Obj2Wrld(O2W), Wrld2Obj(W2O), invertSurface(invertSurface) {}
Shape::Shape(Transform O2W) : Obj2Wrld(O2W), Wrld2Obj(Transform(O2W.mInv)), invertSurface(false) {}
Shape::~Shape() {}
//Bounds Shape::ObjectBound() {
//	return Bounds();
//}
Bounds Shape::WorldBound() {
	Bounds tBounds = Obj2Wrld(ObjectBound());
	return Bounds(tBounds.pMin, tBounds.pMax);
}
// bool Shape::Intersect(const Ray& ray, float* tHit, SurfaceInteraction* interaction);
// bool Shape::IntersectP(const Ray& ray);


Sphere::Sphere() : radius(1), Shape() {}
Sphere::Sphere(float r, Transform O2W) : Shape(O2W) , radius(r) {}
Sphere::Sphere(float r, Transform O2W, Transform W2O) : Shape(O2W, W2O, false) , radius(r) {}
Bounds Sphere::ObjectBound() {
	return Bounds(vec3(-radius), vec3(radius));
}
Bounds Sphere::WorldBound() {
	vec3 center = Obj2Wrld(vec3(0));
	float nR_x = radius * glm::length(vec3(Obj2Wrld.m[0]));
	float nR_y = radius * glm::length(vec3(Obj2Wrld.m[1]));
	float nR_z = radius * glm::length(vec3(Obj2Wrld.m[2]));
	vec3 newRadius = vec3(nR_x, nR_y, nR_z);
	return Bounds(vec3(-newRadius), vec3(newRadius)) + center;
}

bool Sphere::Intersect(const Ray& ray, float* tHit, SurfaceInteraction *surface) {
	float t0, t1;
	vec3 d = ray.dir;
	vec3 o = ray.point;
	vec3 c = vec3(Obj2Wrld.m[3]);
	vec3 r = o - c;
	float scaleFactor = glm::length(Obj2Wrld.m[0]);
	float discrim = pow(glm::dot(d, r), 2) - (glm::dot(d, d) * (glm::dot(r, r) - pow(scaleFactor*radius, 2)));
	if (discrim < 0) return false;
	else {
		float rootDiscrim = glm::sqrt(discrim);
		float dsquared = glm::dot(d, d);
		float minusDdotR = glm::dot(-d, r);
		t0 = (minusDdotR - rootDiscrim) / dsquared;
		t1 = (minusDdotR + rootDiscrim) / dsquared;
		if (t0 < 0 && t1 < 0) return false;
		if (t0 > 0) {
			if (*tHit) *tHit = t0;
		}
		else {
			if (*tHit) *tHit = t1;
		}
		vec3 pHit = ray(*tHit);
		if (surface) {
			surface->localGeo.point = pHit;
			surface->localGeo.normal = this->getNormal(pHit);
		}
		return true;
	}
}

bool Sphere::IntersectP(const Ray& ray) {
	vec3 d = ray.dir;
	vec3 o = ray.point;
	vec3 c = vec3(Obj2Wrld.m[3]);
	vec3 r = o - c;
	float discrim = pow(glm::dot(d, r), 2) - (glm::dot(d, d) * (glm::dot(r, r) - pow(radius, 2)));
	return (discrim > 0);
}


vec3 Sphere::getNormal(vec3 point) {
	vec3 origin = vec3(Obj2Wrld.m * vec4(0, 0, 0, 1));
	vec3 norm = point - origin;
	return glm::normalize(norm);
}


Ellipsoid::Ellipsoid() : Sphere() {}
Ellipsoid::Ellipsoid(float r, Transform O2W) : Sphere(r, O2W) {}
Ellipsoid::Ellipsoid(float r, Transform O2W, Transform W2O) : Sphere(r, O2W, W2O) {}
bool Ellipsoid::Intersect(const Ray& ray, float* tHit, SurfaceInteraction *surface) {
	Ray transformedRay = Wrld2Obj(ray);
	Sphere unitSphere(1, Transform(mat4(1)));
	float t0;
	bool intersect = unitSphere.Intersect(transformedRay, &t0, surface);
	if (intersect) {
		vec3 p = transformedRay(t0);
		vec4 P = Obj2Wrld.m * vec4(p,1);
		vec3 dirInv = vec3(1 / ray.dir.x, 1 / ray.dir.y, 1 / ray.dir.z);
		vec3 tWrld = dirInv * vec3(P.x, P.y, P.z);
		float tFinal = (tWrld.x > 0 && tWrld.x < maxNum) ? tWrld.x :
			(tWrld.y > 0 && tWrld.y < maxNum) ? tWrld.y :
			(tWrld.z > 0 && tWrld.z < maxNum) ? tWrld.z : *tHit;
		if (tHit) *tHit = tFinal;
		vec3 pHit = ray(*tHit);
		if (surface) {
			surface->localGeo.point = pHit;
			surface->localGeo.normal = this->getNormal(pHit);
		}
		return true;
	}
	else return false;
}

bool Ellipsoid::IntersectP(const Ray& ray) {
	Ray transformedRay = Wrld2Obj(ray);
	Sphere unitSphere(1, Transform(mat4(1)));
	float t0;
	bool intersect = unitSphere.IntersectP(transformedRay);
	return intersect;
}


vec3 Ellipsoid::getNormal(vec3 point) {
	mat4 normalTransMatrix = glm::transpose(Obj2Wrld.mInv);
	vec3 norm = vec3(normalTransMatrix * (Wrld2Obj.m * (vec4(point, 1))));
	return glm::normalize(norm);
}

Triangle::Triangle() : v1(vec3(1)), v2(vec3(1)), v3(vec3(1)), Shape() {}
Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, Transform O2W) : Shape(O2W), v1(v1), v2(v2), v3(v3) {}
Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, Transform O2W, Transform W2O) : Shape(O2W, W2O, false), v1(v1), v2(v2), v3(v3) {}
Bounds Triangle::ObjectBound() {
	vec3 pMin = vec3(maxNum), pMax = vec3(minNum);
	mat3 verts = mat3(v1, v2, v3);
	for (int i = 0; i < 3; i++) {
		pMin = glm::min(pMin, verts[i]);
		pMax = glm::max(pMax, verts[i]);
	}
	return Bounds(pMin, pMax);
}
Bounds Triangle::WorldBound() {
	vec4 V1 = Obj2Wrld.m * vec4(v1,1); 
	vec4 V2 = Obj2Wrld.m * vec4(v2,1); 
	vec4 V3 = Obj2Wrld.m * vec4(v3,1);
	vec3 pMin = vec3(maxNum), pMax = vec3(minNum);
	mat3 verts = mat3(vec3(V1), vec3(V2), vec3(V3));
	for (int i = 0; i < 3; i++) {
		pMin = glm::min(pMin, verts[i]);
		pMax = glm::max(pMax, verts[i]);
	}
	return Bounds(pMin, pMax);
}

bool Triangle::Intersect(const Ray& ray, float* tHit, SurfaceInteraction *surface) {
	vec3 V1 = vec3(Obj2Wrld.m * vec4(v1, 1));
	vec3 V2 = vec3(Obj2Wrld.m * vec4(v2, 1));
	vec3 V3 = vec3(Obj2Wrld.m * vec4(v3, 1));
	vec3 a = V1, b = (V1 - V2), c = (V1 - V3), d = ray.dir;
	vec3 X;
	mat3 A = mat3(b, c, d);
	bool singularMatrix = glm::determinant(A) == 0.f;
	if (singularMatrix) {
		return false;
	}
	mat3 invA = Transform::InvertMat3(A);
	vec3 B = V1 - ray.point;
	X = invA * B;
	float beta = X[0], gamma = X[1], t = X[2];
	float t0 = ray.tMin, t1 = ray.tMax;
	if ((t < t0) || (t > t1)) return false;
	if ((gamma < 0) || (gamma > 1)) return false;
	if ((beta < 0) || (beta > (1 - gamma))) return false;
	if (tHit) *tHit = t;
	vec3 pHit = ray(*tHit);
	if (surface) {
		surface->localGeo.point = pHit;
		surface->localGeo.normal = this->getNormal();
	}
	return true;
}

bool Triangle::IntersectP(const Ray& ray) {
	bool intersect = Intersect(ray, new float(0), nullptr);
	return intersect;
}

vec3 Triangle::getNormal() {
	return glm::normalize(glm::cross(v2-v1, v3-v1));
}
