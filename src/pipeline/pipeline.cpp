// contains the 5 stages as classes 

// class pipeline_stage { // superclass
//  int stage_id 
//  uint_32t result? a place to store where the next stage can read the value from
//  bool blocked or free? 
//  pointer to next stage
//  pointer to prev stage
//  uint32 cur instruction 
//}


// class fetch extends pipeline_stage// subclasses that extend pipeline_stage
    // fetch has a pointer to memory 
// class decode
// class execute
// class memory
    // memory has a pointer to the same memory 
// class writeback



//registers will be an array declared in our driver program because they need to be in memory 
