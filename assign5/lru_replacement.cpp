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

// TODO: Add your implementations for desctructor, touch_page, load_page, replace_page here
LRUReplacement::~LRUReplacement()
{
    
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    auto it = std::find(lru_list.begin(), lru_list.end(), page_num);
    if (it != lru_list.end()) {
        lru_list.erase(it);
    }
    
    lru_list.push_front(page_num);
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
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
            break;  // Found a free frame
        }

        frame++;
    }

    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;
    
    lru_list.push_front(page_num);
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    int victim_page = lru_list.back();
    lru_list.pop_back();
    
    int frame = page_table[victim_page].frame_num;
    page_table[page_num].frame_num = frame;
    page_table[page_num].valid = true;
    
    lru_list.push_front(page_num);
    
    return victim_page;
}