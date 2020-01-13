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
  void blurFunction(Mat* inputImage, Mat* outputImage, int blurSize);
public:
ImageManipulator();
  ImageManipulator(Mat inputImage);
  ImageManipulator(Mat inputImage, int blurSize);
  ImageManipulator(Mat inputImage, int blurSize, int numLoops);
  ~ImageManipulator();
  
};
