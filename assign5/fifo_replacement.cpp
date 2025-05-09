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

// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Add additional implementation code
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
FIFOReplacement::~FIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
   int frame = 0;
   while (frame < num_frames){
    bool frame_in_use = false;

    for(int i = 0; i < num_pages; i++){
        if(page_table[i].valid && page_table[i].frame_num == frame){
            frame_in_use = true;
            break;
        }
    }
    if(!frame_in_use){
        break;
    }
    frame++;

   }
   page_table[page_num].frame_num = frame;
   page_table[page_num].valid = true;

   fifo_queue.push(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    int victim_page = fifo_queue.front();
    fifo_queue.pop();

    int frame = page_table[victim_page].frame_num;
    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;

    fifo_queue.push(page_num);
    return victim_page;
}