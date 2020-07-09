#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"

#define M_PI 3.14159265358979323846

// HW1 #2.1
// Image& im: image to L1-normalize
void l1_normalize(Image& im)
  {
  
  // TODO: Normalize each channel
    
    float sum = 0;
    for (int i = 0; i < im.w; i++)
    {
        for (int j = 0; j < im.h; j++)
        {
            for (int k = 0; k < im.c; k++)
            {
                sum += im.clamped_pixel(i, j, k);
            }
        }
    }
    //if (sum == 0)
    //{
    //    sum = 1;
    //}

    for (int i = 0; i < im.w; i++)
    {
        for (int j = 0; j < im.h; j++)
        {
            for (int k = 0; k < im.c; k++)
            {
                im.set_pixel(i, j, k, im.clamped_pixel(i, j, k) / sum);
            }
        }
    }
  
  
  }

// HW1 #2.1
// int w: size of filter
// returns the filter Image of size WxW
Image make_box_filter(int w)
  {
  assert(w%2); // w needs to be odd
  
  // TODO: Implement the filter
  Image box_filter(w, w, 1);
  for (int j = 0; j < w; j++)
  {
      for (int i = 0; i < w; i++)
      {
          box_filter.set_pixel(i, j, 0, 1);
      }
  }
  l1_normalize(box_filter);
  
  return box_filter;
  }

// HW1 #2.2
// const Image&im: input image
// const Image& filter: filter to convolve with
// bool preserve: whether to preserve number of channels
// returns the convolved image
Image convolve_image(const Image& im, const Image& filter, bool preserve)
  {
  assert(filter.c==1);
  Image ret;
  // This is the case when we need to use the function clamped_pixel(x,y,c).
  // Otherwise you'll have to manually check whether the filter goes out of bounds
  
  // TODO: Make sure you set the sizes of ret properly. Use ret=Image(w,h,c) to reset ret
  // TODO: Do the convolution operator
  ret = Image(im.w, im.h, im.c);
  float q=0;
  for (int i = 0; i < im.w; i++)
  {
      for (int j = 0; j < im.h; j++)
      {
          for (int k = 0; k < im.c; k++)
          {
              for (int l = 0; l < filter.w; l++)
              {
                  for (int m = 0; m < filter.w; m++)
                  {

                      q += filter.clamped_pixel(l, m, 0) * im.clamped_pixel(i - ((filter.w + 1) / 2 - l - 1), j - ((filter.w + 1) / 2 - m - 1), k);
                  }
              }

              ret.set_pixel(i, j, k, q);
              q = 0;
          }
      }
  }
  
  // Make sure to return ret and not im. This is just a placeholder
 
  if (preserve)
  {
      return ret;
  }
  else
  {
      Image ret1(im.w, im.h, 1);
      for (float j = 0; j < im.h; j++)
      {
          for (float i = 0; i < im.w; i++)
          {
              for (int k = 0; k < im.c; k++)
              {
                  ret1(i, j, 0) += ret(i, j, k);
              }
              
          }
      }
      return ret1;
  }

  }

// HW1 #2.3
// returns basic 3x3 high-pass filter
Image make_highpass_filter()
  {
  // TODO: Implement the filter
  Image highpass_filter(3, 3, 1);
  for (int j = 0; j < 3; j++)
  {
      for (int i = 0; i < 3; i++)
      {
          highpass_filter.set_pixel(i, j, 0, 0);
      }
  }
  highpass_filter.set_pixel(0, 1, 0, -1);
  highpass_filter.set_pixel(1, 0, 0, -1);
  highpass_filter.set_pixel(1, 1, 0, 4);
  highpass_filter.set_pixel(1, 2, 0, -1);
  highpass_filter.set_pixel(2, 1, 0, -1);
  
  //l1_normalize(highpass_filter);

  return highpass_filter;
  
  }

// HW1 #2.3
// returns basic 3x3 sharpen filter
Image make_sharpen_filter()
  {
  // TODO: Implement the filter
    Image harpen_filter(3, 3, 1);
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            harpen_filter.set_pixel(i, j, 0, 0);
        }
    }
    harpen_filter.set_pixel(0, 1, 0, -1);
    harpen_filter.set_pixel(1, 0, 0, -1);
    harpen_filter.set_pixel(1, 1, 0, 5);
    harpen_filter.set_pixel(1, 2, 0, -1);
    harpen_filter.set_pixel(2, 1, 0, -1);

    //l1_normalize(highpass_filter);

    return harpen_filter;
  }

// HW1 #2.3
// returns basic 3x3 emboss filter
Image make_emboss_filter()
  {
  // TODO: Implement the filter
    Image emboss_filter(3, 3, 1);
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            emboss_filter.set_pixel(i, j, 0, 0);
        }
    }
    emboss_filter.set_pixel(0, 0, 0, -2);
    emboss_filter.set_pixel(0, 1, 0, -1);
    emboss_filter.set_pixel(1, 0, 0, -1);
    emboss_filter.set_pixel(1, 1, 0, 1);
    emboss_filter.set_pixel(1, 2, 0, 1);
    emboss_filter.set_pixel(2, 1, 0, 1);
    emboss_filter.set_pixel(2, 2, 0, 2);

    //l1_normalize(highpass_filter);
    return emboss_filter;
  
  }

// HW1 #2.4
// float sigma: sigma for the gaussian filter
// returns basic gaussian filter
Image make_gaussian_filter(float sigma)
  {
  // TODO: Implement the filter
    int  w = 0;
    float q;
    if (((int)(6 * sigma))%2==0)
    {
        w = (int)(6 * sigma) + 1;
    }
    else
    {
        w = (int)(6 * sigma);
    }

    Image gaussian_filter(w, w, 1);
    for (int j = 0; j < w; j++)
    {
        for (int i = 0; i < w; i++)
        {
            int x = i - (w - 1) / 2;
            int y = j - (w - 1) / 2;
            q = exp(-(pow(x, 2) + pow(y, 2)) / (2 * sigma*sigma)) / (2*M_PI * pow(sigma, 2));
            gaussian_filter.set_pixel(i, j, 0, q);
        }
    }
    l1_normalize(gaussian_filter);
    return gaussian_filter;
  }


// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their sum
Image add_image(const Image& a, const Image& b)
  {
  assert(a.w==b.w && a.h==b.h && a.c==b.c); // assure images are the same size
  
  // TODO: Implement addition
  Image add(a.w, a.h, a.c);
  for (float i = 0; i < a.w; i++)
  {
      for (float j = 0; j < a.h; j++)
      {
          for (float k = 0; k < a.c; k++)
          {
              add(i, j, k) = a(i, j, k) + b(i, j, k);
          }
      }
  }
  return add;
  }

// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their difference res=a-b
Image sub_image(const Image& a, const Image& b)
  {
  assert(a.w==b.w && a.h==b.h && a.c==b.c); // assure images are the same size
  
  // TODO: Implement subtraction
  Image sub(a.w, a.h, a.c);
  for (float i = 0; i < a.w; i++)
  {
      for (float j = 0; j < a.h; j++)
      {
          for (float k = 0; k < a.c; k++)
          {
              sub(i, j, k) = a(i, j, k) - b(i, j, k);
          }
      }
  }
  return sub;
  }

// HW1 #4.1
// returns basic GX filter
Image make_gx_filter()
  {
  // TODO: Implement the filter
    Image gx_filter(3, 3, 1);
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            gx_filter.set_pixel(i, j, 0, 0);
        }
    }

    gx_filter.set_pixel(0, 0, 0, -1);
    gx_filter.set_pixel(2, 0, 0, 1);
    gx_filter.set_pixel(0, 1, 0, -2);
    gx_filter.set_pixel(2, 1, 0, 2);
    gx_filter.set_pixel(0, 2, 0, -1);
    gx_filter.set_pixel(2, 2, 0, 1);
    return gx_filter;
  }

// HW1 #4.1
// returns basic GY filter
Image make_gy_filter()
  {
  // TODO: Implement the filter
    Image gy_filter(3, 3, 1);
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            gy_filter.set_pixel(i, j, 0, 0);
        }
    }
    gy_filter.set_pixel(0, 0, 0, -1);
    gy_filter.set_pixel(1, 0, 0, -2);
    gy_filter.set_pixel(2, 0, 0, -1);
    gy_filter.set_pixel(0, 2, 0, 1);
    gy_filter.set_pixel(1, 2, 0, 2);
    gy_filter.set_pixel(2, 2, 0, 1);
    return gy_filter;
  }

// HW1 #4.2
// Image& im: input image
void feature_normalize(Image& im)
{
    assert(im.w * im.h); // assure we have non-empty image

    // TODO: Normalize the features for each channel
    float min = im(0, 0, 0);
    float max = 0;
    for (float i = 0; i < im.w; i++)
    {
        for (float j = 0; j < im.h; j++)
        {
            for (float k = 0; k < im.c; k++)
            {
                if (im(i, j, k) < min)
                {
                    min = im(i, j, k);
                }
                if (im(i, j, k) > max)
                {
                    max = im(i, j, k);
                }
            }
        }
    }

    float range = max - min;
    if (range != 0)
    {
        for (float i = 0; i < im.w; i++)
        {
            for (float j = 0; j < im.h; j++)
            {
                for (float k = 0; k < im.c; k++)
                {
                    im(i, j, k) = (im(i, j, k) - min) / range;
                }
            }
        }
    }
    else
    {
        for (float i = 0; i < im.w; i++)
        {
            for (float j = 0; j < im.h; j++)
            {
                for (float k = 0; k < im.c; k++)
                {
                    im(i, j, k) = 0;
                }
            }
        }
    }
}


// Normalizes features across all channels
void feature_normalize_total(Image& im)
  {
  assert(im.w*im.h*im.c); // assure we have non-empty image
  
  int nc=im.c;
  im.c=1;im.w*=nc;
  
  feature_normalize(im);
  
  im.w/=nc;im.c=nc;
  
  }


// HW1 #4.3
// Image& im: input image
// return a pair of images of the same size
pair<Image, Image> sobel_image(const Image& im)
{
     //TODO: Your code here
    Image fx = make_gx_filter();
    Image fy = make_gy_filter();
    Image Gx = convolve_image(im, fx, 0);
    Image Gy = convolve_image(im, fy, 0);
    Image GM(im.w, im.h, 1);
    Image D(im.w, im.h, 1);
    for (float i = 0; i < im.w; i++)
    {
        for (float j = 0; j < im.h; j++)
        {
         GM(i, j, 0) = sqrt(pow(Gx(i, j, 0), 2) + pow(Gy(i, j, 0), 2));
         D(i, j, 0) = atan2(Gy(i, j, 0), Gx(i, j, 0));   
        }
    }

    return { GM , D };
}


// HW1 #4.4
// const Image& im: input image
// returns the colorized Sobel image of the same size
Image colorize_sobel(const Image& im)
{

    // TODO: Your code here
    Image ret0(im.w, im.h, im.c);
    Image ret(im.w, im.h, im.c);
    Image f = make_gaussian_filter(4);
    ret0 = convolve_image(im, f, true);
    pair<Image, Image> res = sobel_image(ret0);
    Image mag = res.first;
    Image theta = res.second;
    feature_normalize(mag);

    for (float i = 0; i < im.w; i++)
    {
        for (float j = 0; j < im.h; j++)
        {
            ret(i, j, 0) = theta(i, j, 0) / 2 / M_PI + 0.5;
        }
    }

    for (float i = 0; i < im.w; i++)
    {
        for (float j = 0; j < im.h; j++)
        {
            ret(i, j, 1) = mag(i, j, 0);
            ret(i, j, 2) = mag(i, j, 0);
        }
    }

    hsv_to_rgb(ret);
    
    return ret;
}


// HW1 #4.5
// const Image& im: input image
// float sigma1,sigma2: the two sigmas for bilateral filter
// returns the result of applying bilateral filtering to im
Image bilateral_filter(const Image& im, float sigma1, float sigma2)
  {
    Image bf = im;
  
  // TODO: Your bilateral code
    int  w = (int)(6 * sigma1);
  //if (((int)(6 * sigma1)) % 2 == 0)
  //{
  //    w = (int)(6 * sigma1) + 1;
  //}
  //else
  //{
  //    w = (int)(6 * sigma1);
  //}

  for (int x = 0; x <  im.w ; x++)
  {
      for (int y = 0; y <  im.h ; y++)
      {
          for (float k = 0; k < im.c; k++)
          {
              double iFiltered = 0;
              double wP = 0;
              int neighbor_x = 0;
              int neighbor_y = 0;

              for (int i = 0; i < w; i++)
              {
                  for (int j = 0; j < w; j++)

                  {
                      int neighbor_x = x - (w / 2 - i);
                      int neighbor_y = y - (w / 2 - j);

                      double gi = exp(-(pow(im.clamped_pixel(neighbor_x, neighbor_y, k) - im.clamped_pixel(x, y, k), 2)) / (2 * pow(sigma2, 2))) / (2 * M_PI * pow(sigma2, 2));
                      float distance = float(sqrt(pow(x - neighbor_x, 2) + pow(y - neighbor_y, 2)));
                      double gs = exp(-(pow(distance, 2)) / (2 * pow(sigma1, 2))) / (2 * M_PI * pow(sigma1, 2));
                      double w = gi * gs;
                      iFiltered = iFiltered + im.clamped_pixel(neighbor_x, neighbor_y, k) * w;
                      wP = wP + w;

                  }
              }
              iFiltered = iFiltered / wP;
              bf(x, y, k) = iFiltered;
          }
      }
  }
 
  return bf;
  }



// HELPER MEMBER FXNS

void Image::feature_normalize(void) { ::feature_normalize(*this); }
void Image::feature_normalize_total(void) { ::feature_normalize_total(*this); }
void Image::l1_normalize(void) { ::l1_normalize(*this); }

Image operator-(const Image& a, const Image& b) { return sub_image(a,b); }
Image operator+(const Image& a, const Image& b) { return add_image(a,b); }
