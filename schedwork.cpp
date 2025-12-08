#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtracker(const AvailabilityMatrix& avail,
                 const size_t dailyNeed,
                 const size_t maxShifts,
                 DailySchedule& sched,
                 unsigned int day,
                 unsigned int col,
                 std::vector<size_t>& worker_shifts);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    unsigned int days = avail.size();
    unsigned int workers = avail[0].size();

    sched.resize(days);
    for (unsigned int i = 0; i < days; i++){
      sched[i].resize(dailyNeed, INVALID_ID);
    }

    //keep track of how many shifts per worker
    std::vector<size_t> worker_shifts(workers, 0);

    return backtracker(avail, dailyNeed, maxShifts, sched, 0, 0, worker_shifts);

//sched works like
//sched[`day`][`slot`] and outputs the worker #


}

bool backtracker(const AvailabilityMatrix& avail,
                 const size_t dailyNeed,
                 const size_t maxShifts,
                 DailySchedule& sched,
                 unsigned int day,
                 unsigned int col,
                 std::vector<size_t>& worker_shifts){
  //start

  //if we are at the end of the col, move to next day
  if (col == dailyNeed) {
    return backtracker(avail, dailyNeed, maxShifts, sched, day + 1, 0, worker_shifts);
  }

  //base case: all days are accounted for
  if (day == avail.size()){
    return true;
  }

  for (Worker_T worker = 0; worker < avail[0].size(); ++worker){
    //check if the worker is available
    if (avail[day][worker] == true){

      //check shift limit
      if (worker_shifts[worker] < maxShifts){

        //just because they are available != they are not working!
        //if they aren't already working today, TRY:
        bool working_today = (std::find(sched[day].begin(), sched[day].begin() + col, worker)
                              != sched[day].begin() + col);

        if (!working_today){
          sched[day][col] = worker;
          worker_shifts[worker]++;

          //recurse until all rows and cols are hit
          if (backtracker(avail, dailyNeed, maxShifts, sched, day, col + 1, worker_shifts)){
            return true;
          }

          //BACKTRACK HERE, we hit the "false"
          worker_shifts[worker]--;
          sched[day][col] = INVALID_ID;
        }
      }
    }
  }
  //if no worker fits, then this path was wrong and backtrack
  return false;
}