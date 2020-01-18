#if !defined(IMAGEMANIPULATOR_HPP)
#define IMAGEMANIPULATOR_HPP

#include <boost/stacktrace.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
using namespace cv;
class ImageManipulator
{
private:
  /* data */
  Mat _imgIn;
  Mat _imgOut;
  int _blurSize = 9;
  int _numLoops = 3;
public:
Mat imgIn(){return this->_imgIn;}
int blurSize(){return this->_blurSize;}
  void blurFunction();
  Mat outputImage(){return this->_imgOut;};
  ImageManipulator() = default;
  ImageManipulator(Mat inputImage):ImageManipulator{inputImage,  9, 3} {};
  ImageManipulator(Mat inputImage, int blurSize) : ImageManipulator{inputImage, blurSize, 3}{};
  ImageManipulator(Mat inputImage, int blurSize, int numLoops): _imgIn{inputImage}{
    this->_imgOut = this->_imgIn.clone();
    this->_blurSize = blurSize;
    this->_numLoops = numLoops;
  }
  ~ImageManipulator();
};


#endif // IMAGEMANIPULATOR_HPP

