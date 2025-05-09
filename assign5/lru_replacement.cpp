/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Joel Burlingame
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lru_replacement.h"

// TODO: Add your implementation here
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    
}

LRUReplacement::~LRUReplacement()
{
    
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    lru_list.erase(page_to_iterator[page_num]);
    lru_list.push_front(page_num);

    page_to_iterator[page_num] = lru_list.begin();
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    int frame = free_frame_queue.front();
    free_frame_queue.pop();
    used_frames.insert(frame);

    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;

    lru_list.push_front(page_num);
    
    page_to_iterator[page_num] = lru_list.begin();
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    int victim_page = lru_list.back();
    lru_list.pop_back();
    
    page_to_iterator.erase(victim_page);
    
    int frame = page_table[victim_page].frame_num;
    
    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;
    
    lru_list.push_front(page_num);
    
    page_to_iterator[page_num] = lru_list.begin();
    
    return victim_page;
}