#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

vector<vector<string>> read(string file_name){
    ifstream in(file_name);
    vector<vector<string>> data;
    vector<string> values;
    string line, field;
    while (getline(in,line)){
        values.clear();
        stringstream ss(line);
        while(getline(ss,field,',')){
            values.push_back(field);
        }
        data.push_back(values);
    }
    return data;
}

void FCFS(vector<vector<string>> data){
    int num_processes = data.size();
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    int total_service_time = 0;
    float average_wait_time = 0.000;
    float average_turnaround_time = 0.000;
    float throughput_time = 0.000;
    vector<int> service_time(num_processes);
    vector<int> wait_time(num_processes);
    vector<int> completion_time(num_processes);
    vector<int> turnaround_time(num_processes);

    for (int i = 0; i < num_processes-1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (stoi(data[j][1]) > stoi(data[j + 1][1])) {
                swap(data[j], data[j + 1]);
            }
        }
    }
    for(int i = 0; i < num_processes; i++){
        if (i == 0) {
            service_time[0] = stoi(data[0][2]);
            completion_time[0] = stoi(data[0][1]) + stoi(data[0][2]);
        } else {
            service_time[i] = service_time[i - 1] + stoi(data[i][2]);
            completion_time[i] = completion_time[i - 1] + stoi(data[i][2]);
        }
        if (i > 0) {
            wait_time[i] = service_time[i - 1] - stoi(data[i][1]);
        } else {
            wait_time[i] = 0;
        }
        turnaround_time[i] = completion_time[i] - stoi(data[i][1]);
        total_turnaround_time += turnaround_time[i];
        total_wait_time += wait_time[i];
        total_service_time += stoi(data[i][2]);
    }
    average_wait_time = static_cast<float>(total_wait_time) / static_cast<float>(num_processes);
    average_turnaround_time = static_cast<float>(total_turnaround_time) / static_cast<float>(num_processes);
    throughput_time = static_cast<float>(num_processes) / static_cast<float>(total_service_time);
    cout << "--- FCFS ---" << "\n";
    cout << fixed << setprecision(3) << "Average Turnaround Time: " << average_turnaround_time << "\n";
    cout << setprecision(3) << "Average Waiting Time: " << average_wait_time << "\n";
    cout << setprecision(3) << "Throughput: " << throughput_time  << "\n";
}

void SJFP(vector<vector<string>> data){
    int num_processes = data.size();
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    int total_service_time = 0;
    int current_time = 0;
    int completed_processes = 0;
    float average_wait_time = 0.000;
    float average_turnaround_time = 0.000;
    float throughput_time = 0.000;
    vector<int> service_time(num_processes);
    vector<int> wait_time(num_processes);
    vector<int> completion_time(num_processes);
    vector<int> turnaround_time(num_processes);
    vector<bool> process_done(num_processes, false);

    while (completed_processes < num_processes) {
        int max_service_time = 1000000;
        int min_service_time = -1;
        bool found = false;
        for (int i = 0; i < num_processes; ++i) {
            if (!process_done[i] && stoi(data[i][1]) <= current_time && stoi(data[i][2]) < max_service_time) {
                max_service_time = stoi(data[i][2]);
                min_service_time = i;
                found = true;
            }
        }
        if (!found) {
            current_time++;
        }
        current_time++;
        service_time[min_service_time]++;
        if (service_time[min_service_time] == stoi(data[min_service_time][2])) {
            process_done[min_service_time] = true;
            completed_processes++;
            completion_time[min_service_time] = current_time;
            turnaround_time[min_service_time] = completion_time[min_service_time] - stoi(data[min_service_time][1]);
            wait_time[min_service_time] = turnaround_time[min_service_time] - stoi(data[min_service_time][2]);
            total_turnaround_time += turnaround_time[min_service_time];
            total_wait_time += wait_time[min_service_time];
            total_service_time += stoi(data[min_service_time][2]);
        }
    }
    average_wait_time = static_cast<float>(total_wait_time) / static_cast<float>(num_processes);
    average_turnaround_time = static_cast<float>(total_turnaround_time) / static_cast<float>(num_processes);
    throughput_time = static_cast<float>(num_processes) / static_cast<float>(total_service_time);
    cout << "--- SJFP ---" << "\n";
    cout << fixed << setprecision(3) << "Average Turnaround Time: " << average_turnaround_time << "\n";
    cout << setprecision(3) << "Average Waiting Time: " << average_wait_time << "\n";
    cout << setprecision(3) << "Throughput: " << throughput_time  << "\n";
}
void Priority(vector<vector<string>> data){
    int num_processes = data.size();
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    int total_service_time = 0;
    int current_time = 0;
    int completed_processes = 0;
    float average_wait_time = 0.000;
    float average_turnaround_time = 0.000;
    float throughput_time = 0.000;
    vector<int> service_time(num_processes);
    vector<int> wait_time(num_processes);
    vector<int> completion_time(num_processes);
    vector<int> turnaround_time(num_processes);
    vector<bool> process_done(num_processes, false);

    while (completed_processes < num_processes) {
        int max_priority = 1000000;
        int min_priority = -1;
        bool found = false;
        for (int i = 0; i < num_processes; ++i) {
            if (!process_done[i] && stoi(data[i][1]) <= current_time && stoi(data[i][3]) < max_priority) {
                max_priority = stoi(data[i][3]);
                min_priority = i;
                found = true;
            }
        }
        if (!found) {
            current_time++;
        }
        current_time++;
        service_time[min_priority]++;

        if (service_time[min_priority] == stoi(data[min_priority][2])) {
            process_done[min_priority] = true;
            completed_processes++;
            completion_time[min_priority] = current_time;
            turnaround_time[min_priority] = completion_time[min_priority] - stoi(data[min_priority][1]);
            wait_time[min_priority] = turnaround_time[min_priority] - stoi(data[min_priority][2]);
            total_turnaround_time += turnaround_time[min_priority];
            total_wait_time += wait_time[min_priority];
            total_service_time += stoi(data[min_priority][2]);
        }
    }
    average_wait_time = static_cast<float>(total_wait_time) / static_cast<float>(num_processes);
    average_turnaround_time = static_cast<float>(total_turnaround_time) / static_cast<float>(num_processes);
    throughput_time = static_cast<float>(num_processes) / static_cast<float>(total_service_time);
    cout << "--- Priority ---" << "\n";
    cout << fixed << setprecision(3) << "Average Turnaround Time: " << average_turnaround_time << "\n";
    cout << setprecision(3) << "Average Waiting Time: " << average_wait_time << "\n";
    cout << setprecision(3) << "Throughput: " << throughput_time  << "\n";
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        cerr << "Error: Incorrect number of arguments. Please try again.";
        return 1;
    }
    string input_file = argv[1];
    vector<vector<string>> data = read(input_file);
    FCFS(data);
    SJFP(data);
    Priority(data);
    
}