// main.cpp is a lightweight local tester.
//
// Purpose:
// 1- Load a data file, run the analyzer, and display the top zones / busy slots.
// 2- Help you verify output format and correctness on your own machine.
//
// Look: This file is NOT submitted and is NOT part of the automated grading.

#include "analyzer.h"
#include <iostream>
#include <chrono> // Used to measure execution time locally (helps us sanity-check performance).

using namespace std;

// Prints the "TOP_ZONES" section exactly as expected by the project output format.
// We keep this separate so main stays clean.
static void printZones(const vector<ZoneCount> &v)
{
    cout << "TOP_ZONES\n";
    for (auto &x : v) // Each line: zone,count
        cout << x.zone << "," << x.count << "\n";
}

static void printSlots(const vector<SlotCount> &v)
{
    cout << "TOP_SLOTS\n";
    for (auto &x : v)
        cout << x.zone << "," << x.hour << "," << x.count << "\n";
}

// main() flow for local testing:
// 1. Start timer
// 2. Ingest the CSV and build counts
// 3. Output top zones and busy slots
// 4. Print runtime in milliseconds
// To verify correctness, compare the output against expected results.
int main()
{
    auto t0 = chrono::high_resolution_clock::now(); // Start timing before we ingest and compute results.
    TripAnalyzer analyzer;
    analyzer.ingestFile("SmallTrips.csv");

    printZones(analyzer.topZones(10));                                      // Compute and print the top 10 zones
    printSlots(analyzer.topBusySlots(10));                                  // Compute and print the top 10 busiest (zone, hour)
    auto t1 = chrono::high_resolution_clock::now();                         // Stop timing after all computation and printing.
    auto ms = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count(); // Convert the elapsed time to milliseconds.

    cout << "EXEC_MS\n"
         << ms << "\n";
    return 0;
}