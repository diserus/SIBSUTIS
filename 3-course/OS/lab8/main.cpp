#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <pthread.h>

long long sequential_sum(const std::vector<int>& data) {
    long long sum = 0;
    for (int value : data) {
        sum += value;
    }
    return sum;
}

struct PthreadArgs {
    const std::vector<int>* data;
    size_t start;
    size_t end;
    long long partial_sum;
};

void* pthread_partial_sum(void* arg) {
    PthreadArgs* args = static_cast<PthreadArgs*>(arg);
    args->partial_sum = 0;
    for (size_t i = args->start; i < args->end; ++i) {
        args->partial_sum += (*args->data)[i];
    }
    return nullptr;
}

long long pthreads_sum(const std::vector<int>& data, size_t num_threads) {
    std::vector<pthread_t> threads(num_threads);
    std::vector<PthreadArgs> args(num_threads);
    size_t chunk_size = data.size() / num_threads;

    for (size_t i = 0; i < num_threads; ++i) {
        args[i] = {&data, i * chunk_size, (i + 1) * chunk_size, 0};
        if (i == num_threads - 1) {
            args[i].end = data.size(); 
        }
        pthread_create(&threads[i], nullptr, pthread_partial_sum, &args[i]);
    }

    long long total_sum = 0;
    for (size_t i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], nullptr);
        total_sum += args[i].partial_sum;
    }
    return total_sum;
}

long long std_threads_sum(const std::vector<int>& data, size_t num_threads) {
    std::vector<std::thread> threads;
    std::vector<long long> partial_sums(num_threads, 0);
    size_t chunk_size = data.size() / num_threads;

    auto worker = [&data](size_t start, size_t end, long long& result) {
        result = 0;
        for (size_t i = start; i < end; ++i) {
            result += data[i];
        }
    };

    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? data.size() : (i + 1) * chunk_size;
        threads.emplace_back(worker, start, end, std::ref(partial_sums[i]));
    }

    for (auto& t : threads) {
        t.join();
    }

    long long total_sum = 0;
    for (long long partial : partial_sums) {
        total_sum += partial;
    }
    return total_sum;
}

int main() {
    const size_t data_size = 100000000;
    const size_t num_threads = std::thread::hardware_concurrency();

    std::vector<int> data;
    data.reserve(data_size);
    for (size_t i = 0; i < data_size; ++i) {
        data.push_back(i + 1);
    }

    
    auto start = std::chrono::high_resolution_clock::now();
    long long seq_sum = sequential_sum(data);
    auto end = std::chrono::high_resolution_clock::now();
    auto seq_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Sequential sum: " << seq_sum << " Time: " << seq_duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    long long pthread_sum = pthreads_sum(data, num_threads);
    end = std::chrono::high_resolution_clock::now();
    auto pthread_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Pthreads sum: " << pthread_sum << " Time: " << pthread_duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    long long std_thread_sum = std_threads_sum(data, num_threads);
    end = std::chrono::high_resolution_clock::now();
    auto std_thread_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Std::thread sum: " << std_thread_sum << " Time: " << std_thread_duration.count() << " ms\n";

    
    return 0;
}