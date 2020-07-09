#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <math.h>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image& im)
  {
  assert(im.c == 3); // only accept RGB images
  Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)
  
  // TODO: calculate the pixels of 'gray'
  for (int i = 0; i < im.w; i++)
  {
      for (int j = 0; j < im.h; j++)
      {
          //int address = pixel_address(im, i, j, 0);
          //gray.data[address] = 0.299*im(i,j,0)+0.587*im(i,j,1)+0.114*im(i,j,2);
          gray(i,j,0)= 0.299 * im(i, j, 0) + 0.587 * im(i, j, 1) + 0.114 * im(i, j, 2);
          
      }
  }
  
  //NOT_IMPLEMENTED();
  
  return gray;
  }



// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image& im, float r, float g, float b)
  {
  assert(im.c == 1);
  Image rgb(im.w,im.h,3);
  
  for(int q2=0;q2<im.h;q2++)for(int q1=0;q1<im.w;q1++)
    {
    rgb(q1,q2,0)=r*im(q1,q2);
    rgb(q1,q2,1)=g*im(q1,q2);
    rgb(q1,q2,2)=b*im(q1,q2);
    }
  
  return rgb;
  }




// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image& im, int c, float v)
  {
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  // TODO: shift all the pixels at the specified channel
  for (int i = 0; i < im.w; i++)for (int j = 0; j < im.h; j++)
  {
      im(i, j, c) += v ;
  }
  //NOT_IMPLEMENTED();
  
  }

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image& im, int c, float v)
{
    assert(c >= 0 && c < im.c); // needs to be a valid channel

    // TODO: scale all the pixels at the specified channel
    for (int i = 0; i < im.w; i++)for (int j = 0; j < im.h; j++)
    {
        im(i, j, c) = (1+v)* im(i, j, c);
    }
    //NOT_IMPLEMENTED();
}


// HW0 #5
// Image& im: input image to be modified in-place
  void clamp_image(Image & im)
  {
  // TODO: clamp all the pixels in all channel to be between 0 and 1
    for (int i = 0; i < im.w; i++)for (int j = 0; j < im.h; j++)for (int k = 0; k < im.c; k++)
    {
        float a = 0, b = 1;
        im(i, j, k) = max(im(i, j, k), a);
        im(i, j, k) = min(im(i, j, k), b);
    }
  //NOT_IMPLEMENTED();
  
  }

// These might be handy
float max(float a, float b, float c)
  {
  return max({a,b,c});
  }

float min(float a, float b, float c)
  {
  return min({a,b,c});
  }


// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from RGB format to HSV format
  float R, G, B, V, m, C, S, H0, H;
  for (int i = 0; i < im.w; i++)for (int j = 0; j < im.h; j++)
  {
      R = im(i, j, 0);
      G = im(i, j, 1);
      B = im(i, j, 2);
      if (R* G* B == 0 && R + G + B == 0)
      {

      }
      else
      {
          V = max(R, G, B);
          m = min(R, G, B);
          C = V - m;
          S = C / V;

          if (C == 0)
          {
              H0 = 0;
          }
          else
          {
              if (V == R)
              {
                  H0 = (G - B) / C;
              }
              else if (V == G)
              {
                  H0 = (B - R) / C + 2;
              }
              else if (V == B)
              {
                  H0 = (R - G) / C + 4;
              }
          }

          if (H0 < 0)
          {
              H = H0 / 6 + 1;
          }
          else
          {
              H = H0 / 6;
          }

          im(i, j, 0)=H;
          im(i, j, 1)=S;
          im(i, j, 2)=V;

      }
  }
 
  //NOT_IMPLEMENTED();
  
  }

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from HSV format to RGB format
  float R, G, B, V, m, C, S, X, H;
  for (int i = 0; i < im.w; i++)for (int j = 0; j < im.h; j++)
  {
      H = im(i, j, 0);
      S = im(i, j, 1);
      V = im(i, j, 2);

      C = V * S;
      X = C * (1 - abs(fmod(6 * H, 2) - 1));
      m = V - C;
      
      float a = 0.166667;
      if (0<=H && H < a)
      {
          R = C;
          G = X;
          B = 0;
      }
      else if (H < 2 * a) 
      {
          R = X;
          G = C;
          B = 0;
      }
      else if (H < 3 * a) 
      {
          R = 0;
          G = C;
          B = X;
      }
      else if (H < 4 * a) 
      {
          R = 0;
          G = X;
          B = C;
      }
      else if (H < 5 * a) 
      {
          R = X;
          G = 0;
          B = C;
      }
      else 
      {
          R = C;
          G = 0;
          B = X;
      }
   
      im(i, j, 0) = R + m;
      im(i, j, 1) = G + m;
      im(i, j, 2) = B + m;
   
  }
  //NOT_IMPLEMENTED();
  
  }

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
{
    assert(im.c == 3 && "only works for 3-channels images");

    // TODO: Convert all pixels from RGB format to LCH format
    float R, G, B, RL, GL, BL, X, Y, Z, L, U, V, u, v, Xn, Yn, Zn, un, vn, C, H;
    for (int i = 0; i < im.w; i++)for (int j = 0; j < im.h; j++)
    {
        R = im(i, j, 0);
        G = im(i, j, 1);
        B = im(i, j, 2);
        //RGB to CIEXYZ
        if (R <= 0.04045)
        {
            RL = R / 12.92;
        }
        else
        {
            RL = pow(( R + 0.055) / 1.055, 2.4);
        }

        if (G <= 0.04045)
        {
            GL = G / 12.92;
        }
        else
        {
            GL = pow((G + 0.055) / 1.055, 2.4);
        }

        if (B <= 0.04045)
        {
            BL = B / 12.92;
        }
        else
        {
            BL = pow((B + 0.055) / 1.055, 2.4);
        }
        
        X = 0.4124 * RL + 0.3576 * GL + 0.1805 * BL;
        Y = 0.2126 * RL + 0.7152 * GL + 0.0722 * BL;
        Z = 0.0193 * RL + 0.1192 * GL + 0.9505 * BL;

        //XYZ to LUV
        //The D65 standard illumiant
        float Xn = 0.9505;
        float Yn = 1.0;
        float Zn = 1.0890;
        if (X + 15 * Y + 3 * Z == 0)
        {
            L = 0;
            U = 0;
            V = 0;
        }

        if (X + 15 * Y + 3 * Z != 0)
        {
            if (Y / Yn <= pow(6 / 29.0, 3.0))
            {
                L = pow(29 / 3.0, 3.0) * Y / Yn;
            }
            else
            {
                L = 116 * pow(Y / Yn, 1 / 3.0) - 16;
            }
            u = 4 * X / (X + 15 * Y + 3 * Z);
            v = 9 * Y / (X + 15 * Y + 3 * Z);
            un = 4 * Xn / (Xn + 15 * Yn + 3 * Zn);
            vn = 9 * Yn / (Xn + 15 * Yn + 3 * Zn);
            U = 13 * L * (u - un);
            V = 13 * L * (v - vn);
        }
        
        //LUV to HCL
        C = sqrt(U * U + V * V);
        H = atan2(V, U);
       
        im(i, j, 0) = H;
        im(i, j, 1) = C;
        im(i, j, 2) = L;
    }
    //NOT_IMPLEMENTED();
}


// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
{
    assert(im.c == 3 && "only works for 3-channels images");

    // TODO: Convert all pixels from LCH format to RGB format
    float R, G, B, RL, GL, BL, X, Y, Z, L, U, V, u, v, Xn, Yn, Zn, un, vn, C, H;
    for (int i = 0; i < im.w; i++)for (int j = 0; j < im.h; j++)
    {
        H = im(i, j, 0);
        C = im(i, j, 1);
        L = im(i, j, 2);
        //HLC to LUV
        U = C * cos(H);
        V = C * sin(H);
        //LUV to XYZ
        //The D65 standard illumiant
        float Xn = 0.9505;
        float Yn = 1.0;
        float Zn = 1.0890;
        if (L == 0)
        {
            Y = 0;
            X = 0;
            Z = 0;
        }

        if (L != 0)
        {
            if (L <= 8)
            {
                Y = Yn * L * pow(3 / 29.0, 3.0);
            }
            else
            {
                Y = Yn * pow((L + 16.0) / 116.0, 3.0);
            }
            un = 4 * Xn / (Xn + 15 * Yn + 3 * Zn);
            vn = 9 * Yn / (Xn + 15 * Yn + 3 * Zn);
            u = U / 13 / L + un;
            v = V / 13 / L + vn;
            X = Y * 9 * u / 4 / v;
            Z = Y * (12 - 3 * u - 20 * v) / 4 / v;
        }
        
        //XYZ to RGB
        RL = 3.2406 * X - 1.5372 * Y - 0.4986 * Z;
        GL = -0.9689 * X + 1.8758 * Y + 0.0415 * Z;
        BL = 0.0557 * X - 0.2040 * Y + 1.0570 * Z;
        
        if (RL <= 0.0031308)
        {
            R = 12.92 * RL;
        }
        else
        {
            R = 1.055 * pow(RL, 0.416) - 0.055;
        }

        if (GL <= 0.0031308)
        {
            G = 12.92 * GL;
        }
        else
        {
            G = 1.055 * pow(GL, 0.416) - 0.055;
        }

        if (BL <= 0.0031308)
        {
            B = 12.92 * BL;
        }
        else
        {
            B = 1.055 * pow(BL, 0.416) - 0.055;
        }
        im(i, j, 0) = R;
        im(i, j, 1) = G;
        im(i, j, 2) = B;

    }
}



// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this,c,v); }
void Image::scale(int c, float v) { scale_image(*this,c,v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
