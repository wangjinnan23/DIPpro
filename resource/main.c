#include "fr.h"
#include "Image_FFT.h"
#include "Contrast.h"
#include "convolution.h"
#define SIZE_WH 256
#include "adaboost.h"
#define HIGH_FR 1
#define LOW_FR 2
#include "lowpassfilter.h"
#include "filter.h"
#include "smooth.h"
#include "sharpen.h"
void showfilter(double *filter,int width,int height){
    IplImage *show=cvCreateImage(cvSize(width, height),8,1);
    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++){
            cvSetReal2D(show, j, i, filter[i*width+j]*255.0);
        }
    cvNamedWindow("Filter", 1);
    cvShowImage("Filter", show);
    cvWaitKey(0);
    cvReleaseImage(&show);

}

int main(int argc, const char * argv[]) {
    
    IplImage *src =cvLoadImage("/Users/Tony/DIPImage/moon2.jpg", 0);
    IplImage *dst =cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage *dstcv =cvCreateImage(cvGetSize(src), src->depth, src->nChannels);

    double* srcarry=(double *)malloc(sizeof(double)*src->width*src->height);
    double* dstarry=(double *)malloc(sizeof(double)*src->width*src->height);
    for (int j=0;j<src->height; j++) {
        for(int i=0;i<src->width;i++)
            srcarry[j*src->width+i]=cvGetReal2D(src, j, i);
    }
    
    //double power=FrequencyFiltering(src,dst,GHPF,20,0,0,0,0,1);
    //Complex a[512*512];
    //ImageFFT(src, a);
    //getAmplitudespectrum(a, 512, 512, dst);
    //cvSaveImage("/Users/Tony/DIPImage/testfir_ILPF_10.jpg", dst, 0);
    //MedianFilter(srcarry,dstarry,src->width,src->height,7,7);
    //GaussianFilter(srcarry,dstarry,src->width,src->height, 3, 3, 1);
    //BilateralFilter(srcarry, dstarry, src->width, src->height, 15, 15, 5, 75);
    //cvSmooth(src, dstcv, CV_BILATERAL, 15, 15, 75,5);
    //MeanFilter(src, dst,  7, 7);
    //NoLinearMeanFilter(src, dst, 3, 3, NLMF_MASK_G, NLMF_FUN_G, 1.0);
    //RobustSmoothFilter(src,dst,3,3);
    //cvSaveImage("/Users/Tony/DIPImage/gau_lena_7.jpg", dst, 0);
    //cvSmooth(src, cvdst, CV_MEDIAN, 13, 13, 0, 0);
    //cvSmooth(src, cvdst, CV_BLUR,15,15,0,0);
    UnsharpMasking(srcarry,dstarry,src->width,src->height,SMOOTH_GAUSSIAN,7,7,2.0,2.0);
    //SobelSharpen(srcarry,dstarry,src->width,src->height,1);
    //Sobel(srcarry, dstarry, src->width, src->height);
    //LaplaceSharpen(srcarry, dstarry, src->width, src->height,0,0.5);
    //GaussianFilter(src,dst,3,3,2);
    //MeanFilter(src, dst,  5, 5);
    //Laplace(srcarry,dstarry,src->width,src->height,3);
    ////////////////////////////////////////////////////////
    //HistogramEqualization(src,dst);
    for (int j=0;j<src->height; j++) {
        for(int i=0;i<src->width;i++)
            cvSetReal2D(dst, j, i,dstarry[j*src->width+i]);
    }
    cvSaveImage("/Users/Tony/DIPImage/usm_g_7722.jpg",dst, 0);
    cvNamedWindow("src", 1);
    cvShowImage("src", src);
    cvNamedWindow("dst", 1);
    cvShowImage("dst", dst);
    //cvSub( dstcv,dst, dstcv, NULL);
    //HistogramEqualization(dstcv,dstcv);
    //cvNamedWindow("dstsub", 1);
    //cvShowImage("dstsub", dstcv);
    //cvSub(dst,cvdst,cvdst,NULL);
    //HistogramEqualization(cvdst, cvdst);
    //cvNamedWindow("dst2", 1);
    //cvShowImage("dst2", dst2);
    //HistogramEqualization(dst,dst);
    //printf("work done\n");
    
    cvWaitKey(0);
    free(srcarry);
    return 0;
}





