class LRUCache { 
    
    // REMEMBER, LRUCache benefits greatly from sporadic
    // but necesssary SPRING CLEANINGS !!!!!!!
    // A "spring cleaning" is the removal of gaps within a continuous
    // block of memory (e.g. vector, array)
    
        // The important thing is, it is ok to have gaps in
                 // the contiguous data structure. "Spring cleaning"
                 // the my_queue is important for efficiency, but should
                 // be done infrequently, only when it needs to be done,
                 // so that amortized time complexity per get() and put()
                 // is O(1). 
    
                 // "Spring cleaning" is done every time delete in middle
                 // of vector. The gap is closed each time, and all
                 // following elements are shifted left, which
                 // uses a lot of time.
    
                 // By alloting a container double the size of the
                 // intended "max", the "spring cleaning" heavy time
                 // investment is spread out over numerous O(1) operations
                 // so overall is still O(1)
    
                 // if just one word or phrase in quotation marks, then
                 // comma should go outside I think; if a whole sentence,
                 // then comma should go inside the quoration marks.
    
                 // Ideally, the first half should be packed,
                 // and the second half should be empty, populated with -1
public:
    int max_size; // the capacity
    int curr_size;
    vector<int> my_queue; // stores keys, by FIFO, place in the queue can
                          // change depending on if it is used again
    unordered_map<int, pair<int, int>> hm;
    // key, pair. Pair is index, value
    int index; // current index of my_queue to insert into, increment
               // until overflow my_queue (double capacity) or reached capacity
    int prev_i; // this is used to speed things up. Instead of searching
                // from i = 0 of my_queue for the LRU (least recently
                // used) key, start the search from the previous location
                // of the LRU key. elements migrate to the right, so
                // will be checking for LRU key for a longer and longer 
                // time if all elements are on the right part of my_queue
    LRUCache(int capacity) { // There might be some amortized runtime
                             // complexity analysis
        prev_i = 0;
        index = 0; // don't forget to assign value to public variables!
        max_size = capacity;
        curr_size = 0;
        for(int i = 0; i < 2 * max_size; ++i){
            my_queue.push_back(-1); // -1, because 0 is a valid key
        }
    }
    
    int get(int key) {
        if(index == my_queue.size()){
            int i = 0; // serves as index, also to count number of
                       // keys placed in re-cleaned, neat position without
                       // gaps, "spring-cleaned."
            for(int j = 0; j < my_queue.size() && i < curr_size; ++j){
                if(my_queue[j] == -1){ // skip gaps
                    continue;
                }
                (hm[my_queue[j]]).first = i; // update the index in pair
                my_queue[i] = my_queue[j];
                if(i != j){
                    my_queue[j] = -1; // reassign to -1, since key 
                                      // relocated. if i == j, then don't
                                      // do this (or else will overwrite!)
                }
                i += 1;
            }
            index = curr_size; // update index, all gaps are eliminated
                               // within my_queue now. "Spring cleaning."
            prev_i = 0;
        }
        // I think multiple containers in C++
        // have the .count() method.
        if(hm.count(key) == false){ // key not in hashmap
            
//             cout << "my_queue\n";
//             for(int i = 0; i < my_queue.size(); ++i){
//                 cout << my_queue[i] << ' ';
//             } cout << "\n\n";
            
            return -1;
        }else{
            int output = (hm[key]).second;
            my_queue[(hm[key]).first] = -1;
            (hm[key]).first = index;
            my_queue[index] = key;
        
            index += 1;
            
            // cout << "my_queue\n";
            // for(int i = 0; i < my_queue.size(); ++i){
            //     cout << my_queue[i] << ' ';
            // } cout << "\n\n";
            
            return output;
        }
    }
    
    void put(int key, int value) {
        if(index == my_queue.size()){
            int i = 0; // serves as index, also to count number of
                       // keys placed in re-cleaned, neat position without
                       // gaps, "spring-cleaned."
            for(int j = 0; j < my_queue.size() && i < curr_size; ++j){
                if(my_queue[j] == -1){ // skip gaps
                    continue;
                }
                (hm[my_queue[j]]).first = i; // update the index in pair
                my_queue[i] = my_queue[j];
                if(i != j){
                    my_queue[j] = -1; // reassign to -1, since key 
                                      // relocated. if i == j, then don't
                                      // do this (or else will overwrite!)
                }
                i += 1;
            }
            index = curr_size; // update index, all gaps are eliminated
                               // within my_queue now. "Spring cleaning."
            prev_i = 0;
        }
        
        // after checking if spring cleaning needed,
        // index is guaranteed to be within my_queue bounds
        
        if(hm.count(key) == true){ // key already exists, so size of hm
                                   // stays the same. Capacity only may
                                   // overflow after adding a NEW key.
            my_queue[(hm[key]).first] = -1; // erase it,
                                            // going to be relocated
            (hm[key]).second = value; // update value
            (hm[key]).first = index; // update index, make this the most
                                     // recent key!
            my_queue[index] = key; // place key as most recent into 
                                   //my_queue
            index += 1; // increment index for next query (function call)
        }else{ // else if(hm.count(key) == false)
            my_queue[index] = key;
            hm.insert({key, make_pair(index, value)});
            index += 1;
            curr_size += 1;
            if(curr_size > max_size){
                // remember, the scope of a variable only exists inside
                // the curly bracket scope that it is in! This includes
                // conditional if-else blocks, not only for loops!
                // once } closes the scope, the local variables are
                // destroyed.
                for(int i = prev_i; i < my_queue.size(); ++i){
                    // could use an auxiliary variable to keep track of
                    // index of previous oldest key to make runtime
                    // better.
                    if(my_queue[i] != -1){
                        prev_i = i;
                        hm.erase(my_queue[i]); // remove from LRU cache
                        my_queue[i] = -1; // clear position
                        curr_size -= 1;
                        break;
                    }
                }
            }
        }
        // cout << "my_queue\n";
        // for(int i = 0; i < my_queue.size(); ++i){
        //     cout << my_queue[i] << ' ';
        // } cout << "\n\n";
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */