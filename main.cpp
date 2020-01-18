#include <iostream>
#include <boost/stacktrace.hpp>
#include <boost/program_options.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
namespace po = boost::program_options; // see here for doc: https://www.boost.org/doc/libs/1_64_0/doc/html/program_options.html

using namespace std;
using namespace cv;
void blurFunction(const Mat& imgIn, Mat& imgOut,const int& blurSize){
auto ksize = Size(blurSize, blurSize);  
  GaussianBlur(imgIn,imgOut , ksize, 1 );
}



int main(int ac, char*av[]){
  
  try{
  Mat image;
  po::options_description desc("helptext");
  string filename;
  string outfilename;
  int blursize=0;  
  int numLoops=0;
  bool quietOutput = false;
  desc.add_options()
    ("help,h","detailed help text")
    ("input-file,i",po::value<string>(&filename)->required(),"Input file name")
    ("output-file,o",po::value<string>(&outfilename)->default_value("output.png"),"Output file name")
    ("loop,l",po::value<int>(&numLoops)->default_value(1),"number of times to run blurring option")
    ("blursize,s",po::value<int>(&blursize)->required(),"Blur size.")
    ("quiet,q",po::value<bool>(&quietOutput)->default_value(false),"Quiet (no print to stdout)")
    ;
  po::variables_map vm;

  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

    if(vm.count("help")){
      cout << desc << "\n";
      return 0;
    }
    if(vm.count("quiet,q")){
      quietOutput = true;
    }
    
    

image = imread(filename, cv::ImreadModes::IMREAD_GRAYSCALE);
  if (!quietOutput){
    cout<< "in filename: " << boost::lexical_cast<string>(filename)<<"\n";
      cout<< "out filename: " << boost::lexical_cast<string>(outfilename)<<"\n";
  cout<< "Blur size: " << boost::lexical_cast<string>(blursize)<<"\n";
    cout<< "num loops: " << boost::lexical_cast<string>(numLoops)<<"\n";
  }
 auto ctr=0;
 Mat output_image_data;
while (ctr < numLoops){
  blurFunction(image, image, blursize);
  ctr++;
  }
  
  imwrite(outfilename, image);
  return 0;
  }
  catch(po::error& e){
    cerr << "Error in input: " << e.what() << "\n";
    cout << boost::stacktrace::stacktrace();
    return 1;
  }
  catch(cv::Exception& cvException){
    cerr << "Runtime Error: \n\n" << cvException.msg << "\n";
 cerr << "ERROR CODE: " << cvException.code << "\n";

 cerr << boost::stacktrace::stacktrace();
    return cvException.code;
  }
  catch(...){
    cerr << "EXCEPTION UNKOWN!!";
    
    cerr << boost::stacktrace::stacktrace();
    return 2;
  }
return 0;

}

