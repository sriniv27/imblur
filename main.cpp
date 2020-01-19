/**
 * @file main.cpp
 * @author Suhas (sugas182@gmail.com)
 * @brief Blur an image given its path and kernel size parameters 
 * @version 0.1
 * @date 2020-01-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <boost/stacktrace.hpp>
#include <boost/program_options.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace po = boost::program_options; // see here for doc: https://www.boost.org/doc/libs/1_64_0/doc/html/program_options.html

using namespace std;
using namespace cv;

/**
 * @brief Wrapper around cv::GaussianBlur that takes the address of the image being manipulated and 
 * 
 * @param imgIn 
 * @param imgOut 
 * @param rows 
 * @param cols 
 */
void blurFunction(const Mat& imgIn, Mat& imgOut,const int& rows, const int& cols){
auto ksize = Size(rows, cols);  
  GaussianBlur(imgIn,imgOut , ksize, 1 );
}


/**
 * @brief imblur takes an image along with kernel size parameters and blurs it to be passed to a screen locker of your choice.
 * 
 * @param ac 
 * @param av 
 * @return int 
 */
int main(int ac, char*av[]){
  
  try{
  Mat image;
  po::options_description desc("helptext");
  string filename;
  string outfilename;
  int rows=0;  
  int cols=0;
  bool quietOutput = false;
  desc.add_options()
    ("help,h","detailed help text")
    ("input-file,i",po::value<string>(&filename),"Input file name")
    ("output-file,o",po::value<string>(&outfilename)->default_value("output.png"),"Output file name")
    ("rows,r",po::value<int>(&rows)->default_value(5),"number of rows in the smoothing kernel")
    ("cols,c",po::value<int>(&cols)->default_value(3),"number of columns in the smoothing kernel")
    ("quiet,q",po::value<bool>(&quietOutput)->default_value(false),"Quiet (no print to stdout)")
    ;
  po::variables_map vm;
  
  po::store(po::parse_command_line(ac, av, desc), vm);

  po::notify(vm);
if(vm.count("help")){
      cout << desc << "\n";
      return 1;
    }    

    if(vm.count("input-file")){
      cout << "Input file: " << filename << "\n";
    } else
    {
      cerr << "Input file not specified. Exiting" << "\n";
     
    }
    
    
    if(vm.count("quiet,q")){
      quietOutput = true;
    }
    
    

image = imread(filename, cv::ImreadModes::IMREAD_GRAYSCALE);
  
  if (!quietOutput){
    cout<< "in filename: " << boost::lexical_cast<string>(filename)<<"\n";
      cout<< "out filename: " << boost::lexical_cast<string>(outfilename)<<"\n";
  
  }
 auto ctr=0;
 Mat output_image_data;

  blurFunction(image, image, rows, cols);
  
  
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

