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

    for(int i = 0; i < num_frames; i++){
        free_frame_queue.push(i);
    }
}

// Destructor
Replacement::~Replacement()
{

}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    // Check if the page number is valid
    if (page_num < 0 || page_num >= num_pages) {
        std::cerr << "Error: Page number " << page_num << " out of range (0-" << (num_pages-1) << ")" << std::endl;
        return false;
    }
    
    num_references++;
    
    // Check if the page is valid (already in memory)
    if (page_table[page_num].valid) {
        touch_page(page_num);
        
        // If this is a write operation, mark the page as dirty
        if (is_write) {
            page_table[page_num].dirty = true;
        }
        
        return false;  // No page fault

    } else {
        // Page is not in memory, it's a page fault
        num_page_faults++;
        
        if (free_frames > 0) {
            load_page(page_num);
            free_frames--;

        } else {
            int victim_page = replace_page(page_num);
            num_page_replacements++;

            if (victim_page < 0 || victim_page >= num_pages) {
                std::cerr << "Error: Invalid victim page " << victim_page << std::endl;
            } else {

                page_table[victim_page].valid = false;
            }
        }
        
        // If this is a write operation, mark the page as dirty
        if (is_write) {
            page_table[page_num].dirty = true;
        }
        
        return true;  // Page fault occurred
    }
}


// Print out statistics of simulation
void Replacement::print_statistics() const {

		std::cout << "Number of references: \t\t" << num_references << std::endl;
        std::cout << "Number of page faults: \t\t" << num_page_faults << std::endl;
        std::cout << "Number of page replacements: \t" << num_page_replacements << std::endl;
}