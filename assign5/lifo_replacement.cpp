/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Joel Burlingame
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    
}

LIFOReplacement::~LIFOReplacement() {
   
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    int frame = free_frame_queue.front();
    free_frame_queue.pop();
    used_frames.insert(frame);

    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;

    lifo_stack.push(page_num);
}

// Access an invalid page and no free frames are available

int LIFOReplacement::replace_page(int page_num){
    int victim_page = lifo_stack.top();
    lifo_stack.pop();

    int frame = page_table[victim_page].frame_num;

    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;

    lifo_stack.push(page_num);
    
    return victim_page;
}