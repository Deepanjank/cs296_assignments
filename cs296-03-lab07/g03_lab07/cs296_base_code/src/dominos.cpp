/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  /** /par Common details:
   * The constructor consits of several blocks: <br>
   * The Common variables and function calls in the blocks: <br>
   * b2BodyDef defines the body <br>
   * b2BodyDef has several properties attached to it:<br>
   * 1)type [b2_dynamicBody,b2_staticBody(default)] <br>
     2)position.Set{function sets the position of object} <br>
   * CreateBody creates body defined by the above point <br>
   * b2FixtureDef provides the fixture properties: <br>
     1)shape  <br>
     2)density <br>
     3)friction <br>
     4)restitution <br>
   * CreateFixture creates fixtures.Fixtures are created by initializing a fixture <br>
   * definition and then passing the definition to the parent body. <br> <br> <br>
	*/
  dominos_t::dominos_t()
  {
    //Ground
    /*! \par  Making Ground
	 * variable name : b1 ;  data type : b2Body*<br>
         * pointer to the ground<br> <br>
	 * varible name : shape ;  data type : b2EdgeShape ;  values : first end (-90.0f, 0.0f) , second end (90.0f, 0.0f))<br>
	 * refers to the shape of the ground <br>
	 */
    b2Body* b1;  
    { 
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
    //top horizontal shelf      
    /*! \par Top Horizontal Shelf
	 * variable name : topShelf	;  data type : b2Body*  <br>
	 * refers to the pointer of top horizontal shelf on which the vertical dominos are placed <br> <br>
	 * variable name : shape ;  data type : b2PolygonShape ;  values : width=6.0f ,  height=0.25f  <br>
	 * refers to the shape of top horizontal shelf<br> <br>
	 * variable name : bd ;  data type : b2BodyDef ;  values: pos= (-31.0f, 30.0f)<br>
	 * refers to the body definition of top horizontal shelf <br> <br>
	 */
    {	  
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
      b2Body* topShelf = m_world->CreateBody(&bd);
      topShelf->CreateFixture(&shape, 0.0f);
    }

    //Dominos
    /*! \par Dominos
	 * variable name : body ;  data type : b2Body* <br>
	 * refers to the pointer of various dominos <br> <br>
	 * variable name : shape ;  data type : b2PolygonShape ;  values : width=0.1f ,  height=1.0f <br>
	 * refers to the shape of a dominos <br> <br>
	 * variable name : bd ;  data type : b2BodyDef ; values : type=dynamic ,  pos= (-35.5f + 1.0f * i, 31.25f)<br>
	 * refers to the body definition of domino <br> <br>
	 * variable name : fd ;  data type : b2FixtureDef ;  values : shape= &shape ,  density= 20.0f ,  friction= 0.1f<br>
	 * refers to the fixtures of a domino <br>
	 */ 
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
	}
      
    //Another horizontal shelf
	/*! \par Another Horizontal Shelf
	 * variable name : anotherShelf ;  data type : b2Body* <br>
	 * refers to the pointer of shelf above which train of spheres is placed <br> <br>
	 * variable name : shape  ;  data type : b2PolygonShape ;  values :  <br>
	 * refers to the shape of the above shelf <br> <br>
	 * variable name : bd  ;  data type : b2BodyDef ;  values : pos= (1.0f, 6.0f) <br>
	 * refers to the body definition of the above shelf <br> <br>
	 */ 
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* anotherShelf = m_world->CreateBody(&bd);
      anotherShelf->CreateFixture(&shape, 0.0f);
    }


    //The pendulum that knocks the dominos off
	/*! \par Pendulum that knocks the dominos off
	 * variable name : b2 ;  data type : b2Body* <br> <br>
	 * variable name : bd ;  data type : b2BodyDef ;  values : pos=(-36.5f, 1.5f) <br>
	 * body definition of b2 <br> <br>
	 * variable name : shape  ;  data type : b2PolygonShape ;  values : width= 0.25f , height= 1.5f<br>
	 * refers to the shape of b2 <br> <br>
	 * variable name : b4  ;  data type : b2Body* <br>
	 * refers to the pointer of the pendulum <br> <br>
	 * variable name : shape ;   data type : b2PolygonShape ;  values : width= 0.25f , height= 0.25f<br>
	 * refers to the shape of pendulum <br> <br>
	 * variable name : bd  ;  data type : b2BodyDef ;  values : type= b2_dynamicbody ,  pos= (-40.0f, 33.0f)<br>
	 * refers to the body definition of pendulum <br> <br>
	 * variable name : jd  ;  data type : b2RevoluteJointDef <br> <br>
	 * variable name : anchor ;  data type : b2Vec2 ; values: (-37.0f, 40.0f) <br>
	 * refers to the point around which the pendulum rotates
	 */ 
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);
	  
	b2BodyDef bd;
	bd.position.Set(-36.5f, 28.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-40.0f, 33.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
      
    //The train of small spheres
	/*! \par Train of small spheres
	 * variable name : spherebody ;  data type : b2Body* <br>
	 * refers to the pointer of small spheres <br> <br>
	 * variable name : circle ;  data type : b2CircleShape ;  values : radius= 0.5 <br>
	 * refers to the shape of the spheres <br> <br>
	 * variable name : ballbd  ;  data type : b2BodyDef ;  values : type=dynamic ,  pos=(-22.2f + i*1.0, 26.6f)<br>
	 * refers to the body definition of spheres <br> <br>
	 * variable name : ballfd ; data type : b2FixtureDef ; values : shape=&circle , density=1.0f , friction=0.0f , restitution=0.0f<br>
	 * refers to the fixtures of balls  <br>
	 * The Block runs a for loop to create the spherical balls recursively.
	 */ 
    {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }

    //The pulley system

    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;
      
    //The open box
	/*! \par PULLEY SYSTEM - the open box
	 * variable name : box1  ;  data type : b2Body* <br>
	 * refers to the pointer of open box in which the spheres fall <br> <br>
	 * variable name : bs1, bs2, bs3 ;   data type : b2PolygonShape ;  values : bs1=(2,0.2, b2Vec2(0.f,-1.9f), 0) , <br>
	 * bs2=(0.2,2, b2Vec2(2.0f,0.f), 0) ,   bs3=(0.2,2, b2Vec2(-2.0f,0.f), 0)
	 * refers to the shape of three rectangles forming the box <br> <br>
	 * variable name : bd ;   data type : b2BodyDef ;  values : pos=(10,15)<br>
	 * refers to the body definition of the box <br> <br>
	 * variable name : fd1, fd2, fd3  ;  data type : b2FixtureDef ;  values : for all three density=10.0,<br>
	 * friction=0.5 ,  restitution=0.f , shape=new b2PolygonShape<br>
	 * refers to the fixtures of 3 rectangles forming the box  <br>
	 * This describes the box in which the balls are falling. 
	 */ 
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

    //The bar
	/*! \par PULLEY SYSTEM - The bar
	 * variable name : box2 ;   data type : b2Body* <br>
	 * refers to the pointer of box at the other side of pulley system <br> <br>
	 * variable name : bd  ;  data type : b2BodyDef values : pos=(10,15)<br>
	 * refers to the body definition of the bar <br> <br>
	 * variable name : fd1 ;  data type : b2FixtureDef ;  values : density=34.0 <br>
	 * refers to the fixtures of the bar <br>
	 */
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

    // The pulley joint
	/*! \par PULLEY SYSTEM - The pulley joint
	 * variable name : myjoint ;  data type : b2PulleyJointDef* ;  values : anchor1=(-10,15) anchor2=(10,15)<br>
	 * anchor3=(-10,20) anchor4=(10,20)<br>
	 * refers to the pointer of  <br> <br>
	 */
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    //The revolving horizontal platform
	/*! \par The revolving horizontal platform
	 * variable name : body, body2  ;  data type : b2Body* <br>
	 * refers to the pointer of the platform and the pivot <br> <br>
	 * variable name : shape, shape2 ;  data type : b2PolygonShape ; values : shape:width= 2.2f height= 0.2f , <br>
	 * shape2:width=0.2f height=2.0f<br>
	 * refers to the shape of the platform and the pivot <br> <br>
	 * variable name : bd, bd2 ;  data type : b2BodyDef ; values : bd:type=b2_dynamicBody pos=(14.0f,14.0f) , <br>
	 * bd2:pos= (14.0f,16.0f) <br>
	 * refers to the body definition of the platform and the pivot <br> <br>
	 * variable name : fd  ; data type : b2FixtureDef ; values : density=1.f , shape=&shape<br>
	 * refers to the fixtures of the platform  <br>
	 */
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    //The heavy sphere on the platform
	/*! \par Heavy sphere on the platform
	 * variable name : sbody ;  data type : b2Body* <br>
	 * refers to the pointer of sphere <br> <br>
	 * variable name : circle  ;  data type : b2CircleShape values : radius= 1.0<br>
	 * refers to the shape of sphere <br> <br>
	 * variable name : ballbd ;  data type : b2BodyDef ; values : type=b2_dynamicBody pos=(14.0f,18.0f) <br>
	 * refers to the body definition of sphere <br> <br>
	 * variable name : ballfd ;  data type : b2FixtureDef values : shape=&circle, density=50.0f<br>
	 * friction=0.0f , restitution=0.0f<br> 
	 * refers to the fixtures of sphere <br>
	 */
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
	
	//another revolving platform
	/*! \par The revolving horizontal platform
	 * variable name : body, body2 ;  data type : b2Body* <br>
	 * refers to the pointer of the platform and the pivot <br> <br>
	 * variable name : shape, shape2 ;  data type : b2PolygonShape ; values : shape:width=2.2f, height=0.2f <br>
	 * shape2:width=0.2f , height=6.0f<br>
	 * refers to the shape of the platform and the pivot <br> <br>
	 * variable name : bd, bd2 ;  data type : b2BodyDef value : bd:type=b2_dynamicBody , pos=(16.0f, 6.0f) ;<br>
	 * bd2:pos=(16.0f, 6.0f)<br>
	 * refers to the body definition of the platform and the pivot <br> <br>
	 * variable name : fd ; data type : b2FixtureDef ; values : density=1.f , shape= &shape <br>
	 * refers to the fixtures of the platform  <br>
	 */
	{
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(16.0f, 6.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(16.0f, 6.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
	 
	  b2PolygonShape shape1;
	  shape1.SetAsBox(0.2f,0.2f);
	  b2BodyDef bd1;
      bd1.position.Set(15.0f, 5.65f);
	  b2Body* body1 = m_world->CreateBody(&bd1);
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.f;
      fd1->shape = new b2PolygonShape;
      fd1->shape = &shape1;
      body1->CreateFixture(fd1);
    }

	//heavy box
	/*! \par Heavy box on the lower platform
	 * variable name : body ;  data type : b2Body* <br>
	 * refers to the pointer of box <br> <br>
	 * variable name : shape ;  data type : b2PolygonShape ; values : width=1.0f , width=1.0f<br>
	 * refers to the shape of box <br> <br>
	 * variable name : bd ;  data type : b2BodyDef ; values :  type= b2_dynamicBody<br>
	 * refers to the body definition of box <br> <br>
	 * variable name : fd ;  data type : b2FixtureDef  ; values : shape = &shape, density= 20.0f<br>
	 * ,friction= 0.1f<br>
	 * refers to the fixtures of box <br>
	 */
	{
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(14.2f, 7.5f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
    }


    //The see-saw system at the bottom
    {
    //The triangle wedge
	/*! \par SEE-SAW SYSTEM - The triangle wedge
	 * variable name : sbody ;  data type : b2Body* <br>
	 * refers to the pointer of wedge <br> <br>
	 * variable name : poly ;  data type : b2PolygonShape ; values : ver1=(-1,0) ver2=(1,0) ver3=(0,1.5) <br>
	 * refers to the shape of wedge <br> <br>
	 * variable name : wedgebd ;  data type : b2BodyDef ; values : pos=(40.0f, 0.0f) <br>
	 * refers to the body definition of wedge <br> <br>
	 * variable name : wedgefd ;  data type : b2FixtureDef ; values : shape= &poly, density= 10.0f ,<br>
	 * friction = 0.0f , restitution= 0.0f<br>
	 * refers to the fixtures of wedge <br>
	 */
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(40.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

    //The plank on top of the wedge
	/*! \par SEE-SAW SYSTEM - The plank on the top of wedge
	 * variable name : body ;  data type : b2Body* <br>
	 * refers to the pointer of plank <br> <br>
	 * variable name : shape ;  data type : b2PolygonShape ; values : width=15.0f , height=0.2f <br>
	 * refers to the shape of plank <br> <br>
	 * variable name : bd2 ;  data type : b2BodyDef ;  values : type= b2_dynamicBody , pos= (40.0f,1.5f) <br>
	 * refers to the body definition of plank <br> <br>
	 * variable name : fd2 ; data type : b2FixtureDef values : density=1.f , shape=&shape<br>
	 * refers to the fixtures of plank <br>
	 */
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(40.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(40.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

    //The light box on the right side of the see-saw
	/*! \par SEE-SAW SYSTEM - The light box on the right side of see-saw
	 * variable name : body3 ;  data type : b2Body* <br>
	 * refers to the pointer of the box <br> <br>
	 * variable name : shape2 ;  data type : b2PolygonShape ; values : width=2.0f height=2.0f  <br>
	 * refers to the shape of the box <br> <br>
	 * variable name : bd3 ; data type : b2BodyDef ; values : type=b2_dynamicBody , pos=(53.0f, 2.0f))<br>
	 * refers to the body definition of the box <br> <br>
	 * variable name : fd3 ; data type : b2FixtureDef ; values : density=0.01f , shape=&shape2<br>
	 * refers to the fixtures of the box <br>
	 */
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(53.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }

	//small horizontal shelf
	/*! \par horizontal shelf
	 * variable name : body ;  data type : b2Body* <br>
	 * refers to the pointer of the shelf on which the box lands at the end of animation <br> <br>
	 * variable name : shape ;  data type : b2PolygonShape ; values : pos=(42.0f, 19.0f) <br>
	 * refers to the shape of the above shelf <br> <br>
	 * variable name : bd ;  data type : b2BodyDef; values : width= 3.0f ,  height=0.25f <br>
	 * refers to the body definition of the above shelf <br> <br>
	 */
	{
      b2PolygonShape shape;
      shape.SetAsBox(3.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(42.0f, 19.0f);
      b2Body* body = m_world->CreateBody(&bd);
      body->CreateFixture(&shape, 0.0f);
    }

	//stopper
	/*! \par The stopper
	 * variable name : stopper ;  data type : b2Body* <br>
	 * refers to the pointer of the stopper that stops the heavy sphere <br> <br>
	 * variable name : shape <br>
	 * data type : b2PolygonShape <br>
	 * refers to the shape of the stopper <br> <br>
	 * variable name : bd ;  data type : b2BodyDef ; values : pos=(24.0f,0.0f) <br>
	 * refers to the body definition of stopper <br> <br>
	 * variable name : fd ;  data type : b2FixtureDef;  values : shape=&shape , density-20.0f , friction=0.1f <br>
	 * refers to the fixtures of the stopper <br>
	 */
	{
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      
	  b2BodyDef bd;
	  bd.position.Set(24.0f, 0.0f);
	  b2Body* stopper = m_world->CreateBody(&bd);
	  stopper->CreateFixture(&fd);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
