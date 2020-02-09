/**
 * @file main.cpp
 * @author Suhas (sugas182@gmail.com)
 * @brief Blur an image given its path and kernel size parameters.
 * A selected image is smoothed using OpenCV's implementation of a Gaussian
 * Blur. You can specify the size of the smoothing kernel m-by-n.
 * @version 1.1
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <boost/program_options.hpp>
#include <boost/stacktrace.hpp>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

/// see here for documentation on using boost::program_options:
/// https://www.boost.org/doc/libs/1_64_0/doc/html/program_options.html
namespace po = boost::program_options;

using namespace std;
using namespace cv;
/**
 * @brief Container to hold user-facing information of the image.
 *
 */
struct ImageData
{
private:
    /** Internal store of the image matrix */
    Mat image_;
    /** File path of the input image */
    string filename_;

    /** File path of the output image */
    string outfilename_;
    int rows_;
    int cols_;


public:
    /**
     * @brief Return the size of the smoothing kernel matrix as a cv::Size using the kernels row and column psecificia
     *
     * @return cv::Size
     */
    cv::Size kernelSize() {
        return cv::Size(this->rows_, this->cols_);
    }
    /**
     * @brief Provide the cv::Mat representation of the stored image.
     *
     * @return Mat
     */
    Mat image()
    {
        return this->image_;
    }
    string filename()
    {
        auto fname = this->filename_;
        return fname;
    }
    string outfilename()
    {
        auto oFname = this->outfilename_;
        return oFname;
    }
    /** Number of rows of the smoothing kernel. */
    int rows()
    {
        return this->rows_;
    };
    /** Number of columns of the smoothing kernel */
    int cols()
    {
        return this->cols_;
    };

    /**
     * @brief Construct a new Image Data object
     *
     * @param filename_
     * @param outfilename_
     */
    ImageData ( string _filename, string _outfilename )
    {

        this->filename_ = _filename;
        load_image();
        this->outfilename_ = _outfilename;
    };
    /**
     * @brief load the image from the stored filename.
     *
     * @return Mat
     */
    void load_image()
    {
        // TODO: imread flags could be turned into a user configuration later maybe.
        this->image_ = cv::imread ( this->filename_, cv::ImreadModes::IMREAD_UNCHANGED );
    }
};

/**
 * @brief Apply a blurring operation to an image
 *
 * @param imgIn
 * @param imgOut
 * @param rows
 * @param cols
 */
void blurFunction ( const Mat &imgIn, Mat &imgOut, const int &rows, const int &cols );
void blurFunction ( ImageData imageObj );

/**
 *
 * @brief imblur takes an image along with kernel size parameters and
 * blurs it to be passed to a screen locker of your choice.
 *
 * @param ac
 * @param av
 * @return int
 */
int main ( int ac, char *av[] )
{

    auto console = spdlog::stdout_logger_mt ( "console" );
    auto err_logger = spdlog::stderr_logger_mt ( "stderr" );

    try
    {

        auto console = spdlog::stdout_logger_mt ( "console" );
        auto err_logger = spdlog::stderr_logger_mt ( "stderr" );
        string filename;
        string outfilename;
        int rows = 0;
        int cols = 0;
        bool quietOutput = false;
        int numLoops;

        po::options_description desc ( "helptext" );

        desc.add_options() ( "help,h", "detailed help text" )

        ( "input-file,i", po::value<string> ( &filename ), "Input file name" )

        ( "output-file,o", po::value<string> ( &outfilename )->default_value ( "output.png" ),
          "Output file name" )

        ( "rows,m", po::value<int> ( &rows )->default_value ( 5 ),
          "number of rows in the smoothing kernel" )

        ( "cols,n", po::value<int> ( &cols )->default_value ( 3 ),
          "number of columns in the smoothing kernel" )

        ( "quiet,q", po::value<bool> ( &quietOutput )->default_value ( false ),
          "Quiet (no print to stdout)" )

        ( "numloops,l", po::value<int> ( &numLoops )->default_value ( 1 ),
          "Number of times to run smoothing operation" );

        po::variables_map vm;
        po::store ( po::parse_command_line ( ac, av, desc ), vm );

        po::notify ( vm );

        if ( vm.count ( "help" ) )
        {
            cout << desc << "\n";
            return 1;
        }

        if ( vm.count ( "input-file" ) )
        {
        }
        else
        {
            cerr << "Input file not specified. Exiting"
                 << "\n";
        }

        if ( vm.count ( "quiet,q" ) )
        {
            quietOutput = true;
        }

        ImageData imgInfo ( filename, outfilename );
        imgInfo.load_image();
        auto image = imgInfo.image();

        try
        {
            if ( !quietOutput )
            {
                console->info ( "in filename: {}", boost::lexical_cast<string> ( imgInfo.filename() ) );
                console->info ( "out filename: {}", boost::lexical_cast<string> ( imgInfo.outfilename() ) );
            }
        }
        catch ( const spdlog::spdlog_ex &currentException )
        {
            cerr << currentException.what() << "\n";
        }

        auto ctr = 0;
        Mat output_image_data;
        while ( ctr < numLoops )
        {
            while ( ctr < numLoops )
            {
                blurFunction ( image, image, rows, cols );
                // blurFunction(imgInfo);
                ctr++;
            }

            imwrite ( outfilename, image );
            return 0;

        }
    }
    catch ( po::error &e )
    {
        cerr << "Error in input: " << e.what() << "\n";
        cout << boost::stacktrace::stacktrace();
        return 1;

    }
    catch ( const spdlog::spdlog_ex &ex )
    {
        cerr << "Runtime Error: \n\n" << ex.what() << "\n";

        cerr << boost::stacktrace::stacktrace();
        return 2;

    }
    catch ( ... )
    {
        cerr << "EXCEPTION UNKOWN!!";

        cerr << boost::stacktrace::stacktrace();
        return 3;
    }

    return 0;
}

/**
 * @brief Wrapper around cv::GaussianBlur that takes the address of the image
 * being manipulated along with directed kernel matrix size paramter and
 * applies a GaussianBlur on it.
 *
 * @param imgIn
 * @param imgOut
 * @param rows
 * @param cols
 */
void blurFunction ( const Mat &imgIn, Mat &imgOut, const int &rows, const int &cols )
{
    auto ksize = Size ( rows, cols );
    GaussianBlur ( imgIn, imgOut, ksize, 1 );
}

void blurFunction ( ImageData imageObject )
{
    auto ksize = Size ( imageObject.rows(), imageObject.cols() );
    GaussianBlur ( imageObject.image(), imageObject.image(), imageObject.kernelSize(), 1 );
}
