<div align="center">

# 🚕 Trip Analyzer

**Find the busiest pickup zones and rush hours in a pile of trip records, fast and in the same order every time.**

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![STL only](https://img.shields.io/badge/dependencies-STL%20only-success?style=for-the-badge)
![Build](https://img.shields.io/badge/build-make-orange?style=for-the-badge)
![Course](https://img.shields.io/badge/course-Data%20Structures-8A2BE2?style=for-the-badge)

</div>

---

## 💡 Why this project exists

Ride-hailing and taxi companies sit on millions of trip rows. The first questions they ask are simple: *which zones are busiest, and at what hour?* Answering that on a big CSV is a data-structures problem: pick the wrong container and the program crawls, pick the right one and it finishes almost instantly.

This was my **Data Structures term project**. The goal was to read a trip file once, count efficiently, and print results that are always in the same order, so an automatic grader can compare the output exactly.

## 🔎 What it does

It reads a CSV of trips and prints three things:

| Section | Meaning |
|---|---|
| `TOP_ZONES` | The pickup zones with the most trips (`zone,count`) |
| `TOP_SLOTS` | The busiest (zone, hour-of-day) pairs (`zone,hour,count`) |
| `EXEC_MS` | How long the whole run took, in milliseconds |

Features:

- **One pass over the file.** Every row updates the counts as it is read.
- **Dirty-data tolerant.** Empty lines, rows with fewer than 6 columns, missing zones and bad timestamps are skipped instead of crashing the program. The header row is detected and ignored.
- **Deterministic output.** Ties are broken the same way every run: zones by count (high to low) then name (A to Z); slots by count, then zone, then hour.
- **Top-K on demand.** `topZones(k)` and `topBusySlots(k)` return any number of results.

Input format (`SmallTrips.csv`, 5,000+ rows included as a sample):

```text
TripID,PickupZoneID,DropoffZoneID,PickupDateTime,DistanceKm,FareAmount
1000001,ZONE254,ZONE819,2024-01-01 00:00,16.0,74.9
```

## ⚙️ Setup

You need a C++17 compiler (`g++` or `clang++`). No libraries to install.

```bash
git clone https://github.com/MooreHaww/trip-analyzer-cpp.git
cd trip-analyzer-cpp
make run
```

No `make` (for example on plain Windows)? Compile directly:

```bash
g++ -std=c++17 -O2 main.cpp analyzer.cpp -o app
./app
```

Sample output on the included `SmallTrips.csv`:

```text
TOP_ZONES
ZONE_MAIN_A,506
ZONE_MAIN_B,498
...
TOP_SLOTS
ZONE_MAIN_A,11,31
...
EXEC_MS
6
```

The whole sample file is analysed in about **6 ms** (measured in my test run; yours will differ a little).

## 🎯 What I wanted to learn

- Choose the right container for the job: a hash map for fast counting versus an ordered map for pairs.
- Reason about time complexity: counting is O(1) on average per row, so the file is read in a single O(n) pass.
- Write parsing code that survives messy real-world data.
- Make output deterministic with an explicit comparison function, instead of relying on hash-map order (which is arbitrary).
- Split a C++ program into a header (the contract) and an implementation file, with a tiny `main.cpp` for local testing.

## 🏗️ How it was built

| File | Role |
|---|---|
| `analyzer.h` | The contract: `TripAnalyzer`, `ZoneCount`, `SlotCount` |
| `analyzer.cpp` | The work: CSV parsing, counting, sorting |
| `main.cpp` | Local tester that loads `SmallTrips.csv`, prints both reports and the run time |
| `Makefile` | `make`, `make run`, `make clean` |

**Design decisions**

- `std::unordered_map<string, long long>` counts trips per zone: average O(1) per update.
- `std::map<pair<string,int>, long long>` counts (zone, hour) pairs. A pair has no built-in hash, and an ordered map keeps the code simple.
- Only the pickup zone and pickup time are used, but a row must still have all 6 columns to count. A shorter row is treated as damaged.
- The hour is cut out of `YYYY-MM-DD HH:MM` by hand and checked to be 0 to 23.
- Results are copied into a vector and sorted with a custom comparator (see "Deterministic output" above).

**Build order**

1. Define the data structures and the class interface.
2. Write the CSV line splitter and the hour parser, with checks for bad input.
3. Write `ingestFile` and count zones and slots in one pass.
4. Write the two top-K functions with tie-breaking.
5. Add `main.cpp` and a timer, then test on the sample file.

## 🗺️ Plan / what's next

- [x] Single-pass analyzer with top zones and busy slots
- [x] Tolerates dirty rows
- [ ] Take the file path and K from the command line instead of hard-coding them
- [ ] Add unit tests for the parser and the tie-breaking rules
- [ ] Benchmark on a multi-million-row file
- [ ] Try a faster hash for the (zone, hour) pairs and compare

## 📄 Notes

Built for a university Data Structures course. The sample data is synthetic.
