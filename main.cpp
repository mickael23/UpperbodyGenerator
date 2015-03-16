#include "dirent.h"
#include "draw.h"

#include <stack>
#include <vector>
#include <iostream>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

Draw draw;
string currentFile;
void (Draw::* preparations[4])(int, int) = { &Draw::prepareCircle, &Draw::prepareLeftBar, &Draw::prepareRightBar, &Draw::prepareCross };
void (Draw::* events[4])(int, int) = { &Draw::drawCircle, &Draw::drawLeftBar, &Draw::drawRightBar, &Draw::drawCross };

int state = 0; // 0 for up_head, 1 for left, 2 for right, 3 for middle_head

vector<string> loadFiles(string dirName) {
	vector<string> toReturn;
	
	DIR * dir;
	struct dirent *ent;

	if ((dir = opendir (dirName.c_str())) != NULL) {
		int ct = 0;

		// Print all the files and directories within directory 
		while ((ent = readdir (dir)) != NULL) {
			// Ignore current and parent dirs
			if(string(ent->d_name) == "." || string(ent->d_name) == "..") {
				continue;
			}

			stringstream ss;
			ss << dirName << "/" << ent->d_name;

			toReturn.push_back(string(ss.str()));

			ct++;
		}
	}

	closedir (dir);
	return toReturn;
}

void writeInformations() 
{
	int i = 0;

	// Open a CSV file in order to write informations about scores obtained
	ofstream file;

	std::stringstream ss;
	ss << "upperbodies.csv";
	file.open(ss.str());

	// Pop the unused info
	draw.informations.pop();

	// Write each information
	while(!draw.informations.empty()) {
		Info info = draw.informations.top();

		if(info.valid) {
			file << info.fileName << ", "
				 << info.headUp_x << ", " << info.headUp_y << ", " 
				 << info.left << ", " << info.right << ", "
				 << info.headMiddle_x << ", " << info.headMiddle_y << "\n";
		}

		draw.informations.pop();
	}

	file.close();
}

void onClick(int event, int x, int y, int flags, void * userdata) {
	cout << x << ", " << y << endl;

	(draw.*preparations[state])(x, y);

	if(event == EVENT_LBUTTONDOWN) {
		(draw.*events[state])(x, y);
		state++;
	}

	if(state == 4) {
		draw.informations.top().valid = true;
		draw.informations.push(Info(currentFile));
		state = 0;
	}
}

int main() {
	vector<string> files = loadFiles("Data");

	namedWindow("Upperbody Generator");
	setMouseCallback("Upperbody Generator", onClick, NULL);

	bool next = false;

	for(string s : files) {
		currentFile = s;
		draw.image = imread(s);
		draw.lastImages.push(draw.image.clone());

		draw.informations.push(Info(s));

		imshow("Upperbody Generator", draw.image);

		// Big loop
		while(true) {
			switch(waitKey())
			{
				case 'b':
					// Repasse-t-on au perso précédent ?
					if(state == 0) {
						draw.informations.pop();
						state = 3;
					} else {
						state--;
					}

					// On revient à l'image précédente
					draw.image = draw.lastImages.top();
					draw.lastImages.pop();

					// On redessine l'image
					imshow("Upperbody Generator", draw.image);

					break;
				case 'c':
					// On passe à la prochaine image (ou on quitte)
					next = true;
			}

			if(next == true) {
				next = false;
				state = 0;
				break;
			}
		}
	}

	// Write informations into a file
	writeInformations();

	return 1;
}