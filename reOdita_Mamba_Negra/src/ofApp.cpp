#include "ofApp.h"

// CORE DRAW FUNCTIONS
//--------------------------------------------------------------
void ofApp::setup(){
    
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
                ofSetColor(0);
                draw_triangle(i, j);
                
                ofSetColor(255,0,0,100);
                ofDrawRectangle(j*block_width, i*block_height, ofGetWidth() / draw_binary_ncols, ofGetHeight() / draw_binary_nrows);
            }
       }
    }
    
}

// USER FUNCTIONS FUNCTIONS
//--------------------------------------------------------------
void ofApp::shuffle_draw_matrix(){
    
    
    // GENERATE THE DRAW BINARY MATRIX - WHETHER TO DRAW OR NOT PER CELL
    // Loop through each row
    for (int i = 0; i < (draw_binary_nrows-1); i++) {
        // For each column in the matrix
        for (int j = 0; j < draw_binary_ncols; j++) {
            
            // Only perform operations if the current cell is 100
            if (draw_binary_matrix[i][j] == 100) {
                
                // Random probability of 1 else nothing
                float rand_float = ofRandom(1.0);
                if (rand_float < 0.5) {
                    
                    draw_binary_matrix[i][j] = 1;
                    // If the column is an even number - highlight bottom left as 1, if odd highlight bottom right as 1
                    if (j % 2 != 0) {
                        draw_binary_matrix[i][j-1] = 0;
                        draw_binary_matrix[i+1][j-1] = 1;
                        draw_binary_matrix[i+1][j] = 0;
                    } else {
                        draw_binary_matrix[i][j+1] = 0;
                        draw_binary_matrix[i+1][j+1] = 1;
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
void ofApp::draw_triangle(int i, int j){
   
    // 4 possible cases depending on which corner of the grid
    if (i % 2 == 0) {
        if (j % 2 == 0) {
            // Top Left Corner
            ofVec2f tip_point = ofVec2f(block_width*j, block_height*i);
            ofVec2f base_left = ofVec2f(block_width*j, block_height*(i+1));
            ofVec2f base_right = ofVec2f(block_width*(j+2), block_height*(i+1));
            ofDrawTriangle(tip_point, base_left, base_right);
        } else {
            // Top Right Corner
            ofVec2f tip_point = ofVec2f(block_width*j, block_height*i);
            ofVec2f base_left = ofVec2f(block_width*(j-2), block_height*(i+1));
            ofVec2f base_right = ofVec2f(block_width*j, block_height*(i+1));
            ofDrawTriangle(tip_point, base_left, base_right);
        }
    } else {
        if (j % 2 == 0) {
            // Bottom Left Corner
            ofVec2f tip_point = ofVec2f(block_width*j, block_height*i);
            ofVec2f base_left = ofVec2f(block_width*j, block_height*(i-1));
            ofVec2f base_right = ofVec2f(block_width*(j+2), block_height*(i-1));
            ofDrawTriangle(tip_point, base_left, base_right);
        } else {
            // Bottom Right Corner
            ofVec2f tip_point = ofVec2f(block_width*j, block_height*i);
            ofVec2f base_left = ofVec2f(block_width*(j-2), block_height*(i-1));
            ofVec2f base_right = ofVec2f(block_width*j, block_height*(i-1));
            ofDrawTriangle(tip_point, base_left, base_right);
        }
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
