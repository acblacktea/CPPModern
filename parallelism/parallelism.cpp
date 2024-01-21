//
// Created by ByteDance on 21/10/23.
//

#include <thread>
#include <iostream>
#include <mutex>
#include <future>
#include <queue>
#include <atomic>

static std::mutex mtx;
void testThread() {
    int *a = new int(1);
    int *index1 = new int(1);
    int *index2 = new int(2);
    std::thread t([&](){;
        std::thread t2([&](){
            //std::lock_guard<std::mutex> lock(mtx);
            for (int i = 0; i < 500; ++i) {
                std::cout << *index1 << std::endl;
            }

            int stop = 1;
        });

        std::thread t3([&](){
            //std::lock_guard<std::mutex> lock(mtx);
            for (int i = 0; i < 500; ++i) {
                std::cout << *index2 << std::endl;
            }

            int stop = 1;
        });
        t2.detach();
        t3.detach();

        for (int i = 0; i < 500; ++i) {
            std::cout << 3 << std::endl;
        }

        delete index1;
        delete index2;

        int q = 5;
    });


    t.join();
   // std::cout << a << std::endl;
}

int v = 1;
void criticalSection(int changeV) {
    std::lock_guard<std::mutex> lock(mtx);
    v = changeV;
    //std::lock_guard<std>
}

void testMutex() {
    std::thread t1(criticalSection,2), t2(criticalSection,3);
    t1.join();
    t2.join();
    std::cout << v << std::endl;
}

void criticalSection2(int changeV) {
    std::unique_lock<std::mutex> lock(mtx);

    v = changeV;
    std::cout << v << std::endl;
    lock.unlock();

    // ....

    lock.lock();
    v += 1;
    std::cout << v << std::endl;
}

void testUniqueLock() {
   std::thread t1(criticalSection2, 2), t2(criticalSection2, 5);
   t1.join();
   t2.join();
}

void testFuture() {
    std::packaged_task<int()> task([](){
        return 7;
    });

    std::future<int> result = task.get_future();
    std::thread(std::move(task)).detach();
    //std::cout << "waiting...";
    result.wait();

    std::cout << "done!" << std::endl << "future result is " << result.get() << std::endl;
}

void testConditionVariable() {
    std::queue<int> producedNums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false;

    auto producer = [&]() {
        for (int i = 0;; ++i) {
            //std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::unique_lock<std::mutex> lock(mtx);
            //std::cout << "producing " << i << std::endl;
            producedNums.push(i);
            //notified = true;
            //cv.notify_all();
        }
    };

    auto consumer = [&]() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);

            /*
            while (!notified) {
                int qqq = 123;
                //cv.wait(lock);
            }

            lock.unlock();
             */

            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            //lock.lock();
            if (!producedNums.empty()) {
                std::cout << "consuming " << producedNums.front() << " queue size: " << producedNums.size() << std::endl;
                producedNums.pop();
            }

            notified = false;
        }
    };

    std::thread p(producer);
    std::thread cs[2];
    for (int i = 0; i < 2; ++i) {
        cs[i] = std::thread(consumer);
    }

    p.join();
    for (int i = 0; i < 2; ++i) {
        cs[i].join();
    }
}

void testAtomicOperation() {
    int a = 0;
    volatile int flag = 0;

    std::thread t1([&]() {
        while (flag != 1) {
            int qq = 123;
        };

        int b = a;
        std::cout << "b = " << b << std::endl;
    });

    std::thread t2([&]() {
        a = 5;
        flag = 1;
    });

    t1.join();
    t2.join();
}

void testAtomicOperation2() {
    std::atomic<int> count = {0};
    std::thread t1([&](){
        count.fetch_add(1);
    });

    std::thread t2([&](){
        count++;
        count+=1;
    });

    t1.join();
    t2.join();
    std::cout << count << std::endl;
}

struct A {
    float x;
    int y;
    long long z;
};

class B {
public:
    std::string a, b;
    std::vector<int> c;
};

void testAtomic() {
    std::atomic<A> a;
    std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    //std::at<B> b;
    //std::cout << std::boolalpha << b.is_lock_free() << std::endl;
}


void testMemoryOrderRelaxed() {
    std::atomic<int> counter = {0};
    std::vector<std::thread> vt;
    for (int i = 0; i < 100; ++i) {
        vt.emplace_back([&]() {
           counter.fetch_add(1, std::memory_order_relaxed);
        });
    }

    for (auto& t: vt) {
        t.join();
    }

    std::cout << "current counter:" << counter << std::endl;
}

void testMemoryOrderReleaseConsumption() {
    std::atomic<int> ato;

    std::thread producer([&]() {
        ato.store(12);
        ato.fetch_add(1);
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        ato.fetch_add(1);
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        ato.fetch_add(1, std::memory_order_release);
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    });

    std::thread consumer([&]() {
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        int p;
        while (!(p = ato.load(std::memory_order_consume))) {
            int mark = 3;
        };

        std::cout << "p: " << p << std::endl;
    });

    producer.join();
    consumer.join();
}

void testAtomicReleaseAcquire() {
    std::vector<int> v;
    std::atomic<int> flag = {0};
    std::thread release([&]() {
        v.push_back(42);
        flag.store(1, std::memory_order_release);
    });

    std::thread acqrel([&]() {
       int expected = 1;
       while(!flag.compare_exchange_strong(expected, 2, std::memory_order_acq_rel)) {
           expected = 1;
       }
    });

    std::thread acquire([&]() {
       while (flag.load(std::memory_order_acquire) < 2);

       std::cout << v.at(0) << std::endl;
    });

    release.join();
    acqrel.join();
    acquire.join();
}

std::vector<int> data;
std::atomic<int> flag = {0};

void thread_1()
{
    data.push_back(42);
    flag.store(1, std::memory_order_release);
}

void thread_2()
{
    int expected = 1;
    // memory_order_relaxed is okay because this is an RMW,
    // and RMWs (with any ordering) following a release form a release sequence
    while (!flag.compare_exchange_strong(expected, 2, std::memory_order_relaxed))
    {
        expected = 1;
    }
}

void thread_3()
{
    while (flag.load(std::memory_order_acquire) < 2)
        ;
    // if we read the value 2 from the atomic flag, we see 42 in the vector
    assert(data.at(0) == 42); // will never fire
}


void testReleaseAcquireMode()
{
    for (int i = 0; i < 10000; ++i) {
        data.clear();
        flag = 0;
        std::thread a(thread_1);
        std::thread b(thread_2);
        std::thread c(thread_3);
        a.join();
        b.join();
        c.join();
    }
}

struct Storage {
    char      a;
    int       b;
    double    c;
    long long d;
    long double s;
};

struct alignas(std::max_align_t) AlignasStorage {
    char      a;
    int       b;
    double    c;
    long long d;
    long double s;
};

void testMemoryAlignment() {
    std::cout << alignof(Storage) << std::endl;
    std::cout << alignof(AlignasStorage) << std::endl;
}