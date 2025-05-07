/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Joel Burlingame
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "replacement.h"

// TODO: Add your implementation of the Replacement member functions here

// Constructor
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
	this->num_pages = num_pages;
    this->num_frames = num_frames;
    this->free_frames = num_frames;
    this->num_references = 0;
    this->num_page_faults = 0;
    this->num_page_replacements = 0;
}

// Destructor
Replacement::~Replacement()
{
    // TOOD: Add your code here
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    num_references++;
    if(page_table[page_num].valid){
        touch_page(page_num);
        if(is_write){
            page_table[page_num].dirty = true;
        }
        return false;
    }else{
        num_page_faults++;
        if(free_frames > 0){
            load_page(page_num);
            free_frames--;
        }else{
            int victim_page = replace_page(page_num);
            num_page_replacements++;
            page_table[victim_page].valid = false;
        }
        if(is_write){
            page_table[page_num].dirty = true;
        }
        return true;
    }
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
        // TODO: print out the number of references, number of page faults and number of page replacements
		std::cout << "Number of references: \t\t" << num_references << std::endl;
        std::cout << "Number of page faults: \t\t" << num_page_faults << std::endl;
        std::cout << "Number of page replacements: \t" << num_page_replacements << std::endl;
}