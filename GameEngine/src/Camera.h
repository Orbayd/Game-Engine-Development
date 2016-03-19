#ifndef CAMERA_H
#define CAMERA_H

#include "MathEngine.h"

enum CameraName
{
	CAMERA_0,
	CAMERA_1,
	NOT_INITIALIZED
};

class Camera
{

public:
	// Default constructor
   Camera( CameraName name );

   // Setup on single camera
	void setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);
	void setViewport(const int inX, const int inY, const int width, const int height);
	void setOrientAndPosition(const Vect &inUp, const Vect &inLookAt, const Vect &pos);

   // update camera system
	void updateCamera(void);

   // Get the matrices for rendering
	Matrix &getViewMatrix();
	Matrix &getProjMatrix();
	
	// accessors
	CameraName getName() const;

	// Why no SETS?  Pos,Dir,Up,LookAt, Right
	//   They have to be adjust together in setOrientAndPosition()

	void getUp( Vect &outUp ) const;
	void getDir( Vect &outDir ) const;
	void getTar( Vect &outTar) const;
	void getPos( Vect &outPos) const;
	void getRight( Vect &outRight ) const; 

			
	void getFieldOfView( float &Value) const;
	void setFieldOfView( const float Value);

	void getNearDist( float &Value) const;
	void setNearDist( const float Value);


	void getNearTopLeft(Vect &vOut) const;
	void getNearTopRight(Vect &vOut) const;
	void getNearBottomLeft(Vect &vOut) const;
	void getNearBottomRight(Vect &vOut) const;	
	void getFarTopLeft(Vect &vOut) const;
	void getFarTopRight(Vect &vOut) const;
	void getFarBottomLeft(Vect &vOut) const;
	void getFarBottomRight(Vect &vOut) const;


private:  // methods should never be public
   void privSetViewState( void );
	void privCalcPlaneHeightWidth( void );
	void privCalcFrustumVerts( void );
	void privCalcFrustumCollisionNormals( void );
	void privUpdateProjectionMatrix( void );
	void privUpdateViewMatrix( void );

private:  // data  (Keep it private)

	CameraName name;

	// camera unit vectors (up, dir, right)
	Vect	vUp;
	Vect	vDir;
	Vect	vRight;  // derived by up and dir
	Vect	vPos;   
	Vect	vTar;

	// Define the frustum inputs
	float	nearDist;
	float	farDist;
	float	fovy;
	float	aspectRatio;

	// Screen size in world space
	float	near_height;
	float	near_width;
	float	far_height;
	float	far_width;

	// viewports
	int		viewport_x;
	int		viewport_y;
	int		viewport_width;
	int		viewport_height;

	// world space coords for viewing frustum
	Vect	nearTopLeft;
	Vect	nearTopRight;
	Vect	nearBottomLeft;
	Vect	nearBottomRight;	
	Vect	farTopLeft;
	Vect	farTopRight;
	Vect	farBottomLeft;
	Vect	farBottomRight;

	// Normals of the frustum
	Vect	frontNorm;
	Vect	backNorm;
	Vect	rightNorm;
	Vect	leftNorm;
	Vect	topNorm;
	Vect	bottomNorm;

	// Projection Matrix
	Matrix	projMatrix;
	Matrix	viewMatrix;
};

#endif