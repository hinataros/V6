/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"

RLS::Quaternion4d RLS::Quaternion4d::operator=(RLS::Quaternion4d q)
{
  w = q.w;
  v = q.v;

  return *this;
}

RLS::Quaternion4d RLS::Quaternion4d::operator+(RLS::Quaternion4d q)
{
  w += q.w;
  v += q.v;

  return *this;
}

RLS::Quaternion4d RLS::Quaternion4d::operator-(RLS::Quaternion4d q)
{
  w -= q.w;
  v -= q.v;

  return *this;
}

RLS::Quaternion4d RLS::Quaternion4d::operator*(RLS::Quaternion4d q)
{
  Quaternion4d re = Zero();

  re.w = w*q.w - v.dot(q.v);
  re.v = w*q.v + q.w*v - v.cross(q.v);

  return re;
}

RLS::Quaternion4d RLS::Quaternion4d::operator*=(RLS::Quaternion4d q)
{
  *this = *this*q;

  return *this;
}

RLS::Quaternion4d RLS::Quaternion4d::operator/(RLS::Quaternion4d q)
{
  Quaternion4d re = Zero();

  re.w = q.w;
  re.v = -q.v; //共役

  *this *= re;

  return *this;
}

RLS::Quaternion4d RLS::Quaternion4d::operator/=(RLS::Quaternion4d q)
{
  *this = *this/q;

  return *this;
}
