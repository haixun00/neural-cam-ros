#include "supportfunc.hpp"

void constrain_image(image im)
{
    for(int i = 0; i < im.w*im.h*im.c; ++i){
        if(im.data[i] < 0) im.data[i] = 0;
        if(im.data[i] > 1) im.data[i] = 1;
    }
}

image copy_image(image p)
{
    image copy = p;
    copy.data = (float*)calloc(p.h*p.w*p.c, sizeof(float));
    memcpy(copy.data, p.data, p.h*p.w*p.c*sizeof(float));
    return copy;
}

void free_image(image m)
{
    if(m.data){
        free(m.data);
    }
}

float get_pixel(image m, int x, int y, int c)
{
    assert(x < m.w && y < m.h && c < m.c);
    return m.data[c*m.h*m.w + y*m.w + x];
}



void rgbgr_image(image im)
{
    int i;
    for(i = 0; i < im.w*im.h; ++i){
        float swap = im.data[i];
        im.data[i] = im.data[i+im.w*im.h*2];
        im.data[i+im.w*im.h*2] = swap;
    }
}


image ipl_to_image(IplImage* src)
{
    unsigned char *data = (unsigned char *)src->imageData;
    int h = src->height;
    int w = src->width;
    int c = src->nChannels;
    int step = src->widthStep;

    image out;
    out.data = 0;

    out.h = h;
    out.w = w;
    out.c = c;
    out.data = (float*)calloc(h*w*c, sizeof(float)); 

    int count=0;

    for(int k= 0; k < c; ++k){
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                out.data[count++] = data[i*step + j*c + k]/255.;
            }
        }
    }
    return out;
}

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

image mat_to_image(Mat& src)
{
    uint8_t* pixelPtr = (uint8_t*)src.data;
    int h = src.rows;
    int w = src.cols;
    int c = src.channels();

    image out;
    out.data = 0;

    out.h = h;
    out.w = w;
    out.c = c;
    out.data = (float*)calloc(h*w*c, sizeof(float)); 
    
/*
       // DEBUG:
       string ty =  type2str( src.type() );
       printf("Matrix: %s %dx%d \n", ty.c_str(), src.cols, src.rows );

       cout << "height: " << h << endl;
       cout << "width: " << w << endl;
       cout << "channel: " << c << endl;
*/
    int count=0;

    for(int k = 0; k < c; k++){

       for(int i = 0; i < h; i++){

    	  for(int j = 0; j < w; j++){

             uint8_t pixel_value = pixelPtr[i*w*c + j*c + k]; // B
	     out.data[count++] = (float) pixel_value/255;

          }
        }
     }


    return out;
}


image make_empty_image(int w, int h, int c)
{
    image out;
    out.data = 0;
    out.h = h;
    out.w = w;
    out.c = c;
    return out;
}

// <<<<<<<<<*********************************
// <<<<<<<<< support functions **************
// <<<<<<<<<*********************************

