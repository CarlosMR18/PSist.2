
#include "commonstuff.h"
#include "Ball.h"
#include "ObjectsList.h"
#include <typeinfo>

// Forward declarations
class Man;
class Bullet;


Ball::Ball(int t)
{
  float tmp;

  size = BIG;
  type = t;

  pos[X] = RAND_DOM(0,SIZEX);
  pos[Y] = RAND_DOM(0,SIZEY);
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = 0;
  rot[Y] = 0;

  rspeed[X] = RAND_FRAC()*0.5;
  rspeed[Y] = RAND_FRAC()*0.5;
  rspeed[Z] = RAND_FRAC()*0.5;

  tmp = 2*(RAND_FRAC()-0.5);
  tspeed[X] = tmp*BALL_SPEED;
  //   tmp = 2*(RAND_FRAC()-0.5);
  //  tspeed[Y] = tmp*BALL_SPEED;
  tspeed[Y] = 0;
  tspeed[Z] = 0;

  color[R] = 0.9;
  color[G] = 0.2*t;
  color[B] = 0.1*t;

  acc_ratio = 0.001;

  //  printf("Mi no is %d",mynumber);
}


Ball::Ball(int t, int s, float px, float py)
{
  float tmp;

  size = s;
  type = t;

  pos[X] = px;
  pos[Y] = py;
  pos[Z] = 0;

  rot[Z] = 0;
  rot[X] = 0;
  rot[Y] = 0;

  rspeed[X] = RAND_FRAC()*0.5;
  rspeed[Y] = RAND_FRAC()*0.5;
  rspeed[Z] = RAND_FRAC()*0.5;

  tmp = 2*(RAND_FRAC()-0.5);
  tspeed[X] = tmp*BALL_SPEED;
  //tmp = 2*(RAND_FRAC()-0.5);
  //tspeed[Y] = tmp*BALL_SPEED;
  tspeed[Y] = 0;
   tspeed[Z] = 0;

  color[R] = 0.9;
  color[G] = 0.2;
  color[B] = 0.1;

    acc_ratio = 0.001;

}


void Ball::draw()
{
  predraw();
  glutSolidSphere(size*0.3,9,8);

  // printf("Drawing ball %gm %g\n",pos[X],pos[Y]);
  
  postdraw();
}
 

Ball *Ball::split()
{
  Ball *tmp;

  tmp = new Ball(1,size-1,pos[X],pos[Y]);
  size--;

  return tmp;
}
 
float Ball::getSize()
{
  return (0.3*size);
}

void Ball::reposition()
{
  pos[X] += 1+3*RAND_FRAC();
  pos[Y] += 1+3*RAND_FRAC();

}

float Ball::operator+(Shape* other)
{
  float pos1[3],pos2[3], size1,size2;
  nodo  *p1=NULL;
  Man *theMan;
  Bullet *theBullet;
  
  int res=0;

  theMan = dynamic_cast<Man*>(other);
  
  if(theMan)
    {
      this->getPos(pos1);
      size1 = this->getSize();
      theMan->getPos(pos2);
      size2 = theMan->getSize();
      
      return(mydistance(pos1[X],pos1[Y],pos2[X],pos2[Y]));
    }

  
  theBullet = dynamic_cast<Bullet*>(other);
  
  if(theBullet)
    {
      this->getPos(pos1);
      size1 = this->getSize();
      theBullet->getPos(pos2);
      size2 = theBullet->getSize();

      return(mydistance(pos1[X],pos1[Y],pos2[X],pos2[Y]));
      
    }
  
  return 10000.0;
}
