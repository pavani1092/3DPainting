/** 
 *  vslLinear.h
 *  This file defines interface to graphics linear operation classes for VSL
 *  
 *  Author: Daqing Xue
 *  Date: 7/16/2005
 */

/**
 * Interface to graphics linear operation classes
 * 
 *   Daqing Xue
 *   Department of Computer & Information Science
 *   The Ohio State University
 *   Apr. 2003
 *
 * Copyright (C) 2003 - 2005 Daqing Xue
 *
 * The source code can be freely used, redistributed, and modified for 
 * any purpose, provided that the above copyright information appears 
 * in all copies.
 */

#pragma once

#include <math.h>
#include <iostream>

#pragma warning( push )
#pragma warning( disable : 4201 ) // Nonstandard extension used : nameless struct/union

namespace Crawfis
{
	namespace Math
	{

		template <typename T> inline
		  bool is_zero ( T t, T epsilon = 0.0001f )
		{
		  return fabs(t) < epsilon;
		}


		/**
		 * 
		 *  2D vector template class
		 *
		 */

		template <typename T>
		class vec2
		{
		 public:
		  union {
			T _v[2];
			struct {
			  T x, y;
			};
			struct {
			  T u, v;
			};
			struct {
			  T s, t;
			};
		  };

		 public:
		  explicit vec2( const T & t = T() ) 
			{  _v[0] = t; _v[1] = t;  }
		  
		  explicit vec2( const T * t )
			{  _v[0] = t[0]; _v[1] = t[1];  }
		  
		  vec2( const vec2<T> & v ) 
			{  _v[0] = v[0]; _v[1] = v[1];  }

		  vec2( const T & x, const T & y )  
			{  _v[0] = x; _v[1] = y;  }

		  const T * getValue( T * t = NULL ) const
			{  if (t!=NULL) { t[0] = _v[0]; t[1] = _v[1];  }   return _v; }
		  
		  void setValue( const T * t )
			{  _v[0] = t[0]; _v[1] = t[1];  }

		  void getValue( T & x, T & y ) const
			{  x = _v[0]; y = _v[1];  }
		  
		  void setValue( const T & x, const T & y )
			{  _v[0] = x; _v[1] = y;  }

		  void reset( const T & t )
			{  _v[0] = t; _v[1] = t;  }

		  void zero()
			{  _v[0] = T(0); _v[1] = T(0);  }
		  
		  void negate()
			{  _v[0] = -_v[0]; _v[1] = -_v[1];  }
		  
		  bool isZero() const
			{  return is_zero(_v[0]) && is_zero(_v[1]);  }

		  bool agree( const vec2<T> & v) const
			{  return (*this - v).isZero();  }

		  T length() const
			{  return T(sqrt(length2()));  }	
		  
		  T length2() const
			{  return T(_v[0]*_v[0] + _v[1]*_v[1]);  }	

		  T distance(const vec2<T> & v) const
			{ return (*this-v).length();  }

		  T dot( const vec2<T> & v ) const
			{  return T(_v[0]*v[0] + _v[1]*v[1]);  }
		  
		  void normalize() 
			{ 
			  T l;
			  l = length();
			  if (l != T(0)) { T rl = T(1)/l; _v[0] *= rl; _v[1] *= rl;  }
			}
		  
		  void print() const
			{  std::cout << "[ " << _v[0] << " " << _v[1] << " ]\n";  }
		  
		  // operator functions
		  
		  T operator () ( int i ) const
			{ return _v[i]; }
		  
		  T & operator [] ( int i )
			{ return _v[i]; }
		  
		  const T & operator [] ( int i ) const
			{ return _v[i]; }

		  vec2<T> & operator = ( const vec2<T> & v )
			{ _v[0] = v[0];  _v[1] = v[1];    return (*this); }
		  
		  vec2<T> & operator += ( const vec2<T> & v )
			{ _v[0] += v[0];  _v[1] += v[1];  return (*this); }
		  
		  vec2<T> & operator -= ( const vec2<T> & v )
			{ _v[0] -= v[0];  _v[1] -= v[1];  return (*this); }
		  
		  vec2<T> & operator *= ( const vec2<T> & v )
			{ _v[0] *= v[0];  _v[1] *= v[1];  return (*this); }

		  vec2<T> & operator *= ( T t )
			{ _v[0] *= t;  _v[1] *= t;  return (*this); }

		  vec2<T> & operator /= ( T t )
			{ if (t != T(0)) { T rt = T(1)/t;  _v[0] *= rt; _v[1] *= rt; }  return (*this);  }
		  
		  vec2<T> operator + () const
			{ return vec2<T>(*this); }
		  
		  vec2<T> operator - () const
			{ vec2<T> rv(*this); rv.negate(); return rv; }
		  
		  vec2<T> operator + ( const vec2<T> &v ) const
			{ vec2<T> rv(*this); return rv += v; }
		  
		  vec2<T> operator - ( const vec2<T> &v ) const
			{ vec2<T> rv(*this); return rv -= v; }

		  vec2<T> operator * ( const vec2<T> &v ) const
			{ vec2<T> rv(*this); return rv *= v; }

		  vec2<T> operator * ( T t ) const
			{ vec2<T> rv(*this); return rv *= t; }
		  
		  vec2<T> operator / ( T t ) const
			{ vec2<T> rv(*this); return rv /= t; }

		  bool operator == ( const vec2<T> & v ) const
			{  return _v[0]==v[0] && _v[1]==v[1]; }

		  bool operator != ( const vec2<T> & v) const
			{  return !(*this == v);  }
		};

		// vec2<T> operator functions
				
		template <typename T> inline
		  vec2<T> operator * ( T t, const vec2<T> & v )
		{ 
		  return v*t; 
		}

		template <typename T> inline
		  T dot ( const vec2<T> & v, const vec2<T> & u )
		{
		  return v.dot(u);
		}

		template <typename T> inline
		  vec2<T> normalize ( const vec2<T> & v )
		{
		  vec2<T> rv(v);
		  rv.normalize();
		  return rv;
		}

		/**
		 * 
		 *  3D vector template class
		 *
		 */

		template <typename T>
		class vec3
		{
		 public:
		  union {
			T _v[3];
			struct {
			  T x, y, z;
			};
			struct {
			  T r, g, b;
			};
		  };

		 public:
		  explicit vec3( const T & t = T() ) 
			{  _v[0] = t; _v[1] = t;  _v[2] = t;  }
		  
		  explicit vec3( const T * t )
			{  _v[0] = t[0]; _v[1] = t[1];  _v[2] = t[2];  }

		  explicit vec3( const vec2<T> & v, const T t = T() ) 
			{  _v[0] = v[0]; _v[1] = v[1]; _v[2] = t;  }

		  vec3( const T & x, const T & y, const T & z )  
			{  _v[0] = x; _v[1] = y;  _v[2] = z;  }

		  vec3( const vec3<T> & v ) 
			{  _v[0] = v[0]; _v[1] = v[1]; _v[2] = v[2];  }

		  const T * getValue( T * t = NULL ) const
			{  if (t!=NULL) { t[0] = _v[0]; t[1] = _v[1]; t[2] = _v[2]; }   return _v; }
		  
		  void setValue( const T * t )
			{  _v[0] = t[0]; _v[1] = t[1]; _v[2] = t[2];  }

		  void getValue( T & x, T & y, T & z ) const
			{  x = _v[0]; y = _v[1]; z = _v[2];  }
		  
		  void setValue( const T & x, const T & y, const T & z )
			{  _v[0] = x; _v[1] = y; _v[2] = z;  }

		  void reset( const T & t )
			{  _v[0] = t; _v[1] = t; _v[2] = t;  }

		  void zero()
			{  _v[0] = T(0); _v[1] = T(0); _v[2] = T(0); }
		  
		  void negate()
			{  _v[0] = -_v[0]; _v[1] = -_v[1]; _v[2] = -_v[2];  }
		  
		  bool isZero() const
			{  return is_zero(_v[0]) && is_zero(_v[1]) && is_zero(_v[2]);  }

		  bool agree( const vec3<T> & v) const
			{  return (*this - v).isZero();  }

		  T length() const
			{  return T(sqrt(length2()));  }	
		  
		  T length2() const
			{  return T(_v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2]);  }	

		  T distance(const vec3<T> & v) const
			{ return (*this-v).length();  }

		  T dot( const vec3<T> & v ) const
			{  return T(_v[0]*v[0] + _v[1]*v[1] + _v[2]*v[2]);  }
		  
		  void normalize() 
			{ 
			  T l;
			  l = length();
			  if (l != T(0)) { T rl = T(1)/l; _v[0] *= rl; _v[1] *= rl; _v[2] *= rl; }
			}

		  vec3<T> cross(const vec3<T> & rhs ) const
			{
			  vec3<T> rv;
			  rv[0] = _v[1]*rhs[2] - _v[2]*rhs[1];
			  rv[1] = _v[2]*rhs[0] - _v[0]*rhs[2];
			  rv[2] = _v[0]*rhs[1] - _v[1]*rhs[0];	
			  return rv;
			}

		  void print() const
			{  std::cout << "[ " << _v[0] << " " << _v[1] <<" " << _v[2] << " ]\n";  }
		  
		  // operator functions
		  
		  T operator () ( int i ) const
			{ return _v[i]; }
		  
		  T & operator [] ( int i )
			{ return _v[i]; }
		  
		  const T & operator [] ( int i ) const
			{ return _v[i]; }

		  vec3<T> & operator = ( const vec3<T> & v )
			{ _v[0] = v[0];  _v[1] = v[1];  _v[2] = v[2];     return (*this); }
		  
		  vec3<T> & operator += ( const vec3<T> & v )
			{ _v[0] += v[0];  _v[1] += v[1];  _v[2] += v[2];  return (*this); }
		  
		  vec3<T> & operator -= ( const vec3<T> & v )
			{ _v[0] -= v[0];  _v[1] -= v[1];  _v[2] -= v[2];  return (*this); }
		  
		  vec3<T> & operator *= ( const vec3<T> & v )
			{ _v[0] *= v[0];  _v[1] *= v[1];  _v[2] *= v[2];  return (*this); }

		  vec3<T> & operator *= ( T t )
			{ _v[0] *= t;  _v[1] *= t;  _v[2] *= t;  return (*this); }
		  
		  vec3<T> & operator /= ( T t )
			{
			  if (t != T(0)) { T rt = T(1)/t; _v[0] *= rt; _v[1] *= rt; _v[2] *= rt; }
			  return (*this);
			}
		  
		  vec3<T> operator + () const
			{ return vec3<T>(*this); }
		  
		  vec3<T> operator - () const
			{ vec3<T> rv(*this); rv.negate(); return rv; }
		  
		  vec3<T> operator + ( const vec3<T> &v ) const
			{ vec3<T> rv(*this); return rv += v; }
		  
		  vec3<T> operator - ( const vec3<T> &v ) const
			{ vec3<T> rv(*this); return rv -= v; }

		  vec3<T> operator * ( const vec3<T> &v ) const
			{ vec3<T> rv(*this); return rv *= v; }

		  vec3<T> operator * ( T t ) const
			{ vec3<T> rv(*this); return rv *= t; }
		  
		  vec3<T> operator / ( T t ) const
			{ vec3<T> rv(*this); return rv /= t; }

		  bool operator == ( const vec3<T> & v ) const
			{  return _v[0]==v[0] && _v[1]==v[1] && _v[2]==v[2]; }

		  bool operator != ( const vec3<T> & v) const
			{  return !(*this == v);  }
		};

		// vec3<T> operator functions
				
		template <typename T> inline
		  vec3<T> operator * ( T t, const vec3<T> & v )
		{ 
		  return v*t; 
		}
		template <typename T> inline
		  T dot ( const vec3<T> & v, const vec3<T> & u )
		{
		  return v.dot(u);
		}

		template <typename T> inline
		  vec3<T> normalize ( const vec3<T> & v )
		{
		  vec3<T> rv(v);
		  rv.normalize();
		  return rv;
		}

		template <typename T> inline
		  vec3<T> cross ( const vec3<T> & lhs, const vec3<T> rhs )
		{
		  return lhs.cross(rhs);
		}

		/**
		 * 
		 *  4D vector template class
		 *
		 */

		template <typename T>
		class vec4
		{
		 public:
		  union {
			T _v[4];
			struct {
			  T x, y, z, w;
			};
			struct {
			  T r, g, b, a;
			};
		  };

		 public:
		  explicit vec4( const T & t = T() ) 
			{  _v[0] = t; _v[1] = t; _v[2] = t; _v[3] = t;  }
		  
		  explicit vec4( const T * t )
			{  _v[0] = t[0]; _v[1] = t[1]; _v[2] = t[2]; _v[3] = t[3];  }

		  explicit vec4( const vec3<T> & v, const T t = T() ) 
			{  _v[0] = v[0]; _v[1] = v[1]; _v[2] = v[2]; _v[3] = t;  }

		  vec4( const T & x, const T & y, const T & z, const T & w )  
			{  _v[0] = x; _v[1] = y; _v[2] = z; _v[3] = w;  }

		  vec4( const vec4<T> & v ) 
			{  _v[0] = v[0]; _v[1] = v[1]; _v[2] = v[2]; _v[3] = v[3];  }

		  const T * getValue( T * t = NULL ) const
			{  
			  if (t!=NULL) { t[0] = _v[0]; t[1] = _v[1]; t[2] = _v[2]; t[3] = _v[3]; }
			  return _v; 
			}
		  
		  void setValue( const T * t )
			{  _v[0] = t[0]; _v[1] = t[1]; _v[2] = t[2]; _v[3] = t[3];  }

		  void getValue( T & x, T & y, T & z, T & w ) const
			{  x = _v[0]; y = _v[1]; z = _v[2]; w = _v[3];  }
		  
		  void setValue( const T & x, const T & y, const T & z, const T & w )
			{  _v[0] = x; _v[1] = y; _v[2] = z; _v[3] = w;  }

		  void reset( const T & t )
			{  _v[0] = t; _v[1] = t; _v[2] = t; _v[3] = t;  }

		  void zero()
			{  _v[0] = T(0); _v[1] = T(0); _v[2] = T(0); _v[3] = T(0);  }
		  
		  void negate()
			{  _v[0] = -_v[0]; _v[1] = -_v[1]; _v[2] = -_v[2]; _v[3] = -_v[3];  }
		  
		  bool isZero() const
			{  return is_zero(_v[0]) && is_zero(_v[1]) && is_zero(_v[2]) && is_zero(_v[3]);  }

		  bool agree( const vec4<T> & v) const
			{  return (*this - v).isZero();  }
		  
		  T length() const
			{  return T(sqrt(length2()));  }	
		  
		  T length2() const
			{  return T(_v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] + _v[3]*_v[3]);  }	

		  T distance(const vec4<T> & v) const
			{ return (*this-v).length();  }

		  T dot( const vec4<T> & v ) const
			{  return T(_v[0]*v[0] + _v[1]*v[1] + _v[2]*v[2] + _v[3]*v[3]);  }
		  
		  void normalize() 
			{ 
			  T l;
			  l = length();
			  if (l != T(0)) { T rl = T(1)/l; _v[0] *= rl; _v[1] *= rl; _v[2] *= rl; _v[3] *= rl; }
			}
		  void homogenize()
			{  
			  if (_v[3] != T(0)) { T r = T(1)/_v[3]; _v[0] *= r; _v[1] *= r; _v[2] *= r; }
			  _v[3] = 1.0; 
			}

		  void print() const
			{  std::cout << "[ " << _v[0] << " " << _v[1] <<" " << _v[2] << " " << _v[3] << " ]\n";  }
		  
		  // operator functions
		  
		  T operator () ( int i ) const
			{ return _v[i]; }
		  
		  T & operator [] ( int i )
			{ return _v[i]; }
		  
		  const T & operator [] ( int i ) const
			{ return _v[i]; }

		  vec4<T> & operator = ( const vec4<T> & v )
			{ _v[0] = v[0];  _v[1] = v[1];  _v[2] = v[2];  _v[3] = v[3];      return (*this); }
		  
		  vec4<T> & operator += ( const vec4<T> & v )
			{ _v[0] += v[0];  _v[1] += v[1];  _v[2] += v[2];  _v[3] += v[3];  return (*this); }
		  
		  vec4<T> & operator -= ( const vec4<T> & v )
			{ _v[0] -= v[0];  _v[1] -= v[1];  _v[2] -= v[2];  _v[3] -= v[3];  return (*this); }
		  
		  vec4<T> & operator *= ( const vec4<T> & v )
			{ _v[0] *= v[0];  _v[1] *= v[1];  _v[2] *= v[2];  _v[3] *= v[3];  return (*this); }

		  vec4<T> & operator *= ( T t )
			{ _v[0] *= t;  _v[1] *= t;  _v[2] *= t;  _v[3] *= t;  return (*this); }
		  
		  vec4<T> & operator /= ( T t )
			{
			  if (t != T(0)) { T rt = T(1)/t; _v[0] *= rt; _v[1] *= rt; _v[2] *= rt; _v[3] *= rt; }
			  return (*this);
			}
		  
		  vec4<T> operator + () const
			{ return vec4<T>(*this); }
		  
		  vec4<T> operator - () const
			{ vec4<T> rv(*this); rv.negate(); return rv; }
		  
		  vec4<T> operator + ( const vec4<T> &v ) const
			{ vec4<T> rv(*this); return rv += v; }
		  
		  vec4<T> operator - ( const vec4<T> &v ) const
			{ vec4<T> rv(*this); return rv -= v; }

		  vec4<T> operator * ( const vec4<T> &v ) const
			{ vec4<T> rv(*this); return rv *= v; }

		  vec4<T> operator * ( T t ) const
			{ vec4<T> rv(*this); return rv *= t; }
		  
		  vec4<T> operator / ( T t ) const
			{ vec4<T> rv(*this); return rv /= t; }

		  bool operator == ( const vec4<T> & v ) const
			{  return _v[0]==v[0] && _v[1]==v[1] && _v[2]==v[2] && _v[3]==v[3]; }

		  bool operator != ( const vec4<T> & v) const
			{  return !(*this == v);  }
		};

		// vec4<T> operator functions
				
		template <typename T> inline
		  vec4<T> operator * ( T t, const vec4<T> & v )
		{ 
		  return v*t; 
		}
		template <typename T> inline
		  T dot ( const vec4<T> & v, const vec4<T> & u )
		{
		  return v.dot(u);
		}

		template <typename T> inline
		  vec4<T> normalize ( const vec4<T> & v )
		{
		  vec4<T> rv(v);
		  rv.normalize();
		  return rv;
		}

		template <typename T> inline
		  vec4<T> cross ( const vec4<T> & lhs, const vec4<T> rhs )
		{
		  return lhs.cross(rhs);
		}

		template <typename T> inline
		  vec3<T> homogenize ( const vec4<T> & v )
		{
		  vec4<T> rv(v);
		  rv.homogenize();
		  return vec3<T>(&rv[0]);
		}

		typedef vec2<float> Vector2;
		typedef vec3<float> Vector3;
		typedef vec4<float> Vector4;

		typedef vec2<float> Vector2f;
		typedef vec3<float> Vector3f;
		typedef vec4<float> Vector4f;
		typedef vec2<double> Vector2d;
		typedef vec3<double> Vector3d;
		typedef vec4<double> Vector4d;
	}
}

#pragma warning( pop )