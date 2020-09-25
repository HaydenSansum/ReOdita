#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void shuffle_draw_matrix();
        void reset_draw_matrix();
        void draw_triangle_top(int i, int j, ofColor color_left, ofColor color_right);
        void draw_triangle_bottom(int i, int j, ofColor color_left, ofColor color_right);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Matrix to track where to draw
    int draw_binary_matrix[10][24];
    int draw_binary_nrows = 10;
    int draw_binary_ncols = 24;
    
    // Vectors to shuffle for index ordering
    vector <int> i_order;
    vector <int> j_order;
    
    // Triangle sizes
    float block_width;
    float block_height;
    
    // Parameters
    float rand_chance;
	
    // Screenshots
    ofImage img;
};
