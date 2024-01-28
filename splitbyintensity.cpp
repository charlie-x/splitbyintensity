#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

const unsigned int levels = 10;

/**
 * @brief Main application to process an image.
 *
 * the app takes an image path as a command line argument, loads the image,
 * and separates it into 10 images based on pixel intensity.
 * each of the 10 images will contain pixels of certain brightness,
 * evenly distributed across the full range of 0-255, with black pixels set as transparent.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return int Application exit code.
 */
int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <ImagePath> <ouput>_range.png" << std::endl;
		return -1;
	}

	// get the image input name the command line argument
	std::string imagePath = argv[1];
	
	// prefix for the outputs
	std::string outputPrefix = argv[2];

	cv::Mat originalImage = cv::imread(imagePath, cv::IMREAD_COLOR);

	if (originalImage.empty()) {
		std::cerr << "Error: Image cannot be loaded!" << std::endl;
		return -1;
	}

	//gray conversion, check channels
	cv::Mat grayImage;
	cv::cvtColor(originalImage, grayImage, cv::COLOR_BGR2GRAY);

	// intensity range division
	int rangeSize = 256 / levels; // 256 levels of intensity, 10 outputs

	for (int i = 0; i < levels; ++i) {

		int lowerBound = i * rangeSize;

		int upperBound = (i != 9) ? (i + 1) * rangeSize : 256; // ensure the last range includes the max intensity

		cv::Mat mask = (grayImage >= lowerBound) & (grayImage < upperBound);

		// create a 4-channel image (BGRA) where alpha is determined by the mask
		cv::Mat rangeImageWithAlpha = cv::Mat::zeros(grayImage.size(), CV_8UC4);

		for (int y = 0; y < grayImage.rows; y++) {

			for (int x = 0; x < grayImage.cols; x++) {

				uchar pixelValue = grayImage.at<uchar>(y, x);
			
				uchar alphaValue = mask.at<uchar>(y, x) ? 255 : 0; // fully opaque for mask, transparent otherwise
				
				rangeImageWithAlpha.at<cv::Vec4b>(y, x) = cv::Vec4b(pixelValue, pixelValue, pixelValue, alphaValue);

			}
		}

		std::string filename = "range_" + std::to_string(lowerBound) + "_" + std::to_string(upperBound - 1) + ".png";

		cv::imwrite(filename, rangeImageWithAlpha);
	}

	return 0;
}
