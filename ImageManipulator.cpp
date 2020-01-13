#include "ImageManipulator.hpp"


ImageManipulator::ImageManipulator(Mat inputImage)
{
  this->_imgIn = inputImage;
  this->_imgOut = _imgIn.clone();

  
}

ImageManipulator::ImageManipulator(Mat inputImage, int blurSize)
{
  this->_imgIn = inputImage;
  this->_imgOut = _imgIn.clone();
  this->_blurSize = blurSize;
  
}

ImageManipulator::ImageManipulator(Mat inputImage, int blurSize, int numLoops)
{
  this->_imgIn = inputImage;
  this->_imgOut = _imgIn.clone();
  this->_blurSize = blurSize;
  this->_numLoops = numLoops;
}

ImageManipulator::ImageManipulator()
{
    
}


ImageManipulator::~ImageManipulator()
{
}

void ImageManipulator::blurFunction(Mat *inputImage,Mat *outputImage, int blursize){

  GaussianBlur(*inputImage, *outputImage, Size(blursize,blursize), 1);
  
}