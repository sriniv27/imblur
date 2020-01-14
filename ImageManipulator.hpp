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
  int _blurSize {9};
  int _numLoops {3};
public:
  void blurFunction();
  Mat outputImage(){return this->_imgOut;};
  ImageManipulator() = default;
  ImageManipulator(Mat inputImage):ImageManipulator{inputImage,  _blurSize, _numLoops} {};
  ImageManipulator(Mat inputImage, int blurSize) : ImageManipulator{inputImage, blurSize, _numLoops}{};
  ImageManipulator(Mat inputImage, int blurSize, int numLoops): _imgIn{inputImage}{
    this->_imgOut = this->_imgIn.clone();
    this->_blurSize = blurSize;
    this->_numLoops = numLoops;
  }
  ~ImageManipulator();
};
