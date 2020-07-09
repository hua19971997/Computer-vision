#include <cmath>
#include "image.h"

using namespace std;

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neibor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const
  { 
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)
  
  // TODO: Your code here
    float x_new = (int) x;
    float y_new = (int) y;

    if (fabs(x - x_new) >= fabs(x - x_new - 1))
    {
        if (fabs(y - y_new) >= fabs(y - y_new - 1))
        {
            return  clamped_pixel((int)x_new + 1, (int)y_new + 1, c);
        }
        else
        {
            return  clamped_pixel((int)x_new + 1, (int)y_new, c);
        }
    }
    else
    {
        if (fabs(y - y_new) >= fabs(y - y_new - 1))
        {
            return  clamped_pixel((int)x_new, (int)y_new + 1, c);
        }
        else
        {
            return  clamped_pixel((int)x_new, (int)y_new, c);
        }
    }
  }

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the bilinearly interpolated pixel (x,y,c)
float Image::pixel_bilinear(float x, float y, int c) const
{
    // Since you are inside class Image you can
    // use the member function pixel(a,b,c)
    // TODO: Your code here
        float A4 = fabs((x - floor(x)) * (y - floor(y)));
        float A3 = fabs((ceil(x) - x) * (y - floor(y)));
        float A2 = fabs((x - floor(x)) * (ceil(y) - y));
        float A1 = fabs((ceil(x) - x) * (ceil(y) - y));
        float V1 = clamped_pixel(floor(x), floor(y), c);
        float V2 = clamped_pixel(ceil(x), floor(y), c);
        float V3 = clamped_pixel(floor(x), ceil(y), c);
        float V4 = clamped_pixel(ceil(x), ceil(y), c);
        return  A4 * V4 + A3 * V3 + A2 * V2 + A1 * V1;

}

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image& im, int w, int h)
{
    Image ret(w, h, im.c);

    // TODO: Your code here
    float x_scale = (float) w / (float) im.w;
    float y_scale = (float) h / (float) im.h;
    for (float i = 0; i < w; i++)
    {
        for (float j = 0; j < h; j++)
        {
            for (float k = 0; k < im.c; k++)
            {
                ret(i, j, k) = im.pixel_nearest(-0.5 + ((i + 0.5) / x_scale), -0.5 + ((j + 0.5) / y_scale), k);
            }
        }
    }
    return ret;
}


// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image bilinear_resize(const Image& im, int w, int h)
  {
  
  // TODO: Your code here
  
  NOT_IMPLEMENTED();
  Image image(w, h, im.c);
  float x_scale = (float)w / (float)im.w;
  float y_scale = (float)h / (float)im.h;
  for (float i = 0; i < w; i++)
  {
      for (float j = 0; j < h; j++)
      {
          for (float k = 0; k < im.c; k++)
          {
              image(i, j, k) = im.pixel_bilinear(-0.5 + ((i + 0.5) / x_scale), -0.5 + ((j + 0.5) / y_scale), k);
          }
      }
  }
 
  
  return image;
  }


