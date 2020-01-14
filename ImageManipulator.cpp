#include "ImageManipulator.hpp"


ImageManipulator::~ImageManipulator()
{
}

void ImageManipulator::blurFunction(){
  auto imgIn = this->_imgIn;
  auto imgOut = this->_imgOut;
  auto blurSize = this->_blurSize;
  GaussianBlur(imgIn, imgOut, Size(blurSize, blurSize), 1 );
}
