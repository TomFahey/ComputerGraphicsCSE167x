#include "Scene.h"
#include <iostream>
#include <string>
#include <glm/gtx/string_cast.hpp>

const float pi = 3.14159265 ; // For portability across platforms
float minNum = std::numeric_limits<float>::lowest();
float maxNum = std::numeric_limits<float>::max();

int main() {

	// Triangle setup
	// Vertices
	vec3 v0, v1, v2, v3, v4, v5, v6, v7;
	v0 = vec3(-1, -1, -1);
	v1 = vec3(1, -1, -1);
	v2 = vec3(1, 1, -1);
	v3 = vec3(-1, 1, -1);
	v4 = vec3(-1, -1, 1);
	v5 = vec3(1, -1, 1);
	v6 = vec3(1, 1, 1);
	v7 = vec3(-1, 1, 1);

	// Table
	Transform tableScale = Transform::Scale(vec3(2, 1, 0.25));
	mat4 tableCompoundMatrix = tableScale.m;
	Transform triangleTransform = Transform(tableCompoundMatrix);

	Triangle Triangle1 = Triangle(v0, v1, v5, triangleTransform);
	Triangle Triangle2 = Triangle(v0, v5, v4, triangleTransform);
	Triangle Triangle3 = Triangle(v3, v7, v6, triangleTransform);
	Triangle Triangle4 = Triangle(v3, v6, v2, triangleTransform);
	Triangle Triangle5 = Triangle(v1, v2, v6, triangleTransform);
	Triangle Triangle6 = Triangle(v1, v6, v5, triangleTransform);
	Triangle Triangle7 = Triangle(v0, v7, v3, triangleTransform);
	Triangle Triangle8 = Triangle(v0, v4, v7, triangleTransform);
	Triangle Triangle9 = Triangle(v0, v3, v2, triangleTransform);
	Triangle Triangle10 = Triangle(v0, v2, v1, triangleTransform);
	Triangle Triangle11 = Triangle(v4, v5, v6, triangleTransform);
	Triangle Triangle12 = Triangle(v4, v6, v7, triangleTransform);

	std::shared_ptr<Triangle> pTriangle1 = std::make_shared<Triangle>(Triangle1);
	std::shared_ptr<Triangle> pTriangle2 = std::make_shared<Triangle>(Triangle2);
	std::shared_ptr<Triangle> pTriangle3 = std::make_shared<Triangle>(Triangle3);
	std::shared_ptr<Triangle> pTriangle4 = std::make_shared<Triangle>(Triangle4);
	std::shared_ptr<Triangle> pTriangle5 = std::make_shared<Triangle>(Triangle5);
	std::shared_ptr<Triangle> pTriangle6 = std::make_shared<Triangle>(Triangle6);
	std::shared_ptr<Triangle> pTriangle7 = std::make_shared<Triangle>(Triangle7);
	std::shared_ptr<Triangle> pTriangle8 = std::make_shared<Triangle>(Triangle8);
	std::shared_ptr<Triangle> pTriangle9 = std::make_shared<Triangle>(Triangle9);
	std::shared_ptr<Triangle> pTriangle10 = std::make_shared<Triangle>(Triangle10);
	std::shared_ptr<Triangle> pTriangle11 = std::make_shared<Triangle>(Triangle11);
	std::shared_ptr<Triangle> pTriangle12 = std::make_shared<Triangle>(Triangle12);

	Material diffuseMaterial = Material(new BRDF{Color(0), 
		Color(0.6,0.6,0.5), Color(0), Color(0.6,0.6,0.5) });
	std::shared_ptr<Material> pDiffuseMaterial = std::make_shared<Material>(diffuseMaterial);
	
	GeometricPrimitive triPrimitive1 = GeometricPrimitive(pTriangle1, pDiffuseMaterial);
	GeometricPrimitive triPrimitive2 = GeometricPrimitive(pTriangle2, pDiffuseMaterial);
	GeometricPrimitive triPrimitive3 = GeometricPrimitive(pTriangle3, pDiffuseMaterial);
	GeometricPrimitive triPrimitive4 = GeometricPrimitive(pTriangle4, pDiffuseMaterial);
	GeometricPrimitive triPrimitive5 = GeometricPrimitive(pTriangle5, pDiffuseMaterial);
	GeometricPrimitive triPrimitive6 = GeometricPrimitive(pTriangle6, pDiffuseMaterial);
	GeometricPrimitive triPrimitive7 = GeometricPrimitive(pTriangle7, pDiffuseMaterial);
	GeometricPrimitive triPrimitive8 = GeometricPrimitive(pTriangle8, pDiffuseMaterial);
	GeometricPrimitive triPrimitive9 = GeometricPrimitive(pTriangle9, pDiffuseMaterial);
	GeometricPrimitive triPrimitive10 = GeometricPrimitive(pTriangle10, pDiffuseMaterial);
	GeometricPrimitive triPrimitive11 = GeometricPrimitive(pTriangle11, pDiffuseMaterial);
	GeometricPrimitive triPrimitive12 = GeometricPrimitive(pTriangle12, pDiffuseMaterial);

	AggregatePrimitive tablePrimitive = AggregatePrimitive();
	tablePrimitive.addPrimitive(&triPrimitive1);
	tablePrimitive.addPrimitive(&triPrimitive2);
	tablePrimitive.addPrimitive(&triPrimitive3);
	tablePrimitive.addPrimitive(&triPrimitive4);
	tablePrimitive.addPrimitive(&triPrimitive5);
	tablePrimitive.addPrimitive(&triPrimitive6);
	tablePrimitive.addPrimitive(&triPrimitive7);
	tablePrimitive.addPrimitive(&triPrimitive8);
	tablePrimitive.addPrimitive(&triPrimitive9);
	tablePrimitive.addPrimitive(&triPrimitive10);
	tablePrimitive.addPrimitive(&triPrimitive11);
	tablePrimitive.addPrimitive(&triPrimitive12);


	// Spheres

	vec3 T1 = vec3(-1.5, -0.8, 0.65);
	vec3 T2 = vec3(1.5, -0.8, 0.65);
	vec3 T3 = vec3(-1.5, 0.8, 0.65);
	vec3 T4 = vec3(1.5, 0.8, 0.65);

	vec3 Scale = vec3(0.4);

	Transform Sphere1Transform = Transform(Transform::Translate(T1).m * Transform::Scale(Scale).m);
	Transform Sphere2Transform = Transform(Transform::Translate(T2).m * Transform::Scale(Scale).m);
	Transform Sphere3Transform = Transform(Transform::Translate(T3).m * Transform::Scale(Scale).m);
	Transform Sphere4Transform = Transform(Transform::Translate(T4).m * Transform::Scale(Scale).m);

	std::shared_ptr<Sphere> pSphere1 = std::make_shared<Sphere>(Sphere(1, Sphere1Transform));
	std::shared_ptr<Sphere> pSphere2 = std::make_shared<Sphere>(Sphere(1, Sphere2Transform));
	std::shared_ptr<Sphere> pSphere3 = std::make_shared<Sphere>(Sphere(1, Sphere3Transform));
	std::shared_ptr<Sphere> pSphere4 = std::make_shared<Sphere>(Sphere(1, Sphere4Transform));

	Material diffuseMaterial2 = Material(new BRDF{Color(0), 
		Color(0,0.7,0.7), Color(0), Color(0,0.7,0.7) });
	std::shared_ptr<Material> pDiffuseMaterial2 = std::make_shared<Material>(diffuseMaterial2);


	GeometricPrimitive sphPrimitive1 = GeometricPrimitive(pSphere1, pDiffuseMaterial2);
	GeometricPrimitive sphPrimitive2 = GeometricPrimitive(pSphere2, pDiffuseMaterial2);
	GeometricPrimitive sphPrimitive3 = GeometricPrimitive(pSphere3, pDiffuseMaterial2);
	GeometricPrimitive sphPrimitive4 = GeometricPrimitive(pSphere4, pDiffuseMaterial2);

	// Ellipses

	vec3 T5 = vec3(0, 0, 0.5);
	vec3 T6 = vec3(0, 0, 0.5);

	vec3 Scale2 = vec3(1.0, 0.25, 0.25);

	Transform EllipsoidRotation1 = Transform::Rotate(45, vec3(0, 0, 1));
	Transform EllipsoidRotation2 = Transform::Rotate(135, vec3(0, 0, 1));

	Transform Ellipsoid1Transform = Transform(Transform::Translate(T5).m * EllipsoidRotation1.m 
		* Transform::Scale(Scale2).m);
	Transform Ellipsoid2Transform = Transform(Transform::Translate(T6).m * EllipsoidRotation2.m 
		* Transform::Scale(Scale2).m);


	std::shared_ptr<Ellipsoid> pEllipsoid1 = std::make_shared<Ellipsoid>(Ellipsoid(1, Ellipsoid1Transform));
	std::shared_ptr<Ellipsoid> pEllipsoid2 = std::make_shared<Ellipsoid>(Ellipsoid(1, Ellipsoid2Transform));
	
	Material diffuseMaterial3 = Material(new BRDF{Color(0), 
		Color(0,0.7,0), Color(0), Color(0,0.7,0) });
	std::shared_ptr<Material> pDiffuseMaterial3 = std::make_shared<Material>(diffuseMaterial3);
	Material diffuseMaterial4 = Material(new BRDF{Color(0), 
		Color(0.7,0,0), Color(0), Color(0.7,0,0) });
	std::shared_ptr<Material> pDiffuseMaterial4 = std::make_shared<Material>(diffuseMaterial4);
	
	GeometricPrimitive ellPrimitive1 = GeometricPrimitive(pEllipsoid1, pDiffuseMaterial4);
	GeometricPrimitive ellPrimitive2 = GeometricPrimitive(pEllipsoid2, pDiffuseMaterial4);
	
		
	AggregatePrimitive shapesPrimitive = AggregatePrimitive();
	shapesPrimitive.addPrimitive(&tablePrimitive);
	shapesPrimitive.addPrimitive(&sphPrimitive1);
	shapesPrimitive.addPrimitive(&sphPrimitive2);
	shapesPrimitive.addPrimitive(&sphPrimitive3);
	shapesPrimitive.addPrimitive(&sphPrimitive4);
	shapesPrimitive.addPrimitive(&ellPrimitive1);
	shapesPrimitive.addPrimitive(&ellPrimitive2);

	// Camera setup 
	vec3 eye = vec3(0, -4, 4);
	vec3 centre = vec3(0,-1,0);
	vec3 up = vec3(0, 1, 1);
	int res_x = 640;
	int res_y = 480;
	Camera myCamera = Camera(res_x, res_y, 45, eye, centre, up);
	Ray myCameraRay = Ray();
	std::cout << glm::to_string(myCameraRay.dir) << std::endl;
	Sample mySample = Sample{ 0, 240 };
	myCamera.generateRay(mySample, &myCameraRay);
	std::cout << glm::to_string(myCameraRay.dir) << std::endl;

	// Light setup
	pointLight light1 = pointLight(vec3(1,1,3), vec3(1,1,1));
	std::vector<Light> myLights = std::vector<Light>{light1};


	Film myFilm = Film(res_x, res_y, "C:\\\\Users\\tom_f\\Desktop\\test.png");
	Scene myScene = Scene(myCamera, myFilm, shapesPrimitive, myLights, 0.4, 20);
	myScene.render();
	

	return 0;
}