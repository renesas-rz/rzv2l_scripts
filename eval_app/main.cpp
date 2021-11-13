#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>

using namespace std;

#include "imagenet_classes.hpp"

class drpai {
	std::string imageFilename = "";
	std::string imageDirectory = "";
	std::string camDirectory = "";
	bool	enabled = true;

	std::vector<pair<int,float>> buffer;


    template <class T1, class T2, class Pred = std::less<T2> >
	struct sort_pair_second {
	    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
	        Pred p;
	        return p(left.second, right.second);
	    }
	};
	
	void parseNetwork ( string network ) {
		cout << "Post Processing ";

		if ( network.compare("resnet") == 0) {
			cout << "AI Network Resnet50";
		} else if ( network.compare("mobilenet") == 0) {
			cout << "AI Network Mobile Net";
		} else if ( network.compare("tinyyolo") == 0) {
			cout << "AI Network Tiny Yolo";
		} else if ( network.compare("yolo") == 0) {
			cout << "AI Network Yolo";
		} else {
			cout << "Network not found";
			this->enabled = false;
		}
		cout << ", Filename: " << this->imageFilename << endl;
	}
	
	public:
	
	drpai() : imageFilename("sample_bmp.bin") {
		drpai::parseNetwork( "resnet" );
	}
	
	drpai( string network, string filename ) : imageFilename(filename) {
		drpai::parseNetwork( network );
	}
	void showClass ( int n ) {
	    cout << classes[ std::to_string(n) ] << endl;
	}
	
	bool decodeOutput () {
	    bool ret = true;
		if ( this->enabled ) {
			cout << "Decode ";

			std::ifstream imageFile (this->imageFilename, ios::in | ios::binary);
			if ( imageFile.is_open() ) {
				cout << "Processing file: " << this->imageFilename;

				float f;
				int i = 0;
				while (imageFile.read(reinterpret_cast<char*>(&f), sizeof(float))) {
					this->buffer.push_back(pair<int, float>(i++, f));
				}
				cout << ", Sample size: " << buffer.size() << endl;
				imageFile.close();

			} else {
				cout << "Unable to open file" << endl;
				ret = false;
			}

		}
		return ret;
	}
	void headData ( int n ) {
		if ( enabled ) {
			cout << "List of the top: " << n << endl;
			std::sort(this->buffer.begin(), this->buffer.end(), sort_pair_second<int, float, std::greater<float> >());
			for ( int i = 0; i < n; i++ ) {
				cout << "Top "<< i << " : ("<< \
						std::fixed << std::setw(7) << std::setprecision(2) << this->buffer[i].second*100 \
						<< ") " \
						<< classes[ std::to_string(this->buffer[i].first ) ] \
						<< endl;
			}
		}
	}
	
};
		
/* demo.c:  My first C program on a Linux */ 
int main( int argc, char *argv[] ) 
{ 
    drpai *ai;
	for ( int i = 0; i < argc; i++ ) {
		cout << argv[i] << endl;
	}

	if ( argc == 1 ) {
		ai = new drpai();
	} else {
		ai = new drpai(argv[1], argv[2] );
	}
	
	if ( ai->decodeOutput() ) {
	    ai->headData(5);
	}
	
    return 0; 
} 
