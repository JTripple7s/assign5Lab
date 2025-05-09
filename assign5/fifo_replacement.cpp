/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Joel Burlingame
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"
#include <iostream>

// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{

}

FIFOReplacement::~FIFOReplacement() {

}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {

    if (free_frame_queue.empty()) {
        std::cerr << "Error: No free frames available" << std::endl;

        return;
    }

   int frame = free_frame_queue.front();
   free_frame_queue.pop();

   if (frame < 0 || frame >= num_frames) {
        std::cerr << "Error: Invalid frame number " << frame << std::endl;
        return;
    }

   //used_frames.insert(frame);

   page_table[page_num].frame_num = frame;
   page_table[page_num].valid = true;

   fifo_queue.push(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {

    if (fifo_queue.empty()) {
        std::cerr << "Error: FIFO queue is empty when trying to replace a page" << std::endl;

        return 0;  // Return a default page
    }

    int victim_page = fifo_queue.front();
    fifo_queue.pop();

    if (!page_table[victim_page].valid) {
        std::cerr << "Error: Victim page " << victim_page << " is not valid" << std::endl;

        return victim_page;
    }

    int frame = page_table[victim_page].frame_num;

    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;

    fifo_queue.push(page_num);

    return victim_page;
}
