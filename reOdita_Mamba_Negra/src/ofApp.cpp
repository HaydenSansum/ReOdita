#include "ofApp.h"

// CORE DRAW FUNCTIONS
//--------------------------------------------------------------
void ofApp::setup(){
    
    // Parameters
    rand_chance = 0.5; // Float representing P(draw) (0.5 = 50%, 0.9 = 90%)
    
    // Initialize sizes
    block_width = ofGetWidth() / draw_binary_ncols;
    block_height = ofGetHeight() / draw_binary_nrows;
    
    // Initilize matrix to 100
    for (int i = 0; i < draw_binary_nrows; i++) {
        for (int j = 0; j < draw_binary_ncols; j++) {
            draw_binary_matrix[i][j] = 100;
        }
    }
    
    // Generate an initial draw matrix
    shuffle_draw_matrix();
    
}

//--------------------------------------------------------------
void ofApp::update(){

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    ofSetColor(0);
    
    for (int j = 0; j < draw_binary_ncols; j++) {
        for (int i = 0; i < draw_binary_nrows; i++) {
    
            if (draw_binary_matrix[i][j] == 1) {
                // Draw the top of the triangle
                draw_triangle_top(i, j, ofColor(0), ofColor(50));
            } else if (draw_binary_matrix[i][j] == 2) {
                // Draw the bottom of the triangle
                draw_triangle_bottom(i, j, ofColor(0), ofColor(50));
            }
                
       }
    }
    
}

// USER FUNCTIONS FUNCTIONS
//--------------------------------------------------------------
void ofApp::shuffle_draw_matrix(){
    
    
    // GENERATE THE DRAW BINARY MATRIX - WHETHER TO DRAW OR NOT PER CELL
    
    // Want to randomize the order we iterate through the matrix as this makes a difference in how "regimented" it looks
    i_order.clear();
    j_order.clear();
    for (int num_i = 0; num_i < (draw_binary_nrows-1); num_i++) {
        i_order.push_back(num_i);
    }
    random_shuffle(i_order.begin(), i_order.end());
    
    for (int num_j = 0; num_j < (draw_binary_ncols); num_j++) {
        j_order.push_back(num_j);
    }
    random_shuffle(j_order.begin(), j_order.end());
    
    
    // Loop through each row - in random order
    for (int i_select = 0; i_select < (draw_binary_nrows-1); i_select++) {
        // For each column in the matrix - in random order
        for (int j_select = 0; j_select < draw_binary_ncols; j_select++) {
            
            int i = i_order[i_select];
            int j = j_order[j_select];
            
            // Only perform operations if the current cell is 100
            if (draw_binary_matrix[i][j] == 100) {
                
                // Random probability of 1 else nothing
                float rand_float = ofRandom(1.0);
                if (rand_float < rand_chance) {
                    
                    draw_binary_matrix[i][j] = 1;
                    // If the column is an even number - highlight bottom left as 1, if odd highlight bottom right as 1
                    if (j % 2 != 0) {
                        draw_binary_matrix[i][j-1] = 0;
                        draw_binary_matrix[i+1][j-1] = 2; // Set to 2 to represent the bottom
                        draw_binary_matrix[i+1][j] = 0;
                    } else {
                        draw_binary_matrix[i][j+1] = 0;
                        draw_binary_matrix[i+1][j+1] = 2; // Set to 2 to represent the bottom
                        draw_binary_matrix[i+1][j] = 0;
                    }
                    
                }
            }
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::reset_draw_matrix(){
    for (int i = 0; i < (draw_binary_nrows); i++) {
        for (int j = 0; j < draw_binary_ncols; j++) {
            draw_binary_matrix[i][j] = 100;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw_triangle_top(int i, int j, ofColor color_left, ofColor color_right){
   
    // 4 possible cases depending on which corner of the grid
    if (j % 2 == 0) {
        // Top Left Corner - left panel
        ofSetColor(color_left);
        ofVec2f tip_point = ofVec2f(block_width*j, block_height*i);
        ofVec2f base_left = ofVec2f(block_width*j, block_height*(i+1));
        ofVec2f base_center = ofVec2f(block_width*(j+1), block_height*(i+1));
        ofDrawTriangle(tip_point, base_left, base_center);
        
        // Top Left Corner - right panel
        ofSetColor(color_right);
        ofVec2f base_right = ofVec2f(block_width*(j+2), block_height*(i+1));
        ofDrawTriangle(tip_point, base_center, base_right);
    } else {
        // Top Right Corner - right panel
        ofSetColor(color_right);
        ofVec2f tip_point = ofVec2f(block_width*(j+1), block_height*i);
        ofVec2f base_center = ofVec2f(block_width*(j), block_height*(i+1));
        ofVec2f base_right = ofVec2f(block_width*(j+1), block_height*(i+1));
        ofDrawTriangle(tip_point, base_center, base_right);
        
        // Top Right Corner - left panel
        ofSetColor(color_left);
        ofVec2f base_left = ofVec2f(block_width*(j-1), block_height*(i+1));
        ofDrawTriangle(tip_point, base_center, base_left);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw_triangle_bottom(int i, int j, ofColor color_left, ofColor color_right){
   
    // 4 possible cases depending on which corner of the grid
    if (j % 2 == 0) {
        // Bottom Left Corner - left panel
        ofSetColor(color_left);
        ofVec2f tip_point = ofVec2f(block_width*j, block_height*(i+1));
        ofVec2f base_left = ofVec2f(block_width*j, block_height*(i));
        ofVec2f base_center = ofVec2f(block_width*(j+1), block_height*(i));
        ofDrawTriangle(tip_point, base_left, base_center);
        
        // Bottom Left Corner - right panel
        ofSetColor(color_right);
        ofVec2f base_right = ofVec2f(block_width*(j+2), block_height*(i));
        ofDrawTriangle(tip_point, base_right, base_center);
    } else {
        // Bottom Right Corner - right panel
        ofSetColor(color_right);
        ofVec2f tip_point = ofVec2f(block_width*(j+1), block_height*(i+1));
        ofVec2f base_center = ofVec2f(block_width*(j), block_height*(i));
        ofVec2f base_right = ofVec2f(block_width*(j+1), block_height*(i));
        ofDrawTriangle(tip_point, base_center, base_right);
        
        // Bottom Right Corner - left panel
        ofSetColor(color_left);
        ofVec2f base_left = ofVec2f(block_width*(j-1), block_height*(i));
        ofDrawTriangle(tip_point, base_center, base_left);
        
    }
    
}


// OF HELPER FUNCTIONS
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        img.save(ofGetTimestampString() + ".png");
    }
    
    if (key == 's') {
        reset_draw_matrix();
        shuffle_draw_matrix();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
