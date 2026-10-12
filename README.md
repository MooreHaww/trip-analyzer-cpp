# Trip Analyzer (C++)

Reads a CSV of trip records and reports:

- **Top zones**: the pickup zones with the most trips
- **Top busy slots**: the busiest (zone, hour-of-day) pairs

Trips are counted with a hash map (`std::unordered_map`) for O(1) average updates, and
(zone, hour) pairs with a `std::map`. Results are sorted with deterministic tie-breaking.
Malformed rows are skipped, so the analyzer scales from small files to millions of rows.

| File | Purpose |
|---|---|
| `analyzer.h`, `analyzer.cpp` | `TripAnalyzer`: `ingestFile`, `topZones(k)`, `topBusySlots(k)` |
| `main.cpp` | Loads `SmallTrips.csv` and prints both reports |
| `SmallTrips.csv` | Sample dataset |

## Build and run

```bash
make run
```

or without make: `g++ -std=c++17 -O2 main.cpp analyzer.cpp -o app && ./app`

Term project for Data Structures (CMP2003), Bahçeşehir University.
