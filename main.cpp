#include <iostream>
#include <boost/program_options.hpp>
#include "ImageManipulator.hpp"
namespace po = boost::program_options;

using namespace std;
using namespace cv;





int main(int ac, char*av[]){
  po::options_description desc("helptext");
  string filename;
  string outfilename;
  int blursize;  
  int numLoops;
  desc.add_options()
    ("help,h","detailed help text")
    ("input-file,i",po::value<string>(&filename),"Input file name")
    ("output-file,o",po::value<string>(&outfilename)->default_value(filename),"Output file name")
    ("loop,l",po::value<int>(&numLoops)->default_value(1),"number of times to run blurring option")
    ("blursize,s",po::value<int>(&blursize)->default_value(9),"Blur size.")
    ;
  po::variables_map vm;

  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  try{
    if(vm.count("help")){
      cout << desc << "\n";
    }
 
  }
  catch(po::error& e){
    cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  catch(...){
    cerr << "EXCEPTION UNKOWN!!";
  }
  Mat image = imread(filename, IMREAD_GRAYSCALE);
  Mat output_image_data = image.clone();

  int counter = 0;
  while (counter < numLoops) {
    // blurFunction(&image, &output_image_data, 3);
    counter++;
  }
  imwrite(outfilename, output_image_data);
  return 0;


}

