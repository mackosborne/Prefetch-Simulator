//
// This file contains all of the implementations of the replacement_policy
// constructors from the replacement_policies.h file.
//
// It also contains stubs of all of the functions that are added to each
// replacement_policy struct at construction time.
//
// ============================================================================
// NOTE: It is recommended that you read the comments in the
// replacement_policies.h file for further context on what each function is
// for.
// ============================================================================
//
#include <stdio.h>
#include <stdlib.h>
#include "replacement_policies.h"

// LRU Replacement Policy
// ============================================================================
// TODO feel free to create additional structs/enums as necessary

void lru_cache_access(struct replacement_policy *replacement_policy,
                      struct cache_system *cache_system, uint32_t set_idx, uint32_t tag)
{
    // TODO update the LRU replacement policy state given a new memory access
    int set_start = set_idx * cache_system->associativity;
        struct cache_line *start = &cache_system->cache_lines[set_start];
     
        for (int i = 0; start + i < start + cache_system->associativity; i++) {
            if ((start + i)->status != INVALID && (start + i)->tag == tag) {
                //return (start + i) ;
                ((int*)replacement_policy->data)[set_start+i] = 0;
                //printf("Test");
                
                
            }
            else if((start + i) ->status != INVALID)
            {
                
                ((int*)replacement_policy->data)[set_start+i] += 1;
            }
        }
}

uint32_t lru_eviction_index(struct replacement_policy *replacement_policy,
                            struct cache_system *cache_system, uint32_t set_idx)
{
    // TODO return the index within the set that should be evicted.

    int set_start = set_idx * cache_system->associativity;
    struct cache_line *start = &cache_system->cache_lines[set_start];
    int max = 0;
    int index;
    for (int i = 0; start + i < start + cache_system->associativity; i++) {
            
            
            if( ((int*)replacement_policy->data)[set_start+i] > max) {
                max = ((int*)replacement_policy->data)[set_start+i];
                index = i;
            }
    }   
    return index;
}

void lru_replacement_policy_cleanup(struct replacement_policy *replacement_policy)
{
    // TODO cleanup any additional memory that you allocated in the
    // lru_replacement_policy_new function.
    free(replacement_policy->data);
}

struct replacement_policy *lru_replacement_policy_new(uint32_t sets, uint32_t associativity)
{
    struct replacement_policy *lru_rp = calloc(1, sizeof(struct replacement_policy));
    lru_rp->cache_access = &lru_cache_access;
    lru_rp->eviction_index = &lru_eviction_index;
    lru_rp->cleanup = &lru_replacement_policy_cleanup;

    // TODO allocate any additional memory to store metadata here and assign to
    lru_rp->data=(int*)malloc(associativity * sets * sizeof(int));
    return lru_rp;
}

// RAND Replacement Policy
// ============================================================================
void rand_cache_access(struct replacement_policy *replacement_policy,
                       struct cache_system *cache_system, uint32_t set_idx, uint32_t tag)
{
    // TODO update the RAND replacement policy state given a new memory access
}

uint32_t rand_eviction_index(struct replacement_policy *replacement_policy,
                             struct cache_system *cache_system, uint32_t set_idx)
{
    // TODO return the index within the set that should be evicted.

    int index = rand() % cache_system->associativity;
    return index;
}

void rand_replacement_policy_cleanup(struct replacement_policy *replacement_policy)
{
    // TODO cleanup any additional memory that you allocated in the
    // rand_replacement_policy_new function.
    free(replacement_policy->data);
}

struct replacement_policy *rand_replacement_policy_new(uint32_t sets, uint32_t associativity)
{
    // Seed randomness
    srand(time(NULL));

    struct replacement_policy *rand_rp = malloc(sizeof(struct replacement_policy));
    rand_rp->cache_access = &rand_cache_access;
    rand_rp->eviction_index = &rand_eviction_index;
    rand_rp->cleanup = &rand_replacement_policy_cleanup;

    // TODO allocate any additional memory to store metadata here and assign to
    // rand_rp->data.

    return rand_rp;
}

// LRU_PREFER_CLEAN Replacement Policy
// ============================================================================
void lru_prefer_clean_cache_access(struct replacement_policy *replacement_policy,
                                   struct cache_system *cache_system, uint32_t set_idx,
                                   uint32_t tag)
{
    // TODO update the LRU_PREFER_CLEAN replacement policy state given a new
    // memory access
    // NOTE: you may be able to share code with the LRU policy
    int set_start = set_idx * cache_system->associativity;
        struct cache_line *start = &cache_system->cache_lines[set_start];
     
        for (int i = 0; start + i < start + cache_system->associativity; i++) {
            if ((start + i)->status != INVALID && (start + i)->tag == tag) {
                
                ((int*)replacement_policy->data)[set_start+i] = 0;
                
                
                
            }
            else if((start + i) ->status != INVALID)
            {
                
                ((int*)replacement_policy->data)[set_start+i] += 1;
            }
        }
}

uint32_t lru_prefer_clean_eviction_index(struct replacement_policy *replacement_policy,
                                         struct cache_system *cache_system, uint32_t set_idx)
{
    // TODO return the index within the set that should be evicted.

    int set_start = set_idx * cache_system->associativity;
    struct cache_line *start = &cache_system->cache_lines[set_start];
    int max = -1;
    int index;
    int foundClean = 0;
    for (int i = 0; start + i < start + cache_system->associativity; i++) {
            
            
        if( ((int*)replacement_policy->data)[set_start+i] > max && (start + i)->status == EXCLUSIVE)
        {
            max = ((int*)replacement_policy->data)[set_start+i];
            index = i;
            foundClean = 1;
        }
    }
    if (foundClean != 1)
        {
            for (int i = 0; start + i < start + cache_system->associativity; i++) 
            {
                if( ((int*)replacement_policy->data)[set_start+i] > max) 
                {
                    max = ((int*)replacement_policy->data)[set_start+i];
                    index = i;
                }
            }    
        }    
       
    return index;
}

void lru_prefer_clean_replacement_policy_cleanup(struct replacement_policy *replacement_policy)
{
    // TODO cleanup any additional memory that you allocated in the
    // lru_prefer_clean_replacement_policy_new function.
    free(replacement_policy->data);
}

struct replacement_policy *lru_prefer_clean_replacement_policy_new(uint32_t sets,
                                                                   uint32_t associativity)
{
    struct replacement_policy *lru_prefer_clean_rp = malloc(sizeof(struct replacement_policy));
    lru_prefer_clean_rp->cache_access = &lru_prefer_clean_cache_access;
    lru_prefer_clean_rp->eviction_index = &lru_prefer_clean_eviction_index;
    lru_prefer_clean_rp->cleanup = &lru_prefer_clean_replacement_policy_cleanup;

    // TODO allocate any additional memory to store metadata here and assign to
    // lru_prefer_clean_rp->data.
    lru_prefer_clean_rp->data=(int*)malloc(associativity * sets * sizeof(int));
    return lru_prefer_clean_rp;
}
