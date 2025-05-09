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

// TODO: Add your implementation here
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
LIFOReplacement::~LIFOReplacement() {
   
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
   int frame = 0;
   while (frame < num_frames) {
       bool frame_in_use = false;
       
       for (int i = 0; i < num_pages; i++) {
           if (page_table[i].valid && page_table[i].frame_num == frame) {
               frame_in_use = true;
               break;
           }
       }
       if (!frame_in_use) {
           break;  
       }
       frame++;
   }
   
   // Assign the free frame to the page
   page_table[page_num].frame_num = frame;
   page_table[page_num].valid = true;
   
   // Add the page to the LIFO stack
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